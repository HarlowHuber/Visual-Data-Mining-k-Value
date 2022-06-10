#ifndef __NVINPUT_H__
#define __NVINPUT_H__


#include <bit_vector.h>

// This class is the input base class for the nvboolfunc 
// This is an ABC

class __declspec(dllexport) nvinput_t
{

private:

protected:
	bool inited;

public:
	nvinput_t(void) { inited = false; }
	nvinput_t(nvinput_t& src) {}
	nvinput_t& operator=(nvinput_t& src) { return *this; }
	virtual ~nvinput_t(void) {}

	virtual void init(void) = 0;
	virtual bool readnext(bit_vector_t& dest) = 0;
	virtual void rewind(void) = 0;
	virtual void close(void) = 0;
	virtual size_t read_vector_size(void) = 0;
	virtual bool eof(void) = 0;
};



#endif
