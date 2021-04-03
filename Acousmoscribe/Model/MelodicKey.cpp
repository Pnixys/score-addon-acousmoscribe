#include "MelodicKey.hpp"
namespace Acousmoscribe{

MelodicKey::MelodicKey(Pitch pitch, Range range): m_pitch(pitch), m_range(range) {};

MelodicKey::~MelodicKey(){}

Pitch MelodicKey::getPitch() noexcept { 
    return m_pitch;
}

Range MelodicKey::getRange() noexcept { 
    return m_range;
}

void MelodicKey::setPitch(Pitch pitch) noexcept{ 
    m_pitch = pitch;
    
}

void MelodicKey::setRange(Range range) noexcept {
    m_range = range;
}
}
