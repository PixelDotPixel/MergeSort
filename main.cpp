#include <iostream>
#include <ctime>
#include "Person.h"

using namespace std;


int main()
{
    int bound = -1; clock_t startT; clock_t endT;
    cout << "How many names would you like to index?" << endl;
    cin >> bound;

    //Section 1, readBound
    cout << "---------------------------Section 1---------------------------" << endl;
    Person* mList = new Person[bound];
    mList = readBound(bound);


    //Section 2, countLastName timed
    cout << "---------------------------Section 2---------------------------" << endl;

    //Clocks the last countLastname
    startT = clock();
    for(int i = 0; i < 10000; i++){
        countLastName("Mertz", mList, bound);}
    endT = clock();
    double seconds = static_cast<double>(endT - startT)/ (CLOCKS_PER_SEC * 10000);
    cout << "The time it took to run " << bound << " elements was: " << seconds << endl;

    //actually prints the countlastname function
    cout << "There are " << countLastName("Mertz", mList, bound) << " Mertz's in the list" << endl;

    //Section 3, partialZipSort
    cout << "---------------------------Section 3---------------------------" << endl;
    partialZipSort(mList, 2, 7);
    for(int i = 0; i < 10; i++){
        cout << mList[i].last << ", " << mList[i].first << ", " << mList[i].zipCode << endl;
    }


    //Section 4, nameSort, timed (takes some time to run all 100,000 names)
    cout << "---------------------------Section 4---------------------------" << endl;

    //clocks the process
    startT = clock();
    for(int i = 0; i < 100; i++){
        nameSort(mList, bound);
    }
    endT = clock();
    seconds = static_cast<double>(endT - startT)/ (CLOCKS_PER_SEC * 100);
    cout << "The time it took to run " << bound << " elements was: " << seconds << endl;

    // printst the first 10 elements to check
    for(int i = 0; i < 10; i++){
        cout << mList[i].last << ", " << mList[i].first << ", " << mList[i].zipCode << endl;
    }



    //Section 5, binaryFind(First/Last)ByLastName
    cout << "---------------------------Section 5---------------------------" << endl;
    cout << "Abbott First index: " << binaryFindFirstByLastName("Abbott", mList, bound) << ", Abbott last index: " << binaryFindLastByLastName("Abbott", mList, bound) << endl;
    cout << "Zulauf First index: " << binaryFindFirstByLastName("Zulauf", mList, bound) << ", Zulauf last index: " << binaryFindLastByLastName("Zulauf", mList, bound) << endl;


    //Section 6, countLastNameInSorted, timed
    cout << "---------------------------Section 6---------------------------" << endl;

    //Actually prints the function, and number of names
    cout << "There are " << countLastNameInSorted("Mertz", mList, bound) << " Mertz's in this list" << endl;

    //clocks the process
    startT = clock();
    for(int i = 0; i < 10000; i++){
        countLastNameInSorted("Mertz", mList, bound);}
    endT = clock();

    seconds = static_cast<double>(endT - startT)/ (CLOCKS_PER_SEC * 10000);
    cout << "The time it took to run " << bound << " elements was: " << seconds << endl;

    delete [] mList;

    return 0;
}

