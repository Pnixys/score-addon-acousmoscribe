#include <catch2/catch_all.hpp>
#include <catch2/catch_test_macros.hpp>

#include "testModel.hpp"

/* #include "../Model/Sign.hpp"
#include "../Model/MelodicKey.hpp"
#include "../Model/SpectralKey.hpp" */
#include <score/command/Dispatchers/CommandDispatcher.hpp>

#include <Acousmoscribe/Model/Sign.hpp>
#include <Acousmoscribe/Model/Grain.hpp>
#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Acousmoscribe/Model/SpectralKey.hpp>
#include <Acousmoscribe/Model/RhythmicProfile.hpp>
#include <Acousmoscribe/Model/MelodicProfile.hpp>


/* Commands */
#include <Acousmoscribe/Commands/AddKey.hpp>
#include <Acousmoscribe/Commands/AddSign.hpp>
#include <Acousmoscribe/Commands/RemoveSigns.hpp>
#include <Acousmoscribe/Commands/ScaleSigns.hpp>

#include <Acousmoscribe/View/View.hpp>
#include <Acousmoscribe/View/SignView.hpp>
#include <Acousmoscribe/View/SpectralKeyView.hpp>
#include <Acousmoscribe/View/MelodicKeyView.hpp>

#include <QPainter>
#include <QPainterPath>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>

using namespace Acousmoscribe;

class TestModel : public QObject
{
    Q_OBJECT
public:
    TestModel() : QObject{} { }
    ~TestModel(){};

public:
    Model model = Model(std::chrono::seconds(15), Id<Process::ProcessModel>{0}, this);
};


/*TEST_CASE ("Test of test", "[Test 1]")
{
    Grain g = smooth;
    DynamicProfile d;
    d.attack = 10.;
    d.release = 5.;
    d.volumeEnd = 1;
    d.volumeStart = 0.5;
    MelodicProfile mp = MelodicProfile(mid,none);
    RhythmicProfile rp = RhythmicProfile();

    SignData c = SignData(10,10,g,d,mp,rp); 


    Sign sign = Sign();
    sign.setData(c);
    REQUIRE(sign.duration() == 10);
}*/

SCENARIO ("Creation of equal Sign and change on second", "[Sign][Creation][Modifiaction]")
{
    GIVEN("Creation of two equal sign") 
    {
        /**
         * First time we create a sign data
         **/
        Grain g = smooth;
        DynamicProfile d;
        d.volumeEnd = 1;
        d.volumeStart = 0.5;
        MelodicProfile mp = MelodicProfile(mid,mid,none);
        RhythmicProfile rp = RhythmicProfile();

        SignData initSignData = SignData(10,10,g,d,mp,rp); 

        /**
         * Model Inititalisation
         **/
        TestModel* m_model;

        QObject q = QObject(0);
        Id<Sign> id = Id<Sign>();
        
        /**
         * Creation of sign
         **/
        Sign sign1 = Sign(id,initSignData,&q);
        Sign sign2 = Sign(id,initSignData,&q);

        THEN("No modification sign are equal")
        {
            REQUIRE(sign1.duration() == sign2.duration());
            REQUIRE(sign1.start() == sign2.start());
            REQUIRE(sign1.grain() == sign2.grain());
            REQUIRE(sign1.dynamicProfile() == sign2.dynamicProfile());
            REQUIRE(sign1.melodicProfile() == sign2.melodicProfile());
            REQUIRE(sign1.rhythmicProfile() == sign2.rhythmicProfile());

        }

        WHEN("Change the duration of sign 2")
        {
            sign2.setDuration(15);

            THEN("Test must be false")
            {
                REQUIRE_FALSE(sign1.duration() == sign2.duration());
                REQUIRE(sign1.start() == sign2.start());
                REQUIRE(sign1.grain() == sign2.grain());
                REQUIRE(sign1.dynamicProfile() == sign2.dynamicProfile());
                REQUIRE(sign1.melodicProfile() == sign2.melodicProfile());
                REQUIRE(sign1.rhythmicProfile() == sign2.rhythmicProfile());

            }
        }
    }
}

