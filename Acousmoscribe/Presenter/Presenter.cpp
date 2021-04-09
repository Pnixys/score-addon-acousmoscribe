#include <score/command/Dispatchers/CommandDispatcher.hpp>

/* View */
#include <Acousmoscribe/View/View.hpp>
#include <Acousmoscribe/View/SignView.hpp>
#include <Acousmoscribe/View/SpectralKeyView.hpp>
#include <Acousmoscribe/View/MelodicKeyView.hpp>

/* Presenter */
#include <Acousmoscribe/Presenter/Presenter.hpp>

/* Commands */
#include <Acousmoscribe/Commands/AddKey.hpp>
#include <Acousmoscribe/Commands/AddSign.hpp>
#include <Acousmoscribe/Commands/RemoveSigns.hpp>
#include <Acousmoscribe/Commands/ScaleSigns.hpp>


/* Model */
#include <Acousmoscribe/Model/Process.hpp>
#include <Acousmoscribe/Model/Sign.hpp>
#include <Acousmoscribe/Model/Grain.hpp>
#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Acousmoscribe/Model/SpectralKey.hpp>
#include <Acousmoscribe/Model/RhythmicProfile.hpp>
#include <Acousmoscribe/Model/MelodicProfile.hpp>

#include <ossia/detail/algorithms.hpp>
#include <ossia/detail/math.hpp>
#include <score/tools/IdentifierGeneration.hpp>

#include <score/command/Dispatchers/CommandDispatcher.hpp>
#include <score/command/Dispatchers/MacroCommandDispatcher.hpp>
#include <score/document/DocumentContext.hpp>
#include <score/document/DocumentInterface.hpp>
#include <score/tools/Bind.hpp>

#include <core/document/Document.hpp>
#include <core/document/DocumentModel.hpp>

#include <ossia/detail/algorithms.hpp>
#include <ossia/detail/math.hpp>

#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm/copy.hpp>

#include <QAction>
#include <QApplication>
#include <QInputDialog>
#include <QMenu>


