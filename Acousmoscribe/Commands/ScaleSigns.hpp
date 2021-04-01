#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/Sign.hpp>
#include <Process/TimeValue.hpp>
#include <QVector>

#include <score/model/path/Path.hpp>

namespace Acousmoscribe
{
class Model;

class ScaleSigns final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), ScaleSigns, "Scale signs")
public:
  ScaleSigns(const Model& model, const std::vector<Id<Sign>>& to_scale, double delta);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  std::vector<Id<Sign>> m_toScale;
  double m_delta{};
};
}