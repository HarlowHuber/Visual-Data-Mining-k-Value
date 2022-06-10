/*
 *  UPDATE 3 / 28 / 2022 - Harlow Huber
 *      The files belonging to the Visual Data Mining project are quite old and were built in Visual C++ 6.0 in, I presume, C++98.
 *      This project is being reimagined in Visual Studio 2022 in C++20. I do not know the format of the CHANGE LOG, so I will
 *      put my changes below.All functionality will remain the same, or exceedingly similar.
 *      All previous code comments will remain, for now, as a reference.
 *
 *  BUG FIXES 3 / 28 / 2022 - HARLOW HUBER
 *      changed some "const char*" types to LPCWSTR and vice versa
 *      in "yyerror()", converted "char*" to LPCWSTR/wchar
 */

#define YY_parse_h_included

/*  A Bison++ parser, made from formula.y  */

 /* with Bison++ version bison++ Version 1.21-8, adapted from GNU bison by coetmeur@icdc.fr
  */


#line 1 "bison.cc"
  /* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
  /* Skeleton output parser for bison,
     Copyright (C) 1984, 1989, 1990 Bob Corbett and Richard Stallman

     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 1, or (at your option)
     any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

     /* HEADER SECTION */
#if defined( _MSDOS ) || defined(MSDOS) || defined(__MSDOS__) 
#define __MSDOS_AND_ALIKE
#endif
#if defined(_WINDOWS) && defined(_MSC_VER)
#define __HAVE_NO_ALLOCA
#define __MSDOS_AND_ALIKE
#endif

#ifndef alloca
#if defined( __GNUC__)
#define alloca __builtin_alloca

#elif (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc)  || defined (__sgi)
#include <alloca.h>

#elif defined (__MSDOS_AND_ALIKE)
#include <malloc.h>
#ifndef __TURBOC__
/* MS C runtime lib */
#define alloca _alloca
#endif

#elif defined(_AIX)
#include <malloc.h>
#pragma alloca

#elif defined(__hpux)
#ifdef __cplusplus
extern "C" {
    void* alloca(unsigned int);
};
#else /* not __cplusplus */
void* alloca();
#endif /* not __cplusplus */

#endif /* not _AIX  not MSDOS, or __TURBOC__ or _AIX, not sparc.  */
#endif /* alloca not defined.  */
#ifdef c_plusplus
#ifndef __cplusplus
#define __cplusplus
#endif
#endif
#ifdef __cplusplus
#ifndef YY_USE_CLASS
#define YY_USE_CLASS
#endif
#else
#ifndef __STDC__
#define const
#endif
#endif
#include <stdio.h>
#define YYBISON 1  

/* #line 73 "bison.cc" */
#line 85 "fparse.cpp"
#line 6 "formula.y"

#ifndef LINUX_COMPILE
#include <windows.h>
#endif
#include "formulalib.h"
#include <stdlib.h>
#include <stdio.h>
#line 15 "formula.y"

#include <string.h>
#define YY_parse_PARSE  parse
#define YY_parse_CLASS  formula_parse_t
#define YY_parse_INHERIT  : public formula_t
#define YY_parse_MEMBERS  private: \
		char * str;\
		int cur; \
		public: \
		formula_parse_t(void) : str(NULL), cur(0) {};\
		formula_parse_t(formula_parse_t & src);\
		formula_parse_t & operator=(formula_parse_t & src);\
		~formula_parse_t(void) {if (str) free(str); } \
		void set_str(const char * const str); 
#define YY_parse_CONSTRUCTOR_PARAM  const char const * _str
#define YY_parse_CONSTRUCTOR_INIT  : str(NULL), cur(0)
#define YY_parse_CONSTRUCTOR_CODE   if (_str) str = strdup(_str);
#define YY_parse_LEX  lex_it

#line 42 "formula.y"
typedef union {
    unsigned int nb;
    formula_node_t* node;
} yy_parse_stype;
#define YY_parse_STYPE yy_parse_stype

#line 73 "bison.cc"
/* %{ and %header{ and %union, during decl */
#define YY_parse_BISON 1
#ifndef YY_parse_COMPATIBILITY
#ifndef YY_USE_CLASS
#define  YY_parse_COMPATIBILITY 1
#else
#define  YY_parse_COMPATIBILITY 0
#endif
#endif

#if YY_parse_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YYLTYPE
#ifndef YY_parse_LTYPE
#define YY_parse_LTYPE YYLTYPE
#endif
#endif
#ifdef YYSTYPE
#ifndef YY_parse_STYPE 
#define YY_parse_STYPE YYSTYPE
#endif
#endif
#ifdef YYDEBUG
#ifndef YY_parse_DEBUG
#define  YY_parse_DEBUG YYDEBUG
#endif
#endif
#ifdef YY_parse_STYPE
#ifndef yystype
#define yystype YY_parse_STYPE
#endif
#endif
/* use goto to be compatible */
#ifndef YY_parse_USE_GOTO
#define YY_parse_USE_GOTO 1
#endif
#endif

/* use no goto to be clean in C++ */
#ifndef YY_parse_USE_GOTO
#define YY_parse_USE_GOTO 0
#endif

#ifndef YY_parse_PURE

/* #line 117 "bison.cc" */
#line 168 "fparse.cpp"

#line 117 "bison.cc"
/*  YY_parse_PURE */
#endif

/* section apres lecture def, avant lecture grammaire S2 */

/* #line 121 "bison.cc" */
#line 177 "fparse.cpp"

