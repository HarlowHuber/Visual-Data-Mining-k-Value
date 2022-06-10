/* **********************************************************************
   *  UPDATE 3/28/2022 - Harlow Huber
   *	The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
   *	This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will 
   *	put my changes below. All functionality will remain the same, or exceedingly similar.
   *	All previous code comments will remain, for now, as a reference.
   * 
   *  BUG FIXES 3/28/2022 - Harlow Huber
   *	Vector::operator "=" returns "Boolean" (had no return type). Returns TRUE. This may have intended to be the equivalent of "void" in C++98?
   *	getSize() returns "int" (had no return type)
   *	added "std::" to "cout," "endl," and "flush" calls
   *	
   *  FILE        : vector.cpp
   *  NAME        : Vector Object implementation
   *  OWNER       : Chad Burdyshaw (only owner can make changes)
   *  VERSION     : 1.2            (major change.minor change)
   *
   *  CHANGE LOG  :
   *     VERSION #  DATE      WHO COMMENT
   *     ---------------------------------------------------------------
   *     0.1.0      11.17.98  CB  Created file and imported Vector
   *                                 class info from old restore.h
   *     0.2.0      11.18.98  SAF Updated array indexing to range from 0...k-1
   *                                 rather than 1...k
   *                                 Methods affected: setBit, retrieveBit, compareAndSet
   *                              Updated constructor to set all vector elements to 0
   *     0.3.0      11.18.98  SAF Added >= operator for use in MonotoneBooleanFunction
   *     0.4.0      11.18.98  SAF Added retrieveNumberElements for use in MonotoneBooleanFunction
   *     0.5.0      11.18.98  SAF Added =, ==, & operators for use in MonotoneBooleanFunction
   *     0.5.1      11.19.98  SAF Fixed bug in operator = where 1st bit was not set
   *     0.5.2      11.19.98  SAF Fixed bug where operator = was not assigning value, valueKnown,
   *                                 wasInquired
   *     0.6.0      11.20.98  JWS Added display
   *                              Added getSize
   *                              added retrieveKnown
   *     0.6.1      11.20.98  SAF Fixed a slough of heinous array indexing problems in most
   *                                 operators
   *     0.6.2      11.21.98  JWS Updated setValue to set valueKnown to TRUE
   *     0.6.3      11.21.98  SAF Fixed a memory leak in operator &
   *     1.0.0      11.23.98  ALL Initial Client Release
   *     1.1.0      11.28.98  SAF Added display to a file
   *     1.2.0      11.28.98  SAF Added clearBit
   *
   *  SYSTEM      : ANSI C++ - should build on everything.
   *				Not any longer, since I use __declspec(dllexport) but should
					not be very difficult with some preprocessor directives to
					change ... at your own risks .FD
   *
   *  DESCRIPTION : Vector representing a bit string of "symptoms" and the
   *                                    operations on these vectors
   *
   *  INCLUDES    : N/A
   *
   *  TODO        : N/A
   *
   *************************************************************************/

#include "pch.h"

   // Purpose: Creates a new vector with n elements
   // Input:	number of elements
   // Output:	N/A
   // Returns:	N/A
   // Notes:	sets wasInquired and valueKnown to FALSE.
Vector::Vector(int n)
{
	size = n;
	wasInquired = FALSE;
	valueKnown = FALSE;
	value = -1;

	//initialize array to zeros
	for (int i = 0; i < size; i++)
	{
		array[i] = 0;
	};
};

// Purpose: Sets bit at index to the given value
// Input:	index of bit to set
//			
// Output:	N/A
// Returns:	N/A
// Notes:	N/A
void Vector::set_kValue(int index, int value)
{
	if (index < size)
		array[index] = value;
};

// Purpose: Sets bit at index to FALSE
// Input:	index of bit to set
//			
// Output:	N/A
// Returns:	N/A
// Notes:	N/A
void Vector::clear_kValue(int index)
{
	if (index <= size)
		array[index - 1] = 0;
};

// Purpose: Retrieve k-value at index
// Input:	index of value
// Output:	N/A
// Returns:	value
// Notes:	N/A
int Vector::retrieve_kValue(int index) const
{
	return array[index - 1];
};

// Purpose: Sets vector to given value
// Input:	Boolean value
// Output:	N/A
// Returns:	N/A
// Notes:	N/A
void Vector::setFunctionalValue(int answer)
{
	valueKnown = TRUE;
	value = answer;
};

