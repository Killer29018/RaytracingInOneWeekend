cmake_minimum_required(VERSION 3.18)

project ( RaytracingInOneWeekend )

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64 -std=c++17")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set (linker "")

set (source_dir "${PROJECT_SOURCE_DIR}/src")
set (CMAKE_BINARY_DIR "/bin")

set (EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}${CMAKE_BINARY_DIR}")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set (EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/debug")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    set (EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/release")
endif ()

if (WIN32)
endif()

file (GLOB cppFiles CONFIGURE_DEPENDS "${source_dir}/*.cpp")

add_executable(${PROJECT_NAME} ${cppFiles})

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${linker})
endif()