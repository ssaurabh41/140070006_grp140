#include<iostream>
using namespace std;

//returns first element of input string by java interface
int check(string input){
    if(input[0]=='0'){
        return 0;
    }
    else if(input[0]=='1'){
        return 1;
    }
}

//Calculates (index of last char of x-coordinate)+1
int length_x(string line){
    int x=0,i=0;
    while(i!=2){
        while(line[x]!=',')
        {
            x++;
        }
        i++;
        x++;
        }
        return x-1;
    }

//Calculates (index of last char of y-coordinate)+1
int length_y(string line){
    int y=0,i=0;
    while(i!=2){
        while(line[y]!=',')
        {
            y++;
        }
        i++;
        y++;
    }
    while(line[y]!=',' && line[y]!='\0')
    {
        y++;
    }
    return y;
    }

//Calculates (index of last char of address)+1
int length(string line){
    int y=0,i=0;
    while(i!=3){
    while(line[y]!=',')
    {
        y++;
    }
    i++;
    y++;
    }
    while(line[y]!='\0')
    {
        y++;
    }
    return y;
    }
//Gives x-coordinate
int first_coordinate(string line)
    {
        int lx=length_x(line),k=1,x=0;
        for(int r=lx;r>=3;r--)
        {
            x=x+k*(line[r-1]-48);
            k=k*10;
        }
    return x;
    }

//Gives y-coordinate
int second_coordinate(string line)
    {
        int lx=length_x(line),ly=length_y(line),k=1,y=0;
        for(int r=ly;r>=lx+2;r--)
        {
            y=y+k*(line[r-1]-48);
            k=k*10;
        }
    return y;
    }

//Gives address
string address(string line)
    {
    string a="";
    for(int r=length_y(line)+2;r<=length(line);r++)
    {
        a.push_back(line[r-1]);
    }
    return a;
    }


