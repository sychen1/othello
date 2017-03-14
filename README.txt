Answers for Assignment 9 Part 2

Q: Describe how and what each group member contributed for the past two weeks.

A: In the first week, Sophia and Karen both contributed to implementing the working AI. Karen set up the Player() constructor and wrote the basic code for the heuristic function, and the first half of minimax. Sophia implemented the random move function and changed the heuristic function so that it would add or subtract values if the move was on an edge/corner; she also finished the minimax function. 

In the second week, Sophia implemented the alpha beta pruning function and Karen wrote the README file. 

Q: Document the improvements that your group made to your AI to make it tournament-worthy. Explain why you think your strategy(s) will work. Feel free to discuss any ideas were tried but didn't work out.

A: After the first week, we had a working heuristic function good enough to beat SimplePlayer. But we could not get our minimax to work properly as it was generally losing to SimplePlayer. For this week, we tried to implement alpha-beta pruning but for some reason it was seg-faulting after making a single move. So for the tournament we will be using our heuristic function; we believe it will do considerably well as it beat SimplePlayer 10/10 times and though it looks only one move ahead, it assigns weights to certain squares which prevents it from making a particularly dangerous move. 