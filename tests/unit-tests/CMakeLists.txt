include(ExternalProject)
ExternalProject_Add(cspecs
        GIT_REPOSITORY https://github.com/mumuki/cspec
        GIT_SHALLOW true
        UPDATE_DISCONNECTED true
        INSTALL_DIR "${CMAKE_BINARY_DIR}"
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR})

include_directories(${CMAKE_BINARY_DIR}/include)
link_directories(${CMAKE_BINARY_DIR}/lib)
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
