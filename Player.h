#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
public:
    // Direction states
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    };

    // Constructor and Destructor
    Player(GameMechs *thisGMRef);
    ~Player();

    // Core Functionalities
    objPos getPlayerPos() const;               // Get the player's head position
    objPosArrayList *getPlayerPosList() const; // Get the snake's entire body
    void updatePlayerDir();                    // Update player's direction based on input
    void movePlayer();                         // Move the snake head and handle body tracking
    bool foodConsumption();                    // Check and handle food collision
    bool selfCrash();                          // Detect self-collision
    void increaseLength();                     // Grow the snake on food consumption

    // New Methods for Rendering and Interaction
    void drawPlayer() const; // Draw the snake on the game board
    void resetPlayer();      // Reset snake to its initial state

private:
    // Player attributes
    objPos playerPos;               // Current head position
    objPosArrayList *playerPosList; // Snake body segments
    Dir myDir;                      // Current direction of movement

    // Game mechanisms reference
    GameMechs *mainGameMechsRef;
};

#endif
