#include <Arduino.h>
#include <ezButton.h>

#include <joystick.hpp>
#include <rotary_encoder.hpp>

#define SLIDER_PIN -1 // must be analog
#define SLIDER_MAX 2024

Joystick joystick(A2, A4, A1);
RotaryEncoder rotaryEncoder(3, 2);

ezButton left(-1, INPUT_PULLUP);
ezButton right(-1, INPUT_PULLUP);
ezButton middle(-1, INPUT_PULLUP);
ezButton forward(-1, INPUT_PULLUP);
ezButton backword(-1, INPUT_PULLUP);

ezButton btns[5] = {left, right, middle, forward, backword};

void setup()
{
  Serial.begin(9600);
  joystick.setup();
  rotaryEncoder.setup();

  pinMode(SLIDER_PIN, INPUT);
}

void send_data()
{
}

int read_slider()
{
  return map(analogRead(SLIDER_PIN), 0, SLIDER_MAX, 0, 256);
}

void loop()
{
  joystick.loop();
  int slider_val = read_slider();
  delay(100);
}
