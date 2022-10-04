include(FetchContent)
FetchContent_Declare(cspecs GIT_REPOSITORY https://github.com/mumuki/cspec)
FetchContent_MakeAvailable(cspecs)

include_directories(${cspecs_SOURCE_DIR})
link_libraries(cspecs)

add_executable(commons-unit-test
        test_bitarray.c
        test_config.c
        test_dictionary.c
        test_list.c
        test_memory.c
        test_queue.c
        test_string.c)

configure_file(resources/config.cfg resources/config.cfg COPYONLY)
configure_file(resources/config-double-newline.cfg resources/config-double-newline.cfg COPYONLY)
