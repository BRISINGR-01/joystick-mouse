#include <data_constants.hpp>

#define SLIDER_PIN A0
#define SLIDER_MAX 1023

int read_slider();

bool should_send(data_unit *prev_data, data_unit *data);
