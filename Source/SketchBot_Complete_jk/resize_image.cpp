#include <opencv2/core/core.hpp>
#include <opencv/cv.h>

#include "global_variables.h"

using namespace cv;

int final_height, final_width;

//resizes image in case of uploaded image to a maximum height and maximum width in a proportional manner
//image isnt cropped or distorted
void resize_image(int MAX_WINDOW_HEIGHT, int MAX_WINDOW_WIDTH, const Mat &A, Mat &B)
{
    Size orig_size=A.size();

    final_height=orig_size.height;
    final_width=orig_size.width;
    if(orig_size.height>=MAX_WINDOW_HEIGHT)
        {
            final_height=MAX_WINDOW_HEIGHT;
            final_width=(orig_size.width*final_height)/orig_size.height;
        }
    if(final_width>=MAX_WINDOW_WIDTH)
        {
            final_height=(final_height*MAX_WINDOW_WIDTH)/final_width;
            final_width=MAX_WINDOW_WIDTH;
        }

    Size resize_to(final_width,final_height);

    resize(A, B, resize_to);
}

