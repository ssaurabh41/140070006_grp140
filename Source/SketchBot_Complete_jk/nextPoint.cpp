#include "global_variables.h"
#include "Points.h"
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

using namespace std;
using namespace cv;

//returns an adjacent black point(i.e. in a 3x3 box)
Points nextPoint(Mat image_only_borders, Points p)
{
    for(int i=p.x-1;i<=p.x+1;i++)
        for(int j=p.y-1;j<=p.y+1;j++)
        {
            if(i==p.x && j==p.y);
            else if(image_only_borders.at<uchar>(j,i)==0) return Points(i,j);
        }
    return Points(-1,-1);
}
