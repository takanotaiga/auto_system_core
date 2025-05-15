cmake_minimum_required(VERSION 3.10)
project(IPC_Example)

set(CMAKE_CXX_STANDARD 20)

# IPCライブラリを作成（ipc.cpp, ipc.hpp）
add_library(ipc STATIC ipc.cpp)

# read.cpp 実行ファイル
add_executable(read_exec read.cpp)
target_link_libraries(read_exec PRIVATE ipc)

# write.cpp 実行ファイル
add_executable(write_exec write.cpp)
target_link_libraries(write_exec PRIVATE ipc)


# ---------------------
# Google Test
# ---------------------


include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_ipc test_ipc.cpp)
target_link_libraries(test_ipc
  PRIVATE
    ipc
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_ipc)
