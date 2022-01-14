#include <iostream>
#include <string>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
#include <cmath>

using namespace std;

LinkedList::LinkedList() {
	// Implement this function
    this->head = nullptr;
    this->tail = nullptr;
}

LinkedList::~LinkedList() {
	// Implement this function
    this->clear();
}

LinkedList::LinkedList(const LinkedList& source) {
    // Implement this function
    // Create new list
    // Create Walk pointer to walk through original list
    this->head = nullptr;
    this->tail = nullptr;
    if (source.head == nullptr) {
        // this->head = nullptr;
        // this->tail = nullptr;
        return;
    }
    Node *walk = source.head;
    // Create copied node
    Node *copied = nullptr;
    Node *prev = nullptr;
    while (walk != nullptr) {
        // If copied not null, use prev to track copied
        if (copied != nullptr) {
            prev = copied;
        }
        // create copied node
        copied = new Node;
        //copied node to new walk 
        copied->data = walk->data;
        copied->next = nullptr;
        // If not first Walk, assign prev next to new copied
        if (prev != nullptr) {
            prev->next = copied;
        }
        // cout << "This head" << endl;
        // cout << this->head->data.id << endl;
        if (this->head == nullptr) {
            this->head = prev;
        }
        // Walk to new node in original list
        walk = walk->next;
    }
    this->tail = copied;
}

LinkedList& LinkedList::operator=(const LinkedList& source) 
{
    // Implement this function
    clear();
    this->head = nullptr;
    this->tail = nullptr;
    if (source.head == nullptr) {
        return *this;
    }
    Node *walk = source.head;
    // Create copied node
    Node *copied = nullptr;
    Node *prev = nullptr;
    while (walk != nullptr) {
        // If copied not null, use prev to track copied
        if (copied != nullptr) {
            prev = copied;
        }
        // create copied node
        copied = new Node;
        //copied node to new walk 
        copied->data = walk->data;
        copied->next = nullptr;
        // If not first Walk, assign prev next to new copied
        if (prev != nullptr) {
            prev->next = copied;
        }
        if (this->head == nullptr) {
            this->head = prev;
        }
        // Walk to new node in original list
        walk = walk->next;
    }
    this->tail = copied;
    return *this;
}

void LinkedList::insert(std::string id, int fov, double volume, 
                        double center_x, double center_y, 
                        double min_x, double max_x, 
                        double min_y, double max_y) 
{
    // Implement this function
    Node* newNode = new Node(id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y);
    newNode->next = nullptr;
    // cout << newNode->data.id << endl;

    Node *walk = this->head;
    if (this->head == nullptr) {
        this->head = newNode;
        this->tail = newNode;
        return;
    }
    // if (this->head->next == nullptr) {
    //     if (newNode->data < this->head->data) {
    //         newNode->next = this->head;
    //         this->head = newNode;
    //         return;
    //     }
    // }
    if(newNode->data < this->head->data) {
        newNode->next = this->head;
        this->head = newNode;
        return;
    }
    Node *prev = nullptr;
    while(walk != nullptr) {
        prev = walk;
        walk = walk->next;
        if (walk == nullptr) {
            break;
        }
        if (newNode->data < walk->data) {
            prev->next = newNode;
            newNode->next = walk;
            return;
        }
    }
    this->tail->next = newNode;
    this->tail = newNode;
}

void LinkedList::remove(std::string id, int fov, double volume, 
                        double center_x, double center_y, 
                        double min_x, double max_x, 
                        double min_y, double max_y) {
    // Implement this function
    Node *walk = this->head;
    if (walk == nullptr) {
        return;
    }
    Node *removeNode = new Node(id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y);
    if (walk->data == removeNode->data) {
        this->head = walk->next;
        delete walk;
        delete removeNode;
        return;
    }
    while(walk != nullptr) {
        if (walk->next->data == removeNode->data) {
            delete removeNode;
            removeNode = walk->next;
            if (walk->next->next == nullptr) {
                walk->next = nullptr;
            }
            else {
                walk->next = removeNode->next;
            }
            delete removeNode;
            return;
        }
        walk = walk->next;
    }
}

void LinkedList::clear() {	
    // Implement this function
    if (this->head == nullptr) {
        return;
    }
    Node* walk = this->head;
    Node* nextWalk = nullptr;
    while (walk != nullptr) {
        nextWalk = walk->next;
        delete walk;
        walk = nextWalk;
    }
    this->head = nullptr;
    this->tail = nullptr;
}

string LinkedList::print() const 
{
   	// Implement this function
    ostringstream outSS;
    outSS << "fov,volume,center_x,center_y,min_x,max_x,min_y,max_y" << endl;
    Node* walk = this->head;
    while (walk != nullptr) {
        outSS << walk->data.id << ',' << walk->data.fov << ',' << walk->data.volume << ',' <<  
                walk->data.center_x << ',' << walk->data.center_y << ',' << walk->data.min_x << ',' 
                << walk->data.max_x << ',' << walk->data.min_y << ',' << walk->data.max_y << endl;
        walk = walk->next;
    }
    string outString = outSS.str();
    return outString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}

// given a fov number, count the cells observed in that fov
int LinkedList::countN(int fov)
{
	/* Do not modify this function */
    int count = 0;
    Node* cur = head;
    while (cur)
    {
        if (cur->data.fov == fov)
            count++;
        cur = cur->next;
    }
    return count;
}

/* given a fov number, compute the average volume of all the cells observed in
 * that fov
 */
double LinkedList::average(int fov)
{
    // Implement this function
    double total = 0;
    Node *walk = this->head;
    while(walk != nullptr) {
        if (walk->data.fov == fov) {
            total += walk->data.volume;
        }
        walk = walk->next;
    }
    return total/this->countN(fov);
}

/* given a fov number, compute the variance volume of all the cells observed in
 * that fov
 */
double LinkedList::variance(int fov)
{
	/* Do not modify this function */
    double sum = 0;
    double avg = average(fov);
    int count = countN(fov);

    if (count == 0)
        return -1;

    Node* cur = head;
    while (cur)
    {
        if (fov == cur->data.fov)
            sum += (cur->data.volume - avg) * (cur->data.volume - avg);
        cur = cur->next;
    }
    return sum/count;
}

/* given a fov number, remove outliers
 */
string LinkedList::outliers(int k, int j, int N)
{
    ostringstream outSS;
    // Implement this function
    int count = this->countN(k);
    if (count < N) {
        outSS << "Less than " << N << " cells in fov " << k;
        string a = outSS.str();
        return a;
    }
    double avg = this->average(k);
    double delta = sqrt(this->variance(k));
    double lowerBound = avg - j * delta;
    double upperBound = avg + j * delta;
    // cout << "Upper bound: " << upperBound << endl;
    // cout << "Lower bound: " << lowerBound << endl;
    Node *walk = this->head;
    int removeCount = 0;
    while (walk != nullptr) {
        if ((walk->data.volume < lowerBound || walk->data.volume > upperBound) && walk->data.fov == k) {
            Node* removeNode = walk;
            walk = walk->next;
            this->remove(removeNode->data.id, removeNode->data.fov, removeNode->data.volume, 
                        removeNode->data.center_x, removeNode->data.center_y, removeNode->data.min_x, 
                        removeNode->data.max_x, removeNode->data.min_y, removeNode->data.max_y);
            removeCount++;
            continue;
        }
        walk = walk->next;
    }
    return to_string(removeCount) + " cells are removed.";
}

