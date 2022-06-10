/* **********************************************************************
   *  UPDATE 3/28/2022 - Harlow Huber  
   *	The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
   *	This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
   *	put my changes below. All functionality will remain the same, or exceedingly similar.
   *	All previous code comments will remain, for now, as a reference.
   *
   *  BUG FIXES 3/28/2022 - Harlow Huber
   *	in display(), "ofstream" changed to "std::ofstream"
   *	removed "HanselChainSet::" from private function declarations  
   *	added "std::" to Standard Library functions
   *	changed "if (file != NULL)" to "if (file)," for the previous does not work in newer C++ versions
   * 
   *  FILE        : hanselchainset.cpp
   *  NAME        : Hansel Chain Set Implementation
   *  OWNER       : Jay Summet     (only owner can make changes)
   *  VERSION     : 1.1            (major change.minor change)
   *
   *  CHANGE LOG  :
   *     VERSION #  DATE      WHO COMMENT
   *     ---------------------------------------------------------------
   *     0.1.0      11.21.98  JWS Created file
   *     0.2.0      11.21.98  SAF Added retrieveChainShift stub
   *     0.3.0      11.21.98  SAF Updated generateInquiry to return
   *                                 FALSE if done generating
   *     1.0.0      11.23.98  ALL Initial Client Release
   *     1.1.0      11.28.98  SAF Added display to a file
   *
   *  SYSTEM      : ANSI C++ - should build on everything.
   *
   *  DESCRIPTION : N/A
   *
   *  INCLUDES    : Hansel Chain Set class (hanselchainset.h)
   *                Standard-C Library (stdlib.h)
   *
   *  TODO        : N/A
   *
   *************************************************************************/

#include "pch.h"
#include <stdlib.h>
#include "hanselchainset.h"
   // #include <stdlib.h> <- *That's* a great idea ! 



// Purpose: Creates a new set of Hansel Chains based on n elements per vector
// Input:	number of elements per vector
// Output:	N/A
// Returns:	N/A
// Notes:	N/A
HanselChainSet::HanselChainSet(int n)
{
	if (n < 1) { std::cout << "ACK! too small!\n"; exit(-1); }

	maxChainLength = n + 1;

	// Create the trivial case of N = 1;
	chainNode* newNodePtr;
	newNodePtr = new chainNode;
	newNodePtr->nextNode = NULL;
	newNodePtr->data = new HanselChain();

	// This case has a single chain with two vectors { <0>,<1>} 
	// FIX FOR K-VALUE
	Vector* V = new Vector(1);
	newNodePtr->data->addVector(V);
	V = new Vector(1);
	V->set_kValue(1, 1);
	newNodePtr->data->addVector(V);

	ChainListStart = newNodePtr;
	ChainListEnd = newNodePtr;

	// Generates Hansel chains.
	for (int i = 2; i <= n; i++)
		MagicallyCreateNextLevel();

} // end HanselChainSet::HanselChainSet(int n)

void HanselChainSet::MagicallyCreateNextLevel(void)
{


	HanselChain* ZeroC;
	HanselChain* OneC;
	Vector* CutNPaste;

	// We use our current data as level n(old), and generate level N+1
	chainNode* OldStart = ChainListStart;
	ChainListStart = NULL; ChainListEnd = NULL; length = 0;


	// For each chain in the Old list:
	while (OldStart != NULL)
	{
		// Generate ZeroC and OneC from each chain.
		ZeroC = OldStart->data->generateNext(0);
		OneC = OldStart->data->generateNext(1);


		// Cut the last vector off of OneC and paste onto ZeroC
		CutNPaste = OneC->removeVector();
		ZeroC->addVector(CutNPaste);



		// Add both chains to new list, if OneC still has vectors. 
		addChain(ZeroC);
		if (OneC->retrieveLength() != 0)
			addChain(OneC);

		// Move to next chain, if it exists.
		OldStart = OldStart->nextNode;
	}

} // End HanselChainSet:: MagicallyCreateNextLevel (private)

void HanselChainSet::addChain(HanselChain* Chain)
{
	chainNode* newNodePtr;
	newNodePtr = new chainNode;
	newNodePtr->nextNode = NULL;
	newNodePtr->data = Chain;

	// Is this the FIRST chain in our list?
	if (ChainListStart == NULL) {
		ChainListStart = newNodePtr;
		ChainListEnd = newNodePtr;
	}
	else
	{
		ChainListEnd->nextNode = newNodePtr;
		ChainListEnd = newNodePtr;
	}

	// Always increment the length
	length++;

} // end HanselChainSet::addChain(HanselChain* Chain)





	// Purpose: Generates a new inquiry if function not completely expanded
	// Input:	N/A
	// Output:	next inquiry vector, if existent
	//          length of the Chain the vector is from
	// Returns:	True if function not completely expanded
	// Notes:	Calls HanselChain::retrieveNextUnexpandedVector in each chain
	//             until we run out of chains
