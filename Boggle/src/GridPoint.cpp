/********************************************************************
* File: GridPoint.cpp
*
* Created by : LuisMbedder
*
* Description : this file implements the GridPoint.h interface.
********************************************************************/

#include "GridPoint.h"
#include <string>
#include "strlib.h"


//Constructor, creates a GridPoint object with origin coordinates
GridPoint::GridPoint(void)
{
    x=0;
    y=0;
}

//Constructor creates a GridPoint object with the specified x,y coordinates
GridPoint::GridPoint(int xc,int yc){
    x=xc;
    y=yc;
}

//Getter, returns the x-coordiante of the GridPoint
int GridPoint::getX(){
    return x;
}

//Getter, returns the y-coordiante of the GridPoint
int GridPoint::getY(){
    return y;
}

//returns a string representation of the GridPoint in the form "(x,y)"
std::string GridPoint::toString(){
    return "(" + integerToString(x) + "," + integerToString(y) + ")";
}

//overloads the insertion operator
std::ostream & operator<<(std::ostream & os, GridPoint pt){
    return os << pt.toString();

}

//free function, overloads the == operator
bool operator==(GridPoint p1,GridPoint p2){
    return p1.x == p2.x && p1.y == p2.y;
}

//free function, overloads the != operator
bool operator!=(GridPoint p1, GridPoint p2){
    return !(p1==p2);
}

//free function, overloads the < operator
bool operator<(GridPoint p1,GridPoint p2){//overload < operator to use set class
if(p1.getX() != p2.getX())
return p1.getX() < p2.getX();
return p1.getY() < p2.getY();
    //return ((p2.getX()<p1.getX())&&(p2.getY()<p1.getY()));

}

GridPoint::~GridPoint(void)
{
}
