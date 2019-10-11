template <class T>
class CircularDynamicArray{
    public:
    //Default Constructor, Specified Capacity, and Destructor
    CircularDynamicArray();
    CircularDynamicArray(int s);
    ~CircularDynamicArray();
    CircularDynamicArray(const CircularDynamicArray &oldArray);
    void operator=(const CircularDynamicArray &oldArray);
    int &operator[] (int i);
    void addFront(T v);
    void addEnd(T v);
    void delFront();
    void delEnd();
    int linearSearch(T e);
    void merge(T arr[], int leftIndex, int midIndex, int rightIndex);
    void mergeSort(T arr[], int leftIndex, int rightIndex);
    void stableSort();
    int length();
    int capacity();
    T *cdArray;
    T *oldArray;
    private:
    int arrCapacity;
    int arrSize;
    int frontIndex;
    int endIndex;
    T error;

};

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(){
    //Array of type T is created, room for 2 items.
    cdArray = new T[2];
    arrCapacity = 2;
    arrSize = 0;
    frontIndex = 0;
    endIndex = 1;
}

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(int s){
    //Array of type T is created, room for s items.
    cdArray = new T[s];
    arrCapacity = s;
    arrSize = s;
    frontIndex = 0;
    endIndex = arrSize - 1;
}

template <class T>
CircularDynamicArray<T>::~CircularDynamicArray(){
    delete cdArray;
}

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(const CircularDynamicArray &oldArray){
    cdArray = new T[arrCapacity];

    for(int i = 0; i < arrSize; i++){
        cout << cdArray[i] << " placed at index " << ((frontIndex+i) % oldArray.arrCapacity) << endl;
        cdArray[i] = oldArray[(frontIndex + i) % oldArray.arrCapacity()];
    }
}

template <class T>
void CircularDynamicArray<T>::operator=(const CircularDynamicArray &oldArray){
    cdArray = new T[arrCapacity];
    arrSize = oldArray.arrSize;
    arrCapacity = oldArray.arrCapacity;
    frontIndex = oldArray.frontIndex;
    endIndex = oldArray.endIndex;
    for(int i = 0; i < arrCapacity; i++){
        //cout << cdArray[i] << " placed at index " << i << endl;
        cdArray[i] = oldArray.cdArray[i];
    }
}

template <class T>
int &CircularDynamicArray<T>::operator[](int i){
    if(i >= arrCapacity){
        cout << "Out of bounds reference: " << i << endl;
        return error;
    }
    return cdArray[(frontIndex+i)%arrCapacity];
}

template <class T>
void CircularDynamicArray<T>::addFront(T v){
    arrSize++;
    //Checks if the array is over capacity.
    //If it isn't:
    if(arrSize <= arrCapacity){
        if(frontIndex == 0){
            frontIndex = arrCapacity - 1;
        }
        else{
            frontIndex--;
        }
        cdArray[frontIndex] = v;
    }
    else{
        arrCapacity = arrCapacity * 2;
        T *tempArray = new T[arrCapacity];
        for(int i = 0; i < arrSize-1; i++){
            //cout << cdArray[i] << " placed at index " << ((frontIndex+i) % (arrCapacity/2)) << endl;
            tempArray[i+1] = cdArray[(frontIndex + i) % (arrCapacity/2)];
        }
        cdArray = new T[arrCapacity];
        for(int i = 0; i < arrSize; i++){
            cdArray[i] = tempArray[i];
        }
        cdArray[0] = v;
        delete tempArray;
        frontIndex = 0;
        endIndex = arrSize - 1;

    };
}

template <class T>
void CircularDynamicArray<T>::addEnd(T v){
    arrSize++;
    //Checks if the array is over capacity.
    //If it isn't:
    if(arrSize <= arrCapacity){
        if(endIndex + 1 >= arrCapacity){
            endIndex = 0;
        }
        else{
            endIndex++;
        }
        cdArray[endIndex] = v;
        //cout << v << " inserted." << endl;
    }
    else{
        arrCapacity = arrCapacity * 2;
        T *tempArray = new T[arrCapacity];
        for(int i = 0; i < arrSize; i++){
            //cout << cdArray[i] << " placed at index " << ((frontIndex+i) % (arrCapacity/2)) << endl;
            tempArray[i] = cdArray[(frontIndex + i) % (arrCapacity/2)];
        }
        cdArray = new T[arrCapacity];
        for(int i = 0; i < arrSize; i++){
            cdArray[i] = tempArray[i];
        }
        cdArray[arrSize - 1] = v;
        delete tempArray;
        frontIndex = 0;
        endIndex = arrSize - 1;

    };
}

