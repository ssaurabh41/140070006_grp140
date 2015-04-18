#include "global_variables.h"
#include "Points.h"
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

using namespace std;
using namespace cv;

//clears a point once crossed to avoid infinite recursion.
void clear_traversed_point(Mat image_only_borders, Points p)
{
        image_only_borders.at<uchar>(p.y,p.x)=255;
}
