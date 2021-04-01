#include "RhythmicProfile.hpp"

#include <score/serialization/DataStreamVisitor.hpp>
#include <score/serialization/JSONVisitor.hpp>

#include <score/plugins/SerializableHelpers.hpp>
#include <score/model/EntitySerialization.hpp>
#include <score/model/EntityMapSerialization.hpp>


#include <wobjectimpl.h>

//W_OBJECT_IMPL(Acousmoscribe::RhythmicProfile)

namespace Acousmoscribe {

RhythmicProfile::RhythmicProfile(Speed rhythmVar,  Acceleration acceleration, bool random) :
    m_speed(rhythmVar), m_acceleration(acceleration), m_isRandom(random) {};

RhythmicProfile::~RhythmicProfile(){}

Speed RhythmicProfile::speed() const noexcept { 
    return m_speed;
}

Acceleration RhythmicProfile::acceleration() const noexcept { 
    return m_acceleration; 
} 

bool RhythmicProfile::isRandom() const noexcept {
    return m_isRandom;
}

void RhythmicProfile::setSpeed(Speed speed) {
    m_speed = speed;
}

void RhythmicProfile::setAcceleration(Acceleration acceleration) {
    m_acceleration = acceleration;
}

void RhythmicProfile::setIsRandom(bool rand){
    m_isRandom = rand;
}

}

template <>
void DataStreamReader::read(const Acousmoscribe::RhythmicProfile& rp)
{
  m_stream << rp.speed() << rp.acceleration() << rp.isRandom();
  insertDelimiter();
}

template <>
void DataStreamWriter::write(Acousmoscribe::RhythmicProfile& rp)
{
    Acousmoscribe::Speed s;
    Acousmoscribe::Acceleration a;
    bool random;

    m_stream >> s >> a >> random;

    rp.setSpeed(s);
    rp.setAcceleration(a);
    rp.setIsRandom(random);

    checkDelimiter();
}

template <>
void JSONReader::read(const Acousmoscribe::RhythmicProfile& rp){
    stream.StartArray();
    stream.Int(rp.speed());
    stream.Int(rp.acceleration());
    stream.Bool(rp.isRandom());
    stream.EndArray();
}

template <>
void JSONWriter::write(Acousmoscribe::RhythmicProfile& rp)
{
  const auto& arr = base.GetArray();

  Acousmoscribe::Speed s;
  switch (arr[0].GetInt())
  {
  case 1: s = Acousmoscribe::slow; break;
  case 2: s = Acousmoscribe::medium; break;
  case 3: s = Acousmoscribe::fast; break;
  default: s = Acousmoscribe::continuous;
      break;
  }
  rp.setSpeed(s);

  Acousmoscribe::Acceleration a;
  switch (arr[1].GetInt())
  {
  case 1: a = Acousmoscribe::accelerating; break;
  case 2: a = Acousmoscribe::decelerating; break;
  default: a = Acousmoscribe::constant;
      break;
  }
  rp.setAcceleration(a);
  rp.setIsRandom(arr[2].GetBool());
}