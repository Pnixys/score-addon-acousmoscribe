
#include "MelodicKey.hpp"

#include <score/serialization/DataStreamVisitor.hpp>
#include <score/serialization/JSONVisitor.hpp>

#include <score/plugins/SerializableHelpers.hpp>
#include <score/model/EntitySerialization.hpp>
#include <score/model/EntityMapSerialization.hpp>


#include <wobjectimpl.h>
W_OBJECT_IMPL(Acousmoscribe::MelodicKey)

namespace Acousmoscribe{


/**************************
 * PARTIE MELPDIC KEY DATA
 **************************/
MelodicKeyData::MelodicKeyData(Pitch p, Range r) 
    : m_pitch{p}, m_range{r}
{   
}

Pitch MelodicKeyData::getPitch() const {
    return m_pitch;
}

Range MelodicKeyData::getRange() const {
    return m_range;
}

void MelodicKeyData::setPitch(Pitch p){
    m_pitch = p;
}

void MelodicKeyData::setRange(Range r){
    m_range = r;
}

/*********************
 * PARTIE MELODIC KEY
 *********************/ 

MelodicKey::MelodicKey(const Id<MelodicKey>& id, QObject* parent)
    : IdentifiedObject<MelodicKey>(id, QStringLiteral("MelodicKey"), parent)
    {}


MelodicKey::MelodicKey(const Id<MelodicKey>& id, MelodicKeyData m, QObject* parent)
    : IdentifiedObject<MelodicKey>(id, QStringLiteral("MelodicKey"), parent)
    , m_pitch{m.m_pitch}
    , m_range{m.m_range}
    {}

/* MelodicKey::MelodicKey(Pitch pitch, Range range)
    : m_pitch(pitch), m_range(range) 
{
} */

//MelodicKey::~MelodicKey(){}

Pitch MelodicKey::getPitch() noexcept { 
    return m_pitch;
}

Range MelodicKey::getRange() noexcept { 
    return m_range;
}

<<<<<<< HEAD
void MelodicKey::setPitch(Pitch pitch) noexcept{ 
=======
MelodicKeyData MelodicKey::melodicKeyData() const {
    return MelodicKeyData(m_pitch, m_range);
}

void MelodicKey::setPitch(Pitch pitch) {
>>>>>>> c4a8de7376bbbc754568e2be623fcdd14acfa38e
    m_pitch = pitch;
    
}

void MelodicKey::setRange(Range range) noexcept {
    m_range = range;
}
<<<<<<< HEAD
}
=======

void MelodicKey::setData(MelodicKeyData mkd){
    m_pitch = mkd.getPitch();
    m_range = mkd.getRange();
}

}
>>>>>>> c4a8de7376bbbc754568e2be623fcdd14acfa38e
