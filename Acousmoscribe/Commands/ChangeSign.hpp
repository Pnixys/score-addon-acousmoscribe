#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/Sign.hpp>
#include <Process/TimeValue.hpp>
#include <score/tools/Unused.hpp>
#include <QVector>

#include <score/model/path/Path.hpp>

namespace Acousmoscribe
{
class Model;

class ChangeDynamicProfile final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeDynamicProfile, "Change the dynamic profile of a sign")
public:
  ChangeDynamicProfile(const Model& model, const Id<Sign>& to_change, DynamicProfile dyn);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, DynamicProfile dyn);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<Sign>, SignData> m_before, m_after;
};

class ChangeMelodicProfile final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeMelodicProfile, "Change the melodic profile of a sign")
public:
  ChangeMelodicProfile(const Model& model, const Id<Sign>& to_change, MelodicProfile melo);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, MelodicProfile melo);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<Sign>, SignData> m_before, m_after;
};



class ChangeRhythmicProfile final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeRhythmicProfile, "Change the rhythmic profile of a sign")
public:
  ChangeRhythmicProfile(const Model& model, const Id<Sign>& to_change, RhythmicProfile rhythm);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, RhythmicProfile rhythm);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<Sign>, SignData> m_before, m_after;
};



class ChangeGrain final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeGrain, "Change the grain of a sign")
public:
  ChangeGrain(const Model& model, const Id<Sign>& to_change, Grain grain);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, Grain grain);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QPair<Id<Sign>, SignData> m_before, m_after;
};

}