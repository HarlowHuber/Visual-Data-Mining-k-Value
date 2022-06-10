#include "data3d.h"
#include "bit_vector.h"
#include <list>

using namespace std;


data3d::data3d()
{
	madeUp = false;
	value = false;
	level = 0;
}

data3d::data3d(const data3d& d3d)
{
	bvList = d3d.bvList;
	value = d3d.value;
	level = d3d.level;
	madeUp = d3d.madeUp;
}

data3d::~data3d()
{

}

data3d& data3d::operator=(const data3d& rhs)
{
	bvList = rhs.bvList;
	value = rhs.value;
	level = rhs.level;
	madeUp = rhs.madeUp;

	return *this;
}

int data3d::operator==(const data3d& rhs) const
{
	//	note:	Harlow Huber	4 / 6 / 2022
	//	the following commented out line of code used to be the whole implementation of this function:
	// 
	//		return this->madeUp == rhs.madeUp && this->bvList == rhs.bvList && this->value == rhs.value && this->level == rhs.level;
	// 
	//	however, that std::list operator does not work with std::list<bit_vector_t>, 
	//	for bit_vector_t is not a type that has a built-in comparison operator. 
	//	therefore, it must be defined: 
	//	here is the new implementation to see if two lists of bit_vector_t are equal.

	//	flags
	bool equal_status = true;

	//	temp lists
	std::list<bit_vector_t> temp_lhs(this->bvList);
	std::list<bit_vector_t> temp_rhs(this->bvList);

	//	compare lists according to each bit_vector_t element
	while (temp_lhs.size() > 0 && temp_rhs.size() > 0)
	{
		bit_vector_t bv_lhs = temp_lhs.front();
		bit_vector_t bv_rhs = temp_lhs.front();

		if (bv_lhs != bv_rhs)
		{
			equal_status = false;
			break;
		}

		temp_lhs.pop_front();
		temp_rhs.pop_front();
	}

	//	if elements are equal, check list length
	if (equal_status)
	{
		int lhs_size = this->bvList.size();
		int rhs_size = rhs.bvList.size();

		if (lhs_size != rhs_size)
		{
			equal_status = false;
		}
	}

	return this->madeUp == rhs.madeUp && equal_status && this->value == rhs.value && this->level == rhs.level;
}

int data3d::operator<(const data3d& rhs) const
{
	//	note:	Harlow Huber	4 / 5 / 2022
	//	the following commented out line of code used to be the whole implementation of this function:
	// 
	//		return this->bvList < rhs.bvList && this->value < rhs.value && this->level < rhs.level;
	// 
	//	however, that std::list operator does not work in c++20 (this->bvList < rhs.bvList).
	//	here is the new implementation to compare two lists of bit_vector_t.

	//	flags
	bool rhs_bvList_is_greater = true;
	bool equal_status = true;

	//	temp lists
	std::list<bit_vector_t> temp_lhs(this->bvList);
	std::list<bit_vector_t> temp_rhs(this->bvList);

	//	compare lists according to each bit_vector_t element
	while (temp_lhs.size() > 0 && temp_rhs.size() > 0)
	{
		bit_vector_t bv_lhs = temp_lhs.front();
		bit_vector_t bv_rhs = temp_lhs.front();

		if (bv_lhs < bv_rhs)
		{
			equal_status = false;
		}
		else if (bv_lhs > bv_rhs)
		{
			rhs_bvList_is_greater = false;
			equal_status = false;
			break;
		}

		temp_lhs.pop_front();
		temp_rhs.pop_front();
	}

	//	if elements are equal, check list length
	if (equal_status)
	{
		int lhs_size = this->bvList.size();
		int rhs_size = rhs.bvList.size();

		if (lhs_size >= rhs_size)
		{
			rhs_bvList_is_greater = false;
		}
	}

	return  rhs_bvList_is_greater && this->value < rhs.value && this->level < rhs.level;
}
 