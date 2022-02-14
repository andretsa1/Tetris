/*******************************************/
/*** DO NOT CHANGE ANYTHING IN THIS FILE ***/
/*******************************************/

#include "board.hxx"

using namespace ge211;


board::board()
{
    for(int i = 0; i < b_height; i++) {
        for(int j = 0; j < b_wid; j++) {
            state[i][j] = false;
            type[i][j] = 8;
        }
    }
}