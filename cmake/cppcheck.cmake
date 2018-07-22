# additional target to perform cppcheck run, requires cppcheck

# get all project files
# HACK this workaround is required to avoid qml files checking ^_^
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND ${SOURCE_FILE} ${PROJECT_BINARY_DIR} PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT ${PROJECT_TRDPARTY_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
    endif ()
endforeach ()
find_program(CPP_CHECK cppcheck)
set(CPPCHECK_TEMPLATE "cppcheck:{file}:{line}: {severity}:{message}")
add_custom_target(
    cppcheck
    COMMAND ${CPP_CHECK}
    --enable=warning,performance,portability,information,missingInclude
    --std=c++11
    #--library=qt.cfg
    --error-exitcode=1
    #--template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)"
    --template=${CPPCHECK_TEMPLATE}
    #--verbose
    --quiet
    ${ALL_SOURCE_FILES}
    )

