#include "nvboolfunc.h"
#include <hanselchainset.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>

//***********************************************************************************************
// Default constructor
//***********************************************************************************************

nvboolfunc_t::nvboolfunc_t(void) :
	input(NULL)
{
	size = 0;
	color_array = NULL;
	disk_data = NULL;
	is3d = false;
	my3d = false;
	plot3d = false;
	convert = false;
	highlightMonot = false;
	monotMode = false;
	compress = false;
	firstPos = true;
	height = 1.0f;
	is_hansel_sorted = false;
}

//***********************************************************************************************
// constructor by size ...
//***********************************************************************************************

nvboolfunc_t::nvboolfunc_t(size_t _size) :
	input(NULL),
	kv_attributes(_size, 2),
	all_vectors(_size + 1)
{
	size_t i;
	size = _size + 1;
	disk_data = NULL;
	is3d = false;
	my3d = false;
	plot3d = false;
	convert = false;
	highlightMonot = false;
	monotMode = false;
	firstPos = true;
	compress = false;
	height = 1.0f;
	is_hansel_sorted = false;

	color_array = new color_t * [size];

	for (i = 0; i < size; i++)
	{
		color_array[i] = new color_t[3];
		get_color_at(color_array[i][0], i, size);
		color_array[i][2].upacked = 0x00000000;
		color_array[i][1].upacked = 0xffffffff;
	}


	/*
		// Debug purpose, to replace that after
		if (size ==  11)
		{
			// Color palete ...
			color_array[10][0].upacked = 0xffffffff;
			color_array[9][0].upacked  = 0xffa8c6e5;
			color_array[8][0].upacked  = 0xff548eb2;
			color_array[7][0].upacked  = 0xff0056b2;
			color_array[6][0].upacked  = 0xff7fffff;
			color_array[5][0].upacked  = 0xff00e5e5;
			color_array[4][0].upacked  = 0xff7fe57f;
			color_array[3][0].upacked  = 0xff00cc00;
			color_array[2][0].upacked  = 0xffffff7f;
			color_array[1][0].upacked  = 0xffbf7f3f;
			color_array[0][0].upacked  = 0xff7f0000;
		}
	*/
	// Second we create the disk_datas but not any inodes ...

	// set size and disk data after max Hamming norm is determined
	disk_data = new disk_data_t[size];

	for (i = 0; i < size; i++)
	{
		disk_data[i].current.generic_pointer = NULL;
		disk_data[i].inode.generic_pointer = NULL;
		disk_data[i].parse_begun = false;
	}

	set_sizes();
}


//***********************************************************************************************
// Used to create the MDF shading
//***********************************************************************************************

void nvboolfunc_t::get_color_at(color_t& dest, int idx, int size)
{
	dest.unpacked.a = 0xff;
	if (size > 13)
	{
		dest.unpacked.r = 255;
		dest.unpacked.g = 255;
		dest.unpacked.b = 255;
		return;
	}
	dest.unpacked.r = get_red_at(idx, size);
	dest.unpacked.g = get_green_at(idx, size);
	dest.unpacked.b = get_blue_at(idx, size);
}

unsigned char nvboolfunc_t::get_blue_at(int idx, int size)
{

	float x;
	x = (float)idx / (float)(size - 1) * 10.0f + 1.0f;

	if (x <= 4.0f)
	{
		float c;
		c = -53.167f * x * x * x + 319.0f * x * x - 520.83f * x + 382.0f;
		return (c < 255.0f) ? (unsigned char)c : 255;
	}
	else if (x <= 6.0f) {
		x -= 3.0f;
		return (unsigned char)(-127.0f * x * x + 508.0f * x - 381.0f);
	}
	else if (x <= 8.0f) {
		x -= 5.0f;
		return (unsigned char)(-127.0f * x * x + 508.0f * x - 381.0f);
	}
	else {
		return (unsigned char)((x - 8.0f) * 255.0f / 3.0f);
	}
}

unsigned char nvboolfunc_t::get_green_at(int idx, int size)
{

	float x;
	x = (float)idx / (float)(size - 1) * 10.0f + 1.0f;

	if (x <= 3.0f)
	{
		return (unsigned char)(x * 255.0f / 3.0f);
	}
	else if (x <= 7.0f) {
		float c;
		x -= 2.0f;
		c = -4.1667f * x * x * x + 46.714f * x * x - 151.12f * x + 361.4f;
		return (c > 255.0f) ? 0xff : (unsigned char)c;
	}
	else {
		float c;
		x -= 6.0f;
		c = 9.4167f * x * x * x * x - 131.67f * x * x * x + 667.08f * x * x - 1389.8f * x + 1100.0f;
		return (c > 255.0f) ? 0xff : (unsigned char)c;
	}

}


unsigned char nvboolfunc_t::get_red_at(int idx, int size)
{
	float x;

	x = (float)idx / (float)(size - 1) * 10.0f + 1.0f;

	if (x < 7.0f)
	{
		if (x <= 3.0f)
		{
			return (unsigned char)((x - 1.0f) * 127.0f / 3.0f);
		}
		else if (x <= 4.0f) {
			return (unsigned char)((3.0f - x) * 127.0f);
		}
		else if (x <= 6.0f) {
			return (unsigned char)((x - 4.0f) * 229.0f / 2.0f);
		}
		else {
			return (unsigned char)((x - 6.0f) * 26.0f + 229.0f);
		}
	}
	else {
		float c;
		x -= 6.0f;

		c = -8.5f * x * x * x + 94.857f * x * x - 305.64f * x + 475.0f;
		return (c >= 255.0f) ? 0xff : (unsigned char)c;
	}

}

//***********************************************************************************************
// Copy constructor
//***********************************************************************************************

nvboolfunc_t::nvboolfunc_t(const nvboolfunc_t& src) :
	input(NULL)
{
	size_t i;

	size = src.size;
	height = src.height;

	is_hansel_sorted = src.is_hansel_sorted;

	color_array = new color_t * [size];
	for (i = 0; i < size; i++)
	{
		color_array[i] = new color_t[3];
	}

	disk_data = new disk_data_t[size];
	for (i = 0; i < size; i++)
	{
		if (!is3d)
		{
			if (src.disk_data[i].inode.inode2d)
			{
				data_inode2d_t* cur1, * cur, * tmp;
				disk_data[i].current.generic_pointer = NULL;
				disk_data[i].parse_begun = false;
				disk_data[i].inode.inode2d = new data_inode2d_t;


				*disk_data[i].inode.inode2d = *src.disk_data[i].inode.inode2d;

				cur1 = disk_data[i].inode.inode2d;
				cur = src.disk_data[i].inode.inode2d->next;

				while (cur)
				{
					tmp = new data_inode2d_t;
					tmp = cur;
					tmp->bit_vector = cur->bit_vector;
					cur1->next = tmp;
					cur1 = tmp;
					cur = cur->next;
				}


			}
		}
		else {
			if (src.disk_data[i].inode.inode3d)
			{
				data_inode3d_t* cur1, * cur, * tmp;
				disk_data[i].inode.inode3d = new data_inode3d_t;
				*disk_data[i].inode.inode3d = *src.disk_data[i].inode.inode3d;
				cur1 = disk_data[i].inode.inode3d;
				cur = src.disk_data[i].inode.inode3d->next;

				while (cur)
				{
					tmp = new data_inode3d_t;
					tmp = cur;
					cur1->next = tmp;
					cur1 = tmp;
					cur = cur->next;
				}


			}
		}

		color_array[i][0].packed = src.color_array[i][0].packed;
		color_array[i][1].packed = src.color_array[i][1].packed;
		color_array[i][2].packed = src.color_array[i][2].packed;
	}

}

//***********************************************************************************************
// Copy operator
//***********************************************************************************************

