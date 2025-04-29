add_library(sphere SHARED
    Sphere.cpp
    ${CMAKE_SOURCE_DIR}/src/Vectors/Vector.cpp
    ${CMAKE_SOURCE_DIR}/src/Points/Points.cpp
)
target_include_directories(sphere PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(sphere PROPERTIES OUTPUT_NAME "Sphere")
