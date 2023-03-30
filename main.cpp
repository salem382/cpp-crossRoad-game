#include <iostream>
#include<conio.h>
#include <ctime>
#include <deque>
using namespace std;
class cplayer
{
private:
    int x, y, originalX, originalY;
public:
    cplayer(int width)
    {
        x = originalX = width / 2;
        y = originalY = 0;
    }
    void Reset()
    {
        x = originalX;
        y = originalY;
    }
    void moveUp() { y--; }
    void moveDwon() { y++; }
    void moveLeft() { x--; }
    void moveRight() { x++; }
    inline int getX() { return x; }
    inline int getY() { return y; }
};
class clane
{
private:
    int width, right;
    deque<bool>cars;
public:
    clane(int w)
    {
        width = w;
        for (int i = 0; i < width; i++)
            cars.push_front(true);
        right = rand() % 2;
    }
    void move()
    {
        if (right == 1)
        {
            if (rand() % 10 == 1)
            {
                cars.push_front(true);
                cars.pop_back();
            }
            else
            {
                cars.push_front(false);
                cars.pop_back();
            }
        }
        else
        {
            if (rand() % 10 == 1)
            {
                cars.push_back(true);
                cars.pop_front();
            }
            else
            {
                cars.push_back(false);
                cars.pop_front();
            }

        }
    }
    inline bool getPosition(int x) { return cars[x]; }
};
class game
{
    bool quit;
    int width, height, score;
    cplayer* player;
    deque <clane*> map;
public:
    game(int w, int h)
    {
        width = w;
        height = h;
        quit = false;
        player = new cplayer(w);
        for (int i = 0; i < height; i++)
            map.push_back(new clane(w));
    }
    void Draw()
    {
        system("cls");
        int playerY = player->getY();
        int playerX = player->getX();
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                //upMap
                if (i == 0 && (j == 0 || j == width - 1))
                    cout << "s";
                else if (i == height - 1 && (j == 0 || j == width - 1))
                    cout << "f";
                //player
                else if (i == playerY && j == playerX)
                    cout << "V";
                //cars
                else if (map[i]->getPosition(j) == true && i != 0 && i != height - 1)
                    cout << "#";
                else
                    cout << " ";
            }
            cout << endl;
        }
        cout << "score: " << score << endl;
    }
    void Input()
    {
        if (_kbhit())
        {
            char c = _getch();
            if (c == 'w')
            {
                if (player->getY() > 0)
                    player->moveUp();
            }
            else if (c == 's')
                player->moveDwon();
            else if (c == 'a')
                player->moveLeft();
            else if (c == 'd')
                player->moveRight();
            else if (c == 'q')
                quit = true;
        }
    }
    void Logic()
    {
        //move
        for (int i = 0; i < height; i++)
        {
            if (rand() % 10 == 1)
                map[i]->move();
        }
        //win
        if (player->getY() == height - 1)
        {
            player->Reset();
            score++;
        }
        //gameOver
        for (int i = 1; i < height - 1; i++)
        {
            if (map[i]->getPosition(player->getX()) == true && i == player->getY())
                quit = true;
        }
    }
    void Run()
    {
        while (!quit)
        {
            Draw();
            Input();
            Logic();
        }
    }
};
int main()
{
    srand(time(0));
    game g(20, 10);
    g.Run();
}
