#pragma once
#include <Process/GenericProcessFactory.hpp>
#include <Process/Process.hpp>

#include <Acousmoscribe/Model/Sign.hpp>
#include <Acousmoscribe/Model/SpectralKey.hpp>
#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Acousmoscribe/Metadata.hpp>
#include <score/tools/Clamp.hpp>

namespace Acousmoscribe
{
class Model final : public Process::ProcessModel
{
  SCORE_SERIALIZE_FRIENDS
  PROCESS_METADATA_IMPL(Acousmoscribe::Model)
  W_OBJECT(Model)

public:
  Model(
      const TimeVal& duration, const Id<Process::ProcessModel>& id,
      QObject* parent);

  template <typename Impl>
  Model(Impl& vis, QObject* parent) : Process::ProcessModel{vis, parent}
  {
    vis.writeTo(*this);
  }

  ~Model() override;

  std::pair<int, int> range() const { return m_range; }


  score::EntityMap<Sign> signs;
  score::EntityMap<SpectralKey> spectralKey;
  score::EntityMap<MelodicKey> melodicKeys;

public:
  void signsNeedUpdate() W_SIGNAL(signsNeedUpdate);
  void signsChanged() W_SIGNAL(signsChanged);

  void spectralKeyNeedUpdate() W_SIGNAL(spectralKeyNeedUpdate);
  void spectralKeyChanged() W_SIGNAL(spectralKeyChanged);

  void melodicKeysNeedUpdate() W_SIGNAL(melodicKeysNeedUpdate);
  void melodicKeysChanged() W_SIGNAL(melodicKeysChanged);

private:
  QString prettyName() const noexcept override;

  void setDurationAndScale(const TimeVal& newDuration) noexcept override;
  void setDurationAndGrow(const TimeVal& newDuration) noexcept override;
  void setDurationAndShrink(const TimeVal& newDuration) noexcept override;

  std::pair<int, int> m_range{0, 127};

};

using ProcessFactory = Process::ProcessFactory_T<Acousmoscribe::Model>;
}

