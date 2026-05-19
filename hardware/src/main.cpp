#include <Arduino.h>

#include <joystick.hpp>
#include <rotary_encoder.hpp>
#include <buttons.hpp>
#include <utils.hpp>
#include <data_constants.hpp>

Joystick joystick(A2, A4, 13);
RotaryEncoder rotary_encoder(3, 2);
Buttons btns(4, 5, 6, 7, 8);
data_unit slider_val;

data_unit prev_data[DATA_SIZE] = {};
data_unit data[DATA_SIZE] = {};

void setup()
{
  Serial.begin(9600);
  joystick.setup();
  rotary_encoder.setup();

  pinMode(SLIDER_PIN, INPUT);
}

void fill_data()
{
  // data[BUTTON_IDX] = btns.encode_data(joystick);
  data[X_IDX] = joystick.x;
  data[Y_IDX] = joystick.y;
  // data[SCROLL_IDX] = rotary_encoder.val;
  // data[SLIDER_IDX] = slider_val;
}

void loop()
{
  delay(50);

  joystick.update();
  rotary_encoder.update();
  btns.update();
  slider_val = read_slider();

  fill_data();

  if (should_send(data, prev_data))
  {
    size_t size = DATA_SIZE * sizeof(data_unit);
    Serial.write(data, size);
    memcpy(prev_data, data, size);
  }
  else
  {
    delay(150);
  }
}