#line 121 "bison.cc"
/* prefix */
#ifndef YY_parse_DEBUG

/* #line 123 "bison.cc" */
#line 184 "fparse.cpp"

#line 123 "bison.cc"
/* YY_parse_DEBUG */
#endif


#ifndef YY_parse_LSP_NEEDED

/* #line 128 "bison.cc" */
#line 194 "fparse.cpp"

#line 128 "bison.cc"
 /* YY_parse_LSP_NEEDED*/
#endif



/* DEFAULT LTYPE*/
#ifdef YY_parse_LSP_NEEDED
#ifndef YY_parse_LTYPE
typedef
struct yyltype
{
    int timestamp;
    int first_line;
    int first_column;
    int last_line;
    int last_column;
    char* text;
}
yyltype;

#define YY_parse_LTYPE yyltype
#endif
#endif
/* DEFAULT STYPE*/
      /* We used to use `unsigned long' as YY_parse_STYPE on MSDOS,
     but it seems better to be consistent.
     Most programs should declare their own type anyway.  */

#ifndef YY_parse_STYPE
#define YY_parse_STYPE int
#endif
     /* DEFAULT MISCELANEOUS */
#ifndef YY_parse_PARSE
#define YY_parse_PARSE yyparse
#endif
#ifndef YY_parse_LEX
#define YY_parse_LEX yylex
#endif
#ifndef YY_parse_LVAL
#define YY_parse_LVAL yylval
#endif
#ifndef YY_parse_LLOC
#define YY_parse_LLOC yylloc
#endif
#ifndef YY_parse_CHAR
#define YY_parse_CHAR yychar
#endif
#ifndef YY_parse_NERRS
#define YY_parse_NERRS yynerrs
#endif
#ifndef YY_parse_DEBUG_FLAG
#define YY_parse_DEBUG_FLAG yydebug
#endif
#ifndef YY_parse_ERROR
#define YY_parse_ERROR yyerror
#endif
#ifndef YY_parse_PARSE_PARAM
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
#define YY_parse_PARSE_PARAM
#ifndef YY_parse_PARSE_PARAM_DEF
#define YY_parse_PARSE_PARAM_DEF
#endif
#endif
#endif
#endif
#ifndef YY_parse_PARSE_PARAM
#define YY_parse_PARSE_PARAM void
#endif
#endif
#if YY_parse_COMPATIBILITY != 0
/* backward compatibility */
#ifdef YY_parse_LTYPE
#ifndef YYLTYPE
#define YYLTYPE YY_parse_LTYPE
#else
/* WARNING obsolete !!! user defined YYLTYPE not reported into generated header */
#endif
#endif
#ifndef YYSTYPE
#define YYSTYPE YY_parse_STYPE
#else
/* WARNING obsolete !!! user defined YYSTYPE not reported into generated header */
#endif
#ifdef YY_parse_PURE
#ifndef YYPURE
#define YYPURE YY_parse_PURE
#endif
#endif
#ifdef YY_parse_DEBUG
#ifndef YYDEBUG
#define YYDEBUG YY_parse_DEBUG 
#endif
#endif
#ifndef YY_parse_ERROR_VERBOSE
#ifdef YYERROR_VERBOSE
#define YY_parse_ERROR_VERBOSE YYERROR_VERBOSE
#endif
#endif
#ifndef YY_parse_LSP_NEEDED
#ifdef YYLSP_NEEDED
#define YY_parse_LSP_NEEDED YYLSP_NEEDED
#endif
#endif
#endif
#ifndef YY_USE_CLASS
/* TOKEN C */

/* #line 236 "bison.cc" */
#line 307 "fparse.cpp"
#define	INTEGER	258


#line 236 "bison.cc"
 /* #defines tokens */
#else
/* CLASS */
#ifndef YY_parse_CLASS
#define YY_parse_CLASS parse
#endif
#ifndef YY_parse_INHERIT
#define YY_parse_INHERIT
#endif
#ifndef YY_parse_MEMBERS
#define YY_parse_MEMBERS 
#endif
#ifndef YY_parse_LEX_BODY
#define YY_parse_LEX_BODY  
#endif
#ifndef YY_parse_ERROR_BODY
#define YY_parse_ERROR_BODY  
#endif
#ifndef YY_parse_CONSTRUCTOR_PARAM
#define YY_parse_CONSTRUCTOR_PARAM
#endif
#ifndef YY_parse_CONSTRUCTOR_CODE
#define YY_parse_CONSTRUCTOR_CODE
#endif
#ifndef YY_parse_CONSTRUCTOR_INIT
#define YY_parse_CONSTRUCTOR_INIT
#endif
/* choose between enum and const */
#ifndef YY_parse_USE_CONST_TOKEN
#define YY_parse_USE_CONST_TOKEN 0
/* yes enum is more compatible with flex,  */
/* so by default we use it */
#endif
#if YY_parse_USE_CONST_TOKEN != 0
#ifndef YY_parse_ENUM_TOKEN
#define YY_parse_ENUM_TOKEN yy_parse_enum_token
#endif
#endif

class YY_parse_CLASS YY_parse_INHERIT
{
public:
#if YY_parse_USE_CONST_TOKEN != 0
    /* static const int token ... */

    /* #line 280 "bison.cc" */
#line 358 "fparse.cpp"
    static const int INTEGER;


#line 280 "bison.cc"
    /* decl const */
#else
    enum YY_parse_ENUM_TOKEN {
        YY_parse_NULL_TOKEN = 0

