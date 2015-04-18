#include "Points.h"
#include <math.h>


//the complete explaination for these functions can be found in the Atmel code

//calculates the angle to rotate given the starting coordinates, final coordinates and the current orientation of the bot
int calc_rotate_angle(Points current_point, Points next_point, float current_angle)
{
	float x;
	if(next_point.x==current_point.x)
	{
		if (next_point.y==current_point.y) return 0;
		else if(next_point.y>current_point.y) x=90;
		else if(next_point.y<current_point.y)x=-90;
	}
	else x=atan2(next_point.y-current_point.y, next_point.x-current_point.x)*180/3.1416;

	float angle_to_rotate = current_angle-x;

	if(angle_to_rotate<(-180)) angle_to_rotate+=360.0;
	if(angle_to_rotate>180)    angle_to_rotate-=360.0;                                              //angle is in clockwise direction

	return int(angle_to_rotate);
}

//calculates distance between 2 points
float calc_distance(Points current_point, Points next_point)
{
	return sqrt(pow(current_point.x-next_point.x,2)+pow(current_point.y-next_point.y,2));
}

//updates the current orientation of the bot. To be executed after the bot completes the move
void update_current_angle(Points current_point, Points next_point, float &current_angle)
{
	if(next_point.x==current_point.x)
	{
		if(next_point.y==current_point.y) return;
		if(next_point.y-current_point.y>0) current_angle=90;
		else current_angle=-90;
	}
	else current_angle=atan2(next_point.y-current_point.y, next_point.x-current_point.x)*180/3.1416;
}
