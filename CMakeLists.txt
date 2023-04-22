cmake_minimum_required(VERSION 3.0.0)
project(OurCalendar VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
file(GLOB HEADERS "include/*.h")
file(GLOB MODULES "module/*.c")
add_executable(OurCalendar main.c ${HEADERS} ${MODULES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)