

#include <iostream>
#include <vector>
using namespace std;

template<class T>
class PriorityQueue {
public:

    PriorityQueue() {};//default constructor
    T pop();
    void push(T element);
    void changePriority(T element);
    void deleteElement(T element);
    int getTotalElements();
    int getElementIndex(T element);
    T getElement(int index);
    void printQueue();
	bool ifexist(T data);
protected:
    vector<T> m_queue;
    vector<unsigned int> getChildrenIndex(int index);
    int getParentIndex(int index);
    bool isRoot(int index);
    void heapify();
	virtual void bubbleup(int index);
	virtual void sinkDown(int index = 0);
    void swapElements(int index1, int index2);

};

template<typename T>
bool PriorityQueue<T>::ifexist(T data)
{
	for(int i=0;i<m_queue.size();i++)
	{
		if(m_queue[i]==data)
			return true;
	}
	return false;
}

template<typename T>
void PriorityQueue<T>::heapify() {
    for (int i = m_queue.size() - 1; i >= 0; --i) {
        sinkDown(i);
    }
}

template<typename T>
void PriorityQueue<T>::push(T element) {
    m_queue.push_back(element);

    if (m_queue.empty()) {
        return; //only node
    }
    //else bubble up the last node
    bubbleup(getTotalElements() - 1);
}

// this funk deletes the min and returns the min
template<typename T>
T PriorityQueue<T>::pop() {
    T element;
    if (m_queue.empty()) {
        cout << "Nothing to pop. Queue is empty" << endl;
        element = 0;
    }
    // Get the root element
    element = m_queue[0];

    // Add the last element to the root and resize
    m_queue[0] = m_queue[m_queue.size() - 1];
    m_queue.resize(m_queue.size() - 1);

    // Sink down the root element to get the min heap again.
    sinkDown();

    // return the root element
    return element;

}


template<typename T>
void PriorityQueue<T>::changePriority(T element) {

    int index = getElementIndex(element);

    if (index == -1) {
        return; // This vertex is not there in the priority queue.
    }

    m_queue[index].setCost(element.getCost());
    m_queue[index].setPrevNode(element.getPrevNode());

    // else update the cost of this vertex and either bubbleup or sinkDown.
    int parentIndex = getParentIndex(index);

    if (isRoot(index)) {
        sinkDown(index);
        return;
    }

    if (m_queue[parentIndex] > m_queue[index]) {
        bubbleup(index);
    } else {
        sinkDown(index);
    }

}

template<typename T>
void PriorityQueue<T>::deleteElement(T element) {
    int index = getElementIndex(element);
    if (index == -1) {
        return; //this vertex does not exist in the queue.
    }

    // Fill up the node with the last node in the queue and either bubble up or sink down.

    m_queue[index] = m_queue[m_queue.size() - 1];
    m_queue.resize(m_queue.size() - 1);

    int parentIndex = getParentIndex(index);

    if (isRoot(index)) {
        sinkDown(index);
        return;
    }

    if (m_queue[parentIndex] > m_queue[index]) {
        bubbleup(index);
    } else {
        sinkDown(index);
    }

}

template<typename T>
int PriorityQueue<T>::getParentIndex(int index) {
    int parentIndex;
    if (isRoot(index)) {
        parentIndex = index; // returns the same index if it's the root element
    }
    //else
    parentIndex = static_cast<int>((index - 1) / 2);
    return parentIndex;
}

template<typename T>
bool PriorityQueue<T>::isRoot(int index) {
    if (index == 0) {
        return true;
    }
    // else
    return false;
}

template<typename T>
vector<unsigned int> PriorityQueue<T>::getChildrenIndex(int index) {
    vector<unsigned int> childrenIndex;

    if ((2 * index + 1) < m_queue.size()) {
        childrenIndex.push_back(2 * index + 1);
    }

    if ((2 * index + 2) < m_queue.size()) {
        childrenIndex.push_back(2 * index + 2);
    }

    return childrenIndex;

}

