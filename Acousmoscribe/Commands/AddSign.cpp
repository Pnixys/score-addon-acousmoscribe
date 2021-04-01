// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "AddSign.hpp"

#include <Acousmoscribe/Process.hpp>
#include <Process/TimeValueSerialization.hpp>

#include <score/model/path/PathSerialization.hpp>
#include <score/tools/IdentifierGeneration.hpp>

namespace Acousmoscribe
{

AddSign::AddSign(const Model& model, const SignData& n)
    : m_model{model}, m_id{getStrongId(model.signs)}, m_sign{n}
{
}

void AddSign::undo(const score::DocumentContext& ctx) const
{
  m_model.find(ctx).signs.remove(m_id);
}

void AddSign::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  model.signs.add(new Sign{m_id, m_sign, &model});
}


void AddSign::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_id << m_sign;
}

void AddSign::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_id >> m_sign;
}

ReplaceSigns::ReplaceSigns(
    const Model& model,
    const std::vector<SignData>& n,
    int min,
    int max,
    TimeVal d)
    : m_model{model}
    , m_olddur{model.duration()}
    , m_newdur{d}
{
  for (Sign& Sign : model.signs)
  {
    m_old.push_back({Sign.id(), Sign.signData()});
  }

  int i = 0;
  for (auto& Sign : n)
    m_new.push_back({Id<Acousmoscribe::Sign>{i++}, Sign});
}

void ReplaceSigns::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  model.signs.clear();
  model.setDuration(m_olddur);

  for (auto& Sign : m_old)
    model.signs.add(new Acousmoscribe::Sign{Sign.first, Sign.second, &model});

}

void ReplaceSigns::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  model.signs.clear();
  model.setDuration(m_newdur);

  for (auto& Sign : m_new)
    model.signs.add(new Acousmoscribe::Sign{Sign.first, Sign.second, &model});
}
}

void ReplaceSigns::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_old << m_new << m_olddur << m_newdur;
}

void ReplaceSigns::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_old >> m_olddur >> m_newdur;
}
}
