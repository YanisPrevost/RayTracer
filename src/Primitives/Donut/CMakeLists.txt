add_library(donut SHARED
    Donut.cpp
    ${CMAKE_SOURCE_DIR}/src/Vectors/Vector.cpp
    ${CMAKE_SOURCE_DIR}/src/Points/Points.cpp
    ${CMAKE_SOURCE_DIR}/src/Parsing/ArgumentMap.cpp
)
target_include_directories(donut PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(donut PROPERTIES OUTPUT_NAME "Donut")
set_target_properties(donut PROPERTIES PREFIX "Primitives/lib")