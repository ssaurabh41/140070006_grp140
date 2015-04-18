#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>
#include <iostream>

using namespace cv;
using namespace std;

//analyser for the purpose of making the '!' back to ' ' which we had deliberately done in java so that theres no problem in cin in cpp
string analyser(string input)
{
    string output="";
    string substring;
    for(int i=0;i<input.length();++i){
        substring=input.substr(i,1);

        if(substring.compare("!")==0){
            substring=" ";
        }
        output.append(substring);
    }
    return output;
}

#include "Points.h"
#include "image_functions.h"
#include "global_variables.h"
#include "path_algo_related_functions.h"
#include "Draw_image_on_window.h"
#include "windowsh.h"
#include "parsing.h"


void CallBackFunc(int event ,int x,int y,int flags,void* userdata);
void Erase(int event, int x, int y, int flags, void *userdata);
int handleError( int status, const char* func_name,const char* err_msg, const char* file_name,int line, void* userdata )
{
    //Do nothing -- will suppress console output
    return 0;   //Return value is not used
}

double bot_forward_resolution=5.45;
double bot_rotation_resolution = 4.090*5.44/5.38;

//common variables
vector<Points> drawThis;
vector<Points> path[1000];     int i=0;
bool isPath[1000]={0};
Mat tracing_of_path;                            //to know if the path exists or not
Mat final_points;
int drawing_board_l, drawing_board_b;

//variables needed when user wants to draw the image
Mat image(500,500,CV_8U, Scalar(255));
bool isLeftButtonDown=0;
int previous_mouse_x, previous_mouse_y;

Mat image_only_borders;
bool isRightButtonDown=0;

