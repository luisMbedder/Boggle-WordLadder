/********************************************************************
* File: GridPoint.h
*
* Created by : LuisMbedder
*
* Description : this interface exports the GridPoint class which
*				represents a point on a 2-D integer grid. 
********************************************************************/
#ifndef _GridPoint_h
#define _GridPoint_h

#include <iostream>
#include <string>

class GridPoint
{
public:

	/*
	 * Constructor: GridPoint
	 * Usage: GridPoint origin;
	 *		  GridPoint pt(x,y);
	 * ---------------------------
	 * creates a GridPoint Object. The default constructor sets the
	 * coordinates to 0,0; the second sets the coordiantes to x,y
	*/
		GridPoint(void);
		GridPoint(int xc,int yc);

	/*
	 * Methods: getX,getY
	 * Usage: int x = pt.getX();
	 *		  int x = pt.getY();
	 * ---------------------------
	 * returns the x and y coordinates of the grid point. 
	*/
		int getX();
		int getY();

	/*
	 * Method: toString
	 * Usage: string str=pt.toString();
	 * ---------------------------
	 * returns a string representation of the GridPoint in the form "(x,y)"
	*/
		std::string toString();

	//friend declaration
	friend bool operator==(GridPoint p1,GridPoint p2);

	//instance variables
	int x;
	int y;


	~GridPoint(void);
};

	/*
	 * Operator: <<
	 * Usage: cout<<pt
	 * ---------------------------
	 * overloads the << operator to display GridPoint values
	*/
		std::ostream & operator<<(std::ostream & os,GridPoint pt);

	/*
	 * Operator: ==
	 * Usage: p1==p2
	 * ---------------------------
	 * to support equality testing for GridPoints
	*/
		bool operator==(GridPoint p1, GridPoint p2);

	/*
	 * Operator: !=
	 * Usage: p1!=p2
	 * ---------------------------
	 * adds support for the != operator
	*/
		bool operator!=(GridPoint p1,GridPoint p2);

	/*
	 * Operator: <
	 * Usage: p1<p2
	 * ---------------------------
	 * to support comparison testing. 
	*/
		bool operator<(GridPoint p1, GridPoint p2);

#endif
