#include "LocalTree.hpp"

#include <LocalTree/Property.hpp>
#include <Acousmoscribe/Model/Process.hpp>

namespace Acousmoscribe
{
LocalTreeProcessComponent::LocalTreeProcessComponent(
    const Id<score::Component>& id, ossia::net::node_base& parent,
    Acousmoscribe::Model& proc, const score::DocumentContext& sys, QObject* parent_obj)
    : LocalTree::ProcessComponent_T<Acousmoscribe::Model>{
          parent, proc, sys, id, "AcousmoscribeComponent", parent_obj}
{
}

LocalTreeProcessComponent::~LocalTreeProcessComponent()
{
}
}