nvboolfunc_t& nvboolfunc_t::operator=(const nvboolfunc_t& src)
{
	size_t i;

	if (disk_data) delete_diskdata();

	if (src.size != size)
	{

		if (color_array)
		{
			for (i = 0; i < size; i++)
			{
				if (color_array[i]) delete[](color_array);
			}
			delete[](color_array);
		}

		color_array = new color_t * [size];
		for (i = 0; i < src.size; i++)
		{
			color_array[i] = new color_t[3];
		}
	}

	size = src.size;
	height = src.height;

	disk_data = new disk_data_t[size];
	for (i = 0; i < size; i++)
	{
		if (!is3d)
		{
			if (src.disk_data[i].inode.inode2d)
			{
				data_inode2d_t* cur1, * cur, * tmp;
				disk_data[i].inode.inode2d = new data_inode2d_t;
				disk_data[i].current.generic_pointer = NULL;
				disk_data[i].parse_begun = false;

				*disk_data[i].inode.inode2d = *src.disk_data[i].inode.inode2d;

				cur1 = disk_data[i].inode.inode2d;
				cur = src.disk_data[i].inode.inode2d->next;

				while (cur)
				{
					tmp = new data_inode2d_t;
					tmp = cur;
					tmp->bit_vector = cur->bit_vector;
					cur1->next = tmp;
					cur1 = tmp;
					cur = cur->next;
				}


			}
		}
		else {
			if (src.disk_data[i].inode.inode3d)
			{
				data_inode3d_t* cur1, * cur, * tmp;
				disk_data[i].inode.inode3d = new data_inode3d_t;
				*disk_data[i].inode.inode3d = *src.disk_data[i].inode.inode3d;
				cur1 = disk_data[i].inode.inode3d;
				cur = src.disk_data[i].inode.inode3d->next;

				while (cur)
				{
					tmp = new data_inode3d_t;
					tmp = cur;
					cur1->next = tmp;
					cur1 = tmp;
					cur = cur->next;
				}


			}
		}

		color_array[i][0].packed = src.color_array[i][0].packed;
		color_array[i][1].packed = src.color_array[i][1].packed;
		color_array[i][2].packed = src.color_array[i][2].packed;
	}


	is_hansel_sorted = src.is_hansel_sorted;

	return *this;
}

//***********************************************************************************************
// Destructor
//***********************************************************************************************

nvboolfunc_t::~nvboolfunc_t(void)
{
	size_t i;

	if (disk_data) delete_diskdata();

	if (color_array)
	{
		for (i = 0; i < size; i++)
		{
			if (color_array[i]) delete[](color_array);
		}
		delete[](color_array);
	}

	color_array = NULL;
}

//***********************************************************************************************
// Delete the memory taken by the disk_data objects ...
//***********************************************************************************************


void nvboolfunc_t::delete_diskdata(void)
{
	size_t i;

	if (disk_data)
	{
		for (i = 0; i < size; i++)
		{
			if (!is3d)
			{
				if (disk_data[i].inode.inode2d)
				{
					data_inode2d_t* cur, * tmp;
					cur = tmp = disk_data[i].inode.inode2d;
					while (!cur)
					{
						tmp = cur;
						cur = cur->next;
						delete(tmp);
					}

				}
			}
			else {
				if (disk_data[i].inode.inode3d)
				{
					data_inode3d_t* cur, * tmp;
					cur = tmp = disk_data[i].inode.inode3d;
					while (!cur)
					{
						tmp = cur;
						cur = cur->next;
						delete(tmp);
					}
				}
			}
		}
		delete(disk_data);
	}
	is_hansel_sorted = false;
	disk_data = NULL;
}

//***********************************************************************************************
// factorial function, needed to calculate the proper size
//***********************************************************************************************

int nvboolfunc_t::factorial(int n)
{
	int r = 1;

	for (int i = 1; i <= n; i++)
	{
		r = r * i;
	}

	return r;
}

//***********************************************************************************************
// Combinate function needed to calculate the proper size too
// could be improve in the future 
//***********************************************************************************************

int nvboolfunc_t::ncr(int n, int r)
{
	return factorial(n) / (factorial(r) * factorial(n - r));
}

//***********************************************************************************************
// Function set size used by the contructors etc... 
// make sure the disk_data is allocated before calling
// set the size of each disks ( assume symetry ...)
//***********************************************************************************************
void nvboolfunc_t::set_sizes(void)
{
	size_t i;

	if (disk_data)
	{
		for (i = 0; i <= (size >> 1); i++)
		{
			disk_data[i].xsize = disk_data[size - i - 1].xsize = ncr(size - 1, i);
		}
	}
}

//***********************************************************************************************
// Return the maximum size of the disk.
//***********************************************************************************************

int nvboolfunc_t::get_max_xsize(void)
{
	if (!disk_data) return ncr(size - 1, (size - 1) >> 1);
	else return disk_data[size >> 1].xsize;
}

//***********************************************************************************************
// return the size of the disk if existing, 0 if not
//***********************************************************************************************
int nvboolfunc_t::get_xsize(size_t i)
{
	if (!disk_data || i >= size) return 0;
	else return disk_data[i].xsize;
}

//***********************************************************************************************
// Return a reference on the color of the disk
//***********************************************************************************************


const color_t& nvboolfunc_t::get_disk_color(size_t i)
{

	if (color_array && i < size && color_array[i])
	{
		return color_array[i][0];
	}
	else {
		return c;
	}

}

//***********************************************************************************************
// return the color associated to the value and disk
//***********************************************************************************************

const color_t& nvboolfunc_t::get_val_color(size_t i, bool val)
{

	if (color_array && i < size && color_array[i])
	{
		if (val) return color_array[i][2];
		else return color_array[i][1];
	}
	else {
		return c;
	}

}

//***********************************************************************************************
// Change the 3d mode.
//***********************************************************************************************
void nvboolfunc_t::set3d(bool draw3d)
{
	//is3d = draw3d;
	my3d = draw3d;
}


//***********************************************************************************************
// Toggle the 3d mode.
//***********************************************************************************************
void nvboolfunc_t::toggle3d(void)
{
	//is3d = !is3d;
	my3d = !my3d;
}


//***********************************************************************************************
// set the input pointer, and automatically start the reading of data
//***********************************************************************************************

void nvboolfunc_t::set_input(const nvinput_t* const _input)
{
	input = (nvinput_t*)_input;

	if (input)
	{
		bool r;
		unsigned int inputsize;

		input->init();

		// to be changed for dynamic size changing
		if ((inputsize = input->read_vector_size()) > 14)
		{
			LPCWSTR ws1 = L"Vector Size over than 14\n is not yet implemented";
			LPCWSTR ws2 = L"Sorry";
			::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
			input->close();
			return;
		}

		if (inputsize != size - 1)
		{
			LPCWSTR ws1 = L"input is not the correct size";
			LPCWSTR ws2 = L"Sorry but ...";
			::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
			input->close();
			return;
		}

		bit_vector_t vect(inputsize);
		input->rewind();

		// parse file for kv_attributes
		while (!input->eof())
		{
			input->readnext(vect);

			// calculate the k-value for each attribute
			for (int i = 0; i < inputsize; i++)
			{
				if (vect[i] + 1 > kv_attributes[i])
				{
					kv_attributes[i] = vect[i] + 1;
				}
			}
		}

		//	generate all combos of vectors
		//	iterate over every k-value attribute
		bit_vector_t max_vector(inputsize);
		int max_hamming_norm = 0;

		for (int i = 0; i < inputsize; i++)
		{
			max_vector[i] = kv_attributes[i] - 1;
			max_hamming_norm += max_vector[i];
		}

		calculate_all_vectors(max_vector, max_hamming_norm, 0);

		// create the disk_datas but not any inodes ...
		// set size and disk data after max Hamming norm is determined
		delete[] disk_data;
		size = max_hamming_norm + 1;
		disk_data = new disk_data_t[size];

		for (int i = 0; i < size; i++)
		{
			disk_data[i].current.generic_pointer = NULL;
			disk_data[i].inode.generic_pointer = NULL;
			disk_data[i].parse_begun = false;
		}

		set_sizes();

		// reset file position pointer
		input->rewind();

		// parse file again to store vectors vectors
		while (!input->eof())
		{
			r = input->readnext(vect);

			if (!safe_store(vect, r)) // store real element (vector). r is the value (true or false/black or white)
			{
				LPCWSTR ws1 = L"Error storing datas, I stop there";
				LPCWSTR ws2 = L"Storing error";
				::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
				input->close();
				return;
			}
		}

		is_hansel_sorted = false;
	}
}

