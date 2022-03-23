add_library(libreader STATIC)

target_sources(libreader
PRIVATE
    "VolumeData.cpp"
)

set_target_properties(libreader
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_link_libraries(libreader PRIVATE tomlplusplus)
target_include_directories(libreader PUBLIC "./")
