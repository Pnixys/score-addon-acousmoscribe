#include "RemoveSigns.hpp"

#include <Acousmoscribe/Model/Process.hpp>
#include <Process/TimeValueSerialization.hpp>

#include <score/model/path/PathSerialization.hpp>
#include <score/tools/IdentifierGeneration.hpp>

namespace Acousmoscribe{


RemoveSigns::RemoveSigns(const Model& model, const std::vector<Id<Sign>>& signs)
    : m_model{model}
{
  for (auto id : signs)
  {
    auto& sign = model.signs.at(id);
    m_signs.push_back(
        qMakePair(id, SignData{sign.start(), sign.duration(), sign.grain(), sign.dynamicProfile(), sign.melodicProfile(), sign.rhythmicProfile()}));
  }
}

void RemoveSigns::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  for (auto& sign : m_signs)
  {
    model.signs.add(new Sign{sign.first, sign.second, &model});
  }
}

void RemoveSigns::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  for (auto& sign : m_signs)
  {
    model.signs.remove(sign.first);
  }
}

void RemoveSigns::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_signs;
}

void RemoveSigns::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_signs;
}
}