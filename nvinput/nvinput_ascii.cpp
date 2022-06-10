/* UPDATE 3 / 28 / 2022 - Harlow Huber
* The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
* This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
* put my changes below.All functionality will remain the same, or exceedingly similar.
* All previous code comments will remain, for now, as a reference.
*
* BUG FIXES 4 / 5 / 2022 - HARLOW HUBER
*	changed char* variables to LPCWSTR and vice versa because of incompatable parameter errors
*/

#include "nvinput_ascii.h"
#include <stdlib.h>

#ifndef LINUX_COMPILE
#include <windows.h>
#endif

//***********************************************************************************************
// default constructor
//***********************************************************************************************

nvinput_ascii_file_t::nvinput_ascii_file_t(void)
{
	inited = false;
	infile = NULL;
	filename = NULL;
}

//***********************************************************************************************
// copy contructor, only copy the filename to init after
//***********************************************************************************************

nvinput_ascii_file_t::nvinput_ascii_file_t(nvinput_ascii_file_t& src)
{
	inited = false;
	infile = NULL;
	filename = _strdup(src.filename);
}

//***********************************************************************************************
// Initialise with the name of the file, does not init the file
//***********************************************************************************************

nvinput_ascii_file_t::nvinput_ascii_file_t(char* _filename)
{
	inited = false;
	infile = NULL;
	filename = _strdup(_filename);
}
//***********************************************************************************************
// copy operator, only copy name of the file, must init after
//***********************************************************************************************

nvinput_ascii_file_t& nvinput_ascii_file_t::operator=(nvinput_ascii_file_t& src)
{
	if (infile) close();
	infile = NULL;
	filename = _strdup(src.filename);
	inited = false;
	return *this;
}

//***********************************************************************************************
// destructor, close the file if not done, free the filename
//***********************************************************************************************

nvinput_ascii_file_t::~nvinput_ascii_file_t(void)
{
	if (infile) close();
	infile = NULL;
	if (filename) free(filename);
}



//***********************************************************************************************
// initialize the file input
//***********************************************************************************************

void nvinput_ascii_file_t::init(void)
{
	if (inited) return; // Do not init twice if already called
	fopen_s(&infile, filename, "r");
	if (!infile)
	{
		char buffer[80];
		LPCWSTR buff_L = L"Error";
		LPCWSTR ws = L"File Opening Error";
		sprintf_s(buffer, sizeof(buffer), "Can't open file : %s", filename);
		::MessageBox(NULL, buff_L, ws, MB_OK | MB_ICONERROR);
	}
	inited = true;
}

//***********************************************************************************************
// Rewind the file (set pos to begining)
//***********************************************************************************************

void nvinput_ascii_file_t::rewind(void)
{
	if (infile)
	{
		::rewind(infile);
	}
}

//***********************************************************************************************
// close the file
//***********************************************************************************************

void nvinput_ascii_file_t::close(void)
{
	if (infile)
	{
		fclose(infile);
		infile = NULL;
	}
}

//***********************************************************************************************
// return the End Of File state of the file
//***********************************************************************************************

bool nvinput_ascii_file_t::eof(void)
{
	if (infile)
	{
		long int pos;
		bit_vector_t v;
		bool r = true;

		pos = ftell(infile);
		readnext(v);
		if (!feof(infile)) r = false;
		fseek(infile, pos, SEEK_SET);
		return r;
	}
	return true;
}

//***********************************************************************************************
// Read from a groupfile type
//***********************************************************************************************

bool nvinput_groupfile_t::readnext(bit_vector_t& dest)
{
	bit_vector_t v((size_t)0);

	if (infile && !feof(infile))
	{
		char buffer[256];
		if (!size_read) read_vector_size();
		if (fgets(buffer, 256, infile))
		{
			buffer[size] = '\0';
			bit_vector_t vect(buffer);
			dest = vect;
			if (nb_one > 0)
			{
				nb_one--;
				return true;
			}
			else  if (nb_zero > 0) {
				nb_zero--;
				return false;
			}
		}
	}
	dest = v;
	return false;
}

//***********************************************************************************************
// Read the vector_size from a group file
//***********************************************************************************************

void nvinput_groupfile_t::rewind(void)
{
	nvinput_ascii_file_t::rewind();
	size_read = false;
}

size_t nvinput_groupfile_t::read_vector_size(void)
{
	if (size_read) return size;
	char buffer[256];
	if (infile && fgets(buffer, 256, infile))
	{
		long int pos;
		if (sscanf_s(buffer, "%d %d", &nb_one, &nb_zero) != 2)
		{
			LPCWSTR ws1 = L"The file is corrupted";
			LPCWSTR ws2 = L"File Open Error";
			::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
			close();
			return 0;
		}
		pos = ftell(infile);
		if (fgets(buffer, 256, infile))
		{
			if (buffer[strlen(buffer) - 1] == '\n') size = strlen(buffer) - 1;
			else size = strlen(buffer);
			fseek(infile, pos, SEEK_SET);
			size_read = true;
			return size;
		}
	}
	return 0;
}

//***********************************************************************************************
// read from a vect file
//***********************************************************************************************

bool nvinput_vectfile_t::readnext(bit_vector_t& dest)
{
	// vector file type is the simpliest type of all
	// vector comes with value at the end, no space, just a \n at the end of each
	bit_vector_t vect((size_t)0);
	char buffer[256];
	bool r;
	if (infile)
	{
		memset(buffer, '\0', 256);
		if (!feof(infile))
		{
			if (fgets(buffer, 256, infile))
			{

				if (!size_read)
				{
					size = strlen(buffer);
					if (buffer[size - 1] == '\n') buffer[size - 1] = '\0';
					size = strlen(buffer) - 1;
				}
				else if (buffer[size - 1] == '\n') buffer[size] = '\0';

				r = (buffer[size] == '0') ? false : true;
				buffer[size] = '\0';

				bit_vector_t vect2(buffer);
				dest = vect2;
				return r;
			}
		}
	}

	dest = vect;
	return false;
}

//***********************************************************************************************
// read the vector_size from a vect file
//***********************************************************************************************
size_t nvinput_vectfile_t::read_vector_size(void)
{
	if (size_read) return size;
	if (infile)
	{
		long int pos;
		pos = ftell(infile);
		char buffer[256];

		if (fgets(buffer, 256, infile))
		{
			size = strlen(buffer);
			if (buffer[size - 1] == '\n') buffer[size - 1] = '\0';
			size = strlen(buffer) - 1;
			fseek(infile, pos, SEEK_SET);
			size_read = true;
			return size;
		}

		fseek(infile, pos, SEEK_SET);
	}
	return 0;
}
