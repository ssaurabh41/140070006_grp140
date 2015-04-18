#ifndef PATH_ALGO_RELATED_FUNCTIONS_H
#define PATH_ALGO_RELATED_FUNCTIONS_H

#include "global_variables.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include "Points.h"
#include "image_functions.h"

using namespace cv;

Points startingPoint(Mat image_onlyBlackBorders);

void clear_traversed_point(Mat image_only_borders, Points p);

Points nextPoint(Mat image_only_borders, Points p);

bool make_a_path(Mat image_only_borders, vector<Points> &path);

void clear_traversed_path(Mat image_only_borders, vector<Points> &path);

Points nextPointToDraw(vector<Points>::iterator it, vector<Points> &path, float distance_resolution=5, float rotation_resolution=4);


//these are copy-paste as in the atmel code
int calc_rotate_angle(Points current_point, Points next_point, float current_angle);

float calc_distance(Points current_point, Points next_point);

void update_current_angle(Points current_point, Points next_point, float &current_angle);


//incomplete
void merge_paths(vector<Points> &path1, vector<Points> &path2, bool &isPath1, bool &isPath2);

#endif // PATH_ALGO_RELATED_FUNCTIONS_H
