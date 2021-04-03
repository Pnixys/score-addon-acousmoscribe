#include "MelodicProfile.hpp"

#include <score/serialization/DataStreamVisitor.hpp>
#include <score/serialization/JSONVisitor.hpp>

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

Pitch MelodicProfile::pitch() const {
    return m_pitch;
}

Variation MelodicProfile::variation() const {
    return m_var;
}

}

template <>
void DataStreamReader::read(const Acousmoscribe::MelodicProfile& mp)
{
  m_stream << mp.pitch() << mp.variation();
  insertDelimiter();
}

template <>
void DataStreamWriter::write(Acousmoscribe::MelodicProfile& mp)
{
    Acousmoscribe::Pitch p;
    Acousmoscribe::Variation v;

    m_stream >> p >> v;
    
    mp.setPitch(p);
    mp.setVariation(v);
    checkDelimiter();
}

template <>
void JSONReader::read(const Acousmoscribe::MelodicProfile& mp){
    stream.StartArray();
    stream.Int(mp.pitch());
    stream.Int(mp.variation());
    stream.EndArray();
}

template <>
void JSONWriter::write(Acousmoscribe::MelodicProfile& mp)
{
  const auto& arr = base.GetArray();
  Acousmoscribe::Pitch p;
  switch (arr[0].GetInt())
  {
  case 0: p = Acousmoscribe::very_high; break;
  case 1: p = Acousmoscribe::high; break;
  case 2: p = Acousmoscribe::mid_high; break;
  case 3: p = Acousmoscribe::mid; break;
  case 4: p = Acousmoscribe::mid_low; break;
  case 5: p = Acousmoscribe::low; break;
  default: p = Acousmoscribe::very_low;
      break;
  }
  mp.setPitch(p);

  Acousmoscribe::Variation var;
  switch (arr[1].GetInt())
  {
  case 1: var = Acousmoscribe::ascending; break;
  case 2: var = Acousmoscribe::descending; break;
  case 3: var = Acousmoscribe::random_variation; break;
  default: var = Acousmoscribe::none;
      break;
  }
  mp.setVariation(var);
}