//***********************************************************************************************
// store a bit of data
//***********************************************************************************************

void* nvboolfunc_t::store_inode(bit_vector_t& vect, bool value, bool is_fake)
{
	int i = vect.getlevel();

	// let's find if there is some data 

	if (!disk_data[i].inode.generic_pointer)
	{
		//if (!is3d)
		//{
			data_inode2d_t* tmp;
			tmp = new data_inode2d_t;
			tmp->bit_vector = vect;
			tmp->is_fake = is_fake;
			tmp->next = NULL;
			tmp->chain_up = tmp->chain_dn = NULL;
			tmp->chain_len = 0;
			tmp->chain_nb = -1;
			tmp->value = value;
			tmp->xpos = (disk_data[i].xsize & 1) ? 0.0f : -0.5f;
			blank_2dinode(tmp);
			tmp->parsed = false;

			disk_data[i].inode.inode2d = tmp;
			return (void*)tmp;
		//}
		/*else {
			LPCWSTR ws1 = L"3d is not yet implemented";
			LPCWSTR ws2 = L"Sorry";
			::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
			return NULL;
		}*/
	}
	else {
		if (!is3d)
		{
			data_inode2d_t* tmp;
			tmp = new data_inode2d_t;
			tmp->bit_vector = vect;
			tmp->is_fake = is_fake;
			tmp->next = disk_data[i].inode.inode2d;
			tmp->value = value;
			tmp->xpos = (disk_data[i].xsize & 1) ? 0.0f : -0.5f;
			blank_2dinode(tmp);
			tmp->placed = false;
			tmp->parsed = false;
			disk_data[i].inode.inode2d = tmp;


			return (void*)tmp;
		 }
		/*else {
			LPCWSTR ws1 = L"3d is not yet implemented";
			LPCWSTR ws2 = L"Sorry";
			::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
			return NULL;
		}*/
	}

	return NULL;
}

//***********************************************************************************************
// function used to read all the datas of the disk i NULL if error or end
//***********************************************************************************************

/*
void * nvboolfunc_t::get_next_inode(size_t i)
{
	void * r;
	if (i<size)
	{
		if (disk_data)
		{
			if (r = disk_data[i].current.generic_pointer)
			{
				if (is3d)
					disk_data[i].current.inode3d = disk_data[i].current.inode3d->next;
				else
					disk_data[i].current.inode2d = disk_data[i].current.inode2d->next;
				disk_data[i].parse_begun = true;
				return r;
			}
			else if (disk_data[i].inode.generic_pointer && !disk_data[i].parse_begun)
			{
				disk_data[i].current.generic_pointer = disk_data[i].inode.generic_pointer;
				return disk_data[i].current.generic_pointer;
			}
		}
	}
	return NULL;

}
*/
void* nvboolfunc_t::get_next_inode(size_t i)
{
	void* r;

	if (i < size)
	{
		if (disk_data)
		{
			if (r = disk_data[i].current.generic_pointer) // if parsing has already started 
			{
				if (is3d)
					disk_data[i].current.inode3d = disk_data[i].current.inode3d->next;
				else
					disk_data[i].current.inode2d = disk_data[i].current.inode2d->next;

				disk_data[i].parse_begun = true;

				return r; // return pointer to current node of disk_data
			}
			else if (disk_data[i].inode.generic_pointer && !disk_data[i].parse_begun) // if parsing has not begun
			{
				//Set current item pointed at to the head of the LL.
				disk_data[i].current.generic_pointer = disk_data[i].inode.generic_pointer;

				return disk_data[i].current.generic_pointer; // return pointer to current node of disk_data
			}
		}
	}

	return NULL;
}



//***********************************************************************************************
// rewind the disk
//***********************************************************************************************

void nvboolfunc_t::rewind(size_t i)
{
	if (i < size)
	{
		if (disk_data)
		{
			disk_data[i].current.generic_pointer = NULL;
			disk_data[i].parse_begun = false;
		}
	}
}

//***********************************************************************************************
// sort the items using their values
//***********************************************************************************************

void nvboolfunc_t::little_sort(void)
{

	if (!disk_data) return;

	if (!is3d)
	{
		size_t lvl; // level of disk
		size_t* p = new size_t[size - 1];
		size_t i, j, nb = 0;
		bit_vector_t v0(size - 1, 0);	// vector initialized with all zeros
		bit_vector_t biggest_vector(size - 1);	// the biggest vector for a particular Hamming Norm
		generic_inode_t cur;

		for (lvl = 0; lvl < size; lvl++)
		{
			nb = 0;

			if (disk_data[lvl].inode.generic_pointer) // checks if there is data for the current disk
			{
				rewind(lvl);

				for (size_t k = 0; k < all_vectors[lvl].size(); k++)
				{
					rewind(lvl);

					while (cur.generic_pointer = get_next_inode(lvl)) // while there is an inode
					{
						if (cur.inode2d->bit_vector == all_vectors[lvl][k])
						{
							cur.inode2d->xpos = -((float)k) + ((float)disk_data[lvl].xsize) / 2.0f - 0.5f;
							break;
						}
					}
				}

				//rewind(lvl);

				/*while (cur.generic_pointer = get_next_inode(lvl))
				{
					if (cur.inode2d->bit_vector == biggest_vector)
					{
						cur.inode2d->xpos = -((float)nb) + ((float)disk_data[lvl].xsize) / 2.0f - 0.5f;
						break;
					}
				}*/

				
			}
		}


		/*for (lvl = 0; lvl < size; lvl++)
		{
			nb = 0;

			if (disk_data[lvl].inode.generic_pointer) // checks if there is data for the current disk
			{
				// init
				biggest_vector = v0;

				for (j = 0; j < lvl; j++)
				{
					p[j] = j;
					biggest_vector[p[j]] = true; // biggest bit vector for disk
				}

				rewind(lvl); 

				while (cur.generic_pointer = get_next_inode(lvl)) // while there is an inode
				{
					if (cur.inode2d->bit_vector == biggest_vector)
					{
						cur.inode2d->xpos = ((float)disk_data[lvl].xsize) / 2.0f - 0.5f;
						break;
					}
				}

				if (lvl != 0)
				{
					i = 0;

					FILE* fp;

					//AllocConsole();
					//freopen_s(&fp, "CONIN$", "r", stdin);
					//freopen_s(&fp, "CONOUT$", "w", stdout);
					//freopen_s(&fp, "CONOUT$", "w", stderr);

					while (p[lvl - 1] < size - 1)
					{
						biggest_vector = v0;

						if (i < (lvl - 1) && p[i] == p[i + 1] - 1)
						{
							i++;
						}
						else
						{
							p[i]++;

							if (p[lvl - 1] < size - 1)
							{
								nb++;

								for (j = 0; j < i; j++)
									p[j] = j;

								for (j = 0; j < lvl; j++)
									biggest_vector[p[j]] = true; 

								std::cout << "Biggest vector: ";
								biggest_vector.print();
								std::cout << "Number: " << nb << std::endl;

								i = 0;
								rewind(lvl);

								while (cur.generic_pointer = get_next_inode(lvl))
								{
									//std::cout << "Current vector: ";
									//cur.inode2d->bit_vector.print();
									if (cur.inode2d->bit_vector == biggest_vector)
									{
										cur.inode2d->xpos = -((float)nb) + ((float)disk_data[lvl].xsize) / 2.0f - 0.5f;
										break;
									}
								}
							}
						}
					}
				}
			}
		}*/

		delete[] p;
	}
}

//***********************************************************************************************
// blank all the informations of an inode (non including position)
//***********************************************************************************************

