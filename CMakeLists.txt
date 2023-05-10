cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_TOOLCHAIN_FILE "~/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
message(STATUS "Vcpkg toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

project(Gamebox)

include_directories("~/vcpkg/installed/x64-windows/include")

file(GLOB SRC_FILES
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/g2048/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/mines/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/tetris/*.cpp")
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

# copy images
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory 
  "${PROJECT_SOURCE_DIR}/assets/"
  "$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets")
