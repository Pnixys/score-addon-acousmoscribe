#include "Sign.hpp"

#include <score/serialization/DataStreamVisitor.hpp>
#include <score/serialization/JSONVisitor.hpp>

#include <score/plugins/SerializableHelpers.hpp>
#include <score/model/EntitySerialization.hpp>
#include <score/model/EntityMapSerialization.hpp>

#include <wobjectimpl.h>
W_OBJECT_IMPL(Acousmoscribe::Sign)

namespace Acousmoscribe
{

/*********************
 * PARTIE SIGN DATA
 *********************/
SignData::SignData(double s, double d, Grain g, DynamicProfile dp, MelodicProfile mp, RhythmicProfile rp)
    : m_start{s}, m_duration{d}, m_grain{g}, m_dynamicProfile{dp}, m_melodicProfile{mp}, m_rhythmicProfile{rp}
{
}

double SignData::start() const {
  return m_start;
}

double SignData::duration() const {
  return m_duration;
}

double SignData::end() const {
  return m_start + m_duration;
}

DynamicProfile SignData::dynamicProfile() const {
  return m_dynamicProfile;
}

MelodicProfile SignData::melodicProfile() const {
  return m_melodicProfile;
}

RhythmicProfile SignData::rhythmicProfile() const {
  return m_rhythmicProfile;
}

Grain SignData::grain() const {
  return m_grain;
}


void SignData::setStart(double s) noexcept { m_start = s; }
void SignData::setDuration(double s) noexcept { m_duration = s; }
void SignData::setDynamicProfile(DynamicProfile dp) {m_dynamicProfile = dp; }
void SignData::setMelodicProfile(MelodicProfile mp) {m_melodicProfile = mp; }
void SignData::setRhythmicProfile(RhythmicProfile rp) {m_rhythmicProfile = rp; }
void SignData::setGrain(Grain g) {m_grain = g; }


/*********************
 * PARTIE SIGN
 *********************/
Sign::Sign(const Id<Sign>& id, QObject* parent)
    : IdentifiedObject<Sign>(id, QStringLiteral("Sign"), parent)
    {}

Sign::Sign(const Id<Sign>& id, SignData s, QObject* parent)
    : IdentifiedObject<Sign>(id, QStringLiteral("Sign"), parent)
    , m_start(s.m_start)
    , m_duration(s.m_duration)
    , _grain(s.m_grain)
    , _melodicProfile(s.m_melodicProfile)
    , _dynamicProfile(s.m_dynamicProfile)
    , _rhythmicProfile(s.m_rhythmicProfile)
    {}

double Sign::start() const noexcept {
  return m_start;
}

double Sign::duration() const noexcept {
  return m_duration;
}

double Sign::end() const noexcept {
  return m_start + m_duration;
}

/*
 * Getter de sign sur les profiles
 */
DynamicProfile Sign::dynamicProfile() const {
    return _dynamicProfile;
}

MelodicProfile Sign::melodicProfile() const {
    return _melodicProfile;
}

RhythmicProfile Sign::rhythmicProfile() const {
    return _rhythmicProfile;
}

Grain Sign::grain() const {
    return _grain;
}

/*
 * Getter de signData
 */
SignData Sign::signData() const {
    return SignData{m_start, m_duration, _grain, _dynamicProfile, _melodicProfile, _rhythmicProfile};
}

/*
 * Liste de tous les setters
 */
void Sign::scale(double s) noexcept
{
  if (s != 1.)
  {
    m_start *= s;
    m_duration *= s;
    signChanged();
  }
}

void Sign::setStart(double s) noexcept
{
  if (m_start != s)
  {
    m_start = s;
    signChanged();
  }
}

void Sign::setDuration(double s) noexcept 
{
  if (m_duration != s)
  {
    m_duration = s;
    signChanged();
  }
} 

void Sign::setDynamicProfile(DynamicProfile d)  {
    _dynamicProfile = d;
    signChanged();
}

void Sign::setMelodicProfile(MelodicProfile d) {

    _melodicProfile = d;
    signChanged();
}

void Sign::setRhythmicProfile(RhythmicProfile d) {
    _rhythmicProfile = d;
    signChanged();
}

void Sign::setGrain(Grain g)  {
    _grain = g;
    signChanged(); 
}

void Sign::setData(SignData d)  {
    m_start = d.m_start;
    m_duration = d.m_duration;
    _dynamicProfile = d.m_dynamicProfile;
    _melodicProfile = d.m_melodicProfile;
    _rhythmicProfile = d.m_rhythmicProfile;
    _grain = d.m_grain;
    signChanged();
}

}

/***************************************
 * Partie SERIALISATION DYNAMIC PROFILE
 ***************************************/
template <>
void DataStreamReader::read(const Acousmoscribe::DynamicProfile& dp)
{
  m_stream << dp.volumeStart << dp.volumeEnd;
  insertDelimiter();
} 

template <>
void DataStreamWriter::write(Acousmoscribe::DynamicProfile& dp)
{
  m_stream >> dp.volumeStart >> dp.volumeEnd;
  checkDelimiter();
} 

template <>
void JSONReader::read(const Acousmoscribe::DynamicProfile& dp)
{
  stream.StartArray();
  stream.Double(dp.volumeStart);
  stream.Double(dp.volumeEnd);
  stream.EndArray();
}

template <>
void JSONWriter::write(Acousmoscribe::DynamicProfile& dp)
{
  const auto& arr = base.GetArray();
  dp.volumeStart = arr[2].GetDouble();
  dp.volumeEnd = arr[3].GetDouble();
}