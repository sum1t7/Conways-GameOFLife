#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 25
#define HEIGHT 25
#define BACKGROUND '-'
#define SPEED 100
#define CELL 'O'

typedef enum
{
    DEAD,
    ALIVE
} State;

typedef struct
{
    State state;
} Cell;

// GRID STUFF
Cell grid[WIDTH][HEIGHT] = {0};
 
void init_grid()
{
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {

            grid[i][j].state = DEAD;
        }
    }
}

int print_grid()
{
    int alive_count = 0;
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            if (grid[i][j].state == ALIVE)
            {
                alive_count++;
                printf("%c", CELL);
            }
            else
            {
                printf("%c", BACKGROUND);
            }
        }
        printf("\n");
    }
    return alive_count;
}

void gen_next()
{
    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            int alive_count = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (k == 0 && l == 0)
                        continue;
                    if (i + k < HEIGHT && i + k >= 0 && j + l < WIDTH && j + l >= 0)
                    {
                        if (grid[i + k][j + l].state == ALIVE)
                            alive_count++;
                    }
                }
            }
            switch (alive_count)
            {
            case 0:
            case 1:
                grid[i][j].state = DEAD;
                break;
            case 2:
            case 3:
                if (grid[i][j].state == DEAD && alive_count == 3)
                    grid[i][j].state = ALIVE;
                break;
            default:
                grid[i][j].state = DEAD;
                break;
            }
        }
    }

     
}

int main()
{
    init_grid();
    for (size_t i = 0; i < WIDTH / 5; i++)
    {
        for (size_t j = 0; j < HEIGHT / 5; j++)
        {
            grid[i][j].state = ALIVE;
        }
    }
 
    while (print_grid() != 0)
    {
        Sleep(SPEED);
        gen_next();
        system("cls");
    }
    return 0;
}