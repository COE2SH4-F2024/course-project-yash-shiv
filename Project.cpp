#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Pointers
Player *myPlayer;
GameMechs *snakeGame;
Food *myFood;

int main(void)
{

    Initialize();

    while (!snakeGame->getExitFlagStatus())
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    snakeGame = new GameMechs(30, 15);
    myPlayer = new Player(snakeGame);
    myFood = new Food(snakeGame, myPlayer->getPlayerPos());

    //exitFlag = false;
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        char userInput; 

        userInput = MacUILib_getChar();

        snakeGame->setInput(userInput);
        
        if (userInput == 27)
        {
            snakeGame->setExitTrue();
        }
    }
    else
    {
        snakeGame->setInput(0);
    }
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    if (myPlayer->checkFoodConsumption(myFood))
    {
        myFood->generateFood(myPlayer->getPlayerPos());
        myPlayer->increasePlayerLength(myFood);
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // Print the header and instructions
    MacUILib_printf("2SH4 Snake Game: Built Using C/C++!\n");
    MacUILib_printf("-------------------------------------------------------------------\n");
    MacUILib_printf("Instructions: Use W, A, S, D to move, collect food items to grow,  \n");
    MacUILib_printf("Friendly Reminder: The game will not end if and when you collide with a border!\n");
    MacUILib_printf("DO NOT COLLIDE WITH YOURSELF. When done playing, press ESC key to exit. \n");
    MacUILib_printf("-------------------------------------------------------------------\n");

    // Display warning if snake can collide with itself
    if (snakeGame->getScore() >= 4)  // Changed the condition for clarity
    {
        MacUILib_printf("\nWARNING: Your snake is now capable of colliding with itself. Make your moves wisely.\n\n");
    }

    // Draw the game board
    int x, y; 

    for (y = 0; y < snakeGame->getBoardSizeY(); y++)
    {
        for (x = 0; x < snakeGame->getBoardSizeX(); x++)
        {
            // Handle the borders
            if (x == 0 || x == snakeGame->getBoardSizeX() - 1 || y == 0 || y == snakeGame->getBoardSizeY() - 1)
            {
                MacUILib_printf("#");  // Draw border
                continue;
            }
            else
            {
                bool isPrinted = false;

                // Check if the current cell is part of the snake
                for (int i = 0; i < myPlayer->getPlayerPos()->getSize(); i++)
                {
                    objPos segment = myPlayer->getPlayerPos()->getElement(i);

                    if (x == segment.pos->x && y == segment.pos->y)
                    {
                        MacUILib_printf("%c", segment.symbol);  // Draw snake segment
                        isPrinted = true;
                        break; 
                    }
                }

                // If not part of the snake, check if it's food
                if (!isPrinted)
                {
                    if (x == myFood->getFoodPos().pos->x && y == myFood->getFoodPos().pos->y)
                    {
                        MacUILib_printf("%c", myFood->getFoodPos().symbol);  // Draw food
                    }
                    else
                    {
                        MacUILib_printf(" ");  // Draw empty space
                    }
                }
            }
        }
        MacUILib_printf("\n");  // Move to the next line after finishing a row
    }

    // Print the game stats
    MacUILib_printf("-------------------------------------------------------------------\n");
    MacUILib_printf("GAME STATS\n");
    MacUILib_printf("-------------------------------------------------------------------\n");
    MacUILib_printf("Food Eaten/Game Score: %d\n", snakeGame->getScore());
    if (snakeGame->getScore() == 0)
    {
        MacUILib_printf("Current Snake Length: %d (It's Just the head itself LOL!)\n ", snakeGame->getScore() + 1);
    }
    else
    {
        MacUILib_printf("Current Snake Length: %d\n", snakeGame->getScore() + 1);
    }
    MacUILib_printf("\n");

    // Check if the game has ended
    if (snakeGame->getLoseFlagStatus())
    {
        snakeGame->setExitTrue();  // Set the exit flag if the game is over
    }
    
}



void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); 
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_printf("Games over :( Thanks for Playing!\n");

    MacUILib_uninit();

    // Deallocate to prevent memory leak
    delete myPlayer;
    delete snakeGame;
    delete myFood;
}
