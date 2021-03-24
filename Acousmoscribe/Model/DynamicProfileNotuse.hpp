#include <iostream>

#include <verdigris>

namespace Acousmoscribe{
    
enum Dyn
{
    flat = 0,
    short_attack,
    short_truncated,
    soft,
    supp
};


class DynamicProfile{
public:
    DynamicProfile(Dyn d);
    ~DynamicProfile();

    void setDynamic(Dyn dyn);
private:
    Dyn m_dyn;
};

}