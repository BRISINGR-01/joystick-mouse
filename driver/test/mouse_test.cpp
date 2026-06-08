#include <gtest/gtest.h>
#include <mouse.hpp>
#include <constants.hpp>

#include <vector>

struct Event
{
    enum Type
    {
        MOVE,
        SCROLL,
        PRESS,
        RELEASE
    };
    Type type;
    int x, y;
    Button btn;
    int val;
};

class MockEventInterface : public EventInterface
{
public:
    std::vector<Event> events;

    void send_move_event(int x, int y) override
    {
        events.push_back({Event::MOVE, x, y, (Button)0, 0});
    }

    void send_scroll_event(int val) override
    {
        events.push_back({Event::SCROLL, 0, 0, (Button)0, val});
    }

    void send_press_event(Button btn) override
    {
        events.push_back({Event::PRESS, 0, 0, btn, 0});
    }

    void send_release_event(Button btn) override
    {
        events.push_back({Event::RELEASE, 0, 0, btn, 0});
    }
};

class MouseTest : public ::testing::Test
{
protected:
    MockEventInterface *mock;
    std::unique_ptr<Mouse> mouse;

    void SetUp() override
    {
        auto ptr = std::make_unique<MockEventInterface>();
        mock = ptr.get();
        mouse = std::make_unique<Mouse>(std::move(ptr));
        mouse->set_sensitivity(5);
    }
};

TEST_F(MouseTest, ChangeSensitivity)
{
    mouse->set_sensitivity(1.0);
    ASSERT_EQ(mock->events.size(), 1);
    EXPECT_EQ(mock->events[0].type, Event::SCROLL);
    EXPECT_EQ(mock->events[0].val, 5);
}

TEST_F(MouseTest, ScrollSendsEvent)
{
    mouse->scroll(5);
    ASSERT_EQ(mock->events.size(), 1);
    EXPECT_EQ(mock->events[0].type, Event::SCROLL);
    EXPECT_EQ(mock->events[0].val, 5);
}

TEST_F(MouseTest, ScrollSendsEventNegative)
{
    mouse->scroll(-3);
    ASSERT_EQ(mock->events.size(), 1);
    EXPECT_EQ(mock->events[0].type, Event::SCROLL);
    EXPECT_EQ(mock->events[0].val, -3);
}

TEST_F(MouseTest, PressSendsEvent)
{
    mouse->press(Button::LEFT);
    ASSERT_EQ(mock->events.size(), 1);
    EXPECT_EQ(mock->events[0].type, Event::PRESS);
    EXPECT_EQ(mock->events[0].btn, Button::LEFT);
}

TEST_F(MouseTest, PressAllButtons)
{
    Button buttons[] = {Button::LEFT, Button::RIGHT, Button::MIDDLE, Button::FORWARD, Button::BACKWARD};

    for (auto btn : buttons)
    {
        mock->events.clear();
        mouse->press(btn);
        ASSERT_EQ(mock->events.size(), 1) << "Failed for button " << (int)btn;
        EXPECT_EQ(mock->events[0].type, Event::PRESS);
        EXPECT_EQ(mock->events[0].btn, btn);
    }
}

TEST_F(MouseTest, ReleaseSendsEvent)
{
    mouse->release(Button::RIGHT);
    ASSERT_EQ(mock->events.size(), 1);
    EXPECT_EQ(mock->events[0].type, Event::RELEASE);
    EXPECT_EQ(mock->events[0].btn, Button::RIGHT);
}

TEST_F(MouseTest, MoveWithPositiveValues)
{
    mouse->move(10, 10);
    ASSERT_EQ(mock->events.size(), 1);
    auto &ev = mock->events.front();
    EXPECT_EQ(ev.x, 1);
    EXPECT_EQ(ev.y, 1);
}

TEST_F(MouseTest, MoveWithNegativeValues)
{
    mouse->move(-10, -10);
    ASSERT_EQ(mock->events.size(), 1);
    auto &ev = mock->events.front();
    EXPECT_EQ(ev.x, -1);
    EXPECT_EQ(ev.y, -1);
}

TEST_F(MouseTest, MoveWithMixedSigns)
{
    mouse->move(20, -10);
    ASSERT_EQ(mock->events.size(), 1);
    auto &ev = mock->events.front();
    EXPECT_EQ(ev.x, 2);
    EXPECT_EQ(ev.y, -1);
}

TEST_F(MouseTest, MoveZeroSendsOriginEvent)
{
    mouse->move(0, 0);
    ASSERT_EQ(mock->events.size(), 1);
    EXPECT_EQ(mock->events[0].x, 0);
    EXPECT_EQ(mock->events[0].y, 0);
}
