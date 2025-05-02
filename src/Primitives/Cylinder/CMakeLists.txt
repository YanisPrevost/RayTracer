add_library(cylinder SHARED
    Cylinder.cpp
    ${CMAKE_SOURCE_DIR}/src/Vectors/Vector.cpp
    ${CMAKE_SOURCE_DIR}/src/Points/Points.cpp
    ${CMAKE_SOURCE_DIR}/src/Parsing/ArgumentMap.cpp
)
target_include_directories(cylinder PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(cylinder PROPERTIES OUTPUT_NAME "Cylinder")
set_target_properties(cylinder PROPERTIES PREFIX "Primitives/lib")