## Set project name
project(cpu-tools C CXX)
cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

set(PYBIND11_PYTHON_VERSION 3.7)
set(PYTHON_EXECUTABLE /usr/bin/python3.7)
set(PYTHON_INCLUDE_DIRS "/usr/include/python3.7")
set(PYTHON_LIBRARIES "/usr/lib/python3.7/config-3.7m-x86_64-linux-gnu/libpython3.7.so")

option(BUILD_PYBINDINGS "build pybindings" ON)

set(CPUTOOLS_LIBRARY_SHARED "cputools")
set(pybindings "pycputools") 

# build shared library
add_library(${CPUTOOLS_LIBRARY_SHARED} SHARED src/cpu_tools.c)
target_include_directories(${CPUTOOLS_LIBRARY_SHARED}
                           PRIVATE
                                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                              )
set(BINARIES
      read_cpu_temp
      read_cpu_clock
)

foreach(source ${BINARIES})
    add_executable(${source} src/${source}.c)
    target_include_directories(${source}
                               PRIVATE
                                   $<INSTALL_INTERFACE:include>
                                   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                              )

    target_link_libraries(${source}
                          PRIVATE
                            ${CPUTOOLS_LIBRARY_SHARED})
endforeach()

# get external projects - rename external headers to hpp to distinguish
if (BUILD_PYBINDINGS)
message(STATUS "Checking for pyoind11....")
find_package(pybind11 )
#add_subdirectory(pybind11)
  if(NOT ${pybind11_FOUND})
    message(WARNING "-- Can not find pybind11! Please install with sudo apt install pybind11-dev on a linux system!")
    set(BUILD_PYBINDINGS OFF CACHE BOOL "build pybindings" FORCE)
  else()
    message(STATUS "-- found pybind11, building pybindings.")
   
    add_library(${pybindings} MODULE python/pycputools.cxx)
    target_include_directories(${pybindings}
                               PRIVATE
                                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                   $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                              )

    target_link_libraries(${pybindings}
                             PRIVATE
                          pybind11::module
                          ${CPUTOOLS_LIBRARY_SHARED}  )
    set_target_properties(${pybindings} PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
                                         SUFFIX "${PYTHON_MODULE_EXTENSION}")
    #pybind11_add_module(${pybindings} MODULE python/pycputools.cxx)
    target_include_directories(${pybindings}
                               PRIVATE
                                    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                                   $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                              )

    #target_link_libraries(${pybindings}
    #                      PRIVATE
    #                        ${CPUTOOLS_LIBRARY_SHARED}
    #                      )

  endif()
endif(BUILD_PYBINDINGS)

