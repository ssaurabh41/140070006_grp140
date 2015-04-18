#ifndef DRAW_IMAGE_ON_WINDOW
#define DRAW_IMAGE_ON_WINDOW

//void CallBackFunc(int event ,int x,int y,int flags,void* userdata);
void draw_the_line(int px, int py, int x, int y, Mat &image, vector<Points> &path);
void draw_the_line_white(int px, int py, int x, int y, Mat &image);

#endif // DRAW_IMAGE_ON_WINDOW
