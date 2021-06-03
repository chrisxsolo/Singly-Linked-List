//	LinkedBag340.cpp
//	Created by: CSC340

/*
===>					<===
===>  PLEASE ADD CODE	<===
===>					<===
*/

#include "LinkedBag.h"
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include <iostream>
//#include "Include.h"
//#include "LinkedBagClient340.cpp"
using namespace std;


template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340(){
    string removeContent;
    //initialized and declares the second node pointer to the current node pointer
    Node<ItemType> *entryNodePtr = headPtr->getNext();

    //get the second item
    removeContent = entryNodePtr->getItem();
    
    //remove the second item
    return remove(removeContent);
};

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType & stringObeject){
    //creating the current node from the start of the nodes
    Node<ItemType> *entryNodePtr=headPtr;
    //iterates through the nodes until it reaches the end which is null
    while(entryNodePtr->getNext() != nullptr ){
        //setting the current node to the last node
        entryNodePtr = entryNodePtr->getNext();
    }

    //declaring a new pointer
    Node<ItemType> *addNewNode = new Node<ItemType>();
    //setting the new pointer data to the newEntry being passed in
    addNewNode->setItem(stringObeject);
    //setting the the null value to the new node with the data that was passd
    entryNodePtr->setNext(addNewNode);
        
    //Incrementing the item count in the bag
    itemCount++;
    
    return true;
};


template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const{
    int count =0;

    //creating a current pointer
    Node<ItemType> *currentPtr =headPtr;
    //iterating through the linked list
    while(currentPtr!= nullptr){
        //increasing the amount of times if iterates from each node
        count++;
        //setting the current node to the next node and then repeating the loop
        currentPtr = currentPtr->getNext();
    }
    //resetting the currenptr
    currentPtr = headPtr;
    //returning the amount of times it jumped from node to node until it reached null
    return count;
};


template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const{

    //establishing a current pointer at the beginning of the linked list
    Node<ItemType> *currentPtr = headPtr;

    //calls the recursive method inside this method(recursion)
    return getCurrentSize340RecursiveHelper(currentPtr);

};

//This method gets called from the getCurrentSize340Recursive method
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* currentPtr) const {

    //Once the current pointer reaches the end it will return a non-edited value
    if (currentPtr == nullptr) {
        //resetting the the current ptr to point to the head
        currentPtr = headPtr;
        return 0;
    } else {
        //adds 1 everytime it iterates through the linked list through recursion starting at the head
        currentPtr = currentPtr->getNext();
        return  1 +  getCurrentSize340RecursiveHelper(currentPtr);
    }
}



template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const{
    //Creating a current pointer that exists after the first time the method closes
    static Node<ItemType>* currentPtr = headPtr;
    
    
    //makes the current pointer point to the next node
    currentPtr = currentPtr->getNext();

    //If the current pointer is null it will return as is
    //base condition
    if (currentPtr == nullptr){
        //resetting currentPtr before it returns
        currentPtr = headPtr;
        return 0;
    }else{
    
        //Adds one after each iteration of the recursion
        return 1 + getCurrentSize340RecursiveNoHelper() ;
    }

}
template<typename ItemType>

int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& stringObject) const{

    //starting from the start of the linked list
    Node <ItemType> *currentPtr =headPtr;
    
    //Calling the helper function passing the pointer and string to get the frequency of the string object
    return (getFrequencyOf340RecursiveHelper(currentPtr, stringObject));

};


template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType &stringObject) const{

        //creating node pointer that starts at the head
        static Node<ItemType> *currentPtr = headPtr;
         //Keep track how many times it finds a match to the string object
        int frequency = 0;

        //Once it reaches the end of the linkedlist it sets the pointer to the start of linked list
        //Base condition
        if (currentPtr == nullptr){
    
           currentPtr = headPtr;
            return 0;
        }
        //if the current node data is equal to the object passed in it increases count of frequency
        else if (currentPtr->getItem() == stringObject){
            //Setting the current node to the next node
            currentPtr = currentPtr->getNext();
             frequency++;
            //recursively starts the function again
            return frequency + getFrequencyOf340RecursiveNoHelper(stringObject);
            }else{
            //moves the pointer to the next node and calls the method again
            currentPtr = currentPtr->getNext();
            return frequency + getFrequencyOf340RecursiveNoHelper(stringObject);
        }
};


template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>* currentPtr, const ItemType& stringObject) const {
    //Keep track how many times it finds a match to the string object
    int frequency =0;
    //If the current pointer is null then it will return the value
    if (currentPtr == nullptr) {
        //resetting headptr
       // currentPtr = headPtr;
        return 0;
    }
    //If the data of the node is equal to the string object then it will add 1 and recurse
    if (currentPtr->getItem() == stringObject) {
        frequency++;
        return frequency  + getFrequencyOf340RecursiveHelper(currentPtr->getNext(), stringObject);
    } else {
        //if the data of the node does not equal to the string object that is being passed in then it will recurse
        //until it reaches a pointer that is null
        return getFrequencyOf340RecursiveHelper(currentPtr->getNext(), stringObject);
    }
}

template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340(){
    int counter=0;
    //creating a return variable of ItemType type
    ItemType content;

    //Makes a random number each time the program runs
    srand(time(0));

    //generates a random number based off of how many items there are
    int randomNumber = rand() % itemCount;

    //Creating a currentPtr of ItemType at the start of the linkedbag
    Node<ItemType> *currentPtr = headPtr;

    //traverses through the linkedbag until it hits the random number index
    while(counter < randomNumber){
        currentPtr = currentPtr->getNext();
        counter++;
    }
    
    //grabbing the data of the current node and storing it in content to return
    content = currentPtr->getItem();

    //setting the currentPtr data to the data in the head node
    currentPtr->setItem(headPtr->getItem());

    //creating a pointer to set to delete the head pointer
    Node<ItemType> *deleteHeadPtr = headPtr;

    //making a new head pointer which is the next node
    headPtr = headPtr->getNext();
    
    //setting the pointer to point to null to make it not dangle
    deleteHeadPtr->setNext(nullptr);

    delete deleteHeadPtr;

    //Making the object null
    deleteHeadPtr =  NULL;

    //updating the item count
    itemCount--;

    //returning the item that is removed
    return content;

};

