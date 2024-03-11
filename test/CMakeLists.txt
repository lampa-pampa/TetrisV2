add_executable(all_tests
    test_brick.cpp
    test_bag.cpp
    test_score_counter_impl.cpp
    test_brick_generator_impl.cpp
    test_board_impl.cpp
    test_cube.cpp
    test_game_impl.cpp
    test_vector_2.cpp
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