namespace Acousmoscribe
{
Presenter::Presenter(
    const Acousmoscribe::Model& layer, View* view,
    const Process::Context& ctx, QObject* parent)
    : Process::LayerPresenter{layer, view, ctx, parent}
    , m_model{layer}
    , m_view{view}
    , m_moveDispatcher{ctx.commandStack}
    , m_zr{1.}
{
  putToFront();

  auto& model = layer;

  con(model, &Model::melodicKeysNeedUpdate, this, [&] {
    updateMelodicKey(*m_melodicKeyView);
  });

  con(model, &Model::spectralKeyNeedUpdate, this, [&] {
    updateSpectralKey(*m_spectralKeyView);
  });

  con(model, &Model::signsNeedUpdate, this, [&] {
    for (auto sign : m_signs)
      updateSign(*sign);
  });

  /*con(model, &Model::signsChanged, this, [&] {
    for (auto sign : m_signs)
    {
      delete sign;
    }

    m_signs.clear();

    for (auto& sign : model.signs)
    {
      on_signAdded(sign);
    }
  });*/

  model.melodicKeys.added.connect<&Presenter::on_melodicKeyAdded>(this);
  model.spectralKey.added.connect<&Presenter::on_spectralKeyAdded>(this);

  model.signs.added.connect<&Presenter::on_signAdded>(this);
  model.signs.removing.connect<&Presenter::on_signRemoving>(this);


  // Default MelodicKey
  MelodicKeyData mkData = {mid, weak};
  CommandDispatcher<>{context().context.commandStack}.submit(
        new AddMelodicKey{model, mkData});

  // Default SpectralKey
  SpectralKeyData skData;
  skData.setNature(tonic);
  skData.setNature2(null);
  CommandDispatcher<>{context().context.commandStack}.submit(
        new AddSpectralKey{model, skData});

  connect(m_view, &View::doubleClicked, this, [&](QPointF pos) {
    CommandDispatcher<>{context().context.commandStack}.submit(
        new AddSign{model, m_view->signAtPos(pos)});
  });

  connect(m_view, &View::deleteRequested, this, [&] {
    CommandDispatcher<>{context().context.commandStack}.submit(
        new RemoveSigns{this->model(), selectedSigns()});
  });

  connect(m_view, &View::pressed, this, [&]() {
    m_context.context.focusDispatcher.focus(this);
    for (SignView* n : m_signs)
      n->setSelected(false);
  });

  //connect(m_view, &View::dropReceived, this, &Presenter::on_drop);

  /*connect(m_view, &View::deleteRequested, this, [&] {
    CommandDispatcher<>{context().context.commandStack}.submit(
        new RemoveSigns{this->model(), selectedSigns()});
  });*/

  connect(m_view, &View::askContextMenu, this, &Presenter::contextMenuRequested);


  for (auto& sign : model.signs)
  {
    on_signAdded(sign);
  }
#if __has_include(<valgrind/callgrind.h>)
  // CALLGRIND_START_INSTRUMENTATION;
#endif
} 

Presenter::~Presenter()
{
#if __has_include(<valgrind/callgrind.h>)
  // CALLGRIND_STOP_INSTRUMENTATION;
#endif
}


void Presenter::setWidth(qreal val, qreal defaultWidth)
{
  m_view->setWidth(val);
  m_view->setDefaultWidth(defaultWidth);
}

void Presenter::setHeight(qreal val)
{
  m_view->setHeight(val);
  updateMelodicKey(*m_melodicKeyView);
  updateSpectralKey(*m_spectralKeyView);
  for (auto sign : m_signs)
    updateSign(*sign);
}

void Presenter::putToFront()
{
  m_view->setEnabled(true);
}

void Presenter::putBehind()
{
  m_view->setEnabled(false);
}

void Presenter::on_zoomRatioChanged(ZoomRatio zr)
{
  m_zr = zr;
  m_view->setDefaultWidth(model().duration().toPixels(m_zr));
  updateMelodicKey(*m_melodicKeyView);
  updateSpectralKey(*m_spectralKeyView);
  for (auto sign : m_signs)
    updateSign(*sign);
}

void Presenter::parentGeometryChanged()
{
}

const Acousmoscribe::Model& Presenter::model() const noexcept
{
  return static_cast<const Acousmoscribe::Model&>(m_process);
}

void Presenter::updateMelodicKey(MelodicKeyView& v)
{
  const auto keyRect = v.computeRect();
  const auto newPos = keyRect.topLeft();
  if (newPos != v.pos())
  {
    v.setPos(newPos);
  }

  v.setWidth(keyRect.width());
  v.setHeight(keyRect.height());
}

void Presenter::updateSpectralKey(SpectralKeyView& s)
{
  const auto keyRect = s.computeRect();
  const auto newPos = keyRect.topLeft();
  if (newPos != s.pos())
  {
    s.setPos(newPos);
  }

  s.setWidth(keyRect.width());
  s.setHeight(keyRect.height());
}

void Presenter::updateSign(SignView& v)
{
  //std::cout << "entré dans update sign\n";

  const auto signRect = v.computeRect();
  const auto newPos = signRect.topLeft();
  if (newPos != v.pos())
  {
    v.setPos(newPos);
  }

  v.setWidth(signRect.width());
  v.setHeight(signRect.height());
}


// Melodic Key Changed

void Presenter::on_melodicKeyPitchChanged(const MelodicKey& mKey, Pitch pitch){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeMelodicKeyPitch{model(), mKey.id(), pitch}); 
}

void Presenter::on_melodicKeyRangeChanged(const MelodicKey& mKey, Range range){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeMelodicKeyRange{model(), mKey.id(), range}); 
}


// Spectral Key Changed

void Presenter::on_spectralKeyNatureChanged(const SpectralKey& sKey, Nature nature){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeSpectralKeyNature{model(), sKey.id(), nature}); 
}

void Presenter::on_spectralKeyNature2Changed(const SpectralKey& sKey, Nature nature){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeSpectralKeyNature2{model(), sKey.id(), nature}); 
}

void Presenter::on_spectralKeyIsRichChanged(const SpectralKey& sKey, bool isRich){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeSpectralKeyIsRich{model(), sKey.id(), isRich}); 
}

