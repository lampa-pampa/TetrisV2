#include "vector_2.h"

#include <utility>
#include <vector>

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using std::pair;
using std::vector;
using testing::Eq;
using Tetris::Vector2;

TEST(Vector2, abs)
{
    const vector<pair<Vector2, Vector2>> vector_2_to_expected{
        { {4, 3}, {4, 3} },
        { {-2, 6}, {2, 6} },
        { {-6, -7}, {6, 7} },
        { {1, -3}, {1, 3} },
    };

    for(const auto& pair : vector_2_to_expected)
        ASSERT_THAT(pair.first.abs(), Eq(pair.second));
}

TEST(Vector2, operator_greater_than_or_equal_to_vector_2)
{
    const Vector2 initial_vector{3, 4};
    const vector<pair<Vector2, bool>> vector_2_to_expected{
        { {1, 2}, false },
        { {5, 3}, false },
        { {2, 9}, false },
        { {6, 8}, true },
    };

    for(const auto& pair : vector_2_to_expected)
        ASSERT_THAT(pair.first >= initial_vector, Eq(pair.second));
}

TEST(Vector2, operator_equal_to_vector_2)
{
    const Vector2 initial_vector{2, 1};
    const vector<pair<Vector2, bool>> vector_2_to_expected{
        { {2, 5}, false },
        { {7, 1}, false },
        { {2, 1}, true },
    };

    for(const auto& pair : vector_2_to_expected)
        ASSERT_THAT(pair.first == initial_vector, Eq(pair.second));
}

TEST(Vector2, operator_addition_assignment_vector_2)
{
    const Vector2 initial_vector{1, 2};
    const vector<pair<Vector2, Vector2>> vector_2_to_expected{
        { {1, 2}, {2, 4} },
        { {-1, 3}, {0, 5} },
        { {2, -5}, {3, -3} },
        { {-4, -3}, {-3, -1} },
    };

    for(const auto& pair : vector_2_to_expected)
    {
        Vector2 vector_2{initial_vector};
        vector_2 += pair.first;

        ASSERT_THAT(vector_2, Eq(pair.second));
    }
}

TEST(Vector2, operator_addition_vector_2)
{
    const Vector2 initial_vector{2, 5};
    const vector<pair<Vector2, Vector2>> vector_2_to_expected{
        { {2, 5}, {4, 10} },
        { {-7, 1}, {-5, 6} },
        { {3, -6}, {5, -1} },
        { {-4, -3}, {-2, 2} },
    };

    for(const auto& pair : vector_2_to_expected)
        ASSERT_THAT(initial_vector + pair.first, Eq(pair.second));
}

TEST(Vector2, operator_subtraction_vector_2)
{
    const Vector2 initial_vector{9, 8};
    const vector<pair<Vector2, Vector2>> vector_2_to_expected{
        { {1, 0}, {8, 8} },
        { {-2, 4}, {11, 4} },
        { {5, -7}, {4, 15} },
        { {3, 3}, {6, 5} },
    };

    for(const auto& pair : vector_2_to_expected)
        ASSERT_THAT(initial_vector - pair.first, Eq(pair.second));
}

TEST(Vector2, operator_multiplication_vector_2)
{
    const Vector2 initial_vector{3, 4};
    const vector<pair<Vector2, Vector2>> vector_2_to_expected{
        { {4, 7}, {12, 28} },
        { {-3, 2}, {-9, 8} },
        { {-6, 5}, {-18, 20} },
        { {-9, -2}, {-27, -8} },
    };

    for(const auto& pair : vector_2_to_expected)
        ASSERT_THAT(initial_vector * pair.first, Eq(pair.second));
}

TEST(Vector2, operator_division_vector_2)
{
    const Vector2 initial_vector{1, 6};
    const vector<pair<Vector2, Vector2>> vector_2_to_expected{
        { {2, 8}, {0, 0} },
        { {6, 3}, {0, 2} },
        { {1, -2}, {1, -3} },
        { {-7, -3}, {0, -2} },
    };

    for(const auto& pair : vector_2_to_expected)
        ASSERT_THAT(initial_vector / pair.first, Eq(pair.second));
}

TEST(Vector2, operator_addition_int)
{
    const Vector2 initial_vector{6, 2};
    const vector<pair<int, Vector2>> number_to_expected{
        { 3, {9, 5} },
        { 7, {13, 9} },
        { -2, {4, 0} },
        { -9, {-3, -7} },
    };

    for(const auto& pair : number_to_expected)
        ASSERT_THAT(initial_vector + pair.first, Eq(pair.second));
}

TEST(Vector2, operator_subtraction_int)
{
    const Vector2 initial_vector{1, 0};
    const vector<pair<int, Vector2>> number_to_expected{
        { 2, {-1, -2} },
        { 5, {-4, -5} },
        { -8, {9, 8} },
        { -3, {4, 3} },
    };

    for(const auto& pair : number_to_expected)
        ASSERT_THAT(initial_vector - pair.first, Eq(pair.second));
}

TEST(Vector2, operator_multiplication_int)
{
    const Vector2 initial_vector{5, 7};
    const vector<pair<int, Vector2>> number_to_expected{
        { 8, {40, 56} },
        { 3, {15, 21} },
        { -2, {-10, -14} },
        { -5, {-25, -35} },
    };

    for(const auto& pair : number_to_expected)
        ASSERT_THAT(initial_vector * pair.first, Eq(pair.second));
}

TEST(Vector2, operator_division_int)
{
    const Vector2 initial_vector{8, 3};
    const vector<pair<int, Vector2>> number_to_expected{
        { 2, {4, 1} },
        { 4, {2, 0} },
        { -3, {-2, -1} },
        { -5, {-1, 0} },
    };

    for(const auto& pair : number_to_expected)
        ASSERT_THAT(initial_vector / pair.first, Eq(pair.second));
}