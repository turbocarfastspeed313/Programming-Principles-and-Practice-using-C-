template<class T>
class vector
{
	int sz; //number of elements in the vector
	T* elem;
	int space; //the maximum number of elements the vector can hold

	void reserve(int newspace);

public:
	
	//constructors
	vector() : sz{0}, elem{nullptr}, space{0} {}

	explicit vector (int size, T def = T()) :sz{size}, elem{new T[size]}, space{size}
	{
		for (int i = 0; i < size; i++) elem[i] = def; // initialize each element to 0		
	}

	//{} initialization
 	vector (std::initializer_list<T> lst)
		:sz{lst.size()}, elem{new T[sz]}, space{lst.size()}
	{
		std::copy (lst.begin(), lst.end(), elem);
	}

	//destructor
	~vector()
	{
		delete[] elem;
	}

 	vector (const vector& arg); //copy constructor
	vector& operator= (const vector& arg); //copy assignment

	vector ( vector&& arg); //move constructor
	vector& operator= (vector&& arg); //move assignment

	//subscript operators
	T& operator[] (int n) { return elem[n]; }
	T operator[] (int n) const { return elem[n]; }

	int size() const { return sz; }
	int capacity() const { return space; }

	void resize(int newspace, T def = T()); //growth
	void push_back(T d);
	void erase();
};

//copy constructor
template<typename T> 
vector<T>::vector (const vector& arg)
	:sz{arg.sz}, elem{new T[sz]}
{
	std::copy (arg.elem, arg.elem + arg.sz, elem);
}

//copy assignment
template<typename T> 
vector<T>& vector<T>::operator= (const vector& arg)
{
	if (this == &arg) return *this; //self-assignment, do nothing

	if (arg.sz <= space) // enough space, no need for extra allocation
	{
		for (int i = 0; i < arg.sz; i++) elem[i] = arg.elem[i]; //copy elements
		sz = arg.sz;
		return *this;
	}

	T* n = new T[arg.sz]; 
	for (int i = 0; i < arg.sz; i++) n[i] = arg.elem[i];  //copy all the elements from a to the newly allocated array
	delete[] elem; //delete the previous value held by elem (remember that it's an ASSIGNMENT, not an INITIALIZATION)
	space = arg.sz;
	sz = arg.sz;
	elem = n; //set the elem (of the current vector) to the argumen's elem
	return *this; //return a self-reference
}

//move constructor
template<typename T> 
vector<T>::vector (vector&& arg)
	:sz{arg.sz}, elem{arg.elem}
{
	arg.sz = 0;
	arg.elem = nullptr;
}

//move assignment
template<typename T> 
vector<T>& vector<T>::operator= (vector&& arg)
{
	delete[] elem;
	elem = arg.elem;
	sz = arg.sz;
	arg.elem = nullptr;
	arg.sz = 0;
	return *this;

}

template<typename T> 
void vector<T>::reserve(int newspace)
{
	if(newspace <= space) return; //never allocate less memory
	T* p = new T[newspace];
	for(int i = 0; i < sz; i++) p[i] = elem[i]; //copy the elements from the old array to the new one
	delete[] elem; //deallocate old space
	elem = p; //point elem to the newly allocated array p
	space = newspace;
}

template<typename T> 
void vector<T>::resize(int newspace, T def)
//make the vector have newsize elements
//initialize each new element with a default value 
//	-default T value 
//	-or a value d if specified
{
	reserve(newspace);
	for (int i = sz; i < newspace; i++) elem[i] = def;
	sz = newspace;
}

template<typename T> 
void vector<T>::push_back(T d)
{
	if(space == 0) //if there's no space (default constructor)
		reserve(8); //reserve space for 8 elements

	else if (sz == space) //if the space is equal to the size
		reserve(space * 2); //double the space

	elem[sz] = d; // add d at the end
	++sz; // increase size by 1
	
}

template<typename T>
void vector<T>::erase()
{
	T* n = new T[sz];
	delete[] elem;
	elem = n;
}