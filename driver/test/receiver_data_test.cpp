#include <gtest/gtest.h>
#include <receiver.hpp>
#include <constants.hpp>

class ReceiverDataTest : public ::testing::Test
{
protected:
    Receiver::Data data;
};

TEST_F(ReceiverDataTest, DefaultInitializationIsZero)
{
    EXPECT_EQ(Receiver::Data().data[0], 0);
    EXPECT_EQ(Receiver::Data().data[X_IDX], 0);
    EXPECT_EQ(Receiver::Data().data[Y_IDX], 0);
    EXPECT_EQ(Receiver::Data().data[SCROLL_IDX], 0);
    EXPECT_EQ(Receiver::Data().data[SLIDER_IDX], 0);
}

TEST_F(ReceiverDataTest, SetCopiesAllBytes)
{
    data_unit buf[DATA_SIZE] = {5, 10, 20, 30, 40};
    data.set(buf);
    EXPECT_EQ(data.data[0], 5);
    EXPECT_EQ(data.data[1], 10);
    EXPECT_EQ(data.data[2], 20);
    EXPECT_EQ(data.data[3], 30);
    EXPECT_EQ(data.data[4], 40);
}

TEST_F(ReceiverDataTest, GetXReturnsCorrectIndex)
{
    data_unit buf[DATA_SIZE] = {0, 42, 0, 0, 0};
    data.set(buf);
    EXPECT_EQ(data.get_x(), 42);
}

TEST_F(ReceiverDataTest, GetYReturnsCorrectIndex)
{
    data_unit buf[DATA_SIZE] = {0, 0, -15, 0, 0};
    data.set(buf);
    EXPECT_EQ(data.get_y(), -15);
}

TEST_F(ReceiverDataTest, GetScrollReturnsCorrectIndex)
{
    data_unit buf[DATA_SIZE] = {0, 0, 0, 7, 0};
    data.set(buf);
    EXPECT_EQ(data.get_scroll(), 7);
}

TEST_F(ReceiverDataTest, GetSensitivityReturnsCorrectIndex)
{
    data_unit buf[DATA_SIZE] = {0, 0, 0, 0, 100};
    data.set(buf);
    EXPECT_EQ(data.get_sensitivity(), 100);
}

TEST_F(ReceiverDataTest, IsBtnPressedLeft)
{
    data_unit buf[DATA_SIZE] = {1, 0, 0, 0, 0};
    data.set(buf);
    EXPECT_TRUE(data.is_btn_pressed(Button::LEFT));
    EXPECT_FALSE(data.is_btn_pressed(Button::RIGHT));
}

TEST_F(ReceiverDataTest, IsBtnPressedRight)
{
    data_unit buf[DATA_SIZE] = {2, 0, 0, 0, 0};
    data.set(buf);
    EXPECT_TRUE(data.is_btn_pressed(Button::RIGHT));
    EXPECT_FALSE(data.is_btn_pressed(Button::LEFT));
}

TEST_F(ReceiverDataTest, IsBtnPressedMultiple)
{
    data_unit buf[DATA_SIZE] = {3, 0, 0, 0, 0};
    data.set(buf);
    EXPECT_TRUE(data.is_btn_pressed(Button::LEFT));
    EXPECT_TRUE(data.is_btn_pressed(Button::RIGHT));
    EXPECT_FALSE(data.is_btn_pressed(Button::MIDDLE));
}

TEST_F(ReceiverDataTest, IsBtnPressedAll)
{
    data_unit buf[DATA_SIZE] = {31, 0, 0, 0, 0};
    data.set(buf);
    EXPECT_TRUE(data.is_btn_pressed(Button::LEFT));
    EXPECT_TRUE(data.is_btn_pressed(Button::RIGHT));
    EXPECT_TRUE(data.is_btn_pressed(Button::MIDDLE));
    EXPECT_TRUE(data.is_btn_pressed(Button::FORWARD));
    EXPECT_TRUE(data.is_btn_pressed(Button::BACKWARD));
}

TEST_F(ReceiverDataTest, IsBtnPressedNone)
{
    data_unit buf[DATA_SIZE] = {0, 0, 0, 0, 0};
    data.set(buf);
    EXPECT_FALSE(data.is_btn_pressed(Button::LEFT));
    EXPECT_FALSE(data.is_btn_pressed(Button::RIGHT));
    EXPECT_FALSE(data.is_btn_pressed(Button::MIDDLE));
    EXPECT_FALSE(data.is_btn_pressed(Button::FORWARD));
    EXPECT_FALSE(data.is_btn_pressed(Button::BACKWARD));
}
