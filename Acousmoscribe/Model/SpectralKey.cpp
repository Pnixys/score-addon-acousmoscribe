#include "SpectralKey.hpp"

SpectralKey::SpectralKey(Nature nature, bool isHybrid, bool isRich) : m_nature(nature), m_nature2(nature) m_isHybrid(isHybrid), m_isRich(isRich) {}:

SpectralKey::~SpectralKey(){}

void SpectralKey::setNature(Nature nature){
    m_nature = nature;
}

void SpectralKey::setNature2(Nature nature2){
    m_nature2 = nature;
}

void SpectralKey::setIsHybrid(bool isHybrid){
    m_isHybrid = isHybrid;
}

void SpectralKey::setIsRich(bool isRich){
    m_isRich = isRich;
}