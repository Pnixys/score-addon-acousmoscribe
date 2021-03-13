#pragma once
#include <score/command/Command.hpp>

namespace Acousmoscribe
{
inline const CommandGroupKey& CommandFactoryName()
{
  static const CommandGroupKey key{"Acousmoscribe"};
  return key;
}
}
