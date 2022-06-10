#ifndef __FORMULALIB_H__
#define __FORMULALIB_H__

#include <bit_vector.h>
#include <stdlib.h>


// tree classes

class __declspec (dllexport) formula_node_t
{
public:
	formula_node_t(void) {}
	formula_node_t(formula_node_t& src) {}
	formula_node_t& operator=(formula_node_t& src) { return *this; }
	virtual ~formula_node_t(void) {}

	virtual bool value(bit_vector_t& x) = 0;
	virtual formula_node_t* clone(void) = 0;
};

// unary nodes (including variables)

class __declspec (dllexport) formula1_node_t : public formula_node_t
{
protected:
	class formula_node_t* bottom;	// the first child 

public:
	formula1_node_t(void) :bottom(NULL) {}
	formula1_node_t(formula1_node_t& src) : bottom(NULL) {}
	virtual formula1_node_t& operator=(formula1_node_t& src) { return *this; }
	virtual ~formula1_node_t(void) {}

	virtual bool value(bit_vector_t& x) = 0;
	virtual formula_node_t* clone(void) = 0;
};

// parentheses

class __declspec (dllexport) parenthesis_node_t : public formula1_node_t
{
public:
	parenthesis_node_t(void) {}
	parenthesis_node_t(parenthesis_node_t& src) {}
	parenthesis_node_t& operator=(parenthesis_node_t& src) { return *this; }

	parenthesis_node_t(formula_node_t* _bottom);
	~parenthesis_node_t(void);

	bool value(bit_vector_t& x);
	formula_node_t* clone(void);
};


// variable 

class __declspec (dllexport) variable_node_t : public formula1_node_t
{
protected:
	size_t i;		// number of the variable (from 1 to n)

public:
	variable_node_t(void);
	variable_node_t(variable_node_t& src);
	variable_node_t(size_t _i);
	variable_node_t& operator=(variable_node_t& src);
	~variable_node_t(void);

	bool value(bit_vector_t& x);
	formula_node_t* clone(void);
};

class __declspec (dllexport) const_node_t : public formula1_node_t
{
protected:
	bool val;	// the value to return 

public:
	const_node_t(void) { val = false; }
	const_node_t(const_node_t& src) { val = src.val; }
	const_node_t(bool _val) { val = _val; }
	const_node_t& operator=(const_node_t& src) { val = src.val; return *this; }
	~const_node_t(void) {}

	bool value(bit_vector_t& x) { return val; }
	formula_node_t* clone(void) { return new const_node_t(val); }
};


// not 

class __declspec (dllexport) not_node_t : public formula1_node_t
{
public:
	not_node_t(void) {}
	not_node_t(not_node_t& src) {}
	not_node_t(formula_node_t* child);
	not_node_t& operator=(not_node_t& src);
	~not_node_t(void);

	bool value(bit_vector_t& x);
	formula_node_t* clone(void);
};

// binary nodes

class __declspec (dllexport) formula2_node_t : public formula_node_t
{
protected:
	class formula_node_t* left, * right; // two childs

public:
	formula2_node_t(void) :left(NULL), right(NULL) {}
	formula2_node_t(formula2_node_t& src) :left(NULL), right(NULL) {}
	virtual formula2_node_t& operator=(formula2_node_t& src) { left = right = NULL; return *this; }
	virtual ~formula2_node_t(void) {}

	virtual bool value(bit_vector_t& x) = 0;
	virtual formula_node_t* clone(void) = 0;
};

// And node

class __declspec (dllexport) and_node_t : public formula2_node_t
{
public:
	and_node_t(void) {}
	and_node_t(and_node_t& src) {}
	and_node_t& operator=(and_node_t& src) { return *this; }
	and_node_t(formula_node_t* _left, formula_node_t* _right);
	~and_node_t(void);

	bool value(bit_vector_t& x);
	formula_node_t* clone(void);
};

// or node

class __declspec (dllexport) or_node_t : public formula2_node_t
{
public:
	or_node_t(void) {}
	or_node_t(or_node_t& src) {}
	or_node_t& operator=(or_node_t& src) { return *this; }
	or_node_t(formula_node_t* _left, formula_node_t* _right);
	~or_node_t(void);

	bool value(bit_vector_t& x);
	formula_node_t* clone(void);
};



// Main class derivate from the Bsion parser for the creation of the tree

class __declspec (dllexport) formula_t
{
private:

protected:

	formula_node_t* tree;

public:

	formula_t(void);
	formula_t(formula_t& src);
	formula_t(const char* const expr);
	formula_t& operator= (formula_t& src);
	~formula_t(void);

	bool valueof(bit_vector_t& x);

	bool is_created(void) { return tree != NULL; }
	bool create(const char* const expr);

};




#endif
