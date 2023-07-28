
#pragma once
#include "Lib.h"
#include "Queue.h"

class Auto:public sf::Drawable , public sf::Transformable
{
	RouteQueue routeTracker;
	sf::RectangleShape sprite;
	
	sf::Vector2f acc;
	sf::Vector2f vel;
	float maxspeed = 0.1f;
	float maxforce = 0.01f;
public:
	sf::Vector2f pos;
	Auto();

	Auto(sf::Vector2f pos);
	Auto(const Auto&);

	void setVelocity(sf::Vector2f vel);
	void getVelocity();
	void follow(const Street::Segment& path);
	void seek(sf::Vector2f target);
	void seekNearestLane();

	void follow(const vector<Point>& path);
	void follow(const Street& str, int seg_idx);
	void addRoute(const Route& route);
	void start();
	void follow(const vector<Segment>& path);
	void update();
	void applyForce(sf::Vector2f force);

	

	
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(sprite);
	}
};

