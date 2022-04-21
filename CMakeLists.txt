cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_STANDARD 99)

if (UNIX AND NOT APPLE)
    set(CMAKE_C_FLAGS "-Wall -Werror -Wextra -lreadline")
else()
    set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_C_FLAGS} "-lreadline")
endif()

set(PROJECT_NAME minishell) # EDIT THIS PROJECT NAME IF RECYCLING THIS CMAKE FILE
set(SRCS_DIR srcs)
set(HEADERS_DIR headers)
set(LIBS_DIR libs)
project(${PROJECT_NAME} C)

#include_directories(
#        ${SRCS_DIR}
#        ${HEADERS_DIR})

file(GLOB_RECURSE SRCS ${SRCS_DIR}/*.c ${SRCS_DIR}/*/*.c ${LIBS_DIR}/*.c)
file(GLOB_RECURSE HEADERS ${HEADERS_DIR}/*.h ${HEADERS_DIR}/*/*.h ${LIBS_DIR}/*.h)

add_executable(${PROJECT_NAME}_mandatory ${SRCS} ${HEADERS})
target_link_libraries(${PROJECT_NAME}_mandatory "readline")
set_target_properties(${PROJECT_NAME}_mandatory PROPERTIES COMPILE_FLAGS "-D BONUS=0")