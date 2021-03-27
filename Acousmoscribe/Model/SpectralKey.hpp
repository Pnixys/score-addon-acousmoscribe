#pragma once
#include <score/model/IdentifiedObject.hpp>
#include <score/selection/Selectable.hpp>

#include <verdigris>

namespace Acousmoscribe {

enum Nature
{
    null = 0,
    tonic,
    inharmonic,
    noise
};


 struct SpectralKeyData
{
    SpectralKeyData() = default;
    SpectralKeyData(Nature nature, bool isHybrid, bool isRich)
        : m_nature(nature), m_isHybrid(isHybrid), m_isRich(isRich)
        {
            if(m_isRich)
                m_nature2 = nature;
            else
                m_nature2 = null;
        }

    Nature getNature() { return m_nature; }
    bool isHybrid() { return m_isHybrid; }
    bool isRich() { return m_isRich; }

    void changeNature(Nature nature) {
        m_nature = nature;
        if(m_isRich)
            m_nature2 = nature;
    }

    void changeHybrid(bool h) { m_isHybrid = h;}
    void changeRich(bool r) {m_isRich = r;}

    Nature m_nature;
    Nature m_nature2;
    bool m_isHybrid{false};
    bool m_isRich{false};
}; 

class SpectralKey final : public IdentifiedObject<SpectralKey>{

public:
    SpectralKey(const Id<SpectralKey>& id, QObject* parent);
    SpectralKey(const Id<SpectralKey>& id, SpectralKeyData n, QObject* parent);

   /*  SpectralKey(Nature nature, bool isHybrid, bool isRich);
    ~SpectralKey(); */

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
    bool m_isRich{false};
};

}