// Purpose: Tells the vector is has been presented to the oracle
// Input:	N/A
// Output:	N/A
// Returns:	N/A
// Notes:	Sets the wasInquired flag
void Vector::setInquired(void)
{
	wasInquired = TRUE;
};

// Purpose: Compares self vector the the expandFrom Vector and determines its
//			value from the rules given.
// Input:	vector from which to expand if possible
// Output:	N/A
// Returns:	N/A
// Notes:	If the value of the expandFrom vector is TRUE, we check if self
//              is larger than the expandFrom vector. If self is larger, then
//              self sets its value to TRUE and valueKnown to TRUE.
//          If the value of the expandFrom vector is FALSE, we check if self
//              is smaller than the expandFrom vector. If self is smaller, then
//              self sets its value to FALSE and valueKnown to TRUE.
/*void Vector::compareAndSet(Vector expandFrom)
{
	Boolean expandFromValue = expandFrom.retrieveValue();

	//self and expandFrom vector must be isometric (ie comparable), we will 
	//		check that here

	//if the vectors are isometric we can check to see how they are related
	//if expandFromValue is TRUE we will check to see if self is larger than 
	//		expandFrom vector
	int i = 0;
	Boolean larger = FALSE;
	Boolean smaller = FALSE;

	if (expandFromValue == TRUE)
	{
		//check to see if self is greater than expandFrom vector
		while ((array[i - 1] >= (expandFrom.retrieveBit(i))) && (i <= size))
		{
			i++;
		};
		//if search has looped through entire element then self may be larger  
		//then expandFrom. To make sure we must recheck the last element. To 
		//do so we have to reset i to be in range.
		if (i == size + 1)
		{
			i--;
			if (array[i - 1] >= (expandFrom.retrieveBit(i)))
				larger = TRUE;
		};
	}
	else //(expandFromValue==FALSE)
	{
		//check to see if self is less than expandFrom vector
		while ((array[i - 1] <= (expandFrom.retrieveBit(i))) && (i <= size))
		{
			i++;
		};
		//if search has looped through entire element then self may be smaller  
		//then expandFrom. To make sure we must recheck the last element. To 
		//do so we have to reset i to be in range.
		if (i == size + 1)
		{
			i--;
			if (array[i - 1] <= (expandFrom.retrieveBit(i)))
				smaller = TRUE;
		};
	};

	if (larger == TRUE)
	{
		value = TRUE;
		valueKnown = TRUE;
	}
	else if (smaller == TRUE)
	{
		value = FALSE;
		valueKnown = TRUE;
	}
	else //items are not comparable
	{
		//do nothing
	};
};*/

// Purpose: Retrieves the functional value of the vector as presented by the Oracle.
// Input:	N/A
// Output:	N/A
// Returns:	Returns value
// Notes:	N/A
int Vector::retrieveFunctionalValue(void) const
{
	return value;
};

// Purpose: Retrieves the value of wasInquired. That is, whether or not the vector
//				has been presented by the Oracle.
// Input:	N/A
// Output:	N/A
// Returns:	Returns value of wasInquired
// Notes:	N/A
bool Vector::retrieveInquiredStatus(void) const
{
	return wasInquired;
};

// Purpose: Checks if the value of the vector is known
// Input:       N/A
// Output:      N/A
// Returns:     Returns valueKnown
// Notes:       N/A
bool Vector::retrieveKnown(void) const 
{
	return valueKnown;
}; // Vector::retrieveKnown

// Purpose: Sets all vector bits to FALSE
// Input:       N/A
// Output:      N/A
// Returns:     N/A
// Notes:       N/A
void Vector::clearVector(void) 
{
	// clears each vector element
	for (int clearBit = 0; clearBit < size; clearBit++) 
	{
		array[clearBit] = FALSE;
	}
}; // Vector::clearVector

// Purpose: Checks if selfVector is greater than or equal to secondVector
// Input:       comparer vector
// Output:      N/A
// Returns:     TRUE if selfVector greater than or equal to secondVector
// Notes:       self Vector is not greater/equal if
//                 selfVector[element k] = FALSE && secondVector[element k] = TRUE
bool Vector::operator >=(Vector& secondVector) const 
{
	// checks both vectors' elements
	for (int index = 0; index < size; index++) 
	{
		// selfVector is less than secondVector
		if ((secondVector.array[index] == TRUE) && (array[index] == FALSE)) 
		{
			return FALSE;
		}
	}

	return TRUE;
}; // Vector::operator >=

