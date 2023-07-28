#include "Queue.h"
RouteQueue::RouteQueue() {
	size = 0;
	rear = front = nullptr;
}



RouteQueue::~RouteQueue() {
	destroy(front);
	size = 0;
}



void RouteQueue::destroy(Node* curr) {
	if (curr != rear) {
		destroy(curr->next);
		delete curr;
	}
	else {
		delete rear;
	}
}



RouteQueue::RouteQueue(const RouteQueue& aQueue) {
	//rear = front = nullptr;
	*this = aQueue;
}



const RouteQueue& RouteQueue::operator= (const RouteQueue& queue) {
	if (this == &queue) {
		return *this;
	}
	destroy(rear);
	size = queue.size;
	if (!queue.rear) {
		rear = front = nullptr;
		return *this;
	}
	Node* newNode = new Node(*(queue.front->data));
	rear = front = newNode;
	Node* dest = front;
	RouteQueue::Node* curr = queue.front;
	for (int i = 0; i < queue.size; i++) {
		newNode = new Node(*(curr->data));
		dest->next = newNode;
		curr = curr->next;
		dest = dest->next;
	}
	rear = dest;
	return *this;
}



void RouteQueue::enqueue(const Route& route) {
	Node* newNode = new Node(route);
	if (!rear) {
		rear = front = newNode;
		rear->next = front;
		front->next = rear;
	}
	else {
		rear->next = newNode;
		newNode->next = front;
		rear = newNode;
	}
	size++;
}



bool RouteQueue::dequeue(Route& route) {
	if (size == 0) {
		return false;
	}
	route= *(rear->next->data);
	front = front->next;
	delete rear->next;
	size--;
	if (size != 0) {

		rear->next = front;
	}
	else {
		rear = front = nullptr;
	}
	return true;

}

LanePos RouteQueue::getCorrectLane() const {
	Route *curr = front->data;
	Route *next = front->next->data;
	return (*curr).getNearestLane(*next);

}
LanePos RouteQueue::getCurrLanePos() const {
	return front->data->lane_pos;
}
int RouteQueue::getCurrLane()  const{
	return front->data->getCurrLane();

}
void RouteQueue::setLaneIdx(int lane_idx) {
	rear->next->data->lane_idx = lane_idx;

}

bool RouteQueue::peekCurr(Route& path) const {
	if (size == 0) {
		return false;
	}
	path = *(rear->next->data);
	return true;

}

bool RouteQueue::peekNext(Route& path) const {
	if (size < 1 ) {
		return false;
	}
	path = *(rear->next->next->data);
	return true;
}

