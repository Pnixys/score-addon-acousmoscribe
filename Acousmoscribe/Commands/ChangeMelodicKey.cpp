#include "ChangeMelodicKey.hpp"

#include <Acousmoscribe/Process.hpp>
#include <Process/TimeValueSerialization.hpp>

#include <score/model/path/PathSerialization.hpp>
#include <score/tools/IdentifierGeneration.hpp>

namespace Acousmoscribe
{
ChangeMelodicKeyPitch::ChangeMelodicKeyPitch(
    const Model& model,
    const Id<MelodicKey>& to_change,
    Pitch pitch)
    : m_model{model}, m_toChange{to_change}
{
  auto& melodicKey = model.melodicKeys.at(to_change);
  m_pitchBefore = melodicKey.pitch();
  m_pitchAfter = pitch;
}

void ChangeMelodicKeyPitch::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mk = model.melodicKeys.at(m_toChange);
  mk.setPitch(m_pitchBefore);
}

void ChangeMelodicKeyPitch::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mk = model.melodicKeys.at(m_toChange);
  mk.setPitch(m_pitchAfter);
}

void ChangeMelodicKeyPitch::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_toChange << m_pitchBefore << m_pitchAfter;
}

void ChangeMelodicKeyPitch::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_toChange >> m_pitchBefore >> m_pitchAfter;
}


ChangeMelodicKeyRange::ChangeMelodicKeyRange(
    const Model& model,
    const Id<MelodicKey>& to_change,
    Range range)
    : m_model{model}, m_toChange{to_change}
{
  auto& melodicKey = model.melodicKeys.at(to_change);
  m_rangeBefore = melodicKey.range();
  m_rangeAfter = range;
}

void ChangeMelodicKeyRange::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mk = model.melodicKeys.at(m_toChange);
  mk.setRange(m_rangeBefore);
}

void ChangeMelodicKeyRange::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mk = model.melodicKeys.at(m_toChange);
  mk.setRange(m_rangeAfter);
}

void ChangeMelodicKeyRange::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_toChange << m_rangeBefore << m_rangeAfter;
}

void ChangeMelodicKeyRange::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_toChange >> m_rangeBefore >> m_rangeAfter;
}






}