/* UPDATE 3 / 28 / 2022 - Harlow Huber
* The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
* This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
* put my changes below.All functionality will remain the same, or exceedingly similar.
* All previous code comments will remain, for now, as a reference.
*
* BUG FIXES 4 / 5 / 2022 - HARLOW HUBER
*	commented out code that depends on the formulalib library. this library is unfixeable at the time of writing and will be re-implemented later
*/

#include "nvinput_math.h"
#include <stdlib.h>
#include <winuser.h>


//***********************************************************************************************
// default constructor ... here do nothing
//***********************************************************************************************

nvinput_math_t::nvinput_math_t(void) :
	size(10), partial(false), nb_read(0), nb_max(1 << 10)
{
}

//***********************************************************************************************
// constructor using a formula string
//***********************************************************************************************

/*nvinput_math_t::nvinput_math_t(const char* const _formula) :
	size(10), partial(false), nb_read(0), nb_max(1 << 10)
{
	formula.set_str(_formula);
	formula.parse();
}

//***********************************************************************************************
// set the formula
//***********************************************************************************************

void nvinput_math_t::set_formula(const char* const _formula)
{
	formula.set_str(_formula);
	formula.parse();
}
//***********************************************************************************************
// copy contructor ... do nothing too 
//***********************************************************************************************

nvinput_math_t::nvinput_math_t(nvinput_math_t& src) :
	formula(src.formula)
{
	nb_read = src.nb_read;
	nb_max = src.nb_max;
	size = src.size;
	partial = src.partial;
	nb_read = 0;
	nb_max = src.nb_max;
}

//***********************************************************************************************
// Copy operator
//***********************************************************************************************

nvinput_math_t& nvinput_math_t::operator=(nvinput_math_t& src)
{
	nb_read = src.nb_read;
	nb_max = src.nb_max;
	size = src.size;
	formula = src.formula;
	return *this;
}
*/

//***********************************************************************************************
// destructor
//***********************************************************************************************

nvinput_math_t::~nvinput_math_t(void)
{
}

//***********************************************************************************************
// Initializate the object, for being ready to read ...
//***********************************************************************************************

void nvinput_math_t::init(void)
{
	nb_read = 0;
}

//***********************************************************************************************
// read the next element ... (here assume to be randomized)
//***********************************************************************************************


bool nvinput_math_t::readnext(bit_vector_t& dest)
{
	MessageBox(NULL, NULL, L"Sorry, readnext() not yet implemented", MB_OK);
	exit(-1);

	if (partial)
	{
		if (nb_read < nb_max)
		{
			if (random)
			{
				bit_vector_t vect(size, rand());
				dest = vect;
				nb_read++;
				//return formula.valueof(dest);

			}
			else {
				bit_vector_t vect(size, nb_read);
				dest = vect;
				nb_read++;
				//return formula.valueof(dest);
			}

		}
		else {
			return false;
		}
	}
	else {
		if (nb_read < (1 << size))
		{
			bit_vector_t vect(size, nb_read);
			dest = vect;
			nb_read++;
			//return formula.valueof(dest);
		}
		else return false;
	}

	return false;
}


//***********************************************************************************************
// rewind the reading ...
//***********************************************************************************************

void nvinput_math_t::rewind(void)
{
	nb_read = 0;
}

//***********************************************************************************************
// close the stream ...
//***********************************************************************************************

void nvinput_math_t::close(void)
{
}

//***********************************************************************************************
// return the bit vetor size contained in the input
//***********************************************************************************************

size_t nvinput_math_t::read_vector_size(void)
{
	return size;
}

//***********************************************************************************************
// return true if End Of Input is reached
//***********************************************************************************************

bool nvinput_math_t::eof(void)
{
	if (partial)
	{
		if (nb_read >= nb_max) return true;
		else return false;
	}
	else {
		if (nb_read >= (1 << size)) return true;
		else return false;
	}
}
