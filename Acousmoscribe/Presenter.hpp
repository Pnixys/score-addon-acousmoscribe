#pragma once

#include <Acousmoscribe/Process.hpp>
#include <Process/Focus/FocusDispatcher.hpp>
#include <Process/LayerPresenter.hpp>

/* Commands */
#include <Acousmoscribe/Commands/ChangeMelodicKey.hpp>

#include <score/command/Dispatchers/SingleOngoingCommandDispatcher.hpp>

#include <nano_observer.hpp>

namespace Acousmoscribe
{
class Model;
class View;
class Sign;
class SignView;
class MelodicKey;
class MelodicKeyView;
class SpectralKey;
class SpectralKeyView;

class Presenter final : public Process::LayerPresenter
{
public:
  explicit Presenter(
      const Model& model, 
      View* view,
      const Process::Context& ctx, 
      QObject* parent);

  void setWidth(qreal width, qreal defaultWidth) override;
  void setHeight(qreal height) override;

  void putToFront() override;
  void putBehind() override;

  void on_zoomRatioChanged(ZoomRatio) override;

  void parentGeometryChanged() override;

  const Acousmoscribe::Model& model() const noexcept;

/*
  void on_spectralKeyChanged(SpectralKeyView& sKey);
/*  
  void on_spectralKeyNature1Changed(Nature& nature1);
  void on_spectralKeyNature2Changed(Nature& nature2);
  void on_spectralKeyIsRichChanged(bool& isRich);
  void on_spectralKeyIsRich2Changed(bool& isRich2);
  void on_spectralKeyIsHybridChanged(bool& isHybrid);
  void on_spectralKeyIsHybrid2Changed(bool& isHybrid2);
  void on_spectralKeyIsWarpedChanged(bool& isWarped);
  void on_spectralKeyIsWarped2Changed(bool& isWarped2);
  */

  //void on_melodicKeyChanged(MelodicKeyView& mKey);
  
  void on_melodicKeyPitchChanged(const MelodicKey&, Pitch& pitch);
  void on_melodicKeyRangeChanged(const MelodicKey&, Range& range);
  

  /*
  void on_deselectOtherSigns();
  void on_signDuplicate();
  void on_signScaled(const Sign&, double newScale);
  void on_signMoved(SignView& s); 
  void on_signMoveFinished(SignView& s); 

  // Dynamic Profile :
  void on_signAttackChanged(const Sign&, double newAttack);
  void on_signReleaseChanged(const Sign&, double newRelease);
  void on_signVolumeInChanged(const Sign&, double newVolIn);
  void on_signVolumeOutChanged(const Sign&, double newVolOut);
  void on_signVolumeChanged(const Sign&, double newVol);

  // Other profiles
  void on_signMelodicProfileChanged(SignView& s);
  void on_signRhythmicProfileChanged(SignView& s);
  void on_signGrainChanged(SignView& s);
*/

private:  

  void updateSpectralKey(SpectralKeyView&);
  void on_spectralKeyAdded(const SpectralKey&);
//  void on_spectralKeyRemoving(const SpectralKey&);

  void updateMelodicKey(MelodicKeyView&);
  void on_melodicKeyAdded(const MelodicKey&);
  void on_melodicKeyRemoving(MelodicKey&);
/*
  void updateSign(SignView&);
  void on_signAdded(const Sign&);
  void on_signRemoving(const Sign&);
  */

  const Model& m_model;
  View* m_view{};
  MelodicKeyView* m_melodicKeyView;
  SpectralKeyView* m_spectralKeyView;
  std::vector<SignView*> m_signs;

  /* COMMAND DISPATCHERS */
  SingleOngoingCommandDispatcher<ChangeMelodicKeyPitch> m_changeMelodicKeyPitch;
  SingleOngoingCommandDispatcher<ChangeMelodicKeyRange> m_changeMelodicKeyRange;

  ZoomRatio m_zr{};
};
}
