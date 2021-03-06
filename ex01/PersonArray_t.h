#include "Person_t.h"

class PersonArray_t
{
public:
	~PersonArray_t();

	explicit PersonArray_t(size_t initial_size = PersonArray_t::glob_reallocation_size);  // costructs dynamic array with given minimal number of elements
																						  // may be used as a "default" constructor, e.g. no arguments

	inline size_t getNumElements() const;   // returns the current number of persons in array
	inline size_t getCapacity()    const;   // returns the current dynamic array capacity

	void insert(const Person_t* personPtr);	// inserts given person to the end of array
											// if array is full in time of method call, method will first expand the array 
											// capacity by glob_reallocation_size elements


	inline Person_t* firstElement() const;   // returns the first person pointer in the array
											 // returns NULL if empty
	inline Person_t* lastElement() const;    // returns the last person pointer in the array
											 // returns NULL if empty

	inline bool isEmpty() const;             // returns true iff array is empty

	Person_t* find(const Person_t& person) const; // method tries to find given person in the array
												  // if such person is found, the element is returned
												  // otherwise, returns NULL 

	Person_t* remove(const Person_t& person);	  // method removes the given element
												  // if more than one found, removes only the first
												  // on success, returns the element, otherwise returns NULL

	void removeDelete(const Person_t& person);	  // removes and deletes all elements with given value 

	inline void removeAll();       // empty array without deleting the elements themselves
	void removeDeleteAll();		   // empty array and delete all the elements 

	int append(size_t index, const Person_t* person);		 // appends given person after given index
													         // if index is out of bounds, returns 0
													         // on success returns 1

	int prepend(size_t index, const Person_t* person);		 // prepends given element before given index
															 // if index is out of bounds, returns 0
													         // on success, returns 1

	inline Person_t* elementAt(size_t index) const;           // returns the element at given index
															  // returns NULL if index is out of bounds


private:
	const Person_t**	m_array;	// array of pointers to persons 
									// the const specifier in this case indicates that we are not going
								    // to modify the persons' data members throughout our PersonArray_t implementation
								    // as a means of protection
									

	size_t      m_capacity;         // number of elements the dynamic array can currently hold without reallocating
	size_t      m_num_elements;     // number of elements currently in the array

	PersonArray_t(const PersonArray_t&);                // private  copy constructor (objects cannot be copied)
	PersonArray_t& operator= (const PersonArray_t&);    // private assignment operator (objects cannot be copied)

	void increaseCapacity();				// increase array capacity by glob_reallocation_size
											// implemeneted by allocating a new array with bigger size
											// and then moving all elements to the new array

	void pushAllStartingAt(size_t index);		 // push all the elements, starting from given index, one slot further (e.g. increase indices of said elements by one)
											     // effectively "freeing" the slot at given index

	void contractStartingAt(size_t index);		 // push all the elements after given index, to the "left" (one index down), removing the element at index

	static const size_t glob_reallocation_size;  // the number of elements that are added to the capacity when an array is full
												 // and we wish to insert a new element

};


extern ostream& operator<<(ostream& os, const PersonArray_t& array); // "To string" - fill os with textual representation of the array

// inline implementations

inline size_t PersonArray_t::getCapacity() const
{
	return m_capacity;
}

inline Person_t* PersonArray_t::firstElement() const
{
	if (isEmpty())
		return NULL;

	return (Person_t*)this->m_array[0];
}

inline Person_t* PersonArray_t::lastElement() const
{
	if (isEmpty())
		return NULL;

	return (Person_t*)(m_array[m_num_elements - 1]);

}
inline size_t PersonArray_t::getNumElements() const
{
	return m_num_elements;
}


inline Person_t* PersonArray_t::elementAt(size_t index) const
{
	if (index >= m_num_elements)
		return NULL;

	return (Person_t*)m_array[index];
}

inline bool PersonArray_t::isEmpty() const
{
	return m_num_elements == 0;
}

inline void PersonArray_t::removeAll()
{
	m_num_elements = 0; //this means that any pointers left in the array would be treated as junk
						//we would never access them again and some of them will be overriden as we insert new pointers
}