cmake_minimum_required(VERSION 3.16)

project("Volume Data Reader Example")

add_executable(volume-data-reader-example)

set_target_properties(volume-data-reader-example
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

# Create a header-only library
add_library(tomlplusplus INTERFACE)
target_include_directories(tomlplusplus INTERFACE "externals/tomlplusplus/")

add_subdirectory("src/volume-data-reader/")

target_sources(volume-data-reader-example
PRIVATE
    "src/main.cpp"
)

target_link_libraries(volume-data-reader-example
PRIVATE
    libreader
)

add_custom_command(TARGET volume-data-reader-example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:volume-data-reader-example>/res"
    DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
    COMMENT "Creating symlinks to project resources..."
)
