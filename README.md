# PongGame

This project is a simple Pong game created with the SFML library in C++. The game features single and multiplayer modes, with an AI-controlled paddle in single-player mode.

![Demo](./PongGame/assets/demo.gif)

# Dependencies

SFML library

Visual Studio 2022

# Classes

Entity: This is the base class for all game entities, such as paddles and the ball. It handles the basic functionalities such as setting position, rendering, and getting global bounds.

Paddle: This class inherits from the Entity class and represents a paddle. It has the ability to move up and down, change its velocity, and check for boundary collision.

Ball: This class also inherits from the Entity class and represents the ball. It has the ability to move, change its velocity, and check for collision with the paddles and the game boundaries.

Button: This class represents a button that can be used in the game menu. It has the ability to render, check if it is pressed, and update its state based on mouse position.

State: This class is an abstract base class for game states, such as the main menu and the game state itself. It contains some common functionalities such as setting up text and updating mouse position.

MenuState: This class inherits from the State class and represents the main menu of the game. It has the ability to initialize the background and buttons, update and render the buttons.

GameState: This class also inherits from the State class and represents the game itself. It has the ability to initialize the game field, entities, and scores, update player and ball movements, and render the game field and scores.

Game: This class handles the game loop and manages the game states. It has the ability to update the delta time, SFML events, and call the update and render functions for the current game state.

# Usage

Upon running the game, the user is first presented with a menu where they can choose to play a single player or two player game. In single player mode, the user plays against an AI-controlled paddle. In two player mode, two users can play against each other on the same keyboard.

The controls for the game are as follows:

Player 1 (left paddle): W and S keys to move up and down, respectively.

Player 2 (right paddle): Up and Down arrow keys to move up and down, respectively.

Pause: Press Space key to pause and unpause.

Return to Menu: Press ESC.
