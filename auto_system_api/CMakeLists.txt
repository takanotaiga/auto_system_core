cmake_minimum_required(VERSION 3.10)
project(auto_system_api)

set(CMAKE_CXX_STANDARD 20)

add_library(ipc_backend STATIC src/backend/ipc_backend.cpp)
target_include_directories(ipc_backend PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# # read.cpp 実行ファイル
# add_executable(read_exec read.cpp)
# target_link_libraries(read_exec PRIVATE ipc)

# # write.cpp 実行ファイル
# add_executable(write_exec write.cpp)
# target_link_libraries(write_exec PRIVATE ipc)


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

add_executable(test_ipc_backend test/test_ipc_backend.cpp)
target_link_libraries(test_ipc_backend
  PRIVATE
    ipc_backend
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_ipc_backend)
