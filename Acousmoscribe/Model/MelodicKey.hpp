#include <iostream>
#include "MelodicProfile.hpp"

enum Range{
    weak = 0,
    medium,
    strong
};

class MelodicKey
{

public:
    MelodicKey(Pitch pitch, Range range);
    ~MelodicKey();

    Pitch pitch() const noexcept { return m_pitch; }
    Range range() const noexcept { return m_range; }

    void setPitch(Pitch pitch) noexcept;
    void setRange(Range range) noexcept;

private:
    Pitch m_pitch;
    Range m_range;
};