template<typename T>
int PriorityQueue<T>::getTotalElements() {
    return m_queue.size();
}

template<typename T>
int PriorityQueue<T>::getElementIndex(T element) {
    // returns -1 if element not found
    int index = -1;
    for (int i = 0; i < m_queue.size(); i++) {
        if (m_queue[i] == element) {
            index = i;
            break;
        }
    }

    // else
    return index;
}

template<typename T>
void PriorityQueue<T>::bubbleup(int index) {
    bool isMinHeap = false;
    int currentIndex = index;

    while (!isMinHeap) {
        if (isRoot(currentIndex)) {
            isMinHeap = true;
            return; // It's the root node.
        }

        // else
        int parentIndex = getParentIndex(currentIndex);

        if (m_queue[parentIndex] > m_queue[currentIndex]) {
            swapElements(currentIndex, parentIndex);
            currentIndex = parentIndex;
        } else {
            isMinHeap = true;
        }

    }
}

template<typename T>
void PriorityQueue<T>::sinkDown(int index) {
    int currentIndex = index;
    bool isMinHeap = false;
    while (!isMinHeap) {
        vector<unsigned int> childrenIndex = getChildrenIndex(currentIndex);
        int NumChildren = childrenIndex.size();
        switch (NumChildren) {
        case 0:
            isMinHeap = true; // It's a leaf. No need to sink down any further.
            break;

        case 1: // 1 children

            if (m_queue[currentIndex] > m_queue[childrenIndex[0]]) {
                swapElements(currentIndex, childrenIndex[0]);
                currentIndex = childrenIndex[0];
            } else {
                isMinHeap = true;
            }
            break;

        case 2:
            // Get the smaller children first.
            int smallerChildrenIndex =
                    (m_queue[childrenIndex[0]] < m_queue[childrenIndex[1]]) ?
                            childrenIndex[0] : childrenIndex[1];
            if (m_queue[currentIndex] > m_queue[smallerChildrenIndex]) {
                swapElements(currentIndex, smallerChildrenIndex);
                currentIndex = smallerChildrenIndex;
            } else {
                isMinHeap = true;
            }
            break;
        }
    }
}

template<typename T>
void PriorityQueue<T>::swapElements(int index1, int index2) {

    T temp = m_queue[index1];
    m_queue[index1] = m_queue[index2];
    m_queue[index2] = temp;
}

template<typename T>
T PriorityQueue<T>::getElement(int index) {
    return m_queue[index];
}

template<typename T>
void PriorityQueue<T>::printQueue() {
    for (typename vector<T>::iterator it = m_queue.begin(); it != m_queue.end();
            it++) {
        cout << *it << "  ";
    }
}

template <class T>
class maxheap :public PriorityQueue<T>
{
protected:
	void sinkDown(int index) 
	{
		int currentIndex = index;
		bool isMaxHeap = false;
		while (!isMaxHeap) {
			vector<unsigned int> childrenIndex = getChildrenIndex(currentIndex);
			int NumChildren = childrenIndex.size();
			switch (NumChildren) {
			case 0:
				isMaxHeap = true; // It's a leaf. No need to sink down any further.
				break;

			case 1: // 1 children

				if (m_queue[currentIndex] < m_queue[childrenIndex[0]]) {
					swapElements(currentIndex, childrenIndex[0]);
					currentIndex = childrenIndex[0];
				} else {
					isMaxHeap = true;
				}
				break;

			case 2:
				// Get the smaller children first.
				int smallerChildrenIndex =
						(m_queue[childrenIndex[0]] > m_queue[childrenIndex[1]]) ?
								childrenIndex[0] : childrenIndex[1];
				if (m_queue[currentIndex] < m_queue[smallerChildrenIndex]) {
					swapElements(currentIndex, smallerChildrenIndex);
					currentIndex = smallerChildrenIndex;
				} else {
					isMaxHeap = true;
				}
				break;
			}
		}
}

