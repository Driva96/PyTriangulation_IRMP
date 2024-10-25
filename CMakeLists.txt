cmake_minimum_required(VERSION 3.12)
project(triangulation VERSION 0.0.1)


set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(PYBIND11_FINDPYTHON ON)

add_definitions(-std=c++17)
add_compile_options(-O3) # Use level 3 optimization

# Find the Pybind11 package
find_package(pybind11 REQUIRED)

find_package(Ceres REQUIRED)
find_package(Eigen3 REQUIRED)

# Collect source files for the IRMP and pyIRMP directories
file(GLOB_RECURSE IRMP_FILES ${CMAKE_SOURCE_DIR}/src/IRMP/*.cpp ${CMAKE_SOURCE_DIR}/src/IRMP/*.h)
file(GLOB_RECURSE PYIRMP_FILES ${CMAKE_SOURCE_DIR}/src/pyIRMP/*.cpp ${CMAKE_SOURCE_DIR}/src/pyIRMP/*.h)

# Create a pybind11 module, using pyIRMP source files
pybind11_add_module(triangulation_module ${PYIRMP_FILES} ${IRMP_FILES})
target_include_directories(triangulation_module PRIVATE ${CMAKE_SOURCE_DIR}/src/ ${EIGEN3_INCLUDE_DIR} ${CERES_INCLUDE_DIRS})
target_compile_definitions(triangulation_module PRIVATE VERSION_INFO="${PROJECT_VERSION}")

# target_link_libraries(triangulation ${CERES_LIBRARIES})
# Link any necessary libraries (e.g., Ceres)
target_link_libraries(triangulation_module PRIVATE Ceres::ceres)