Vector* HanselChainSet::generateInquiry(int& nextInquiryChainLength)
{
	// This function steps through all of the chains, starting with the
	// shortest, looking for unexpanded vectors. For chains of the same
	// length, we look for vectors starting at the end on the first.
	// If that chain does not have any unexpanded vectors, we begin looking
	// (from the front now) in all other chains of the same length for
	// an unexpanded vector. 
	// Should NO unexpanded vectors be found in all chains of the same length,
	// we move onto chains of the next avalible length  starting once
	// again at the end (i.e. looking in reverse order) of the first chain.
	// We keep doing this until either (a) we find an unexpanded vector, which
	// we then return for the oracle to pass judgement on, or (b) we exhast
	// all chains, and no unexpanded vectors exist, in which case we return
	// NULL, indicating that the binary space has been completely mapped
	// and that we are done.
	Vector* ReturnVector;
	chainNode* Pointer;

	//Starting at length one, we work up in chain length. 
	int currentLength = 1;
	bool StartAtEnd = TRUE;

	while (currentLength <= maxChainLength)
	{
		// Set the nextInquiryChainLength incase we find it this time.
		nextInquiryChainLength = currentLength;

		// Start at begining of chain-set.
		Pointer = ChainListStart;

		// Check each vector of currentLength.
		while (Pointer != NULL)
		{

			if (Pointer->data->retrieveLength() == currentLength)
			{

				if (StartAtEnd)
				{

					// Get the first unexpanded vector, checking from the end.
					ReturnVector = Pointer->data->retrieveNextUnexpandedVector(TRUE);

					// did this chain have one? If so, return it.
					if (ReturnVector != NULL)
						return(ReturnVector);

					StartAtEnd = FALSE;  // Check from begining on all others.
				}
				else
				{
					// Get the first unexpanded vector, checking from the front.
					ReturnVector = Pointer->data->retrieveNextUnexpandedVector(FALSE);

					// Did this chain have one? if so, return it.
					if (ReturnVector != NULL)
						return(ReturnVector);
				} // end else (if start_atEnd)

			} // End if Length is correct.

			// The current chain either is not the right size, or does not
			// have an unexpanded vector, so check out the next chain
			Pointer = Pointer->nextNode;

		} // end while (cycle through chain list)


		// Move up to next length of chain, starting at end of first.
		currentLength++;
		StartAtEnd = TRUE;

	} // End while (currentLength <= maxChainLength)

   // Ok, NONE of the chains have any vectors that have not been expanded yet.
   // So the binary space is complete, and we indicate this by returning NULL.
	return(NULL);
} // end generateInquiry 

	// Purpose: Expands the vectors based on a known vector generated by oracle's answer
	// Input:	vector from which to expand other vectors
	//          length of the Chain from which the vector was taken
	// Output:	N/A
	// Returns:	N/A
	// Notes:	calls HanselChain::expandChainVectors with expandFrom vector on each Chain
	//             of length L or (L + 2), where L is the length of the Chain that
	//             the expandFrom vector is from
/*void HanselChainSet::expandVectorValues(Vector expandFrom, int length)
{
	chainNode* TempPointer;
	TempPointer = ChainListStart;


	// Ask all chains of length L or L+2 to expand all vectors.
	while (TempPointer != NULL)
	{

		if ((TempPointer->data->retrieveLength() == length) ||
			(TempPointer->data->retrieveLength() == length + 2)) {
			TempPointer->data->expandChainVectors(expandFrom);
		}

		TempPointer = TempPointer->nextNode;
	} // end while.
}*/

// Purpose: Displays the Hansel Chain set (i.e. binary space of function)
//             to a file
// Input:	pointer to file stream
// Output:	N/A
// Returns:	N/A
// Notes:	displays to outputFile the vectors, their values, and their inquiry bits
void HanselChainSet::display(std::ofstream& outputFile) const {
	chainNode* TempPtr;

	TempPtr = ChainListStart;

	while (TempPtr != NULL) {
		TempPtr->data->display(outputFile);  // Tell each chain to display it's vectors.
			// output to a file
		if (outputFile) {
			outputFile << " --------------------------------" << std::endl << std::flush;
		}	// end output to a file
		else {
			std::cout << " --------------------------------" << std::endl << std::flush;
		}
		TempPtr = TempPtr->nextNode; // Move to the next chain.
	}
}; // end HanselChainSet::display()

// Purpose: Displays the inquired vectors from the Hansel Chain set
//             (i.e. binary space of function)
// Input:	N/A
// Output:	N/A
// Returns:	N/A
// Notes:	displays to screen the vectors, their values, and their inquiry bits
void HanselChainSet::displayQuestions(void)
{
	chainNode* TempPtr;

	TempPtr = ChainListStart;

	while (TempPtr != NULL) {
		TempPtr->data->displayQuestions();  // Tell each chain to display it's vectors.
		TempPtr = TempPtr->nextNode; // Move to the next chain.
	}
}; // end HanselChainSet::displayQuestions()




/*
	Wiped out by FD ... sorry I don't need it and it would be the mess

	// Purpose: Gives each hansel chain the MonBoolFunc to put the switchpoint into.
	// Input:	MonotoneBooleanFunction
	// Output:	N/A
	// Returns:	N/A
	// Notes:	N/A
void HanselChainSet::fillOutputMonoBoolFunc(MonotoneBooleanFunction& Func)
{	chainNode* TempPtr;
	Vector* vector;

	TempPtr = ChainListStart;

	while(TempPtr != NULL) {
		vector = TempPtr->data->getShiftPoint();  //
		if (vector != NULL)
		{
			if (vector->allZeros() )
			{
				// Generate all vectors for each element set.
				for(int i = 1; i <= vector->getSize(); i++)
				{
					Vector SpecialCase(vector->getSize());
					SpecialCase.setValue(TRUE);

					SpecialCase.setBit(i);
					Func.addVector(SpecialCase);
				} // end for.

				return; // Break out, done, binary space all TRUE.
			} // end if
			else
			{
			   Func.addVector(*vector);
			}
		}
		TempPtr = TempPtr->nextNode; // Move to the next chain.
	}


}
*/