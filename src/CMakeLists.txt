find_package(fmt CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(Poco CONFIG REQUIRED)

# Generic test that uses conan libs
add_executable(intro main.cpp)

include_directories("${PROJECT_SOURCE_DIR}/utils")
add_subdirectory(utils)
set(EXTRA_LIBS ${EXTRA_LIBS} utils)

target_link_libraries(
  intro
  PUBLIC project_options project_warnings
  PRIVATE CLI11::CLI11 fmt::fmt spdlog::spdlog Poco::Poco ${EXTRA_LIBS})

target_include_directories(intro PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
