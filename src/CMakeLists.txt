
include_directories(${CMAKE_SOURCE_DIR}/src/
${CMAKE_SOURCE_DIR}/src/Vectors/
${CMAKE_SOURCE_DIR}/src/Points/
${CMAKE_SOURCE_DIR}/src/Interfaces/
${CMAKE_SOURCE_DIR}/src/Parsing
${CMAKE_SOURCE_DIR}/src/Color)

file(GLOB_RECURSE RAYTRACER_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.hpp
)


list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Plane/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Sphere/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Cone/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Lights/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Cylinder/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Donut/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/PointLight/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/DirectionalLight/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/Triangle/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/ObjFile/.*")
list(FILTER RAYTRACER_SOURCES EXCLUDE REGEX ".*/BoundingBox/.*")


find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIGPP REQUIRED libconfig++)
include_directories(${LIBCONFIGPP_INCLUDE_DIRS})

set(SFML_DIR "/usr/lib64/")
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)


add_executable(raytracer ${RAYTRACER_SOURCES})

target_link_libraries(raytracer
    ${LIBCONFIGPP_LIBRARIES}
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)
add_compile_options(-Wall -Wextra  -Wpedantic)
option(ENABLE_O3 "Compile with -O3 optimization" OFF)

if(ENABLE_O3)
    add_compile_options(-O3)
endif()

# add_compile_options(-pg)

target_link_libraries(raytracer ${LIBCONFIGPP_LIBRARIES})

add_subdirectory(Primitives/Plane)
add_subdirectory(Primitives/Sphere)
add_subdirectory(Primitives/Cone)
add_subdirectory(Primitives/Cylinder)
add_subdirectory(Primitives/Donut)
add_subdirectory(Primitives/Triangle)
add_subdirectory(Primitives/ObjFile)
add_subdirectory(Primitives/BoundingBox)
add_subdirectory(Lights/PointLight)
add_subdirectory(Lights/DirectionalLight)
