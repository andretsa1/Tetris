#pragma once

#include <ge211.hxx>

#include <string>

#include "model.hxx"

struct Ui
        : ge211::Abstract_game
{
public:
    explicit Ui(Model& model);

    Model& model_;

    ge211::Color const light_color{255,255,255};

    ge211::Color const dark_color{0,0,0};

    ge211::Color const grey_color{100, 100, 100};

    ge211::Color const purple_color{128,0,128};

    ge211::Color const blue_color{0,0,255};

    ge211::Color const cyan_color{0,255,255};

    ge211::Color const orange_color{255,165,0};

    ge211::Color const yellow_color{255,255,0};

    ge211::Color const green_color{0,255,0};

    ge211::Color const red_color{255,0,0};

    int const grid_size = 30;

    ge211::Font score_font{"sans.ttf", 18};

    ge211::Font gm_font{"sans.ttf", 40};

    ge211::Text_sprite score_sprite = ge211::Text_sprite{"Lines cleared: ",
                                                         score_font};

    ge211::Text_sprite gameover_sprite = ge211::Text_sprite{"Game Over",
                                                         gm_font};

    ge211::Text_sprite level_sprite = ge211::Text_sprite{"Level: ",
                                                            score_font};

    //builder to be reconfigured
    ge211::Text_sprite::Builder builder;

    ge211::Rectangle_sprite const
            grey{{grid_size, grid_size}, grey_color};

    ge211::Rectangle_sprite const
            white{{grid_size, grid_size}, light_color};

    ge211::Rectangle_sprite const
            cyan{{grid_size, grid_size}, cyan_color};

    ge211::Rectangle_sprite const
            blue{{grid_size, grid_size}, blue_color};

    ge211::Rectangle_sprite const
            purple{{grid_size, grid_size}, purple_color};

    ge211::Rectangle_sprite const
            orange{{grid_size, grid_size}, orange_color};

    ge211::Rectangle_sprite const
            yellow{{grid_size, grid_size}, yellow_color};

    ge211::Rectangle_sprite const
            green{{grid_size, grid_size}, green_color};

    ge211::Rectangle_sprite const
            red{{grid_size, grid_size}, red_color};

    ge211::Rectangle_sprite const
            black{{grid_size, grid_size}, dark_color};

    void on_key(ge211::Key) override;

    void on_key_down(ge211::Key) override;

    void on_key_up(ge211::Key) override;

    void draw(ge211::Sprite_set&) override;

    void draw_block(ge211::Sprite_set& sprites, block b);

    void draw_set(ge211::Sprite_set& sprites, board b);

    ge211::Dims<int> initial_window_dimensions() const override;

    std::string initial_window_title() const override;

    void on_frame(double dt) override;

    //ge211::Text_sprite game_over = ge211::Text_sprite{"Game Over!", };
};