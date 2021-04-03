#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/Sign.hpp>
#include <Process/TimeValue.hpp>

#include <score/model/path/Path.hpp>

namespace Acousmoscribe
{
class Model;

class AddSign final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), AddSign, "Add a sign")

public:
  AddSign(const Model& model, const SignData& sign);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;


protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  Id<Sign> m_id;
  SignData m_sign;
};
}
