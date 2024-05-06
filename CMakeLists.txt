cmake_minimum_required(VERSION 3.10)

project(
  greet2
  VERSION 1.0.0
  LANGUAGES CXX)

add_library(greet2 STATIC)

target_sources(${PROJECT_NAME} PRIVATE include/greet2/greet2.h src/greet2.cpp)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

if(fmt_FOUND)
  message("======> fmt found")
endif()

set(PUBLIC_HEADERS include/greet2/greet2.h)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER
                                                 "${PUBLIC_HEADERS}")

include(GNUInstallDirs)

set(INC_DIR ${CMAKE_INSTALL_INCLUDEDIR})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE # where the library itself will look for its internal headers
          ${PROJECT_SOURCE_DIR}/src
  PUBLIC # where top-level project will look for the library's public headers
         $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
         # where external projects will look for the library's public headers
         $<INSTALL_INTERFACE:${INC_DIR}>)

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

option(LIB_INSTALL "Generate the install target." ON)

# Install targets.
if(LIB_INSTALL)
  include(CMakePackageConfigHelpers)
  set(CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/greet2)

  set(version_config ${PROJECT_BINARY_DIR}/greet2-config-version.cmake)
  set(project_config ${PROJECT_BINARY_DIR}/greet2-config.cmake)
  set(targets_export_name greet2-targets)

  set(LIB_DIR ${CMAKE_INSTALL_LIBDIR} CACHE STRING "")

  # generate the version file for the config file
  write_basic_package_version_file(
    ${version_config}
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY AnyNewerVersion)

  configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/support/cmake/greet2-config.cmake.in
    ${project_config}
    INSTALL_DESTINATION ${CMAKE_DIR})

  set(INSTALL_TARGETS greet2)

  # Install the library and headers.
  install(TARGETS ${INSTALL_TARGETS} EXPORT ${targets_export_name}
    LIBRARY DESTINATION ${LIB_DIR}
    ARCHIVE DESTINATION ${LIB_DIR}
    PUBLIC_HEADER DESTINATION "${INC_DIR}/greet2"
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

  # Use a namespace because CMake provides better diagnostics for namespaced
  # imported targets.
  export(TARGETS ${INSTALL_TARGETS} NAMESPACE greet2::
         FILE ${PROJECT_BINARY_DIR}/${targets_export_name}.cmake)
  
  # Install version, config and target files.
  install(
    FILES ${project_config} ${version_config}
    DESTINATION ${CMAKE_DIR})

  install(EXPORT ${targets_export_name} DESTINATION ${CMAKE_DIR}
        NAMESPACE greet2::)
endif()