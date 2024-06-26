cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(SoundProcessor)
set(exe_name ${PROJECT_NAME})

if (MSVC)
    # warning level 4 and all warnings as errors
#    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
#    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(PATH_TO_EXECUTABLES src/executables/)
add_executable(${exe_name} src/main.cpp)
add_library(corelib OBJECT ${PATH_TO_EXECUTABLES}SoundProcessor.cpp ${PATH_TO_EXECUTABLES}ConsoleParser.cpp
        ${PATH_TO_EXECUTABLES}Messages.cpp  ${PATH_TO_EXECUTABLES}ConverterManager.cpp ${PATH_TO_EXECUTABLES}Streams.cpp
        ${PATH_TO_EXECUTABLES}FilesParser.cpp ${PATH_TO_EXECUTABLES}WavMetadataParse.cpp ${PATH_TO_EXECUTABLES}ConvertingMethods.cpp)
target_include_directories(corelib PUBLIC src/executables)
target_include_directories(corelib PUBLIC src/headers)
target_include_directories(corelib PUBLIC include_libs/cxxopts/include)
target_link_libraries(${exe_name} corelib)
