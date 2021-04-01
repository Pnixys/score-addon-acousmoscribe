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
    SpectralKeyData(Nature nature, bool isHybrid, bool isRich, bool isRich2);

    Nature getNature();
    bool isHybrid();
    bool isRich();
    bool isRich2();

    void setNature(Nature nature);
    void setHybrid(bool h);
    void setRich(bool r);
    void setRich2(bool r);

    Nature m_nature;
    Nature m_nature2;
    bool m_isHybrid{false};
    bool m_isRich{false};
    bool m_isRich2{false};
}; 

class SpectralKey final : public IdentifiedObject<SpectralKey>{

public:
    SpectralKey(const Id<SpectralKey>& id, QObject* parent);
    SpectralKey(const Id<SpectralKey>& id, SpectralKeyData n, QObject* parent);

   /*  SpectralKey(Nature nature, bool isHybrid, bool isRich);
    ~SpectralKey(); */

    Nature getNature() const noexcept;
    Nature getNature2() const noexcept;
    bool isHybrid() const noexcept;
    bool isRich() const noexcept;
    bool isRich2() const noexcept;

    void setNature(Nature nature);
    void setNature2(Nature nature2);
    void setIsHybrid(bool isHybrid);
    void setIsRich(bool isRich);
    void setIsRich2(bool isRich);
private:
    Nature m_nature;
    Nature m_nature2;
    bool m_isHybrid{false};
    bool m_isRich{false};
    bool m_isRich2{false};
};

}