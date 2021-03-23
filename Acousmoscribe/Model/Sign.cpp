#include "Sign.hpp"

#include <wobjectimpl.h>
W_OBJECT_IMPL(Sign::Sign)

namespace Sign
{
Sign::Sign(const Id<Sign>& id, QOject* parent)
    : IdentifiedObject<Sign>(id, QStringLiteral("Sign"), parent){}

Sign::Sign(const Id<Sign>& id, SignData s, QObject* parent)
    : IdentifiedObject<Sign>(id, QStringLiteral("Sign"), parent)
    , m_start{s.m_start}
    , m_duration{s.m_duration}
    , _grain(s.m_grain)
    , _dynamicProfile(s.m_dynamicProfile)
    , _melodicProfile(s.m_melodicProfile)
    , _rhythmicProfile(s.m_rhytmicProfile)
    {}

/*
 * Getter de sign sur les profiles
 */
DynamicProfile Sign::dynamicProfile() const noexcept{
    return _dynamicProfile;
}

MelodicProfile Sign::melodicProfile() const noexcept{
    return _melodicProfile;
}

RhythmicProfile Sign::rythmicProfile() const noexcept{
    return _rhytmicProfile;
}

Grain Sign::grain() const noexcept{
    return _grain;
}

/*
 * Getter de signData
 */
SignData Sign::signData() const noexcept {
    return SignData{m_start, m_duration, _grain, _dunamicProfile, _melodicProfile, _rhytmicProfile};
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

void Sign::setDynamicProfile(DynamicProfile d) noexcept {
    _dynamicProfile = d;
    signChanged();
}

void Sign::setMelodicProfile(MelodicProfile d) noexcept{
    _melodicProfile = d;
    signChanged();
}

void Sign::setRhythmicProfile(RhythmicProfile d) noexcept{
    _rhytmicProfile = d;
    signChanged();
}

void Sign::setGrain(Grain g) noexcept {
    _grain = g;
    signChanged();
}

void Sign::setData(SignData d) noexcept {
    m_start = d.m_start;
    m_duration = d.m_duration;
    _dynamicProfile = d.m_dynamucProfile;
    _melodicProfile = d.m_melodicProfile;
    _rhytmicProfile = d.m_rhytmicProfile;
    _grain = d.m_grain;
    signChanged();
}

}