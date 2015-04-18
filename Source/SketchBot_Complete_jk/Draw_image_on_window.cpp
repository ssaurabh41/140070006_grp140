#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv/cv.h>
#include<iostream>
#include "Points.h"
#include "global_variables.h"

using namespace cv;
using namespace std;

//draws a continuous line between 2 points and stores the points in path
void draw_the_line(int px, int py, int x, int y, Mat &image, vector<Points> &path)
{
    Points A(0,0);
    if(x>px)
    {
        for(int i=px;i<x;i++)
            if(y>py)
                for(int j=y+(i-x)*(py-y)/(px-x);j<=y+(i-x+1)*(py-y)/(px-x);j++)
                {
                    A={i,j};
                    path.push_back(A);
                    image.at<uchar>(j,i)=0;
                    image.at<uchar>(j+1,i)=0;
                    image.at<uchar>(j-1,i)=0;
                    image.at<uchar>(j,i+1)=0;
                    image.at<uchar>(j,i-1)=0;
                }

            else
                for(int j=y+(i-x)*(py-y)/(px-x);j>=y+(i-x+1)*(py-y)/(px-x);j--)
                {
                    A={i,j};
                    path.push_back(A);
                    image.at<uchar>(j,i)=0;
                    image.at<uchar>(j+1,i)=0;
                    image.at<uchar>(j-1,i)=0;
                    image.at<uchar>(j,i+1)=0;
                    image.at<uchar>(j,i-1)=0;
                }
    }
    else if(x<px)
    {
        for(int i=px;i>x;i--)
            if(y>py)
                //for(int j=y+(i-x)*(py-y)/(px-x);j>=y+(i-x+1)*(py-y)/(px-x);j--)
                for(int j=y+(i-x)*(py-y)/(px-x);j<=y+(i-x-1)*(py-y)/(px-x);j++)
                    {
                        A={i,j};
                        path.push_back(A);
                        image.at<uchar>(j,i)=0;
                        image.at<uchar>(j+1,i)=0;
                        image.at<uchar>(j-1,i)=0;
                        image.at<uchar>(j,i+1)=0;
                        image.at<uchar>(j,i-1)=0;
                    }
            else
                //for(int j=y+(i-x)*(py-y)/(px-x);j<=y+(i-x+1)*(py-y)/(px-x);j++)
                for(int j=y+(i-x)*(py-y)/(px-x);j>=y+(i-x-1)*(py-y)/(px-x);j--)
                    {
                        A={i,j};
                        path.push_back(A);
                        image.at<uchar>(j,i)=0;
                        image.at<uchar>(j+1,i)=0;
                        image.at<uchar>(j-1,i)=0;
                        image.at<uchar>(j,i+1)=0;
                        image.at<uchar>(j,i-1)=0;
                    }
    }
    else if(x==px)
    {
        if(py>y)
            for(int j=py;j>=y;j--)
            {
                A={x,j};
                path.push_back(A);
                image.at<uchar>(j,x)=0;
                image.at<uchar>(j+1,x)=0;
                image.at<uchar>(j-1,x)=0;
                image.at<uchar>(j,x+1)=0;
                image.at<uchar>(j,x-1)=0;
            }
        else
            for(int j=py;j<=y;j++)
            {
                A={x,j};
                path.push_back(A);
                image.at<uchar>(j,x)=0;
                image.at<uchar>(j+1,x)=0;
                image.at<uchar>(j-1,x)=0;
                image.at<uchar>(j,x+1)=0;
                image.at<uchar>(j,x-1)=0;
            }
    }
}

//makes a white line between the points i.e. erases that part of image.
void draw_the_line_white(int px, int py, int x, int y, Mat &image)
{
    Points A(0,0);
    if(x>px)
    {
        for(int i=px;i<x;i++)
            if(y>py)
                for(int j=y+(i-x)*(py-y)/(px-x);j<=y+(i-x+1)*(py-y)/(px-x);j++)
                {
                    for(int a=i-1;a<=i+1;a++)
                        for(int b=j-1;b<=j+1;b++)
                        image.at<uchar>(b,a)=255;
                }

            else
                for(int j=y+(i-x)*(py-y)/(px-x);j>=y+(i-x+1)*(py-y)/(px-x);j--)
                {
                    for(int a=i-1;a<=i+1;a++)
                        for(int b=j-1;b<=j+1;b++)
                        image.at<uchar>(b,a)=255;
                }
    }
    else if(x<px)
    {
        for(int i=px;i>x;i--)
            if(y>py)
                for(int j=y+(i-x)*(py-y)/(px-x);j<=y+(i-x-1)*(py-y)/(px-x);j++)
                    {
                        for(int a=i-1;a<=i+1;a++)
                        for(int b=j-1;b<=j+1;b++)
                        image.at<uchar>(b,a)=255;
                    }
            else
                for(int j=y+(i-x)*(py-y)/(px-x);j>=y+(i-x-1)*(py-y)/(px-x);j--)
                    {
                        for(int a=i-1;a<=i+1;a++)
                        for(int b=j-1;b<=j+1;b++)
                        image.at<uchar>(b,a)=255;
                    }
    }
    else if(x==px)
    {
        if(py>y)
            for(int j=py;j>=y;j--)
            {
                for(int a=x-1;a<=x+1;a++)
                    for(int b=j-1;b<=j+1;b++)
                        image.at<uchar>(b,a)=255;
            }
        else
            for(int j=py;j<=y;j++)
            {
                for(int a=x-1;a<=x+1;a++)
                    for(int b=j-1;b<=j+1;b++)
                        image.at<uchar>(b,a)=255;
            }
    }
}
