#pragma once
#include <Process/Focus/FocusDispatcher.hpp>
#include <Process/LayerPresenter.hpp>
#include <Process/ZoomHelper.hpp>

#include <score/model/Identifier.hpp>

namespace Acousmoscribe
{
class Model;
class View;
class Presenter final : public Process::LayerPresenter
{
public:
  explicit Presenter(
      const Model& model, View* view,
      const Process::Context& ctx, QObject* parent);

  void setWidth(qreal width, qreal defaultWidth) override;
  void setHeight(qreal height) override;

  void putToFront() override;
  void putBehind() override;

  void on_zoomRatioChanged(ZoomRatio) override;

  void parentGeometryChanged() override;

  //void on_spectralKeyChanged(SpectralKeyView& sKey);
  void on_spectralKeyNature1Changed(Nature& nature1);
  void on_spectralKeyNature2Changed(Nature& nature2);
  void on_spectralKeyIsRichChanged(bool& isRich);
  void on_spectralKeyIsHybridChanged(bool& isHybrid);

  //void on_melodicKeyChanged(MelodicKeyView& mKey);
  void on_melodicKeyPitchChanged(Pitch& pitch);
  void on_melodicKeyRangeChanged(Range& range);

  void on_deselectOtherSigns();
  void on_signDuplicate();
  void on_signScaled(const Sign&, double newScale);
  //void on_signChanged(SignView& sign);
  void on_signAttackChanged(Dyn& attack);
  void on_signAttackChangeFinished(Dyn& attack);
  void on_signReleaseChanged(Dyn& release);
  void on_signReleaseChangeFinished(Dyn& release);
  //void on_signDynamicProfileChanged(DynamicProfile& dynP);
  void on_signMelodicProfileChanged(MelodicProfile& melP);
  void on_signRhythmicProfileChanged(RhythmicProfile& rhyP);
  void on_signGrainChanged(Grain& grain);

  /*void on_signvolumeStartChanged(volume ?);
  void on_signvolumeStartChangeFinished(volume ?);
  void on_signvolumeEndChanged(volume ?);
  void on_signvolumeEndChangeFinished(volume ?);*/

private:
  void on_spectralKeyAdded(const SpectralKey&);
  void on_spectralKeyRemoving(const SpectralKey&);

  void on_melodicKeyAdded(const MelodicKey&);
  void on_melodicKeyRemoving(const MelodicKey&);

  void on_SignAdded(const Sign&);
  void on_SignRemoving(const Sign&);

  const Model& m_model;
  View* m_view{};
};
}
