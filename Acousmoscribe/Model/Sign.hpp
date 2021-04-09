#pragma once
#include <score/model/IdentifiedObject.hpp>
#include <score/selection/Selectable.hpp>

#include <verdigris>
#include <iostream>

#include "Grain.hpp"
//#include "DynamicProfile.hpp"
#include "MelodicProfile.hpp"
#include "RhythmicProfile.hpp"


namespace Acousmoscribe
{
    
//Dynamic Profile :
typedef struct{
    float volumeStart{1};
    float volumeEnd{1};
}DynamicProfile;

struct SignData
{
    SignData() = default;
    SignData(double s, double d, Grain g, DynamicProfile dp, MelodicProfile mp, RhythmicProfile rp);
    double start() const;
    double duration() const;
    double end() const;

    DynamicProfile dynamicProfile() const;
    MelodicProfile melodicProfile() const;
    RhythmicProfile rhythmicProfile() const;
    Grain grain() const;

    void setStart(double s) noexcept;
    void setDuration(double s) noexcept;

    void setDynamicProfile(DynamicProfile dp);
    void setMelodicProfile(MelodicProfile mp);
    void setRhythmicProfile(RhythmicProfile rp);
    void setGrain(Grain g);

    double m_start{};
    double m_duration{};

    Grain m_grain{smooth};
    DynamicProfile m_dynamicProfile;
    MelodicProfile m_melodicProfile;
    RhythmicProfile m_rhythmicProfile;
};

class Sign final : public IdentifiedObject<Sign>
{
    W_OBJECT(Sign)
    SCORE_SERIALIZE_FRIENDS

public:
    Selectable selection;

    Sign(const Id<Sign>& id, QObject* parent);
    Sign(const Id<Sign>& id, SignData s, QObject* parent);

    template <typename DeserializerVisitor, enable_if_deserializer<DeserializerVisitor>* = nullptr>
    Sign(DeserializerVisitor&& vis, QObject* parent) : IdentifiedObject<Sign>{vis, parent}
    {
        vis.writeTo(*this);
    }

    double start() const noexcept;

    double duration() const noexcept;

    double end() const noexcept;

    DynamicProfile dynamicProfile() const;

    MelodicProfile melodicProfile() const;

    RhythmicProfile rhythmicProfile() const;

    Grain grain() const;

    SignData signData() const;

    void scale(double s) noexcept;

    void setStart(double s) noexcept;

    void setDuration(double s) noexcept;

    void setDynamicProfile(DynamicProfile d);

    void setMelodicProfile(MelodicProfile d);

    void setRhythmicProfile(RhythmicProfile d);

    void setGrain(Grain g);

    void setData(SignData d);

public:
    void signChanged() W_SIGNAL(signChanged);


private:
    double m_start{};
    double m_duration{};
    Grain _grain{smooth};
    DynamicProfile _dynamicProfile;
    MelodicProfile _melodicProfile;
    RhythmicProfile _rhythmicProfile;
};

}