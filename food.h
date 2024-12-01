#ifndef FOOD_H
#define FOOD_H

#include <cstdlib>
#include <time.h>
#include "GameMechs.h"

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class Food
{
    private:
        objPos foodPos; // Holds the foods position and symbol - SP 
        GameMechs* mainGameMechsRef;
        
    public:
           
        Food(GameMechs* thisGMRef);
        
       // Destructor
        ~Food();


        void generateFood(objPos blockOff);     
        
        void getFoodPos() const;        
};

#endif

