#include "RhythmicProfile.hpp"


#include <wobjectimpl.h>

//W_OBJECT_IMPL(Acousmoscribe::RhythmicProfile)

namespace Model {

RhythmicProfile::RhythmicProfile(Speed rhythmVar,  Acceleration acceleration, bool random) :
    m_speed(rhythmVar), m_acceleration(acceleration), m_isRandom(random) {};

RhythmicProfile::~RhythmicProfile(){}

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