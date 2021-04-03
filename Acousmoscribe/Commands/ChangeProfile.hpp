#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/Sign.hpp>
#include <Process/TimeValue.hpp>
#include <QVector>

#include <score/model/path/Path.hpp>

namespace Acousmoscribe
{
class Model;

class ChangeDynamicProfile final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ChangeDynamicProfile, "Change a Sign's Dynamic Profile")
public:
  ChangeDynamicProfile(const Model& model, const Id<Sign>& to_change, DynamicProfile dyn);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  Id<Sign> m_toChange;
  DynamicProfile m_dynBefore, m_dynAfter;
};
}