SCENARIO("Creation of sign, mutiple Modification", "[Sign][Dynamic][Rhythmic][Melodic]")
{
    GIVEN("Creation of Sign")
    {
        Grain g = smooth;
        DynamicProfile d;
        d.volumeEnd = 1;
        d.volumeStart = 0.5;
        MelodicProfile mp = MelodicProfile(mid,mid,none);
        RhythmicProfile rp = RhythmicProfile(continuous, constant, false);

        SignData initSignData = SignData(10,10,g,d,mp,rp); 

        QObject q = QObject(0);
        Id<Sign> id = Id<Sign>();

        Sign signBase = Sign(id,initSignData,&q);
        Sign sign = Sign(id,initSignData,&q);

        THEN("Verification that setData Work correctly")
        {
            REQUIRE(sign.duration() == initSignData.duration());
            REQUIRE(sign.start() == initSignData.start());
            REQUIRE(sign.grain() == initSignData.grain());
            REQUIRE(sign.dynamicProfile() == initSignData.dynamicProfile());
            REQUIRE(sign.melodicProfile() == initSignData.melodicProfile());
            REQUIRE(sign.rhythmicProfile() == initSignData.rhythmicProfile());
        }

        WHEN("change start")
        {
            sign.setStart(5);

            THEN("Now sign must be different of init sign data")
            {
                REQUIRE_FALSE(sign.start() == signBase.start());
                REQUIRE(sign.start() == 5);
            }
        }

        WHEN("change grain")
        {
            sign.setGrain(big);

            THEN("Now sign must be different of init sign data")
            {
                REQUIRE_FALSE(sign.grain() == signBase.grain());
                REQUIRE(sign.grain() == big);
            }
        }

        WHEN("change dynamic profile")
        {
            DynamicProfile newDynProfile;
            newDynProfile.volumeEnd = 0.9;
            newDynProfile.volumeStart = 0.7;

            sign.setDynamicProfile(newDynProfile);

            THEN("sign must be different of init sign data")
            {
                REQUIRE_FALSE(sign.dynamicProfile() ==  signBase.dynamicProfile());
                REQUIRE(sign.dynamicProfile() == newDynProfile);
            }
        }

        WHEN("change melodic profile")
        {
            MelodicProfile mp = MelodicProfile(high,high,random_variation);

            sign.setMelodicProfile(mp);

            THEN("sign must be different of init sign data")
            {
                REQUIRE_FALSE(sign.melodicProfile() == signBase.melodicProfile());
                REQUIRE(sign.melodicProfile() == mp);
            }

        }

        WHEN("change rhythmic profile")
        {
            RhythmicProfile rp = RhythmicProfile(slow, accelerating, true);

            sign.setRhythmicProfile(rp);

            THEN("sign must be different of init sign data")
            {
                REQUIRE_FALSE(sign.rhythmicProfile() == signBase.rhythmicProfile());
                REQUIRE(sign.rhythmicProfile() == rp);
            }
        }
    }
}

