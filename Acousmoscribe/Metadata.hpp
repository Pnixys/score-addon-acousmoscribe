#pragma once
#include <Process/ProcessMetadata.hpp>

namespace Acousmoscribe
{
class Model;
}

PROCESS_METADATA(
    , Acousmoscribe::Model, "35f91fde-f536-4b9b-a579-89e3dd3231e6",
    "Acousmoscribe",                                   // Internal name
    "Acousmoscribe",                                   // Pretty name
    Process::ProcessCategory::Other,              // Category
    "Acousmoscribe",                                      // Category
    "Système de notation Acousmoscribe",                                // Description
    "Elodie Gaudry, Loïc Lachiver, Thomas Heurtel, Antoine Deynoux, Julien Daugaron",                                     // Author
    (QStringList{"Acousmoscribe", "Notation", "Di-Santo", "Narbel"}), // Tags
    {},                                           // Inputs
    {},                                           // Outputs
    Process::ProcessFlags::SupportsTemporal | Process::ProcessFlags::PutInNewSlot            // Flags
)
