#include "score_addon_acousmoscribe.hpp"

#include <score/plugins/FactorySetup.hpp>

#include <Acousmoscribe/Commands/CommandFactory.hpp>
#include <Acousmoscribe/Executor.hpp>
#include <Acousmoscribe/Inspector/Inspector.hpp>
#include <Acousmoscribe/Layer.hpp>
#include <Acousmoscribe/LocalTree.hpp>
#include <Acousmoscribe/Model/Process.hpp>
#include <score_addon_acousmoscribe_commands_files.hpp>

score_addon_acousmoscribe::score_addon_acousmoscribe()
{
}

score_addon_acousmoscribe::~score_addon_acousmoscribe()
{
}

std::vector<std::unique_ptr<score::InterfaceBase>>
score_addon_acousmoscribe::factories(
    const score::ApplicationContext& ctx, const score::InterfaceKey& key) const
{
  return instantiate_factories<
      score::ApplicationContext,
      FW<Process::ProcessModelFactory, Acousmoscribe::ProcessFactory>,
      FW<Process::LayerFactory, Acousmoscribe::LayerFactory>,
      FW<Process::InspectorWidgetDelegateFactory, Acousmoscribe::InspectorFactory>,
      FW<Execution::ProcessComponentFactory,
         Acousmoscribe::ProcessExecutorComponentFactory>,
      FW<LocalTree::ProcessComponentFactory,
         Acousmoscribe::LocalTreeProcessComponentFactory>>(ctx, key);
}

std::pair<const CommandGroupKey, CommandGeneratorMap>
score_addon_acousmoscribe::make_commands()
{
  using namespace Acousmoscribe;
  std::pair<const CommandGroupKey, CommandGeneratorMap> cmds{
      CommandFactoryName(), CommandGeneratorMap{}};

  ossia::for_each_type<
#include <score_addon_acousmoscribe_commands.hpp>
      >(score::commands::FactoryInserter{cmds.second});

  return cmds;
}

#include <score/plugins/PluginInstances.hpp>
SCORE_EXPORT_PLUGIN(score_addon_acousmoscribe)
