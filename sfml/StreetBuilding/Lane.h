#pragma once
#include "Segment.h"
/*
* Lane object inherit head, tail from Segment object  
* containing multiple segment in the same lane
*/

struct Lane : Segment{
	vector<Segment> segArray;

	/*Constructor*/
	Lane();
	Lane(const Point& start, const Point& end);
	Lane(const Lane&);
	const Lane& operator= (const Lane& lane);

	void add(const Point&);
	void update();


	void setSprite(LanePos);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		for (auto seg : segArray) {
			seg.setSprite();
			//seg.setOrigin(seg.origin);
			seg.setPosition(seg.head.pos);
			seg.setRotation(seg.angle);
		
			target.draw(seg, states);
		}

	}


};
struct LaneSpawner : Lane {
	
	LaneSpawner(const Lane& base, int idx) : Lane() {
		//SegmentSpawner::laneOffset = (float)idx;
		for (auto seg : base.segArray) {
			SegmentSpawner spawner(seg);
			segArray.push_back(spawner.get((float)idx));
		}
	}
	const Lane get() const;
};