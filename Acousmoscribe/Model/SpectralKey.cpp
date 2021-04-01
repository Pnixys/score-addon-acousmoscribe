#include "SpectralKey.hpp"

#include <wobjectimpl.h>
//W_OBJECT_IMPL(Acousmoscribe::SpectralKey)

namespace Acousmoscribe
{

/***************************
 * PARTIE SPECTRAL KEY DATA
 ***************************/
SpectralKeyData::SpectralKeyData(Nature nature, bool isHybrid, bool isRich, bool isRich2)
        : m_nature(nature), m_isHybrid(isHybrid), m_isRich(isRich), m_isRich2(isRich2)
        {
            if(m_isRich)
                m_nature2 = nature;
            else
                m_nature2 = null;
        }

Nature SpectralKeyData::getNature() { 
    return m_nature; 
}
bool SpectralKeyData::isHybrid() { 
    return m_isHybrid; 
}
bool SpectralKeyData::isRich() { 
    return m_isRich; 
}

bool SpectralKeyData::isRich2() { 
    return m_isRich2; 
}

void SpectralKeyData::setNature(Nature nature) {
    m_nature = nature;
    if(m_isRich)
        m_nature2 = nature;
}

void SpectralKeyData::setHybrid(bool h) { 
    m_isHybrid = h;
}
void SpectralKeyData::setRich(bool r) {
    m_isRich = r;
}

void SpectralKeyData::setRich2(bool r) {
    m_isRich2 = r;
}

/**********************
 * PARTIE SPECTRAL KEY
 **********************/
SpectralKey::SpectralKey(const Id<SpectralKey>& id, QObject* parent)
    : IdentifiedObject<SpectralKey>(id, QStringLiteral("SpectralKey"), parent)
    {}


SpectralKey::SpectralKey(const Id<SpectralKey>& id, SpectralKeyData s, QObject* parent)
    : IdentifiedObject<SpectralKey>(id, QStringLiteral("SpectralKey"), parent)
    , m_nature(s.m_nature)
    , m_nature2(s.m_nature2)
    , m_isHybrid(s.m_isHybrid)
    , m_isRich(s.m_isRich)
    , m_isRich2(s.m_isRich2)
    {}

Nature SpectralKey::getNature() const noexcept {
    return m_nature;
}

Nature SpectralKey::getNature2() const noexcept {
    return m_nature2;
}

bool SpectralKey::isHybrid() const noexcept {
    return m_isHybrid;
}

bool SpectralKey::isRich() const noexcept {
    return m_isRich;
}

bool SpectralKey::isRich2() const noexcept {
    return m_isRich2;
}

void SpectralKey::setNature(Nature nature){
    m_nature = nature;
}

void SpectralKey::setNature2(Nature nature2){
    m_nature2 = nature2;
}

void SpectralKey::setIsHybrid(bool isHybrid){
    m_isHybrid = isHybrid;
}

void SpectralKey::setIsRich(bool isRich){
    m_isRich = isRich;
}

void SpectralKey::setIsRich2(bool isRich){
    m_isRich2 = isRich;
}

}