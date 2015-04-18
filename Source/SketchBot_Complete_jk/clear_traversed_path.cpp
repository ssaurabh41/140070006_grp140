#include "global_variables.h"
#include "Points.h"
#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

using namespace std;
using namespace cv;


//makes a 3x3 box around every pixel present in path white in the image entered.
//this is to remove excess pixels which might remain after a path is generated
/*
    say image is like this:
          *
          **
           *
    then as the path is made, it becomes ->     x       ->   x        ->       x
                                                **           x*                x*
                                                 *            *                 x

    so  one of the * has remained. It doesnt belong to a different path and so must be deleted
*/
void clear_traversed_path(Mat image_only_borders, vector<Points> &path)
{
    vector<Points>::iterator it=path.begin();
    for(it=path.begin()+1;it!=path.end()-1;++it)
    {

        for(int x=it->x-1;x<=it->x+1;x++)
            for(int y=it->y-1;y<=it->y+1;y++)
            {

                bool isAtStart=0;
                for(int a=(path.begin()->x)-1;a<=(path.begin()->x)+1;a++)
                {
                    for(int b=(path.begin()->y)-1;b<=(path.begin()->y)+1;b++)
                        if(x==a && y==b)
                        {
                            isAtStart=1;
                            break;
                        }
                    if(isAtStart) break;
                }
                if(!isAtStart)  image_only_borders.at<uchar>(y,x)=255;
            }
    }
}

//check for whether point is around start point




