#pragma once
#include "Lib.h"
#include "StreetBuilding/Street.h"
#include "Graph.h"
#include "Auto.h"


class Traffic: public sf::Drawable, sf::Transformable
{
	int size;
	vector<vector<Route*>> routeMatrix;
	RouteGraph graph;
	vector<Point>base;
	
	int getVertex(const Point& pt);
	

public:
	void addRoute(int, int, const Route&);
	void deleteRoute(int, int);
	void addIntersection(int vhead, int vtail, const Point&, Route&);
	
	void place(Auto& vehicle);
	bool guide(Auto& vehicle, const sf::Vector2f& dest);
	int getNearVertex(const sf::Vector2f& pos);
	vector<Street>streetArray;
	void addStreet(const Street& newStreet);
	int addPoint(const Point& pt);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (auto street : streetArray) {
			target.draw(street);
		}
	}

};

