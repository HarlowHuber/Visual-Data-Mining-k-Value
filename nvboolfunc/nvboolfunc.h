#ifndef __NVBOOLFUNC_H__
#define __NVBOOLFUNC_H__


#include <bit_vector.h>
#include <nvinput.h>
#include <cmath>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <iterator>

#include "data3d.h"

// This is the color manipulation union ... ABGR for windows ...

typedef union __color_t
{
	struct __unpacked
	{
		unsigned char r; // Red component
		unsigned char g; // Green component
		unsigned char b; // Blue component
		unsigned char a; // Alpha component
	} unpacked;
	unsigned long int upacked;  // packed color
	long int packed;			  // packed color signed
	unsigned char b8_array[4]; // array of component
} color_t;

//This is one data set. One vector with a value (true/false).
//One square that is drawn.  One section of the 3d top.
typedef struct __data_inode2d_t
{
	bit_vector_t bit_vector;	// the vector 
	bool value;					// value of the data set
	bool is_fake;				// is this element a real or created ?
	float xpos;					// position of the element in the disk
	bool placed;				// used in intern to place an element (to be proiminent from others)

	bool visited;		//Is it visited in our 3d function?

	bool parsed;				// flag used to parse only once the chain (in one function)
	int nb_bush;				// number of the bush if computed (used by show_bush)

	struct __data_inode2d_t* chain_up;	// hansel chain up element  if computed
	struct __data_inode2d_t* chain_dn; // hansel chain down element if computed
	int chain_nb;						// number of the chain (each chain has a different number)
	int chain_len;						// size of the chain 
	bool mexp;					// true if in the monoton expand function, this node has been generated there (or modified)
/*

	// there comes datas for the bush
	// maybe should be turned into another structure more general, see after
	//
	// this part is now commented because of a design decision, but since
	// Dr Kovalerchuk change is mind like he change of shirt, I prefer keep it
	// here ;)) (don't take it bad if you read it, but it's true that I prefer
	// the French method : first analysis, then analysis, a little more of analysis
	// and finally code =) this way we don't change all the time ;)
	// Anyhow it might really be usefull after, this part work with the functions commented too
	//
	// Florian
	//
	int order1, order2;
	struct __data_inode2d_t * bush_parent1;
	struct __data_inode2d_t * bush_parent2;
	struct __data_inode2d_t ** bush_childs;
	size_t nb_childs;
	int bush_state;
//	bush_array_t * bush_array;
*/
	struct __data_inode2d_t* next;		// next element
} data_inode2d_t;



typedef struct _poslist_t   // generic link list used inside
{
	data_inode2d_t* node;		// node pointed
	struct _poslist_t* next;	// next elem
	union emphasis_u
	{
		float pos;				// position of the element
		int val;				// value assigned
	} emphasis;
} poslist_t;


/*
typedef struct _bush_array_t
{
	poslist_t ** list;
	int * nb_of_node;
	int nb_level;
} bush_array_t;
*/

// 3d version
//Linked list of bit vectors for the 3d plot.

/*typedef struct bitVectorList
{
	bit_vector_t* b;

	bitVectorList* next;
} bitVectorList;*/

typedef struct __data_inode3d_t
{
	//This holds information about the 3d data.

	//Each section of the 3d structure represents a group of vectors.
	//They are at the same level so they have the same number of 1s in them.
	//Each group is composed of vectors that differ from each other by at most 1 bit.
	//So 100, 010, and 001 all belong together.

	//So this structure consists of a list of bit vecotrs.

//	list<bit_vector_t> bvList;		//The data.


	bool value;					//Value of the data.


	struct __data_inode3d_t* next;
} data_inode3d_t;


typedef union _generic_inode_t
{
	void* generic_pointer;			// used for conversion purpose
	data_inode2d_t* inode2d;		// 2d pointer
	data_inode3d_t* inode3d;		// 3d pointer
} generic_inode_t;



// data disk main link list
//Represnets one level of the disk.
typedef struct __disk_data_t
{
	int xsize;						// size (number of potential element) of the disk
	bool parse_begun;				// if parsing begun or not

	generic_inode_t current;		// current element pointed at
	generic_inode_t inode;			// first element of the link list


	//List of 3d data.
	//This is a list of 3d data nodes.  Each node is an object that represnents 
	//a grouping of data and it's true/false value.  A grouping is a list of 
	//bit_vectors that are related.



	std::list<data3d> dataList3d;


} disk_data_t;


// This class represents the bool function in the way it should be represented

class __declspec(dllexport) nvboolfunc_t
{
private:
	std::vector<int> kv_attributes;													// array of k-values that represent the k-value for each vector attribute
	std::vector<std::multimap<int, bit_vector_t, std::greater<int>>> all_vectors;	// all possible vectors given a vector of k-values, grouped by Hamming norm,
																					// and sorted from greatest to smallest
																					// sorted_vectors[Hamming norm][list of vectors][vector]

