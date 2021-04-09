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

/************************************
 * SERIALISATION SIGN AVEC SIGN DATA
 ************************************/
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

/*******************************
 * SERIALISATION SIGN AVEC SIGN
 ******************************/
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



/***********************************
 * SERIALISATION SIGN AVEC LE MODEL
 ***********************************/
template <>
void DataStreamReader::read(const Acousmoscribe::Model& proc)
{
  m_stream << (int32_t)proc.signs.size();

  for (const auto& sign : proc.signs)
  {
    readFrom(sign);
  } 

  m_stream << (int32_t)proc.spectralKey.size();

  for (const auto& speck : proc.spectralKey)
  {
    readFrom(speck);
  }

  m_stream << (int32_t)proc.melodicKeys.size();

  for (const auto& melok : proc.melodicKeys)
  {
    readFrom(melok);
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
  
  int32_t speck_count;
  m_stream >> speck_count;

  for(; speck_count-- >0;)
    proc.spectralKey.add(new Acousmoscribe::SpectralKey{*this, &proc});
  
  int32_t melok_count;
  m_stream >> melok_count;

  for(; speck_count-- >0;)
    proc.melodicKeys.add(new Acousmoscribe::MelodicKey{*this, &proc});

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

/**********************************
 * SERIALISATION SPECTRAL KEY DATA
 **********************************/

template <>
void DataStreamReader::read(const Acousmoscribe::SpectralKeyData& skd)
{
  m_stream << skd.nature() << skd.nature2() << skd.isHybrid() << skd.isHybrid2() << skd.isRich() << skd.isRich2() << skd.isWarped() << skd.isWarped2();
  insertDelimiter();
} 

template <>
void DataStreamWriter::write(Acousmoscribe::SpectralKeyData& skd)
{
    Acousmoscribe::Nature nat;
    Acousmoscribe::Nature nat2;
    bool hyb, hyb2, rich, rich2, warp, warp2;
    m_stream >> nat >> nat2 >> hyb >> hyb2 >> rich >> rich2 >> warp >> warp2;
    skd.setNature(nat);
    skd.setNature2(nat2);
    skd.setIsHybrid(hyb);
    skd.setIsHybrid2(hyb2);
    skd.setIsRich(rich);
    skd.setIsRich2(rich2);
    skd.setIsWarped(warp);
    skd.setIsWarped2(warp2);
    checkDelimiter();
} 

template <>
void JSONReader::read(const Acousmoscribe::SpectralKeyData& skd)
{
  stream.StartArray();
  stream.Int(skd.nature());
  stream.Int(skd.nature2());
  stream.Bool(skd.isHybrid());
  stream.Bool(skd.isHybrid2());
  stream.Bool(skd.isRich());
  stream.Bool(skd.isRich2());
  stream.Bool(skd.isWarped());
  stream.Bool(skd.isWarped());
  stream.EndArray();
}

template <>
void JSONWriter::write(Acousmoscribe::SpectralKeyData& skd)
{
  const auto& arr = base.GetArray();
  Acousmoscribe::Nature n;
  switch (arr[0].GetInt())
  {
  case 1: n = Acousmoscribe::tonic; break;
  case 2: n = Acousmoscribe::inharmonic; break;
  case 3: n = Acousmoscribe::noise; break;
  default: n = Acousmoscribe::null;
    break;
  }
  skd.setNature(n);

  switch (arr[1].GetInt())
  {
  case 1: n = Acousmoscribe::tonic; break;
  case 2: n = Acousmoscribe::inharmonic; break;
  case 3: n = Acousmoscribe::noise; break;
  default: n = Acousmoscribe::null;
    break;
  }
  skd.setNature2(n);
  skd.setIsHybrid(arr[2].GetBool());
  skd.setIsRich(arr[3].GetBool());
  skd.setIsRich2(arr[4].GetBool());
}

/****************************
 * SERIALISATION SPECTRAL KEY
 ****************************/

template <>
void DataStreamReader::read(const Acousmoscribe::SpectralKey& sk)
{
  m_stream << sk.spectralKeyData();
  insertDelimiter();
} 

template <>
void DataStreamWriter::write(Acousmoscribe::SpectralKey& sk)
{
    Acousmoscribe::SpectralKeyData sd;
    m_stream >> sd;
    sk.setData(sd);
    checkDelimiter();
} 

template <>
void JSONReader::read(const Acousmoscribe::SpectralKey& sk)
{
  stream.StartArray();
  stream.Int(sk.nature());
  stream.Int(sk.nature2());
  stream.Bool(sk.isHybrid());
  stream.Bool(sk.isHybrid2());
  stream.Bool(sk.isRich());
  stream.Bool(sk.isRich2());
  stream.Bool(sk.isWarped());
  stream.Bool(sk.isWarped2());
  stream.EndArray();
}

template <>
void JSONWriter::write(Acousmoscribe::SpectralKey& sk)
{
  const auto& arr = base.GetArray();
  Acousmoscribe::Nature n;
  switch (arr[0].GetInt())
  {
  case 1: n = Acousmoscribe::tonic; break;
  case 2: n = Acousmoscribe::inharmonic; break;
  case 3: n = Acousmoscribe::noise; break;
  default: n = Acousmoscribe::null;
    break;
  }
  sk.setNature(n);

  switch (arr[1].GetInt())
  {
  case 1: n = Acousmoscribe::tonic; break;
  case 2: n = Acousmoscribe::inharmonic; break;
  case 3: n = Acousmoscribe::noise; break;
  default: n = Acousmoscribe::null;
    break;
  }
  sk.setNature2(n);
  sk.setIsHybrid(arr[2].GetBool());
  sk.setIsHybrid2(arr[3].GetBool());
  sk.setIsRich(arr[4].GetBool());
  sk.setIsRich2(arr[5].GetBool());
  sk.setIsWarped(arr[6].GetBool());
  sk.setIsWarped2(arr[7].GetBool());
}


/*********************************
 * SERIALISATION MELODIC KEY DATA
 *********************************/
template <>
void DataStreamReader::read(const Acousmoscribe::MelodicKeyData& mkd)
{
  m_stream << mkd.pitch() << mkd.range();
  insertDelimiter();
} 

template <>
void DataStreamWriter::write(Acousmoscribe::MelodicKeyData& mkd)
{
  Acousmoscribe::Pitch p;
  Acousmoscribe::Range r;
  m_stream >> p >> r;
  mkd.setPitch(p);
  mkd.setRange(r);
  checkDelimiter();
} 

template <>
void JSONReader::read(const Acousmoscribe::MelodicKeyData& mkd)
{
  stream.StartArray();
  stream.Int(mkd.pitch());
  stream.Int(mkd.range());
  stream.EndArray();
}

template <>
void JSONWriter::write(Acousmoscribe::MelodicKeyData& mkd)
{
  const auto& arr = base.GetArray();
  Acousmoscribe::Pitch p;
  switch (arr[0].GetInt())
  {
  case 1: p = Acousmoscribe::high; break;
  case 2: p = Acousmoscribe::mid_high; break;
  case 3: p = Acousmoscribe::mid; break;
  case 4: p = Acousmoscribe::mid_low; break;
  case 5: p = Acousmoscribe::low; break;
  case 6: p = Acousmoscribe::very_low; break;
  default: p = Acousmoscribe::very_high;
    break;
  }
  mkd.setPitch(p);

  Acousmoscribe::Range r;
  switch (arr[1].GetInt())
  {
  case 1: r = Acousmoscribe::normal; break;
  case 2: r = Acousmoscribe::strong; break;
  default: r = Acousmoscribe::weak;
    break;
  }
  mkd.setRange(r);
}

/****************************
 * SERIALISATION MELODIC KEY
 ****************************/
template <>
void DataStreamReader::read(const Acousmoscribe::MelodicKey& mk)
{
  m_stream << mk.melodicKeyData();
  insertDelimiter();
} 

template <>
void DataStreamWriter::write(Acousmoscribe::MelodicKey& mk)
{
  Acousmoscribe::MelodicKeyData mkd;
  m_stream >> mkd;
  mk.setData(mkd);
  checkDelimiter();
} 

template <>
void JSONReader::read(const Acousmoscribe::MelodicKey& mk)
{
  stream.StartArray();
  stream.Int(mk.pitch());
  stream.Int(mk.range());
  stream.EndArray();
}

template <>
void JSONWriter::write(Acousmoscribe::MelodicKey& mk)
{
  const auto& arr = base.GetArray();
  Acousmoscribe::Pitch p;
  switch (arr[0].GetInt())
  {
  case 1: p = Acousmoscribe::high; break;
  case 2: p = Acousmoscribe::mid_high; break;
  case 3: p = Acousmoscribe::mid; break;
  case 4: p = Acousmoscribe::mid_low; break;
  case 5: p = Acousmoscribe::low; break;
  case 6: p = Acousmoscribe::very_low; break;
  default: p = Acousmoscribe::very_high;
    break;
  }
  mk.setPitch(p);

  Acousmoscribe::Range r;
  switch (arr[1].GetInt())
  {
  case 1: r = Acousmoscribe::normal; break;
  case 2: r = Acousmoscribe::strong; break;
  default: r = Acousmoscribe::weak;
    break;
  }
  mk.setRange(r);
}