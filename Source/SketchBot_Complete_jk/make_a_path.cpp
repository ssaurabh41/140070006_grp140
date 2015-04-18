#include "global_variables.h"
#include "Points.h"
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>
#include "path_algo_related_functions.h"

using namespace std;
using namespace cv;

//Here i have used a vector to store the black pixels as encountered in a path in proper order.
//returns 0 if no path present
//returns 1 if a path is successfully  determined and stored
bool make_a_path(Mat image_only_borders, vector<Points> &path)
{
    //first check whether we have a path remaining i.e. a black pixel
    if(startingPoint(image_only_borders).x==-1) return 0;
    path.push_back(startingPoint(image_only_borders));
    vector<Points>::iterator it=path.end()-1;

    //next search for a black point in the vicinity of the point already in path to take as the next point in path. If no such point found, the function returns.
    while(nextPoint(image_only_borders,*it).x!=-1)
    {

        path.push_back(nextPoint(image_only_borders,*it));
        imshow("No Noise",image_only_borders);
        clear_traversed_point(image_only_borders,*(path.end()-2));   //the point once added to path is cleared to prevent infinite recursion
        //waitKey(1);
        it=path.end()-1;
    }

    //remove single dots remaining
    reduce_noise(image_only_borders);
    return 1;
}
