#include <Arduino.h>
#include <ezButton.h>

#define SW A1
#define Y A4
#define X A2

#define MOUSE_SENSITIVITY 100 // output range of X or Y movement
#define responseDelay 5       // response delay of the mouse, in ms
#define minA 0
#define maxA 1023
#define threshold MOUSE_SENSITIVITY / 10 // resting threshold

ezButton button(SW, INPUT_PULLUP);
int readAxis(int thisAxis);
void setup()
{
  Serial.begin(9600);
  pinMode(X, INPUT);
  pinMode(Y, INPUT);
  button.setDebounceTime(50);
}

int x = 0;
int y = 0;

void loop()
{
  button.loop();
  int bValue = button.getState();

  x = readAxis(X);
  y = readAxis(Y);

  Serial.print(x);
  Serial.print(":");
  Serial.print(y);
  Serial.print(":");
  Serial.println(bValue);

  delay(50);
}

int readAxis(int thisAxis)
{
  int reading = analogRead(thisAxis);
  reading = map(reading, minA, maxA, -MOUSE_SENSITIVITY, MOUSE_SENSITIVITY);

  if (abs(reading) < threshold)
  {
    reading = 0;
  }

  return reading;
}