int main()
{

redirectError(handleError);

try{
    int what;
    cin>>what;

    if(what==0)                                          //code when user wants to draw the image
    {
        for(int i=0;i<image.cols;++i)
        {
            for(int j=0;j<image.rows;++j)
            {
                image.at<uchar>(j,i)=255;
            }
        }

        //drawing_board_l=first_coordinate(what);
        //drawing_board_b=second_coordinate(what);

        tracing_of_path=image.clone();
        final_points=image.clone();

        namedWindow("my window",CV_WINDOW_AUTOSIZE);
        setMouseCallback("my window",CallBackFunc,(NULL));
        waitKey(0);

    }

    else if (what==1)                                    //code when user wants to upload an image
    {
        Mat orig_image, resized_image;        // new blank images

        string image_file_path;
        //image_file_path=address(what);
        cin>>image_file_path;
        image_file_path=analyser(image_file_path);

        //drawing_board_l=first_coordinate(what);
        //drawing_board_b=second_coordinate(what);

        orig_image = cv::imread(image_file_path);   //read the file
        resize_image(400,600, orig_image, resized_image);

        namedWindow( "Display window", CV_WINDOW_AUTOSIZE );
        imshow( "Display window", resized_image );
        //waitKey(0);

        Mat image_in_grayscale;
        cvtColor(resized_image, image_in_grayscale,CV_BGR2GRAY);
        namedWindow("GrayScale Image",CV_WINDOW_AUTOSIZE);
        imshow("GrayScale Image",image_in_grayscale);
        destroyWindow("GrayScale Image");
        //waitKey(0);

        //Mat image_only_borders;
        image_only_borders=image_in_grayscale.clone();

        namedWindow("B&W",CV_WINDOW_AUTOSIZE);
        BlackNWhite(image_in_grayscale,150);
        imshow("B&W",image_in_grayscale);
        destroyWindow("B&W");

        //waitKey(0) ;

        detect_borders(image_in_grayscale, image_only_borders);
        namedWindow("Only Borders",CV_WINDOW_AUTOSIZE);
        imshow("Only Borders",image_only_borders);
        destroyWindow("Only Borders");

        reduce_noise(image_only_borders);
        namedWindow("No Noise",CV_WINDOW_AUTOSIZE);
        imshow("No Noise",image_only_borders);

        setMouseCallback("No Noise", Erase, (NULL));

        waitKey(0);

        while(startingPoint(image_only_borders).x!=-1 && i<1000)    //again i<1000 as max number of paths is 1000
        {
            make_a_path(image_only_borders, path[i]);
            isPath[i]=1;
            clear_traversed_path(image_only_borders,path[i]);
            i++;
        }

        imshow("No Noise",image_only_borders);
        waitKey(0);

        tracing_of_path=image_only_borders.clone();
        final_points=image_only_borders.clone();

    }

    //now merge paths....
    for(int j=0;j<i;j++)
        for(int k=j+1;k<i;k++)
            if(isPath[j] && isPath[k])   merge_paths(path[j], path[k], isPath[j], isPath[k]);

    //display how our bot will actually trace the path
    namedWindow("How bot will draw", CV_WINDOW_AUTOSIZE);
    for(int j=0;j<i;j++)
    {
        if(isPath[j])
        {
            for (vector<Points>::iterator it = path[j].begin() ; it != path[j].end(); ++it)
            {   //cout <<it->x<<" "<<it->y<<endl;
                tracing_of_path.at<uchar>(it->y, it->x) = 0;
                imshow("How bot will draw", tracing_of_path);
                waitKey(1);
            }
        }
    }

    //now only take the points which can be drawn
    //vector<Points> drawThis;
    float current_angle=90.0;
    int pathToDraw=0; int pathIndex=0;       //timepass is index of path



    while(pathIndex<i)
    {
        if(isPath[pathIndex])
        {
            pathToDraw=pathIndex;
        }
        else
        {
            pathIndex++;
            continue;
        }

        //get drawing board resolution and set drawing_resolution and rotation_resolution accordingly

        vector<Points>::iterator it=path[pathToDraw].begin();

        while(it<path[pathToDraw].end()-1)
        {
            drawThis.push_back(*path[pathToDraw].begin());
            //now call function which calculates the point
            Points current_point=*it;
            float distance;
            int angleToRotate;

            while(it<path[pathToDraw].end()-1)
            {

                distance=calc_distance(current_point, *(it+1));
                angleToRotate=calc_rotate_angle(current_point, *(it+1), current_angle);
                if(distance>3*bot_forward_resolution && (angleToRotate>2*bot_rotation_resolution || angleToRotate<-2*bot_rotation_resolution || (angleToRotate==0)))
                    break;

              /*if(abs(calc_rotate_angle(*(it),*(it+5),0) - calc_rotate_angle(*(it-5),*(it),0))>=40
               && abs(calc_rotate_angle(*(it),*(it+1),0) - calc_rotate_angle(*(it),*(it+5),0))<=0.5
               && abs(calc_rotate_angle(*(it-1),*(it),0) - calc_rotate_angle(*(it-5),*(it),0))<=0.5
                )
                {
                    update_current_angle(*it, *(it+1), current_angle);
                    it--;
                    break;

                }*/
                it++;
            }
            it++;

            //before push_back check whether points lie on a line if yes, delete previous point
            if(calc_rotate_angle(current_point, *(it),current_angle)==0)
            {
                drawThis.pop_back();
            }

            drawThis.push_back(*it);

            //update current angle
            update_current_angle(current_point, *it, current_angle);
        }

        drawThis.push_back(*(path[pathIndex].end()-1));
        pathIndex++;
        Points null=Points(0,0);
        drawThis.push_back(null);
    }

    //display the final_points
        for(int i=0;i<final_points.cols;i++)
            for(int j=0;j<final_points.rows;j++)
            {
                final_points.at<uchar>(j,i)=255;
            }

    namedWindow("Final Points",CV_WINDOW_AUTOSIZE);
    imshow("Final Points",final_points);


    //cout final points to be drawn
    for (vector<Points>::iterator it = drawThis.begin() ; it < drawThis.end(); ++it)
        {
            //cout <<it->x<<" "<<it->y<<endl;
            final_points.at<uchar>(it->y,it->x)=0;
            imshow("Final Points",final_points);
            waitKey(5);
        }
    //cout<<"Points Shown Successfully";

    waitKey(0);
    destroyAllWindows();

    namedWindow("Final Points",CV_WINDOW_AUTOSIZE);
    imshow("Final Points",final_points);


{
    //XBee communication: 0:command; 1:x2; 2:y2  commands: 0 is start, 1 is move, 2 is pen-up, 3 is pen-down
    char data=0;
    char dx, dy;
    bool isPenDown=1;
    char isNegative;

    //first tp data....
    {//instruction to start
        sendAndRecieve(data);
    }

    {//now penup
        data=1;
        sendAndRecieve(data);
    }
    {//now move to 1st point
        dx=drawThis.begin()->x;
        sendAndRecieve(dx);

        if(dx<0) isNegative=1;
        else isNegative=0;
        sendAndRecieve(isNegative);

        dy=tracing_of_path.rows - drawThis.begin()->y;
        sendAndRecieve(dy);

        if(dy<0) isNegative=1;
        else isNegative=0;
        sendAndRecieve(isNegative);
        readByte();
    }

    {//now pendown
        data=2;
        sendAndRecieve(data);
        isPenDown=1;
    }
    {//now 2nd point
        dx=drawThis.begin()->x;
        dx=((drawThis.begin()+1)->x) - dx;
        sendAndRecieve(dx);

        if(dx<0) isNegative=1;
        else isNegative=0;
        sendAndRecieve(isNegative);

        dy=drawThis.begin()->y;
        dy=-(((drawThis.begin()+1)->y) - dy);
        sendAndRecieve(dy);

        if(dy<0) isNegative=1;
        else isNegative=0;
        sendAndRecieve(isNegative);
        readByte();
    }

    //First the command bit:  move as it is is 0, penup is 1, pendown is 2
    //Second x1: it.x-(it-1).x
    //Third y1: it.y-(it-1).y

    for(vector<Points>::iterator it=drawThis.begin()+2; it!= drawThis.end(); ++it)
    {
        //first the command
        if((it)->x==0 && (it)->y==0 && isPenDown==1)
        {
            data=1;
            //cout<<"Data";
            sendAndRecieve(data);
            ++it;
            isPenDown=0;
        }

        else if((it-2)->x==0 && (it-2)->y==0 && isPenDown==0)
        {
            data=2;
            //cout<<"Data";
            sendAndRecieve(data);
            isPenDown=1;
        }

        else
        {
            data=0;
            //cout<<"Data";
            sendAndRecieve(data);
        }



        //now the x-coordinate
        if(isPenDown)
        {
            //cout<<"DX";
            dx=(it->x) - ((it-1)->x);
            sendAndRecieve(dx);

            if(dx<0) isNegative=1;
            else isNegative=0;
            sendAndRecieve(isNegative);
            //cout<<it->x<<endl;
        }

        else
        {
            //cout<<"DX";
            dx=(it->x) - ((it-2)->x);
            sendAndRecieve(dx);

            if(dx<0) isNegative=1;
            else isNegative=0;
            sendAndRecieve(isNegative);
            //cout<<it->x<<endl;
        }

        //now the y-coordinate
        if(isPenDown)
        {
            //cout<<"DY";
            dy=-((it->y) - ((it-1)->y));
            sendAndRecieve(dy);

            if(dy<0) isNegative=1;
            else isNegative=0;
            sendAndRecieve(isNegative);
            //readByte();
            //cout<<it->y<<endl;
        }

        else
        {
            //cout<<"DY";
            dy=-((it->y) - ((it-2)->y));
            sendAndRecieve(dy);

            if(dy<0) isNegative=1;
            else isNegative=0;
            sendAndRecieve(isNegative);
            //readByte();
            //cout<<it->y<<endl;
        }

    }

}

}

catch(...)
{
    cout<<"The given image cannot be processed or drawn by the bot.";
    exit(1);
}

    cout<<"Drawing successfully made ( hopefully ;) )";

    return 0;
}


