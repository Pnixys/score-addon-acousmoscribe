#include "ChangeMelodicKey.hpp"

#include <Acousmoscribe/Model/Process.hpp>
#include <Process/TimeValueSerialization.hpp>

#include <score/model/path/PathSerialization.hpp>
#include <score/tools/IdentifierGeneration.hpp>

namespace Acousmoscribe
{
ChangeMelodicKeyPitch::ChangeMelodicKeyPitch(
    const Model& model,
    const Id<MelodicKey>& to_change,
    Pitch pitch)
    : m_model{model}
{
  auto& mKey = model.melodicKeys.at(to_change);
  MelodicKeyData data = mKey.melodicKeyData();
  m_before = qMakePair(mKey.id(), data);
  data.setPitch(pitch);
  m_after = qMakePair(mKey.id(), data);
}

void ChangeMelodicKeyPitch::update(unused_t, unused_t, Pitch pitch)
{
  m_after.second.setPitch(pitch);
}

void ChangeMelodicKeyPitch::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_before;
  auto& m = model.melodicKeys.at(mKey.first);
  m.setPitch(mKey.second.pitch());
}

void ChangeMelodicKeyPitch::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_after;
  auto& m = model.melodicKeys.at(mKey.first);
  m.setPitch(mKey.second.pitch());
}

void ChangeMelodicKeyPitch::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_before << m_after;
}

void ChangeMelodicKeyPitch::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_before >> m_after;
}


ChangeMelodicKeyRange::ChangeMelodicKeyRange(
    const Model& model,
    const Id<MelodicKey>& to_change,
    Range range)
    : m_model{model}
{
  auto& mKey = model.melodicKeys.at(to_change);
  MelodicKeyData data = mKey.melodicKeyData();
  m_before = qMakePair(mKey.id(), data);
  data.setRange(range);
  m_after = qMakePair(mKey.id(), data);
}

void ChangeMelodicKeyRange::update(unused_t, unused_t, Range range)
{
  m_after.second.setRange(range);
}

void ChangeMelodicKeyRange::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_before;
  auto& m = model.melodicKeys.at(mKey.first);
  m.setRange(mKey.second.range());
}

void ChangeMelodicKeyRange::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_after;
  auto& m = model.melodicKeys.at(mKey.first);
  m.setRange(mKey.second.range());
}

void ChangeMelodicKeyRange::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_before << m_after;
}

void ChangeMelodicKeyRange::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_before >> m_after;
}
}