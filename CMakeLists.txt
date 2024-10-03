cmake_minimum_required(VERSION 3.16...3.16)
project(G4tutorial)

#load G4
find_package(Geant4 REQUIRED)
include($(Geant4_USE_FILE))
include_directories(${PROJECT_SOURCE_DIR}/include)

#files you want to complie
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/.hh)

#add executable file ZL
add_executable(ZL G4tutorial.cc ${sources} ${headers})

target_link_libraries(ZL ${Geant4_LIBRARIES}
