#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

#include "global_variables.h"

using namespace cv;

//checks src_in_blackNwhite for black points which have white pixels surrounding them. These are boundary points and shown in the output image
void detect_borders(Mat src_in_blackNwhite, Mat output)
{
    for(int i=0;i<output.cols;i++)
        for(int j=0;j<output.rows;j++)
            output.at<uchar>(j,i)=255;

    for(int i=1;i<src_in_blackNwhite.cols-1;i++)
    {
        for(int j=1;j<src_in_blackNwhite.rows-1;j++)
        {
            if(src_in_blackNwhite.at<uchar>(j,i)==0)
            {for(int x=i-1;x<=i+1;x++)
            {
                for(int y=j-1;y<=j+1;y++)
                {
                    if(src_in_blackNwhite.at<uchar>(y,x)==255)
                    {
                        output.at<uchar>(j,i)=0; break;
                    }
                }
            }
            }
        }
    }
}

//this one is based on difference in intensity values between adjacent pixels however the previous one is found to work better in most cases
void better_detect_borders(Mat src_in_grayscale, Mat output)
{
    for(int i=1;i<src_in_grayscale.cols-1;i++)
        for(int j=1;j<src_in_grayscale.rows-1;j++)
        {
            bool isBorder=0;
            unsigned char intensity=src_in_grayscale.at<uchar>(j,i);
            for(int x=i-1;x<=i+1;x++)
            {
                for(int y=j-1;y<=j+1;y++)
                {
                    if(x==i && y==j) continue;
                    if(intensity-src_in_grayscale.at<uchar>(y,x)>100 || src_in_grayscale.at<uchar>(y,x)-intensity>100)
                    {
                        isBorder=1; break;
                    }
                }
                if(isBorder) break;
            }
            if(isBorder) output.at<uchar>(j,i)=0;
            else output.at<uchar>(j,i)=255;
        }
}

//some borders better detected by the later code while others by the previous one.


