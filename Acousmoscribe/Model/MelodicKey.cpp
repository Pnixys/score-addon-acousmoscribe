#include "MelodicKey.hpp"
namespace Model{

MelodicKey::MelodicKey(Pitch pitch, Range range): m_pitch(pitch), m_range(range) {};

MelodicKey::~MelodicKey(){}

void MelodicKey::setPitch(Pitch pitch) {
    m_pitch = pitch;
}

void MelodicKey::setRange(Range range) {
    m_range = range;
}
}