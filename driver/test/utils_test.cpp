#include <gtest/gtest.h>
#include <utils.hpp>

TEST(UtilsTest, FillCopiesBytesAndReturnsTrueWhenComplete)
{
    data_unit dest[DATA_SIZE] = {};
    data_unit buf[] = {10, 20, 30, 40, 50};
    bool result = fill(5, 0, buf, dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest[0], 10);
    EXPECT_EQ(dest[1], 20);
    EXPECT_EQ(dest[2], 30);
    EXPECT_EQ(dest[3], 40);
    EXPECT_EQ(dest[4], 50);
}

TEST(UtilsTest, FillPartialReturnsFalse)
{
    data_unit dest[DATA_SIZE] = {};
    data_unit buf[] = {10, 20};
    bool result = fill(2, 0, buf, dest);
    EXPECT_FALSE(result);
    EXPECT_EQ(dest[0], 10);
    EXPECT_EQ(dest[1], 20);
    EXPECT_EQ(dest[2], 0);
}

TEST(UtilsTest, FillWithOffsetCompletesAccumulatedData)
{
    data_unit dest[DATA_SIZE] = {1, 2, 3, 0, 0};
    data_unit buf[] = {40, 50};
    bool result = fill(2, 3, buf, dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest[0], 1);
    EXPECT_EQ(dest[1], 2);
    EXPECT_EQ(dest[2], 3);
    EXPECT_EQ(dest[3], 40);
    EXPECT_EQ(dest[4], 50);
}

TEST(UtilsTest, FillRespectsDataSizeBoundary)
{
    data_unit dest[DATA_SIZE] = {};
    data_unit buf[] = {1, 2, 3, 4, 5, 6, 7};
    bool result = fill(7, 0, buf, dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest[0], 1);
    EXPECT_EQ(dest[1], 2);
    EXPECT_EQ(dest[2], 3);
    EXPECT_EQ(dest[3], 4);
    EXPECT_EQ(dest[4], 5);
}

TEST(UtilsTest, FillWithOffsetBeyondDataSize)
{
    data_unit dest[DATA_SIZE] = {1, 2, 3, 4, 5};
    data_unit buf[] = {99};
    bool result = fill(1, 5, buf, dest);
    EXPECT_TRUE(result);
    EXPECT_EQ(dest[0], 1);
    EXPECT_EQ(dest[1], 2);
    EXPECT_EQ(dest[2], 3);
    EXPECT_EQ(dest[3], 4);
    EXPECT_EQ(dest[4], 5);
}

TEST(UtilsTest, GetBtnReturnsCorrectEnum)
{
    EXPECT_EQ(get_btn(LEFT_IDX), Button::LEFT);
    EXPECT_EQ(get_btn(RIGHT_IDX), Button::RIGHT);
    EXPECT_EQ(get_btn(MIDDLE_IDX), Button::MIDDLE);
    EXPECT_EQ(get_btn(FORWARD_IDX), Button::FORWARD);
    EXPECT_EQ(get_btn(BACKWARD_IDX), Button::BACKWARD);
}

TEST(UtilsTest, GetBtnReturnsMinusOneForInvalid)
{
    EXPECT_EQ(get_btn(-1), (Button)-1);
    EXPECT_EQ(get_btn(99), (Button)-1);
}

TEST(UtilsTest, GetBtnDebugReturnsCorrectString)
{
    EXPECT_EQ(get_btn_debug(LEFT_IDX), "LEFT");
    EXPECT_EQ(get_btn_debug(RIGHT_IDX), "RIGHT");
    EXPECT_EQ(get_btn_debug(MIDDLE_IDX), "MIDDLE");
    EXPECT_EQ(get_btn_debug(FORWARD_IDX), "FORWARD");
    EXPECT_EQ(get_btn_debug(BACKWARD_IDX), "BACKWARD");
}

TEST(UtilsTest, GetBtnDebugReturnsNumberForInvalid)
{
    EXPECT_EQ(get_btn_debug(-1), "-1");
    EXPECT_EQ(get_btn_debug(99), "99");
}
