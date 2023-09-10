cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(task1)
set(exe_name ${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "-O0")
add_executable(${exe_name} src/main.cpp)
#add_executable(${exe_name} begin/main.cpp begin/m1.cpp begin/m2.cpp)

# Включаем отслеживание всех предупреждений (warnings) и запрещаем компиляцию при наличии предупреждений.
# Считается хорошим тоном, когда программа собирается без предупрреждений.
# Но вы можете убрать /WX и -Werror (разрешив компиляцию с предупреждениями), если сможете разумно объяснить своё решение.
if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()