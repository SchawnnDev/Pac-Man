# PacMan Game

This project was developed as part of a university coursework with
the aim of learning modern C++ programming techniques and applying them to recreate the original 1980 Namco Pac-Man game using the SDL2 library.

## Installation

To install the game, clone the Git repository and navigate to the `PacMan/build` directory:

```
$ git clone https://github.com/SchawnnDev/PacMan.git
$ cd PacMan/build
```

Then, use CMake to generate the build files:

```
$ cmake ../
```

Finally, compile the game using make:

```
$ make
```

Note that all dependencies are downloaded and compiled during the build process, so there is no need to install anything on the system beforehand.

## Requirements

To build and run the game, you will need:

- CMake
- A C++ 20 compiler

## Usage

To play the game, use the following keyboard controls:

- `C`: insert coin
- `1`: start game with 1 player
- `2`: start game with 2 players
- `Esc`: exit the game
- Arrow keys: control the movement of PacMan

## Features

The game includes all the original features of the Namco 1980 PacMan game, including:

- Multiplayer mode
- Sounds
- Ghost AI
- Fruits
- Power-ups

## Missing Features

Although the game includes most of the original features, some features are still missing or could be improved:

- Handling speed perfectly
- Cornering
- Some sounds
- Animation when completing a level (the animation with PacMan eating the ghosts)

## Contributing

Contributions are welcome! If you want to contribute, please fork this repository and create a pull request with your changes.