cmake_minimum_required(VERSION 3.10)
project(auto_system_api)

set(CMAKE_CXX_STANDARD 20)

add_library(auto_system_api STATIC 
  src/backend/ipc_backend.cpp
)
target_include_directories(auto_system_api PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
# add_library(ipc STATIC src/ipc.cpp)
# target_include_directories(ipc PUBLIC
#   ${CMAKE_CURRENT_SOURCE_DIR}/include
#   ipc_backend
# )

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
    auto_system_api
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_ipc_backend)
