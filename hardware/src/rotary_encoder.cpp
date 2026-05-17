#include <rotary_encoder.hpp>

int aPin = 0;
int bPin = 0;
volatile int encoderCount = 0;

RotaryEncoder::RotaryEncoder(int a, int b) : val(0)
{
    aPin = a;
    bPin = b;
}

void handleEncoderInterrupt()
{
    static int lastState = 0;
    uint8_t state = (digitalRead(aPin) << 1) | digitalRead(bPin);

    if ((lastState == 0b00 && state == 0b01) ||
        (lastState == 0b01 && state == 0b11) ||
        (lastState == 0b11 && state == 0b10) ||
        (lastState == 0b10 && state == 0b00))
    {
        encoderCount++;
    }
    else if ((lastState == 0b00 && state == 0b10) ||
             (lastState == 0b10 && state == 0b11) ||
             (lastState == 0b11 && state == 0b01) ||
             (lastState == 0b01 && state == 0b00))
    {
        encoderCount--;
    }

    lastState = state;
}

void RotaryEncoder::setup()
{
    pinMode(aPin, INPUT_PULLUP);
    pinMode(bPin, INPUT_PULLUP);
    int a = digitalPinToInterrupt(aPin);
    int b = digitalPinToInterrupt(bPin);

    if (a == -1 || b == -1)
    {
        Serial.println("Pin A or B is not avaliable as interrupt pin");
        exit(1);
    }

    attachInterrupt(a, handleEncoderInterrupt, CHANGE);
    attachInterrupt(b, handleEncoderInterrupt, CHANGE);
}

void RotaryEncoder::update()
{
    val = constrain(encoderCount, -127, 127);
    encoderCount = 0;
}
