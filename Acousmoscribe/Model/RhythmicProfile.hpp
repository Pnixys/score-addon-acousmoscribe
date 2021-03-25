#ifndef RHYTHM_DEFINE
#define RHYTHM_DEFINE

#include <iostream>

#include <verdigris>

namespace Acousmoscribe{
enum Speed
{
    continuous = 0, //no rhythm
    slow,
    medium,
    fast
};

enum Acceleration
{
    constant =0,
    accelerating,
    decelerating
};

class RhythmicProfile {

public:
    RhythmicProfile(){}
    RhythmicProfile(Speed rhythmVar, Acceleration acceleration, bool random);
    ~RhythmicProfile();
    Speed speed() const noexcept { return m_speed; }
    Acceleration acceleration() const noexcept { return m_acceleration; } 
    bool isRandom() const noexcept { return m_isRandom; }

    void setSpeed(Speed speed);
    void setAcceleration(Acceleration acceleration);
    void setIsRandom(bool rand);

private:
    Speed m_speed{};
    Acceleration m_acceleration{};
    bool m_isRandom{false};
};

}
#endif