	// followering block of functions are implemented in nvboolfunc_vec_gen ("nvboolfunc vector generate")
	void calculate_all_vectors(bit_vector_t max_vector, int max_hamming_norm, size_t max_vector_index);			// calculate all vectors smaller than a given threshold
	int calc_mb_value(bit_vector_t vector);
	// end nvboolfunc_vec_gen

	// hansel chain functions
	void calculateHanselChains(int vector_dimension);
	std::vector<std::vector<bit_vector_t>> genChains(int num, int vector_dimension, std::unordered_map<int, std::vector<std::vector<bit_vector_t>>> chain);
	std::vector<std::vector<bit_vector_t>> hanselChainSet;

	int factorial(int n);		// return n! (factorial)
	int ncr(int n, int r);		// return n!/[(n-p)!p!]

	void set_sizes(void);		// init the size of the disks
	color_t c;					// default color used for many things

protected:
	// poslist inside managing functions
	// poslist_t is a internal structure of link list, somnetimes used as
	// stacks

	// add an item at the head of the poslist_t given the node
	static poslist_t* poslist_add_head(data_inode2d_t* pos, poslist_t* list);

	// add an item at the head of the poslist_t given the pos only
	static poslist_t* poslist_add_head(float pos, poslist_t* list);

	// delete the head of a poslist_t
	static poslist_t* delete_head(poslist_t* list);

	// swap to poslist element data
	static void poslist_swap(poslist_t* list, data_inode2d_t** node);

	// find an element in a sorted poslist
	static poslist_t* poslist_find(float pos, poslist_t* list);

	// delete the poslist
	static void poslist_delete(poslist_t* list);

	// insert an element in a poslist_t
	static poslist_t* insert_after(poslist_t* list, poslist_t* pos, data_inode2d_t* node, int val);

	// insert keeping the sorted property of the poslist_t
	static poslist_t* insert_sorted(poslist_t* list, data_inode2d_t* node, int val);

	//		void add_bush_node(bush_array_t * base_array, data_inode2d_t * node, int lvl);
	//		void delete_bush_array(bush_array_t * base_array);

	size_t size;			  // size is the number of disks, ie the size of input vectors + 1 !!
	disk_data_t* disk_data;  // array of link lists
	color_t** color_array;	  // colors of the disks, 3 colors: one for the disk, one
							  // for the value 1, one for the value 0

	float height;			  // the heigth of each disk

	bool is3d;				  // true if must represent in 3D

	bool highlightMonot;	//Should we highlight monotonization violations?

	bool monotMode;			//Is user expanding data monotonoly?

	bool my3d;					//Since Florian's 3d is tied into so much ill use my own.

	bool plot3d;				//Should the data be drawn in a 3d format?

	bool firstPos;

	bool compress;			//Draw in compressed 3d mode?

	void delete_diskdata(void); // does what it seems ;)

	//bool is_yinyan;				// true if this object is in the yinyan mode form  
								// (use the getter)

	// store a node in the MDF/YYF...
	void* store_inode(bit_vector_t& vect, bool value, bool is_fake = false);

	// perform a check before storing, (avoid duplicated)
	void* safe_store(bit_vector_t& vect, bool value, bool is_fake = false, bool addit = true);

	// reset the parameters of a 2d inode
	void blank_2dinode(data_inode2d_t* inode, bool free_mem = false);

	// reset all parameters
	void blank_all_inodes(bool free_mem);

	void internal_bush_tree(data_inode2d_t* startpoint); // create the bush tree structure [obsolete]
	nvinput_t* input; // the input itself

	// for the rest of the descriptions, see in the .cpp file (nvboolfunc.cpp)
	data_inode2d_t* get_inode_once(float xpos, size_t lvl);

	// reset the parse field of all data
	void blank_parse_all(void);

	// give the offset to add for placing the bush [obsolete!]
	float get_offset(data_inode2d_t* node, float xpos, bool left = true);

	/*
	void set_bush_pos(data_inode2d_t * node);
	void add_child(generic_inode_t& inode, generic_inode_t * child);
	*/

	// color manipulation

	// give the color (relative to the shading) at a point
	void get_color_at(color_t& dest, int idx, int size);

	// give the blue component of the shade color
	unsigned char get_blue_at(int idx, int size);

	// give the red component of the shade color
	unsigned char get_red_at(int idx, int size);

	// give the green component of the shade color
	unsigned char get_green_at(int idx, int size);

	bool is_hansel_sorted;			// true if hansel chains has been computed

	// hansel chain special function managing, sorry for inconvenience, I don't have the time
	// to make a better documentation yet, but I'll try to do it further.

	// get the lower element of the hansel chain
	data_inode2d_t* hansel_get_lower(data_inode2d_t* hchain);

	// get the toppest element of the hansel chain
	data_inode2d_t* hansel_get_top(data_inode2d_t* hchain);

