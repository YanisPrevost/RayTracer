add_library(triangle SHARED
    Triangle.cpp
    ${CMAKE_SOURCE_DIR}/src/Vectors/Vector.cpp
    ${CMAKE_SOURCE_DIR}/src/Points/Points.cpp
    ${CMAKE_SOURCE_DIR}/src/Parsing/ArgumentMap.cpp
)
target_include_directories(triangle PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(triangle PROPERTIES OUTPUT_NAME "Triangle")
set_target_properties(triangle PROPERTIES PREFIX "Primitives/lib")
