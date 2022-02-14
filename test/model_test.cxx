#include "model.hxx"
#include <catch.hxx>
struct Test_access {
    Model& model;
    board& board() {
        return model.board_;
    }

    void on_frame(double dt)
    {
        return model.on_frame(dt);
    }

    void update_board()
    {
        return model.update_board();
    }

    void gameover()
    {
        return model.gameover();
    }

    void hold()
    {
        return model.hold();
    }

    void move_left()
    {
        return model.move_left();
    }

    void move_right()
    {
        return model.move_right();
    }

    void rotate_cw()
    {
        return model.rotate_cw();
    }


    void rotate_ccw()
    {
        return model.rotate_ccw();
    }

    void new_block()
    {
        return model.new_block();
    }

    void fast_fall()
    {
        return model.fast_fall();
    }

    void drop()
    {
        return model.drop();
    }

    void reset_fall()
    {
        return model.reset_fall();
    }

};

TEST_CASE("Filling a row")
{
    Model m;
    Test_access t{reinterpret_cast<Model&>(m)};

    // Make the 15th row all 'true' or occupied
    for (int i = 0; i < 10; i++) {
            t.board().state[15][i] = true;
    }

    // Other positions (for testing)
    t.board().state[14][1] = true; // should move down 1
    t.board().state[5][2] = true; // should move down 1
    t.board().state[18][9] = true; // shouldn't move

    t.model.update_board();
    //One line should be cleared
    CHECK(t.model.lines_cleared == 1);

    // The first 2 points were above the cleared line, so they should go down 1
    CHECK(!t.board().state[14][1]);
    CHECK(t.board().state[15][1]);

    CHECK(!t.board().state[5][2]);
    CHECK(t.board().state[6][2]);

    // The last point was below the cleared line, so it shouldn't move
    CHECK(!t.board().state[19][9]);
    CHECK(t.board().state[18][9]);
    // check if the line is cleared

    for (int i = 0; i < 10; i++) {
        // One block fell into the row
        if (i != 1) {
            CHECK(!t.board().state[15][i]);
        }
    }

    //check if the new block spawns in the right position
    CHECK(t.model.block_.center.x == 4);
    CHECK(t.model.block_.center.y == 1);
}


TEST_CASE("Score increasing")
{
   Model m;
   Test_access t {reinterpret_cast<Model&>(m)};

   CHECK(t.model.lines_cleared == 0);
   // Clear a row
    // Make the 15th row all 'true' or occupied
    for (int i = 0; i < board::b_wid; i++) {
        t.board().state[15][i] = true;
    }
    t.model.update_board();
    CHECK(t.model.lines_cleared == 1);

}

TEST_CASE("Move right and left")
{
    Model m;
    Test_access t {reinterpret_cast<Model&>(m)};

    t.new_block();
    t.move_right();
    CHECK(t.model.block_.center.x == 5);
    t.move_left();
    t.move_left();
    CHECK(t.model.block_.center.x == 3);
}

TEST_CASE("Rotation")
{
    Model m;
    Test_access t {reinterpret_cast<Model&>(m)};

    t.new_block();
    block temp = t.model.block_;

    int tmp = 0;
    for (size_t i = 0; i < temp.dir.size(); i++) {
        tmp = temp.dir[i].height;
        temp.dir[i].height = temp.dir[i].width;
        temp.dir[i].width = tmp * (-1);
    }

    t.rotate_cw();

    for (size_t i = 0; i < t.model.block_.dir.size(); i++) {
        CHECK(temp.dir[i].height == t.model.block_.dir[i].height);
        CHECK(temp.dir[i].width == t.model.block_.dir[i].width);
    }

    for (size_t i = 0; i < temp.dir.size(); i++) {
        tmp = temp.dir[i].height;
        temp.dir[i].height = temp.dir[i].width * (-1);
        temp.dir[i].width = tmp;
    }

    t.rotate_ccw();

    for (size_t i = 0; i < t.model.block_.dir.size(); i++) {
        CHECK(temp.dir[i].height == t.model.block_.dir[i].height);
        CHECK(temp.dir[i].width == t.model.block_.dir[i].width);
    }
}

TEST_CASE("Testing Hold")
{
    Model m;
    Test_access t {reinterpret_cast<Model&>(m)};

    // Make new block
    //t.model.block_num = 0;
    // Predetermine which block will spawn
    t.new_block();
    block temp = t.model.block_;

    // Hold the block
    t.hold();

    CHECK(temp.block_type == t.model.on_hold);
}

TEST_CASE("Game over")
{
    Model m;
    Test_access t {reinterpret_cast<Model&>(m)};
    // Fill up board
    //Call new_block
    // See if game_over ran (check gameLive)
    for (int i = 0; i < board::b_height; i++)
    {
        for (int j = 0; j < board::b_wid; j++)
        {
            t.board().state[i][j] = true;
        }
    }
    t.new_block();
    CHECK(!t.model.gamelive);
}
//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate at least six of the functional
// requirements.
//
