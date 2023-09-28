#include <stdio.h>
#include <math.h>

enum e_direction
{
		NORTH = 90,
		SOUTH = 270,
		EAST = 0,
		WEST = 180
};

typedef struct s_vector
{
	float x;
	float y;
};

#define FOV 60
#define H_FOV 30
#define PLAYER_POS_X 2 
#define PLAYER_POS_Y 3
#define PLAYER_DIR NORTH
#define PLANE_W 320
#define PLANE_H 200
#define PLANE_HW 160
#define RAY_INCREMENT 60/320

const int map[] = {
	1,1,1,1,1,1,
	1,0,0,0,0,1,
	1,0,0,0,0,1,
	1,0,0,0,0,1,
	1,1,1,1,1,1
};

void distance_to_wall();

void	check_if_wall()
{
	check_horizontal();
	check_vertical();
}

void raycast()
{
	int	i;
	int	ray_angle;

	ray_angle = PLAYER_DIR - H_FOV; 
	i = 0;
	while (i < PLANE_X)
	{

		i++;
		ray_angle += RAY_INCREMENT;
	}
}

int	main(void)
{
	raycast();
	check_if_wall();
	return (0);
}
