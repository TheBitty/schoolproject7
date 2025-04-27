//This program tests various operation of a linked list
//45 67 23 89 -999

#include <iostream> 
#include <cassert> 

using namespace std;

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type>* link;
};

template <class Type>
class circularLinkedList
{
public:
	//Overloads the assignment operator.
	const circularLinkedList<Type>& operator=(const circularLinkedList<Type>& otherList)
	{
		if (this != &otherList) //avoid self-copy
		{
			copyList(otherList);
		}//end else

		return *this;
	}

	//Initializes the list to an empty state.
	//Postcondition: first = NULL, last = NULL,
	//                count = 0
	void initializeList()
	{
		destroyList();
	}

	//Function to determine whether the list is empty. 
	//Postcondition: Returns true if the list is empty; otherwise, returns false.
	bool isEmptyList()
	{
		return (first == NULL);
	}


	void print() const
	{
		nodeType<Type>* current; //pointer to traverse the list

		if (first != NULL)
		{
			current = first->link;

			while (current != first) //while more data to print
			{
				cout << current->info << " ";
				current = current->link;
			}

			cout << first->info << " ";
		}
		else
			cout << "List is empty";
	}

	//Function to return the number of nodes in the list.
	//Postcondition: The value of count is returned.
	int length()
	{
		return count;
	}


	//Function to delete all the nodes from the list.
	//Postcondition: first = NULL, last = NULL, 
	//               count = 0
	void destroyList()
	{
		nodeType<Type>* temp;
		nodeType<Type>* current = NULL;

		if (first != NULL)
		{
			current = first->link;
			first->link = NULL;
		}

		while (current != NULL)
		{
			temp = current;
			current = current->link;
			delete temp;
		}

		first = NULL;	//initialize last to NULL; first has already
		//been set to NULL by the while loop
		count = 0;
	}


	//Function to return the first element of the list.
	//Precondition: The list must exist and must not be empty.
	//Postcondition: If the list is empty, then the program terminates; otherwise, the first element of the list is returned.
	Type front()
	{
		assert(first != NULL);
		return first->link->info; //return the info of the first node	
	}


	//Function to return the last element of the list.
	//Precondition: The list must exist and must not be empty.
	//Postcondition: If the list is empty, then the program terminates; otherwise, the last element of the list is returned.
	Type back()
	{
		assert(first != NULL);
		return first->info; //return the info of the first node	
	}


	//Function to determine whether searchItem is in the list.		
	//Postcondition: Returns true if searchItem is found in the list; otherwise, it returns false.
	bool search(const Type& searchItem)
	{
		nodeType<Type>* current; //pointer to traverse the list
		bool found = false;

		if (first != NULL)
		{
			current = first->link;

			while (current != first && !found)
			{
				if (current->info >= searchItem)
					found = true;
				else
					current = current->link;

				found = (current->info == searchItem);
			}
		}

		return found;
	}


	void insertNode(const Type& newitem)
	{
		nodeType<Type>* current; //pointer to traverse the list
		nodeType<Type>* trailCurrent; //pointer just before current
		nodeType<Type>* newNode;  //pointer to create a node

		bool  found;

		newNode = new nodeType<Type>; //create the node

		newNode->info = newitem;   //store newitem in the node
		newNode->link = NULL;      //set the link field of the node
		//to NULL

		if (first == NULL)  //Case 1	e.g., 3
		{
			first = newNode;
			first->link = newNode;
			count++;
		}
		else
		{
			if (newitem >= first->info)//e.g., 25 > 3
			{
				newNode->link = first->link;
				first->link = newNode;
				first = newNode;
			}
			else
			{
				trailCurrent = first; //e.g., 1 < 3 
				current = first->link;
				found = false;

				while (current != first && !found)
					if (current->info >= newitem)
						found = true;
					else
					{
						trailCurrent = current;
						current = current->link;
					}

				trailCurrent->link = newNode;
				newNode->link = current;
			}

			count++;
		}//end else
	}

