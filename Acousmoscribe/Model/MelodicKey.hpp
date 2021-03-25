#include <iostream>
#include "MelodicProfile.hpp"

//#include <verdigris>

namespace Acousmoscribe {

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

    void setPitch(Pitch pitch);
    void setRange(Range range);

private:
    Pitch m_pitch;
    Range m_range;
};
}