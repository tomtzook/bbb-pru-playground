cmake_minimum_required(VERSION 3.16)
project(pru_test C CXX)

set(STACK_SIZE 0x100)
set(HEAP_SIZE 0x100)

set(CMAKE_C_COMPILER ${PRU_COMPILER_HOME}/bin/clpru)
set(CMAKE_CXX_COMPILER ${PRU_COMPILER_HOME}/bin/clpru)
set(CMAKE_LINKER ${PRU_COMPILER_HOME}/bin/lnkpru)
set(CMAKE_AR ${PRU_COMPILER_HOME}/bin/arpru)

set(CMAKE_FIND_ROOT_PATH ${PRU_COMPILER_HOME})

set(CMAKE_C_COMPILE_OBJECT "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -fe <OBJECT> <SOURCE>")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES> <OBJECTS>")
set(CMAKE_C_COMPILER_ABI ELF)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C99_EXTENSION_COMPILE_OPTION --c99)
unset(CMAKE_C_IMPLICIT_INCLUDE_DIRECTORIES)
unset(CMAKE_C_IMPLICIT_LINK_DIRECTORIES)
unset(CMAKE_C_IMPLICIT_LINK_LIBRARIES)

set(CMAKE_CXX_COMPILER_ABI ELF)
unset(CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES)
unset(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES)
unset(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES)

include_directories(lib/include)
include_directories(${PRU_SOFTPKG_HOME}/include)
include_directories(${PRU_SOFTPKG_HOME}/include/am335x)

add_executable(pru_test main.cpp
        lib/src/rp/rpmsg.cpp
        lib/src/regs.cpp
        lib/src/iep.cpp
        lib/src/config.cpp
        lib/src/intc.cpp)
target_compile_options(pru_test PRIVATE
        --include_path=${CMAKE_CURRENT_SOURCE_DIR}/include
        --include_path=${PRU_COMPILER_HOME}/include
        --include_path=${PRU_SOFTPKG_HOME}/include
        --include_path=${PRU_SOFTPKG_HOME}/include/am335x
        -v3
        -O2
        --display_error_number
        -ppd
        -ppa
        --asm_listing
        --c_src_interlist
        --endian=little
        --hardware_mac=on
        --pp_directory=${CMAKE_CURRENT_BINARY_DIR}
        --c++03)
target_link_options(pru_test PRIVATE
        -i${PRU_COMPILER_HOME}/lib
        -i${PRU_COMPILER_HOME}/include
        --reread_libs
        --warn_sections
        --stack_size=${STACK_SIZE}
        --heap_size=${HEAP_SIZE}
        -m ${CMAKE_CURRENT_BINARY_DIR}/pru_test.map)
target_link_libraries(pru_test PRIVATE
        --library=libc.a
        --library=${PRU_SOFTPKG_HOME}/lib/rpmsg_lib.lib)
set_target_properties(pru_test
        PROPERTIES
        SUFFIX ".out"
)

add_custom_target(pru_test_arm_bin
        COMMAND "${PRU_COMPILER_HOME}/bin/hexpru"
        "${PRU_COMPILER_HOME}/bin.cmd"
        "pru_test.out"
        DEPENDS pru_test
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
