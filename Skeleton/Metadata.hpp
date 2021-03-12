#pragma once
#include <Process/ProcessMetadata.hpp>

namespace Skeleton
{
class Model;
}

PROCESS_METADATA(
    , Skeleton::Model, "00000000-0000-0000-0000-000000000000",
    "Acousmoscribe",                                   // Internal name
    "Acousmoscribe",                                   // Pretty name
    Process::ProcessCategory::Other,              // Category
    "Other",                                      // Category
    "Description",                                // Description
    "Daugaron,
     Deynoux,
     Gaudry,
     Heurtel,
     Larchiver",                                     // Author
    (QStringList{"Put", "Your", "Tags", "Here"}), // Tags
    {},                                           // Inputs
    {},                                           // Outputs
    Process::ProcessFlags::SupportsAll            // Flags
)
