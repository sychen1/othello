#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    Move *heuristic();
    Move *random();
    int minimax(Board *board, Side side, Move *move);
    Move *doMinimax();

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *gameboard;
    // The player's own side
    Side s;
    // The other player's side
    Side other;
};

#endif
