add_library(lab9_lib
        adapters/console_adapter.cpp
        config/config_loader.cpp
        backend/graph_gen.cpp
)

target_include_directories(lab9_lib
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(lab9_lib PRIVATE ${PROJECT_COMPILE_OPTIONS})
target_link_options(lab9_lib PRIVATE ${PROJECT_LINK_OPTIONS})

target_compile_definitions(lab9_lib PRIVATE
        RESOURCES_PATH="${CMAKE_SOURCE_DIR}/resources"
)