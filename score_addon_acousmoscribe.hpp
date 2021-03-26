#pragma once
#include <score/application/ApplicationContext.hpp>
#include <score/command/Command.hpp>
#include <score/command/CommandGeneratorMap.hpp>
#include <score/plugins/InterfaceList.hpp>
#include <score/plugins/qt_interfaces/CommandFactory_QtInterface.hpp>
#include <score/plugins/qt_interfaces/FactoryFamily_QtInterface.hpp>
#include <score/plugins/qt_interfaces/FactoryInterface_QtInterface.hpp>
#include <score/plugins/qt_interfaces/GUIApplicationPlugin_QtInterface.hpp>
#include <score/plugins/qt_interfaces/PluginRequirements_QtInterface.hpp>


#include <utility>
#include <vector>

class score_addon_acousmoscribe final : public score::Plugin_QtInterface,
                                   public score::FactoryInterface_QtInterface,
                                   public score::CommandFactory_QtInterface
{
  SCORE_PLUGIN_METADATA(1, "35f91fde-f536-4b9b-a579-89e3dd3231e6")

public:
  score_addon_acousmoscribe();
  ~score_addon_acousmoscribe() override;

private:
  std::vector<std::unique_ptr<score::InterfaceBase>> factories(
      const score::ApplicationContext& ctx,
      const score::InterfaceKey& key) const override;

  std::pair<const CommandGroupKey, CommandGeneratorMap>
  make_commands() override;
};
