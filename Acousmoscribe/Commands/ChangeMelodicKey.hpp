#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Process/TimeValue.hpp>
#include <QVector>

#include <score/model/path/Path.hpp>

namespace Acousmoscribe
{
class Model;

class ChangeMelodicKeyPitch final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeMelodicKeyPitch, "Change a Melodic Key")
public:
  ChangeMelodicKeyPitch(const Model& model, const Id<MelodicKey>& to_change, Pitch pitch);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  Id<MelodicKey> m_toChange;
  Pitch m_pitchBefore, m_pitchAfter;
};


class ChangeMelodicKeyRange final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeMelodicKeyRange, "Change a Melodic Key")
public:
  ChangeMelodicKeyRange(const Model& model, const Id<MelodicKey>& to_change, Range range);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  Id<MelodicKey> m_toChange;
  Range m_rangeBefore, m_rangeAfter;
};
}