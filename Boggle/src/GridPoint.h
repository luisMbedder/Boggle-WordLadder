
#ifndef _point_h
#define _point_h

#include <iostream>
#include <string>

class GridPoint
{
public:
	GridPoint(void);
	GridPoint(int xc,int yc);

	int getX();
	int getY();

	std::string toString();

	friend bool operator==(GridPoint p1,GridPoint p2);

	int x;
	int y;


	~GridPoint(void);
};

std::ostream & operator<<(std::ostream & os,GridPoint pt);

bool operator==(GridPoint p1, GridPoint p2);

bool operator!=(GridPoint p1,GridPoint p2);

//bool operator>(GridPoint p1, GridPoint p2);
bool operator<(GridPoint p1, GridPoint p2);

#endif