void CallBackFunc(int event ,int x,int y,int flags,void* userdata)
{
    if(event==EVENT_LBUTTONDOWN)
    {
        if(previous_mouse_x<image.cols-1 && previous_mouse_x>1 && previous_mouse_y<image.rows-1 && previous_mouse_y>1
                && x<image.cols-1 && x>1 && y<image.rows-1 && y>1)
        {
            image.at<uchar>(y,x)=0;
            Points pt(x,y);
            //cout<<endl<<x<<"\t"<<y;
            path[i].push_back(pt);
        }
            imshow("my window",image);
            isLeftButtonDown=1;
            previous_mouse_x=x;
            previous_mouse_y=y;
    }

    if(event==EVENT_MOUSEMOVE && isLeftButtonDown==1)
    {
        if(previous_mouse_x<image.cols-1 && previous_mouse_x>1 && previous_mouse_y<image.rows-1 && previous_mouse_y>1
                && x<image.cols-1 && x>1 && y<image.rows-1 && y>1)
                {
                    image.at<uchar>(y,x)=0;
                    Points pt(x,y);
                    //cout<<endl<<x<<"\t"<<y;
                    draw_the_line(previous_mouse_x, previous_mouse_y, x, y, image, path[i]);
                    path[i].push_back(pt);
                }

        imshow("my window",image);

        previous_mouse_x=x; previous_mouse_y=y;
    }

    if(event==EVENT_LBUTTONUP)
    {
        isLeftButtonDown=0;
        isPath[i]=1;
        i++;
    }
}

void Erase(int event ,int x,int y,int flags,void* userdata)
{
    if(event==EVENT_RBUTTONDOWN)
    {
        if(previous_mouse_x<image_only_borders.cols-1 && previous_mouse_x>1 && previous_mouse_y<image_only_borders.rows-1 && previous_mouse_y>1
                && x<image_only_borders.cols-1 && x>1 && y<image_only_borders.rows-1 && y>1)
        {
            image_only_borders.at<uchar>(y,x)=255;
        }
            imshow("No Noise",image_only_borders);
            isRightButtonDown=1;
            previous_mouse_x=x;
            previous_mouse_y=y;
    }

    if(event==EVENT_MOUSEMOVE && isRightButtonDown==1)
    {
        if(previous_mouse_x<image_only_borders.cols-1 && previous_mouse_x>1 && previous_mouse_y<image_only_borders.rows-1 && previous_mouse_y>1
                && x<image_only_borders.cols-1 && x>1 && y<image_only_borders.rows-1 && y>1)
                {
                    image_only_borders.at<uchar>(y,x)=255;
                    draw_the_line_white(previous_mouse_x, previous_mouse_y, x, y, image_only_borders);
                }

        imshow("No Noise",image_only_borders);

        previous_mouse_x=x; previous_mouse_y=y;
    }

    if(event==EVENT_RBUTTONUP)
    {
        isRightButtonDown=0;
    }
}


