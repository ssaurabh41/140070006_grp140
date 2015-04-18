#include <opencv2/core/core.hpp>
#include <opencv/cv.h>
#include "global_variables.h"
#include "Points.h"

using namespace std;
using namespace cv;

//returns class Points. If no black pixel left, returns (-1,-1). Input: image consisting of only borders.
Points startingPoint(Mat image_onlyBlackBorders)
{
    for(int i=0;i<image_onlyBlackBorders.cols;i++)
        for(int j=0;j<image_onlyBlackBorders.rows;j++)
            if(image_onlyBlackBorders.at<uchar>(j,i)==0) return Points(i,j);
    return Points(-1,-1);
}