void Presenter::on_spectralKeyIsRich2Changed(const SpectralKey& sKey, bool isRich){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeSpectralKeyIsRich2{model(), sKey.id(), isRich}); 
}

void Presenter::on_spectralKeyIsHybridChanged(const SpectralKey& sKey, bool isHybrid){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeSpectralKeyIsHybrid{model(), sKey.id(), isHybrid}); 
}

void Presenter::on_spectralKeyIsHybrid2Changed(const SpectralKey& sKey, bool isHybrid){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeSpectralKeyIsHybrid2{model(), sKey.id(), isHybrid}); 
}
void Presenter::on_spectralKeyIsWarpedChanged(const SpectralKey& sKey, bool warped){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeSpectralKeyWarped{model(), sKey.id(), warped}); 
}

void Presenter::on_spectralKeyIsWarped2Changed(const SpectralKey& sKey, bool warped){
  CommandDispatcher<>{context().context.commandStack}.submit(new ChangeSpectralKeyWarped2{model(), sKey.id(), warped}); 
}


// ===================================================== SIGN ===================================================== 

void Presenter::on_signMoved(SignView& v)
{
  if(!m_origMoveStart)
  {
    m_origMoveStart = v.sign.start();
  }

  auto newPos = v.pos();
  auto rect = m_view->boundingRect();
  auto height = rect.height();

  auto signs = selectedSigns();
  auto it = ossia::find(signs, v.sign.id());
  if (it == signs.end())
  {
    signs = {v.sign.id()};
  }

  m_moveDispatcher.submit(
      model(),
      signs,
      newPos.x() / m_view->defaultWidth() - *m_origMoveStart);
}

void Presenter::on_signMoveFinished(SignView& v)
{
  on_signMoved(v);
  m_moveDispatcher.commit();

  m_origMoveStart = std::nullopt;
}

void Presenter::on_signScaled(const Sign& sign, double newScale)
{
  auto signs = selectedSigns();
  auto it = ossia::find(signs, sign.id());
  if (it == signs.end())
  {
    signs = {sign.id()};
  }

  auto dt = newScale - sign.duration();
  CommandDispatcher<>{context().context.commandStack}.submit(new ScaleSigns{model(), signs, dt}); 
}


// --------------------------------------------- Sign/Dynamic Profile ---------------------------------------------      



void Presenter::on_signVolumeStartChanged(const Sign& sign, float newVolStart)
{
  if(sign.dynamicProfile().volumeStart != newVolStart)
  {
    auto newDP = sign.dynamicProfile() ;
    newDP.volumeStart = newVolStart ;

    CommandDispatcher<>{context().context.commandStack}.submit(new ChangeDynamicProfile{model(), sign.id(), newDP}); 
  }
};

void Presenter::on_signVolumeEndChanged(const Sign& sign, float newVolEnd)
{
  if(sign.dynamicProfile().volumeEnd != newVolEnd)
  {
    auto newDP = sign.dynamicProfile() ;
    newDP.volumeEnd = newVolEnd ;

    CommandDispatcher<>{context().context.commandStack}.submit(new ChangeDynamicProfile{model(), sign.id(), newDP}); 
  }
};

/*void on_signVolumeChanged(const Sign&, double newVol)
{
  if(sign.dynamicProfile().volume != newVol)
  {
    auto newDP = sign.dynamicProfile() ;
    newDP.volume = newVol ;

    m_changeDynamicProfile.submit(model(), sign.id(), newDP);
  }
};*/

// --------------------------------------------- Sign/Melodic Profile ---------------------------------------------      

void Presenter::on_signMelodicProfilePitchChanged(const Sign& sign, Pitch newPitch){
  if(sign.melodicProfile().pitch() != newPitch)
  {
    auto newMP = sign.melodicProfile() ;
    newMP.setPitch(newPitch)  ;

    //CommandDispatcher<>{context().context.commandStack}.submit(new ChangeMelodicProfile{model(), sign.id(), newMP}); 
  }
}

