#include <iostream>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

//CDA class
template <class elmtype> class CDA{
    private:
        int frontIndex;
        int capacity;
        int size;
        elmtype *currIndex;

    public:
        int lastIndex;
//regular constructor
        CDA(){
            currIndex = new elmtype[1];
            capacity = 1;
            size  = 0;
            frontIndex = 0;
            lastIndex = 0;
        }

//second constructor we were required to setup
        CDA(int s){
            currIndex = new elmtype[s];
            capacity = s;
            size  = 0; 
            frontIndex = 0;
            lastIndex = s-1;
        }
//third constructor
        CDA(int s, elmtype init){
            currIndex = new elmtype[s];
            capacity = s;
            size  = 0;
            frontIndex = 0;
            lastIndex = s-1; 

            for(int x = 0; x < s; x++){ 
                currIndex[x] = init;
            }
        }


//copy constructor
        CDA(const CDA &temp) {
            frontIndex = temp.frontIndex;
            lastIndex = temp.lastIndex; 
            capacity = temp.capacity;
            size = temp.size;

            currIndex = new elmtype[capacity];
            for(int x = 0; x < capacity; x++){
                currIndex[x] = temp.currIndex[x];
            }
        }

CDA& operator = (const CDA &temp){
            
            frontIndex = temp.frontIndex;
            lastIndex = temp.lastIndex; 
            capacity = temp.capacity;
            size = temp.size;

            currIndex = new elmtype[capacity];
            for(int x = 0; x < capacity; x++){
                currIndex[x] = temp.currIndex[x];
            }

            return *this;
        }


//destructor
        ~CDA(){
            delete []currIndex;
        }
//reference for out of bounds
        elmtype& operator[](int i){

            if( i < 0 || i > capacity ) {
                cout << "Index out of bounds" <<endl; 
                return currIndex[0];
            }

            return currIndex[( i + frontIndex )% capacity];
        }

        //adding to the front of the array
    void AddFront(elmtype v){
            if(size == capacity){
                elmtype *temp = new elmtype[capacity*2];

                for(int x = 0; x < capacity; x++){
                    temp[x] = currIndex[(frontIndex + x )% capacity];
                }

                delete []currIndex;
                currIndex = temp;
                frontIndex = 0;
                lastIndex = size-1;
                capacity*=2;
            }
            size++;
            currIndex[(frontIndex-1+capacity)%capacity] = v;
            frontIndex = (frontIndex-1+capacity)%capacity;

        }

//adding to the end of the array
        void AddEnd(elmtype v){

            // resize
            if(size == capacity){
                elmtype *temp = new elmtype[capacity*2];

                for(int x = 0; x < capacity; x++){
                    temp[x] = currIndex[(frontIndex + x )% capacity];
                }

                delete []currIndex;
                currIndex = temp;
                frontIndex = 0;
                lastIndex = size-1;
                capacity *= 2;
                }
            size++;
            lastIndex = (lastIndex + 1) % capacity;
            currIndex[lastIndex] = v;
        }

//deleting from the end
        void DelEnd(){
            if(size <= capacity/4){
                elmtype *temp = new elmtype[capacity/2];

                for(int x = 0; x < capacity/2; x++){
                    temp[x] = currIndex[(frontIndex + x )% capacity];
                }

                delete []currIndex;
                currIndex = temp;
                frontIndex = 0;
                lastIndex = size-1;
                capacity/=2;
            }
            size--;
            lastIndex--;
        }
//deleting from the front
        void DelFront(){
            if(size <= capacity/4){
                elmtype *temp = new elmtype[capacity/2];

                for(int x = 0; x < capacity/2; x++){
                    temp[x] = currIndex[(frontIndex + x )% capacity];
                }

                delete []currIndex;
                currIndex = temp;
                frontIndex = 0;
                lastIndex = size-1;
                capacity/=2;
            }
            size--;
            frontIndex++;
        }
//returning size
        int Length(){
            return size;
        }
//returning capacity
        int Capacity(){
            return capacity;
        }





     //quickselect algorithm, working with a random pivot here.

        elmtype Select(int k){
            srand ( time(NULL) );
            elmtype pivot = currIndex[rand() % size];

            CDA<elmtype> a;
            CDA<elmtype> b;
            CDA<elmtype> c;
            for(int x = 0 ; x< size; x++){
                if (currIndex[(frontIndex + x) % capacity] < pivot) 
                    a.AddEnd(currIndex[(frontIndex + x) % capacity]); 
                else if(currIndex[(frontIndex + x) % capacity]==pivot){
                    b.AddEnd(currIndex[(frontIndex + x) % capacity]);
                } 
                else{
                    c.AddEnd(currIndex[(frontIndex + x) % capacity]);
                } 
            }
            
            if(k<=(a.Length()))
                return a.Select(k);
            else if(k<=(a.Length()+b.Length())){
                return pivot;
            }
            else
                return c.Select(k-a.Length()-b.Length());
            
        }   



//merge function that is a helper function for mergesort takes care of storing elements of both left and right subarrays. then merges them together to have one CDA

void merge(int arr[], int const left, int const mid, int const right) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
  
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
  
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = arr[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = arr[mid + 1 + j];
  
    auto indexOfSubArrayOne = 0, // Initial index of first sub-currIndex
        indexOfSubArrayTwo = 0; // Initial index of second sub-currIndex
    int indexOfMergedArray = left; // Initial index of merged currIndex
  
    // Merge the temp arrays back into currIndex[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}
  
//recursive mergesort 
void mergeSort(int arr[], int const beginning, int const lastIndex) {
    if (beginning >= lastIndex)
        return; // Returns recursively
  
    auto mid = beginning + (lastIndex - beginning) / 2;
    mergeSort(arr, beginning, mid);
    mergeSort(arr, mid + 1, lastIndex);
    merge(arr, beginning, mid, lastIndex);
}
//sort algorithm which uses mergesort also
void Sort(){

            elmtype *temp = new elmtype[capacity];

            for(int x = 0; x < capacity; x++){
                temp[x] = currIndex[(frontIndex + x )% capacity];
            }

            delete []currIndex;
            currIndex = temp;
            frontIndex = 0;
            lastIndex = size-1;

            mergeSort(currIndex, 0, lastIndex);
        }



        //search algorithm to search for the index we are interested in
        int Search(elmtype b){ 
            for (int x = 0; x < capacity; x++){

                if (currIndex[(x+frontIndex)%capacity] == b) return x;
            }   
            return -1;
        }
//searching through both subarays
        int BinSearch(elmtype b){   
           return BinSearchHelper(currIndex,frontIndex,lastIndex, b);
        } 
//helper function for binsearch
        int BinSearchHelper(int arr[], int low, int high, int x) {
            int mid;
            if (x <= arr[low])
                return low;
            if (x > arr[high])
                return ~size;

            mid = (low + high) / 2; 

            if (arr[mid] == x)
                return mid;

            else if (arr[mid] < x) {
                if (mid + 1 <= high && x <= arr[mid + 1])
                    return mid + 1;
                else
                    return BinSearchHelper(arr, mid + 1, high, x);
            } 
            else {
                if (mid - 1 >= low && x > arr[mid - 1])
                    return ~mid;
                else
                return BinSearchHelper(arr, low, mid - 1, x);
            }
        }

};
