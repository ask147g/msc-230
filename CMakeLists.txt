cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(src-msc-230)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB SOURCE_FILES "*.in")
file(COPY ${SOURCE_FILES} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB PROCESSING_FILES "processing/*.C")
file(COPY ${PROCESSING_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(msc-230 msc-230.cc ${sources} ${headers})
target_link_libraries(msc-230 ${Geant4_LIBRARIES})

add_custom_target(src-msc-230 DEPENDS msc-230)