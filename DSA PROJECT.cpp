#include <iostream>
using namespace std;
#define MAX_FLOORS 5
#define MAX_CAPACITY 3

struct QueueNode {
    int carID;
    QueueNode* next;
    QueueNode(int id) : carID(id), next(NULL) {}
};

class Queue {
public:
    QueueNode *front, *rear;
    Queue() : front(NULL), rear(NULL) {}

    void enqueue(int carID) {
        QueueNode* temp = new QueueNode(carID);
        if (!rear) {
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
    }

    int dequeue() {
        if (!front) return -1;
        int carID = front->carID;
        QueueNode* temp = front;
        front = front->next;
        if (!front) rear = NULL;
        delete temp;
        return carID;
    }

    bool isEmpty() { return front == NULL; }
    void display();
};

void Queue::display() {
    QueueNode* temp = front;
    while (temp) {
        cout << temp->carID << " ";
        temp = temp->next;
    }
    cout << endl;
}

struct StackNode {
    int carID;
    StackNode* next;
    StackNode(int id) : carID(id), next(NULL) {}
};

class Stack {
public:
    StackNode* top;
    int count;
    Stack() : top(NULL), count(0) {}

    bool push(int carID) {
        if (count >= MAX_CAPACITY) return false;
        StackNode* temp = new StackNode(carID);
        temp->next = top;
        top = temp;
        count++;
        return true;
    }

    int pop() {
        if (!top) return -1;
        int carID = top->carID;
        StackNode* temp = top;
        top = top->next;
        delete temp;
        count--;
        return carID;
    }

    bool isEmpty() { return top == NULL; }
    void display();
};

void Stack::display() {
    StackNode* temp = top;
    while (temp) {
        cout << temp->carID << " ";
        temp = temp->next;
    }
    cout << endl;
}

struct ListNode {
    int carID;
    ListNode* next;
    ListNode(int id) : carID(id), next(NULL) {}
};

class LinkedList {
public:
    ListNode *head, *tail;
    LinkedList() : head(NULL), tail(NULL) {}

    void addCar(int carID) {
        ListNode* temp = new ListNode(carID);
        if (!tail) {
            head = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    int removeCar() {
        if (!head) return -1;
        int carID = head->carID;
        ListNode* temp = head;
        head = head->next;
        if (!head) tail = NULL;
        delete temp;
        return carID;
    }

    void display();
};

void LinkedList::display() {
    ListNode* temp = head;
    while (temp) {
        cout << temp->carID << " ";
        temp = temp->next;
    }
    cout << endl;
}

class ParkingLot {
    int floors;
    Stack* parkingFloors;
    Queue entryQueue;
    LinkedList overflowList;

public:
    ParkingLot(int f) : floors(f) {
        parkingFloors = new Stack[floors];
    }

    void addCar(int carID);
    void removeCar(int carID);
    void displayStatus();
    void expandParking(int newFloors);
};

void ParkingLot::addCar(int carID) {
    for (int i = 0; i < floors; i++) {
        if (parkingFloors[i].push(carID)) {
            cout << "Car " << carID << " parked on Floor " << i + 1 << endl;
            return;
        }
    }
    overflowList.addCar(carID);
    cout << "Car " << carID << " added to overflow waitlist." << endl;
}

void ParkingLot::removeCar(int carID) {
    for (int i = 0; i < floors; i++) {
        Stack tempStack;
        bool found = false;
        while (!parkingFloors[i].isEmpty()) {
            int topCar = parkingFloors[i].pop();
            if (topCar == carID) {
                found = true;
                cout << "Car " << carID << " removed from Floor " << i + 1 << endl;
                break;
            } else {
                tempStack.push(topCar);
            }
        }
        while (!tempStack.isEmpty()) {
            parkingFloors[i].push(tempStack.pop());
        }
        if (found) return;
    }
    cout << "Car " << carID << " not found." << endl;
}

void ParkingLot::displayStatus() {
    cout << "--- Parking Lot Status ---" << endl;
    for (int i = 0; i < floors; i++) {
        cout << "Floor " << i + 1 << ": ";
        parkingFloors[i].display();
    }
    cout << "Entry Queue: ";
    entryQueue.display();
    cout << "Overflow Waitlist: ";
    overflowList.display();
}

void ParkingLot::expandParking(int newFloors) {
    Stack* newParkingFloors = new Stack[floors + newFloors];
    for (int i = 0; i < floors; i++) {
        newParkingFloors[i] = parkingFloors[i];
    }
    delete[] parkingFloors;
    parkingFloors = newParkingFloors;
    floors += newFloors;
    cout << "Parking expanded by " << newFloors << " floors." << endl;
}

int main() {
    ParkingLot lot(MAX_FLOORS);
    lot.addCar(101);
    lot.addCar(102);
    lot.addCar(103);
    lot.addCar(104);
    lot.addCar(105);
    lot.addCar(106);
    lot.removeCar(103);
    lot.displayStatus();
    lot.expandParking(2);
    lot.displayStatus();
    return 0;
}