void nvboolfunc_t::blank_2dinode(data_inode2d_t* inode, bool free_mem)
{
	if (inode)
	{

		inode->nb_bush = -1;
		inode->placed = false;
		inode->mexp = false;
		//My Change.
		//inode->next = NULL;
		/*
		inode->placed = false;
		inode->bush_parent1 = NULL;
		inode->bush_parent2 = NULL;
		if (free_mem && inode->bush_childs && inode->nb_childs > 0)
			delete[](inode->bush_childs);

		if (free_mem && inode->bush_array) delete_bush_array(inode->bush_array);
		inode->bush_array = NULL;

		inode->bush_childs = NULL;
		inode->nb_childs = 0;
		inode->bush_state = 0;
		inode->order1 = inode->order2 = 0;
		*/
	}
}

//***********************************************************************************************
//  blank all the inodes of all disks, to be used before searching for trees
//***********************************************************************************************

void nvboolfunc_t::blank_all_inodes(bool free_mem)
{
	if (!is3d)
	{
		size_t i;
		data_inode2d_t* cur;

		if (disk_data)
		{
			for (i = 0; i < size; i++)
			{
				if (disk_data[i].inode.generic_pointer)
				{
					cur = disk_data[i].inode.inode2d;
					while (cur)
					{
						blank_2dinode(cur, free_mem);
						cur = cur->next;
					}
				}
			}
		}
	}
	else {
		// not yet implemented
	}
}

//***********************************************************************************************
// Store the inode, if and only if it is not yet present in the structure, return
// a pointer on the stored inode, must be converted using the genreic_inode_t union
//***********************************************************************************************

void* nvboolfunc_t::safe_store(bit_vector_t& vect, bool value, bool is_fake, bool addit)
{
	if (disk_data)
	{

		int i;
		i = vect.getlevel();

		if (disk_data[i].inode.generic_pointer)
		{
			if (!is3d)
			{
				data_inode2d_t* cur = disk_data[i].inode.inode2d;
				while (cur && cur->bit_vector != vect) cur = cur->next; // if cur->bit_vector is equal to vect, then do not store

				if (!cur && addit)
				{
					return store_inode(vect, value, is_fake);
				}
				else return (void*)cur;
			}
			else {
				// not yet done
			}
		}
		else
		{
			return store_inode(vect, value, is_fake);
		}
	}

	return NULL;
}

//***********************************************************************************************
// add the child to the child list of the inode
//***********************************************************************************************

/*
void nvboolfunc_t::add_child(generic_inode_t& inode, generic_inode_t * child)
{

	if (inode.generic_pointer && child)
	{
		if (!is3d)
		{
			if (!inode.inode2d->bush_childs && inode.inode2d->nb_childs>0)
			{
				inode.inode2d->bush_childs = new data_inode2d_t*[inode.inode2d->nb_childs+1];
			} else {
				data_inode2d_t ** tmp = new data_inode2d_t*[inode.inode2d->nb_childs+1];
				memcpy(tmp, inode.inode2d->bush_childs, (inode.inode2d->nb_childs)*sizeof(data_inode2d_t*));
				delete[](inode.inode2d->bush_childs);
				inode.inode2d->bush_childs = tmp;
			}

			inode.inode2d->bush_childs[inode.inode2d->nb_childs++] = child->inode2d;
		} else {
			//not yet done
		}
	}
}
*/
//***********************************************************************************************
// delete all the fake elements, assume that the elements has been blanked before
//***********************************************************************************************

void nvboolfunc_t::clear_fake(void)
{
	if (!is3d)
	{
		data_inode2d_t* cur, ** last, * tmp;
		size_t i;
		cur = tmp = NULL;
		last = NULL;
		if (disk_data)
		{
			for (i = 0; i < size; i++)
			{
				if (disk_data[i].inode.inode2d)
				{
					tmp = cur = disk_data[i].inode.inode2d;
					last = &disk_data[i].inode.inode2d;
					while (cur)
					{
						if (cur->is_fake)
						{
							tmp = cur;
							cur = cur->next;
							*last = cur;
							delete(tmp);
						}
						else {
							last = &cur->next;
							cur = cur->next;
						}
					}
				}
			}
		}
	}
	else {
		// not yet done
	}
}


//***********************************************************************************************
// execute the overall procedure of the bush sort
// assume no collision on the begining (launch solve_collision for that before
//  ---------------------------------------------------------------------------
// This function does not move the elements anymore, but just create the tree and
// select the bush. (only a viewing function)
//***********************************************************************************************

void nvboolfunc_t::bush_sort(size_t lvl, float xpos)
{
	if (lvl < size)
	{
		if (!is3d)
		{
			data_inode2d_t* cur;
			cur = get_inode(xpos, lvl);
			if (cur)
			{
				clear_fake();
				blank_all_inodes(true); // should be changed by a selective blank

				cur->nb_bush = 1;
				internal_bush_tree(cur);

			}
		}
		else {
			// not yet done
		}
	}
}

//***********************************************************************************************
// does sort the datas so that it shows the bushes
//***********************************************************************************************

void nvboolfunc_t::internal_bush_tree(data_inode2d_t* startpoint)//, int lvl, bush_array_t * base_array)
{
	if (!disk_data || !startpoint) return;
	if (!is3d)
	{

		size_t k; // we only add one 1 so we need to store only one place
		size_t nb = 0;
		bit_vector_t v(startpoint->bit_vector);
		generic_inode_t cur; //, tmp;
		bit_vector_t sv = startpoint->bit_vector;
		// bush_array_t * the_array = NULL;


//		the_array = (!base_array) ? startpoint->bush_array : base_array;

		if ((size_t)sv.getlevel() == size - 1) return; // here add the double direction

		// first generate the up level of the potential bush

		for (k = 0; k < size - 1; k++)
		{
			// init
			v = sv;
			if (!sv[k])
			{
				nb++;
				v[k] = true;
				if ((cur.generic_pointer = safe_store(v, true, true)) == NULL) return;

				if (cur.inode2d->nb_bush != startpoint->nb_bush)
				{
					cur.inode2d->nb_bush = startpoint->nb_bush;
					if (cur.inode2d->value)
						internal_bush_tree(cur.inode2d); // should add the double direction
				}
				/*
				if (!(cur.inode2d->bush_state & BUSH_REG_STATE))
				{
					cur.inode2d->bush_state |= IS_BUSH1_REG;
					cur.inode2d->bush_parent1 = startpoint;
					cur.inode2d->order1 = nb;
					tmp.inode2d = startpoint;
					add_child(tmp, &cur);
					//add_bush_node(the_array, cur, lvl + 1);
					if (cur.inode2d->value) internal_bush_tree(cur.inode2d, true);//, lvl + 1, the_array); // add double direction
				} else if ((cur.inode2d->bush_state & BUSH_REG_STATE) == IS_BUSH1_REG) {
					cur.inode2d->bush_state |= IS_BUSH2_REG;
					cur.inode2d->bush_parent2 = startpoint;
					cur.inode2d->order2 = nb;
					tmp.inode2d = startpoint;
					add_child(tmp, &cur);
				};
				*/

			}
		}
	}
}

//***********************************************************************************************
// return the vector located at xpos, lvl return false if nothing
//***********************************************************************************************

bool nvboolfunc_t::get_vectdata(float xpos, size_t lvl, bit_vector_t& vect, bool& r)
{
	data_inode2d_t* inode;
	inode = get_inode(xpos, lvl);
	if (!inode) return false;
	vect = inode->bit_vector;
	r = inode->value;
	return true;
}

//***********************************************************************************************
// return the inode at pos xpos, lvl, NULL if nothing
//***********************************************************************************************


data_inode2d_t* nvboolfunc_t::get_inode(float xpos, size_t lvl)
{
	if (lvl > size)
		return NULL;

	data_inode2d_t* cur = disk_data[lvl].inode.inode2d;


	while (cur)
	{
		try
		{
			if (fabs(cur->xpos - xpos) <= 0.5)
			{

				return cur;
				break;
			}
		}
		catch (...)
		{
		}
		cur = cur->next;

	}
	return NULL;
}

//***********************************************************************************************
// return the needed offset for viewing the tree
//***********************************************************************************************

