#ifndef RYTHM_DEFINE
#define RYTHM_DEFINE

#include <iostream>

enum Speed
{
    continuous = 0, //no rythm
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
    RhythmicProfile(Speed rythmVar, Acceleration acceleration, bool random);

    Speed speed() const noexcept { return m_speed; }
    Acceleration acceleration() const noexcept { return m_acceleration; } 
    bool isRandom() const noexcept { return m_isRandom; }

    void setSpeed(Speed s) noexcept;
    void setAcceleration(Acceleration a) noexcept;
    void setIsRandom(bool r) noexcept;

private:
    Speed m_speed{};
    Acceleration m_acceleration{};
    bool m_isRandom{false};
};

#endif