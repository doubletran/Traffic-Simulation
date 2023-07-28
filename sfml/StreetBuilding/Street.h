#pragma once

#include "Lane.h"

class Street : public Lane
{
public:
	vector<Lane>laneArray;
	char* name = 0;
	int lane;
	int dir;

	Street();
	Street(const Point&, const Point&, const char* name);
	Street(const Street& street);
	const Street& operator= (const Street& street);

	void setName(const char*);
	void add(const Point&);
	void add(const Point&, int laneIdx);
	void addLane();
	
	int getLaneIdx(LanePos);
	LanePos getLanePos(int laneIdx);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		int lane_idx = 0;
		for (auto lane : laneArray) {
			target.draw(lane);
		}
		for (auto lane : laneArray) {
			if (lane_idx == 0) {
				lane.setSprite(LEFT);
			}
			else if (lane_idx == laneArray.size() - 1) {
				//lane.segArray[0].angle = 0;
				lane.setSprite(RIGHT);
			}
			else {
				lane.setSprite(MIDDLE);
			}
			lane_idx++;
			for (auto seg : lane.segArray) {
				//seg.setSprite();
				seg.marking.setPosition(seg.head.pos);
				seg.marking.setRotation(seg.angle);
				target.draw(seg.marking);

			}

		}
	}
};

	/*
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		
		for (auto seg : segArray) {
			seg.setSprite(multiLane.size());
			seg.setOrigin((*head).pos);
			seg.setPosition((*head).pos);
			seg.setRotation(seg.angle);
			target.draw(seg, states);
		}
	}
	*/
/*
class Oneway: public Street {
public:
	int lane;
	Oneway(const Point& start, const Point& end, int lane, const char * name);
	void add(const Point& pt);



};

class Twoway : public Street {

	Twoway(const Point& pt1, const Point& pt2, int lane1, int lane2, const char * name);

};

*/

