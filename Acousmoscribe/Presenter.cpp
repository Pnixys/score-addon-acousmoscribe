#include <score/command/Dispatchers/CommandDispatcher.hpp>

/* View */
#include <Acousmoscribe/View.hpp>
#include <Acousmoscribe/SignView.hpp>
#include <Acousmoscribe/MelodicKeyView.hpp>
#include <Acousmoscribe/SpectralKeyView.hpp>



/* Presenter */
#include <Acousmoscribe/Presenter.hpp>

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

const Acousmoscribe::Model& Presenter::model() const noexcept
{
  return static_cast<const Acousmoscribe::Model&>(m_process);
}

void Presenter::updateMelodicKey(MelodicKeyView& v)
{
  const auto keyRect = v.computeRect();
  v.setWidth(keyRect.width());
  v.setHeight(keyRect.height());
}

void Presenter::on_melodicKeyPitchChanged(MelodicKey& mKey, Pitch& pitch){
  m_changeMelodicKeyPitch.submit(model(), mKey.id(), pitch);
}

void Presenter::on_melodicKeyRangeChanged(MelodicKey& mKey, Range& range){
  m_changeMelodicKeyRange.submit(model(), mKey.id(), range);
}

void Presenter::on_melodicKeyAdded(MelodicKey& mKey)
{
  auto v = new MelodicKeyView{mKey, *this, m_view};
  //updateNote(*v);
  m_melodicKeyView = v;
}

}
