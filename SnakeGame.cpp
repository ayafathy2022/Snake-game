#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>

using namespace std;

bool GameOver;          //if the player lost the game or he can start a new one or not
const int width = 60;   //map dimension
const int hight = 20;

class GameObject
{
public:
    int SnakeHeadX, SnakeHeadY;   //to know where it is located
    int FruitX, FruitY;
    int Score;
    int TailX[100], TailY[100];   //max snake tail is 100
    int TailLenght;
    enum eDirection        //if we press a for example the snake will constantly go left so you do not have to press it again
    {
       STOP = 0,
       LEFT,
       RIGHT,
       UP,
       DOWN
    };
    eDirection dir;
};
class SnakeGame: public GameObject
{
public:
    SnakeGame()
    {
        cout<< "\tWelcome to Our Snake game. (press any key to continue)" <<endl;
        getch();
        system("cls");
        cout<< "Game instructions: " <<endl;
        cout<< "-> Use arrow keys to move the snake. "<<endl;
        cout<< "-> You will be provided Fruits at the several coordinates of the screen which you have to eat. "<<endl;
        cout<< "-> Everytime you eat a Fruit the length of the snake will be increased by 1 element and thus the score." <<endl;
        cout<< "\nPress any key to play The game...";
        getch();
        system("cls");
    }
        void Setup() //which part of the game the player is
        {
            GameOver = false;
            dir = STOP;              //so snake will not move until we start moving it
            SnakeHeadX = width / 2;  //the snake will be in the middle or centered on the map
            SnakeHeadY = hight / 2;
            srand(time(nullptr));    //to set the fruit somewhere random in the map
            FruitX = rand() % width;
            FruitY = rand() % hight;
            Score = 0;
        }

        void Draw()  //all the snake head and the snake tail the food and the border if the playing field
        {
            //system("cls");
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});  //to clear the screen from flickering
            cout<< "score:" << Score <<endl;
            for(int i=0; i<width+2; i++)
                cout<< "*";
            cout<<endl;     //for top wall

            for(int i=0; i<hight; i++)     //to print the map i will be height and j will be width its like printing a matrix
                {
                    for(int j=0; j<width; j++)     //*****
                    {                              //*   *
                        if(j == 0)                 //*   *
                            cout<< "*";            //*****

            if(i == SnakeHeadY && j == SnakeHeadX)
                cout<< "O";
            else if(i == FruitY && j == FruitX)
                cout<< "$";
            else
            {
                bool print = false;
                for(int k=0; k<TailLenght; k++)     //that will draw the tail (make it appear)
                {
                    if(TailX[k] == j && TailY[k] == i)
                    {
                        cout<< "o";
                        print = true;
                    }
                }
                if(!print)
                   cout<< " ";
            }

            if(j == width-1)
                cout<< "*";        //to print the wall in the next side
        }
        cout<<endl;
    }
    for(int i=0; i<width+2; i++)
        cout<< "*";
    cout<<endl;
        }
        //those are function to get a character from console window
        void Input()   //will read which part of the keyboard the player is pressing
        {
            if(_kbhit())   //will return positive number if character in the keyboard is expressed and if not will return zero
                {
                    switch(_getch())   //will return the ask value of the character that is pressed
                    {
                        case 'a':
                            dir = LEFT;
                            break;
                        case 'd':
                            dir = RIGHT;
                            break;
                        case 'w':
                            dir = UP;
                            break;
                        case 's':
                            dir = DOWN;
                            break;
                        case 'x':         //to terminate the game
                            GameOver = true;
                            break;
                    }
                }
            }

        void Logic()   //we see if the player lost the game
        {
            int prevx = TailX[0];
            int prevy = TailY[0];
            int prev2x, prev2y;
            for(int i=1; i<TailLenght; i++)
                {
                    prev2x = TailX[i];
                    prev2y = TailY[i];
                    TailX[i] = prevx;
                    TailY[i] = prevy;
                    prevx = prev2x;
                    prevy = prev2y;
                    TailX[0] = SnakeHeadX;     //that will make the tail follow the head
                    TailY[0] = SnakeHeadY;
                }
                switch(dir)      //through this the snake moves
                {
                    case LEFT:
                        SnakeHeadX--;
                        break;
                    case RIGHT:
                        SnakeHeadX++;
                        break;
                    case UP:
                        SnakeHeadY--;
                        break;
                    case DOWN:
                        SnakeHeadY++;
                        break;
                    default:
                        break;
                }
                if(SnakeHeadX > width || SnakeHeadX < 0 || SnakeHeadY > hight || SnakeHeadY < 0) //if the snake hit the wall gameover
                        GameOver = true;

                for(int i=0; i<TailLenght; i++)
                    if(TailX[i] == SnakeHeadX && TailY[i] == SnakeHeadY)     //if the snake hit himself gameover
                        GameOver = true;

                    if( SnakeHeadX == FruitX && SnakeHeadY == FruitY)
                        {
                            Score += 10;
                            FruitX = rand() % width;
                            FruitY = rand() % hight;
                            TailLenght++;
                        }
        }
        ~SnakeGame()   //destructor
        {
            cout<< "You Lost The Game, Better Luck Next Time " <<endl;
        }
};

int main()
{
    SnakeGame snake;
    snake.Setup();

    while(!GameOver)
    {
        snake.Draw();
        snake.Input();
        snake.Logic();
        Sleep(70);
    }
    return 0;
}


/*  o
    o       o
    o       o     o
    O       oO    ooO     ooooO
*/
