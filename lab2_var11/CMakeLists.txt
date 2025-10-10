cmake_minimum_required(VERSION 3.10)
project(lab2_var11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include_directories(include)
add_library(vector_lib src/vector.cpp)
add_library(tothirteen_lib src/thirteen_num_syst.cpp)

target_link_libraries(tothirteen_lib vector_lib)
add_executable(main main.cpp)

target_link_libraries(main tothirteen_lib vector_lib)

# Добавление тестов
enable_testing()

add_executable(tests tests/tests.cpp)
target_link_libraries(tests vector_lib tothirteen_lib gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests COMMAND tests)