#include "DynamicProfile.hpp"

#include <wobjectimpl.h>

//W_OBJECT_IMPL(Acousmoscribe::DynamicProfile)

namespace Acousmoscribe {

DynamicProfile::DynamicProfile(Dyn d) : m_dyn(d) {};

void DynamicProfile::setDynamic(Dyn dyn){
    m_dyn = dyn;
}

DynamicProfile::~DynamicProfile(){}

}