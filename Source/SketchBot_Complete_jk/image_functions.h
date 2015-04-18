#ifndef IMAGE_FUNCTIONS_H
#define IMAGE_FUNCTIONS_H

#include <opencv/cv.h>
using namespace cv;

void BlackNWhite(Mat &B);
void BlackNWhite(Mat &input, Mat&output);
void BlackNWhite(Mat &A, unsigned char threshhold);
void BlackNWhite(Mat &input, Mat &output, unsigned char threshhold);

void resize_image(int MAX_WINDOW_HEIGHT, int MAX_WINDOW_WIDTH, const Mat &A, Mat &B);

void convert_drawing_resolution(string units);

void detect_borders(Mat src_in_blackNwhite, Mat output);
void better_detect_borders(Mat src_in_grayscale, Mat output);

void reduce_noise(Mat image_only_borders);

#endif // IMAGE_FUNCTIONS_H