float nvboolfunc_t::get_offset(data_inode2d_t* node, float xpos, bool left)
{
	float offset = 0.0f, offsetc = 0.0f;//, offset2;

	// there is the second implementation of the get_offset function, using
	// the bush_array (no longer recursive and so quicker, more reliable

//	int i;
//	float xpos1;

	if (left)
	{
		if (xpos < -((float)disk_data[node->bit_vector.getlevel()].xsize) / 2.0f)
			offset = -((float)disk_data[node->bit_vector.getlevel()].xsize) / 2.0f - xpos;
		/*
				for (i = 0; i < node->bush_array->nb_level)
				{
					xpos1 = xpos - ((float)node->nb_childs)/2.0f + ((float)i) + offset;
				}
		*/
	}
	else {
		if (xpos > ((float)disk_data[node->bit_vector.getlevel()].xsize) / 2.0f)
			offset = ((float)disk_data[node->bit_vector.getlevel()].xsize) / 2.0f - xpos;


	}


	/*
	// there is the implementation only using the bush_tree (child/parents)
	// not up to date (but kept as comments, we never know ...
	if (node)
	{
		if (left)
		{
			size_t i;
			float xpos1;
			if (xpos < -((float)disk_data[node->bit_vector.getlevel()].xsize)/2.0f)
				offset = -((float)disk_data[node->bit_vector.getlevel()].xsize)/2.0f - xpos;

			if (node->nb_childs != 0 && node->bush_childs)
			{
				for (i=0; i<node->nb_childs; i++)
				{
					xpos1 = xpos - ((float)node->nb_childs)/2.0f + ((float)i) + offset;
					if (node->bush_childs[i] && (offset2 = get_offset(node->bush_childs[i], xpos1, true)) > offsetc)
						offsetc = offset2;
				}
				offset += offsetc;
			}
		} else {
			size_t i;
			float xpos1;
			if (xpos > ((float)disk_data[node->bit_vector.getlevel()].xsize)/2.0f)
				offset = ((float)disk_data[node->bit_vector.getlevel()].xsize)/2.0f - xpos;

			if (node->nb_childs != 0 && node->bush_childs)
			{
				for (i=0; i<node->nb_childs; i++)
				{
					xpos1 = xpos - ((float)node->nb_childs)/2.0f + ((float)i) + offset;
					if (node->bush_childs[i] && (offset2 = get_offset(node->bush_childs[i], xpos1, false)) < offsetc)
						offsetc = offset2;
				}
				offset += offsetc;
			}
		}
	}
	*/

	return offset;
}


//***********************************************************************************************
// set the position given the position of the root (recursive function)
//***********************************************************************************************

/*
void nvboolfunc_t::set_bush_pos(data_inode2d_t * node)
{
	if (node && node->nb_childs > 0 && node->bush_childs)
	{
		unsigned i;
		for (i = 0; i < node->nb_childs ; i++)
		{
			if (node->bush_childs[i])
			{
				node->bush_childs[i]->xpos = node->xpos - ((float)node->nb_childs)/2.0f + ((float)i);
				set_bush_pos(node->bush_childs[i]);
			}
		}
	}
}
*/
//***********************************************************************************************
//  Solve the placing collisions
// Basically reorder data so that there is no more collisions
//***********************************************************************************************

void nvboolfunc_t::solve_collision(void)
{
	if (disk_data)
	{
		blank_parse_all();
		size_t i;
		for (i = 0; i < size; i++)
		{
			if (disk_data[i].inode.inode2d)
			{
				float pos;
				poslist_t* freelist = NULL;
				poslist_t* busylist = NULL;
				poslist_t* collision_list = NULL;

				for (pos = -((float)disk_data[i].xsize) / 2.0f + 0.5f; pos <= ((float)disk_data[i].xsize) / 2.0f; pos += 1.0f)
				{
					data_inode2d_t* node = NULL;

					node = get_inode_once(pos, i);

					do
					{
						if (!node)
						{
							if (collision_list)
							{
								collision_list->node->xpos = pos;
								collision_list = delete_head(collision_list);
							}
							else {
								freelist = poslist_add_head(pos, freelist);
							}
						}
						else {
							poslist_t* node2;
							node2 = poslist_find(pos, busylist);
							if (!node2)
							{
								busylist = poslist_add_head(node, busylist);
							}
							else {
								if (node->placed)
								{
									if (node2->node->placed)
									{
										LPCWSTR ws1 = L"Unsolvable master/master collision";
										LPCWSTR ws2 = L"Collision error";
										::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
										poslist_delete(freelist);
										poslist_delete(busylist);
										poslist_delete(collision_list);
										return;
									}
									else {
										poslist_swap(node2, &node);
									}
								}
								if (freelist)
								{
									node->xpos = freelist->emphasis.pos;
									freelist = delete_head(freelist);
								}
								else {
									collision_list = poslist_add_head(node, collision_list);
								}
							}
						}
					} while (node = get_inode_once(pos, i));
				}

				poslist_delete(busylist);
				poslist_delete(freelist);
				if (collision_list)
				{
					LPCWSTR ws1 = L"Collision not solved,\nnot enought space in disk(!)";
					LPCWSTR ws2 = L"Collision error";
					::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
					poslist_delete(collision_list);
				}

			}
		}
	}
}


//***********************************************************************************************
// add to the head of a poslist
//***********************************************************************************************

poslist_t* nvboolfunc_t::poslist_add_head(data_inode2d_t* pos, poslist_t* list)
{
	poslist_t* tmp;
	if (pos)
	{
		tmp = new poslist_t;
		tmp->node = pos;
		tmp->next = list;
		tmp->emphasis.pos = pos->xpos;
		return tmp;
	}
	else return list;
}

poslist_t* nvboolfunc_t::poslist_add_head(float pos, poslist_t* list)
{
	poslist_t* tmp;
	tmp = new poslist_t;
	tmp->node = NULL;
	tmp->next = list;
	tmp->emphasis.pos = pos;
	return tmp;
}

//***********************************************************************************************
// delete the head of the list
//***********************************************************************************************

poslist_t* nvboolfunc_t::delete_head(poslist_t* list)
{
	if (list)
	{
		poslist_t* tmp = list->next;
		delete list;
		return tmp;
	}
	else return NULL;
}

//***********************************************************************************************
// swap the value node and the one wich is present in the list item
//***********************************************************************************************

void nvboolfunc_t::poslist_swap(poslist_t* list, data_inode2d_t** node)
{
	if (list && node)
	{
		data_inode2d_t* tmp;
		tmp = list->node;
		list->node = *node;
		*node = tmp;
		list->emphasis.pos = (*node)->xpos;
	}
}

//***********************************************************************************************
// find the given pos in the list 
//***********************************************************************************************

poslist_t* nvboolfunc_t::poslist_find(float pos, poslist_t* list)
{
	if (list)
	{
		poslist_t* cur = list;
		while (cur)
		{
			if (fabs(cur->emphasis.pos - pos) < 0.5f) return cur;
			cur = cur->next;
		}
	}
	return NULL;
}

//***********************************************************************************************
// delete the entire list
//***********************************************************************************************

void nvboolfunc_t::poslist_delete(poslist_t* list)
{
	poslist_t* lst = list;
	while (lst = delete_head(lst));
}

//***********************************************************************************************
// insert just after the element, create the element, and return the modified list
//***********************************************************************************************

poslist_t* nvboolfunc_t::insert_after(poslist_t* list, poslist_t* pos, data_inode2d_t* node, int val)
{

	if (!list)
	{
		poslist_t* tmp;
		if (tmp = poslist_add_head(node, list))
		{
			tmp->emphasis.val = val;
		}
		return tmp;
	}
	else {
		poslist_t* next;
		next = pos->next;
		if (!(next = poslist_add_head(node, next))) return NULL;
		pos->next = next;
		next->emphasis.val = val;
		return list;
	}
	return NULL;
}

//***********************************************************************************************
// insert regarding to the value order (in an increasing sort)
//***********************************************************************************************

