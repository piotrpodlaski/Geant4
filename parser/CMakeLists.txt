cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(cadmesh_example)

# GEANT4 core
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# Include CADMesh in your project.
 find_package(cadmesh)
 # include_directories(${CADMESH_INCLUDE_DIRS})



# User code
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh include/*.h include/*.hpp)

add_executable(cadmesh_example cadmesh_example.cpp ${sources} ${headers})
target_link_libraries(cadmesh_example ${Geant4_LIBRARIES})

target_link_libraries(cadmesh_example cadmesh)
target_link_libraries(cadmesh_example ${cadmesh_LIBRARIES})
configure_file(geometry.cfg geometry.cfg COPYONLY)
configure_file(config.xml config.xml COPYONLY)
