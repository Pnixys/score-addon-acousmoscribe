#pragma once
#include <iostream>

//#include <verdigris>

namespace Acousmoscribe{

enum Pitch
{
    very_high = 0,
    high,
    mid_high,
    mid,
    mid_low,
    low,
    very_low
};

enum Variation
{
    none = 0,
    ascending,
    descending,
    random_variation
};

class MelodicProfile{
public:
    MelodicProfile(){}
    MelodicProfile(Pitch pitch, Pitch pitchEnd, Variation var);
    ~MelodicProfile();
    void setPitch(Pitch pitch);
    void setPitchEnd(Pitch pitchEnd);
    void setVariation(Variation variation);
    Pitch pitch() const;
    Pitch pitchEnd() const;
    Variation variation() const;

private:
    Pitch m_pitch{mid};
    Pitch m_pitchEnd{mid};
    Variation m_var{none};
};

inline bool operator==(MelodicProfile const mp1, MelodicProfile const mp2){
  return mp1.pitch() == mp2.pitch() && mp1.variation() == mp2.variation();
}

}