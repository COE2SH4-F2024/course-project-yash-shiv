#include "Player.h"
#include <iostream>

// Constructor: Initialize the snake with a single segment
Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // Initialize the player's position list
    playerPosList = new objPosArrayList();
    objPos temporaryPosition(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*');
    playerPosList->insertHead(temporaryPosition);
}

// Destructor: Clean up dynamically allocated memory
Player::~Player()
{
    delete playerPosList;
}

// Get reference to the entire snake body
objPosArrayList *Player::getPlayerPosList() const
{
    return playerPosList;
}

// Update the player's direction based on input
void Player::updatePlayerDir()
{
    char input;

    input = mainGameMechsRef->getInput();

    switch (input)
    {
    case 27:
        mainGameMechsRef->setExitTrue();
        break;
    case 'w':
        if (myDir != DOWN)
        {
            myDir = UP;
        }
        break;

    case 'a':
        if (myDir != RIGHT)
        {
            myDir = LEFT;
        }
        break;

    case 's':
        if (myDir != UP)
        {
            myDir = DOWN;
        }
        break;

    case 'd':
        if (myDir != LEFT)
        {
            myDir = RIGHT;
        }
        break;

    case 'W':
        if (myDir != DOWN)
        {
            myDir = UP;
        }
        break;

    case 'A':
        if (myDir != RIGHT)
        {
            myDir = LEFT;
        }
        break;

    case 'S':
        if (myDir != UP)
        {
            myDir = DOWN;
        }
        break;

    case 'D':
        if (myDir != LEFT)
        {
            myDir = RIGHT;
        }
        break;

    default:
        break;
    }
}

// Move the snake (head and body)
void Player::movePlayer()
{
    objPos headPosition = playerPosList->getHeadElement(); // The current head position

    int boardSizeX, boardSizeY;

    boardSizeX = mainGameMechsRef->getBoardSizeX();
    boardSizeY = mainGameMechsRef->getBoardSizeY();

    int newPositionX = headPosition.pos->x;
    int newPositionY = headPosition.pos->y;

    // Finite State Machine logic
    switch (myDir)
    {
    case LEFT:
        if (newPositionX == 0)
        {
            newPositionX = boardSizeX - 1;
        }
        newPositionX--;
        break;

    case RIGHT:
        if (newPositionX == boardSizeX - 1)
        {
            newPositionX = 0;
        }
        newPositionX++;
        break;

    case UP:
        if (newPositionY == 0)
        {
            newPositionY = boardSizeY - 1;
        }
        newPositionY--;
        break;

    case DOWN:
        if (newPositionY == boardSizeY - 1)
        {
            newPositionY = 0;
        }
        newPositionY++;
        break;

    default:
        break;
    }

    // Create a new head position and insert it into the list
    objPos newHead(newPositionX, newPositionY, '*');
    playerPosList->insertHead(newHead);

    // Check for food collision and self-collision
    if (foodConsumption())
    {
        increaseLength(); // Grow the snake on food consumption
    }
    else
    {
        playerPosList->removeTail(); // Remove the tail if no food is consumed
    }

    if (selfCrash())
    {
        mainGameMechsRef->setLoseFlag();
        mainGameMechsRef->setExitTrue();
    }
}

// Check if the snake consumes food
bool Player::foodConsumption()
{
    objPos head = playerPosList->getHeadElement();
    objPos food = mainGameMechsRef->getFood();
    return (head.pos->x == food.pos->x && head.pos->y == food.pos->y);
}

// Grow the snake on food consumption
void Player::increaseLength()
{
    mainGameMechsRef->generateFood(*playerPosList); // Generate new food at a valid position
    mainGameMechsRef->incrementScore();             // Increment score
}

// Detect if the snake collides with itself
bool Player::selfCrash()
{
    objPos head = playerPosList->getHeadElement();

    // Check each body segment against the head
    for (int i = 1; i < playerPosList->getSize(); ++i)
    {
        objPos segment = playerPosList->getElement(i);
        if (head.pos->x == segment.pos->x && head.pos->y == segment.pos->y)
        {
            return true; // Collision detected
        }
    }
    return false;
}
