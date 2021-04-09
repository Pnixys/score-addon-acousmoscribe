#pragma once
#include <Process/GenericProcessFactory.hpp>

#include <Acousmoscribe/Presenter/Presenter.hpp>
#include <Acousmoscribe/Model/Process.hpp>
#include <Acousmoscribe/View/View.hpp>

namespace Acousmoscribe
{
using LayerFactory = Process::LayerFactory_T<
    Acousmoscribe::Model, Acousmoscribe::Presenter, Acousmoscribe::View>;
}
