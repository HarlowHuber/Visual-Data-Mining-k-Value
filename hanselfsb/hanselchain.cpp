/* **********************************************************************
   *  UPDATE 3/28/2022 - Harlow Huber
   *	The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
   *	This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
   *	put my changes below. All functionality will remain the same, or exceedingly similar.
   *	All previous code comments will remain, for now, as a reference. 
   *
   *  BUG FIXES 3/28/2022 - HARLOW HUBER
   *	in display(), "ofstream" changed to "std::ofstream"
   *	displayQuestions() has code that outputs vector data to a "NULL" "ofstream"
   *		I assume this code is unfinished, so far now it is commented out because I do not know what it is supposed to do exactly
   *
   *  FILE        : hanselchain.cpp
   *  NAME        : Hansel Chain Implementation
   *  OWNER       : Jay Summet     (only owner can make changes)
   *  VERSION     : 1.1            (major change.minor change)
   **
   **	I have seen many comments in my life, but this one is the less efficient of all !
   ** next time you program something try to think first of your code and next of your
   ** property, it will prevent somebody (me for example) to have to debug your own stuff
   ** and reprogram the major part !
   **		Florian DELIZY (poor people in charge to use that "thing")
   **
   *
   *  CHANGE LOG  :
   *     VERSION #  DATE      WHO COMMENT
   *     ---------------------------------------------------------------
   *     0.1.0      11.21.98  JWS Created file
   *     0.2.0      11.22.98  JWS Fixed seg fault for reading chains
   *                                 of length 1
   *     1.0.0      11.23.98  ALL Initial Client Release
   *     1.1.0      11.28.98  SAF Added display to a file
   *
   *
   *  SYSTEM      : ANSI C++ - should build on everything.
   *
   *  DESCRIPTION : N/A
   *
   *  INCLUDES    : Hansel Chain class (hanselchain.h)
   *                I/O Stream class (iostream.h)
   *
   *  TODO        : N/A
   *
   *************************************************************************/

#include "pch.h"
#include "hanselchain.h"

// Purpose: Creates an empty Hansel Chain
// Input:	N/A
// Output:	N/A
// Returns:	N/A
// Notes:	Sets length to 0
HanselChain::HanselChain()
{
	length = 0;
	VectorListStart = NULL;
	VectorListEnd = NULL;

}; // end HanselChain::HanselChain()

HanselChain::~HanselChain()
{
	vectorNode* TempPtr;
	vectorNode* DeletePtr;

	TempPtr = VectorListStart;
	while (TempPtr != NULL)
	{
		DeletePtr = TempPtr;
		TempPtr = TempPtr->nextNode;

		// Zap both the vector and the node.
		delete DeletePtr->data;
		delete DeletePtr;
	}
} // End HanselChain::~HanselChain()

HanselChain* HanselChain::generateNext(int First)
{
	vectorNode* TempPtr;
	HanselChain* NewChain = new HanselChain();
	Vector* NewVector;

	TempPtr = VectorListStart;

	// Do this for each vector.
	while (TempPtr != NULL)
	{
		// create a new vector with one more elment than the current vector.
		NewVector = new Vector(TempPtr->data->getSize() + 1);

		// Set the first bit if we are generating OneC, otherwise leave at zero.
		if (First == 1)
			NewVector->set_kValue(1, 1);

		// Copy the remaining bits over.
		for (int i = 2; i <= NewVector->getSize(); i++)
			if (TempPtr->data->retrieve_kValue(i - 1) == 1)
				NewVector->set_kValue(i, 1);

		// Add the new Vector to our new Chain.
		NewChain->addVector(NewVector);

		TempPtr = TempPtr->nextNode; // Move to next node if it exists.
	} // end while 

	return(NewChain);
} //end HanselChain::GenerateNext(int)

// Purpose: Displays the chain to a file
// Input:	pointer to file stream
// Output:	N/A
// Returns:	N/A
// Notes:	N/A
void HanselChain::display(std::ofstream& outputFile) const {
	vectorNode* TempPtr;

	TempPtr = VectorListStart;
	while (TempPtr != NULL) {
		TempPtr->data->display(outputFile);	//display the vector in that node
		TempPtr = TempPtr->nextNode;	// move to next node
	}
} // End HanselChain::display

// Purpose: Adds a vector to the end of the Chain
// Input:	vector to add to end of chain
// Output:	N/A
// Returns:	N/A
// Notes:	Increments length
void HanselChain::addVector(Vector* endVector)
{
	vectorNode* newNodePtr;
	newNodePtr = new vectorNode;
	newNodePtr->nextNode = NULL;
	newNodePtr->data = endVector;


	// Is this the FIRST vector in the chain?
	if (VectorListStart == NULL) {
		VectorListStart = newNodePtr;
		VectorListEnd = newNodePtr;
	} // End if this is the first vector to be added.
	else  // It's not the first, add to end.
	{
		VectorListEnd->nextNode = newNodePtr;
		VectorListEnd = newNodePtr;
	}

	// Always increment length.
	length++;



}; // end HanselChain::addVector

