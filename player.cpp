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

    //creates player's gameboard and defines player's side and opponent's side
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
 *
 * NOTE: to select the method of making a move, it must be uncommented and the
 * other methods must be commented out.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {

    //adds opponent's move to gameboard
    gameboard->doMove(opponentsMove, other);

    Move* bestMove = nullptr;
    //bestMove = doAlphaBeta();
    //bestMove = doMinimax();
    //bestMove = random();
    bestMove = heuristic();
    //bestMove = iterDeepening(msLeft);

    gameboard->doMove(bestMove, s);
    return bestMove;
}

/*
 * Compute's next move using iterative deepening on alpha beta
 */
Move *Player::iterDeepening(int msLeft)
{
    Move *bestMove = nullptr;
    if (msLeft == -1)
    {
        

        return doAlphaBeta();
    }
    else
    {
        clock_t start;
        start = clock();
        clock_t t = clock() - start;
        int depth = 0;

        while (((float) (clock() - start))/CLOCKS_PER_SEC/1000 < (msLeft - t))
        {
            int alpha = -65;
            int beta = 65;
            int returned;
            bestMove = alphaBeta(gameboard, s, other, alpha, beta, returned, bestMove, depth);
            depth++;
        }
        return bestMove;
    }
}

/*
 * Compute's next move using alpha beta with iterative deepening
 */
Move* Player::alphaBeta(Board *board, Side side, Side opp, int alpha, int beta, int& returned, Move* makeMove, int depth)
{
    //create copy of gameboard and test given move
    Board *testboard = gameboard->copy();
    testboard->doMove(makeMove, side);

    if ((testboard->isDone()) && (depth == 0))
    {
        
        returned = testboard->count(side) - testboard->count(opp);
        return nullptr;
    }
    else if (depth > 0)
    {

        Move* best = nullptr;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move *move = new Move(i, j);
                if (testboard->checkMove(move, side))
                {

                    //calculate which move has the highest score
                    int score;
                    alphaBeta(testboard, opp, side, -beta, -alpha, score, move, depth - 1);
                    if (score != 100)
                    {
                        score = -score;
                        if (score > alpha)
                        {
                            best = move;
                            alpha = score;
                        }
                        if (score >= beta)
                        {
                            returned = beta;
                            return move;
                        }
                    }
                }
            }
        }
        returned = alpha;
        return best;
    }
    returned = 100;
    return nullptr;
}

/*
 * Compute's next move using alpha beta without iterative deepening
 * NOTE: only works for certain "first moves" if playing against a human, 
 *  usually segfaults
 */

Move *Player::doAlphaBeta()
{
    // initialize alpha and beta
    int alpha = -65;
    int beta = 65;
    Move *bestMove = nullptr;

    //for all possible moves
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if (gameboard->checkMove(move, s))
            {
                //calculate which move has the best alpha-beta score
                int curr_count = alphaBeta(gameboard, s, other, alpha, beta, move);
                //check if we have a better move
                if (curr_count > alpha)
                {
                    alpha = curr_count;
                    bestMove = move;
                }
                //check if we have a worse move and should stop checking this branch
                if (curr_count >= beta)
                {
                    return bestMove;
                }
            }
        }
    }

    //returns best move
    return bestMove;
}

/*
 * Compute's best integer score of a move for alpha beta
 */

int Player::alphaBeta(Board *board, Side side, Side opp, int alpha, int beta, Move* makeMove)
{
    //create copy of gameboard and test given move
    Board *testboard = gameboard->copy();
    testboard->doMove(makeMove, side);

    // if we have reached the end of the game, return the count
    if (testboard->isDone())
    {

        int returned = testboard->count(side) - testboard->count(opp);
        return returned;
    }
    
    //check all the opponent's moves and call alpha beta on them
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            Move *move = new Move(i, j);
            if (testboard->checkMove(move, other))
            {
                int currCount = alphaBeta(testboard, other, side, -beta, -alpha, move);
                // check if we have a better move
                if (currCount > alpha)
                {
                    alpha = currCount;
                }
                // check if we cannot do any better
                if (currCount >= beta)
                {
                    return beta;
                }
            }
        }
    }

    return alpha;

}
    



