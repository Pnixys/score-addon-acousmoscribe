#pragma once
#include <Process/Focus/FocusDispatcher.hpp>
#include <Process/LayerPresenter.hpp>
#include <Process/ZoomHelper.hpp>

#include <score/model/Identifier.hpp>
#include <Acousmoscribe/MelodicKeyView.hpp>

#include <Acousmoscribe/Model/Sign.hpp>
#include <Acousmoscribe/Model/Grain.hpp>
#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Acousmoscribe/Model/SpectralKey.hpp>
#include <Acousmoscribe/Model/RhythmicProfile.hpp>
#include <Acousmoscribe/Model/MelodicProfile.hpp>
//#include <Acousmoscribe/Model/DynamicProfileNotuse.hpp>


#include "SignView.hpp"
#include "SpectralKeyView.hpp"
#include "MelodicKeyView.hpp"

#include <Acousmoscribe/Process.hpp>


namespace Acousmoscribe
{
class Model;
class View;
class MelodicKeyView;
class MelodicKey;
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

/*
  void on_spectralKeyChanged(SpectralKeyView& sKey);
  
  void on_spectralKeyNature1Changed(Nature& nature1);
  void on_spectralKeyNature2Changed(Nature& nature2);
  void on_spectralKeyIsRichChanged(bool& isRich);
  void on_spectralKeyIsHybridChanged(bool& isHybrid);
  */

  void on_melodicKeyChanged(MelodicKeyView& mKey);

  /*
  void on_melodicKeyPitchChanged(Pitch& pitch);
  void on_melodicKeyRangeChanged(Range& range);
  */

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
/*
  void updateSpectralKey(SpectralKeyView&);
  void on_spectralKeyAdded(const SpectralKey&);
  void on_spectralKeyRemoving(const SpectralKey&);
*/
  void updateMelodicKey(MelodicKeyView&);
  void on_melodicKeyAdded(MelodicKey&);
  void on_melodicKeyRemoving(MelodicKey&);
/*
  void updateSign(SignView&);
  void on_signAdded(const Sign&);
  void on_signRemoving(const Sign&);
  */

  const Model& m_model;
  View* m_view{};
  MelodicKeyView* m_melodicKeyView;
  std::vector<SignView*> m_signs;

  ZoomRatio m_zr{};
};
}
