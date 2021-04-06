#include <score/command/Dispatchers/CommandDispatcher.hpp>

/* View */
#include <Acousmoscribe/View.hpp>
#include <Acousmoscribe/SignView.hpp>
#include <Acousmoscribe/MelodicKeyView.hpp>
#include <Acousmoscribe/SpectralKeyView.hpp>

/* Presenter */
#include <Acousmoscribe/Presenter.hpp>

/* Commands */
#include <Acousmoscribe/Commands/AddKey.hpp>

/* Model */
#include <Acousmoscribe/Process.hpp>
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
    , m_changeMelodicKeyPitch{ctx.commandStack}
    , m_changeMelodicKeyRange{ctx.commandStack}
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

  model.melodicKeys.added.connect<&Presenter::on_melodicKeyAdded>(this);
  model.spectralKey.added.connect<&Presenter::on_spectralKeyAdded>(this);

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
} 

void Presenter::setWidth(qreal val, qreal defaultWidth)
{
  m_view->setWidth(val);
  updateMelodicKey(*m_melodicKeyView);
  updateSpectralKey(*m_spectralKeyView);
}

void Presenter::setHeight(qreal val)
{
  m_view->setHeight(val);
  updateMelodicKey(*m_melodicKeyView);
  updateSpectralKey(*m_spectralKeyView);
}

void Presenter::putToFront()
{
  m_view->setOpacity(1);
}

void Presenter::putBehind()
{
  m_view->setOpacity(0.2);
}

void Presenter::on_zoomRatioChanged(ZoomRatio zr)
{
  m_zr = zr;
  m_view->setDefaultWidth(model().duration().toPixels(m_zr));
  updateMelodicKey(*m_melodicKeyView);
  updateSpectralKey(*m_spectralKeyView);
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

void Presenter::on_melodicKeyPitchChanged(const MelodicKey& mKey, Pitch& pitch){
  m_changeMelodicKeyPitch.submit(model(), mKey.id(), pitch);
}

void Presenter::on_melodicKeyRangeChanged(const MelodicKey& mKey, Range& range){
  m_changeMelodicKeyRange.submit(model(), mKey.id(), range);
}

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
}
