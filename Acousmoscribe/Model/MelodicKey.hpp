#pragma once
#include <score/model/IdentifiedObject.hpp>

#include <score/selection/Selectable.hpp>

#include <verdigris>
#include <iostream>

#include "MelodicProfile.hpp"

//#include <verdigris>

namespace Acousmoscribe {

enum Range{
    weak = 0,
    normal,
    strong
};
struct MelodicKeyData{
    MelodicKeyData() = default;
    MelodicKeyData(Pitch p, Range r);

    Pitch getPitch() const;
    Range getRange() const;

    void setPitch(Pitch p);
    void setRange(Range r);

    Pitch m_pitch;
    Range m_range;
};

class MelodicKey final : public IdentifiedObject<MelodicKey>
{
    W_OBJECT(MelodicKey)
    SCORE_SERIALIZE_FRIENDS
public:
    Selectable selection;

    MelodicKey(const Id<MelodicKey>& id, QObject* parent);
    MelodicKey(const Id<MelodicKey>& id, MelodicKeyData n, QObject* parent);

    template <typename Impl>
    MelodicKey(Impl& vis, QObject* parent) : IdentifiedObject{vis, parent}
    {
      vis.writeTo(*this);
    }

    //MelodicKey(Pitch pitch, Range range);
    //~MelodicKey();

    Pitch getPitch() noexcept;
    Range getRange() noexcept;

<<<<<<< HEAD
    void setPitch(Pitch pitch) noexcept;
    void setRange(Range range) noexcept;
    
=======
    MelodicKeyData melodicKeyData() const;

    void setPitch(Pitch pitch);
    void setRange(Range range);
>>>>>>> c4a8de7376bbbc754568e2be623fcdd14acfa38e

    void setData(MelodicKeyData mkd);

    void melodicKeyChanged() W_SIGNAL(melodicKeyChanged);
private:
    Pitch m_pitch{};
    Range m_range{};
};
}