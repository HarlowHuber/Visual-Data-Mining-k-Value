#ifndef __DATA3D_H__
#define __DATA3D_H__
#include "bit_vector.h"
#include <list>


class __declspec(dllexport) data3d
{
	//This holds information about the 3d data.

	//Each section of the 3d structure represents a group of vectors.
	//They are at the same level so they have the same number of 1s in them.
	//Each group is composed of vectors that differ from each other by at most 1 bit.
	//So 100, 010, and 001 all belong together.

	//So this structure consists of a list of bit vecotrs.


public:
	std::list<bit_vector_t> bvList;
	//Value of this data.
	bool value;
	//The disk level it belongs to.
	int level;
	//Whether data is expanded (fake) data.
	bool madeUp;

	data3d();
	data3d(const data3d&);
	~data3d();
	data3d& operator=(const data3d& rhs);
	int operator==(const data3d& rhs) const;
	int operator<(const data3d& rhs) const;
};


#endif

