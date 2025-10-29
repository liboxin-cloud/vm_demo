cmake_minimum_required(VERSION 3.10)

project(vm_demo C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)


set(SOURCES 
    vm.c
    test_vm.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(vm_test ${SOURCES})

target_link_libraries(vm_test m)

