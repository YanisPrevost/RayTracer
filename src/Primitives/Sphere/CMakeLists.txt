add_library(sphere SHARED Sphere.cpp)
target_include_directories(sphere PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(sphere PROPERTIES OUTPUT_NAME "sphere")
