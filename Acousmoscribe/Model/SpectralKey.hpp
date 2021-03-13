#pragma once
#include <score/model/IdentifiedObject.hpp>
#include <score/selection/Selectable.hpp>

#include <verdigris>


enum Nature
{
    none = 0,
    tonic,
    inharmonic,
    noise
};

class SpectralKey final : public IdentifiedObject<SpectralKey>{

public:
    SpectralKey(Nature nature, bool isHybrid, bool isRich);
    ~SpectralKey();

    Nature nature() const noexcept { return m_nature; }
    Nature nature2() const noexcept { return m_nature2; }
    bool isHybrid() const noexcept {return m_isHybrid; }
    bool isRich() const noexcept {return m_isRich; }

    void setNature(Nature nature);
    void setNature2(Nature nature2);
    void setIsHybrid(bool isHybrid);
    void setIsRich(bool isRich);
private:
    Nature m_nature;
    Nature m_nature2;
    bool m_isHybrid{false};
    bool m_isRich;
};

#endif