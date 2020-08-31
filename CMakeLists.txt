cmake_minimum_required(VERSION 3.13.0)

project(
    CorgiMemory
    DESCRIPTION "Library for memory stuff"
    LANGUAGES CXX
    VERSION 1.0.0
    HOMEPAGE_URL "http://github.com/ProfesseurPoire/CorgiMemory")

# We'll install the library in lib64 if we're in x64, in lib otherwise
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(arch_suffix "64")
endif()

add_library(${PROJECT_NAME} INTERFACE)

set(install_folder lib${arch_suffix}/${PROJECT_NAME}-${PROJECT_VERSION}/)

target_include_directories(
    ${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${install_folder}/include>)

#####################################################
# Installing the library and exporting the targets
#####################################################

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(
    TARGETS ${PROJECT_NAME} 
    EXPORT ${PROJECT_NAME}-target
    LIBRARY     DESTINATION ${install_folder}/
    ARCHIVE     DESTINATION ${install_folder}/
    RUNTIME     DESTINATION ${install_folder}/
    INCLUDES    DESTINATION ${install_folder}/include)

install(
    EXPORT  ${PROJECT_NAME}-target
    DESTINATION ${install_folder}/cmake)

configure_file(cmake/config.cmake.in ${PROJECT_NAME}Config.cmake @ONLY)

# Installs the config and config version file 
install(
    FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"  
    DESTINATION ${install_folder}/cmake)

# Installing header files
install(
    DIRECTORY include/
    DESTINATION ${install_folder}/include
    FILES_MATCHING PATTERN *.h)

#########################################
# Tests
#########################################

#option(BUILD_TESTS "Build the tests" ON)
#
#if(BUILD_TESTS)
#enable_testing()
#add_subdirectory(tests)
#endif()