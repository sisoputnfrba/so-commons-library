link_libraries(pthread)

add_executable(commons-integration-test-logger logger/main.c)
add_executable(commons-integration-test-temporal temporal/main.c)

add_test(NAME commons-integration-test-logger COMMAND ./commons-integration-test-logger)
add_test(NAME commons-integration-test-logger-valgrind
        COMMAND valgrind
        --leak-check=full
        --track-origins=yes
        --error-exitcode=1
        -v
        ./commons-integration-test-logger)

add_test(NAME commons-integration-test-temporal COMMAND ./commons-integration-test-temporal)
add_test(NAME commons-integration-test-temporal-valgrind
        COMMAND valgrind
        --leak-check=full
        --track-origins=yes
        --error-exitcode=1
        -v
        ./commons-integration-test-temporal)
