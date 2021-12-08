#include "Cube.h"
#include <cassert>
#include <cstdio>

Ring ror(Ring ring)
{
    // need rotation, not just truncated shift
    asm("ror $8, %0" : "+r" (ring));
    return ring;
}

Ring rol(Ring ring)
{
    // need rotation, not just truncated shift
    asm("rol $8, %0" : "+r" (ring));
    return ring;
}

Face rot_cw(Face face)
{
    Face newFace = face;
    newFace.tl = face.bl;
    newFace.tr = face.tl;
    newFace.br = face.tr;
    newFace.bl = face.br;
    return newFace;
}

Face rot_ccw(Face face)
{
    Face newFace = face;
    newFace.bl = face.tl;
    newFace.tl = face.tr;
    newFace.br = face.bl;
    newFace.tr = face.br;
    return newFace;
}

char idx(Ring ring, int index)
{
    return (ring >> ((7 - index) * 4)) & 0xF;
}

Ring make_ring(std::initializer_list<char> vals)
{
    Ring out = 0;
    for (char val : vals)
    {
        out <<= 4;
        out |= (val & 0xF);
    }
    return out;
}

// bool solved(Cube cube)
// {
//     return solved(cube.sx0) && solved(cube.sx1) && solved(cube.sy0) && solved(cube.sy1) && solved(cube.sz0) && solved(cube.sz1);
// }

// Ring updates

Cube update_x(Cube cube)
{
    Cube newCube = cube;
    
    // Update X (from face)
    newCube.x0 = make_ring({
        cube.front.tl, cube.front.bl, cube.down.tl, cube.down.bl, cube.back.br, cube.back.tr, cube.up.tl, cube.up.bl
    });
    newCube.x1 = make_ring({
        cube.front.tr, cube.front.br, cube.down.tr, cube.down.br, cube.back.bl, cube.back.tl, cube.up.tr, cube.up.br
    });

    return newCube;
}

Cube update_y(Cube cube)
{
    Cube newCube = cube;
    
    // Update Y (from face)
    newCube.y0 = make_ring({
        cube.front.tl, cube.front.tr, cube.right.tl, cube.right.tr, cube.back.tl, cube.back.tr, cube.left.tl, cube.left.tr
    });
    newCube.y1 = make_ring({
        cube.front.bl, cube.front.br, cube.right.bl, cube.right.br, cube.back.bl, cube.back.br, cube.left.bl, cube.left.br
    });

    return newCube;
}

Cube update_z(Cube cube)
{
    Cube newCube = cube;
    
    // Update Z (from face)
    newCube.z0 = make_ring({
        cube.up.tl, cube.up.tr, cube.right.tr, cube.right.br, cube.down.br, cube.down.bl, cube.left.bl, cube.left.tl
    });
    newCube.z1 = make_ring({
        cube.up.bl, cube.up.br, cube.right.tl, cube.right.bl, cube.down.tr, cube.down.tl, cube.left.br, cube.left.tr
    });

    return newCube;
}

// Face updates

Cube from_x0(Cube cube)
{
    Cube newCube = cube;

    // cube.front.tl, cube.front.bl, cube.down.tl, cube.down.bl, cube.back.br, cube.back.tr, cube.up.tl, cube.up.bl

    newCube.front.tl = idx(cube.x0, 0);
    newCube.front.bl = idx(cube.x0, 1);
    newCube.down.tl = idx(cube.x0, 2);
    newCube.down.bl = idx(cube.x0, 3);
    newCube.back.br = idx(cube.x0, 4);
    newCube.back.tr = idx(cube.x0, 5);
    newCube.up.tl = idx(cube.x0, 6);
    newCube.up.bl = idx(cube.x0, 7);

    return newCube;
}

Cube from_x1(Cube cube)
{
    Cube newCube = cube;

    newCube.front.tr = idx(cube.x1, 0);
    newCube.front.br = idx(cube.x1, 1);
    newCube.down.tr = idx(cube.x1, 2);
    newCube.down.br = idx(cube.x1, 3);
    newCube.back.bl = idx(cube.x1, 4);
    newCube.back.tl = idx(cube.x1, 5);
    newCube.up.tr = idx(cube.x1, 6);
    newCube.up.br = idx(cube.x1, 7);

    return newCube;
}

