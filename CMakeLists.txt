project(score_addon_acousmoscribe LANGUAGES CXX)

# General initialization
score_common_setup()

# Source files
set(HDRS
    Acousmoscribe/Executor.hpp
    Acousmoscribe/Inspector/Inspector.hpp
    Acousmoscribe/LocalTree.hpp
    Acousmoscribe/Metadata.hpp
    Acousmoscribe/Presenter.hpp
    Acousmoscribe/Process.hpp
    Acousmoscribe/View.hpp
    Acousmoscribe/Layer.hpp
    Acousmoscribe/CommandFactory.hpp

    score_addon_acousmoscribe.hpp
)
set(SRCS
    Acousmoscribe/Executor.cpp
    Acousmoscribe/Inspector/Inspector.cpp
    Acousmoscribe/LocalTree.cpp
    Acousmoscribe/Presenter.cpp
    Acousmoscribe/Process.cpp
    Acousmoscribe/View.cpp

    score_addon_acousmoscribe.cpp
)


# Creation of the library
add_library(${PROJECT_NAME} ${SRCS} ${HDRS})

# Code generation
score_generate_command_list_file(${PROJECT_NAME} "${HDRS}")

# Link
target_link_libraries(${PROJECT_NAME} PUBLIC score_plugin_engine)

# Target-specific options
setup_score_plugin(${PROJECT_NAME})
