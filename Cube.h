#pragma once

#include <cstdint>
#include <initializer_list>
#include "RingSet.h"

// Store the values in the ring (in order)
// 4bits per value (32bits total) - value from 0 to 7 (maps to 1 to 8)
typedef uint32_t Ring;

Ring rot_cw(Ring ring);
Ring rot_ccw(Ring ring);

char idx(Ring ring, int index);

// Move type
enum class RotationType : uint8_t
{
    LEFT_CW, LEFT_CCW,
    RIGHT_CW, RIGHT_CCW,
    UP_CW, UP_CCW,
    DOWN_CW, DOWN_CCW,
    FRONT_CW, FRONT_CCW,
    BACK_CW, BACK_CCW,
};

struct Face
{
    char tl=0, tr=0, bl=0, br=0;
};

// Cube consists of x0, x1, y0, y1, z0, z1 rings
// Rings start at top/left of front/right/top, go down
struct Cube
{
    Face up, down, left, right, front, back;
    Ring x0=0, x1=0, y0=0, y1=0, z0=0, z1=0;
    RingSet sx0, sx1, sy0, sy1, sz0, sz1;
};

Ring make_ring(std::initializer_list<char> vals);

Cube from_x0(Cube cube);
Cube from_x1(Cube cube);
Cube from_y0(Cube cube);
Cube from_y1(Cube cube);
Cube from_z0(Cube cube);
Cube from_z1(Cube cube);

Cube update_x(Cube cube);
Cube update_y(Cube cube);
Cube update_z(Cube cube);

Cube move(Cube cube, RotationType type);
bool solved(Cube cube);
void print(Cube cube);