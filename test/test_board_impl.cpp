#include "board.h"
#include "board_impl.h"
#include <gtest/gtest.h>
#include <memory>

using std::shared_ptr;

TEST(BoardImpl, test_get_width)
{
    shared_ptr<Board> board{new BoardImpl{nullptr, 10, 20}};
    ASSERT_EQ(board->get_width(), 10);
}