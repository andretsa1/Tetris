#include "ui.hxx"
#include <iostream>

Ui::Ui(Model& model)
    : model_(model),
      builder(score_font)
{ }

void
Ui::on_key(ge211::Key key)
{
    if (key == ge211::Key::up()) {
        model_.rotate_cw();
    }
    if (key == ge211::Key::left()) {
        model_.move_left();
    }
    if (key == ge211::Key::right()) {
        model_.move_right();
    }
    if (key == ge211::Key::code('z')) {
        model_.rotate_ccw();
    }
    if (key == ge211::Key::code(' ')) {
        model_.drop();
    }
    if (key == ge211::Key::code('c')) {
        model_.hold();
    }
}

void
Ui::on_key_down(ge211::Key key)
{
    if (key == ge211::Key::down()) {
        model_.fast_fall();
    }
}

void
Ui::on_key_up(ge211::Key key)
{
    if (key == ge211::Key::down()) {
        model_.reset_fall();
    }
}


void
Ui::draw_block(ge211::Sprite_set& sprites, block b) {

    for(size_t i = 0; i < b.dir.size(); i++) {
        if (b.block_type == 0) {
            sprites.add_sprite(cyan, {(b.center.x + b.dir[i].width) *
            grid_size, (b.center.y + b.dir[i].height) * grid_size}, 2);
        } else if (b.block_type == 1) {
            sprites.add_sprite(purple, {(b.center.x + b.dir[i].width) *
            grid_size, (b.center.y + b.dir[i].height) * grid_size}, 2);
        } else if (b.block_type == 2) {
            sprites.add_sprite(green, {(b.center.x + b.dir[i].width) *
            grid_size, (b.center.y + b.dir[i].height) * grid_size}, 2);
        } else if (b.block_type == 3) {
            sprites.add_sprite(red, {(b.center.x + b.dir[i].width) *
            grid_size, (b.center.y + b.dir[i].height) * grid_size}, 2);
        } else if (b.block_type == 4) {
            sprites.add_sprite(orange, {(b.center.x + b.dir[i].width) *
            grid_size, (b.center.y + b.dir[i].height) * grid_size}, 2);
        } else if (b.block_type == 5) {
            sprites.add_sprite(blue, {(b.center.x + b.dir[i].width) *
            grid_size, (b.center.y + b.dir[i].height) * grid_size}, 2);
        } else if (b.block_type == 6) {
            sprites.add_sprite(yellow, {(b.center.x + b.dir[i].width) *
            grid_size, (b.center.y + b.dir[i].height) * grid_size}, 2);
        }
    }

    if (b.block_type == 0) {
        sprites.add_sprite(cyan, {b.center.x * grid_size, b.center.y *
        grid_size}, 2);
    } else if (b.block_type == 1) {
        sprites.add_sprite(purple, {b.center.x * grid_size, b.center.y *
        grid_size}, 2);
    } else if (b.block_type == 2) {
        sprites.add_sprite(green, {b.center.x * grid_size, b.center.y *
        grid_size}, 2);
    } else if (b.block_type == 3) {
        sprites.add_sprite(red, {b.center.x * grid_size, b.center.y *
        grid_size}, 2);
    } else if (b.block_type == 4) {
        sprites.add_sprite(orange, {b.center.x * grid_size, b.center.y *
        grid_size}, 2);
    } else if (b.block_type == 5) {
        sprites.add_sprite(blue, {b.center.x * grid_size, b.center.y *
        grid_size}, 2);
    } else if (b.block_type == 6) {
        sprites.add_sprite(yellow, {b.center.x * grid_size, b.center.y *
        grid_size}, 2);
    }

}

void
Ui::draw_set(ge211::Sprite_set& sprites, board b)
{
    for(int i = 0; i < board::b_height; i++) {
        for (int j = 0; j < board::b_wid; j++) {
            if(model_.board_.state[i][j]) {
                if (b.type[i][j] == 0) {
                    sprites.add_sprite(cyan, {j * grid_size, i
                    * grid_size}, 1);
                } else if (b.type[i][j] == 1) {
                    sprites.add_sprite(purple, {j * grid_size, i
                    * grid_size}, 1);
                } else if (b.type[i][j] == 2) {
                    sprites.add_sprite(green, {j * grid_size, i
                    * grid_size}, 1);
                } else if (b.type[i][j] == 3) {
                    sprites.add_sprite(red, {j * grid_size, i
                    * grid_size}, 1);
                } else if (b.type[i][j] == 4) {
                    sprites.add_sprite(orange, {j * grid_size, i
                    * grid_size}, 1);
                } else if (b.type[i][j] == 5) {
                    sprites.add_sprite(blue, {j * grid_size, i
                    * grid_size}, 1);
                } else if (b.type[i][j] == 6) {
                    sprites.add_sprite(yellow, {j * grid_size, i
                    * grid_size}, 1);
                } else {
                    sprites.add_sprite(white, {j * grid_size, i
                    * grid_size}, 1);
                }
            } else if (model_.board_.type[i][j] == 7) {
                sprites.add_sprite(grey, {j * grid_size, i
                * grid_size}, 1);
            } else {
                sprites.add_sprite(black, {j * grid_size, i
                * grid_size}, 1);
            }
        }
    }
}

void
Ui::draw(ge211::Sprite_set& sprites) {

    for(int i = 0; i < board::b_height; i++) {
        for(int j = 10; j < board::b_height; j++) {
            sprites.add_sprite(grey, {j * grid_size, i
            * grid_size}, 1);
        }
    }

    std::queue<block> temp = model_.queue_block;
    for(int i = 0; i < 3; i++) {
        draw_block(sprites, temp.front());
        temp.pop();
    }

    builder << "Lines cleared: " << model_.lines_cleared;
    score_sprite.reconfigure(builder);
    //Clear builder
    builder.message("");
    sprites.add_sprite(score_sprite,{450, 10},3);

    builder << "Level: " << model_.level;
    level_sprite.reconfigure(builder);
    //Clear builder
    builder.message("");
    sprites.add_sprite(level_sprite,{450, 30},3);

    draw_block(sprites, model_.hold_block);

    draw_set(sprites, model_.board_);

    draw_block(sprites, model_.block_);

    if (!model_.gamelive) {

        builder << "Game Over!";

        gameover_sprite.reconfigure(builder);

        builder.message("");

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < board::b_wid; j++) {
                sprites.add_sprite(white, {j * grid_size, i
                * grid_size}, 3);
            }
        }

        for (int i = 0; i < 4; i++) {
            sprites.add_sprite(black, {90 + i * grid_size, 269}, 2);
        }

        sprites.add_sprite(gameover_sprite,{100, 270},3);

    }

}



void
Ui::on_frame(double dt)
{
    model_.on_frame(dt);
}

ge211::Dims<int>
Ui::initial_window_dimensions() const
{
    return {599,600};

}

std::string
Ui::initial_window_title() const
{
    return "Tetris";
}
