#include "global_variables.h"
#include "Points.h"
#include "path_algo_related_functions.h"
#include <vector>

//this is to search in a path for points which can be drawn by the bot (fits the least count of various movements of bot.
//not used in main function as of now. There the code is reproduced.
Points nextPointToDraw(std::vector<Points>::iterator it, std::vector<Points> &path, float current_angle, float distance_resolution, float rotation_resolution)
{
    Points current_point=*it;
    float distance;
    int angleToRotate;

    while(it<path.end())
    {
        distance=calc_distance(current_point, *(it+1));
        angleToRotate=calc_rotate_angle(current_point, *(it+1), current_angle);
        if(distance>distance_resolution && angleToRotate>rotation_resolution)
        {
            break;
        }
        it++;
    }
    it++;
    return *(it);
}
