#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

objPosArrayList::objPosArrayList()
{   
    arrayCapacity = ARRAY_MAX_CAP; //Sets max capacity of array (200) - SP

    aList = new objPos[ARRAY_MAX_CAP]; // DAM for array

    listSize = 0;
}

objPosArrayList::~objPosArrayList() // Destructor for objPosArrayList class - SP
{
    delete[] aList; //Frees allocated memory
}

int objPosArrayList::getSize() const // Returns the current size of the array list - SP
{
    return listSize; 
}

void objPosArrayList::insertHead(objPos thisPos) // Inserts an element at the "head" of the array - SP 
{
    int i;

    for(i = listSize; i > 0; i--)
    {
        aList[i] = aList[i-1]; //Shifts elements to the right 

        if(listSize == arrayCapacity) 
        {
            break; //Breaks if the array is at max capacity 
        }    
    }

    aList[0] = thisPos;        
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos) // Inserts an element at the "tail" of the array - SP 
{
    if (listSize < arrayCapacity) 
    {
        aList[listSize] = thisPos;        
        listSize++;

    }

}

void objPosArrayList::removeHead() // Removes an element at the "head" of the array - SP 
{
    int i; 

    if (listSize > 0) 
    {
        for (i = 0; i < listSize - 1; i++) 
        { 
            aList[i] = aList[i + 1];
        }
        listSize--;
    }
}

void objPosArrayList::removeTail()  // Removes an element at the "tail" of the array - SP 
{
    if(listSize == 0){}

    else
    {
        listSize--;
    }
}

objPos objPosArrayList::getHeadElement() const // Returns the element at the head of the array - SP 
{
    return aList [0];
}

objPos objPosArrayList::getTailElement() const // Returns the element at the head of the tail - SP
{
    return aList [listSize - 1];
}

objPos objPosArrayList::getElement(int index) const // Returns the element at a specified index value in the array. - SP
{
    return aList [index];
}