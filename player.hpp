#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <time.h>
#include <cmath>
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

    Move *iterDeepening(int msLeft);
    Move* alphaBeta(Board *board, Side side, Side opp, int alpha, int beta, int& returned, Move* makeMove, int depth);
    int alphaBeta(Board *board, Side side, Side opp, int alpha, int beta, Move* makeMove);
    Move *doAlphaBeta();

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *gameboard;
    // The player's own side
    Side s;
    // The other player's side
    Side other;
};

#endif