        /* #line 283 "bison.cc" */
#line 368 "fparse.cpp"
        , INTEGER = 258


#line 283 "bison.cc"
        /* enum token */
    }; /* end of enum declaration */
#endif
public:
    int YY_parse_PARSE(YY_parse_PARSE_PARAM);
    virtual void YY_parse_ERROR(char* msg) YY_parse_ERROR_BODY;
#ifdef YY_parse_PURE
#ifdef YY_parse_LSP_NEEDED
    virtual int  YY_parse_LEX(YY_parse_STYPE* YY_parse_LVAL, YY_parse_LTYPE* YY_parse_LLOC) YY_parse_LEX_BODY;
#else
    virtual int  YY_parse_LEX(YY_parse_STYPE* YY_parse_LVAL) YY_parse_LEX_BODY;
#endif
#else
    virtual int YY_parse_LEX() YY_parse_LEX_BODY;
    YY_parse_STYPE YY_parse_LVAL;
#ifdef YY_parse_LSP_NEEDED
    YY_parse_LTYPE YY_parse_LLOC;
#endif
    int   YY_parse_NERRS;
    int    YY_parse_CHAR;
#endif
#if YY_parse_DEBUG != 0
    int YY_parse_DEBUG_FLAG;   /*  nonzero means print parse trace     */
#endif
public:
    YY_parse_CLASS(YY_parse_CONSTRUCTOR_PARAM);
    //public:
    YY_parse_MEMBERS
};
/* other declare folow */
#if YY_parse_USE_CONST_TOKEN != 0

/* #line 314 "bison.cc" */
#line 406 "fparse.cpp"
const int YY_parse_CLASS::INTEGER = 258;


#line 314 "bison.cc"
/* const YY_parse_CLASS::token */
#endif
/*apres const  */
YY_parse_CLASS::YY_parse_CLASS(YY_parse_CONSTRUCTOR_PARAM) YY_parse_CONSTRUCTOR_INIT
{
#if YY_parse_DEBUG != 0
    YY_parse_DEBUG_FLAG = 0;
#endif
    YY_parse_CONSTRUCTOR_CODE;
};
#endif

/* #line 325 "bison.cc" */
#line 424 "fparse.cpp"


#define	YYFINAL		32
#define	YYFLAG		-32768
#define	YYNTBASE	18

#define YYTRANSLATE(x) ((unsigned)(x) <= 259 ? yytranslate[x] : 20)

static const char yytranslate[] = { 0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     3,
     4,    14,    15,     2,     8,    13,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     6,     2,    16,     2,     2,
    11,     2,    12,     7,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     5,     2,    17,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     9,    10
};

#if YY_parse_DEBUG != 0
static const short yyprhs[] = { 0,
     0,     3,     5,     7,    11,    15,    18,    22,    26,    30,
    33,    37,    41,    45,    48,    51
};

static const short yyrhs[] = { 19,
    10,     0,    19,     0,     1,     0,     3,    19,     4,     0,
    11,    19,    12,     0,     8,    19,     0,    19,     7,    19,
     0,    19,    13,    19,     0,    19,    14,    19,     0,    19,
    19,     0,    19,     6,    19,     0,    19,     5,    19,     0,
    19,    15,    19,     0,    16,     9,     0,    17,     9,     0,
     9,     0
};

#endif

#if YY_parse_DEBUG != 0
static const short yyrline[] = { 0,
    59,    60,    65,    75,    76,    77,    78,    79,    80,    81,
    82,    83,    84,    85,    86,    87
};

static const char* const yytname[] = { "$","error","$illegal.","'('","')'",
"'v'","'V'","'^'","'-'","INTEGER","'000'","'['","']'","'.'","'*'","'+'","'X'",
"'x'","line","formula",""
};
#endif

static const short yyr1[] = { 0,
    18,    18,    18,    19,    19,    19,    19,    19,    19,    19,
    19,    19,    19,    19,    19,    19
};

static const short yyr2[] = { 0,
     2,     1,     1,     3,     3,     2,     3,     3,     3,     2,
     3,     3,     3,     2,     2,     1
};

static const short yydefact[] = { 0,
     3,     0,     0,    16,     0,     0,     0,     2,     0,     6,
     0,    14,    15,     0,     0,     0,     1,     0,     0,     0,
    10,     4,     5,    12,    11,     7,     8,     9,    13,     0,
     0,     0
};

static const short yydefgoto[] = { 30,
    21
};

static const short yypact[] = { 20,
-32768,    95,    95,-32768,    95,    -8,    -2,    35,    50,    -5,
    65,-32768,-32768,    95,    95,    95,-32768,    95,    95,    95,
    80,-32768,-32768,   105,   105,   105,    80,    80,    80,    13,
    17,-32768
};

static const short yypgoto[] = { -32768,
     0
};


#define	YYLAST		122


static const short yytable[] = { 8,
    12,     9,    10,     4,    11,     5,    13,    18,    19,    20,
     6,     7,    31,    24,    25,    26,    32,    27,    28,    29,
     1,     0,     2,     0,     0,     0,     0,     3,     4,     0,
     5,     0,     0,     0,     0,     6,     7,     2,     0,    14,
    15,    16,     3,     4,    17,     5,     0,    18,    19,    20,
     6,     7,     2,    22,    14,    15,    16,     3,     4,     0,
     5,     0,    18,    19,    20,     6,     7,     2,     0,    14,
    15,    16,     3,     4,     0,     5,    23,    18,    19,    20,
     6,     7,     2,     0,    14,    15,    16,     3,     4,     0,
     5,     0,    18,    19,    20,     6,     7,     2,     0,     0,
     0,     0,     3,     4,     0,     5,     0,     0,     0,     0,
     6,     7,     3,     4,     0,     5,     0,    18,    19,    20,
     6,     7
};

