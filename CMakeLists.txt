cmake_minimum_required(VERSION 3.0)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -target x86_64-apple-darwin20.3.0") # -target is for m1 mac only
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") # USE THIS FOR UBUNTU/DEBIAN

project(Allotemplate)

include(CheckCCompilerFlag)

set(CMAKE_REQUIRED_LINK_OPTIONS "-arch;x86_64")
check_c_compiler_flag("-arch x86_64" x86_64Supported)
message("x86_64Supported=${x86_64Supported}")

set(CMAKE_REQUIRED_LINK_OPTIONS "-arch;arm64")
check_c_compiler_flag("-arch arm64" arm64Supported)
message("arm64Supported=${arm64Supported}")

# name of application. replace 'app' with desired app name
set(APP_NAME app)

# path to main source file
add_executable(${APP_NAME} src/main.cpp src/mpc.cpp src/sample.cpp src/SineEnv.cpp)



# add allolib as a subdirectory to the project
add_subdirectory(allolib)

# add gamma?
find_library(GAMMA_LIB Gamma lib)
find_library(PORTAUDIO_LIB portaudio lib)
find_library(SNDFILE_LIB sndfile lib)
find_path(GAMMA_INCLUDES Gamma.h gamma/Gamma)
include_directories(${GAMMA_INCLUDES})


if (EXISTS ${CMAKE_CURRENT_LIST_DIR}/al_ext)
  message("Buiding extensions in al_ext")
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/al_ext)
  get_target_property(AL_EXT_LIBRARIES al_ext AL_EXT_LIBRARIES)
  # target_link_libraries(${APP_NAME} PRIVATE )
endif()

# link allolib to project
# target_link_libraries(${APP_NAME} PRIVATE al)

#final
target_link_libraries(${APP_NAME} al ${AL_EXT_LIBRARIES} ${GAMMA_LIB} ${PORTAUDIO_LIB} ${SNDFILE_LIB})











# example line for find_package usage
# find_package(Qt5Core REQUIRED CONFIG PATHS "C:/Qt/5.12.0/msvc2017_64/lib" NO_DEFAULT_PATH)

# replace ${PATH_TO_INCLUDE_DIR} before including other libraries
# target_include_directories(${APP_NAME} PRIVATE ${PATH_TO_INCLUDE_DIR})

# replace ${PATH_TO_LIB_FILE} before linking other libraries
# target_link_libraries(${APP_NAME} PRIVATE ${PATH_TO_LIB_FILE})

# binaries are put into the ./bin directory by default
set_target_properties(${APP_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_LIST_DIR}/bin
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_LIST_DIR}/bin
)
