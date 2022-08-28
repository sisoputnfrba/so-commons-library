add_library(commons SHARED
        commons/bitarray.c
        commons/config.c
        commons/error.c
        commons/log.c
        commons/memory.c
        commons/process.c
        commons/string.c
        commons/temporal.c
        commons/txt.c
        commons/collections/dictionary.c
        commons/collections/list.c
        commons/collections/queue.c)

install(TARGETS commons
        LIBRARY DESTINATION lib)

install(DIRECTORY commons
        DESTINATION include
        FILES_MATCHING PATTERN "*.h")
