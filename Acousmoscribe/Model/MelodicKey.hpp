#pragma once
#include <iostream>
#include "MelodicProfile.hpp"

//#include <verdigris>

namespace Acousmoscribe {

enum Range{
    weak = 0,
    normal,
    strong
};

class MelodicKey
{

public:
    MelodicKey(Pitch pitch, Range range);
    ~MelodicKey();

    Pitch getPitch() const noexcept;
    Range getRange() const noexcept;

    void setPitch(Pitch pitch);
    void setRange(Range range);

private:
    Pitch m_pitch;
    Range m_range;
};
}