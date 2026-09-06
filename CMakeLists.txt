cmake_minimum_required(VERSION 3.28)
project(tracked_foveation)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendor EXCLUDE_FROM_ALL)

add_executable(mouse_tracker mouse_tracker.cpp)
target_link_libraries(mouse_tracker PRIVATE vendor)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0)

add_executable(pipeline pipeline.cpp)
target_include_directories(pipeline PRIVATE ${GST_INCLUDE_DIRS})
target_link_libraries(pipeline PRIVATE ${GST_LIBRARIES})
target_compile_options(pipeline PRIVATE ${GST_CFLAGS_OTHER})