Cube from_y0(Cube cube)
{
    Cube newCube = cube;

    // cube.front.tl, cube.front.tr, cube.right.tl, cube.right.tr, cube.back.tl, cube.back.tr, cube.left.tl, cube.left.tr

    newCube.front.tl = idx(cube.y0, 0);
    newCube.front.tr = idx(cube.y0, 1);
    newCube.right.tl = idx(cube.y0, 2);
    newCube.right.tr = idx(cube.y0, 3);
    newCube.back.tl = idx(cube.y0, 4);
    newCube.back.tr = idx(cube.y0, 5);
    newCube.left.tl = idx(cube.y0, 6);
    newCube.left.tr = idx(cube.y0, 7);

    return newCube;
}

Cube from_y1(Cube cube)
{
    Cube newCube = cube;

    newCube.front.bl = idx(cube.y1, 0);
    newCube.front.br = idx(cube.y1, 1);
    newCube.right.bl = idx(cube.y1, 2);
    newCube.right.br = idx(cube.y1, 3);
    newCube.back.bl = idx(cube.y1, 4);
    newCube.back.br = idx(cube.y1, 5);
    newCube.left.bl = idx(cube.y1, 6);
    newCube.left.br = idx(cube.y1, 7);

    return newCube;
}

Cube from_z0(Cube cube)
{
    Cube newCube = cube;

    // cube.up.tl, cube.up.tr, cube.right.tr, cube.right.br, cube.down.br, cube.down.bl, cube.left.bl, cube.left.tl

    newCube.up.tl = idx(cube.z0, 0);
    newCube.up.tr = idx(cube.z0, 1);
    newCube.right.tr = idx(cube.z0, 2);
    newCube.right.br = idx(cube.z0, 3);
    newCube.down.br = idx(cube.z0, 4);
    newCube.down.bl = idx(cube.z0, 5);
    newCube.left.bl = idx(cube.z0, 6);
    newCube.left.tl = idx(cube.z0, 7);

    return newCube;
}

Cube from_z1(Cube cube)
{
    Cube newCube = cube;

    newCube.up.bl = idx(cube.z1, 0);
    newCube.up.br = idx(cube.z1, 1);
    newCube.right.tl = idx(cube.z1, 2);
    newCube.right.bl = idx(cube.z1, 3);
    newCube.down.tr = idx(cube.z1, 4);
    newCube.down.tl = idx(cube.z1, 5);
    newCube.left.br = idx(cube.z1, 6);
    newCube.left.tr = idx(cube.z1, 7);

    return newCube;
}

// TRUE MOVES

Cube up_cw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.y0 = rol(newCube.y0);
    // Face rotate
    newCube.up = rot_cw(newCube.up);
    // Face update
    newCube = from_y0(newCube);
    // Ring updates
    newCube = update_x(newCube);
    newCube = update_z(newCube);
    // Return cube
    return newCube;
}

Cube up_ccw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.y0 = ror(newCube.y0);
    // Face rotate
    newCube.up = rot_ccw(newCube.up);
    // Face update
    newCube = from_y0(newCube);
    // Ring updates
    newCube = update_x(newCube);
    newCube = update_z(newCube);
    // Return cube
    return newCube;
}

Cube down_cw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.y1 = ror(newCube.y1);
    // Face rotate
    newCube.down = rot_cw(newCube.down);
    // Face update
    newCube = from_y1(newCube);
    // Ring updates
    newCube = update_x(newCube);
    newCube = update_z(newCube);
    // Return cube
    return newCube;
}

Cube down_ccw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.y1 = rol(newCube.y1);
    // Face rotate
    newCube.down = rot_ccw(newCube.down);
    // Face update
    newCube = from_y1(newCube);
    // Ring updates
    newCube = update_x(newCube);
    newCube = update_z(newCube);
    // Return cube
    return newCube;
}

Cube left_cw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.x0 = ror(newCube.x0);
    // Face rotate
    newCube.left = rot_cw(newCube.left);
    // Face update
    newCube = from_x0(newCube);
    // Ring updates
    newCube = update_y(newCube);
    newCube = update_z(newCube);
    // Return cube
    return newCube;
}

