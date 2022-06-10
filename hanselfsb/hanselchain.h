#pragma once

/* **********************************************************************
   *  UPDATE 3/28/2022 - Harlow Huber
   *	The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
   *	This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will 
   *	put my changes below. All functionality will remain the same, or exceedingly similar.
   *	All previous code comments will remain, for now, as a reference.
   * 
   *  BUG FIXES 3/28/2022 - HARLOW HUBER
   *	in display(), "ofstream" changed to "std::ofstream"
   * 
   *  FILE        : hanselchain.h
   *  NAME        : Hansel Chain Specification
   *  OWNER       : Jay Summet     (only owner can make changes)
   *  VERSION     : 1.1            (major change.minor change)
   **
   ** I did change some things in this code, I had too, see code for more
   ** information, now it is a dll, and IS reusable ...
   **
   ** Florian DELIZY (FD)
   **
   *
   *  CHANGE LOG  :
   *     VERSION #  DATE      WHO COMMENT
   *     ---------------------------------------------------------------
   *     0.1.0      11.21.98  JWS Created file
   *     1.0.0      11.23.98  ALL Initial Client Release
   *     1.1.0      11.28.98  SAF Added file output for display
   *
   *
   *  SYSTEM      : ANSI C++ - should build on everything.
   *
   *  DESCRIPTION : N/A
   *
   *  INCLUDES    : File Stream (fstream.h)
   *
   *  TODO        : N/A
   *
   *************************************************************************/

#ifndef _HANSELCHAIN_H
#define _HANSELCHAIN_H

#include "pch.h"

   // #include "vector.h" <- change this boy, use the compiler options to make it work !
   //in addition vector is something allready exists ... if I have the time it will go away
   // FD

// #include "monobool.h" <- could I now why ?!?!??

// Purpose:	Represents a Hansel Chain
class __declspec(dllexport) HanselChain {

public:
	// Purpose: Creates an empty Hansel Chain
	// Input:	N/A
	// Output:	N/A
	// Returns:	N/A
	// Notes:	Sets length to 0
	HanselChain();

	// Purpose: Deletes the Chain and all vectors it holds.
	// Input:	N/A
	// Output:	N/A
	// Returns:	N/A
	// Notes:	N/A
	~HanselChain();

	// Purpose: Displays the chain to a file
	// Input:	pointer to file stream
	// Output:	N/A
	// Returns:	N/A
	// Notes:	N/A
	void display(std::ofstream& outputFile) const;

	// Purpose:	Calls the display method of all vectors in chain.
	// Input:	N/A
	// Output:	N/A
	// Returns:	N/A
	// Notes: Prints only questions
	void displayQuestions();

	// Purpose: This method will return a new HanselChain, which is
	//		composed of each of the vectors in the current
	//		hansel chain with the "FIRST" argument prefixed
	//		onto them. 
	// Input:	Either a zero or a 1, depending on what to prefix 
	// Output:	N/A
	// Returns:	A new HanselChain, seperate from the old one. 
	// Notes:	N/A
	HanselChain* generateNext(int First);

	// Purpose: Adds a vector to the end of the Chain
	// Input:	vector to add to end of chain
	// Output:	N/A
	// Returns:	N/A
	// Notes:	Increments length
	void addVector(Vector* endVector);

	// Purpose: Removes a vector to the end of the Chain
	// Input:	N/A
	// Output:	N/A
	// Returns:	vector removed from end of chain
	// Notes:	Decrements length
	Vector* removeVector(void);

	// Purpose: Retrieves the length of the chain
	// Input:	N/A
	// Output:	N/A
	// Returns:	length
	// Notes:	N/A
	int retrieveLength();

	// Purpose: Presents vectors in chain with a vector from which they expand themselves
	// Input:	vector from which to expand Chain vectors
	// Output:	N/A
	// Returns:	N/A
	// Notes:	N/A
	//void expandChainVectors(Vector expandFrom);

	// Purpose: Retrieves next unexpanded vector from Chain if existent
	// Input:	Boolean to determine if self should start at top of chain
	// Output:	vector, if exists
	// Returns:	true if vector exists, else false
	// Notes:	N/A
	Vector* retrieveNextUnexpandedVector(bool startTop);

	// Purpose: Finds the "shift point" if any in this chain, and returnsit to
	//			the MonotoneBooleanFunction.
	// Input:	N/A
	// Output:  N/A
	// Returns: Returns the shift point.
	// Notes:	N/A
	Vector* getShiftPoint();

	// I had to do it ... 
	//.FD

	Vector* operator[](int i) // I now it should return a reference, 
							  // but I don't have the time to rewrite this program :/
	{
		if (i < 0 || i > length) return NULL;

		int j;
		vectorNode* cur = VectorListStart;
		for (j = 0; j < i && cur; j++) cur = cur->nextNode;
		return cur->data;

	}


private:
	int length;				// number of vectors in chain
	struct vectorNode
	{
		Vector* data;
		vectorNode* nextNode;
	};
	vectorNode* VectorListStart;	// Pointer to List of vectors
	vectorNode* VectorListEnd;		// Pointer to End of Vector
};	// HanselChain

#endif
