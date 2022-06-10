/* UPDATE 3 / 28 / 2022 - Harlow Huber
* The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
* This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
* put my changes below.All functionality will remain the same, or exceedingly similar.
* All previous code comments will remain, for now, as a reference.
*
* BUG FIXES 4 / 5 / 2022 - HARLOW HUBER
*	commented out code that depends on the formulalib library. this library is unfixeable at the time of writing and will be re-implemented later
*/

#ifndef __NVINPUT_MATH_H__
#define __NVINPUT_MATH_H__

#include "nvinput.h"
#include "framework.h"
// #include <fparse.h>

class __declspec(dllexport) nvinput_math_t : public nvinput_t
{
private:

protected:
	int nb_read;			// number of elements read
	int nb_max;				// number of elements to read
	bool random;			// is the sample random or not
	bool partial;			// is it partial ?
	size_t size;			// size of vectors

	// formula_parse_t formula; // the parsing formula object

public:
	nvinput_math_t(void);
	nvinput_math_t(nvinput_math_t& src);
	nvinput_math_t(const char* const _formula);
	nvinput_math_t& operator=(nvinput_math_t& src);
	~nvinput_math_t(void);

	void init(void);
	bool readnext(bit_vector_t& dest);
	void rewind(void);
	void close(void);
	size_t read_vector_size(void);
	bool eof(void);

	// particular to the test

	void set_randomize(bool rand) { random = rand; }
	void set_partial(bool part) { partial = part; }
	//void set_formula(const char* const _formula);
	void set_max_number(int nb) { nb_max = nb; }
	void set_size(size_t s) { size = s; }
};

#endif
