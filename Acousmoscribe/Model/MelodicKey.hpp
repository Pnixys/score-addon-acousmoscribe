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

    Pitch getPitch() noexcept;
    Range getRange() noexcept;

    void setPitch(Pitch pitch) noexcept;
    void setRange(Range range) noexcept;
    

private:
    Pitch m_pitch{};
    Range m_range{};
};
}