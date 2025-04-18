#include <iostream>
#include <vector>
#include <string>

struct node {
    int info;
    node* nextlink;
};

template<typename Type>
class linkedListDataType
{
    static void divideAt(linkedListDataType<Type> linked_list, int postion);


    };

template<typename Type>
void linkedListDataType<Type>::divideAt(linkedListDataType<Type> linked_list, int postion) {
}

////Divide the list at the node with the info item into two
//sublists.
//Postcondition: first and last point to the first and
// last nodes of the first sublist.
// secondList.first and secondList.last
// point to the first and last nodes of the
// second sublist.
//unorderedLinkedList<int> myList;
//unorderedLinkedList<int> otherList;

//divides myList into two sublists: myList points to the list with the
//elements 34 65,and otherList points to the sublist with the elements
//18 39 27 89 12.
