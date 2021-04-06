#include <score/command/Dispatchers/CommandDispatcher.hpp>

#include <Acousmoscribe/Presenter.hpp>
#include <Acousmoscribe/Process.hpp>
#include <Acousmoscribe/View.hpp>

#include <Acousmoscribe/SpectralKeyView.hpp>
#include <ossia/detail/algorithms.hpp>
#include <ossia/detail/math.hpp>
#include <score/tools/IdentifierGeneration.hpp>


namespace Acousmoscribe
{
Presenter::Presenter(
    const Acousmoscribe::Model& layer, View* view,
    const Process::Context& ctx, QObject* parent)
    : Process::LayerPresenter{layer, view, ctx, parent}
    , m_model{layer}
    , m_view{view}
{
  MelodicKeyData mkData;
  mkData.setPitch(high);
  mkData.setRange(weak);
  auto id = getStrongId(layer.melodicKeys);
  auto mk = new MelodicKey(id, mkData, parent);
  m_melodicKeyView = new MelodicKeyView(*mk, *this, m_view);
  updateMelodicKey(*m_melodicKeyView);

  SpectralKeyData skData;
  skData.setNature(noise);
  skData.setNature2(noisy_tonic);
  skData.setHybrid2(true);
  auto id2 = getStrongId(layer.spectralKey);
  auto sk = new SpectralKey(id2, skData, parent);
  m_spectralKeyView = new SpectralKeyView(*sk, *this, m_view);
  updateSpectralKey(*m_spectralKeyView);
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


void Presenter::on_melodicKeyChanged(MelodicKeyView& mKey)
{
  mKey.melodicKey.setPitch(low);
  mKey.melodicKey.setRange(weak);
}

void Presenter::on_melodicKeyAdded(MelodicKey& mKey)
{
  auto v = new MelodicKeyView{mKey, *this, m_view};
  //updateNote(*v);
  m_melodicKeyView = v;
}

void Presenter::on_spectralKeyChanged(SpectralKeyView& mKey)
{
  mKey.spectralKey.setNature(inharmonic);
  mKey.spectralKey.setNature2(noisy_inharmonic);
  mKey.spectralKey.setIsRich(true);
}

void Presenter::on_spectralKeyAdded(SpectralKey& mKey)
{
  auto v = new SpectralKeyView{mKey, *this, m_view};
  //updateNote(*v);
  m_spectralKeyView = v;
}

}
