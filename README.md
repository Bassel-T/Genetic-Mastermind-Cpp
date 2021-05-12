# Genetic-Mastermind-Cpp

## Usage

To run the program, run the commands:

`g++ -std=c++11 Genetics.cpp Node.h`

`./a.out [first digit] [second digit] [third digit] [fourth digit]`

Note: Each digit an be any number from 0 to 9.

## Algorithm

Also known as Evolutionary Programming, the algorithm maintains a population of multiple candidate states. Each state has some sort of a "fitness" function to calculate how good each state is. At the end of a round, the winners are selected based on the fitness scores.

Instead of generating successors the way DFS or BFS would, this Genetic Algorithm uses recombination to combine parts of two members in the population, comparable to reality. A child will get chromosomes from his/her parents. During recombination, two children are created. One has the first part of parent x and the second part of parent y, while the other will flip those segments; the first part of y and the second of x.

Only a certain number of parents will actually have children. The top two will reproduce together, the next two, and so on, until a value of your choosing (which can be changed in `Genetics.cpp`). The remainder of the population will simply pass into the next generation. However, each character in the next generation has an ability to "Mutate," which changes one of the values in their genes. This happens at a low frequency (15% by default, which can also be changed).

The algorithm continues to generate new populations until the target value is reached.

## Mastermind

Mastermind is a fun game from my childhood that takes two to play. Player One chooses a sequence of numbers/colors and hides it from the other person. Player Two must guess what the sequence is. If a digit is the correct digit but in the wrong location, they get a black point. If a digit is the correct digit and in the right location, they get a white point (colors may vary from board to board). The goal is to use the past scores to intelligently find Player One's sequence within some number of guesses.