#include <score/command/Dispatchers/CommandDispatcher.hpp>

#include <Acousmoscribe/Presenter.hpp>
#include <Acousmoscribe/Process.hpp>
#include <Acousmoscribe/View.hpp>

#include <Acousmoscribe/SpectralKeyView.hpp>
#include <ossia/detail/algorithms.hpp>
#include <ossia/detail/math.hpp>



namespace Acousmoscribe
{
Presenter::Presenter(
    const Acousmoscribe::Model& layer, View* view,
    const Process::Context& ctx, QObject* parent)
    : Process::LayerPresenter{layer, view, ctx, parent}
    , m_model{layer}
    , m_view{view}
{
}

void Presenter::setWidth(qreal val, qreal defaultWidth)
{
  m_view->setWidth(val);
}

void Presenter::setHeight(qreal val)
{
  m_view->setHeight(val);
}

void Presenter::putToFront()
{
  m_view->setOpacity(1);
}

void Presenter::putBehind()
{
  m_view->setOpacity(0.2);
}

void Presenter::on_zoomRatioChanged(ZoomRatio)
{
}

void Presenter::parentGeometryChanged()
{
}

void Presenter::updateMelodicKey(MelodicKeyView& v)
{
  const auto keyRect = v.computeRect();
  v.setWidth(keyRect.width());
  v.setHeight(keyRect.height());
}

void Presenter::on_melodicKeyChanged(MelodicKeyView& mKey)
{
  mKey.melodicKey.setPitch(mid_high);
  mKey.melodicKey.setRange(weak);
}

void Presenter::on_melodicKeyAdded(MelodicKey& mKey)
{
  auto v = new MelodicKeyView{mKey, *this, m_view};
  //updateNote(*v);
  m_melodicKeyView = v;
}

}
