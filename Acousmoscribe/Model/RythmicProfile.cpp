#include "RhythmicProfile.hpp"

RhythmicProfile::RhythmicProfile(Speed rythmVar,  Acceleration acceleration, bool random) :
    m_speed(rythmVar), m_acceleration(acceleration), m_isRandom(random) {};

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