void Presenter::on_signMelodicProfilePitchEndChanged(const Sign& sign, Pitch newPitchEnd){
  if(sign.melodicProfile().pitchEnd() != newPitchEnd)
  {
    auto newMP = sign.melodicProfile() ;
    newMP.setPitchEnd(newPitchEnd)  ;

    //CommandDispatcher<>{context().context.commandStack}.submit(new ChangeMelodicProfile{model(), sign.id(), newMP}); 
  }
}

void Presenter::on_signMelodicProfileVariationChanged(const Sign& sign, Variation newVar){
  if(sign.melodicProfile().variation() != newVar)
  {
    auto newMP = sign.melodicProfile() ;
    newMP.setVariation(newVar) ;

    //CommandDispatcher<>{context().context.commandStack}.submit(new ChangeMelodicProfile{model(), sign.id(), newMP}); 
  }
}

// --------------------------------------------- Sign/Rhythmic Profile ---------------------------------------------      

void Presenter::on_signRhythmicProfileSpeedChanged(const Sign& sign, Speed newSpeed)
{
  if(sign.rhythmicProfile().speed() != newSpeed)
  {
    auto newRP = sign.rhythmicProfile() ;
    newRP.setSpeed(newSpeed)  ;

    //CommandDispatcher<>{context().context.commandStack}.submit(new ChangeRhythmicProfile{model(), sign.id(), newRP}); 
  }
}

void Presenter::on_signRhythmicProfileAccelerationChanged(const Sign& sign, Acceleration newAcc)
{
  if(sign.rhythmicProfile().acceleration() != newAcc)
  {
    auto newRP = sign.rhythmicProfile() ;
    newRP.setAcceleration(newAcc)  ;

    //CommandDispatcher<>{context().context.commandStack}.submit(new ChangeRhythmicProfile{model(), sign.id(), newRP}); 
  }
}

void Presenter::on_signRhythmicProfileIsRandomChanged(const Sign& sign, bool newIsRandom)
{
  if(sign.rhythmicProfile().isRandom() != newIsRandom)
  {
    auto newRP = sign.rhythmicProfile() ;
    newRP.setIsRandom(newIsRandom)  ;

    //CommandDispatcher<>{context().context.commandStack}.submit(new ChangeRhythmicProfile{model(), sign.id(), newRP}); 
  }
}

// -------------------------------------------------- Sign/Grain  --------------------------------------------------      

void Presenter::on_signGrainChanged(const Sign& sign, Grain g)
{
  if(sign.grain() != g)
  {
    CommandDispatcher<>{context().context.commandStack}.submit(new ChangeGrain{model(), sign.id(), g}); 
  }
}

// =================================================================================================================

void Presenter::on_melodicKeyAdded(const MelodicKey& mKey)
{
  auto v = new MelodicKeyView{mKey, *this, m_view};
  updateMelodicKey(*v);
  m_melodicKeyView = v;
}

void Presenter::on_spectralKeyAdded(const SpectralKey& mKey)
{
  auto v = new SpectralKeyView{mKey, *this, m_view};
  updateSpectralKey(*v);
  m_spectralKeyView = v;
}


void Presenter::on_signAdded(const Sign& s)
{
  auto v = new SignView{s, *this, m_view};
  updateSign(*v);
  m_signs.push_back(v);
}

void Presenter::on_signRemoving(const Sign& s)
{
  /*auto it = ossia::find_if(m_signs, [&](const auto& other) { return &other->sign == &s; });
  if (it != m_signs.end())
  {
    delete *it;
    m_signs.erase(it);
  }*/
}

void Presenter::on_signDuplicate()
{

}

void Presenter::on_deselectOtherSigns()
{
  for (SignView* s : m_signs)
    s->setSelected(false);
}


std::vector<Id<Sign>> Presenter::selectedSigns() const
{
  using namespace boost::adaptors;

  std::vector<Id<Sign>> res;
  boost::copy(
      m_signs | boost::adaptors::filtered([](SignView* v) { return v->isSelected(); })
          | transformed([](SignView* v) { return v->sign.id(); }),
      std::back_inserter(res));
  return res;
  
}

}
