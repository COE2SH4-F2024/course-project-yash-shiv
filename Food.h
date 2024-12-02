#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "GameMechs.h"

class Food
{

    private:
        objPos foodPos;
        GameMechs *mainGameMechsRef;

    public:
        Food(GameMechs *gameRef, objPosArrayList *playerPosList);
        ~Food();

        void generateFood(objPosArrayList *blockOff);
        
        bool checkSelfCollision(objPosArrayList *playerPosList);
        
        objPos const getFoodPos() ;
    };

#endif