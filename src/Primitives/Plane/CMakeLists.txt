add_library(plane SHARED Plane.cpp)
target_include_directories(plane PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(plane PROPERTIES OUTPUT_NAME "Plane")