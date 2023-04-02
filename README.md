# ThreadedMultiplayerGame

## Thread-Safe Game Implementation using Message-Passing
This project implements a thread-safe game using a message-passing system between the main thread and player threads. The game allows multiple players to move around a game board, collect items, and earn points.

#### Implementation Details
Each player is assigned a separate thread to handle their movement and item collection. The player threads update the player's position on the game board and check for item collection.

To ensure thread safety and prevent interference between players' movements, a message-passing system is used between the main thread and player threads. Each player thread sends messages to the main thread when they move or collect an item. The main thread updates the game board and score based on these messages.

To avoid conflicts between player threads, each player thread has its own message queue, and the main thread polls these message queues to receive updates from each player and updates the game state accordingly.

Thread attributes are used to set the priority of each player thread based on the player's score or other game-related factors. This ensures that players with higher scores or better performance are given higher priority in the game.

The game logic is handled by a main thread, which generates the game board, displays the game interface, and updates the score for each player.

#### Usage
To run the game make sure u have the sfml library then simply clone the repository and run the main.cpp file using C++:
```
make 
./myprogram
```

#### Contributions
Contributions are welcome! If you have any feedback or would like to contribute to the project, please create a pull request or submit an issue.

#### License
This project is licensed under the MIT License. See the LICENSE file for details.
