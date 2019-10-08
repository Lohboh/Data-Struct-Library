template <class T>
class CircularDynamicArray{
    public:
    //Default Constructor, Specified Capacity, and Destructor
    CircularDynamicArray();
    CircularDynamicArray(int s);
    ~CircularDynamicArray();
    CircularDynamicArray(const CircularDynamicArray &oldarray);
    void operator=(const CircularDynamicArray &oldarray);
    int &operator[] (int i);
    void addFront(T v);
    void addEnd(T v);
    void delFront();
    void delEnd();
    int length();
    int capacity();
    T *cdarray;
    T *oldarray;
    private:
    int arrcapacity;
    int arrsize;
    int frontIndex;
    int endIndex;

};

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(){
    //Array of type T is created, room for 2 items.
    cdarray = new T[2];
    arrcapacity = 2;
    arrsize = 0;
    frontIndex = 0;
    endIndex = 1;
}

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(int s){
    //Array of type T is created, room for s items.
    cdarray = new T[s];
    arrcapacity = s;
    arrsize = s;
    frontIndex = 0;
    endIndex = arrsize - 1;
}

template <class T>
CircularDynamicArray<T>::~CircularDynamicArray(){
    delete cdarray;
}

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(const CircularDynamicArray &oldarray){
    cdarray = new T[arrcapacity];

    for(int i = 0; i < arrsize; i++){
        cout << cdarray[i] << " placed at index " << ((frontIndex+i) % oldarray.arrcapacity) << endl;
        cdarray[i] = oldarray[(frontIndex + i) % oldarray.arrcapacity()];
    }
}

template <class T>
void CircularDynamicArray<T>::operator=(const CircularDynamicArray &oldarray){
    cdarray = new T[arrcapacity];

    for(int i = 0; i < arrsize; i++){
        cout << cdarray[i] << " placed at index " << ((frontIndex+i) % oldarray.arrcapacity) << endl;
        cdarray[i] = oldarray[(frontIndex + i) % oldarray.arrcapacity()];
    }
}

template <class T>
int &CircularDynamicArray<T>::operator[](int i){
    if(i >= arrcapacity){
        cout << "Out of bounds." << endl;
    }
    return cdarray[(frontIndex+i)%arrcapacity];
}

template <class T>
void CircularDynamicArray<T>::addFront(T v){
    arrsize++;
    //Checks if the array is over capacity.
    //If it isn't:
    if(arrsize <= arrcapacity){
        if(frontIndex == 0){
            frontIndex = arrcapacity - 1;
        }
        else{
            frontIndex--;
        }
        cdarray[frontIndex] = v;
    }
    else{
        arrcapacity = arrcapacity * 2;
        T *temparray = new T[arrcapacity];
        for(int i = 0; i < arrsize-1; i++){
            //cout << cdarray[i] << " placed at index " << ((frontIndex+i) % (arrcapacity/2)) << endl;
            temparray[i+1] = cdarray[(frontIndex + i) % (arrcapacity/2)];
        }
        cdarray = new T[arrcapacity];
        for(int i = 0; i < arrsize; i++){
            cdarray[i] = temparray[i];
        }
        cdarray[0] = v;
        delete temparray;
        frontIndex = 0;
        endIndex = arrsize - 1;

    };
}

template <class T>
void CircularDynamicArray<T>::addEnd(T v){
    arrsize++;
    //Checks if the array is over capacity.
    //If it isn't:
    if(arrsize <= arrcapacity){
        if(endIndex + 1 >= arrcapacity){
            endIndex = 0;
        }
        else{
            endIndex++;
        }
        cdarray[endIndex] = v;
        //cout << v << " inserted." << endl;
    }
    else{
        arrcapacity = arrcapacity * 2;
        T *temparray = new T[arrcapacity];
        for(int i = 0; i < arrsize; i++){
            //cout << cdarray[i] << " placed at index " << ((frontIndex+i) % (arrcapacity/2)) << endl;
            temparray[i] = cdarray[(frontIndex + i) % (arrcapacity/2)];
        }
        cdarray = new T[arrcapacity];
        for(int i = 0; i < arrsize; i++){
            cdarray[i] = temparray[i];
        }
        cdarray[arrsize - 1] = v;
        delete temparray;
        frontIndex = 0;
        endIndex = arrsize - 1;

    };
}

template <class T>
void CircularDynamicArray<T>::delFront(){
    frontIndex++;
    arrsize--;
    if(arrcapacity/arrsize >= 4){
        //cout << "Shrinking from the front." << endl;
        T *temparray = new T[arrcapacity];
        for(int i = 0; i < arrsize; i++){
            temparray[i] = cdarray[(frontIndex + i) % (arrcapacity)];
        }
        arrcapacity = arrcapacity/2;
        frontIndex = 0;
        endIndex = arrsize - 1;
        cdarray = new T[arrcapacity];
        for(int i = 0; i < arrsize; i++){
            cdarray[i] = temparray[i];
        }
        delete temparray;
    }
}

template <class T>
void CircularDynamicArray<T>::delEnd(){
    endIndex--;
    arrsize--;
    if(arrcapacity/arrsize >= 4){
    //cout << "Shrinking from the back." << endl;
    T *temparray = new T[arrcapacity];
    for(int i = 0; i < arrsize; i++){
        temparray[i] = cdarray[(frontIndex + i) % (arrcapacity)];
    }
    arrcapacity = arrcapacity/2;
    frontIndex = 0;
    endIndex = arrsize - 1;
    cdarray = new T[arrcapacity];
    for(int i = 0; i < arrsize; i++){
        cdarray[i] = temparray[i];
    }
    delete temparray;
    }
}

template <class T>
int CircularDynamicArray<T>::length(){
    return arrsize;
}

template <class T>
int CircularDynamicArray<T>::capacity(){
    return arrcapacity;
}