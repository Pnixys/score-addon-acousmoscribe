#include "ChangeProfile.hpp"

#include <Acousmoscribe/Process.hpp>
#include <Process/TimeValueSerialization.hpp>

#include <score/model/path/PathSerialization.hpp>
#include <score/tools/IdentifierGeneration.hpp>

namespace Acousmoscribe
{
ChangeDynamicProfile::ChangeDynamicProfile(
    const Model& model,
    const Id<Sign>& to_change,
    DynamicProfile dyn)
    : m_model{model}, m_toChange{to_change}
{
  auto& sign = model.signs.at(to_change);
  m_dynBefore = sign.dynamicProfile();
  m_dynAfter = dyn;
}

void ChangeDynamicProfile::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& s = model.signs.at(m_toChange);
  s.setDynamicProfile(m_dynBefore);
}

void ChangeDynamicProfile::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& s = model.signs.at(m_toChange);
  s.setDynamicProfile(m_dynAfter);
}

void ChangeDynamicProfile::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_toChange << m_dynBefore << m_dynAfter;
}

void ChangeDynamicProfile::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_toChange >> m_dynBefore >> m_dynAfter;
}
}