cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#https://github.com/danmar/cppcheck/blob/master/tools/git-pre-commit-cppcheck
#https://github.com/kbenzie/git-cmake-format
#https://stackoverflow.com/questions/40325957/how-do-i-add-valgrind-tests-to-my-cmake-test-target
#syntastic/linters.vim

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(clang-format)

include(cppcheck)
include(cpd)
include(infer)
include(cpplint)

add_custom_target(check DEPENDS cppcheck cpd infer cpplint)

set(CMAKE_CXX_CPPCHECK cppcheck
    --enable=all
    --inconclusive
    --std=posix
    --project=compile_commands.json
    --error-exitcode=1
    --template="cppcheck: {file}:{line}: {severity}: {message}")
set(CMAKE_CXX_CPPLINT cpplint)
add_executable(main main.cpp)



