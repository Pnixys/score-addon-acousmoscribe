#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Acousmoscribe/Model/SpectralKey.hpp>

#include <Process/TimeValue.hpp>

#include <score/model/path/Path.hpp>

namespace Acousmoscribe
{
class Model;

class AddMelodicKey final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), AddMelodicKey, "Add a melodic key")

public:
  AddMelodicKey(const Model& model, const MelodicKeyData& data);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;


protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  Id<MelodicKey> m_id;
  MelodicKeyData m_data;
};


class AddSpectralKey final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), AddSpectralKey, "Add a spectral key")

public:
  AddSpectralKey(const Model& model, const SpectralKeyData& data);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;


protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  Id<SpectralKey> m_id;
  SpectralKeyData m_data;
};
}
