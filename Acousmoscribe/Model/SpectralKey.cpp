#include "SpectralKey.hpp"

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
SpectralKeyData::SpectralKeyData(Nature nature, Nature nature2, bool isHybrid, bool isHybrid2, bool isRich, bool isRich2, bool isWarped, bool isWarped2)
        : m_nature(nature), m_nature2(nature2), m_isHybrid(isHybrid), m_isHybrid2(isHybrid2), m_isRich(isRich), m_isRich2(isRich2), m_isWarped(isWarped), m_isWarped2(isWarped2)
        {
        }

Nature SpectralKeyData::nature() const{ 
    return m_nature; 
}

Nature SpectralKeyData::nature2() const {
    return m_nature2;
}

bool SpectralKeyData::isHybrid() const{ 
    return m_isHybrid; 
}

bool SpectralKeyData::isHybrid2() const{ 
    return m_isHybrid2; 
}

bool SpectralKeyData::isRich() const{ 
    return m_isRich; 
}

bool SpectralKeyData::isRich2() const{ 
    return m_isRich2; 
}

bool SpectralKeyData::isWarped() const{ 
    return m_isWarped; 
}

bool SpectralKeyData::isWarped2() const{ 
    return m_isWarped2; 
}

void SpectralKeyData::setNature(Nature nature) {
    m_nature = nature;
}

void SpectralKeyData::setNature2(Nature nature2) {
    m_nature2 = nature2;
}

void SpectralKeyData::setIsHybrid(bool h) { 
    m_isHybrid = h;
}

void SpectralKeyData::setIsHybrid2(bool h) { 
    m_isHybrid2 = h;
}

void SpectralKeyData::setIsRich(bool r) {
    m_isRich = r;
}

void SpectralKeyData::setIsRich2(bool r) {
    m_isRich2 = r;
}

void SpectralKeyData::setIsWarped(bool w) { 
    m_isWarped = w;
}

void SpectralKeyData::setIsWarped2(bool w) { 
    m_isWarped2 = w;
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
    , m_isHybrid2(s.m_isHybrid2)
    , m_isRich(s.m_isRich)
    , m_isRich2(s.m_isRich2)
    , m_isWarped(s.m_isWarped)
    , m_isWarped2(s.m_isWarped2)
    {}

Nature SpectralKey::nature() const noexcept {
    return m_nature;
}

Nature SpectralKey::nature2() const noexcept {
    return m_nature2;
}

bool SpectralKey::isHybrid() const noexcept {
    return m_isHybrid;
}

bool SpectralKey::isHybrid2() const noexcept {
    return m_isHybrid2;
}

bool SpectralKey::isRich() const noexcept {
    return m_isRich;
}

bool SpectralKey::isRich2() const noexcept {
    return m_isRich2;
}

bool SpectralKey::isWarped() const noexcept {
    return m_isWarped;
}

bool SpectralKey::isWarped2() const noexcept {
    return m_isWarped2;
}

SpectralKeyData SpectralKey::spectralKeyData() const {
    return SpectralKeyData{m_nature, m_nature2, m_isHybrid, m_isHybrid2, m_isRich, m_isRich2, m_isWarped, m_isWarped2};
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

void SpectralKey::setIsHybrid2(bool isHybrid2){
    m_isHybrid2 = isHybrid2;
}

void SpectralKey::setIsRich(bool isRich){
    m_isRich = isRich;
}

void SpectralKey::setIsRich2(bool isRich){
    m_isRich2 = isRich;
}

void SpectralKey::setIsWarped(bool isWarped){
    m_isHybrid2 = isWarped;
}

void SpectralKey::setIsWarped2(bool isWarped2){
    m_isHybrid2 = isWarped2;
}

void SpectralKey::setData(SpectralKeyData sd){
    m_nature = sd.nature();
    m_nature2 = sd.nature2();
    m_isHybrid = sd.isHybrid();
    m_isHybrid2 = sd.isHybrid2();
    m_isRich = sd.isRich();
    m_isRich2 = sd.isRich2();
    m_isWarped = sd.isWarped();
    m_isWarped = sd.isWarped();
}

}
