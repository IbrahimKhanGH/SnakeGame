// Ibrahim Khan 
// Snake Game


#include <iostream> // cin, cout
#include <conio.h>  // console IO
#include <windows.h>

using namespace std;

// global variables
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;

void Setup() // sets up the game and the head of the snake
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2; // position of the snake starts in the middle
    fruitX = rand() % width;
    fruitY = rand() % height; // randomizes the position of the fruit
    score = 0;
}

void Draw() // this draws the entire game, including border
{
    system("cls"); //system("clear");
    for (int i = 0; i < width+2; i++)
    {
        cout << "#"; // this makes the border
    }
    cout << endl;
 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#"; // this makes the border
            }
            if (i == y && j == x)
            {
                cout << "O"; // initial start of snake head
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "F"; // adds an F where the fruit is placed
            }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o"; // adds to the tail of the snake
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }            
            }
            if (j == width - 1)
            {
                cout << "#"; // this prints the border
            }
        }
        cout << endl;
    }
 
    for (int i = 0; i < width+2; i++)
    {
        cout << "#"; // this prints the border
    }

    cout << endl;
    cout << "Score:" << score << endl; // prints the score
}

void Input() // input of the user
{
    if (_kbhit())
    {
        switch (_getch())
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
        case 'x': // killswicth/endgame
            gameOver = true;
            break;
        }
    }
}


void Logic() // the logic of the game (score addition, snake head running into itself, border reset)
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) // the users input changes the position of the snake head
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
  
    if (x > width || x < 0 || y > height || y < 0)
      gameOver = true;
 
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
 
    if (x == fruitX && y == fruitY) 
    {
        score += 10; // adds 10 to the score and randomizes a new fruit
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++; // adds one to the tail
    }
}

int main() // main function
{
    Setup(); // sets up the game
    while (!gameOver) // keeps running until something ends the game
    {
        Draw(); // draws the game
        Input(); // this is the users movement
        Logic(); // adds the score and kills the game based on the input
        Sleep(10); //sleep(10);
    }
    return 0;
}
