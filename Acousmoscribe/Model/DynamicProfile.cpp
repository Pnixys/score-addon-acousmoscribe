#include "DynamicProfile.hpp"

DynamicProfile::DynamicProfile(Dyn d) : m_dyn(d) {};

void DynamicProfile::setDynamic(Dyn dyn){
    m_dyn = dyn;
}

DynamicProfile::~DynamicProfile(){}