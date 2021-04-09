// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "AddSign.hpp"

#include <Acousmoscribe/Model/Process.hpp>
#include <Process/TimeValueSerialization.hpp>

#include <score/model/path/PathSerialization.hpp>
#include <score/tools/IdentifierGeneration.hpp>

namespace Acousmoscribe
{

AddSign::AddSign(const Model& model, const SignData& n)
    : m_model{model}, m_id{getStrongId(model.signs)}, m_sign{n}
{
  std::cout << "entré dans addsign\n";
  std::cout << "start : " << n.start() << "\n";
  std::cout << "duration : " << n.duration() << "\n";

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

}