SCENARIO("Creation of Spectral Key", "[SpectralKey]")
{
    GIVEN("Creation of Spectral Key")
    {
        /**
         * Creation of Spectral Key Data 
         **/

        SpectralKeyData initSpectralKeyData = SpectralKeyData(tonic,tonic,false,false,false,false,false,false); 

        /**
         * Model Inititalisation
         **/
        TestModel* m_model;

        QObject q = QObject(0);
        Id<SpectralKey> id = Id<SpectralKey>();
        
        /**
         * Creation of Spectral Key
         **/
        SpectralKey sp1 = SpectralKey(id,initSpectralKeyData,&q);
        SpectralKey sp2 = SpectralKey(id,initSpectralKeyData,&q);

        WHEN("Check if the 2 spectral key are equal")
        {
            THEN("Check")
            {
                REQUIRE(sp1.nature() == sp2.nature());
                REQUIRE(sp1.nature2() == sp2.nature2());
                REQUIRE(sp1.isHybrid() == sp2.isHybrid());
                REQUIRE(sp1.isHybrid2() == sp2.isHybrid2());
                REQUIRE(sp1.isRich() == sp2.isRich());
                REQUIRE(sp1.isRich2() == sp2.isRich2());
                REQUIRE(sp1.isWarped() == sp2.isWarped());
                REQUIRE(sp1.isWarped2() == sp2.isWarped2());
            }
        }
        WHEN("Change First Nature")
        {
            sp1.setNature(inharmonic);

            THEN("Test changement")
            {
                REQUIRE(sp1.nature() == inharmonic);
            }

            THEN("Spectral Key Nature 1 must be different")
            {
                REQUIRE_FALSE(sp1.nature() == sp2.nature());
                REQUIRE(sp1.nature2() == sp2.nature2());
                REQUIRE(sp1.isHybrid() == sp2.isHybrid());
                REQUIRE(sp1.isHybrid2() == sp2.isHybrid2());
                REQUIRE(sp1.isRich() == sp2.isRich());
                REQUIRE(sp1.isRich2() == sp2.isRich2());
                REQUIRE(sp1.isWarped() == sp2.isWarped());
                REQUIRE(sp1.isWarped2() == sp2.isWarped2());
            }
        }

        WHEN("Change Second Nature")
        {
            sp1.setNature2(inharmonic);

            THEN("Spectral Key Nature 2 must be different")
            {
                REQUIRE(sp1.nature() == sp2.nature());
                REQUIRE_FALSE(sp1.nature2() == sp2.nature2());
                REQUIRE(sp1.isHybrid() == sp2.isHybrid());
                REQUIRE(sp1.isHybrid2() == sp2.isHybrid2());
                REQUIRE(sp1.isRich() == sp2.isRich());
                REQUIRE(sp1.isRich2() == sp2.isRich2());
                REQUIRE(sp1.isWarped() == sp2.isWarped());
                REQUIRE(sp1.isWarped2() == sp2.isWarped2());
            }
        }

        
    }
}

SCENARIO("Test on Melodic Key", "[MelodicKey]")
{
    GIVEN("Creation of Melodic Key")
    {
        TestModel* m_model;

        MelodicKeyData mkd = MelodicKeyData(mid, normal);

        QObject q = QObject(0);
        Id<MelodicKey> id = Id<MelodicKey>();
    
        MelodicKey mp1 = MelodicKey(id,mkd,&q);
        MelodicKey mp2 = MelodicKey(id,mkd,&q);

        WHEN("Check if the 2 Melodic Key are equal")
        {
            THEN("CHECK")
            {
                REQUIRE(mp1.pitch() == mp2.pitch());
                REQUIRE(mp1.range() == mp2.range());
            }
        }

        WHEN("Change melodic key pitch")
        {
            mp1.setPitch(high);

            THEN("Melodic key must be different")
            {
                REQUIRE_FALSE(mp1.pitch() == mp2.pitch());
                REQUIRE(mp1.range() == mp2.range());
            }
        }

        WHEN("Change melodic key range")
        {
            mp1.setRange(strong);

            THEN("Melodic key must be different")
            {
                REQUIRE(mp1.pitch() == mp2.pitch());
                REQUIRE_FALSE(mp1.range() == mp2.range());
            }

        }
    }
}

/* SCENARIO("Test on presenter and command", "[presenter][command]")
{
    MelodicKeyData mkData = {mid,weak};

    TestModel* m_model;

    Process::Context ctx = Process::Context(NULL,NULL,NULL);
    QObject q = QObject(0);

    auto qi = ItemIsFocusable(&q);
    View v = View(&qi);

    Presenter p_pres = Presenter(m_model->model, &v,ctx,&q);

     CommandDispatcher<>{context().context.commandStack}.submit(
        new AddMelodicKey{m_model, mkData}); 

 }*/