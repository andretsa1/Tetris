#include "block.hxx"

using namespace ge211;


block::block(Position c, int type)
        : center(c), block_type(type)
{
    dir = block_set[block_type];
}


void
block::rotate_ccw()
{
    //width * -1 = new height
    //height * 1 = new width
    int temp = 0;
    for (size_t i = 0; i < dir.size(); i++) {
        temp = dir[i].height;
        dir[i].height = dir[i].width * (-1);
        dir[i].width = temp;
    }
}

void
block::rotate_cw()
{
    //width * 1 = new height
    //height * -1 = new width
    int temp = 0;
    for (size_t i = 0; i < dir.size(); i++) {
        temp = dir[i].height;
        dir[i].height = dir[i].width;
        dir[i].width = temp * (-1);
    }
}

block
block::next_pos(double dt) const
{
    block result(*this);
    result.center.y = result.center.y + 1;

    return result;
}

void
block::move_right()
{
    center.x = center.x + 1;
}

void
block::move_left()
{
    center.x = center.x - 1;
}
