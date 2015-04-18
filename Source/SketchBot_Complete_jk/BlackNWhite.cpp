#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

#include "global_variables.h"

using namespace cv;

//function overloading is done

//first using 150 as the threshhold value...the input image gets changed
void BlackNWhite(Mat &image_in_grayscale)
{
    for(int i=0;i<image_in_grayscale.cols;i++)
        for(int j=0;j<image_in_grayscale.rows;j++)
        {
            if((image_in_grayscale.at<uchar>(j,i))<150)
                image_in_grayscale.at<uchar>(j,i)=0;
            else image_in_grayscale.at<uchar>(j,i)=255;
        }
}

//next if user wants to set a threshhold value of his...the input image gets changed
//this one is used in the main function
void BlackNWhite(Mat &image_in_grayscale, unsigned char threshhold)
{
    for(int i=0;i<image_in_grayscale.cols;i++)
        for(int j=0;j<image_in_grayscale.rows;j++)
        {
            if((image_in_grayscale.at<uchar>(j,i))<threshhold)
                image_in_grayscale.at<uchar>(j,i)=0;
            else image_in_grayscale.at<uchar>(j,i)=255;
        }
}

//here if user doesnt want the input image to change, he can provide an output image (threshhold = 150)
void BlackNWhite(Mat &input, Mat &output)
{
    for(int i=0;i<input.cols;i++)
        for(int j=0;j<input.rows;j++)
        {
            if((input.at<uchar>(j,i))<150)
                output.at<uchar>(j,i)=0;
            else output.at<uchar>(j,i)=255;
        }
}

//output image is different and option to set the threshhold value by user
void BlackNWhite(Mat &input, Mat &output, unsigned char threshhold)
{
    for(int i=0;i<input.cols;i++)
        for(int j=0;j<input.rows;j++)
        {
            if((input.at<uchar>(j,i))<threshhold)
                output.at<uchar>(j,i)=0;
            else output.at<uchar>(j,i)=255;
        }
}

