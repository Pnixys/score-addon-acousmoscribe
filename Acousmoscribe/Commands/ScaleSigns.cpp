#include "ScaleSigns.hpp"

#include <Acousmoscribe/Model/Process.hpp>
#include <Process/TimeValueSerialization.hpp>

#include <score/model/path/PathSerialization.hpp>
#include <score/tools/IdentifierGeneration.hpp>

namespace Acousmoscribe
{
ScaleSigns::ScaleSigns(
    const Model& model,
    const std::vector<Id<Sign>>& to_scale,
    double delta)
    : m_model{model}, m_toScale{to_scale}, m_delta{delta}
{
}

void ScaleSigns::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  for (auto& sign : m_toScale)
  {
    auto& s = model.signs.at(sign);
    s.setDuration(s.duration() - m_delta);
  }
}

void ScaleSigns::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  for (auto& sign : m_toScale)
  {
    auto& s = model.signs.at(sign);
    s.setDuration(std::max(s.duration() + m_delta, 0.001));
  }
}

void ScaleSigns::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_toScale << m_delta;
}

void ScaleSigns::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_toScale >> m_delta;
}
}