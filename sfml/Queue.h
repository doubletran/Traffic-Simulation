#pragma once
#include "Route.h"
class RouteQueue
{
public:

	//Name:   Queue constructor
	//Desc:   This function initialize Gueue to null
	//input:  None
	//output: empty Queue
	//return: None
	RouteQueue();

	//Name:   Queue destructor
	//Desc:   This function deallocates memory for the Queue object
	//input:  None
	//output: empty Queue
	//return: None
	~RouteQueue();


	//Name:   Queue  copy constructor
	//Desc:   This function initialize Gueue with another queue object
	//input:  Queue object
	//output: new Queue object coped from another object
	//return: None
	RouteQueue(const RouteQueue& aQueue);


	//Name:   enqueue
	//Desc:   This function add incoming guest to the end of the queue
	//input:  Guest object
	//output: The queue with the newly added guest
	//return: None
	void enqueue(const Route& route);

	//Name:	  dequeue
	//Desc:   This function remove the first guest in the line
	//input:  Guest object
	//output: the guest object of the first guest in the line 
	//			removed from the queue
	//return: boolean if the front queue has any guest to be removed
	bool dequeue(Route& path);


	//Name:	  peek
	//Desc:   This function peek at the first guest in the line
	//input:  Guest object
	//output: the guest object of the first guest in the line 
	//return: boolean if the front queue has any guest
	bool peekCurr(Route& path) const;
	LanePos getCorrectLane() const;
	LanePos getCurrLanePos() const;
	int getCurrLane() const;
	bool peekNext(Route& path) const;
	void setLaneIdx(int lane_idx);

	//Name:   Operator = function
	//Desc:   This function deep copies the queue ADT
	//input:  source Queue object
	//output: None
	//return: Queue object copied from another object
	const RouteQueue& operator= (const RouteQueue& aQueue);


private:
	struct Node {
		Route* data;                                                                                                                 
		Node* next, * prev;
		Node(const Route& route){
			data = new Route(route);
			next = nullptr;
		}
		~Node() {
			if (data) {
				delete data;
			}
			data = nullptr;
			next = nullptr;
		}
	};
	Node* rear, * front;
	int size;

	//Name:	  destroy
	//Desc:   This function recursively destroy every nodes
	//input:  Node pointer to current guest to be deallocated
	//output: the empty queue
	//return: None
	void destroy(Node*);
};


