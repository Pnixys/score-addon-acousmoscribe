#include "SpectralKey.hpp"

#include <wobjectimpl.h>
//W_OBJECT_IMPL(Acousmoscribe::SpectralKey)

namespace Model
{
/* 

SpectralKey::SpectralKey(const Id<SpectralKey>& id, QObject* parent)
    : IdentifiedObject<SpectralKey>(id, QStsringLiteral("SpectralKey"), parent)
{
}

SpectralKey::SpectralKey(const Id<SpectralKey>& id, SpectralKeyData n, QObject* parent)
    : IdentifiedObject<SpectralKey>(id, QStringLiteral("SpectralKey"), parent)
    , m_start{n.m_start}
    , m_duration{n.m_duration}
    , m_pitch{n.m_pitch}
    , m_velocity{n.m_velocity}
{
} */

/* SpectralKey::SpectralKey(Nature nature, bool isHybrid, bool isRich) {
    m_nature = nature;
    m_isHybrid = isHybrid;
    m_isRich = isRich;
    if(m_isRich)
        m_nature2 = nature;
};

SpectralKey::~SpectralKey(){} */

SpectralKey::SpectralKey(const Id<SpectralKey>& id, QObject* parent)
    : IdentifiedObject<SpectralKey>(id, QStringLiteral("SpectralKey"), parent)
    {}


SpectralKey::SpectralKey(const Id<SpectralKey>& id, SpectralKeyData s, QObject* parent)
    : IdentifiedObject<SpectralKey>(id, QStringLiteral("SpectralKey"), parent)
    , m_nature(s.m_nature)
    , m_nature2(s.m_nature2)
    , m_isHybrid(s.m_isHybrid)
    , m_isRich(s.m_isRich)
    {}


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

}