#pragma once

#include <ge211.hxx>
#include <vector>
#include <block.hxx>
#include <board.hxx>
#include <queue>

struct Model {

    explicit Model();

    int const qb_pos = 12;

    int const qb_pos_y = 16;

    int const board_height = 19;

    double const original_speed = 0.75;

    using Dimensions = board::Dimensions;

    /// Model positions will use `int` coordinates, as board positions do.
    using Position = board::Position;

    /// Model rectangles will use `int` coordinates, as board rectangles do.
    using Rectangle = board::Rectangle;

    ge211::Random_source<int> block_num;

    int on_hold;

    int queue[3];

    block hold_block;

    int current_block;

    block block_;

    std::queue<block> queue_block;

    void hold();

    void move_left();

    void move_right();

    void rotate_cw();

    void rotate_ccw();

    void new_block();

    void fast_fall();

    void on_frame(double dt);

    void drop();

    void s_drop();

    board board_;

    double t;

    double speed;

    void reset_fall();

    void update_board();

    void gameover();

    bool gamelive;

    double temp_speed;

    int lines_cleared;

    int level;
};
