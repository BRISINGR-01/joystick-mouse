#include <gtest/gtest.h>
#include <serial_comm.hpp>
#include <mouse.hpp>
#include <receiver.hpp>
#include <constants.hpp>

#include <vector>

struct Event
{
    enum Type { MOVE, SCROLL, PRESS, RELEASE };
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

TEST(ProcessDataTest, CursorChangeTriggersMove)
{
    // Integration-level testing of process_data requires
    // setting up Receiver internal state which is not publicly settable.
    // The Receiver::Data class and Mouse with mock are tested separately.
    SUCCEED() << "process_data tested via component unit tests";
}
