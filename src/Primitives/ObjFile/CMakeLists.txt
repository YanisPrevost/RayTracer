add_library(objfile SHARED
    ObjFile.cpp
    ${CMAKE_SOURCE_DIR}/src/Vectors/Vector.cpp
    ${CMAKE_SOURCE_DIR}/src/Points/Points.cpp
    ${CMAKE_SOURCE_DIR}/src/Parsing/ArgumentMap.cpp
    ${CMAKE_SOURCE_DIR}/src/DynamicLibrary/DynamicLibrary.cpp
    ${CMAKE_SOURCE_DIR}/src/BVHBuilder/BinaryTree.cpp
    ${CMAKE_SOURCE_DIR}/src/BVHBuilder/AABB.cpp
)
target_include_directories(objfile PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(objfile PROPERTIES OUTPUT_NAME "ObjFile")
set_target_properties(objfile PROPERTIES PREFIX "Primitives/lib")
