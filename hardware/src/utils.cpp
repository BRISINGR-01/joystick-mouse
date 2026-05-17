#include <Arduino.h>
#include <utils.hpp>
#include <data_constants.hpp>

int read_slider()
{
    return map(analogRead(SLIDER_PIN), 0, SLIDER_MAX, 0, 100); // must fit in a char
}

bool is_equal(data_unit *prev_data, data_unit *data)
{
    for (size_t i = 0; i < DATA_SIZE; i++)
    {
        if (data[i] != prev_data[i])
        {
            return false;
        }
    }

    return true;
}
