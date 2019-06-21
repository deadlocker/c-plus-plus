#ifndef STACK_H
#define STACK_H


//  stack declaration


template<typename a>
class Stack {

	/**
	 * This is the function to find number of stackData in stack
	 */
	size_t size;

	/**
	 * This is the functoin to find maximum number of stackData possible in stack
	 */
	 
	size_t value;

	/**
	 * This is the element pointer for dynamic memory allocation to store stackData
	 */
	 
	a *stackData;

public:

	/**
	 * constructor
	 */
	 
    Stack();

    Stack(size_t);

    /**
     * copy constructor
     */
     
    Stack(const Stack&);

    /**
     * copy assigner
     */
    Stack& operator = (const Stack&);

    /**
     * destructor
     */
     
    ~Stack();

    /** 
     * function to get size
     */
     
    size_t current_size() const;

    /**
     * get value
     */
     
    size_t maximum_value() const;

    /**
     * function to checkif stack is full or not
     */
     
	bool is_full();

	/**
	 * function to tes if empty or not
	 */
	 
	bool is_empty();

	/**
	 * function to clear content
	 */
	 
	void clear();

    /**
     * function to push top element
     */
     
    bool push(a);

    /**
     * function to get copy of top element
     */
     
    a top();

    /**
     * function to pop top element
     */
     
    bool pop();
};



/**
 * This is the constructors
 */
 
template<typename a>
Stack<a>::Stack()
    : size(0)
    , value(80) {

    stackData = new a[value];
}

template<typename a>
Stack<a>::Stack(size_t x)
    : size(0)
    , value(x) {

    stackData = new a[value];
}

/**
 * This is the copy constructor
 */
 
template<typename a>
Stack<a>::Stack(const Stack<a>& sta)
    : size(sta.size)
    , value(sta.value) {

    stackData = new a[value];
    for(size_t i = 0; i < value; ++i) stackData[i] = sta.stackData[i];
}

/**
 * This is the copy assigner function
 */
 
template<typename a>
Stack<a>& Stack<a>::operator = (const Stack<a>& sta) {
    size = sta.size;
    value = sta.value;

    stackData = new a[value];
    for(size_t m = 0; m < value; ++m) stackData[m] = sta.stackData[m];

    return *this;
}

/**
 * This is the destructor function
 */
 
template<typename a>
Stack<a>::~Stack() {

    delete [] stackData;
    stackData = nullptr;
}

/**
 * This is the function to get size
 */
 
template<typename a>
size_t Stack<a>::current_size() const {
    return size;
}

/**
 * This is the function to get value
 */
 
template<typename a>
size_t Stack<a>::maximum_value() const {
    return value;
}

/**
 * This is the function to test if stack is full
 */
 
template<typename a>
bool Stack<a>::is_full() {
    if(size == value) {
        return true;
    } else {
        return false;
    }
}


/**
 * function to clear content
 */
	 
template<typename a>
void Stack<a>::clear() {
    size = 0;
}



/**
 * Stack function to check if stack is empty or not
 */
 
template<typename a>
bool Stack<a>::is_empty() {
    if(size == 0) {
        return true;
    } else {
        return false;
    }
}



/**
 * stack function to push top element
 */
 
template<typename a>
bool Stack<a>::push(a new_element) {
    if(size >= value) {
        return false;
    } else {
        ++size;
        stackData[size - 1] = new_element;
        return true;
    }
}

/**
 * stack function to get copy of top element
 */
 
template<typename a>
a Stack<a>::top() {
    if(size == 0) {
        a not_an_element;
        return not_an_element;
    } else {
        return stackData[size - 1];
    }
}

/**
 * stack function to pop top element
 */
template<typename a>
bool Stack<a>::pop() {
    if(size == 0) {
        return false;
    } else {
        --size;
        return true;
    }
}

#endif