	// get the lower one level in the hansel chain (looking or not to fake data)
	int hansel_get_lower_one(data_inode2d_t* hchain, bool usefake = true);

	// get the upper zero level in the hansel chain (looking or not to fake data)
	int hansel_get_upper_zero(data_inode2d_t* hchain, bool usefake = true);

	// get next (up) element of the hansel chain
	data_inode2d_t* hansel_secured_next(data_inode2d_t* hchain);

	// get last (down) element of the hansel chain
	data_inode2d_t* hansel_secured_last(data_inode2d_t* hchain);

	// get an element of the hansel chain given its number
	data_inode2d_t* hansel_get_by_nb(int nb);

	// get the number of a hansel chain
	int hchain_get_nb(data_inode2d_t* hchain);

	// monotone expand internal functions
	void expand_inode(data_inode2d_t* inode, bool* consistency, bool parsefake = false, bool dir = false, bool recurs = false);

	// apply hansel criteria on the hchain
	void hansel_criteria(data_inode2d_t* hchain);

public:
	// default constructor
	nvboolfunc_t(void);

	// copy contructor
	nvboolfunc_t(const nvboolfunc_t& src);

	// create a boolfunc given its size (in bits)
	nvboolfunc_t(size_t _size);

	// Copy operator
	nvboolfunc_t& operator=(const nvboolfunc_t& src);

	// destructor
	~nvboolfunc_t(void);

	// set the height of each disk (only used for viewing)
	void set_height(float h) { height = h; }

	// retreive the height of each disks
	float get_height(void) { return height; }

	// retrieve the size of the disks (or yinyan) = nbits + 1
	size_t get_size(void) { return size; }

	// retrieve the maximum width of the disks
	int get_max_xsize(void);

	// true if the shape is in 3d (not implemented)
	bool is_3d(void) { return is3d; }

	//For my 3d settings LR.
	bool isMy3d(void) { return my3d; }


	//Toggle show first position.
	bool isShowFirstPos(void) { return firstPos; }
	void toggleFirstPos(void) { firstPos = !firstPos; }

	//Get and set for 3dplot.
	bool is3dPlot(void) { return plot3d; }
	void toggle3dPlot(void) { plot3d = !plot3d; }

	//To calculate the 3d data for plotting.
	void calc3dData(void);

	//Toggle compressed drawing mode.
	void toggleCompress(void) { compress = !compress; }
	bool isCompressed(void) { return compress; }

	// retreive the width of the disk i
	int get_xsize(size_t i);

	// retrieve the color of the disk i
	const color_t& get_disk_color(size_t i);

	// retreive the color of the value on the disk
	const color_t& get_val_color(size_t i, bool val);

	// set the input, and read it
	void set_input(const nvinput_t* const _input);

	//Change the 3d nature.
	void set3d(bool draw3d);
	//Toggle 3d nature to the opposite.
	void toggle3d(void);


	//Toggle monot mode.
	void toggleMonot() { monotMode = !monotMode; }
	bool isMonot() { return monotMode; }

	//Toggle highlihgt monot.
	void toggleMonotViol() { highlightMonot = !highlightMonot; }
	bool isMonotViol() { return highlightMonot; }



	// used to browse data (get the next inode of the disk)
	void* get_next_inode(size_t i);

	// rewind the reading of the disk
	void rewind(size_t i);

	// Natural order sort (little sort)
	void little_sort(void);

	// retrieve the data at the given position,lvl
	bool get_vectdata(float xpos, size_t lvl, bit_vector_t& vect, bool& r);

	// get the inode at the given position
	data_inode2d_t* get_inode(float xpos, size_t lvl);

	// select a bush up, formerly used to create a bush tree
	void bush_sort(size_t lvl, float xpos);

	// Solve any collision if exist in the disk (must set up master/slaves before)
	void solve_collision(void);

	// Align the hansel chains
	void hansel_place(bool expand = false);

	// used internally for placing hansel chains
	static int hansel_order_add(int xc, int y);

	// swap two data given its positions from xpos1 to xpos2
	bool simple_swap(float xpos1, float xpos2, size_t lvl);

	// move an all hansel Chain from xpos1 to xpos2
	bool hchain_move(float xpos1, float xpos2, size_t lvl);

	// true if hanselm chains have been computed
	bool get_is_hansel_sorted(void) { return is_hansel_sorted; }

	// delete generated data (by expand or bushsort)
	void clear_fake(void);

	// Center all hanselchains (try to actually) only in an MDF
	void center_hchain_sort(void);

	// Monotonly expand + hansel criteria
	void mexpand(void);


	//Convert fake to real data.
	bool convert;
	void toggleConvert() { convert = !convert; }
	bool isConvert() { return convert; }

	//Get the disk_data in the array for a level.
	disk_data_t getDiskData(int lvl) { if (lvl >= 0 && lvl <= size) return disk_data[lvl]; }
};


#endif