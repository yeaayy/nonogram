
option(TRACE_OBJECT "Print Nonogram object creation and destruction" OFF)

add_library(nonogram_base STATIC
    parser/error_handler.cpp
    parser/parser.cpp
    parser/stream.cpp

    number_parser.cpp
    number_list_parser.cpp
    space_parser.cpp
    nonogram_parser.cpp

    cue.cpp
    nonogram.cpp
)

if(TRACE_OBJECT)
    target_compile_definitions(nonogram_base PRIVATE "TRACE_OBJECT")
endif()

target_include_directories(nonogram_base PUBLIC .)

target_link_libraries(nonogram PUBLIC nonogram_base)
