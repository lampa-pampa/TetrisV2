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
        board/board_impl.cpp
        brick/brick.cpp
        config/config.cpp
        game_controller/game_controller.cpp
        game/game_impl.cpp
        config/matrix/console/matrix_config.cpp
        run_tetris/main_loop.cpp
        run_tetris/run_tetris.cpp
        timer/timer_impl.cpp
        ui/game_ui/matrix_display_game_ui_impl.cpp
        ui/matrix_display/console/console_matrix_display_impl.cpp
        ui/matrix_display/console/ncurses_colors.cpp
        ui/progress_bar/progress_bar.cpp
        ui/text_area/text_area.cpp
)

add_executable(tetris_v2
    main/console/main.cpp
)

target_link_libraries(tetris_v2
    TETRIS_V2
    -lncursesw
)