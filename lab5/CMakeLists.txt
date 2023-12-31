cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(csvParser)
set(exe_name ${PROJECT_NAME})

if (MSVC)
    # warning level 4 and all warnings as errors
#        add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
#        add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_executable(${exe_name} src/main.cpp)
add_library(corelib OBJECT src/executables/csvParser.cpp)
target_include_directories(corelib PUBLIC src/headers)
target_link_libraries(${exe_name} corelib)