// Purpose: Removes a vector to the end of the Chain
// Input:	N/A
// Output:	N/A
// Returns:	vector removed from end of chain
// Notes:	Decrements length
Vector* HanselChain::removeVector(void)
{

	vectorNode* TempPtr;
	Vector* ReturnPtr;

	// Empty list?
	if (VectorListStart == NULL)
		return(NULL);

	if (VectorListStart == VectorListEnd) // Only one node.
	{
		ReturnPtr = VectorListStart->data;
		delete VectorListStart;	// Delete the Node
		VectorListStart = NULL;
		VectorListEnd = NULL;
	}
	else
	{
		TempPtr = VectorListStart;

		// Find the second to the last node
		while (TempPtr->nextNode != VectorListEnd)
			TempPtr = TempPtr->nextNode;

		// Get the stuff we need and delete last node.
		ReturnPtr = VectorListEnd->data;
		delete VectorListEnd;
		VectorListEnd = TempPtr;
		VectorListEnd->nextNode = NULL;
	}

	length--;
	return(ReturnPtr);
}; // End HanselChain::RemoveVector()

// Purpose: Retrieves the length of the chain
// Input:	N/A
// Output:	N/A
// Returns:	length
// Notes:	N/A
int HanselChain::retrieveLength()
{
	return(length);
};  // End HanselChain::retrieveLength()

// Purpose: Presents vectors in chain with a vector from which they expand themselves
// Input:	vector from which to expand Chain vectors
// Output:	N/A
// Returns:	N/A
// Notes:	N/A
/*void HanselChain::expandChainVectors(Vector expandFrom)
{
	vectorNode* TempPointer;
	TempPointer = VectorListStart;


	while (TempPointer != NULL)
	{

		TempPointer->data->compareAndSet(expandFrom);
		TempPointer = TempPointer->nextNode;
	}

}; // End HanselChain::expandChainVectors*/

// Purpose: Retrieves next unexpanded vector from Chain if existent
// Input:	Boolean to determine if self should start at top of chain
// Output:	vector, if exists
// Returns:	true if vector exists, else false
// Notes:	N/A
Vector* HanselChain::retrieveNextUnexpandedVector(bool startTop)
{
	vectorNode* TempPointer;
	vectorNode* CurrentPointer;

	if (startTop)	 // Start at end of chain.
	{
		CurrentPointer = VectorListEnd;
		do
		{

			if (!CurrentPointer->data->retrieveKnown()) {
				// retrievedVector = TempPointer->data;

				return(CurrentPointer->data);
				//CurrentPointer = VectorListStart;
			}
			else
			{

				TempPointer = CurrentPointer;
				CurrentPointer = VectorListStart;

				// Move down chain one node, hard way. 
				if (CurrentPointer != TempPointer) {
					while ((CurrentPointer->nextNode != TempPointer) &&
						(CurrentPointer != TempPointer))
						CurrentPointer = CurrentPointer->nextNode;
				} // end if
			} // end else

		} while (CurrentPointer != VectorListStart);

		if (!CurrentPointer->data->retrieveKnown()) {
			// retrievedVector = TempPointer->data;
			return(CurrentPointer->data);
		}// end if 

	}
	else  // Start at begining of chain. 
	{
		TempPointer = VectorListStart;

		while (TempPointer != NULL)
		{
			if (!TempPointer->data->retrieveKnown()) {
				//retrievedVector = TempPointer->data;
				return(TempPointer->data);
				TempPointer = NULL;
			}
			else
			{
				TempPointer = TempPointer->nextNode;
			}
		}
	}

	// No vector found, return NULL
	return(NULL);

};// end HanselChain::retrieveNextUnexpandVector

// Purpose: Displays the inquired vectors from the Hansel Chain set
//             (i.e. binary space of function)
// Input:	N/A
// Output:	N/A
// Returns:	N/A
// Notes:	displays to screen the vectors, their values, and their inquiry bits
void HanselChain::displayQuestions(void)
{
	vectorNode* TempPtr;
	TempPtr = VectorListStart;
	while (TempPtr != NULL) {
		if (TempPtr->data->retrieveInquiredStatus()) {
			//TempPtr->data->display(std::ofstream(NULL));  // Tell each vector to display it's elements
		}
		TempPtr = TempPtr->nextNode; // Move to the next chain.
	}
}; // end HanselChainSet::displayQuestions()

// Purpose: Finds the "shift point" if any in this chain, and returnsit to
//			the MonotoneBooleanFunction.
// Input:	N/A
// Output:  N/A
// Returns: Returns the shift point.
// Notes:	N/A
Vector* HanselChain::getShiftPoint()
{
	vectorNode* TempPointer;
	TempPointer = VectorListStart;

	while (TempPointer != NULL) // more vectors left
	{
		if (TempPointer->data->retrieveKnown()) // dumb error checking
			if (TempPointer->data->retrieveFunctionalValue())  // Is this the shift point?
				return(TempPointer->data);

		TempPointer = TempPointer->nextNode;
	} // end while.
	return(NULL);
}