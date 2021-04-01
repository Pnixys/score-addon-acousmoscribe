#include "MelodicKey.hpp"
namespace Acousmoscribe{

MelodicKey::MelodicKey(Pitch pitch, Range range): m_pitch(pitch), m_range(range) {};

MelodicKey::~MelodicKey(){}

Pitch MelodicKey::getPitch() const noexcept { 
    return m_pitch;
}

Range MelodicKey::getRange() const noexcept { 
    return m_range;
}

void MelodicKey::setPitch(Pitch pitch) {
    m_pitch = pitch;
}

void MelodicKey::setRange(Range range) {
    m_range = range;
}
}