poslist_t* nvboolfunc_t::insert_sorted(poslist_t* list, data_inode2d_t* node, int val)
{
	if (!list)
	{
		return insert_after(list, list, node, val);
	}
	else {
		if (list->emphasis.val < val)
		{
			poslist_t* cur = list;
			while (cur && cur->next && cur->next->emphasis.val < val) cur = cur->next;
			return insert_after(list, cur, node, val);
		}
		else {
			poslist_t* tmp;
			tmp = poslist_add_head(node, list);
			tmp->emphasis.val = val;
			return tmp;
		}
	}
}

//***********************************************************************************************
// add a bush node, if the level does not yet exist, create the level too 
//***********************************************************************************************
/*
void nvboolfunc_t::add_bush_node(bush_array_t * base_array, data_inode2d_t * node, int lvl)
{
	if (base_array)
	{
		if (lvl > base_array->nb_level - 1)
		{
			if (!base_array->list && lvl = 0)
			{
				base_array->list = new poslist_t*[lvl + 1];
				base_array->nb_of_node = new int[lvl + 1];
				base_array->nb_level = lvl + 1;
				memset(base_array->nb_level, '\0', (lvl + 1) * sizeof(poslist_t *));
				memset(base_array->nb_of_node, '\0',(lvl + 1) * sizeof(int));
			} else {
				poslist_t ** tmp = new poslist_t*[lvl+1];
				int * tmp1;
				tmp1 = new int[lvl + 1];
				memset(tmp1, '\0',(lvl + 1) * sizeof(int));
				memset(tmp, '\0', (lvl + 1) * sizeof(poslist_t *));
				memcpy(tmp, base_array->list, (base_array->nb_level)*sizeof(poslist_t*));
				memcpy(tmp1, base_array->nb_of_node, (base_array->nb_level)*sizeof(int));
				delete[](base_array->list);
				delete[](base_array->nb_of_node);
				base_array->list = tmp;
				base_array->nb_of_node = tmp1;
			}

		}
		base_array->list = poslist_add_head(node, base_array->list);
	}
}

//***********************************************************************************************
// delete the given bush array (do not delete the inode pointed by, but only the references to
//***********************************************************************************************

void nvboolfunc_t::delete_bush_array(bush_array_t * base_array)
{
	if (base_array)
	{
		if (base_array->list)
		{
			int i;
			for (i = 0 ; i < base_array->nb_level; i++)
			{
				poslist_delete(base_array->list[i]);
			}
			delete[](base_array->list);
		}
		if (base_array->nb_of_node) delete[](base_array->nb_of_node);
	}
}
*/


//***********************************************************************************************
//  Blank all the parse flag of the inodes, using before get_inode_once
//***********************************************************************************************

void nvboolfunc_t::blank_parse_all(void)
{
	if (!is3d)
	{
		size_t i;
		data_inode2d_t* cur;

		if (disk_data)
		{
			for (i = 0; i < size; i++)
			{
				if (disk_data[i].inode.generic_pointer)
				{
					cur = disk_data[i].inode.inode2d;
					while (cur)
					{
						cur->parsed = false;
						cur = cur->next;
					}
				}
			}
		}
	}
	else {
		// not yet implemented
	}

}

//***********************************************************************************************
//  find the inode at the given position
//***********************************************************************************************

data_inode2d_t* nvboolfunc_t::get_inode_once(float xpos, size_t lvl)
{

	if (!disk_data) return NULL;
	data_inode2d_t* cur = disk_data[lvl].inode.inode2d;

	while (cur)
	{
		if (!cur->parsed && fabs(cur->xpos - xpos) < 0.5)
		{
			cur->parsed = true;
			return cur;
			break;
		}
		cur = cur->next;
	}
	return NULL;

}

//***********************************************************************************************
// Add y to xc to get the following numbering :
// 0 1 -1 2 -2 3 -3 4 -4 and so on (not reversible)
//***********************************************************************************************

int nvboolfunc_t::hansel_order_add(int xc, int y)
{
	if (xc <= 0)
	{
		if (y & 1)
		{
			return (-xc + ((y + 1) >> 1));
		}
		else {
			return xc - (y >> 1);
		}
	}
	else {
		if (y & 1)
		{
			return -xc - ((y - 1) >> 1);
		}
		else {
			return  xc + (y >> 1);
		}
	}
}

//***********************************************************************************************
// This function place the data relatively to the logical place in the Hansel Chain
// non regarding to the value itself (just vectors)
//***********************************************************************************************

void nvboolfunc_t::hansel_place(bool expand)
{
	HanselChainSet* hchains = NULL;

	if (size > 16)
	{
		LPCWSTR ws1 = L"Sorry the importing HanselChainSet object \n only supports until 15bits";
		LPCWSTR ws2 = L"Import limitation";
		::MessageBox(NULL, ws1, ws2, MB_ICONERROR | MB_OK);
		return;
	}

	hchains = new HanselChainSet(size - 1);
	if (!hchains)
	{
		LPCWSTR ws1 = L"Error in the HanselChainSet creation";
		LPCWSTR ws2 = L"Import work error";
		::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
		return;
	}

	// Now we create some usefull tools to browse the HanselChainSet object

	HanselChain* hchain;
	bit_vector_t cur(size - 1);
	data_inode2d_t* inode;

	int* places_offset = new int[size];

	memset(places_offset, 0, sizeof(int) * size);
	blank_all_inodes(false);
	int i, j, l;

	for (i = size - 3, j = 0; i >= 0; i -= 2, j++)
	{
		places_offset[i] = hansel_order_add(0, disk_data[j].xsize);
	}

	for (i = 0; i < hchains->get_length(); i++)
	{
		hchain = (*hchains)[i];
		l = hchain->retrieveLength();
		data_inode2d_t* last_inode = NULL;

		for (j = 0; j < l; j++)
		{
			cur = *(*hchain)[j]; // cur is reference to a single vector in hchain
			inode = (data_inode2d_t*)safe_store(cur, true, true, expand); // inode ia referenece to cur, which is referenced in disk_data, so below operations update disk_data

			if (inode)
			{
				inode->xpos = (disk_data[cur.getlevel()].xsize & 1) ? 0.0f : -0.5f;
				inode->xpos += (float)places_offset[l - 1];
				inode->chain_nb = i;
				inode->chain_len = l;
				inode->chain_up = NULL;
				inode->chain_dn = last_inode;

				if (last_inode) 
					last_inode->chain_up = inode;

				last_inode = inode;
			}
		}		
		
		places_offset[l - 1] = hansel_order_add(places_offset[l - 1], 1);
	}

	delete[] places_offset;
	delete(hchains);
	is_hansel_sorted = true;
}

//***********************************************************************************************
// Swap two position in the disk
//***********************************************************************************************

bool nvboolfunc_t::simple_swap(float xpos1, float xpos2, size_t lvl)
{
	if (disk_data && lvl < size
		&& xpos1 > -((float)disk_data[lvl].xsize) / 2.0f && xpos1 < ((float)disk_data[lvl].xsize) / 2.0f
		&& xpos2 > -((float)disk_data[lvl].xsize) / 2.0f && xpos2 < ((float)disk_data[lvl].xsize) / 2.0f)

	{
		data_inode2d_t* i1, * i2;
		float tmp;

		if (i1 = get_inode(xpos1, lvl))
		{
			if (i2 = get_inode(xpos2, lvl))
			{
				tmp = i1->xpos;
				i1->xpos = i2->xpos;
				i2->xpos = tmp;
			}
			else i1->xpos = xpos2;
			return true;
		}
	}
	return false;
}

// TO BE IMPROVED !!!!! 

bool nvboolfunc_t::hchain_move(float xpos1, float xpos2, size_t lvl)
{
	bool r = true;
	if (disk_data && lvl < size)
	{
		data_inode2d_t* inode = NULL, * cur = NULL;
		int i = 0;
		if (inode = get_inode(xpos1, lvl))
		{
			simple_swap(xpos1, xpos2, lvl);
			cur = inode;
			i = 0;
			while (cur = cur->chain_up) simple_swap(xpos1, xpos2, lvl + (++i));
			cur = inode;
			i = 0;
			while (cur = cur->chain_dn) simple_swap(xpos1, xpos2, lvl - (++i));
		}
	}


	return r;
}


