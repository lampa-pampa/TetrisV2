add_library(TETRIS_V2)

target_include_directories(TETRIS_V2
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

target_sources(TETRIS_V2
    PRIVATE
        board/board_impl.cpp
        brick/brick.cpp
        config/config.cpp
        config/keyboard/console/config.cpp
        config/matrix_display/console/config.cpp
        game_controller/game_controller.cpp
        game/game_impl.cpp
        run_tetris/main_loop.cpp
        run_tetris/run_tetris.cpp
        timer/timer_impl.cpp
        ui/game_ui/matrix_display_game_ui_impl.cpp
        ui/matrix_display/console/console_matrix_display_impl.cpp
        ui/render/brick_preview/brick_preview.cpp
        ui/render/container/container.cpp
        ui/render/cubes/cubes.cpp
        ui/render/progress_bar/progress_bar.cpp
        ui/render/text/font/fixed_width.cpp
        ui/render/text/font/font.cpp
        ui/render/text/text.cpp
)

add_executable(tetris_v2
    main/console/main.cpp
)

target_link_libraries(tetris_v2
    TETRIS_V2
    -lncursesw
)