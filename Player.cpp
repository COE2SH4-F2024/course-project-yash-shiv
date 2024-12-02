#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPositionList = new objPosArrayList();
    objPos temporaryPosition (mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*'); 

    playerPositionList->insertHead(temporaryPosition);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPositionList;
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list
    return playerPositionList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic 
    char input;

    input = mainGameMechsRef->getInput();

    switch(input)
    {   
        case 27:
                mainGameMechsRef ->setExitTrue();
                break;
        case 'w':
            if(myDir != DOWN)
            {
            myDir = UP;
            }
            break;

        case 'a':
            if(myDir != RIGHT)
            {
            myDir = LEFT;
            }
            break;

        case 's':
            if(myDir != UP)
            {
            myDir = DOWN;
            }
            break;

        case 'd':
            if(myDir != LEFT)
            {
            myDir = RIGHT;
            }
            break;

        case 'W':
            if(myDir != DOWN)
            {
            myDir = UP;
            }
            break;

        case 'A':
            if(myDir != RIGHT)
            {
            myDir = LEFT;
            }
            break;

        case 'S':
            if(myDir != UP)
            {
            myDir = DOWN;
            }
            break;

        case 'D':
            if(myDir != LEFT)
            {
            myDir = RIGHT;
            }
            break;

        default:
            break;
    }        
    mainGameMechsRef->clearInput();
}

void Player::movePlayer()
{
    objPos headPosition = playerPositionList->getHeadElement(); //The current head positioning 

    int boardSizeX, boardSizeY; 

    boardSizeX = mainGameMechsRef->getBoardSizeX ();
    boardSizeY = mainGameMechsRef->getBoardSizeY ();

    int newPositionX, newPositionY; 
    newPositionX = headPosition.pos->x;
    newPositionY = headPosition.pos->y;


    // PPA3 Finite State Machine logic
    switch (myDir)
    {
       case LEFT:
            if(newPositionX == 0)
            {
                newPositionX = boardSizeX - 1;
            }
            newPositionX--;
            
            break;

        case RIGHT:
            if(newPositionX == boardSizeX - 1)
            {
                newPositionX = 0;
            }
            newPositionX++;
            
            break;

        case UP:
            if(newPositionY==0)
            {
                newPositionY = boardSizeY - 1;
            }
            newPositionY--;
            
            break;

        case DOWN:
            if(newPositionY == boardSizeY - 1)
            {
                newPositionY = 0;
            }
            newPositionY++;
            
            break;

        default:
            break; 
    }
    playerPositionList->insertHead(headPosition);
}

// More methods to be added