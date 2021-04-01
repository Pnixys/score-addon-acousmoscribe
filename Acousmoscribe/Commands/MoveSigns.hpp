#pragma once
#include "CommandFactory.hpp"
#include <Acousmoscribe/Model/Sign.hpp>

#include <score/model/path/Path.hpp>
#include <score/tools/Unused.hpp>

#include <QVector>

namespace Acousmoscribe
{
class Model;

class MoveSigns final : public score::Command
{
  SCORE_COMMAND_DECL(Acousmoscribe::CommandFactoryName(), MoveSigns, "Move Signs")
public:
  MoveSigns(
      const Model& model,
      const std::vector<Id<Sign>>& to_move,
      double t_delta);

  void undo(const score::DocumentContext& ctx) const override;
  void redo(const score::DocumentContext& ctx) const override;

  void update(unused_t, unused_t, double t_delta);

protected:
  void serializeImpl(DataStreamInput& s) const override;
  void deserializeImpl(DataStreamOutput& s) override;

private:
  Path<Model> m_model;
  QVector<QPair<Id<Sign>, SignData>> m_before, m_after;
};
}
