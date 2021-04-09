project(score_addon_acousmoscribe LANGUAGES CXX)

# General initialization
score_common_setup()

# Source files
set(HDRS
    Acousmoscribe/Executor.hpp
    Acousmoscribe/Inspector/Inspector.hpp
    Acousmoscribe/LocalTree.hpp
    Acousmoscribe/Metadata.hpp
    Acousmoscribe/Presenter/Presenter.hpp
    Acousmoscribe/Layer.hpp

    #View
    Acousmoscribe/View/View.hpp
    Acousmoscribe/View/SpectralKeyView.hpp
    Acousmoscribe/View/MelodicKeyView.hpp
    Acousmoscribe/View/SignView.hpp
    
    #Commands
    Acousmoscribe/Commands/CommandFactory.hpp
    Acousmoscribe/Commands/AddKey.hpp
    Acousmoscribe/Commands/ChangeMelodicKey.hpp
    Acousmoscribe/Commands/ChangeSpectralKey.hpp
    Acousmoscribe/Commands/AddSign.hpp
    Acousmoscribe/Commands/ChangeSign.hpp
    Acousmoscribe/Commands/MoveSigns.hpp
    Acousmoscribe/Commands/RemoveSigns.hpp
    Acousmoscribe/Commands/ScaleSigns.hpp

    #Model
    Acousmoscribe/Model/Process.hpp
    Acousmoscribe/Model/Grain.hpp
    Acousmoscribe/Model/MelodicProfile.hpp
    Acousmoscribe/Model/MelodicKey.hpp
    Acousmoscribe/Model/RhythmicProfile.hpp
    Acousmoscribe/Model/SpectralKey.hpp
    Acousmoscribe/Model/Sign.hpp

    score_addon_acousmoscribe.hpp
)
set(SRCS
    Acousmoscribe/Executor.cpp
    Acousmoscribe/Inspector/Inspector.cpp
    Acousmoscribe/LocalTree.cpp
    Acousmoscribe/Presenter/Presenter.cpp
    
    #View
    Acousmoscribe/View/View.cpp
    Acousmoscribe/View/SpectralKeyView.cpp
    Acousmoscribe/View/MelodicKeyView.cpp
    Acousmoscribe/View/SignView.cpp
    
    #Commands
    Acousmoscribe/Commands/AddKey.cpp
    Acousmoscribe/Commands/ChangeMelodicKey.cpp
    Acousmoscribe/Commands/ChangeSpectralKey.cpp
    Acousmoscribe/Commands/AddSign.cpp
    Acousmoscribe/Commands/ChangeSign.cpp
    Acousmoscribe/Commands/MoveSigns.cpp
    Acousmoscribe/Commands/RemoveSigns.cpp
    Acousmoscribe/Commands/ScaleSigns.cpp

    #Model
    Acousmoscribe/Model/Process.cpp
    Acousmoscribe/Model/MelodicProfile.cpp
    Acousmoscribe/Model/MelodicKey.cpp
    Acousmoscribe/Model/RhythmicProfile.cpp
    Acousmoscribe/Model/SpectralKey.cpp
    Acousmoscribe/Model/Sign.cpp
    
    score_addon_acousmoscribe.cpp
)



find_package(Catch2 REQUIRED)

# Creation of the library
add_library(${PROJECT_NAME} ${SRCS} ${HDRS})
add_subdirectory(${OSSIA_3RDPARTY_FOLDER}/Catch2 catch2)
add_executable(testModel Acousmoscribe/testModel/testModel.cpp)

# Code generation
score_generate_command_list_file(${PROJECT_NAME} "${HDRS}")

# Link
target_compile_options(testModel PUBLIC -std=c++17)
target_link_libraries(${PROJECT_NAME} PUBLIC score_plugin_engine)

target_link_libraries(testModel PRIVATE score_addon_acousmoscribe Catch2::Catch2WithMain)

add_test(NAME testModel COMMAND testModel)

include(CTest)
include(Catch)
# Target-specific options
setup_score_plugin(${PROJECT_NAME})
