#include <Arduino.h>
#include <utils.hpp>
#include <data_constants.hpp>

int read_slider()
{
    return map(analogRead(SLIDER_PIN), 0, SLIDER_MAX, 0, 100); // must fit in a char
}

bool should_send(data_unit *data, data_unit *prev_data)
{
    for (size_t i = 0; i < DATA_SIZE; i++)
    {
        if (i == X_IDX || i == Y_IDX)
        {
            if (data[i] != 0)
                return true;

            continue;
        }

        if (data[i] != prev_data[i])
        {
            return true;
        }
    }

    return false;
}
