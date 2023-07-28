#include "Auto.h"
Auto::Auto() : routeTracker() {};
Auto::Auto(sf::Vector2f pos) : routeTracker(){
	sprite.setSize(sf::Vector2f(30.f, 30.f));
	this->pos = pos;
	this->vel = sf::Vector2f(maxspeed, maxspeed);
	sprite.setPosition(pos);
	sprite.setFillColor(sf::Color::Black);
	
}
Auto::Auto(const Auto& vehicle) {
	pos = vehicle.pos;
	vel = vehicle.vel;
	acc = vehicle.acc;
	routeTracker = vehicle.routeTracker;
}
void Auto::update() {
	vel += acc;
	limit(vel, maxspeed);
	pos += vel;
	acc = sf::Vector2f(0, 0);
	sprite.setPosition(pos);
	sprite.setRotation(atan(vel.y / vel.x));
}
void Auto::applyForce(sf::Vector2f force) {
	acc += force;
}
void Auto::seek(sf::Vector2f target) {
	sf::Vector2f desired = target - pos;
	limit(desired);
	desired *= maxspeed;
	sf::Vector2f steer = desired - vel;
	limit(steer, maxforce);
	applyForce(steer);

}

void Auto::follow(const Segment &path) {
	
	sf::Vector2f predict = vel;
	limit(predict);
	predict *= 25.f;
	sf::Vector2f predictPos = pos+ predict;

	sf::Vector2f normalPoint = getNormalPoint(predictPos, path.head.pos, path.tail.pos);
	//check if we are off the path;
	float distance = dist(normalPoint, predictPos);
	if (distance > LANE/3) {
		//create a target in the path and ahead of a normal point
		sf::Vector2f dir = path.tail.pos -path.head.pos;
		limit(dir);
		dir *= 10.f;
		seek(normalPoint + dir);
	}

}
void Auto::addRoute(const Route& route) {
	routeTracker.enqueue(route);
}

void Auto::start() {
	Route curr;
	curr.setLane(pos);
	while (routeTracker.peekCurr(curr)) {
		follow(curr.getSegment());
		int diff = routeTracker.getCurrLanePos() > routeTracker.getCorrectLane();
		if (diff> 0) {
			curr.setLane(curr.lane_idx - 1);
		}
		else if (diff < 0) {
			curr.setLane(curr.lane_idx + 1);
		}
		if (curr.endRoute(pos)) {
			routeTracker.dequeue(curr);
		}

	}
}

void Auto::follow(const vector <Segment>& path) {
	static int idx = 0;
	follow(path[idx]);
	if (pos.x > path[idx].tail.pos.x - 10) {
		if (idx + 1 < path.size()) {
			idx++;
		}
	}
	
}
void Auto::follow(const vector<Point>& path) {
	sf::Vector2f predict = vel;
	limit(predict);
	predict *= 25.f;
	sf::Vector2f predictPos = pos + predict;
	float max_dist = 10000;
	for (size_t i = 0; i < path.size()-1; i++) {
		sf::Vector2f a = path[i].pos;
		sf::Vector2f b = path[i + 1].pos;
		sf::Vector2f normalPoint = getNormalPoint(predictPos, a, b);
		float distance = dist(normalPoint, predictPos);
		if (distance < max_dist) {
			max_dist = distance;	
		}
		if (max_dist > LANE) {
			//create a target in the path and ahead of a normal point
			sf::Vector2f dir = b - a;
			limit(dir);
			dir *= 10.f;
			seek(normalPoint + dir);
		}

	}

}