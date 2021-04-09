// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "MoveSigns.hpp"

#include <Acousmoscribe/Model/Process.hpp>

#include <score/model/path/PathSerialization.hpp>

namespace Acousmoscribe
{

MoveSigns::MoveSigns(
    const Model& model,
    const std::vector<Id<Sign>>& to_move,
    double t_delta)
    : m_model{model}
{
  m_before.reserve(to_move.size());
  m_after.reserve(to_move.size());
  for (auto& sign_id : to_move)
  {
    auto& sign = model.signs.at(sign_id);
    SignData data = sign.signData();
    m_before.push_back(qMakePair(sign.id(), data));
    data.m_start = std::max(data.m_start + t_delta, 0.);
    m_after.push_back(qMakePair(sign.id(), data));
  }
}

void MoveSigns::undo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  for (const auto& sign : m_before)
  {
    auto& n = model.signs.at(sign.first);
    n.setStart(sign.second.start());
  }
  model.signsNeedUpdate();
}

void MoveSigns::redo(const score::DocumentContext& ctx) const
{
  auto& model = m_model.find(ctx);
  for (const auto& sign : m_after)
  {
    auto& n = model.signs.at(sign.first);
    n.setStart(sign.second.start());
  }
  model.signsNeedUpdate();
}

void MoveSigns::update(unused_t, unused_t, double t_delta)
{
  for(int i = 0, N = m_before.size(); i < N; i++)
  {
    auto& data = m_before[i].second;
    m_after[i].second.setStart(std::max(data.start() + t_delta, 0.));
  }
}

void MoveSigns::serializeImpl(DataStreamInput& s) const
{
  s << m_model << m_before << m_after;
}

void MoveSigns::deserializeImpl(DataStreamOutput& s)
{
  s >> m_model >> m_before >> m_after;
}

}
