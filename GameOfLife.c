#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define WIDTH 200
#define HEIGHT 100
#define BACKGROUND '-'
#define SPEED 100
#define CELL 'E'

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
            if (rand() % 5 == 0 && rand() % 2 == 0)
            {
                grid[i][j].state = ALIVE;
                continue;
            }
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
    Cell new_grid[WIDTH][HEIGHT] = {0};

    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            new_grid[i][j].state = grid[i][j].state;
        }
    }

    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            int alive_count = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int row = (i + k) % HEIGHT;
                    int col = (j + l) % WIDTH;
                    if (k == 0 && l == 0)
                        continue;
                    if (grid[row][col].state == ALIVE)
                        alive_count++;
                }
            }
            switch (alive_count)
            {
            case 0:
            case 1:
                new_grid[i][j].state = DEAD;
                break;
            case 2:
            case 3:
                if (grid[i][j].state == DEAD && alive_count == 3)
                {
                    new_grid[i][j].state = ALIVE;
                }
                break;
            default:
                new_grid[i][j].state = DEAD;
                break;
            }
        }
    }

    for (size_t i = 0; i < HEIGHT; i++)
    {
        for (size_t j = 0; j < WIDTH; j++)
        {
            grid[i][j].state = new_grid[i][j].state;
        }
    }
}

int main()
{
    srand(time(NULL));
    init_grid();
    system("clear");
    while (print_grid() != 0)
    {
        usleep(SPEED * 1000);
        gen_next();
        system("clear");
    }
    return 0;
}