#include "board.hxx"
#include <ge211.hxx>
#include <vector>

struct block {
    using Dimensions = ge211::Dims<int>;

    using Position = ge211::Posn<int>;

    using Direction = std::vector<Dimensions>;

    block(Position center, int block_type);

    void rotate_cw();

    void rotate_ccw();

    void move_left();

    void move_right();

    block next_pos(double dt) const;

    Position center;

    Direction dir;

    int block_type;

    std::vector<Direction> block_set =
            {
             {{-1, 0}, {1, 0},
             {2, 0}}, // long block

             {{-1, 0}, {0, -1}, {1, 0}},
             //tetris block

             {{-1, 0}, {0, -1}, {1, -1}},
             //S block

             {{1, 0}, {0, -1}, {-1, -1}},
             //reverse S block

             {{-1, 0}, {1, 0}, {1, -1}},
             //L block

             {{-1, 0}, {1, 0}, {-1, -1}},
             //reverse L block

             {{0, -1}, {1, -1}, {1, 0}}
             //square
             };
};