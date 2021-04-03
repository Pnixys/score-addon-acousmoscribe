#include "SpectralKey.hpp"

#include <wobjectimpl.h>

#include <score/plugins/SerializableHelpers.hpp>
#include <score/model/EntitySerialization.hpp>
#include <score/model/EntityMapSerialization.hpp>

#include <score/serialization/DataStreamVisitor.hpp>
#include <score/serialization/JSONVisitor.hpp>

#include <Process/Dataflow/Port.hpp>

#include <wobjectimpl.h>
W_OBJECT_IMPL(Acousmoscribe::SpectralKey)

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

Nature SpectralKeyData::getNature() const{ 
    return m_nature; 
}

Nature SpectralKeyData::getNature2() const {
    return m_nature2;
}

bool SpectralKeyData::isHybrid() const{ 
    return m_isHybrid; 
}

bool SpectralKeyData::isRich() const{ 
    return m_isRich; 
}

bool SpectralKeyData::isRich2() const{ 
    return m_isRich2; 
}

void SpectralKeyData::setNature(Nature nature) {
    m_nature = nature;
}

void SpectralKeyData::setNature2(Nature nature) {
    m_nature2 = m_nature;
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

SpectralKeyData SpectralKey::spectralKeyData() const {
    return SpectralKeyData{m_nature, m_isHybrid, m_isRich, m_isRich2};
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

void SpectralKey::setData(SpectralKeyData sd){
    m_nature = sd.getNature();
    m_nature2 = sd.getNature2();
    m_isHybrid = sd.isHybrid();
    m_isRich = sd.isRich();
    m_isRich2 = sd.isRich2();
}

}
