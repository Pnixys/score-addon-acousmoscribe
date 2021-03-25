#include "Process.hpp"

#include <wobjectimpl.h>

W_OBJECT_IMPL(Acousmoscribe::Model)
namespace Acousmoscribe
{

Model::Model(
    const TimeVal& duration, const Id<Process::ProcessModel>& id,
    QObject* parent)
    : Process::ProcessModel{duration, id, "AcousmoscribeProcess", parent}
{
  metadata().setInstanceName(*this);
}

Model::~Model()
{
}

QString Model::prettyName() const noexcept
{
  return tr("Acousmoscribe Process");
}

void Model::setDurationAndScale(const TimeVal& newDuration) noexcept 
{
  signsChanged();
  setDuration(newDuration);
}

void Model::setDurationAndGrow(const TimeVal& newDuration) noexcept 
{
  if(duration() == newDuration)
    return;
  if(newDuration == TimeVal::zero())
    return;
  auto ratio = double(duration().impl) / newDuration.impl;

  for (auto& sgn : signs)
    sgn.scale(ratio);

  signsChanged();
  setDuration(newDuration);
}

void Model::setDurationAndShrink(const TimeVal& newDuration) noexcept 
{
}
}
template <>
void DataStreamReader::read(const Acousmoscribe::Model& proc)
{
  insertDelimiter();
}

template <>
void DataStreamWriter::write(Acousmoscribe::Model& proc)
{
  checkDelimiter();
}

template <>
void JSONReader::read(const Acousmoscribe::Model& proc)
{
}

template <>
void JSONWriter::write(Acousmoscribe::Model& proc)
{
}
