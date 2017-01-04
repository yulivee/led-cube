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

void snake_init( Snake snake, int size, int x, int y, int z, Direction direction) {
    snake.size = size;
    snake.x = x;
    snake.y = y;
    snake.z = z;
    snake.Direction = direction;
    is_cell_occupied[x][y][z] = 1;
}

void snake_grow(const Snakesegment *new_segment)
{
    snake.segments[snake.size++] = *new_segment;
    is_cell_occupied[x][y][z] = 1;
}

bool is_valid_move(int new_head_x, int new_head_y, int new_head_z )
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
                 new_head_z == snake.segments[snake.size - 1].z &&
               )
            )
       )
    {
        return false;
    }

    return true;
}

Dir get_dir()
{
    if (snake.size == 0) {
        return 0;
    }

    return snake.segments[0].dir;
}

void set_dir(Dir dir)
{
    if (snake.size != 0) {
        snake.segments[0].dir = dir;
    }
}

void init_segment(Snake snake, int i)
{
    snake.segments[i] = (SnakeSegment) {
        0, 0, RIGHT
    };
}

snake_chdir( Snake snake )
{

    bool invalid_move = 1;
    int new_direction;
    while( invalid_move ) {
	new_direction = random(4,9);
        if( is_valid_move( new_direction ) ) {
            invalid_move = 0;
        }
    }

    snake_set_dir(new_direction);

    // if the snake is not full size yet, grow it
    if ( snake.size < SNAKE_LENGHT ) {
        snake_grow(snake);
    }

    move(snake);

}

void get_directions( int *dir_x, int *dir_y, int *dir_z, Dir dir ) {
{
    switch (dir) {
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
}


bool move( Snake snake ) {

   int dir_x, dir_y, dir_z;

   for (int i = snake.size - 1; i >= 0; i--) {

        //for the last snake segment
        if ( i == snake.size - 1 && snake.size == SNAKE_LENGHT ) {
            //clear field
            is_cell_occupied[snake.segments[i].x][snake.segments[i].y][snake.segments[i].z] = false;
	}

	// copy directions to the next snake segment
	get_directions( &dir_x, &dir_y, &dir_z, snake.segments[i].dir );
	snake.segments[i].x += dx;
	snake.segments[i].y += dy;
	snake.segments[i].z += dz;

        //for the the snake head
        if ( i == 0 ) {
            //block field
            is_cell_occupied[snake.segments[i].x][snake.segments[i].y][snake.segments[i].z] = true;
	}

    // 
    for (int i = snake.size - 1; i >= 1; i--) {
        snake.segments[i].dir = snake.segments[i - 1].dir;
    }   

	return true;

}
