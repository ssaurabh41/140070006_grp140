#include <iostream>
#include <vector>

#include "global_variables.h"
#include "Points.h"

//checks if the path1 and path2 have any connection and if it exists, appends a path to another in the beginning or at the end in same order or reverse order as required
//changes the isPath value for the path which is added. So only the path to which addition is done stays.
//if no connection, nothing happens.
void merge_paths(std::vector<Points> &path1, std::vector<Points> &path2, bool &isPath1, bool &isPath2)
{
    int canBeClubbed=0;
    for(int x=((path1.end()-1)->x)-1; x<=((path1.end()-1)->x)+1;x++)
    {
        for(int y=((path1.end()-1)->y)-1; y<=((path1.end()-1)->y)+1;y++)
        {
            if(((path2.end()-1)->x)==x && ((path2.end()-1)->y)==y)
            {
                canBeClubbed=1; break;
            }
            if((path2.begin()->x)==x && (path2.begin()->y)==y)
            {
                canBeClubbed=2; break;
            }
        }
        if(canBeClubbed) break;
    }
    if(canBeClubbed==1)   //code to merge the two paths.. add to path1 path2 in reverse order
    {
        std::vector<Points>::reverse_iterator rit = path2.rbegin();
         for (; rit!= path2.rend(); ++rit)
        {
            path1.push_back(*rit);
        }
        isPath2=false;
        return;
    }
    else if(canBeClubbed==2)   //add to path1 path2 from beginning... this is the more likely case
    {
        std::vector<Points>::iterator it=path2.begin();

        for(;it!=path2.end();++it)
        {
                path1.push_back(*it);
        }
        isPath2=false;
        return;
    }

    //similar to check for beginning of path1 and both ends of path2.
    for(int x=(path1.begin()->x)-1; x<=(path1.begin()->x)+1;x++)
    {
        for(int y=(path1.begin()->y)-1; y<=(path1.begin()->y)+1;y++)
        {
            if(((path2.end()-1)->x)==x && ((path2.end()-1)->y)==y)
            {
                canBeClubbed=1; break;
            }
            if((path2.begin()->x)==x && (path2.begin()->y)==y)
            {
                canBeClubbed=2; break;
            }
        }
        if(canBeClubbed) break;
    }

    if(canBeClubbed==1)   //add to path2 path1 from beginning... this is the more likely case
    {
        std::vector<Points>::iterator it=path1.begin();

        for(;it!=path1.end();++it)
        {
                path2.push_back(*it);
        }
        isPath1=false;
        return;
    }

     if(canBeClubbed==2)   //add to path2 path1 from beginning... this is the more likely case
    {   std::vector<Points> temp;
        std::vector<Points>::reverse_iterator rit = path1.rbegin();
         for (; rit!= path1.rend(); ++rit)
        {
            temp.push_back(*rit);
        }
        std::vector<Points>::iterator it=path2.begin();
        for(;it!=path2.end();++it){

                temp.push_back(*it);
        }

        path2=temp;

        isPath1=false;
        return;
    }
}

