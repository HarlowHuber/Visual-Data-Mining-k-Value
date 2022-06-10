#include "nvinput.h"
#include <stdio.h>

class __declspec(dllexport) nvinput_ascii_file_t : public nvinput_t
{

private:

protected:
	FILE* infile;			// input file stream
	char* filename;		// filename ...

public:
	nvinput_ascii_file_t(void);
	nvinput_ascii_file_t(nvinput_ascii_file_t& src);
	nvinput_ascii_file_t(char* _filename);
	nvinput_ascii_file_t& operator=(nvinput_ascii_file_t& src);
	virtual ~nvinput_ascii_file_t(void);

	virtual void init(void);
	virtual bool readnext(bit_vector_t& dest) = 0;
	virtual void rewind(void);
	virtual void close(void);
	virtual size_t read_vector_size(void) = 0;
	virtual bool eof(void);
};


class __declspec(dllexport) nvinput_groupfile_t : public nvinput_ascii_file_t
{
protected:

	bool size_read;			// is the size read ?
	int nb_one;				// number of vector with value 1
	int nb_zero;			// the same for 0
	size_t size;			// size of the vectors

public:
	nvinput_groupfile_t(void) : size_read(false), nb_one(0), nb_zero(0), size(0), nvinput_ascii_file_t() {}
	nvinput_groupfile_t(nvinput_groupfile_t& src) : size_read(false), nb_one(0), nb_zero(0), size(0) {}
	nvinput_groupfile_t(char* filename) : size_read(false), nb_one(0), nb_zero(0), size(0), nvinput_ascii_file_t(filename) {}
	nvinput_groupfile_t& operator=(nvinput_groupfile_t& src) { return *this; }

	void rewind(void);
	bool readnext(bit_vector_t& dest);
	size_t read_vector_size(void);
};

class __declspec(dllexport) nvinput_vectfile_t : public nvinput_ascii_file_t
{
protected:
	bool size_read;			// is size read ?
	size_t size;			// size of the vectors ...

public:
	nvinput_vectfile_t(void) : size_read(false), size(0), nvinput_ascii_file_t() {}
	nvinput_vectfile_t(nvinput_vectfile_t& src) : size_read(false), size(0) {}
	nvinput_vectfile_t(char* filename) : size_read(false), size(0), ::nvinput_ascii_file_t(filename) {}
	nvinput_vectfile_t& operator=(nvinput_vectfile_t& src) { return *this; }

	bool readnext(bit_vector_t& dest);
	size_t read_vector_size(void);
};
