/*
 *	UPDATE 3 / 28 / 2022 - Harlow Huber
 *		The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
 *		This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
 *		put my changes below.All functionality will remain the same, or exceedingly similar.
 *		All previous code comments will remain, for now, as a reference.
 *
 *	BUG FIXES
 */

#include "bit_vector.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// implementation of nvboolfunc

//**********************************************************************************************
//	Bitwise OR of two bit_vector_t.
//**********************************************************************************************

bit_vector_t& bit_vector_t::bitOr(bit_vector_t& x, bit_vector_t& y) // FIX: how does this work with k-value
{

	if (x.get_size() != y.get_size())
	{
		bit_vector_t bt = *new bit_vector_t();
		return bt;
	}

	bit_vector_t& newBV = *new bit_vector_t(x.get_size());

	//Or x and y and store the results in newBV.

	for (size_t i = 0; i < x.get_size(); i++)
	{
		newBV.kv_array[i] = x.kv_array[i] | y.kv_array[i];
	}

	return newBV;
}

//***********************************************************************************************
// default contructor
//***********************************************************************************************
bit_vector_t::bit_vector_t(void)
{
	size = 0;
	level = 0;
	kv_array = NULL;
}

//***********************************************************************************************
// contructor from a string "01001001000"
//***********************************************************************************************
bit_vector_t::bit_vector_t(const char* const str)
{
	if (str)
	{
		size = strlen(str);
		kv_array = new int[size];

		if (!kv_array)
		{
			size = 0;
			level = 0;
		}
		else 
		{
			for (size_t i = 0; i < size; i++)
			{
				kv_array[i] = str[i] - '0'; // subtract 0 to get decimal value from ASCII value
			}

			setLevel();
		}
	}
	else 
	{
		kv_array = NULL;
		size = 0;
		level = 0;
	}
}

//***********************************************************************************************
// contructor by the size only
//***********************************************************************************************
bit_vector_t::bit_vector_t(size_t _size)
{
	size = _size;
	kv_array = new int[size];
	level = 0;

	if (!kv_array)
	{
		size = 0;
	}
}

//***********************************************************************************************
// contructor by size and value as value only would not be distinguishable
// take bits from the right and forget the others ...
//***********************************************************************************************
bit_vector_t::bit_vector_t(size_t _size, int val)
{
	size = _size;
	kv_array = new int[size];

	if (!kv_array)
	{
		size = 0;
		level = 0;
	}
	else 
	{
		for (size_t i = 0; i < size; i++) 
		{
			kv_array[i] = val;
		}

		setLevel();
	}
}

//***********************************************************************************************
// copy contructor
//***********************************************************************************************
bit_vector_t::bit_vector_t(const bit_vector_t& src)
{
	size = src.size;
	kv_array = new int[size];

	if (!kv_array)
	{
		size = 0;
		level = 0;
	}
	else 
	{
		for (size_t i = 0; i < size; i++) 
		{
			kv_array[i] = src.kv_array[i];
		}

		level = src.level;
	}

}

//***********************************************************************************************
// copy operator
//***********************************************************************************************
bit_vector_t& bit_vector_t::operator=(const bit_vector_t& src)
{
	if (size != src.size)
	{
		if (kv_array) delete[](kv_array);

		size = src.size;
		kv_array = new int[size];

		if (!kv_array)
		{
			size = 0;
			level = 0;
		}
		else 
		{
			for (size_t i = 0; i < size; i++)
			{
				kv_array[i] = src.kv_array[i];
			}

			level = src.level;
		}
	}
	else 
	{
		for (size_t i = 0; i < size; i++)
		{
			kv_array[i] = src.kv_array[i];
		}

		level = src.level;
	}

	return *this;
}

//***********************************************************************************************
// destructor
//***********************************************************************************************
bit_vector_t::~bit_vector_t(void)
{
	if (kv_array) delete[](kv_array);
	size = 0;
	level = 0;
}

//***********************************************************************************************
// return the level of the vector (norm of the vector)
//***********************************************************************************************

int bit_vector_t::getlevel(void)
{
	return level;
}

//***********************************************************************************************
// sets the level of the vector (norm of the vector)
//***********************************************************************************************

void bit_vector_t::setLevel(void)
{
	level = 0;

	for (size_t i = 0; i < size; i++) 
		level += kv_array[i];
}


