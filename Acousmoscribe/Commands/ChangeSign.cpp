#include "ChangeSign.hpp"

#include <Acousmoscribe/Model/Process.hpp>
#include <Process/TimeValueSerialization.hpp>

#include <score/model/path/PathSerialization.hpp>
#include <score/tools/IdentifierGeneration.hpp>

namespace Acousmoscribe
{

/* ChangeDynamicProfile */

ChangeDynamicProfile::ChangeDynamicProfile(
    const Model& model,
    const Id<Sign>& to_change,
    DynamicProfile dyn)
    : m_model{model}
{
  auto& mKey = model.signs.at(to_change);
  SignData data = mKey.signData();
  m_before = qMakePair(mKey.id(), data);
  data.setDynamicProfile(dyn);
  m_after = qMakePair(mKey.id(), data);
}

void ChangeDynamicProfile::update(unused_t, unused_t, DynamicProfile dyn)
{
  m_after.second.setDynamicProfile(dyn);
}

void ChangeDynamicProfile::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_before;
  auto& m = model.signs.at(mKey.first);
  m.setDynamicProfile(mKey.second.dynamicProfile());
}

void ChangeDynamicProfile::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_after;
  auto& m = model.signs.at(mKey.first);
  m.setDynamicProfile(mKey.second.dynamicProfile());
}

void ChangeDynamicProfile::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_before << m_after;
}

void ChangeDynamicProfile::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_before >> m_after;
}


/* ChangeMelodicProfile */

ChangeMelodicProfile::ChangeMelodicProfile(
    const Model& model,
    const Id<Sign>& to_change,
    MelodicProfile melo)
    : m_model{model}
{
  auto& mKey = model.signs.at(to_change);
  SignData data = mKey.signData();
  m_before = qMakePair(mKey.id(), data);
  data.setMelodicProfile(melo);
  m_after = qMakePair(mKey.id(), data);
}

void ChangeMelodicProfile::update(unused_t, unused_t, MelodicProfile melo)
{
  m_after.second.setMelodicProfile(melo);
}

void ChangeMelodicProfile::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_before;
  auto& m = model.signs.at(mKey.first);
  m.setMelodicProfile(mKey.second.melodicProfile());
}

void ChangeMelodicProfile::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_after;
  auto& m = model.signs.at(mKey.first);
  m.setMelodicProfile(mKey.second.melodicProfile());
}

void ChangeMelodicProfile::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_before << m_after;
}

void ChangeMelodicProfile::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_before >> m_after;
}


/* ChangeRhythmicProfile */

ChangeRhythmicProfile::ChangeRhythmicProfile(
    const Model& model,
    const Id<Sign>& to_change,
    RhythmicProfile rhythm)
    : m_model{model}
{
  auto& mKey = model.signs.at(to_change);
  SignData data = mKey.signData();
  m_before = qMakePair(mKey.id(), data);
  data.setRhythmicProfile(rhythm);
  m_after = qMakePair(mKey.id(), data);
}

void ChangeRhythmicProfile::update(unused_t, unused_t, RhythmicProfile rhythm)
{
  m_after.second.setRhythmicProfile(rhythm);
}

void ChangeRhythmicProfile::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_before;
  auto& m = model.signs.at(mKey.first);
  m.setRhythmicProfile(mKey.second.rhythmicProfile());
}

void ChangeRhythmicProfile::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_after;
  auto& m = model.signs.at(mKey.first);
  m.setRhythmicProfile(mKey.second.rhythmicProfile());
}

void ChangeRhythmicProfile::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_before << m_after;
}

void ChangeRhythmicProfile::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_before >> m_after;
}


/* ChangeGrain */

ChangeGrain::ChangeGrain(
    const Model& model,
    const Id<Sign>& to_change,
    Grain grain)
    : m_model{model}
{
  auto& mKey = model.signs.at(to_change);
  SignData data = mKey.signData();
  m_before = qMakePair(mKey.id(), data);
  data.setGrain(grain);
  m_after = qMakePair(mKey.id(), data);
}

void ChangeGrain::update(unused_t, unused_t, Grain grain)
{
  m_after.second.setGrain(grain);
}

void ChangeGrain::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_before;
  auto& m = model.signs.at(mKey.first);
  m.setGrain(mKey.second.grain());
}

void ChangeGrain::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  auto& mKey = m_after;
  auto& m = model.signs.at(mKey.first);
  m.setGrain(mKey.second.grain());
}

void ChangeGrain::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_before << m_after;
}

void ChangeGrain::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_before >> m_after;
}

}