static const short yycheck[] = { 0,
     9,     2,     3,     9,     5,    11,     9,    13,    14,    15,
    16,    17,     0,    14,    15,    16,     0,    18,    19,    20,
     1,    -1,     3,    -1,    -1,    -1,    -1,     8,     9,    -1,
    11,    -1,    -1,    -1,    -1,    16,    17,     3,    -1,     5,
     6,     7,     8,     9,    10,    11,    -1,    13,    14,    15,
    16,    17,     3,     4,     5,     6,     7,     8,     9,    -1,
    11,    -1,    13,    14,    15,    16,    17,     3,    -1,     5,
     6,     7,     8,     9,    -1,    11,    12,    13,    14,    15,
    16,    17,     3,    -1,     5,     6,     7,     8,     9,    -1,
    11,    -1,    13,    14,    15,    16,    17,     3,    -1,    -1,
    -1,    -1,     8,     9,    -1,    11,    -1,    -1,    -1,    -1,
    16,    17,     8,     9,    -1,    11,    -1,    13,    14,    15,
    16,    17
};

#line 325 "bison.cc"
/* fattrs + tables */

/* parser code folow  */


/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

  /* Note: dollar marks section change
     the next  is replaced by the list of actions, each action
     as one case of the switch.  */

#if YY_parse_USE_GOTO != 0
     /*
      SUPRESSION OF GOTO : on some C++ compiler (sun c++)
       the goto is strictly forbidden if any constructor/destructor
       is used in the whole function (very stupid isn't it ?)
      so goto are to be replaced with a 'while/switch/case construct'
      here are the macro to keep some apparent compatibility
     */
