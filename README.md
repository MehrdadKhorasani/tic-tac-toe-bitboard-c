# Tic-Tac-Toe (Bitwise Implementation in C)

A lightweight Tic-Tac-Toe implementation in C that represents the game board using bitwise operations (bitboards). This approach demonstrates how classic board games can be implemented efficiently with low-level bit manipulation.

## Features
- Bitwise board representation using integers
- Fast win detection using predefined bit masks
- Minimal memory usage
- Clean and simple C implementation
- Educational example of bit manipulation in game logic

## How It Works
Instead of storing the board in arrays, each player’s moves are stored in an integer bitboard. Each bit represents a cell on the board: 

0 1 2  
3 4 5  
6 7 8  

For example, if a player marks cells 0, 4, 8, the bitboard looks like: 

100010001

Winning positions are checked using bit masks:

000000111  // row 1  
000111000  // row 2  
111000000  // row 3  
001001001  // column 1  
010010010  // column 2  
100100100  // column 3  
100010001  // diagonal  
001010100  // diagonal  

A player wins if:  
(player_board & win_mask) == win_mask

This makes win detection extremely fast and elegant.

## Building

just run the build bash. and then run the game file:  
./game
