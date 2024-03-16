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
        board_impl.cpp
        brick.cpp
        game_impl.cpp
        score_counter_impl.cpp
        timer_impl.cpp
        ui/console_matrix_display_impl.cpp
        ui/matrix_display_game_ui_impl.cpp
        ui/ncurses_colors.cpp
)

add_executable(tetris_v2
    main.cpp
)

target_link_libraries(tetris_v2
    TETRIS_V2
    -lncursesw
)