cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(lab2)
set(exe_name ${PROJECT_NAME})
set(test_name test)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(corelib OBJECT src/circularBuffer.cpp)
set_target_properties(corelib PROPERTIES EXCLUDE_FROM_ALL TRUE)
set_target_properties(corelib PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD TRUE)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
    set(CMAKE_POLICY_DEFAULT_CMP0135 NEW)
endif()

# ��������� ���������� GoogleTest
include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/58d77fa8070e8cec2dc1ed015d66b454c8d78850.zip
)
## For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ��������� ����������� ���� ��������� ��� ������� ������: ��� cpp-����� ������ + �������� ���������� + ���������� gtest_main
# ��� ����������� main.cpp ����� �� �����, �.�. ������� main ����������� � gtest_main
add_executable(${test_name} src/test.cpp)
target_link_libraries(${test_name} gtest_main)
target_link_libraries(${test_name} gmock_main)
target_link_libraries(${test_name} corelib)
