#include "RingSet.h"
#include "Cube.h"
#include <cstdio>

int main()
{
    Cube cube;
    cube.y0 = make_ring({ 2, 2, 3, 5, 4, 8, 1, 8 });
    cube.y1 = make_ring({ 8, 5, 7, 2, 3, 7, 3, 4 });
    cube.x0 = make_ring({ 2, 8, 5, 6, 7, 8, 7, 1 });
    cube.x1 = make_ring({ 2, 5, 6, 4, 3, 4, 9, 1 });
    // Update faces
    cube = from_y0(cube);
    cube = from_y1(cube);
    cube = from_x0(cube);
    cube = from_x1(cube);
    // Update z ring
    // cube = update_z(cube);
    // Print cube
    print(cube);

    printf("\n\n");

    // Up-CCW

    for (size_t i = 0; i < 100000000; ++i)
    {
        cube = move(cube, RotationType::UP_CCW);
    }

    print(cube);

    return 0;
}