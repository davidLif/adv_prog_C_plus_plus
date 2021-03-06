#ifndef __SUBJECT_H
#define __SUBJECT_H
#include <vector>

class Observer;

// Subject abstract class
// Each subject may be observerd by more than one observer
// For example, a cTime_t object observerd by two different calendars

class Subject {

public:

	// default CTOR
	Subject();

	virtual ~Subject() = 0;
	// attach a new observer
	// if observer already exists, nothing will be changed
	virtual void attach(Observer*);

	// detach an observer
	// if observer does not exist nothing will be changed
	virtual void detach(Observer*);


protected:
	// update() all observers
	virtual void notify();

private:
	std::vector<Observer*> observers;

	// disallow copying the observer collection
	// Observers must explicitly attach to subject
	Subject(const Subject&);
	Subject& operator=(const Subject&);

};


#endif