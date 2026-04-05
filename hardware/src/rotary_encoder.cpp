#include <rotary_encoder.hpp>

int aPin = 0;
int bPin = 0;
volatile int encoderCount = 0;

RotaryEncoder::RotaryEncoder(int a, int b)
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
    attachInterrupt(digitalPinToInterrupt(aPin), handleEncoderInterrupt, CHANGE);
    attachInterrupt(digitalPinToInterrupt(bPin), handleEncoderInterrupt, CHANGE);
    Serial.begin(9600);
}

int RotaryEncoder::readVal()
{
    return encoderCount;
}

// https://pcb-copy.com/mouse-rotary-encoder-the-working-principle-and-how-to-connect-it-with-the-arduino/
