#pragma once
#include <score/model/IdentifiedObject.hpp>
#include <score/selection/Selectable.hpp>

#include <verdigris>
#include <iostream>

#include "Grain.hpp"
//#include "DynamicProfile.hpp"
#include "MelodicProfile.hpp"
#include "RhythmicProfile.hpp"


namespace Model
{
    
//Dynamic Profile :
typedef struct{
    double attack; //attack duration
    double release; //release duration
    float volumeStart;
    float volumeEnd;
}DynamicProfile;

struct SignData
{
SignData() = default;
SignData(double s, double d, Grain g, DynamicProfile dp, MelodicProfile mp, RhythmicProfile rp)
    : m_start{s}, m_duration{d}, m_grain{g}, m_dynamicProfile{dp}, m_melodicProfile{mp}, m_rhythmicProfile{rp}
{
}
    double start() const { return m_start; }
    double duration() const { return m_duration; }
    double end() const { return m_start + m_duration; }

    DynamicProfile dynamicProfile() { return m_dynamicProfile; }
    MelodicProfile melodicProfile() { return m_melodicProfile; }
    RhythmicProfile rythmicProfile() { return m_rhythmicProfile; }
    Grain grain() { return m_grain; }

    void setStart(double s) noexcept { m_start = s; }
    void setDuration(double s) noexcept { m_duration = s; }

    void setDynamicProfile(DynamicProfile dp) {m_dynamicProfile = dp; }
    void setMelodicProfile(MelodicProfile mp) {m_melodicProfile = mp; }
    void setRhythmicProfile(RhythmicProfile rp) {m_rhythmicProfile = rp; }
    void setGrain(Grain g) {m_grain = g; }

    double m_start{};
    double m_duration{};

    Grain m_grain;
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

    double start() const noexcept { return m_start; }

    double duration() const noexcept { return m_duration; }

    double end() const noexcept { return m_start + m_duration; }

    DynamicProfile dynamicProfile() const;

    MelodicProfile melodicProfile() const;

    RhythmicProfile rythmicProfile() const;

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
    Grain _grain;
    DynamicProfile _dynamicProfile;
    MelodicProfile _melodicProfile;
    RhythmicProfile _rhythmicProfile;
};

}