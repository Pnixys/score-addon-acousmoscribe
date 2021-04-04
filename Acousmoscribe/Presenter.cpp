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
}

void Presenter::setWidth(qreal val, qreal defaultWidth)
{
  m_view->setWidth(val);
  updateMelodicKey(*m_melodicKeyView);
}

void Presenter::setHeight(qreal val)
{
  m_view->setHeight(val);
  updateMelodicKey(*m_melodicKeyView);
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

}
