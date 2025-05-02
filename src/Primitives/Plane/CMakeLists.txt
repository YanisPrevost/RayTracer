add_library(plane SHARED
    Plane.cpp
    ${CMAKE_SOURCE_DIR}/src/Vectors/Vector.cpp
    ${CMAKE_SOURCE_DIR}/src/Points/Points.cpp
    ${CMAKE_SOURCE_DIR}/src/Parsing/ArgumentMap.cpp
)
target_include_directories(plane PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(plane PROPERTIES OUTPUT_NAME "Plane")
set_target_properties(plane PROPERTIES PREFIX "Primitives/lib")