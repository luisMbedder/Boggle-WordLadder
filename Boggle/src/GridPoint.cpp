#include "GridPoint.h"
#include <string>
#include "strlib.h"

GridPoint::GridPoint(void)
{
	x=0;
	y=0;
}

GridPoint::GridPoint(int xc,int yc){
	x=xc;
	y=yc;
}

int GridPoint::getX(){
	return x;
}

int GridPoint::getY(){
	return y;
}

std::string GridPoint::toString(){
	return "(" + integerToString(x) + "," + integerToString(y) + ")"; 
}

bool operator==(GridPoint p1,GridPoint p2){
	return p1.x == p2.x && p1.y == p2.y;
}

bool operator!=(GridPoint p1, GridPoint p2){
	return !(p1==p2);
}

bool operator<(GridPoint p1, GridPoint p2){//overload < operator to use set class
	return ((p1.getX()<p2.getX())&&(p1.getY()<p2.getY()));
		
}
bool operator>(GridPoint p1, GridPoint p2){//overlaod > operator to use set class
	return ((p1.getX()>p2.getX())&&(p1.getY()>p2.getY()));
}

std::ostream & operator<<(std::ostream & os, GridPoint pt){
	return os << pt.toString();
		
}

GridPoint::~GridPoint(void)
{
}
