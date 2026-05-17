#pragma once

#define DATA_SIZE 5

typedef char data_unit;

#define BUTTON_COUNT 5
#define LEFT_IDX 0
#define RIGHT_IDX 1
#define MIDDLE_IDX 2
#define FORWARD_IDX 3
#define BACKWARD_IDX 4
// The values of each button represent to which bit in the data stream it corresponds
enum Button
{
    LEFT = 1,
    RIGHT = 2,
    MIDDLE = 4,
    FORWARD = 8,
    BACKWARD = 16
};

// Data stream: char data[DATA_SIZE]
//  buttons  x move   y move   scroll   slider
// 00010101 00000010 00010100 00000000 00010100
#define BUTTON_IDX 0
#define X_IDX 1
#define Y_IDX 2
#define SCROLL_IDX 3
#define SLIDER_IDX 4
