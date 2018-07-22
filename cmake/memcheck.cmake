#add_custom_target(memcheck
    #COMMAND ${CMAKE_CTEST_COMMAND} 
#    --force-new-ctest-process --test-action memcheck)
    #COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log")

find_program(VALGRIND valgrind)
add_custom_target(
    memcheck)

function(add_memcheck prog)
    add_custom_command(
        TARGET memcheck
        COMMAND ${VALGRIND}
        -q
        --tool=memcheck
        --leak-check=yes
        --show-reachable=yes
        --num-callers=50
        --error-exitcode=1 
        $<TARGET_FILE:${prog}>
        DEPENDS ${prog})
endfunction()
