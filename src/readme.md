<div align="center">
  <img src="img/c.png" height="50px" style="display: inline-block; margin-left: auto; margin-right: auto;">
</div>

# Escape

## About the Game
Escape is a console-based adventure game played in the Linux terminal. In this game, you control a player navigating through a maze. Your objective is to reach the goal without being caught by the dynamic water that starts spreading after you trigger a trap. The game features dynamic water spreading, traps, and an undo feature.
This README outlines the Prerequisites, how to run the game, the Characters in the game and it's core mechanics. 

## Getting Started
### Prerequisites
- A Linux system with a terminal.
- A C compiler such as gcc for building the game.
- The make command for building and compiling the program.

## Run the Game
- Run *make* in your terminal to compile the game from the source code.
- Once compiled, start the game by running: *./escape map.txt*.
- After you're done, you can clean up the build files by running: *make clean*.

## Characters on the Map
- *** → Border
- *P* → Player
- 'G' → Goal (green background)
- '@' → Trap (red background)
- '~' → Water (blue background)
- 'X' → Trapdoors
- 'O' → Walls
- ' ' → Empty space

## Game Mechanics
### Player Movement:
- w: Move up.
- s: Move down.
- a: Move left.
- d: Move right.
- u: Undo the last action.

### Win/Lose Conditions:
- **Win:** Reach the goal (*G*).
- **Lose:** The water spreads and touches the player (*P*) or the player walks into the water.

### Trap Mechanics:
Traps (represented by *@*) can be triggered, causing the trapdoors (X) to disappear and starting the water flooding process. Water spreads across the map in every direction after a trap is triggered.

### Undo Feature:
The game supports undoing moves using the *u* command. This will restore the player’s previous state, including position, water state, and trap state.

### Water Spreading:
Water spreads automatically once triggered. It spreads to adjacent cells (up, down, left, right) on each turn.