	void bubbleup(int index) 
	{
		bool isMaxHeap = false;
		int currentIndex = index;

		while (!isMaxHeap) {
			if (isRoot(currentIndex)) {
				isMaxHeap = true;
				return; // It's the root node.
			}

			// else
			int parentIndex = getParentIndex(currentIndex);

			if (m_queue[parentIndex] < m_queue[currentIndex]) {
				swapElements(currentIndex, parentIndex);
				currentIndex = parentIndex;
			} else {
				isMaxHeap = true;
			}

		}
}
	
//public:
//	maxheap(): PriorityQueue<T>(){};

};


//#include <iostream>
//#include<vector>
//#include <algorithm>
//#include <stdexcept>
//
//using namespace std;
//
//
//template <class T>
//class Minheap
//{
//private:
//	int size;
//	vector<T> arr;
//	// returns the parent of the ith node
//	// Recursive Heapify-down algorithm
//	// the node at index i and its two direct children
//	// violates the heap property
//	void heapify_down(T i)
//	{
//		// get left and right child of node at index i
//		T left = l(i);
//		T right = r(i);
//
//		T smallest = i;
//
//		// compare arr[i] with its left and right child
//		// and find smallest value
//		if (left < size() && arr[left] < arr[i])
//			smallest = left;
//
//		if (right < size() && arr[right] < arr[smallest])
//			smallest = right;
//
//		// swap with child having lesser value and 
//		// call heapify-down on the child
//		if (smallest != i) {
//			swap(arr[i], arr[smallest]); ////////////////////////////////////////////???????????????????????????????????
//			heapify_down(smallest);
//		}
//
//	void buildHeap( );
//	void percolateDown( int hole);
//
//	
//
//
//public:
//
//  Minheap( int capacity );
//  T parent(int i)
//	{
//		return arr[(i-1)/2];
//	}
//  T r(int i)
//  {
//	  return arr[2*i+1];
//  }
//  T l(int i)
//  {
//	  return arr[2*i+2];
//  }
//
//  int size()
//  {return size;}
//
//	bool isEmpty( ) const
//	{return size()==0;}
//
//
//const T & findMin( ) const;
//
//void insert( const T & x );
//
//void deleteMin( );
//
//void deleteMin( T & minItem );
//
//void makeEmpty( );
//
//};
//
////template <class T>
////Minheap<T>:: Minheap(int capasity)
////{
////
//
////}
//
////template <class T>
////template <class T>
//
//
//template <class T>
//void Minheap<T>::insert( const T & x )
//{
//
//
//// Percolate up
//
//// Note that instead of swapping we move the hole up
//
//	int hole = ++size;
//
//	for ( ; hole > 1 && x < arr[ hole / 2 ]; hole /= 2 )
//
//		arr[ hole ] = arr[ hole / 2 ];
//
//	arr[ hole ] = x;
//
//}
//
//template <class T>
//void Minheap<T>::deleteMin( )
//
//{
//
//if ( isEmpty( ) )
//
//throw Underflow( );
//
//// move the last element to the first and shrink the array
//
//arr[ 1 ] = arr[ size–– ];
//
//percolateDown( 1 );
//
//}
//
//template <class T>
//void Minheap<T>::percolateDown( int hole )
//{
//
//	int child;
//	T tmp = array[ hole ]; // tmp is the item that will
//
//	// be percolated down
//
//	for( ; hole * 2 <= size; hole = child )
//	{
//		child = hole * 2;
//		if ( child != size && arr[ child + 1 ] < arr[ child ] )
//		child++;
//
//		if ( arr[ child ] < tmp )
//			arr[ hole ] = arr[ child ];
//
//		else
//			break;
//	}
//
//	arr[ hole ] = tmp;
//
//}
//
//
//
//
//
////template <class T>
////void Minheap<T>::buildHeap(vector<T> Input)
////{
////
////arr = Input; // copy input array to private array;
////
////size = Input.size();
////
////for ( int i = currentSize / 2; i > 0; i–– )
////
////percolateDown( i );