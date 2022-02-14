#include "model.hxx"

using namespace ge211;

Model::Model()
    : block_num(0, 6),
      on_hold(block_num.next()),
      hold_block(block({qb_pos, qb_pos_y}, on_hold)),
      current_block(block_num.next()),
      block_(block({4,1}, current_block)),
      t(0),
      speed(original_speed),
      gamelive(true),
      temp_speed(original_speed),
      lines_cleared(0),
      level(1)
{
    for(int i = 0; i < 3; i++) {
        queue[i] = block_num.next();
        queue_block.push(block({qb_pos, 3 * (i+1) - 1}, queue[i]));
    }
}

void
Model::hold() {
    int temp = on_hold;
    on_hold = current_block;
    current_block = temp;
    hold_block = block({qb_pos, qb_pos_y}, on_hold);
    block_ = block({4, 1}, current_block);
}

void
Model::gameover() {
    for (int i = 0; i < board::b_height; i++) {
        for (int j = 0; j < board::b_wid; j++) {
            board_.state[i][j] = true;
            board_.type[i][j] = 7;
        }
    }
    gamelive = false;
}

void
Model::move_left() {
    bool out = false;
    for(size_t i = 0; i < block_.dir.size(); i++) {
        //check if the block touches the bottom
        if(block_.center.x + block_.dir[i].width - 1 < 0) {
            out = true;
        } else if(board_.state[block_.center.y + block_.dir[i].height][block_
        .center.x + block_.dir[i].width - 1]) {
            out = true;
        }
    }
    if(!out) {
        block_.move_left();
    }
}

void
Model::move_right() {
    bool out = false;
    for(size_t i = 0; i < block_.dir.size(); i++) {
        //check if the block touches the bottom
        if(block_.center.x + block_.dir[i].width + 1 > 9) {
            out = true;
        } else if(board_.state[block_.center.y + block_.dir[i].height][block_
        .center.x + block_.dir[i].width + 1]) {
            out = true;
        }
    }

    if(!out) {
        block_.move_right();
    }

}

void
Model::update_board()
{
    bool flag = false;
    for (int i = 0; i < board::b_height; i++) {
        flag = false;
        for (int j = 0; j < board::b_wid; j++) {
            if(!board_.state[i][j]) {
                flag = false;
                break;
            }
            flag = true;
        }
        if (flag) {
            for (int j = 0; j < 10; j++) {
                board_.state[i][j] = false;
            }
            lines_cleared++;

            if (lines_cleared % 10 == 0) {
                temp_speed/=2;
                speed = temp_speed;
                level++;
            }

            for (int k = i; k > 0; k--) {
                for (int j = 0; j < 10; j++) {
                    board_.state[k][j] = board_.state[k-1][j];
                    board_.type[k][j] = board_.type[k-1][j];
                }
            }
        }
    }
}

void
Model::rotate_cw() {
    //block_.rotate_cw();
    bool out = false;

    //Create prospective block to be rotated
    block test = block_;
    test.rotate_cw();
    for(size_t i = 0; i < test.dir.size(); i++) {
        if(test.center.x + test.dir[i].width < 0) {
            // goes off to left
            out = true;
        }
        else if(test.center.x + test.dir[i].width > 9) {
            //goes off to right
            out = true;
        }
        else if(board_.state[test.center.y + test.dir[i].height]
        [test.center.x + test.dir[i].width]) {
            // hits other blocks
            out = true;
        }
    }
    if(!out) {
        block_.rotate_cw();
    }
}

void
Model::rotate_ccw() {
    //
    bool out = false;

    //Create prospective block to be rotated
    block test = block_;
    test.rotate_ccw();
    for(size_t i = 0; i < test.dir.size(); i++) {
        if(test.center.x + test.dir[i].width < 0) {
            // goes off to left
            out = true;
        }
        else if(test.center.x + test.dir[i].width > 9) {
            //goes off to right
            out = true;
        }
        else if(board_.state[test.center.y + test.dir[i].height]
        [test.center.x + test.dir[i].width]) {
            // hits other blocks
            out = true;
        }
    }
    if(!out) {
        block_.rotate_ccw();
    }
}

void
Model::new_block() {
    bool flag = false;
    current_block = queue[0];
    for(int i = 0; i < 2; i++) {
        queue[i] = queue[i+1];
    }
    queue[2] = block_num.next();
    block temp = block({4,1}, current_block);

    for (size_t i = 0; i < block_.dir.size(); i++) {
        if (board_.state[temp.center.y + temp.dir[i].height][temp.center.x +
        temp.dir[i].width]) {
            flag = true;
        }
    }

    if (board_.state[temp.center.y][temp.center.x]) {
        flag = true;
    }

    if(!flag) {
        block_ = block({4,1}, current_block);
        for(int i = 0; i < 3; i++) {
            queue_block.pop();
            queue_block.push(block({qb_pos, 3 * (i+1) - 1}, queue[i]));
        }
    } else {
        gameover();
    }
}


