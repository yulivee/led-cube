#include "move.h"
/*
 *  D0  D1  D2  D3   |  0,0  1,0  2,0  3,0
 *                   |
 *  D4  D5  D6  D7   |  0,1  1,1  2,1  3,1
 *                   |
 *  D8  D9  D10 D11  |  0,2  1,2  2,2  3,2
 *                   |
 *  D12 D13 D14 D15  |  0,3  1,3  2,3  3,3
 *
 *  Nodes on L0:
 *  Corner - 3 degrees of freedom: D0 D3 D12 D15
 *  Edge   - 4 degrees of freedom: D1 D2 D4 D8 D7 D11 D13 D14
 *  Bottom - 5 degrees of freedom: D5 D6 D9 D10
 *
 *  Nodes on L1 and L2:
 *  Edge   - 4 degrees of freedom: D0 D3 D12 D15
 *  Bottom - 5 degrees of freedom: D1 D2 D4 D8 D7 D11 D13 D14
 *  Cube   - 6 degrees of freedom: D5 D6 D9 D10
 *
 *  Nodes on L3:
 *  Corner - 3 degrees of freedom: D0 D3 D12 D15
 *  Edge   - 4 degrees of freedom: D1 D2 D4 D8 D7 D11 D13 D14
 *  Bottom - 5 degrees of freedom: D5 D6 D9 D10
 *
 */

void get_directions( int *dir_x, int *dir_y, int *dir_z, Direction direction )/*{{{*/
{
    switch (direction) {
    case UP:
        *dir_x = 0;
        *dir_y = 0;
        *dir_z = 1;
        break;
    case DOWN:
        *dir_x = 0;
        *dir_y = 0;
        *dir_z = -1;
        break;
    case RIGHT:
        *dir_x = 1;
        *dir_y = 0;
        *dir_z = 0;
        break;
    case LEFT:
        *dir_x = -1;
        *dir_y = 0;
        *dir_z = 0;
        break;
    case BACK:
        *dir_x = 0;
        *dir_y = -1;
        *dir_z = 0;
        break;
    case FORTH:
        *dir_x = 0;
        *dir_y = 1;
        *dir_z = 0;
        break;
    default:
        *dir_x = 0;
        *dir_y = 0;
        *dir_z = 0;
        break;
    }
}/*}}}*/

void init( Snake snake, int size, int x, int y, int z, Direction direction )/*{{{*/
{
    snake.size = size;

    for ( int i = 0; i < size; i++ ) {
        if ( i == 0 ) {
            snake.segments[i].x = x;
            snake.segments[i].y = y;
            snake.segments[i].z = z;
        } else {
            int dir_x, dir_y, dir_z;
            get_directions( &dir_x, &dir_y, &dir_z, snake.segments[i-1].direction);
            snake.segments[i].x = snake.segments[i-1].x - dir_x;
            snake.segments[i].y = snake.segments[i-1].y - dir_y;
            snake.segments[i].z = snake.segments[i-1].z - dir_z;
        }
        snake.segments[i].direction = direction;
        is_cell_occupied[snake.segments[i].x][snake.segments[i].y][snake.segments[i].z] = true;
    }
}/*}}}*/

void grow( Snake snake, const Snakesegment *new_segment)
{
    snake.segments[snake.size++] = *new_segment;
    is_cell_occupied[snake.segments[snake.size+1].x][snake.segments[snake.size+1].y][snake.segments[snake.size+1].z] = 1;
}

bool is_valid_move( Snake snake, int new_head_x, int new_head_y, int new_head_z )/*{{{*/
{
    if ( new_head_x >= MAX_X ||
            new_head_x < 0 ||
            new_head_y >= MAX_Y ||
            new_head_y < 0 ||
            new_head_z >= MAX_Z ||
            new_head_z < 0 ||
            ( is_cell_occupied[new_head_x][new_head_y][new_head_z] &&
              !( new_head_x == snake.segments[snake.size - 1].x &&
                 new_head_y == snake.segments[snake.size - 1].y &&
                 new_head_z == snake.segments[snake.size - 1].z
               )
            )
       ) {
        return false;
    }

    return true;
}/*}}}*/

Direction get_dir(Snake snake)/*{{{*/
{
    if (snake.size == 0) {
        return 0;
    }

    return snake.segments[0].direction;
}/*}}}*/

void set_dir(Snake snake, Direction direction)/*{{{*/
{
    if (snake.size != 0) {
        snake.segments[0].direction = direction;
    }
}/*}}}*/

void init_segment(Snake snake, int i)/*{{{*/
{
    snake.segments[i] = (Snakesegment) {
        0, 0, RIGHT
    };
}/*}}}*/

bool snake_chdir( Snake snake )/*{{{*/
{

    bool invalid_move = true;
    int new_direction;
    while( invalid_move ) {
        int new_direction = random(4,9);
        int dir_x, dir_y, dir_z;
        get_directions(&dir_x, &dir_y, &dir_z, new_direction);
        if( is_valid_move( snake, dir_x, dir_y, dir_z ) ) {
            invalid_move = 0;
        }
    }

    set_dir(snake, new_direction);

    // if the snake is not full size yet, grow it
    if ( snake.size < SNAKE_LENGHT ) {
        snake_grow( snake, &snake.segments[snake.size - 1] );
    }

    move(snake);

    return 1;

}/*}}}*/

bool move( Snake snake )/*{{{*/
{

    int dir_x, dir_y, dir_z;

    for (int i = snake.size - 1; i >= 0; i--) {

        //for the last snake segment
        if ( i == snake.size - 1 && snake.size == SNAKE_LENGHT ) {
            //clear field
            is_cell_occupied[snake.segments[i].x][snake.segments[i].y][snake.segments[i].z] = false;
        }

        // copy directions to the next snake segment
        get_directions( &dir_x, &dir_y, &dir_z, snake.segments[i].direction );
        snake.segments[i].x += dir_x;
        snake.segments[i].y += dir_y;
        snake.segments[i].z += dir_z;

        //for the the snake head
        if ( i == 0 ) {
            //block field
            is_cell_occupied[snake.segments[i].x][snake.segments[i].y][snake.segments[i].z] = true;
        }
    }

    //
    for (int i = snake.size - 1; i >= 1; i--) {
        snake.segments[i].direction = snake.segments[i - 1].direction;
    }

    return true;

}/*}}}*/
