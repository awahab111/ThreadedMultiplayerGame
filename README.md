# ThreadedMultiplayerGame


implemented this game using threads, a thread is created for each player to handle their movement and item collection. Each player thread updates the player's position on the game board and checks if the player has collected any items.

To ensure thread safety and prevent interference between players' movements, a message-passing system is used between the main thread and player threads. Each player thread sends messages to the main thread when they move or collect an item. The main thread updates the game board and score based on these messages.

To avoid conflicts between player threads, each player thread has its own message queue, and the main thread polls these message queues to receive updates from each player and updates the game state accordingly.

Thread attributes are used to set the priority of each player thread based on the player's score or other game-related factors. This ensures that players with higher scores or better performance are given higher priority in the game.