void
Model::s_drop() {
    int ct = 0;
    bool flag = true;
    while(flag && gamelive) {

        for (int i = 0; i < board::b_height; i++) {
            for (int j = 0; j < board::b_wid; j++) {
                if (!board_.state[i][j]) {
                    board_.type[i][j] = 8;
                }
            }
        }

        for (size_t i = 0; i < block_.dir.size(); i++) {
            if(block_.center.y + block_.dir[i].height + ct > board_height ||
               block_.center.y + ct > board_height) {
                for(size_t j = 0; j < block_.dir.size(); j++) {
                    board_.type[block_.center.y + block_.dir[j].height
                    + ct - 1][block_.center.x + block_.dir[j].width] = 7;
                }
                board_.type[block_.center.y + ct - 1][block_.center.x] = 7;
                flag = false;
                break;
            }

            if(board_.state[block_.center.y + block_.dir[i].height + ct][block_
            .center.x + block_.dir[i].width] || board_.state[block_.center.y
            + ct][block_.center.x]) {
                for(size_t j = 0; j < block_.dir.size(); j++) {
                    board_.type[block_.center.y + block_.dir[j].height
                    + ct - 1][block_.center.x + block_.dir[j].width] = 7;
                }
                board_.type[block_.center.y + ct - 1][block_.center.x] = 7;
                flag = false;
                break;
            }
        }
        ct++;
    }

}


void
Model::drop() {
    int ct = 0;
    bool flag = true;
    while(flag && gamelive) {

        for (size_t i = 0; i < block_.dir.size(); i++) {
            //check if the block touches the bottom
            if(block_.center.y + block_.dir[i].height + ct > board_height ||
            block_.center.y + ct > board_height) {
                for(size_t j = 0; j < block_.dir.size(); j++) {

                    board_.state[block_.center.y + block_.dir[j].height
                    + ct - 1][block_.center.x + block_.dir[j].width] = true;

                    board_.type[block_.center.y + block_.dir[j].height
                    + ct - 1][block_.center.x + block_.dir[j].width] = block_
                            .block_type;
                }
                board_.state[block_.center.y + ct - 1][block_.center.x] = true;
                board_.type[block_.center.y + ct - 1][block_.center.x] =
                        block_.block_type;
                update_board();
                new_block();
                flag = false;
                break;
            }

            //check if the block touches the set blocks on the bottom
            if(board_.state[block_.center.y + block_.dir[i].height + ct][block_
            .center.x + block_.dir[i].width] || board_.state[block_.center.y
            + ct][block_.center.x]) {
                for(size_t j = 0; j < block_.dir.size(); j++) {

                    board_.state[block_.center.y + block_.dir[j].height
                    + ct - 1][block_.center.x + block_.dir[j].width] = true;

                    board_.type[block_.center.y + block_.dir[j].height
                    + ct - 1][block_.center.x + block_.dir[j].width] = block_
                            .block_type;
                }
                board_.state[block_.center.y + ct - 1][block_.center.x] = true;
                board_.type[block_.center.y + ct - 1][block_.center.x] =
                        block_.block_type;
                update_board();
                new_block();
                flag = false;
                break;
            }
        }
        ct++;
    }

}

void
Model::fast_fall()
{
    speed = 0.05;
}

void
Model::reset_fall()
{
    speed = temp_speed;
}

void
Model::on_frame(double dt) {

    if (gamelive) {
        s_drop();
        t += dt;

        if(t > speed) {
            t = 0;
            for(size_t i = 0; i < block_.dir.size(); i++) {
                //check if the block touches the bottom
                if(block_.next_pos(dt).center.y + block_.next_pos(dt) .dir[i]
                        .height > board_height || block_.next_pos(dt).center.y >
                        board_height) {
                    for(size_t j = 0; j < block_.dir.size(); j++) {
                        board_.state[block_.center.y + block_.dir[j].height]
                        [block_.center.x + block_.dir[j].width] = true;

                        board_.type[block_.center.y + block_.dir[j].height]
                        [block_.center.x + block_.dir[j].width] = block_
                                .block_type;
                    }
                    board_.state[block_.center.y][block_.center.x] = true;
                    board_.type[block_.center.y][block_.center.x] = block_
                            .block_type;
                    update_board();
                    new_block();
                    break;
                }

                //check if the block touches the set blocks on the bottom
                if(board_.state[block_.next_pos(dt).center.y +  block_
                .next_pos(dt).dir[i].height][block_.next_pos(dt).center.x +
                block_.next_pos(dt).dir[i].width] || board_.state[block_
                .next_pos(dt).center.y][block_.next_pos(dt).center.x]) {
                    for(size_t j = 0; j < block_.dir.size(); j++) {
                        board_.state[block_.center.y + block_.dir[j].height]
                        [block_.center.x + block_.dir[j].width] = true;

                        board_.type[block_.center.y + block_.dir[j].height]
                        [block_.center.x + block_.dir[j].width] = block_
                                .block_type;
                    }
                    board_.state[block_.center.y][block_.center.x] = true;
                    board_.type[block_.center.y][block_.center.x] = block_
                            .block_type;
                    update_board();
                    new_block();
                    break;
                }
            }
            block_ = block_.next_pos(dt);
        }
    }
}