// Purpose:	Element-wise AND of two vectors
// Input:       comparer vector
// Output:      N/A
// Returns:     Result of operation
// Notes:       N/A
Vector Vector::operator &(Vector& secondVector) const // FIX: how to implement for k-value??
{
	Vector thirdVector(size);

	// checks both vectors' elements
	for (int index = 0; index < size; index++) 
	{
		// selfVector is less than secondVector
		if ((secondVector.array[index] == TRUE) && (array[index] == TRUE)) {
			thirdVector.set_kValue(index + 1, 1);
		}	
	}	

	return thirdVector;
}; // Vector::operator &

// Purpose: Overloads == (equal) operator for two Vectors
// Input:       comparer vector
// Output:      N/A
// Returns:     Result of operation
// Notes:       N/A
bool Vector::operator ==(Vector& secondVector) const 
{
	// checks both vectors' elements
	for (int index = 0; index < size; index++) 
	{
		// selfVector is not equal to secondVector
		if (secondVector.array[index] != array[index]) 
		{
			return FALSE;
		}	
	}	

	return TRUE;
}; // Vector::operator ==

// Purpose: Overloads != (not equal) operator for two Vectors
// Input:       comparer vector
// Output:      N/A
// Returns:     Result of operation
// Notes:       N/A
bool Vector::operator !=(const Vector& secondVector) const 
{
	bool returnValue = TRUE;
	// checks both vectors' elements
	for (int index = 0; index < size; index++) {

		// selfVector is not equal to secondVector
		if (secondVector.array[index] != array[index]) 
		{
			return TRUE;
		}
	}	

	return FALSE;
}; // Vector::operator ==

// Purpose: Assignment of secondVector to selfVector
// Input:       original vector vector
// Output:      N/A
// Returns:     Result of operation
// Notes:       N/A
bool Vector::operator =(const Vector& secondVector) {
	// assigns all vector elements
	for (int index = 0; index < size; index++) 
	{
		array[index] = secondVector.array[index];
	}	// assigns all vector elements

	value = secondVector.value;
	wasInquired = secondVector.wasInquired;
	valueKnown = secondVector.valueKnown;

	return TRUE;
}; // Vector::operator =

// Purpose: Displays vector elements and value to a file
// Input:       pointer to a file stream
// Output:      N/A
// Returns:     N/A
// Notes:       N/A
void Vector::display(std::ofstream& outputFile) const {
	// display each vector
	if (outputFile) {
		outputFile << " " << std::flush;
	}
	else {
		std::cout << " " << std::flush;
	}

	for (int i = 0; i < size; i++) {
		if (outputFile) {
			outputFile << array[i];
		}
		else {
			std::cout << array[i];
		}
	}	// end display each vector
	for (int j = 0; j < (MAX_ELEMENTS - size); j++) {
		if (outputFile) {
			outputFile << " ";
		}
		else {
			std::cout << " ";
		}
	}

	if (outputFile) {
		outputFile << "   " << value << "       " << std::flush;
	}
	else {
		std::cout << "   " << value << "       " << std::flush;
	}

	if (wasInquired == TRUE) {
		if (outputFile) {
			outputFile << "YES" << std::endl << std::flush;
		}
		else {
			std::cout << "YES" << std::endl << std::flush;
		}
	}
	else {
		if (outputFile) {
			outputFile << "NO" << std::endl << std::flush;
		}
		else {
			std::cout << "NO" << std::endl << std::flush;
		}
	}
}; // Vector::display

// Purpose: Gets size of vector
// Input:       N/A
// Output:      N/A
// Returns:     size
// Notes:       N/A
int Vector::getSize(void) const {
	return size;
}; // Vector::getSize

// Purpose: Finds the number of TRUE elements in the vector
// Input:       N/A
// Output:      N/A
// Returns:     integer number of TRUE elements
// Notes:       N/A
int Vector::retrieveNumberTrueElements(void) const {
	int elementNumber = 0;
	// count TRUE elements
	for (int counter = 0; counter < size; counter++) {
		if (array[counter] == TRUE) {
			elementNumber++;
		}
	}	// end count TRUE elements
	return elementNumber;
}; // Vector::retrieveNumberElements

// Purpose: Returns true if all vector bits are 0.
// Input:       N/A
// Output:      N/A
// Returns:     Truth value of all bits being zero.
// Notes:       N/A
bool Vector::allZeros(void)
{
	for (int i = 0; i < size; i++)
		if (array[i] == 1)
			return FALSE;


	return TRUE;

} // end allZeros.