cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")

set(PROJECT_NAME minishell) # EDIT THIS PROJECT NAME IF RECYCLING THIS CMAKE FILE
set(SRCS_DIR srcs)
set(HEADERS_DIR headers)
set(LIBS_DIR libs)
project(${PROJECT_NAME} C)

#include_directories(
#        ${SRCS_DIR}
#        ${HEADERS_DIR})

file(GLOB_RECURSE SRCS ${SRCS_DIR}/*.c ${LIBS_DIR}/*.c)
file(GLOB_RECURSE HEADERS ${HEADERS_DIR}/*.h ${LIBS_DIR}/*.h)

add_executable(${PROJECT_NAME}_mandatory ${SRCS} ${HEADERS})
set_target_properties(${PROJECT_NAME}_mandatory PROPERTIES COMPILE_FLAGS "-D BONUS=0")

add_executable(${PROJECT_NAME}_bonus ${SRCS} ${HEADERS})
set_target_properties(${PROJECT_NAME}_bonus PROPERTIES COMPILE_FLAGS "-D BONUS=1")