//***********************************************************************************************
// Hansel Chain managing functions (architecture side)
//***********************************************************************************************
// get the lower element of a hansel chain (in term of level)
//***********************************************************************************************

data_inode2d_t* nvboolfunc_t::hansel_get_lower(data_inode2d_t* hchain)
{
	if (!is_hansel_sorted || !hchain || hchain->chain_nb < 0) return NULL;
	data_inode2d_t* cur = hchain;
	while (cur && cur->chain_dn) cur = cur->chain_dn;
	return cur;
}

//***********************************************************************************************
// get the top element
//***********************************************************************************************

data_inode2d_t* nvboolfunc_t::hansel_get_top(data_inode2d_t* hchain)
{
	if (!is_hansel_sorted || !hchain || hchain->chain_nb < 0) return NULL;
	data_inode2d_t* cur = hchain;
	while (cur && cur->chain_up) cur = cur->chain_up;
	return cur;
}


//***********************************************************************************************
// get the level of the lower one present in the hansel chain
//***********************************************************************************************

int nvboolfunc_t::hansel_get_lower_one(data_inode2d_t* hchain, bool usefake)
{
	if (!is_hansel_sorted || !hchain || hchain->chain_nb < 0) return -1;
	data_inode2d_t* cur;
	cur = hansel_get_lower(hchain);
	while (cur)
	{

		if (((cur->is_fake && usefake) || !cur->is_fake) && cur->value) return cur->bit_vector.getlevel();
		cur = hansel_secured_next(cur);
	}
	return size;
}

//***********************************************************************************************
// get the upper zero of the hansel chain
//***********************************************************************************************

int nvboolfunc_t::hansel_get_upper_zero(data_inode2d_t* hchain, bool usefake)
{
	if (!is_hansel_sorted || !hchain || hchain->chain_nb < 0) return -1;
	data_inode2d_t* cur;
	cur = this->hansel_get_top(hchain);
	while (cur)
	{
		if (((cur->is_fake && usefake) || !cur->is_fake) && !cur->value) return cur->bit_vector.getlevel();
		cur = hansel_secured_last(cur);
	}
	return size;
}


//***********************************************************************************************
// give the next element of the hansel chain 
//***********************************************************************************************

data_inode2d_t* nvboolfunc_t::hansel_secured_next(data_inode2d_t* hchain)
{
	if (!is_hansel_sorted || !hchain || hchain->chain_nb < 0) return NULL;
	return hchain->chain_up;
}

//***********************************************************************************************
// get the last element of the hansel chain 
//***********************************************************************************************

data_inode2d_t* nvboolfunc_t::hansel_secured_last(data_inode2d_t* hchain)
{
	if (!is_hansel_sorted || !hchain || hchain->chain_nb < 0) return NULL;
	return hchain->chain_dn;
}

//***********************************************************************************************
// gives an element of the hansel chain given its unique number
//***********************************************************************************************

data_inode2d_t* nvboolfunc_t::hansel_get_by_nb(int nb)
{
	if (!disk_data || !is_hansel_sorted || nb < 0) return NULL;
	data_inode2d_t* cur;
	unsigned int i;
	for (i = 0; i < size; i++)
	{
		cur = disk_data[i].inode.inode2d;
		while (cur)
		{
			if (cur->chain_nb == nb) return cur;
			cur = cur->next;
		}
	}

	return NULL;
}

//***********************************************************************************************
// return the number of the hansel chain given an element
//***********************************************************************************************

int nvboolfunc_t::hchain_get_nb(data_inode2d_t* hchain)
{
	if (!is_hansel_sorted || !hchain) return -1;
	return hchain->chain_nb;
}

//***********************************************************************************************
// center the hansel chains
//***********************************************************************************************

void nvboolfunc_t::center_hchain_sort(void)
{

	if (!is_hansel_sorted) return;

	int* places_offset = new int[size];

	memset(places_offset, 0, sizeof(int) * size);
	blank_all_inodes(false);
	int i, j, l;
	int max_chain_nb;

	// create the list

	poslist_t* hchain_list = NULL;
	data_inode2d_t* hchain;

	max_chain_nb = get_max_xsize();

	for (i = 0; i < max_chain_nb; i++)
	{
		hchain = hansel_get_by_nb(i);
		if (hchain)
		{
			hchain_list = insert_sorted(hchain_list, hansel_get_lower(hchain), hansel_get_lower_one(hchain));
			if (!hchain_list)
			{
				LPCWSTR ws1 = L"poslist management error";
				LPCWSTR ws2 = L"center_hchain_error";
				::MessageBox(NULL, ws1, ws2, MB_OK | MB_ICONERROR);
			}
		}
	}

	// create the first order

	for (i = size - 3, j = 0; i >= 0; i -= 2, j++)
	{
		places_offset[i] = hansel_order_add(0, disk_data[j].xsize);
	}

	// then set the places.
	data_inode2d_t* cur;

	while (hchain_list)
	{
		l = hchain_list->node->chain_len;
		cur = hchain_list->node;
		while (cur)
		{
			cur->xpos = (disk_data[cur->bit_vector.getlevel()].xsize & 1) ? 0.0f : -0.5f;
			cur->xpos += (float)places_offset[l - 1];
			cur = hansel_secured_next(cur);
		}
		places_offset[l - 1] = hansel_order_add(places_offset[l - 1], 1);
		hchain_list = delete_head(hchain_list);
	}

	delete[](places_offset);

	is_hansel_sorted = true;

}

//***********************************************************************************************
// Expand the data in an MDF form, then constraint them using the hansel chain criteria
// It basically uses the internal functions for it
//***********************************************************************************************

void nvboolfunc_t::mexpand(void)
{
	unsigned int j;
	data_inode2d_t* node;

	bool* consistency;

	hansel_place(true);

	consistency = new bool[get_max_xsize()];
	memset(consistency, '\0', sizeof(bool) * get_max_xsize());


	blank_all_inodes(false);

	// first expand using monoticity

	for (j = size - 1; j > (size >> 1); j--)
	{
		blank_parse_all();
		node = disk_data[j].inode.inode2d;
		while (node)
		{
			if (node->value) expand_inode(node, consistency);
			node = node->next;
		}
	}

	for (j = 0; j <= size >> 1; j++)
	{
		blank_parse_all();
		node = disk_data[j].inode.inode2d;
		while (node)
		{
			if (!node->value) expand_inode(node, consistency);
			node = node->next;
		}
	}

	for (j = size - 1; j > size >> 1; j--)
	{
		blank_parse_all();
		node = disk_data[j].inode.inode2d;
		while (node)
		{
			if (!node->value) expand_inode(node, consistency);
			node = node->next;
		}
	}

	for (j = 0; j <= size >> 1; j++)
	{
		blank_parse_all();
		node = disk_data[j].inode.inode2d;
		while (node)
		{
			if (node->value) expand_inode(node, consistency);
			node = node->next;
		}
	}


	for (j = 0; j < (unsigned int)get_max_xsize(); j++)
		if (!consistency[j])
		{
			data_inode2d_t* tmp, * tmp1, * tmp2;
			tmp = hansel_get_by_nb(j);
			if (tmp) tmp = hansel_get_lower(tmp);
			while (tmp)
			{
				tmp1 = tmp->chain_up;
				tmp2 = disk_data[tmp->bit_vector.getlevel()].inode.inode2d;
				if (tmp2 == tmp)
				{
					disk_data[tmp->bit_vector.getlevel()].inode.inode2d = tmp->next;
				}
				else {
					while (tmp2 && tmp2->next != tmp) tmp2 = tmp2->next;
					tmp2->next = tmp->next;
				}
				delete(tmp);
				tmp = tmp1;
			}
		}

	// then create and sort for hansel chains

	// finally apply the hanselchain contraints (for keeping borders)

	int max_chain_nb = get_max_xsize();
	int i;

	for (i = 0; i < max_chain_nb; i++)
	{
		node = this->hansel_get_by_nb(i);
		if (node) hansel_criteria(node);
	}

	// then sort all these guys

	little_sort();
}


