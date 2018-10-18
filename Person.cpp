//----------------------------------------------------------
// CS260 Assignment 1 Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may not be republished without approval.
//----------------------------------------------------------
#include "Person.h"



bool operator==(const Person& p1, const Person& p2){
    if(p1.kNum == p2.kNum)
        return true;
    else
        return false;
}

//For merge sort (made a mistake and thought i needed to override to handle strings)
bool operator>=(const Person p1, const Person p2){
    int i = 0;
    if((p1.last == p2.last) && (p1.first == p2.first)){
        return true;
    }

    if(p1.last != p2.last){
        if(p1.last > p2.last){
            return true;
        }
        else
            return false;
    }
    else if(p1.last == p2.last){
        if(p1.first > p2.first){
            return true;
        }
        else
            return false;
    }
}

//Section 1, takes in a bound and reads from a text file. Starts at index 0 goes to the upper bound
Person* readBound(int bound){
    Person* List = new Person[bound];
    ifstream readFile;
    string shuttleLine, shuttle;
    int shuttleNum;
    readFile.open("people.txt");
    if (!readFile){
        cout << "file was not found";
    }
    for(int i = 0; i < bound; i++){
        int k = 0;
        getline(readFile, shuttleLine);
        for(int j = 0; j < 4; j++){
            while((shuttleLine.at(k) != ',') && (j < 3)){
                shuttle += shuttleLine.at(k);
                k++;
            }
            if(j == 3){
                shuttleLine.erase(0, k);
                shuttleNum = std::stoi(shuttleLine);
            }

            switch (j) {
            case 0: List[i].kNum = shuttle;
                break;
            case 1: List[i].last = shuttle;
                break;
            case 2: List[i].first = shuttle;
                break;
            case 3: List[i].zipCode = shuttleNum;
                break;
            }
            k++;
            shuttle = "";
        }

    }
    return List;
}

//Section 2, takes in a last name to count how many duplicates of the last name are in the list
int countLastName(const std::string& lastName, const Person* array, int size) {
    int count = 0;
    for(int i = 0; i < size; i++){
        if(array[i].last == lastName)
           count++;
    }
    return count;
}

//Section 3, takes in a lower bound and upper bound to sort by zip
void partialZipSort(Person* array, int start, int end) {
    Person shuttle1;
    int size = end-start;
    Person* tempArray = new Person[size];
    tempArray = &array[start];

    for(int i = 0; i < size; i++){
        int j = i;
        bool swapped = false;

        while((tempArray[j].zipCode < tempArray[j-1].zipCode) && (j > 0)){
            swapped = true;
            shuttle1 = tempArray[j];
            tempArray[j] = tempArray[j-1];
            tempArray[j-1] = shuttle1;
            j--;
        }
    }

    for(int i = start; i < end; i++){
        array[i] = tempArray[i-start];
    }

    tempArray = NULL;
    delete[] tempArray;
}

//Section 4, Takes in the array and its size. It uses the variables taken in to call its helper functions and sort the array.
void nameSort(Person* array, int size) {
    Person* sArray = new Person[size];
    mergeInternal(array, sArray, 0, size-1);
    delete [] sArray;

}

//Section 4, Part 1. Helper function (Recursive)
void mergeInternal(Person* array, Person* tArray,  int low, int high){
    if(low >= high){
        return;
    }
    int middle = (low+high)/2;
    mergeInternal(array, tArray, low, middle);
    mergeInternal(array, tArray, middle+1, high);

    merge(array, low, high, middle, tArray);

}
//Section 4, Part 2. Helper function to mergeInternal
void merge(Person* array, int low, int high, int mid, Person* tArray){
    int i = low, j = low, k = mid+1;
    while((j <= mid) && (k <= high)){
        if(array[k] >= array[j]){
            tArray[i++] = array[j++];
        }
        else{
            tArray[i++] = array[k++];
        }
    }
    while(i <= high){
        if(k > high){
            tArray[i++] = array[j++];
        }
        else if(j > mid){
            tArray[i++] = array[k++];
        }
    }
    for(int i = low; i <= high; i++){
            array[i] = tArray[i];
        }


}

//Section 5, uses binary search to find the first instance of a last name in the array, and returns its index
int binaryFindFirstByLastName(const std::string& value, const Person* array, int size) {
    int low = 0; int middle = size-1; int high = size; int incriment = size-1;

    while((array[middle].last != value) || ((array[middle].last == value) && (array[middle - 1].last == value))){
        if(array[middle].last > value){
            middle = middle - incriment;
            incriment = (incriment + 1)/2;
        }

        else if(array[middle].last < value){
            middle = middle + incriment;
            incriment = (incriment + 1)/2;
            if(middle > size)
                return -1;
        }

        else if(value == array[middle-1].last){
            middle = middle - incriment;
            incriment = (incriment + 1)/2;

        }
        if(array[0].last == value){
            return 0;
        }
        if(incriment == 0){
            return middle;
        }

    }

    return middle;
}

//Section 5, part 2, uses binary search to find the last instance of a last name in the array, and returns its index
int binaryFindLastByLastName(const std::string& value, const Person* array, int size) {
        int low = 0; int middle = size-1; int high = size; int incriment = size-1;

        while((array[middle].last != value) || ((array[middle].last == value) && (array[middle + 1].last == value))){
            if(array[middle].last > value){
                middle = middle - incriment;
                incriment = (incriment + 1)/2;
            }

            else if(array[middle].last < value){
                middle = middle + incriment;
                incriment = (incriment + 1)/2;
                if(middle > size)
                    return -1;
            }

            else if(value == array[middle + 1].last){
                middle = middle + incriment;
                incriment = (incriment + 1)/2;

            }
            if(array[size-1].last == value){
                return size-1;
            }
            if(incriment == 0){
                return middle - 1;
            }
    }


    return middle;

}

//Section 6, calls on binary find last and first to find the range that a last name exists, then returns that number + 1
int countLastNameInSorted(std::string lastName, const Person* array, int size) {
    return binaryFindLastByLastName(lastName, array, size) - binaryFindFirstByLastName(lastName, array, size) + 1;
}






