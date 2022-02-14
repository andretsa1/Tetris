#pragma once

#include <ge211.hxx>

#include <unordered_map>
#include <unordered_set>
#include <vector>

/// Represents the state of the board.
struct board
{
    /// Board dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Board positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Board rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    board();

    static int const b_wid = 10;
    static int const b_height = 20;

    bool state[b_height][b_wid];

    int type[b_height][b_height];
};