//***********************************************************************************************
// Internal function to expand a single piece of data, 
// does not expand if the inode is fake unless you ask it too (last parameter), mainly used
// for recursion, if parsefake is true, parse only fake data
//
// WARNING: Depth Recursive Function, be aware of your stack !!
//***********************************************************************************************

void nvboolfunc_t::expand_inode(data_inode2d_t* inode, bool* consistency, bool parsefake, bool val, bool recurs) // default parsefake=false
{
	unsigned int i;
	bool myval;
	size_t sz;
	char* debug, * debug1;

	if (!inode || inode->parsed) return;
	if (inode->chain_nb >= 0) consistency[inode->chain_nb] = true;
	if (parsefake != inode->is_fake) return;


	if (!recurs)
	{ // init the parameters
		myval = inode->value; // go up for value 1, down for value 0
	}
	else {
		myval = val;
	}

	sz = inode->bit_vector.get_size();
	debug = inode->bit_vector.get_string();
	inode->parsed = true;
	for (i = 0; i < sz; i++)
	{
		generic_inode_t converter;
		bit_vector_t bv(inode->bit_vector);
		if (bv[i] != myval)
		{
			bv[i] = myval;
			converter.generic_pointer = safe_store(bv, myval, true);
			//debug1 = bv.get_string();
			if (converter.inode2d->is_fake) converter.inode2d->value = myval;
			converter.inode2d->mexp = true;
			expand_inode(converter.inode2d, consistency, true, myval, true);
		}
	}

}

//***********************************************************************************************
// apply the Hansel Chain constraint (upper zero and lower one)
//***********************************************************************************************

void nvboolfunc_t::hansel_criteria(data_inode2d_t* hchain)
{
	data_inode2d_t* hchaincur;
	int lower1, upper0;

	lower1 = size;
	upper0 = -1;
	if (!hchain || hchain->chain_nb < 0) return;

	lower1 = hansel_get_lower_one(hchain, false);
	upper0 = hansel_get_upper_zero(hchain, false);
	hchaincur = hansel_get_lower(hchain);

	while (hchaincur)
	{
		if (hchaincur->is_fake && !hchaincur->mexp)
		{
			int lvl = hchaincur->bit_vector.getlevel();
			if (lvl < upper0) hchaincur->value = false;
			else if (lvl > lower1) hchaincur->value = true;
		}
		hchaincur = hansel_secured_next(hchaincur);
	}

}




//**********************************************************************************************
//	Calculate the 3d data so it can be plotted later.
//	Called when an nvboolfunc is created.
//	Setup the 3d linked list of data.
//**********************************************************************************************

void nvboolfunc_t::calc3dData(void)
{
	//I think this is how things work.  LR.
	//There is an array of __disk_data_t structures.  Each one is a level of the disk.
	//They have a linked list of inodes, either 2d or 3d.  Each inode is one bit_vector
	//that is, each one is a square, one thing to graph. One true/false vector.

	//For the 3d, each inode is a group, not a single vector.

	//For each level (item in disk_data array).
	//Get all the 2d data and create groups (inode3d).
	//(An inode3d is another linked list of vectors in that group.)
	//Put these groups into a linked list.  A linked list of inode3ds.


	//Groups are vectors that differ at most by one place.
	//1100 and 1010 are in the same group.

	//Groups can be found by using OR and the vector of bits.
	//Then count the number of ones in the resulting ORed vector.  It will
	//equal the level(number of 1s) + 1.







	//For i = 0 to max number of lvls.
		//Rewind disk i, mark all 2d data as unvisited.

		//While there is data left to visit.

			//Put new data3d onto disk 3d list.

			//Put 1st unvisited into that new data3d, set value = 2d value.

			//Mark visited.

			//Go through rest of 2d data and put any matching ones into this data3d.

				//If it fits, add it, mark visited.

				//Get next 2d.

			//Finished one group. Goto top of while.






	//For i = 0 to max number of lvls.
	for (int i = 0; i < size; i++)
	{


		//Rewind disk i, mark all 2d data as unvisited.
		rewind(i);

		data_inode2d_t* d2d = (data_inode2d_t*)get_next_inode(i);
		while (d2d != NULL)
		{
			d2d->visited = false;
			d2d = (data_inode2d_t*)get_next_inode(i);
		}


		disk_data_t* thisLevel = &disk_data[i];

		//Clear any old 3d data first.
		thisLevel->dataList3d.clear();

		int numberVisited = 1;

		//While there is data left to visit.
		while (numberVisited > 0)
		{
			numberVisited = 0;

			//Put 1st unvisited into that new data3d, set value = 2d value.
			rewind(i);


			//Put new data3d onto disk 3d list.
			data3d thisGroup = data3d();



			//Get the first unused node and put it as the start of this
			//group's list.

			rewind(i);
			bool itemFound = false;

			d2d = (data_inode2d_t*)get_next_inode(i);
			while (d2d != NULL && itemFound == false)
			{
				if (d2d->visited != true)
				{


					//Save this 2d vetor and its values.
					//It is now the master vector for this node
					//and determines what other nodes can go in here.
					thisGroup.bvList.push_back(d2d->bit_vector);
					thisGroup.value = d2d->value;
					thisGroup.madeUp = d2d->is_fake;

					//Mark visited.
					itemFound = true;
					d2d->visited = true;
					//numberVisited++;

				}

				d2d = (data_inode2d_t*)get_next_inode(i);

			}



			rewind(i);

			//Go through rest of 2d data and put any matching ones into this data3d.
			d2d = (data_inode2d_t*)get_next_inode(i);
			while (d2d != NULL && itemFound == true)
			{
				if (d2d->visited == false)
				{

					numberVisited++;
					//If it fits, add it, mark visited.
					int currentSize = thisGroup.bvList.front().getlevel();
					bit_vector_t newBV = d2d->bit_vector.bitOr(d2d->bit_vector, thisGroup.bvList.front());
					int thisSize = newBV.getlevel();
					if (thisSize == currentSize + 1 && thisGroup.value == d2d->value && thisGroup.madeUp == d2d->is_fake)
					{
						thisGroup.bvList.push_back(d2d->bit_vector);
						d2d->visited = true;
					}
				}

				//Get next 2d.
				d2d = (data_inode2d_t*)get_next_inode(i);

			}

			//If there is no 2d left that is not visited, exit.
			//Finished one group. Goto top of while.

			thisLevel->dataList3d.push_back(thisGroup);
		}



	}













	/*
		//For each disk layer.
		for (int i = 0; i < this->size; i++)
		{
			disk_data_t thisLevel = disk_data[i];


			//Mark all the 2dnodes as not visited.
			//Put this layers nodes into a list.
			this->rewind(i);
			data_inode2d_t &d = *(data_inode2d_t *)this->get_next_inode(i);

			while (&d != NULL)
			{
				d.visited = false;
				d = *(data_inode2d_t *)this->get_next_inode(i);
			}


			int nodesLeft = 1;

			while (nodesLeft > 0)
			{
				//Keep going through and building groups untill every node is used.
				//Build the 3d group.

				nodesLeft = 0;
				this->rewind(i);
				data_inode2d_t &d2d = *(data_inode2d_t *)this->get_next_inode(i);
				d2d.visited = true;

				data3d &d3d = * new data3d();
				d3d.bvList.push_back(d2d.bit_vector);

				dataList3d.push_back(d3d);

				//Iterate through the list of 2d nodes.
				d2d = *((data_inode2d_t *)this->get_next_inode(i));
				while(&d2d != NULL)
				{

					//Add to the current group if it fits,
					bit_vector_t b = d2d.bit_vector.bitOr(d3d.bvList.front(), d2d.bit_vector);
					if ( (b.get_value() == i + 1)&& d2d.visited != true)
					{
						//Add it.
						d3d.bvList.push_back(d2d.bit_vector);
						//Mark it visited from the main list.
						d2d.visited = true;
					}

					if (d2d.visited != true)
						nodesLeft++;

					d2d = *(data_inode2d_t *)this->get_next_inode(i);
				}



				//Advance to the next 3d group.
			}

		}

	*/






}