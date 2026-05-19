#include <data_constants.hpp>

#define SLIDER_PIN A0 // must be analog
#define SLIDER_MAX 2024

int read_slider();

bool should_send(data_unit *prev_data, data_unit *data);
