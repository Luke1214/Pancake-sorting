# Pancake-sorting
Pancake sorting using A*

To Compile:
Navigate to 'pancakes' directory in the terminal, then run the following commands:
1. mkdir build          (NOTE: if directory 'build' already exists, first run 'rmdir build')
2. cd build
3. cmake ..             (NOTE: if cmake is not found, use Homebrew to install cmake)
4. make
After program compiles, run:
5. ./pancakes

Introduction:
The pancake sorting problem involves a disordered stack of pancakes, where each pancake has a different size. The goal is to sort the stack so that the largest pancake is at the bottom and the smallest at the top, using only a spatula to flip a top portion of the stack.


Assumptions:
1. Pancake stack must be entered as a list of integers with no spaces between
   the digits. Integers must be between 1 and 10 (inclusive). If the 
   highest number in the list is N, the list must contain all integers
   1,...,N.

   Examples of valid input:
   12345678910
   32145
   7152634

   Examples of invalid input:
   1,2,3,4,5
   1239
   41p01

2. Pancake stacks are considered to be in the correct order when they are in
   ascending order. I.e, the pancakes is ordered such that left->right = top->bottom.

3. The cost function is the number of flips to get to a given stack from the start stack.
   The heuristic function is the number of stack positions for which the pancake at that 
   position is not of adjacent size to the pancake below.

4. This implementation has both a Uniform Cost Search and A* search. The user can select
   which one to use.


Files:

graph.h
graph.cpp
    These files define and implement the graph. This graph is populated with nodes that 
    represent all possible stack permutations that can be made from the goal stack.    

node.h
node.cpp
    These files define and implement the nodes in the graph. 

search.h
search.cpp
    The files define and implement the A* and USC searches.

comparison.h
    This file implements the comparison that is used to determine priority for the 
    priority queue.

pancakes.cpp:
    This file contains the main() function. It takes the user input, validates it and 
    modifies it if necessary (if the user enters a '10' it changes that string to a 
    single character ':', which has a higher dec value than 1,...,9). 
    
This file also establishes the goal state and prints the stack.
