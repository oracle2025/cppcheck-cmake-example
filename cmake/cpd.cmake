#pmd cpd --minimum-tokens 100 --files main.cpp
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)
foreach (SOURCE_FILE ${ALL_SOURCE_FILES})
    string(FIND ${SOURCE_FILE} ${PROJECT_BINARY_DIR} PROJECT_TRDPARTY_DIR_FOUND)
    if (NOT ${PROJECT_TRDPARTY_DIR_FOUND} EQUAL -1)
        list(REMOVE_ITEM ALL_SOURCE_FILES ${SOURCE_FILE})
    endif ()
endforeach ()
find_program(PMD pmd)
add_custom_target(
    cpd
    COMMAND ${PMD}
    cpd
    --minimum-tokens 20
    --language cpp
    --files ${ALL_SOURCE_FILES}
    )

