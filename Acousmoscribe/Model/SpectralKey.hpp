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
    noise
};


 struct SpectralKeyData
{
    SpectralKeyData() = default;
    SpectralKeyData(Nature nature, bool isHybrid, bool isRich, bool isRich2);

    Nature getNature() const;
    Nature getNature2() const;
    bool isHybrid() const;
    bool isRich() const;
    bool isRich2() const;

    void setNature(Nature nature);
    void setNature2(Nature nature);
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

    Nature getNature() const noexcept;  
    Nature getNature2() const noexcept;
    bool isHybrid() const noexcept;
    bool isRich() const noexcept;
    bool isRich2() const noexcept;

    SpectralKeyData spectralKeyData() const;

    void setNature(Nature nature);
    void setNature2(Nature nature2);
    void setIsHybrid(bool isHybrid);
    void setIsRich(bool isRich);
    void setIsRich2(bool isRich);

    void setData(SpectralKeyData sd);

    void spectralKeyChanged() W_SIGNAL(spectralKeyChanged);
private:
    Nature m_nature;
    Nature m_nature2;
    bool m_isHybrid{false};
    bool m_isRich{false};
    bool m_isRich2{false};
};

}