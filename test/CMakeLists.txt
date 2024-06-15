add_executable(all_tests
    bag/test_bag.cpp
    board/test_board_impl.cpp
    brick/test_bag.cpp
    brick/test_brick.cpp
    cube/test_cube.cpp
    game/test_game_impl.cpp
    score_counter/test_score_counter_impl.cpp
    ui/render/container/test_container.cpp
    vector_2/test_vector_2.cpp
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

target_link_libraries(all_tests
    PRIVATE
        TETRIS_V2
        -lgtest
        -lgtest_main
        -lpthread
)

include(GoogleTest)
gtest_discover_tests(all_tests)