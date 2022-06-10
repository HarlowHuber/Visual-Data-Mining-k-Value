/*
** This is the bison parser used for parsing the boolean function input
** compile with bison_pp -o fparse.cpp -S bison.cpp -H fparse.h formula.y
*/

%header{
#ifndef LINUX_COMPILE
#include <windows.h>
#endif
#include <formulalib.h>
#include <stdlib.h>
#include <stdio.h>
%}

%{
#include <string.h>
%}


%define PARSE parse
%define CLASS formula_parse_t
%define INHERIT : public formula_t

%define MEMBERS private: \
		char * str;\
		int cur; \
		public: \
		formula_parse_t(void) : str(NULL), cur(0) {};\
		formula_parse_t(formula_parse_t & src);\
		formula_parse_t & operator=(formula_parse_t & src);\
		~formula_parse_t(void) {if (str) free(str); } \
		void set_str(const char * const str); 

%define CONSTRUCTOR_PARAM const char const * _str
%define CONSTRUCTOR_INIT : str(NULL), cur(0)
%define CONSTRUCTOR_CODE  if (_str) str = strdup(_str);



%define LEX lex_it

%union {
	unsigned int nb;
	formula_node_t * node;
	}

%left '(' ')'
%left 'v' 'V' '^'
%left '-'

%token <nb> INTEGER

%type <node> formula
%type <node> line

%% 

line
	: formula '\0'
	| formula				{ 
						  if (tree) delete(tree);
						  tree = $1; 
						}
						
	| error 				{ 
						  ::MessageBox(NULL, "Formula syntax error", "Error", MB_OK | MB_ICONERROR);
						  if (tree) delete (tree);
						  tree = NULL;
						  if (str) free(str);
						  YYABORT;
						}
	;

formula
		: '(' formula ')'		{ $$ = new parenthesis_node_t($2);}
		| '[' formula ']'		{ $$ = new parenthesis_node_t($2);}
		| '-' formula 			{ $$ = new not_node_t($2); }
		| formula '^' formula		{ $$ = new and_node_t ($1, $3);}
		| formula '.' formula		{ $$ = new and_node_t ($1, $3);}
		| formula '*' formula		{ $$ = new and_node_t ($1, $3);}
		| formula formula		{ $$ = new and_node_t ($1, $2);}		
		| formula 'V' formula		{ $$ = new or_node_t ($1, $3);}
		| formula 'v' formula		{ $$ = new or_node_t ($1, $3);}
		| formula '+' formula		{ $$ = new or_node_t ($1, $3);}
		| 'X' INTEGER			{ $$ = new variable_node_t ($2); }
		| 'x' INTEGER			{ $$ = new variable_node_t ($2); }
		| INTEGER					{
										if ($1 == 0) $$ = new const_node_t (false); 
										else $$ = new const_node_t (true); 
									}
		;

%%

//************************************************************************************************
// Set the sring 
//************************************************************************************************

void formula_parse_t::set_str(const char * const _str)
{
	if (_str) str = strdup(_str);
}

//************************************************************************************************
// get the tokens from the string line, detect end of input.
//************************************************************************************************

int formula_parse_t::lex_it(void)
{
	int c = 0;
	bool is_num = false;
	
	char buffer[256];
	
	if (!str) return 0;
	// read, return VAR, INTEGER, OR
	while (1)
	{
		buffer[c] = str[c + cur];
		if ( buffer[c] >= '0' && buffer[c] <= '9' )
		{
			is_num = true;
		} else {
			if (is_num)
			{
				buffer[c] = '\0';
				yylval.nb = atoi(buffer);
				cur += c;
				return INTEGER;
			} else {
				cur++;
				return (int) buffer[c];
			}
		}
		c++;
	}
	
}

//************************************************************************************************
// error callback
//************************************************************************************************


void formula_parse_t::yyerror(char * msg)
{
	::MessageBox(NULL, msg, "Bison Parse Error :", MB_OK | MB_ICONERROR);
}

//************************************************************************************************
// copy operator
//************************************************************************************************

formula_parse_t & formula_parse_t::operator=(formula_parse_t & src)
{
	if (tree) delete (tree);
	tree = NULL;
	if (src.tree) tree = src.tree->clone();
	str = NULL;
	if (src.str) str = strdup(src.str);
	cur = src.cur;
	return *this;
}

//************************************************************************************************
// copy constructor
//************************************************************************************************

formula_parse_t::formula_parse_t(formula_parse_t & src)
{
	tree = NULL;
	if (src.tree) tree = src.tree->clone();
	str = NULL;
	if (src.str) str = strdup(src.str);
	cur = src.cur;
}
