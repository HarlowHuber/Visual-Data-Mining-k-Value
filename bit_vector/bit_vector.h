#pragma once

/*
 *	UPDATE 3 / 28 / 2022 - Harlow Huber
 *		The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
 *		This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
 *		put my changes below.All functionality will remain the same, or exceedingly similar.
 *		All previous code comments will remain, for now, as a reference.
 * 
 *	BUG FIXES
 */

#ifndef __BIT_VECTOR_H__
#define __BIT_VECTOR_H__

// this class is used to keep track of each vector ...
// used both by the input and the nvboolfunc

#include "vector.h" // added to include work of other on Hanselchains
#include <vector>

// in this implementation the first bit is the left one, means, little endian ...
class __declspec(dllexport) bit_vector_t
{
private:
	void setLevel(void);					// set the level of the vector when initialized
protected:
	int* kv_array;							// array containing the k-value elements
	size_t size;							// size of the vector
	int level;								// the level (Hamming norm) of the bit_vector_t

public:
	bit_vector_t(void);						// default constructor
	bit_vector_t(const char* const str);	// from a string
	bit_vector_t(size_t _size);				// only witha size
	bit_vector_t(size_t _size, int val);	// to check for little/big endian ...
	bit_vector_t(const bit_vector_t& src);	// copy constructor
	bit_vector_t(const Vector& src);		// conversion methods

	bit_vector_t& operator=(const bit_vector_t& src);	// copy operator
	bit_vector_t& operator=(const Vector& src);			// conversion method from proprietary vector
	~bit_vector_t(void);

	int getlevel(void);

	bool operator>(bit_vector_t& x);		// lattice order operators, to now if
	bool operator<(bit_vector_t& x);		// two bitvector are not comparable, then
	bool operator>=(bit_vector_t& x);		// try the two opposite operators
	bool operator<=(bit_vector_t& x);		// return false if not comparable or if
	bool operator==(bit_vector_t& x);		// comparison return false, true if not
	bool operator!=(bit_vector_t& x);		// nearly the same

	bit_vector_t& bitOr(bit_vector_t& x, bit_vector_t& y);	//Bitwise OR of the vectors.

	int& operator[](size_t i);				// access operator needed by input

	char* get_string(void);					// retreive a string describing the vector, to be deleted after use

	size_t get_size(void) { return size; }	// get the size of the vector

	size_t get_value(void);					// return a conversion of the value of the vector

	void print(void);						// print a vector to the screen
};

#endif