	//Function to delete deleteItem from the list.
	//Postcondition: If found, the node containing deleteItem is deleted from the list, first points to the first		
	//                node, and last points to the last node of the updated list. 
	void deleteNode(const Type& deleteItem)
	{
		nodeType<Type>* current; //pointer to traverse the list
		nodeType<Type>* trailCurrent; //pointer just before current
		bool found;

		if (first == NULL)    //Case 1; list is empty. 
			cout << "Can not delete from an empty list." << endl;
		else
		{
			found = false;
			trailCurrent = first;
			current = first->link;

			while (current != first && !found)
				if (current->info >= deleteItem)
					found = true;
				else
				{
					trailCurrent = current;
					current = current->link;
				}

			if (current == first)
			{
				if (first->info == deleteItem)
				{
					if (first == first->link)
						first = NULL;
					else
					{
						trailCurrent->link = current->link;
						first = trailCurrent;
					}
					delete current;

					count--;
				}
				else
					cout << "The item to be deleted is not in the list." << endl;
			}
			else
				if (current->info == deleteItem)
				{
					trailCurrent->link = current->link;
					count--;
					delete current;
				}
				else
					cout << "Item to be deleted is not in the list." << endl;
		} //end else
	}

	//Function to divide the list at the node with the info item into two sublists
	//Postcondition: first and last point to the first and last nodes of the first sublist.
	//               secondList.first and secondList.last point to the first and last nodes of the
	//               second sublist.
	void divideAt(circularLinkedList<Type>& secondList, const Type& item)
	{
		// Clear the second list first
		secondList.destroyList();

		// Handle empty list case
		if (first == NULL)
		{
			cout << "Cannot divide an empty list." << endl;
			return;
		}

		// Find the node with the item
		nodeType<Type>* current = first->link;
		nodeType<Type>* previous = first;
		bool found = false;

		// Search for the item
		while (current != first && !found)
		{
			if (current->info == item)
				found = true;
			else
			{
				previous = current;
				current = current->link;
			}
		}

		// If item not found, also check the last node (first)
		if (!found && first->info == item)
		{
			found = true;
			current = first;
			// Find the node before first
			previous = first->link;
			while (previous->link != first)
				previous = previous->link;
		}

		// If item not found at all
		if (!found)
		{
			cout << "Item not found in the list." << endl;
			return;
		}

		// Special case: If there's only one node in the list
		if (first->link == first)
		{
			// Create a new node for secondList
			secondList.first = new nodeType<Type>;
			secondList.first->info = first->info;
			secondList.first->link = secondList.first; // Point to itself
			secondList.count = 1;

			// Empty first list
			first = NULL;
			count = 0;
			return;
		}

		// Special case: Item is in the first node of the list
		if (current == first->link)
		{
			// Create a new list for secondList that contains all original nodes
			nodeType<Type>* newNode = new nodeType<Type>;
			newNode->info = first->info;
			newNode->link = first->link;
			secondList.first = newNode;
			secondList.count = count;

			// Empty first list
			first = NULL;
			count = 0;
			return;
		}

		// Special case: Item is in the last node (first)
		if (current == first)
		{
			// Create a new node for secondList with just the last item
			secondList.first = new nodeType<Type>;
			secondList.first->info = first->info;
			secondList.first->link = secondList.first; // Point to itself
			secondList.count = 1;

			// Update first list to exclude the last node
			previous->link = first->link;
			first = previous;
			count--;
			return;
		}

		// Regular case: Item is in the middle of the list
		// Count nodes in the original list
		int totalCount = 0;
		nodeType<Type>* temp = first->link;
		do {
			totalCount++;
			temp = temp->link;
		} while (temp != first->link);

		// Count nodes before the found node
		int firstListCount = 0;
		temp = first->link;
		while (temp != current) {
			firstListCount++;
			temp = temp->link;
		}

		// Create new nodes for the second list
		nodeType<Type>* newFirst = NULL;
		nodeType<Type>* newLast = NULL;
		temp = current;

		do {
			nodeType<Type>* newNode = new nodeType<Type>;
			newNode->info = temp->info;

			if (newFirst == NULL) {
				newFirst = newNode;
				newLast = newNode;
				newNode->link = newNode; // Point to itself initially
			}
			else {
				newLast->link = newNode;
				newLast = newNode;
				newNode->link = newFirst; // Complete the circle
			}

			temp = temp->link;
		} while (temp != first->link);

		// Update second list
		secondList.first = newLast; // Remember, first points to the last node
		secondList.count = totalCount - firstListCount;

		// Update first list
		previous->link = first;
		first = previous;
		count = firstListCount;
	}