//***********************************************************************************************
// Order operator in the lattice scope  strict >
//***********************************************************************************************

bool bit_vector_t::operator>(bit_vector_t& x)
{
	if (!x.kv_array || !kv_array || x.size != size) 
		return false;

	for (size_t i = 0; i < size; i++)
	{
		if (kv_array[i] <= x.kv_array[i])
			return false;
	}

	return true;
}

//***********************************************************************************************
// Order operator in the lattice scope  strict <
//***********************************************************************************************

bool bit_vector_t::operator<(bit_vector_t& x)
{
	if (!x.kv_array || !kv_array || x.size != size) 
		return false;

	for (size_t i = 0; i < size; i++)
	{
		if (kv_array[i] >= x.kv_array[i])
			return false;
	}

	return true;
}

//***********************************************************************************************
// Order operator in the lattice scope  >=
//***********************************************************************************************

bool bit_vector_t::operator>=(bit_vector_t& x)
{
	if (!x.kv_array || !kv_array || x.size != size) 
		return false;
	
	for (size_t i = 0; i < size; i++)
	{
		if (kv_array[i] < x.kv_array[i])
			return false;
	}

	return true;
}

//***********************************************************************************************
// Order operator in the lattice scope  strict <=
//***********************************************************************************************

bool bit_vector_t::operator<=(bit_vector_t& x)
{
	if (!x.kv_array || !kv_array || x.size != size) 
		return false;
	
	for (size_t i = 0; i < size; i++)
	{
		if (kv_array[i] > x.kv_array[i])
			return false;
	}

	return true;
}

//***********************************************************************************************
// This operator return true if the 2 vectors are equal
//***********************************************************************************************

bool bit_vector_t::operator==(bit_vector_t& x)
{
	if (!x.kv_array || !kv_array || x.size != size) 
		return false;
	
	for (size_t i = 0; i < size; i++)
	{
		if (kv_array[i] != x.kv_array[i])
			return false;
	}

	return true;
}

//***********************************************************************************************
// This operator return true if different, or not comparable false if not.
//***********************************************************************************************

bool bit_vector_t::operator!=(bit_vector_t& x)
{
	if (!x.kv_array || !kv_array || x.size != size) 
		return true;

	for (size_t i = 0; i < size; i++)
	{
		if (kv_array[i] != x.kv_array[i])
			return true;
	}

	return false;
}

//***********************************************************************************************
// return the bit from the vector
//***********************************************************************************************
int& bit_vector_t::operator[](size_t i)
{
	if (i > size) return kv_array[size];
	else return kv_array[i];
}

//***********************************************************************************************
// return a conversion in the value
//***********************************************************************************************

size_t bit_vector_t::get_value(void)
{
	size_t r = 0;

	for (int i = 0; i < size; i++)	
		r |= static_cast<size_t>(kv_array[i]) << i; // used to be for Boolean: (bit_array[i]) ? 0x1 : 0x0) << i

	return r;
}

//***********************************************************************************************
// return a string containing the bit vector
//***********************************************************************************************

char* bit_vector_t::get_string(void)
{
	size_t i;
	char* v = new char[size + 1];
	v[size] = '\0';

	for (i = 0; i < size; i++)
	{
		v[i] = kv_array[i];
	}

	return v;
}

//***********************************************************************************************
// Compatibility methods
// construct a bit_vector_t from a Vector of the Hanselchain project
// and operator= from the same type of object
//***********************************************************************************************

bit_vector_t::bit_vector_t(const Vector& src)
{

	size = (size_t)src.getSize();
	kv_array = new int[size];

	if (!kv_array)
	{
		size = 0;
		level = 0;
	}
	else 
	{
		for (int i = 0; i < size; i++)
		{
			kv_array[i] = src.retrieve_kValue(i); // FIX used to be (src.retrieveBit(i + 1) == 1) ???
		}

		setLevel();
	}
}

bit_vector_t& bit_vector_t::operator=(const Vector& src)
{
	bit_vector_t u(src);
	*this = u;
	return *this;
}

void bit_vector_t::print(void)
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%i, ", kv_array[i]);
		fflush(stdout);
	}

	int dec_value = 0;
	int base = 1;
	
	for (int i = size - 1; i >= 0; i--)
	{
		int last_digit = kv_array[i];
		dec_value += last_digit * base;
		base = base * 2;
	}

	printf(" Decimal value: %i\n", dec_value);
}