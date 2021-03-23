#include <iostream>

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

    void setDynamic(Dyn dyn) noexcept;
private:
    Dyn m_dyn;
};
