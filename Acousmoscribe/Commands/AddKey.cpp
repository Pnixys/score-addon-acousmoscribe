// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "AddKey.hpp"

#include <Acousmoscribe/Model/Process.hpp>
#include <Process/TimeValueSerialization.hpp>

#include <score/model/path/PathSerialization.hpp>
#include <score/tools/IdentifierGeneration.hpp>

namespace Acousmoscribe
{

AddMelodicKey::AddMelodicKey(const Model& model, const MelodicKeyData& data)
    : m_model{model}, m_id{getStrongId(model.melodicKeys)}, m_data{data}
{
}

void AddMelodicKey::undo(const score::DocumentContext& ctx) const
{
  m_model.find(ctx).melodicKeys.remove(m_id);
}

void AddMelodicKey::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  model.melodicKeys.add(new MelodicKey{m_id, m_data, &model});
}

void AddMelodicKey::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_id << m_data;
}

void AddMelodicKey::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_id >> m_data;
}


AddSpectralKey::AddSpectralKey(const Model& model, const SpectralKeyData& data)
    : m_model{model}, m_id{getStrongId(model.spectralKey)}, m_data{data}
{
}

void AddSpectralKey::undo(const score::DocumentContext& ctx) const
{
  m_model.find(ctx).spectralKey.remove(m_id);
}

void AddSpectralKey::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  model.spectralKey.add(new SpectralKey{m_id, m_data, &model});
}

void AddSpectralKey::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_id << m_data;
}

void AddSpectralKey::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_id >> m_data;
}

}
