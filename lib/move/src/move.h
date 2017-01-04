#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

#define MAX_X  4
#define MAX_Y  4
#define MAX_Z  4
#define SNAKE_LENGHT 8

//int led_cube[][][];

typedef struct
{
    int x;
    int y;
    int z;
    Direction direction;
} Snakesegment;

typedef struct
{
   Snakesegment segment[SNAKE_LENGHT];
   int size;
} Snake;

typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    BACK,
    FORTH,
} Direction;

bool is_cell_occupied[MAX_X][MAX_Y][MAX_Z];

#ifdef __cplusplus
}
#endif

#endif
