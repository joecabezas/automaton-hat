#ifndef SERVO_CELL_INDEXES_H
#define SERVO_CELL_INDEXES_H

signed char SERVO_CELL_INDEXES[15][2] = {
    // center
    {0, 2},

    // left
    {1, 1},
    {1, 2},
    {2, 2},
    {2, 3},
    {3, 2},
    {3, 3},
    {4, 2},

    // right
    {-1, 1},
    {-1, 2},
    {-2, 2},
    {-2, 3},
    {-3, 2},
    {-3, 3},
    {-4, 2},
};

#endif