Cube left_ccw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.x0 = rol(newCube.x0);
    // Face rotate
    newCube.left = rot_ccw(newCube.left);
    // Face update
    newCube = from_x0(newCube);
    // Ring updates
    newCube = update_y(newCube);
    newCube = update_z(newCube);
    // Return cube
    return newCube;
}

Cube right_cw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.x1 = rol(newCube.x1);
    // Face rotate
    newCube.right = rot_cw(newCube.right);
    // Face update
    newCube = from_x1(newCube);
    // Ring updates
    newCube = update_y(newCube);
    newCube = update_z(newCube);
    // Return cube
    return newCube;
}

Cube right_ccw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.x1 = ror(newCube.x1);
    // Face rotate
    newCube.right = rot_ccw(newCube.right);
    // Face update
    newCube = from_x1(newCube);
    // Ring updates
    newCube = update_y(newCube);
    newCube = update_z(newCube);
    // Return cube
    return newCube;
}

Cube front_cw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.z1 = ror(newCube.z1);
    // Face rotate
    newCube.front = rot_cw(newCube.front);
    // Face update
    newCube = from_z1(newCube);
    // Ring updates
    newCube = update_y(newCube);
    newCube = update_x(newCube);
    // Return cube
    return newCube;
}

Cube front_ccw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.z1 = rol(newCube.z1);
    // Face rotate
    newCube.front = rot_ccw(newCube.front);
    // Face update
    newCube = from_z1(newCube);
    // Ring updates
    newCube = update_y(newCube);
    newCube = update_x(newCube);
    // Return cube
    return newCube;
}

Cube back_cw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.z0 = rol(newCube.z0);
    // Face rotate
    newCube.back = rot_cw(newCube.back);
    // Face update
    newCube = from_z0(newCube);
    // Ring updates
    newCube = update_y(newCube);
    newCube = update_x(newCube);
    // Return cube
    return newCube;
}

Cube back_ccw(Cube cube)
{
    Cube newCube = cube;
    // Ring rotate
    newCube.z0 = ror(newCube.z0);
    // Face rotate
    newCube.back = rot_ccw(newCube.back);
    // Face update
    newCube = from_z0(newCube);
    // Ring updates
    newCube = update_y(newCube);
    newCube = update_x(newCube);
    // Return cube
    return newCube;
}

Cube move(Cube cube, RotationType type)
{
    switch (type)
    {
    case RotationType::UP_CW:
        return up_cw(cube);
    case RotationType::UP_CCW:
        return up_ccw(cube);
    case RotationType::DOWN_CW:
        return down_cw(cube);
    case RotationType::DOWN_CCW:
        return down_ccw(cube);
    case RotationType::FRONT_CW:
        return front_cw(cube);
    case RotationType::FRONT_CCW:
        return front_ccw(cube);
    case RotationType::BACK_CW:
        return back_cw(cube);
    case RotationType::BACK_CCW:
        return back_ccw(cube);
    case RotationType::LEFT_CW:
        return left_cw(cube);
    case RotationType::LEFT_CCW:
        return left_ccw(cube);
    case RotationType::RIGHT_CW:
        return right_cw(cube);
    case RotationType::RIGHT_CCW:
        return right_ccw(cube);
    default:
        assert(0);
        return cube;
    }
}

void print(Cube cube)
{
    /*
        U U
        U U
    L L F F R R B B
    L L F F R R B B
        D D
        D D
    */

    printf("    %d %d\n", cube.up.tl, cube.up.tr);
    printf("    %d %d\n", cube.up.bl, cube.up.br);
    printf("%d %d %d %d %d %d %d %d\n", cube.left.tl, cube.left.tr, cube.front.tl, cube.front.tr, cube.right.tl, cube.right.tr, cube.back.tl, cube.back.tr);
    printf("%d %d %d %d %d %d %d %d\n", cube.left.bl, cube.left.br, cube.front.bl, cube.front.br, cube.right.bl, cube.right.br, cube.back.bl, cube.back.br);
    printf("    %d %d\n", cube.down.tl, cube.down.tr);
    printf("    %d %d\n", cube.down.bl, cube.down.br);
}