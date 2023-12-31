#pragma once
#include "StreetBuilding/Street.h"
class Route
{
	Street* street;
	Segment segment;
	int weight;
	int seg_idx;
	Route(const Street& str, int seg_idx, const Segment& seg);

public:
	LanePos lane_pos;
	int lane_idx;
	Route();
	Route(const Street& str, int seg_idx);
	Route(const Route& route);

	
	~Route() {
		if (street) {
			delete street;
		}
		street = nullptr;
	}
	void init();
	
	void setLane(const int lane);
	void setLane(const sf::Vector2f pos);
	bool divide(vector<Point> pts, vector<Route>&pieces);
	bool divide(const Point& cutoff, vector<Route>& pieces);
	int getCurrLane() { return lane_idx; }

	Segment getSegment() const;
	Segment getSegment(const int lane_idx) const;
	Point getTail(const int lane_idx) const;
	Point getHead(const int lane_idx) const;
	LanePos getNearestLane(const Route& next) const;
	LanePos getNearestLane(const sf::Vector2f pos) const;
	
	bool endRoute(const sf::Vector2f pos);
	
	int getWeight();
	operator int() const {
		return weight;
	}
	
};
