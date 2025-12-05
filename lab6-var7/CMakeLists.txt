cmake_minimum_required(VERSION 3.10)
project(lab6_patterns)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.0.tar.gz
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

# Все исходные файлы проекта
set(ALL_SOURCES
    main.cpp
    src/NPC/npc.cpp
    src/NPC/orc.cpp
    src/NPC/knight.cpp
    src/NPC/bear.cpp
    src/NPC/npc_factory.cpp
    src/Visitor/fight_visitor.cpp
    src/Observer/subject.cpp
    src/Observer/console_observer.cpp
    src/Observer/file_observer.cpp
    src/DungeonMap.cpp
)

# Основная программа
add_executable(main ${ALL_SOURCES})

# Тесты (без main.cpp)
list(REMOVE_ITEM ALL_SOURCES main.cpp)
add_executable(lab_tests tests/tests.cpp ${ALL_SOURCES})
target_link_libraries(lab_tests gtest_main)

enable_testing()
add_test(NAME lab_tests COMMAND lab_tests)