#define YYGOTO(lb) {yy_gotostate=lb;continue;}
#define YYBEGINGOTO  enum yy_labels yy_gotostate=yygotostart; \
                     for(;;) switch(yy_gotostate) { case yygotostart: {
#define YYLABEL(lb) } case lb: {
#define YYENDGOTO } } 
#define YYBEGINDECLARELABEL enum yy_labels {yygotostart
#define YYDECLARELABEL(lb) ,lb
#define YYENDDECLARELABEL  };
#else
     /* macro to keep goto */
#define YYGOTO(lb) goto lb
#define YYBEGINGOTO 
#define YYLABEL(lb) lb:
#define YYENDGOTO
#define YYBEGINDECLARELABEL 
#define YYDECLARELABEL(lb)
#define YYENDDECLARELABEL 
#endif
/* LABEL DECLARATION */
YYBEGINDECLARELABEL
YYDECLARELABEL(yynewstate)
YYDECLARELABEL(yybackup)
/* YYDECLARELABEL(yyresume) */
YYDECLARELABEL(yydefault)
YYDECLARELABEL(yyreduce)
YYDECLARELABEL(yyerrlab)   /* here on detecting error */
YYDECLARELABEL(yyerrlab1)   /* here on error raised explicitly by an action */
YYDECLARELABEL(yyerrdefault)  /* current state does not do anything special for the error token. */
YYDECLARELABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */
YYDECLARELABEL(yyerrhandle)
YYENDDECLARELABEL
/* ALLOCA SIMULATION */
/* __HAVE_NO_ALLOCA */
#ifdef __HAVE_NO_ALLOCA
int __alloca_free_ptr(char* ptr, char* ref)
{
    if (ptr != ref) free(ptr);
    return 0;
}

#define __ALLOCA_alloca(size) malloc(size)
#define __ALLOCA_free(ptr,ref) __alloca_free_ptr((char *)ptr,(char *)ref)

#ifdef YY_parse_LSP_NEEDED
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		    __ALLOCA_free(yyls,yylsa)+\
		   (num))
#else
#define __ALLOCA_return(num) \
            return( __ALLOCA_free(yyss,yyssa)+\
		    __ALLOCA_free(yyvs,yyvsa)+\
		   (num))
#endif
#else
#define __ALLOCA_return(num) return(num)
#define __ALLOCA_alloca(size) alloca(size)
#define __ALLOCA_free(ptr,ref) 
#endif

/* ENDALLOCA SIMULATION */

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (YY_parse_CHAR = YYEMPTY)
#define YYEMPTY         -2
#define YYEOF           0
#define YYACCEPT        __ALLOCA_return(0)
#define YYABORT         __ALLOCA_return(1)
#define YYERROR         YYGOTO(yyerrlab1)
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL          YYGOTO(yyerrlab)
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do                                                              \
  if (YY_parse_CHAR == YYEMPTY && yylen == 1)                               \
    { YY_parse_CHAR = (token), YY_parse_LVAL = (value);                 \
      yychar1 = YYTRANSLATE (YY_parse_CHAR);                                \
      YYPOPSTACK;                                               \
      YYGOTO(yybackup);                                            \
    }                                                           \
  else                                                          \
    { YY_parse_ERROR ("syntax error: cannot back up"); YYERROR; }   \
while (0)

#define YYTERROR        1
#define YYERRCODE       256

#ifndef YY_parse_PURE
   /* UNPURE */
#define YYLEX           YY_parse_LEX()
#ifndef YY_USE_CLASS
/* If nonreentrant, and not class , generate the variables here */
int     YY_parse_CHAR;                      /*  the lookahead symbol        */
YY_parse_STYPE      YY_parse_LVAL;              /*  the semantic value of the */
                /*  lookahead symbol    */
int YY_parse_NERRS;                 /*  number of parse errors so far */
#ifdef YY_parse_LSP_NEEDED
YY_parse_LTYPE YY_parse_LLOC;   /*  location data for the lookahead     */
            /*  symbol                              */
#endif
#endif


#else
   /* PURE */
#ifdef YY_parse_LSP_NEEDED
#define YYLEX           YY_parse_LEX(&YY_parse_LVAL, &YY_parse_LLOC)
#else
#define YYLEX           YY_parse_LEX(&YY_parse_LVAL)
#endif
#endif
#ifndef YY_USE_CLASS
#if YY_parse_DEBUG != 0
    int YY_parse_DEBUG_FLAG;                    /*  nonzero means print parse trace     */
    /* Since this is uninitialized, it does not stop multiple parsers
       from coexisting.  */
#endif
#endif



       /*  YYINITDEPTH indicates the initial size of the parser's stacks       */

#ifndef YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif


#if __GNUC__ > 1                /* GNU C and GNU C++ define this.  */
#define __yy_bcopy(FROM,TO,COUNT)       __builtin_memcpy(TO,FROM,COUNT)
#else                           /* not GNU C or C++ */

    /* This is the most reliable way to avoid incompatibilities
       in available built-in functions on various systems.  */

#ifdef __cplusplus
static void __yy_bcopy(char* from, char* to, int count)
#else
#ifdef __STDC__
static void __yy_bcopy(char* from, char* to, int count)
#else
static void __yy_bcopy(from, to, count)
char* from;
char* to;
int count;
#endif
#endif
{
    register char* f = from;
    register char* t = to;
    register int i = count;

    while (i-- > 0)
        *t++ = *f++;
}
#endif

int
#ifdef YY_USE_CLASS
YY_parse_CLASS::
#endif
YY_parse_PARSE(YY_parse_PARSE_PARAM)
#ifndef __STDC__
#ifndef __cplusplus
#ifndef YY_USE_CLASS
/* parameter definition without protypes */
YY_parse_PARSE_PARAM_DEF
#endif
#endif
#endif
{
    register int yystate;
    register int yyn;
    register short* yyssp;
    register YY_parse_STYPE* yyvsp;
    int yyerrstatus;      /*  number of tokens to shift before error messages enabled */
    int yychar1 = 0;          /*  lookahead token as an internal (translated) token number */

    short yyssa[YYINITDEPTH];     /*  the state stack                     */
    YY_parse_STYPE yyvsa[YYINITDEPTH];        /*  the semantic value stack            */

    short* yyss = yyssa;          /*  refer to the stacks thru separate pointers */
    YY_parse_STYPE* yyvs = yyvsa;     /*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YY_parse_LSP_NEEDED
    YY_parse_LTYPE yylsa[YYINITDEPTH];        /*  the location stack                  */
    YY_parse_LTYPE* yyls = yylsa;
    YY_parse_LTYPE* yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

    int yystacksize = YYINITDEPTH;

#ifdef YY_parse_PURE
    int YY_parse_CHAR;
    YY_parse_STYPE YY_parse_LVAL;
    int YY_parse_NERRS;
#ifdef YY_parse_LSP_NEEDED
    YY_parse_LTYPE YY_parse_LLOC;
#endif
#endif

    YY_parse_STYPE yyval;             /*  the variable used to return         */
                  /*  semantic values from the action     */
                  /*  routines                            */

    int yylen;
    /* start loop, in which YYGOTO may be used. */
    YYBEGINGOTO

#if YY_parse_DEBUG != 0
        if (YY_parse_DEBUG_FLAG)
            fprintf(stderr, "Starting parse\n");
#endif
    yystate = 0;
    yyerrstatus = 0;
    YY_parse_NERRS = 0;
    YY_parse_CHAR = YYEMPTY;          /* Cause a token to be read.  */

    /* Initialize stack pointers.
       Waste one element of value and location stack
       so that they stay on the same level as the state stack.
       The wasted elements are never initialized.  */

    yyssp = yyss - 1;
    yyvsp = yyvs;
#ifdef YY_parse_LSP_NEEDED
    yylsp = yyls;
#endif

    /* Push a new state, which is found in  yystate  .  */
    /* In all cases, when you get here, the value and location stacks
       have just been pushed. so pushing a state here evens the stacks.  */
    YYLABEL(yynewstate)

        * ++yyssp = yystate;

    if (yyssp >= yyss + yystacksize - 1)
    {
        /* Give user a chance to reallocate the stack */
        /* Use copies of these so that the &'s don't force the real ones into memory. */
        YY_parse_STYPE* yyvs1 = yyvs;
        short* yyss1 = yyss;
#ifdef YY_parse_LSP_NEEDED
        YY_parse_LTYPE* yyls1 = yyls;
#endif

        /* Get the current used size of the three stacks, in elements.  */
        int size = yyssp - yyss + 1;

#ifdef yyoverflow
        /* Each stack pointer address is followed by the size of
       the data in use in that stack, in bytes.  */
#ifdef YY_parse_LSP_NEEDED
       /* This used to be a conditional around just the two extra args,
      but that might be undefined if yyoverflow is a macro.  */
        yyoverflow("parser stack overflow",
            &yyss1, size * sizeof(*yyssp),
            &yyvs1, size * sizeof(*yyvsp),
            &yyls1, size * sizeof(*yylsp),
            &yystacksize);
#else
        yyoverflow("parser stack overflow",
            &yyss1, size * sizeof(*yyssp),
            &yyvs1, size * sizeof(*yyvsp),
            &yystacksize);
#endif

        yyss = yyss1; yyvs = yyvs1;
#ifdef YY_parse_LSP_NEEDED
        yyls = yyls1;
#endif
#else /* no yyoverflow */
        /* Extend the stack our own way.  */
        if (yystacksize >= YYMAXDEPTH)
        {
            char c[22] = { 'p', 'a', 'r', 's', 'e', 'r', ' ', 's', 't', 'a', 'c', 'k', ' ', 'o', 'v', 'e', 'r', 'f', 'l', 'o', 'w', '\0'};
            YY_parse_ERROR(c);
            __ALLOCA_return(2);
        }
        yystacksize *= 2;
        if (yystacksize > YYMAXDEPTH)
            yystacksize = YYMAXDEPTH;
        yyss = (short*)__ALLOCA_alloca(yystacksize * sizeof(*yyssp));
        __yy_bcopy((char*)yyss1, (char*)yyss, size * sizeof(*yyssp));
        __ALLOCA_free(yyss1, yyssa);
        yyvs = (YY_parse_STYPE*)__ALLOCA_alloca(yystacksize * sizeof(*yyvsp));
        __yy_bcopy((char*)yyvs1, (char*)yyvs, size * sizeof(*yyvsp));
        __ALLOCA_free(yyvs1, yyvsa);
#ifdef YY_parse_LSP_NEEDED
        yyls = (YY_parse_LTYPE*)__ALLOCA_alloca(yystacksize * sizeof(*yylsp));
        __yy_bcopy((char*)yyls1, (char*)yyls, size * sizeof(*yylsp));
        __ALLOCA_free(yyls1, yylsa);
#endif
#endif /* no yyoverflow */

        yyssp = yyss + size - 1;
        yyvsp = yyvs + size - 1;
#ifdef YY_parse_LSP_NEEDED
        yylsp = yyls + size - 1;
#endif

#if YY_parse_DEBUG != 0
        if (YY_parse_DEBUG_FLAG)
            fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

        if (yyssp >= yyss + yystacksize - 1)
            YYABORT;
    }

#if YY_parse_DEBUG != 0
    if (YY_parse_DEBUG_FLAG)
        fprintf(stderr, "Entering state %d\n", yystate);
#endif

    YYGOTO(yybackup);
    YYLABEL(yybackup)

        /* Do appropriate processing given the current state.  */
        /* Read a lookahead token if we need one and don't already have one.  */
        /* YYLABEL(yyresume) */

          /* First try to decide what to do without reference to lookahead token.  */

        yyn = yypact[yystate];
    if (yyn == YYFLAG)
        YYGOTO(yydefault);

    /* Not known => get a lookahead token if don't already have one.  */

    /* yychar is either YYEMPTY or YYEOF
       or a valid token in external form.  */

    if (YY_parse_CHAR == YYEMPTY)
    {
#if YY_parse_DEBUG != 0
        if (YY_parse_DEBUG_FLAG)
            fprintf(stderr, "Reading a token: ");
#endif
        YY_parse_CHAR = YYLEX;
    }

    /* Convert token to internal form (in yychar1) for indexing tables with */

    if (YY_parse_CHAR <= 0)           /* This means end of input. */
    {
        yychar1 = 0;
        YY_parse_CHAR = YYEOF;                /* Don't call YYLEX any more */

#if YY_parse_DEBUG != 0
        if (YY_parse_DEBUG_FLAG)
            fprintf(stderr, "Now at end of input.\n");
#endif
    }
    else
    {
        yychar1 = YYTRANSLATE(YY_parse_CHAR);

#if YY_parse_DEBUG != 0
        if (YY_parse_DEBUG_FLAG)
        {
            fprintf(stderr, "Next token is %d (%s", YY_parse_CHAR, yytname[yychar1]);
            /* Give the individual parser a way to print the precise meaning
               of a token, for further debugging info.  */
#ifdef YYPRINT
            YYPRINT(stderr, YY_parse_CHAR, YY_parse_LVAL);
#endif
            fprintf(stderr, ")\n");
        }
#endif
    }

    yyn += yychar1;
    if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
        YYGOTO(yydefault);

    yyn = yytable[yyn];

    /* yyn is what to do for this token type in this state.
       Negative => reduce, -yyn is rule number.
       Positive => shift, yyn is new state.
         New state is final state => don't bother to shift,
         just return success.
       0, or most negative number => error.  */

    if (yyn < 0)
    {
        if (yyn == YYFLAG)
            YYGOTO(yyerrlab);
        yyn = -yyn;
        YYGOTO(yyreduce);
    }
    else if (yyn == 0)
        YYGOTO(yyerrlab);

    if (yyn == YYFINAL)
        YYACCEPT;

    /* Shift the lookahead token.  */

#if YY_parse_DEBUG != 0
    if (YY_parse_DEBUG_FLAG)
        fprintf(stderr, "Shifting token %d (%s), ", YY_parse_CHAR, yytname[yychar1]);
#endif

    /* Discard the token being shifted unless it is eof.  */
    if (YY_parse_CHAR != YYEOF)
        YY_parse_CHAR = YYEMPTY;

    *++yyvsp = YY_parse_LVAL;
#ifdef YY_parse_LSP_NEEDED
    * ++yylsp = YY_parse_LLOC;
#endif

    /* count tokens shifted since error; after three, turn off error status.  */
    if (yyerrstatus) yyerrstatus--;

    yystate = yyn;
    YYGOTO(yynewstate);

    /* Do the default action for the current state.  */
    YYLABEL(yydefault)

        yyn = yydefact[yystate];
    if (yyn == 0)
        YYGOTO(yyerrlab);

    /* Do a reduction.  yyn is the number of a rule to reduce with.  */
    YYLABEL(yyreduce)
        yylen = yyr2[yyn];
    if (yylen > 0)
        yyval = yyvsp[1 - yylen]; /* implement default value of the action */

#if YY_parse_DEBUG != 0
    if (YY_parse_DEBUG_FLAG)
    {
        int i;

        fprintf(stderr, "Reducing via rule %d (line %d), ",
            yyn, yyrline[yyn]);

        /* Print the symbols being reduced, and their result.  */
        for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
            fprintf(stderr, "%s ", yytname[yyrhs[i]]);
        fprintf(stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


    /* #line 811 "bison.cc" */
#line 1048 "fparse.cpp"

    switch (yyn) {

    case 2:
#line 60 "formula.y"
    {
        if (tree) delete(tree);
        tree = yyvsp[0].node;
        ;
        break; }
    case 3:
#line 65 "formula.y"
    {
        LPCWSTR c1 = L"Formula syntax error";
        LPCWSTR c2 = L"Error";
        ::MessageBox(NULL, c1, c2, MB_OK | MB_ICONERROR);
        if (tree) delete (tree);
        tree = NULL;
        if (str) free(str);
        YYABORT;
        ;
        break; }
    case 4:
#line 75 "formula.y"
    { yyval.node = new parenthesis_node_t(yyvsp[-1].node);;
    break; }
    case 5:
#line 76 "formula.y"
    { yyval.node = new parenthesis_node_t(yyvsp[-1].node);;
    break; }
    case 6:
#line 77 "formula.y"
    { yyval.node = new not_node_t(yyvsp[0].node); ;
    break; }
    case 7:
#line 78 "formula.y"
    { yyval.node = new and_node_t(yyvsp[-2].node, yyvsp[0].node);;
    break; }
    case 8:
#line 79 "formula.y"
    { yyval.node = new and_node_t(yyvsp[-2].node, yyvsp[0].node);;
    break; }
    case 9:
#line 80 "formula.y"
    { yyval.node = new and_node_t(yyvsp[-2].node, yyvsp[0].node);;
    break; }
    case 10:
#line 81 "formula.y"
    { yyval.node = new and_node_t(yyvsp[-1].node, yyvsp[0].node);;
    break; }
    case 11:
#line 82 "formula.y"
    { yyval.node = new or_node_t(yyvsp[-2].node, yyvsp[0].node);;
    break; }
    case 12:
#line 83 "formula.y"
    { yyval.node = new or_node_t(yyvsp[-2].node, yyvsp[0].node);;
    break; }
    case 13:
#line 84 "formula.y"
    { yyval.node = new or_node_t(yyvsp[-2].node, yyvsp[0].node);;
    break; }
    case 14:
#line 85 "formula.y"
    { yyval.node = new variable_node_t(yyvsp[0].nb); ;
    break; }
    case 15:
#line 86 "formula.y"
    { yyval.node = new variable_node_t(yyvsp[0].nb); ;
    break; }
    case 16:
#line 87 "formula.y"
    {
        if (yyvsp[0].nb == 0) yyval.node = new const_node_t(false);
        else yyval.node = new const_node_t(true);
        ;
        break; }
    }

#line 811 "bison.cc"
    /* the action file gets copied in in place of this dollarsign  */
    yyvsp -= yylen;
    yyssp -= yylen;
#ifdef YY_parse_LSP_NEEDED
    yylsp -= yylen;
#endif

#if YY_parse_DEBUG != 0
    if (YY_parse_DEBUG_FLAG)
    {
        short* ssp1 = yyss - 1;
        fprintf(stderr, "state stack now");
        while (ssp1 != yyssp)
            fprintf(stderr, " %d", *++ssp1);
        fprintf(stderr, "\n");
    }
#endif

    * ++yyvsp = yyval;

#ifdef YY_parse_LSP_NEEDED
    yylsp++;
    if (yylen == 0)
    {
        yylsp->first_line = YY_parse_LLOC.first_line;
        yylsp->first_column = YY_parse_LLOC.first_column;
        yylsp->last_line = (yylsp - 1)->last_line;
        yylsp->last_column = (yylsp - 1)->last_column;
        yylsp->text = 0;
    }
    else
    {
        yylsp->last_line = (yylsp + yylen - 1)->last_line;
        yylsp->last_column = (yylsp + yylen - 1)->last_column;
    }
#endif

    /* Now "shift" the result of the reduction.
       Determine what state that goes to,
       based on the state we popped back to
       and the rule number reduced by.  */

    yyn = yyr1[yyn];

    yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
    if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
        yystate = yytable[yystate];
    else
        yystate = yydefgoto[yyn - YYNTBASE];

    YYGOTO(yynewstate);

    YYLABEL(yyerrlab)   /* here on detecting error */

        if (!yyerrstatus)
            /* If not already recovering from an error, report this error.  */
        {
            ++YY_parse_NERRS;

#ifdef YY_parse_ERROR_VERBOSE
            yyn = yypact[yystate];

            if (yyn > YYFLAG && yyn < YYLAST)
            {
                int size = 0;
                char* msg;
                int x, count;

                count = 0;
                /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
                for (x = (yyn < 0 ? -yyn : 0);
                    x < (sizeof(yytname) / sizeof(char*)); x++)
                    if (yycheck[x + yyn] == x)
                        size += strlen(yytname[x]) + 15, count++;
                msg = (char*)malloc(size + 15);
                if (msg != 0)
                {
                    strcpy(msg, "parse error");

                    if (count < 5)
                    {
                        count = 0;
                        for (x = (yyn < 0 ? -yyn : 0);
                            x < (sizeof(yytname) / sizeof(char*)); x++)
                            if (yycheck[x + yyn] == x)
                            {
                                strcat(msg, count == 0 ? ", expecting `" : " or `");
                                strcat(msg, yytname[x]);
                                strcat(msg, "'");
                                count++;
                            }
                    }
                    YY_parse_ERROR(msg);
                    free(msg);
                }
                else
                    YY_parse_ERROR("parse error; also virtual memory exceeded");
            }
            else
#endif /* YY_parse_ERROR_VERBOSE */
                char c[12] = {'p', 'a', 'r', 's', 'e', ' ', 'e', 'r', 'r', 'o', 'r', '\0'};
                YY_parse_ERROR(c);
        }

    YYGOTO(yyerrlab1);
    YYLABEL(yyerrlab1)   /* here on error raised explicitly by an action */

        if (yyerrstatus == 3)
        {
            /* if just tried and failed to reuse lookahead token after an error, discard it.  */

            /* return failure if at end of input */
            if (YY_parse_CHAR == YYEOF)
                YYABORT;

#if YY_parse_DEBUG != 0
            if (YY_parse_DEBUG_FLAG)
                fprintf(stderr, "Discarding token %d (%s).\n", YY_parse_CHAR, yytname[yychar1]);
#endif

            YY_parse_CHAR = YYEMPTY;
        }

    /* Else will try to reuse lookahead token
       after shifting the error token.  */

    yyerrstatus = 3;              /* Each real token shifted decrements this */

    YYGOTO(yyerrhandle);

    YYLABEL(yyerrdefault)  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
        yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
    if (yyn) YYGOTO(yydefault);
#endif

    YYLABEL(yyerrpop)   /* pop the current state because it cannot handle the error token */

        if (yyssp == yyss) YYABORT;
    yyvsp--;
    yystate = *--yyssp;
#ifdef YY_parse_LSP_NEEDED
    yylsp--;
#endif

#if YY_parse_DEBUG != 0
    if (YY_parse_DEBUG_FLAG)
    {
        short* ssp1 = yyss - 1;
        fprintf(stderr, "Error: state stack now");
        while (ssp1 != yyssp)
            fprintf(stderr, " %d", *++ssp1);
        fprintf(stderr, "\n");
    }
#endif

    YYLABEL(yyerrhandle)

        yyn = yypact[yystate];
    if (yyn == YYFLAG)
        YYGOTO(yyerrdefault);

    yyn += YYTERROR;
    if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
        YYGOTO(yyerrdefault);

    yyn = yytable[yyn];
    if (yyn < 0)
    {
        if (yyn == YYFLAG)
            YYGOTO(yyerrpop);
        yyn = -yyn;
        YYGOTO(yyreduce);
    }
    else if (yyn == 0)
        YYGOTO(yyerrpop);

    if (yyn == YYFINAL)
        YYACCEPT;

#if YY_parse_DEBUG != 0
    if (YY_parse_DEBUG_FLAG)
        fprintf(stderr, "Shifting error token, ");
#endif

    * ++yyvsp = YY_parse_LVAL;
#ifdef YY_parse_LSP_NEEDED
    * ++yylsp = YY_parse_LLOC;
#endif

    yystate = yyn;
    YYGOTO(yynewstate);
    /* end loop, in which YYGOTO may be used. */
    YYENDGOTO
}

/* END */

/* #line 1010 "bison.cc" */
#line 1328 "fparse.cpp"
#line 93 "formula.y"


//************************************************************************************************
// Set the sring 
//************************************************************************************************

void formula_parse_t::set_str(const char* const _str)
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
        if (buffer[c] >= '0' && buffer[c] <= '9')
        {
            is_num = true;
        }
        else {
            if (is_num)
            {
                buffer[c] = '\0';
                yylval.nb = atoi(buffer);
                cur += c;
                return INTEGER;
            }
            else {
                cur++;
                return (int)buffer[c];
            }
        }
        c++;
    }

}

//************************************************************************************************
// error callback
//************************************************************************************************


void formula_parse_t::yyerror(char* msg)
{
    LPCWSTR c = L"Bison Parse Error :";
    wchar_t wtext[20];
    mbstowcs(wtext, msg, strlen(msg) + 1);
    ::MessageBox(NULL, wtext, c, MB_OK | MB_ICONERROR);
}

//************************************************************************************************
// copy operator
//************************************************************************************************

formula_parse_t& formula_parse_t::operator=(formula_parse_t& src)
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

formula_parse_t::formula_parse_t(formula_parse_t& src)
{
    tree = NULL;
    if (src.tree) tree = src.tree->clone();
    str = NULL;
    if (src.str) str = strdup(src.str);
    cur = src.cur;
}
