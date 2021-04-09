#pragma once
#include <score/model/IdentifiedObject.hpp>

#include <score/selection/Selectable.hpp>

#include <verdigris>
#include <iostream>

namespace Acousmoscribe {

enum Nature
{
    null = 0,
    tonic,
    inharmonic,
    noise,
    tonic_inharmonic,
    noisy_tonic,
    noisy_inharmonic,
};


 struct SpectralKeyData
{
    SpectralKeyData() = default;
    SpectralKeyData(Nature nature, Nature nature2, bool isHybrid, bool isHybrid2, bool isRich, bool isRich2, bool isWarped, bool isWarped2);

    Nature nature() const;
    Nature nature2() const;
    bool isHybrid() const;
    bool isHybrid2() const;
    bool isRich() const;
    bool isRich2() const;
    bool isWarped() const;
    bool isWarped2() const;

    void setNature(Nature nature);
    void setNature2(Nature nature);
    void setIsHybrid(bool h);
    void setIsHybrid2(bool h);
    void setIsRich(bool r);
    void setIsRich2(bool r);
    void setIsWarped(bool w);
    void setIsWarped2(bool w);

    Nature m_nature;
    Nature m_nature2;
    bool m_isWarped{false};
    bool m_isWarped2{false};
    bool m_isHybrid{false};
    bool m_isHybrid2{false};
    bool m_isRich{false};
    bool m_isRich2{false};
}; 

class SpectralKey final : public IdentifiedObject<SpectralKey>{

    W_OBJECT(SpectralKey)
    SCORE_SERIALIZE_FRIENDS

public:
    Selectable selection;

    SpectralKey(const Id<SpectralKey>& id, QObject* parent);
    SpectralKey(const Id<SpectralKey>& id, SpectralKeyData n, QObject* parent);

    /* template <typename DeserializerVisitor, enable_if_deserializer<DeserializerVisitor>* = nullptr>
    SpectralKey(DeserializerVisitor&& vis, QObject* parent) : IdentifiedObject<SpectralKey>{vis, parent}
    {
        vis.writeTo(*this);
    } */

    template <typename Impl>
    SpectralKey(Impl& vis, QObject* parent) : IdentifiedObject{vis, parent}
    {
      vis.writeTo(*this);
    }

    //~SpectralKey(); 

    Nature nature() const noexcept;  
    Nature nature2() const noexcept;
    bool isHybrid() const noexcept;
    bool isHybrid2() const noexcept;
    bool isRich() const noexcept;
    bool isRich2() const noexcept;
    bool isWarped() const noexcept;
    bool isWarped2() const noexcept;

    SpectralKeyData spectralKeyData() const;

    void setNature(Nature nature);
    void setNature2(Nature nature2);
    void setIsHybrid(bool isHybrid);
    void setIsHybrid2(bool isHybrid2);
    void setIsRich(bool isRich);
    void setIsRich2(bool isRich2);
    void setIsWarped(bool isWarped);
    void setIsWarped2(bool isWarped2);

    void setData(SpectralKeyData sd);

    void spectralKeyChanged() W_SIGNAL(spectralKeyChanged);
private:
    Nature m_nature;
    Nature m_nature2;
    bool m_isHybrid{false};
    bool m_isHybrid2{false};
    bool m_isRich{false};
    bool m_isRich2{false};
    bool m_isWarped{false};
    bool m_isWarped2{false};
};

}