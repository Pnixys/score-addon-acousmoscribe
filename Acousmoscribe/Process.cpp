#include "Process.hpp"

#include <score/plugins/SerializableHelpers.hpp>
#include <score/model/EntitySerialization.hpp>
#include <score/model/EntityMapSerialization.hpp>

#include <score/serialization/DataStreamVisitor.hpp>
#include <score/serialization/JSONVisitor.hpp>

#include <Process/Dataflow/Port.hpp>

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


// PARTIE SERIALIZATION

// SERIALIZATION AVEC SIGNDATA
template <>
void DataStreamReader::read(const Acousmoscribe::SignData& sd)
{
  m_stream << sd.m_start << sd.m_duration << sd.m_grain << sd.m_dynamicProfile << sd.m_melodicProfile << sd.m_rhythmicProfile;
  insertDelimiter();
} 

template <>
void DataStreamWriter::write(Acousmoscribe::SignData& sd)
{
  m_stream >> sd.m_start >> sd.m_duration >> sd.m_grain >> sd.m_dynamicProfile >> sd.m_melodicProfile >> sd.m_rhythmicProfile;
  checkDelimiter();
}
 
template <>
void JSONReader::read(const Acousmoscribe::SignData& sd)
{
  stream.StartArray();
  stream.Double(sd.m_start);
  stream.Double(sd.m_duration);
  stream.Int(sd.m_grain);
  JSONReader::read(sd.m_dynamicProfile);
  JSONReader::read(sd.m_melodicProfile);
  JSONReader::read(sd.m_rhythmicProfile);
  stream.EndArray();
} 

template <>
void JSONWriter::write(Acousmoscribe::SignData& sd)
{
  const auto& arr = base.GetArray();
  sd.m_start = arr[0].GetDouble();
  sd.m_duration = arr[1].GetDouble();
  sd.m_grain = (Acousmoscribe::Grain) arr[2].GetInt();
  JSONWriter::write(sd.m_dynamicProfile); 
  JSONWriter::write(sd.m_melodicProfile);
  JSONWriter::write(sd.m_rhythmicProfile);
}

// SERIALIZATION AVEC SIGN
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
  stream.Key("Sign");
  stream.StartArray();
  stream.Double(s.m_start);
  stream.Double(s.m_duration);
  stream.Int(s._grain);
  JSONReader::read(s._dynamicProfile);
  JSONReader::read(s._melodicProfile);
  JSONReader::read(s._rhythmicProfile);
  stream.EndArray();
} 




template <>
void JSONWriter::write(Acousmoscribe::Sign& s)
{
  const auto& arr = obj["Sign"].toArray();
  s.m_start = arr[0].GetDouble();
  s.m_duration = arr[1].GetDouble();
  s._grain = (Acousmoscribe::Grain) arr[2].GetInt();
  JSONWriter::write(s._dynamicProfile); 
  JSONWriter::write(s._melodicProfile);
  JSONWriter::write(s._rhythmicProfile);
}



//SERIALIZATION AVEC LE MODEL
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
