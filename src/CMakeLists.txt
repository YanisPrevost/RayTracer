
include_directories(${CMAKE_SOURCE_DIR}/src/
${CMAKE_SOURCE_DIR}/src/Vectors/
${CMAKE_SOURCE_DIR}/src/Points/
${CMAKE_SOURCE_DIR}/src/Interfaces/)

file(GLOB_RECURSE RAYTRACER_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.hpp
)


list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Plane/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Sphere/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Lights/.*")


find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIGPP REQUIRED libconfig++)
include_directories(${LIBCONFIGPP_INCLUDE_DIRS})

set(SFML_DIR "/usr/lib64/")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(raytracer ${RAYTRACER_SOURCES})

target_link_libraries(raytracer
    ${LIBCONFIGPP_LIBRARIES}
    sfml-graphics
    sfml-window
    sfml-system
)

target_link_libraries(raytracer ${LIBCONFIGPP_LIBRARIES})

add_subdirectory(Primitives/Plane)
add_subdirectory(Primitives/Sphere)
add_subdirectory(Lights/PointLight)
add_subdirectory(Lights/DirectionalLight)
