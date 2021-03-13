#pragma once
#include <Process/GenericProcessFactory.hpp>

#include <Acousmoscribe/Presenter.hpp>
#include <Acousmoscribe/Process.hpp>
#include <Acousmoscribe/View.hpp>

namespace Acousmoscribe
{
using LayerFactory = Process::LayerFactory_T<
    Acousmoscribe::Model, Acousmoscribe::Presenter, Acousmoscribe::View>;
}
