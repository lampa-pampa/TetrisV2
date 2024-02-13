add_executable(all_tests
    test_brick.cpp
    test_bag.cpp
    test_score_counter_impl.cpp
    test_brick_generator_impl.cpp
    test_board_impl.cpp
    test_pixel.cpp
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