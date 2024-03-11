add_library(TETRIS_V2)

target_include_directories(TETRIS_V2
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(TETRIS_V2
    PRIVATE
        game_impl.cpp
)

add_executable(tetris_v2
    main.cpp
)

target_link_libraries(tetris_v2
    TETRIS_V2
    -lncursesw
)