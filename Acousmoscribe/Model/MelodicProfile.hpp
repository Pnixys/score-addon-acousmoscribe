#include <iostream>

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
    MelodicProfile(Pitch pitch, Variation var);
    ~MelodicProfile();
    void setPitch(Pitch pitch) noexcept;
    void setVariation(Variation variation) noexcept;

private:
    Pitch m_pitch;
    Variation m_var;
};
