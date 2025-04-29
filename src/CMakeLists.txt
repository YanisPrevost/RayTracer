
include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE RAYTRACER_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.hpp
)


list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Plane/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Sphere/.*")


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

# Link libconfig++ to the raytracer executable
target_link_libraries(raytracer ${LIBCONFIGPP_LIBRARIES})

# Add plugin directories
add_subdirectory(Primitives/Plane)
add_subdirectory(Primitives/Sphere)