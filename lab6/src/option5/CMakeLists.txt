cmake_minimum_required(
    VERSION 3.13
    FATAL_ERROR
)

add_executable(
    main
    src/main.c
    src/message_queue/message_queue.h
    src/message_queue/message_queue.c
    src/my_ftoa/my_ftoa.h
    src/my_ftoa/my_ftoa.c
)

target_link_libraries(
    main
    -lrt
    -lm
)