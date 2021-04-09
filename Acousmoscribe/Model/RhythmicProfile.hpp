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
    Speed speed() const noexcept;
    Acceleration acceleration() const noexcept;
    bool isRandom() const noexcept;

    void setSpeed(Speed speed);
    void setAcceleration(Acceleration acceleration);
    void setIsRandom(bool rand);

private:
    Speed m_speed{continuous};
    Acceleration m_acceleration{constant};
    bool m_isRandom{false};
};

inline bool operator==(RhythmicProfile const rp1, RhythmicProfile const rp2) {
  return rp1.acceleration() == rp2.acceleration() && rp1.speed() == rp2.speed() && rp1.isRandom() == rp2.isRandom();
}
}
#endif