/*
 * Compute's next move using minimax
 */

Move *Player::doMinimax()
{
    int bestCount = -65;
    Move *bestMove = nullptr;

    //for all possible moves
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if (gameboard->checkMove(move, s))
            {
                //calculate which move has the highest score
                int curr_count = minimax(gameboard, s, move);
                if (curr_count > bestCount)
                {
                    bestCount = curr_count;
                    bestMove = move;
                }
            }
        }
    }

    //adds and returns best move
    //gameboard->doMove(bestMove, s);
    return bestMove;
}

/*
 * Compute's best integer score of a move for minimax
 */

int Player::minimax(Board *board, Side side, Move *move)
{
    //create copy of gameboard and test given move
    Board *testboard = gameboard->copy();
    testboard->doMove(move, side);
    int bestCount = 65;;

    //if given move is player's own move
    if (side == s)
    {
        //calculate the lowest score out of opponent's next possible moves and stores in bestCount
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                Move *move = new Move(i, j);
                if (testboard->checkMove(move, other))
                {
                    int currCount = minimax(testboard, other, move);
                    if (currCount < bestCount)
                    {
                        bestCount = currCount;
                    }
                }
            }
        }
    }

    //if given move is opponent's move, calculate player piece count minus opponent piece count 
    else
    {

        bestCount = testboard->count(s) - testboard->count(other);

    }

    return bestCount;

}

/* 
 * Compute's the next move using a heuristic algorithm
 */

Move *Player::heuristic()
{
    std::vector<Move*> moves;

    //determines all possible moves
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Move *move = new Move(i, j);
            if (gameboard->checkMove(move, s))
            {
                moves.push_back(move);
            }
        }
    }

    //pass if no possible moves
    if (moves.empty())
    {
        return nullptr;
    }


    Move *bestMove;
    int bestMove_count = -65;

    //for all possible moves, create copy of board and test the move
    for (int i = 0; i < (int) moves.size(); i++)
    {
        Board *testboard = gameboard->copy();
        testboard->doMove(moves[i], s);

        //compute's player's piece count after move
        int curr_count = testboard->count(s);

        //adds 3 to count if move is corner
        if (((moves[i]->x == 7) || (moves[i]->x == 0)) && ((moves[i]->y == 0) || (moves[i]->y == 7)))
        {
            curr_count += 3;
        }

        //subtracts 2 from count if move is adjacent to corner but is an edge
        else if ((((moves[i]->x == 7) || (moves[i]->x == 0)) && ((moves[i]->y == 1) || (moves[i]->y == 6))) || (((moves[i]->x == 1) || (moves[i]->x == 6)) && ((moves[i]->y == 0) || (moves[i]->y == 7))))
        {
            curr_count -= 2;
        }

        //adds 2 to count if move is edge
        else if ((moves[i]->x == 7) || (moves[i]->x == 0) || (moves[i]->y == 0) || (moves[i]->y == 7))
        {
            curr_count += 2;
        }

        //subtracts 3 if move is adjacent to corner but not an edge
        else if (((moves[i]->x == 6) || (moves[i]->x == 1)) && ((moves[i]->y == 6) || (moves[i]->y == 1)))
        {
            curr_count -= 3;
        }

        //stores move with the highest count in bestMove
        if (curr_count > bestMove_count)
        {
            bestMove = moves[i];
            bestMove_count = curr_count;
        }
    }

    //adds and returns best move
    //gameboard->doMove(bestMove, s);
    return bestMove;
}

/*
 * Returns an arbitrary possible move
 */

Move *Player::random()
{
    Move *nextMove = gameboard->randMove(s);

    gameboard->doMove(nextMove, s);

    return nextMove;
}
