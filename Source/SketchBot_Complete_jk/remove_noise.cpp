#include <opencv2/core/core.hpp>
#include <opencv/cv.h>
#include <iostream>

#include "global_variables.h"

using namespace cv;

//removes isolated pixels
//we have also added an extra feature which enables the user to erase points (by RightMouse click + drag) which he doesnt want in final drawing
void reduce_noise(Mat image_only_borders)
{
    bool isNoise=1;
    for(int i=1;i<image_only_borders.cols-1;i++)
    {
        for(int j=1;j<image_only_borders.rows-1;j++)
        {
            if(image_only_borders.at<uchar>(j,i)==0)
            {
                for(int x=i-1;x<=i+1;x++)
                {
                    for(int y=j-1;y<=j+1;y++)
                        if((image_only_borders.at<uchar>(y,x)==0) && !(x==i&&y==j))
                        {
                            isNoise=0;
                            break;
                        }
                    if(isNoise==0) break;
                }
                if(isNoise==1) {image_only_borders.at<uchar>(j,i)=255; /*std::cout<<"change\n";*/}
                isNoise=1;
            }
        }
    }
}
