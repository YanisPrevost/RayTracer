add_library(cone SHARED
    Cone.cpp
    ${CMAKE_SOURCE_DIR}/src/Vectors/Vector.cpp
    ${CMAKE_SOURCE_DIR}/src/Points/Points.cpp
    ${CMAKE_SOURCE_DIR}/src/Parsing/ArgumentMap.cpp
)
target_include_directories(cone PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(cone PROPERTIES OUTPUT_NAME "Cone")
set_target_properties(cone PROPERTIES PREFIX "Primitives/lib")