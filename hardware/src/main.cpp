#include <Arduino.h>
#include <ezButton.h>

#include <joystick.hpp>
#include <rotary_encoder.hpp>

auto joystick = Joystick(A2, A4, A1);
auto rotaryEncoder = RotaryEncoder(3, 2);

void setup()
{
  Serial.begin(9600);
  joystick.setup();
  rotaryEncoder.setup();
}

void loop()
{
  joystick.loop();

  Serial.print("a: ");
  Serial.println(digitalRead(2));
  Serial.print("b: ");
  Serial.println(digitalRead(3));
  Serial.println(rotaryEncoder.readVal());

  delay(100);
}
