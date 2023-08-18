#pragma once
#include "Lib.h"
#include "StreetBuilding/Street.h"
#include "Graph.h"
#include "Auto.h"


class Traffic: public sf::Drawable, sf::Transformable, protected Graph <Route, Point>
{
	vector<Street> streetArray;




	
	int getVertex(const Point& pt);
	int getNearVertex(const sf::Vector2f& pos);
	

public:

	void addIntersection(int vhead, int vtail, const Point&, Route&);
	
	void place(Auto& vehicle);
	bool guide(Auto& vehicle, const sf::Vector2f& dest);
	
	void addStreet(const Street& newStreet);


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (auto &street : streetArray) {
			target.draw(street);
		}
	}

};

/*
class Intersection {
	Point pt;
	int size;
	vector <vector<Route>>pairs;
	Intersection(const Point& pt, vector<Route>& routes) {
		this->pt = pt;
		size = 0;
		for (auto& route : routes) {
			pairs.push_back(vector<Route>());
			route.divide(pt, pairs[size++]);
		}

	}
	void getDivisions()
};

*/