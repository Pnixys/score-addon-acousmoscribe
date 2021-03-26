#include "Process.hpp"

#include <score/plugins/SerializableHelpers.hpp>
#include <score/model/EntitySerialization.hpp>
#include <score/model/EntityMapSerialization.hpp>

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
   if(duration() == newDuration)
    return;
  if(newDuration == TimeVal::zero())
    return;

  auto ratio = double(duration().impl) / newDuration.impl;
  auto inv_ratio = newDuration.impl / double(duration().impl);

  std::vector<Id<Sign>> toErase;
  for (Sign& n : signs)
  {
    if (n.end() >= inv_ratio)
    {
      toErase.push_back(n.id());
    }
    else
    {
      n.scale(ratio);
    }
  }

  for (auto& sign : toErase)
  {
    signs.remove(sign);
  }
  signsChanged();
  setDuration(newDuration);
}
}

/**
 * Serialization avec le structure data
 **/
/*
template <>
void DataStreamReader::read(const Acousmoscribe::Sign& s)
{
  m_stream << s.signData();
  insertDelimiter();
}

template <>
void DataStreamWriter::write(Acousmoscribe::Sign& s)
{
  Acousmoscribe::SignData d;
  m_stream >> d;
  s.setData(d);
  checkDelimiter();
}
 
template <>
void JSONReader::read(const Acousmoscribe::Sign& s)
{
  /* stream.Key("Note");
  stream.StartArray();
  stream.Double(n.m_start);
  stream.Double(n.m_duration);
  stream.Int(n.m_pitch);
  stream.Int(n.m_velocity);
  stream.EndArray(); 
}




template <>
void JSONWriter::write(Acousmoscribe::Sign& s)
{
  /* const auto& arr = obj["Note"].toArray();
  n.m_start = arr[0].GetDouble();
  n.m_duration = arr[1].GetDouble();
  n.m_pitch = arr[2].GetInt();
  n.m_velocity = arr[3].GetInt(); 
}

 */
/**
 * Serialization Avec le model en paramètre
 **/
template <>
void DataStreamReader::read(const Acousmoscribe::Model& proc)
{
  m_stream << (int32_t)proc.signs.size();

  for (const auto& sign : proc.signs)
  {
    readFrom(sign);
  } 

  insertDelimiter();
}

template <>
void DataStreamWriter::write(Acousmoscribe::Model& proc)
{
  int32_t sign_count;
  m_stream >> sign_count;

  for(; sign_count-- > 0;)
    proc.signs.add(new Acousmoscribe::Sign{*this, &proc});
  
  
  checkDelimiter();
}

template <>
void JSONReader::read(const Acousmoscribe::Model& proc)
{
  obj["Signs"] = proc.signs;
}

template <>
void JSONWriter::write(Acousmoscribe::Model& proc)
{
  for(const auto& json_vref : obj["Signs"].toArray()){
    JSONObject::Deserializer deserializer{json_vref};
    proc.signs.add(new Acousmoscribe::Sign{deserializer, &proc});
  }
}



