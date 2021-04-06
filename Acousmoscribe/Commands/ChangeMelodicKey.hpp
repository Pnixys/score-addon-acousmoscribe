#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Process/TimeValue.hpp>
#include <score/tools/Unused.hpp>
#include <QVector>

#include <score/model/path/Path.hpp>

namespace Acousmoscribe
{
class Model;

class ChangeMelodicKeyPitch final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeMelodicKeyPitch, "Change a Melodic Key")
public:
  ChangeMelodicKeyPitch(const Model& model, const Id<MelodicKey>& to_update, Pitch pitch);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, Pitch pitch);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<MelodicKey>, MelodicKeyData> m_before, m_after;
};


class ChangeMelodicKeyRange final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeMelodicKeyRange, "Change a Melodic Key")
public:
  ChangeMelodicKeyRange(const Model& model, const Id<MelodicKey>& to_change, Range range);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, Range range);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<MelodicKey>, MelodicKeyData> m_before, m_after;
};
}