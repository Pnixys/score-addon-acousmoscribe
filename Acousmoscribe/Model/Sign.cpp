#include "Sign.hpp"

#include <wobjectimpl.h>
W_OBJECT_IMPL(Acousmoscribe::Sign)

namespace Acousmoscribe
{

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

/*
 * Getter de sign sur les profiles
 */
DynamicProfile Sign::dynamicProfile() const {
    return _dynamicProfile;
}

MelodicProfile Sign::melodicProfile() const {
    return _melodicProfile;
}

RhythmicProfile Sign::rythmicProfile() const {
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