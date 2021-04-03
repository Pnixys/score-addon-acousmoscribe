
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

Pitch MelodicKeyData::pitch() const {
    return m_pitch;
}

Range MelodicKeyData::range() const {
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

Pitch MelodicKey::pitch() const noexcept { 
    return m_pitch;
}

Range MelodicKey::range() const noexcept { 
    return m_range;
}

MelodicKeyData MelodicKey::melodicKeyData() const {
    return MelodicKeyData(m_pitch, m_range);
}

void MelodicKey::setPitch(Pitch pitch) {
    m_pitch = pitch;
    
}

void MelodicKey::setRange(Range range) {
    m_range = range;
}

void MelodicKey::setData(MelodicKeyData mkd){
    m_pitch = mkd.pitch();
    m_range = mkd.range();
}

}
