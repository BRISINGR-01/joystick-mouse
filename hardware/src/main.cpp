#include <Arduino.h>

#include <joystick.hpp>
#include <rotary_encoder.hpp>
#include <buttons.hpp>
#include <utils.hpp>
#include <data_constants.hpp>

Joystick joystick(A2, A4, 13);
RotaryEncoder rotaryEncoder(3, 2);
Buttons btns(4, 5, 6, 7, 8);
data_unit slider_val;

data_unit prev_data[DATA_SIZE] = {};
data_unit data[DATA_SIZE] = {};

void setup()
{
  Serial.begin(9600);
  joystick.setup();
  rotaryEncoder.setup();

  pinMode(SLIDER_PIN, INPUT);
}

void fill_data()
{
  data[BUTTON_IDX] = btns.encode_data(joystick);
  data[X_IDX] = joystick.x;
  data[Y_IDX] = joystick.y;
  data[SCROLL_IDX] = rotaryEncoder.val;
  data[SLIDER_IDX] = slider_val;
}

void loop()
{
  delay(100);

  joystick.update();
  rotaryEncoder.update();
  btns.update();
  slider_val = read_slider();

  fill_data();

  if (is_equal(prev_data, data))
  {
    return;
  }

  size_t size = DATA_SIZE * sizeof(data_unit);
  Serial.write(data, size);
  memcpy(prev_data, data, size);
}
