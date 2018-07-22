cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#https://github.com/danmar/cppcheck/blob/master/tools/git-pre-commit-cppcheck
#https://github.com/kbenzie/git-cmake-format
#https://stackoverflow.com/questions/40325957/how-do-i-add-valgrind-tests-to-my-cmake-test-target
#syntastic/linters.vim

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# $ mkdir build; cd build
# $ cmake -DCMAKE_BUILD_TYPE=Debug ..
# $ ctest -T memcheck
# $ cat ./Testing/Temporary/MemoryChecker.*.log
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

include(clang-format)

include(cppcheck)
include(cpd)
include(infer)
include(cpplint)
include(memcheck)

add_custom_target(check DEPENDS cppcheck cpd infer cpplint memcheck)

set(CMAKE_CXX_CPPCHECK cppcheck
    --enable=all
    --inconclusive
    --std=posix
    --project=compile_commands.json
    --error-exitcode=1
    --template="cppcheck: {file}:{line}: {severity}: {message}")
set(CMAKE_CXX_CPPLINT cpplint)
include (CTest)
add_executable(main main.cpp)
set(CTEST_MEMORYCHECK_COMMAND_OPTIONS --error-exitcode=1)
add_test(main_test main)
add_memcheck(main)



