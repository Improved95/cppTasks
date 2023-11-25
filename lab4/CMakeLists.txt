cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(SoundProcessor)
set(exe_name ${PROJECT_NAME})
set(test_name test)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
#    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(PATH_TO_EXECUTABLES src/executables/)
add_executable(${exe_name} src/main.cpp)
add_library(corelib OBJECT ${PATH_TO_EXECUTABLES}SoundProcessor.cpp ${PATH_TO_EXECUTABLES}Converter.cpp ${PATH_TO_EXECUTABLES}Parser.cpp
        ${PATH_TO_EXECUTABLES}CoutMessages.cpp)
target_include_directories(corelib PUBLIC src/headers)
target_include_directories(corelib PUBLIC lib/cxxopts/include)
target_link_libraries(${exe_name} corelib)
target_link_libraries(${exe_name} cxxopts)

#