	//Default constructor
	//Initializes the list to an empty state. 		
	//Postcondition: first = NULL, last = NULL, 
	//               count = 0 
	circularLinkedList()
	{
		first = NULL;
		count = 0;
	}


	//Copy constructor
	circularLinkedList(const circularLinkedList<Type>& otherList)
	{
		first = NULL;
		copyList(otherList);
	}


	//Destructor
	//Deletes all the nodes from the list.
	//Postcondition: The list object is destroyed. 
	~circularLinkedList()
	{
		destroyList();
	}


protected:
	int count;		//variable to store the number of elements in the list
	nodeType<Type>* first; //pointer to the first node of the list
	nodeType<Type>* last;  //pointer to the last node of the list 
private:
	//Function to make a copy of otherList.
	//Postcondition: A copy of otherList is created and assigned to this list.
	void copyList(const circularLinkedList<Type>& otherList)
	{
		nodeType<Type>* newNode;
		nodeType<Type>* current;
		nodeType<Type>* tempFirst;

		if (first != NULL)
			destroyList();

		if (otherList.first == NULL)
		{
			first = NULL;
			count = 0;
		}
		else
		{
			current = otherList.first->link;  //current points to the 
			//list to be copied
			count = otherList.count;

			//copy the first node
			tempFirst = new nodeType<Type>;  //create the node

			tempFirst->info = current->info; //copy the info
			last = tempFirst;    		     //make last point to the 
			//first node
			current = current->link;     //make current point to the 
			//next node

			//copy the remaining list
			while (current != otherList.first)
			{
				newNode = new nodeType<Type>;  //create a node
				newNode->info = current->info;
				last->link = newNode;
				last = newNode;

				current = current->link;

			}//end while

			if (tempFirst == last)
			{
				first = tempFirst;
				first->link = first;
			}
			else
			{
				newNode = new nodeType<Type>;  //create a node
				newNode->info = current->info;
				last->link = newNode;
				first = newNode;
				first->link = tempFirst;
			}

		}//end else
	}
};

int main()
{
	circularLinkedList<int> list1, list2, testList, secondList;
	int num;

	cout << "Enter number ending with -999" << endl;
	cin >> num;

	while (num != -999)
	{
		list1.insertNode(num);
		cin >> num;
	}

	cout << endl;

	cout << "List 1: ";
	list1.print();
	cout << endl;

	cout << "Length List 1: " << list1.length() << endl;

	// Test divideAt function
	testList.insertNode(12);
	testList.insertNode(89);
	testList.insertNode(27);
	testList.insertNode(39);
	testList.insertNode(18);
	testList.insertNode(65);
	testList.insertNode(34);

	cout << "Test List: ";
	testList.print();
	cout << endl;

	int itemToDivideAt;
	cout << "Enter item to divide at: ";
	cin >> itemToDivideAt;

	testList.divideAt(secondList, itemToDivideAt);

	cout << "After dividing at " << itemToDivideAt << ":" << endl;
	cout << "First part: ";
	testList.print();
	cout << endl;

	cout << "Second part: ";
	secondList.print();
	cout << endl;

	// Continue with original test code
	cout << "Enter the number to be searched:  ";
	cin >> num;
	cout << endl;

	if (list1.search(num))
		cout << num << " found in the list" << endl;
	else
		cout << num << " not in the list" << endl;

	cout << "Enter the number to be deleted: ";
	cin >> num;
	cout << endl;

	list1.deleteNode(num);

	cout << "After deleting the node, "
		<< "List 1: ";
	list1.print();
	cout << endl;

	cout << "Length List 1: " << list1.length() << endl;

	list2 = list1;

	cout << "List 2: ";
	list2.print();
	cout << endl;

	cout << "Length List 2: " << list2.length() << endl;

	cout << "List 1: ";
	list1.print();
	cout << endl;

	return 0;
}
