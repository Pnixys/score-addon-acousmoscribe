#include "MelodicProfile.hpp"

//#include <wobjectimpl.h>

//W_OBJECT_IMPL(Acousmoscribe::MelodicProfile)

namespace Acousmoscribe {

MelodicProfile::MelodicProfile(Pitch pitch, Variation var) : m_pitch(pitch), m_var(var) {};

MelodicProfile::~MelodicProfile(){}

void MelodicProfile::setPitch(Pitch pitch) {
    m_pitch = pitch;
}

void MelodicProfile::setVariation(Variation variation) {
    m_var = variation;
}

}