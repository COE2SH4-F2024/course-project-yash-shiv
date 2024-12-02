#include "Food.h"
#include <time.h>

Food::Food(GameMechs *gameRef, objPosArrayList *playerPos)
{
    mainGameMechsRef = gameRef;
    foodPos.symbol = 'o';
    generateFood(playerPos);
}

Food::~Food()
{
}

void Food::generateFood(objPosArrayList *blockOff)
{
    int i; 
    int foodPosX, foodPosY;
    bool condition = false; // Start with an invalid position
     
    int xRange, yRange; 
    xRange = mainGameMechsRef->getBoardSizeX() - 2;
    yRange = mainGameMechsRef->getBoardSizeY() - 2;

    // Keep generating random positions until a valid one is found
    while (!condition)
    {
        // Generate random food position within board boundaries (not touching borders)
        foodPosX = 1 + rand() % xRange;
        foodPosY = 1 + rand() % yRange;

        // Assume the position is valid
        condition = true;

        // Check if the generated position overlaps with any blocked area (e.g., snake's body)
        for (i = 0; i < blockOff->getSize(); i++)
        {
            objPos segment = blockOff->getElement(i);
            
            // If food position overlaps with any blocked segment, mark it invalid
            if (foodPosX == segment.pos->x && foodPosY == segment.pos->y)
            {
                condition = false; // Mark position as invalid
                break; // Exit the loop early, as we need to generate a new position
            }
        }
    }

    // Set the valid food position once found
    this->foodPos.setObjPos(foodPosX, foodPosY, foodPos.symbol);
}


objPos const Food::getFoodPos()
{
    return foodPos;
}

bool Food::checkSelfCollision(objPosArrayList *playerPos)
{

    return playerPos->getElement(0) == foodPos;
}
