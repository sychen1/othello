// rando small change for the bonus points

#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */

    gameboard = new Board();
    s = side;
    other = (s == BLACK) ? WHITE : BLACK;

}

/*
 * Destructor for the player.
 */
Player::~Player() {
    delete gameboard;
}

	

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    gameboard->doMove(opponentsMove, other);

    return heuristic();

    
}

Move *Player::heuristic()
{
    std::vector<Move*> moves;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if (gameboard->checkMove(move, s))
            {
                moves.push_back(move);
            }
        }
    }
    if (moves.empty())
    {
        return nullptr;
    }


    Move *bestMove;
    int bestMove_count = -65;
    for (int i = 0; i < (int) moves.size(); i++)
    {
        Board *testboard = gameboard->copy();
        testboard->doMove(moves[i], s);
        int curr_count = testboard->count(s);
        if (((moves[i]->x == 7) || (moves[i]->x == 0)) && ((moves[i]->y == 0) || (moves[i]->y == 7)))
        {
            curr_count += 3;
        }
        else if ((((moves[i]->x == 7) || (moves[i]->x == 0)) && ((moves[i]->y == 1) || (moves[i]->y == 6))) || (((moves[i]->x == 1) || (moves[i]->x == 6)) && ((moves[i]->y == 0) || (moves[i]->y == 7))))
        {
            curr_count -= 2;
        }
        else if ((moves[i]->x == 7) || (moves[i]->x == 0) || (moves[i]->y == 0) || (moves[i]->y == 7))
        {
            curr_count += 2;
        }
        else if (((moves[i]->x == 6) || (moves[i]->x == 1)) && ((moves[i]->y == 6) || (moves[i]->y == 1)))
        {
            curr_count -= 3;
        }

        if (curr_count > bestMove_count)
        {
            bestMove = moves[i];
            bestMove_count = curr_count;
        }
    }


    gameboard->doMove(bestMove, s);
    return bestMove;
}

Move *Player::random();
{
    Move *nextMove = gameboard->randMove(s);

    gameboard->doMove(nextMove, s);

    return nextMove;
}