template <class T>
void CircularDynamicArray<T>::delFront(){
    frontIndex++;
    arrSize--;
    if(arrCapacity/arrSize >= 4){
        //cout << "Shrinking from the front." << endl;
        T *tempArray = new T[arrCapacity];
        for(int i = 0; i < arrSize; i++){
            tempArray[i] = cdArray[(frontIndex + i) % (arrCapacity)];
        }
        arrCapacity = arrCapacity/2;
        frontIndex = 0;
        endIndex = arrSize - 1;
        cdArray = new T[arrCapacity];
        for(int i = 0; i < arrSize; i++){
            cdArray[i] = tempArray[i];
        }
        delete tempArray;
    }
}

template <class T>
void CircularDynamicArray<T>::delEnd(){
    endIndex--;
    arrSize--;
    if(arrCapacity/arrSize >= 4){
    //cout << "Shrinking from the back." << endl;
    T *tempArray = new T[arrCapacity];
    for(int i = 0; i < arrSize; i++){
        tempArray[i] = cdArray[(frontIndex + i) % (arrCapacity)];
    }
    arrCapacity = arrCapacity/2;
    frontIndex = 0;
    endIndex = arrSize - 1;
    cdArray = new T[arrCapacity];
    for(int i = 0; i < arrSize; i++){
        cdArray[i] = tempArray[i];
    }
    delete tempArray;
    }
}

template <class T>
int CircularDynamicArray<T>::linearSearch(T e){
    for(int i = 0; i < arrSize - 1; i++){
        if(cdArray[(frontIndex + i) % (arrCapacity)] == e){
            return i;
        }
    }
    return -1;
}

template <class T>
void CircularDynamicArray<T>::merge(T arr[], int leftIndex, int midIndex, int rightIndex){
    //Creating temporary arrays.
    int leftHalfSize = midIndex - leftIndex + 1;
    int rightHalfSize = rightIndex - midIndex;
    T leftTemp[leftHalfSize], rightTemp[rightHalfSize];

    int subIndexL, subIndexR, subIndexMerged;
    //Copying data to temporary arrays.
    for(subIndexL = 0; subIndexL < leftHalfSize; subIndexL++){
        leftTemp[subIndexL] = arr[leftIndex + subIndexL];
    }

    for(subIndexR = 0; subIndexR < rightHalfSize; subIndexR++){
        rightTemp[subIndexR] = arr[midIndex + subIndexR + 1];
    }
    //Initial indices of the subarrays.
    subIndexL = 0;
    subIndexR = 0;
    subIndexMerged = leftIndex;

    //Merge the subarrays back into the original array
    while(subIndexL < leftHalfSize && subIndexR < rightHalfSize){
        if(leftTemp[subIndexL] <= rightTemp[subIndexR]){
            arr[subIndexMerged] = leftTemp[subIndexL];
            subIndexL++;
        }
        else{
            arr[subIndexMerged] = rightTemp[subIndexR];
            subIndexR++;
        }
        subIndexMerged++;
    }

    //Whatever remains in the left array is copied into the original array.
    while(subIndexL < leftHalfSize){
        arr[subIndexMerged] = leftTemp[subIndexL];
        subIndexL++;
        subIndexMerged++;
    }

    //Same for the right array.
    while(subIndexR < rightHalfSize){
        arr[subIndexMerged] = rightTemp[subIndexR];
        subIndexR++;
        subIndexMerged++;
    }
}

template <class T>
void CircularDynamicArray<T>::mergeSort(T arr[], int leftIndex, int rightIndex){
    if(leftIndex < rightIndex){
        //Finds the midpoint.
        int midPoint = leftIndex + (rightIndex - leftIndex) / 2;

        //Sorts both halves.
        mergeSort(arr, leftIndex, midPoint);
        mergeSort(arr, midPoint+1, rightIndex);

        //Merges the two halves.
        merge(arr, leftIndex, midPoint, rightIndex); 
    }
}

template <class T>
void CircularDynamicArray<T>::stableSort(){
    mergeSort(cdArray, frontIndex, endIndex);
}

template <class T>
int CircularDynamicArray<T>::length(){
    return arrSize;
}

template <class T>
int CircularDynamicArray<T>::capacity(){
    return arrCapacity;
}