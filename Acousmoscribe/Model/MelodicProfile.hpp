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
    MelodicProfile(Pitch pitch, Variation var);
    ~MelodicProfile();
    void setPitch(Pitch pitch);
    void setVariation(Variation variation);

private:
    Pitch m_pitch;
    Variation m_var;
};

}