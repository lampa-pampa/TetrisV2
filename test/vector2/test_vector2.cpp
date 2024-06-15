#include "vector2/vector2.h"

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
    const vector<pair<Vector2, Vector2>> test_cases{
        {{1, 1}, {1, 1}},
        {{-1, 1}, {1, 1}},
        {{1, -1}, {1, 1}},
        {{-1, -1}, {1, 1}},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.abs(), Eq(pair.second));
}

TEST(Vector2, center)
{
    const vector<pair<Vector2, Vector2>> test_cases{
        {{2}, {1}},
        {{2, 4}, {1, 2}},
        {{4, 2}, {2, 1}},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first.center(), Eq(pair.second));
}

TEST(Vector2, scale)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, Vector2>> test_cases{
        {{2}, {2}},
        {{2, 1}, {2, 1}},
        {{1, 2}, {1, 2}},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(initial_vector.scale(pair.first), Eq(pair.second));
}

TEST(Vector2, operator_greater_than)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, bool>> test_cases{
        {{1, 1}, false},
        {{2, 1}, false},
        {{1, 2}, false},
        {{2, 2}, true},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first > initial_vector, Eq(pair.second));
}

TEST(Vector2, operator_smaller_than)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, bool>> test_cases{
        {{1, 1}, false},
        {{1, 0}, false},
        {{0, 1}, false},
        {{0, 0}, true},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first < initial_vector, Eq(pair.second));
}

TEST(Vector2, operator_eqal_to)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, bool>> test_cases{
        {{0, 0}, false},
        {{1, 0}, false},
        {{0, 1}, false},
        {{1, 1}, true},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first == initial_vector, Eq(pair.second));
}

TEST(Vector2, operator_greater_than_or_equal_to)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, bool>> test_cases{
        {{0, 0}, false},
        {{0, 1}, false},
        {{0, 2}, false},
        {{1, 0}, false},
        {{1, 1}, true},
        {{1, 2}, true},
        {{2, 0}, false},
        {{2, 1}, true},
        {{2, 2}, true},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first >= initial_vector, Eq(pair.second));
}

TEST(Vector2, operator_smaller_than_or_equal_to)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, bool>> test_cases{
        {{0, 0}, true},
        {{0, 1}, true},
        {{0, 2}, false},
        {{1, 0}, true},
        {{1, 1}, true},
        {{1, 2}, false},
        {{2, 0}, false},
        {{2, 1}, false},
        {{2, 2}, false},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(pair.first <= initial_vector, Eq(pair.second));
}

TEST(Vector2, operator_addition)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, Vector2>> test_cases{
        {{0, 0}, {1, 1}},
        {{1, 0}, {2, 1}},
        {{0, 1}, {1, 2}},
        {{1, 1}, {2, 2}},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(initial_vector + pair.first, Eq(pair.second));
}

TEST(Vector2, operator_subtraction)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, Vector2>> test_cases{
        {{0, 0}, {1, 1}},
        {{1, 0}, {0, 1}},
        {{0, 1}, {1, 0}},
        {{1, 1}, {0, 0}},
    };

    for (const auto& pair : test_cases)
        ASSERT_THAT(initial_vector - pair.first, Eq(pair.second));
}

TEST(Vector2, operator_addition_assignment)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, Vector2>> test_cases{
        {{0, 0}, {1, 1}},
        {{1, 0}, {2, 1}},
        {{0, 1}, {1, 2}},
        {{1, 1}, {2, 2}},
    };

    for (const auto& pair : test_cases)
    {
        Vector2 vector{initial_vector};
        vector += pair.first;
        ASSERT_THAT(vector, Eq(pair.second));
    }
}

TEST(Vector2, operator_subtraction_assignment)
{
    const Vector2 initial_vector{1, 1};
    const vector<pair<Vector2, Vector2>> test_cases{
        {{0, 0}, {1, 1}},
        {{1, 0}, {0, 1}},
        {{0, 1}, {1, 0}},
        {{1, 1}, {0, 0}},
    };

    for (const auto& pair : test_cases)
    {
        Vector2 vector{initial_vector};
        vector -= pair.first;
        ASSERT_THAT(vector, Eq(pair.second));
    }
}
