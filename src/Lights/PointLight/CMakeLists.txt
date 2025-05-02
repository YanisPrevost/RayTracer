add_library(pointLight SHARED
    PointLight.cpp
    ${CMAKE_SOURCE_DIR}/src/Lights/ALights.cpp
    ${CMAKE_SOURCE_DIR}/src/Vectors/Vector.cpp
    ${CMAKE_SOURCE_DIR}/src/Points/Points.cpp
    ${CMAKE_SOURCE_DIR}/src/Ray/Ray.cpp
    ${CMAKE_SOURCE_DIR}/src/Builder/RayTracer.cpp
    ${CMAKE_SOURCE_DIR}/src/Parsing/ArgumentMap.cpp
)
target_include_directories(pointLight PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(pointLight PROPERTIES OUTPUT_NAME "PointLight")
set_target_properties(pointLight PROPERTIES PREFIX "Lights/lib")