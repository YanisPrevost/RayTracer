add_library(boundingbox SHARED
    BoundingBox.cpp
    ${CMAKE_SOURCE_DIR}/src/Vectors/Vector.cpp
    ${CMAKE_SOURCE_DIR}/src/Points/Points.cpp
    ${CMAKE_SOURCE_DIR}/src/Parsing/ArgumentMap.cpp
)
target_include_directories(boundingbox PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(boundingbox PROPERTIES OUTPUT_NAME "BoundingBox")
set_target_properties(boundingbox PROPERTIES PREFIX "Primitives/lib")