#!/bin/bash
set -e

clang-format -i ./ipc.hpp 
clang-format -i ./read.cpp
clang-format -i ./write.cpp