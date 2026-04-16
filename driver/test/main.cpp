#include <packet.pb.h>
#include <memory>

std::unique_ptr<joystic_mouse::Package> create_pkg(bool left_btn,
                                                   bool right_btn,
                                                   bool middle_btn,
                                                   bool forward_btn,
                                                   bool backword_btn,

                                                   short int slider,
                                                   signed short int scroll,

                                                   signed short int x_move,
                                                   signed short int y_move)
{
    auto pkg = std::make_unique<joystic_mouse::Package>();

    pkg->set_left_btn(left_btn);
    pkg->set_right_btn(right_btn);
    pkg->set_middle_btn(middle_btn);
    pkg->set_forward_btn(forward_btn);
    pkg->set_backward_btn(backword_btn);
    pkg->set_slider(slider);
    pkg->set_scroll(scroll);
    pkg->set_x_move(x_move);
    pkg->set_y_move(y_move);

    assert(pkg->IsInitialized());

    return pkg;
}

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    auto pkg = create_pkg(false, false, true, false, false, true, 0, 10, 0);

    std::cout << pkg->DebugString() << std::endl;

    google::protobuf::ShutdownProtobufLibrary();
}