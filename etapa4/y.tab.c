/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20160324

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "hash.h"
    #include "astree.h"
    #include "semantic.h"
    void yyerror(char *s);

#line 14 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{ HASH_NODE* symbol; ASTREE* astree;} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 39 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_BYTE 257
#define KW_SHORT 258
#define KW_LONG 259
#define KW_FLOAT 260
#define KW_DOUBLE 261
#define KW_WHEN 262
#define KW_THEN 263
#define KW_ELSE 264
#define KW_WHILE 265
#define KW_FOR 266
#define KW_TO 267
#define KW_READ 268
#define KW_RETURN 269
#define KW_PRINT 270
#define OPERATOR_LE 271
#define OPERATOR_GE 272
#define OPERATOR_EQ 273
#define OPERATOR_NE 274
#define OPERATOR_AND 275
#define OPERATOR_OR 276
#define TK_IDENTIFIER 277
#define LIT_INTEGER 278
#define LIT_REAL 279
#define LIT_CHAR 280
#define LIT_STRING 281
#define TOKEN_ERROR 282
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    3,    5,    5,    5,    5,
    5,    5,    5,    6,    6,    8,    8,    7,    7,    4,
   10,   10,   12,   12,   13,    9,    9,    9,    9,    9,
   11,   15,   15,   14,   14,   14,   14,   14,   14,   14,
   17,   17,   20,   20,   19,   19,   19,   19,   16,   16,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   21,
   21,   22,   22,
};
static const YYINT yylen[] = {                            2,
    1,    2,    0,    1,    1,    4,    2,    2,    2,    5,
    5,    5,    4,    2,    1,    2,    1,    2,    1,    7,
    1,    0,    3,    1,    2,    1,    1,    1,    1,    1,
    1,    3,    0,    1,    3,    2,    2,    2,    1,    0,
    2,    1,    1,    1,    6,    8,    5,    9,    3,    5,
    3,    1,    4,    4,    1,    1,    1,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    2,
    0,    3,    0,
};
static const YYINT yydefred[] = {                         0,
   26,   27,   28,   29,   30,    0,    0,    1,    0,    5,
    4,    0,    0,    2,    0,    0,    0,    0,    6,    8,
    9,    7,    0,    0,    0,   21,    0,    0,   25,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   33,
    0,   31,   34,   39,   23,    0,    0,    0,   10,   12,
   11,    0,    0,    0,   36,    0,   55,   57,   56,    0,
    0,   43,   37,    0,    0,    0,    0,    0,   20,   14,
   18,   16,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   41,    0,    0,   35,    0,    0,    0,    0,    0,    0,
    0,   51,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   64,   67,    0,   32,    0,   47,    0,   53,
    0,   70,   54,    0,    0,    0,    0,    0,    0,   72,
   46,    0,   48,
};
static const YYINT yydgoto[] = {                          7,
    8,    9,   10,   11,   16,   49,   50,   51,   12,   25,
   41,   26,   27,   42,   68,   43,   63,   64,   44,   65,
  101,  122,
};
static const YYINT yysindex[] = {                      -222,
    0,    0,    0,    0,    0,  -44,    0,    0, -222,    0,
    0, -262, -157,    0,  -22,  -28,  -75, -157,    0,    0,
    0,    0, -253, -244,   18,    0,   -4,  -52,    0, -116,
 -157, -193,    8,   12,   16, -216,  -11,   11,  -29,    0,
   13,    0,    0,    0,    0, -207, -205, -202,    0,    0,
    0,  -11,  -11, -196,    0,  -27,    0,    0,    0,  -11,
  297,    0,    0,  297,   11,  -11,  -11,  342,    0,    0,
    0,    0,  410,  421,   34,  -11,  -11,  433,  -11,  -11,
  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,  -11,
    0,  297,  252,    0,   38, -158, -116,  -11,  319,  454,
   65,    0,   15,   15,   15,   15,  470,  470,   37,   37,
    7,    7,    0,    0,  -11,    0, -116,    0,  275,    0,
  -11,    0,    0,  297, -156,  -11,  454, -116,  443,    0,
    0, -116,    0,
};
static const YYINT yyrindex[] = {                       107,
    0,    0,    0,    0,    0,    0,    0,    0,  107,    0,
    0,    0,    0,    0,    0,    0,    0,   68,    0,    0,
    0,    0,    0,    0,    0,    0,   69,    0,    0,   53,
    0,   57,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   58,  -28,   60,    0,    0,
    0,    0,    0,    0,    0,  399,    0,    0,    0,    0,
  -57,    0,    0,  123,  -51,    0,    0,   53,    0,    0,
    0,    0,    0,    0,    0,    0,   79,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -50,    0,    0,    0,    0,  -49,    0,    0,   80,
    0,    0,   52,   74,   96,  118,  151,  158,    6,   29,
  -40,  -17,    0,    0,    0,    0,  -49,    0,    0,    0,
    0,    0,    0,  -48,   64,    0,   80,  -49,    0,    0,
    0,  -49,    0,
};
static const YYINT yygindex[] = {                         0,
  115,    0,    0,    0,    0,   81,   78,   82,   -1,    0,
    0,   95,    0,  -34,    0,    0,   63,  685,    0,    0,
    0,    2,
};
#define YYTABLESIZE 811
static const YYINT yytable[] = {                         66,
   66,   38,   66,   66,   66,   67,   40,   42,   49,   40,
   50,   17,   77,   13,   15,   23,   24,   18,   66,   66,
   66,   66,   65,   65,   28,   65,   65,   65,   60,   24,
   19,   66,   29,   95,    1,    2,    3,    4,    5,   31,
   32,   65,   65,   65,   65,   68,   68,   52,   89,   68,
   60,   53,   66,   90,    6,   54,   89,   88,   30,   87,
   55,   90,  118,   76,   68,   68,   68,   68,   69,   69,
   46,   69,   69,   47,   85,   65,   86,   48,   89,   88,
   75,   87,  125,   90,   46,   47,   48,   69,   69,   69,
   69,   58,   58,  131,   98,   58,  116,  133,   68,    1,
    2,    3,    4,    5,  117,  123,    3,  128,   22,   24,
   58,   40,   58,   59,   59,   13,   15,   59,   17,   71,
   73,   69,   45,   14,   71,   45,   70,   91,  130,   72,
    0,    0,   59,    0,   59,   60,   60,    0,    0,   60,
    0,    0,    0,    0,   58,   33,    0,    0,   34,   35,
    0,   36,   37,   38,   60,    0,   60,   61,   61,    0,
   39,   61,   44,    0,    0,    0,   59,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   61,    0,   61,    0,
    0,   44,    0,    0,    0,    0,    0,    0,   60,    0,
   62,   62,    0,    0,   62,    0,    0,   63,   63,    0,
    0,   63,   20,   21,   22,    0,   38,    0,    0,   62,
   61,   62,   42,   49,   40,   50,   63,    0,   63,    0,
    0,    0,    0,   66,    0,    0,   66,    0,    0,    0,
   66,   66,   66,   66,   66,   66,   66,   66,   66,   66,
   66,    0,    0,   62,    0,    0,   65,    0,    0,   65,
   63,    0,    0,   65,   65,   65,   65,   65,   65,   65,
   65,   65,   65,   65,    0,   56,   57,   58,   59,   68,
    0,    0,   68,    0,    0,    0,   68,   68,   68,   68,
   68,   68,   68,   68,   68,   68,   68,   56,   57,   58,
   59,   62,   69,   89,   88,   69,   87,    0,   90,   69,
   69,   69,   69,   69,   69,   69,   69,   69,   69,   69,
    0,   85,  115,   86,    0,   58,   89,   88,   58,   87,
    0,   90,   58,   58,   58,   58,   58,   58,   58,   58,
   58,   58,   58,    0,   85,    0,   86,   59,   89,   88,
   59,   87,    0,   90,   59,   59,   59,   59,   59,   59,
   59,   59,   59,   59,   59,    0,   85,    0,   86,   60,
   89,   88,   60,   87,    0,   90,   60,   60,   60,   60,
   60,   60,   60,   60,   60,   60,   60,    0,   85,    0,
   86,   61,    0,    0,   61,    0,   44,    0,   61,   61,
   61,   61,   61,   61,   61,   61,   61,   61,   61,   44,
   44,   44,   44,   44,    0,    0,    0,    0,    0,    0,
    0,  120,    0,    0,   62,    0,    0,   62,    0,    0,
    0,   63,    0,    0,   63,   62,   62,   62,   62,   62,
   62,   62,   63,   63,   63,   63,   63,   63,   63,   52,
   52,   52,   52,   52,    0,   52,    0,    0,    0,    0,
   96,   89,   88,    0,   87,    0,   90,   52,   52,   52,
   52,   97,   89,   88,   40,   87,   94,   90,    0,   85,
    0,   86,    0,  102,   89,   88,    0,   87,    0,   90,
   85,    0,   86,  132,   89,   88,    0,   87,    0,   90,
    0,   52,   85,    0,   86,   89,   88,  121,   87,    0,
   90,    0,   85,    0,   86,    0,    0,    0,    0,    0,
    0,   89,   88,   85,   87,   86,   90,    0,    0,    0,
    0,    0,   79,   80,   81,   82,   83,   84,    0,   85,
    0,   86,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  126,    0,    0,    0,   79,   80,   81,   82,   83,
   84,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   79,   80,   81,
   82,   83,   84,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   79,
   80,   81,   82,   83,   84,    0,    0,    0,    0,    0,
    0,    0,    0,   33,    0,    0,   34,   35,    0,   36,
   37,   38,    0,    0,    0,    0,    0,    0,   39,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   52,    0,    0,   52,    0,    0,    0,   52,
   52,   52,   52,   52,   52,   52,   52,   52,   52,   52,
   79,   80,   81,   82,   83,   84,    0,    0,    0,    0,
    0,   79,   80,   81,   82,   83,   84,    0,    0,    0,
    0,    0,    0,   79,   80,   81,   82,   83,   84,    0,
    0,    0,    0,   79,   80,   81,   82,   83,   84,    0,
    0,   61,    0,    0,   79,   80,   81,   82,   83,   84,
    0,    0,    0,    0,    0,    0,   73,   74,    0,    0,
   79,   80,   81,   82,   78,    0,    0,    0,    0,    0,
   92,   93,    0,    0,    0,    0,    0,    0,    0,    0,
   99,  100,    0,  103,  104,  105,  106,  107,  108,  109,
  110,  111,  112,  113,  114,    0,    0,    0,    0,    0,
    0,    0,  119,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  124,
    0,    0,    0,    0,    0,  127,    0,    0,    0,    0,
  129,
};
static const YYINT yycheck[] = {                         40,
   41,   59,   43,   44,   45,   35,  123,   59,   59,   59,
   59,   13,   40,   58,  277,   91,   18,   40,   59,   60,
   61,   62,   40,   41,  278,   43,   44,   45,   40,   31,
   59,   61,  277,   68,  257,  258,  259,  260,  261,   44,
   93,   59,   60,   61,   62,   40,   41,   40,   42,   44,
   40,   40,   93,   47,  277,   40,   42,   43,   41,   45,
  277,   47,   97,   91,   59,   60,   61,   62,   40,   41,
  278,   59,   44,  279,   60,   93,   62,  280,   42,   43,
  277,   45,  117,   47,  278,  279,  280,   59,   60,   61,
   62,   40,   41,  128,   61,   44,   59,  132,   93,  257,
  258,  259,  260,  261,  263,   41,    0,  264,   41,   41,
   59,   59,   61,   40,   41,   59,   59,   44,   59,   41,
   41,   93,   59,    9,   47,   31,   46,   65,  127,   48,
   -1,   -1,   59,   -1,   61,   40,   41,   -1,   -1,   44,
   -1,   -1,   -1,   -1,   93,  262,   -1,   -1,  265,  266,
   -1,  268,  269,  270,   59,   -1,   61,   40,   41,   -1,
  277,   44,   40,   -1,   -1,   -1,   93,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   59,   -1,   61,   -1,
   -1,   59,   -1,   -1,   -1,   -1,   -1,   -1,   93,   -1,
   40,   41,   -1,   -1,   44,   -1,   -1,   40,   41,   -1,
   -1,   44,  278,  279,  280,   -1,  264,   -1,   -1,   59,
   93,   61,  264,  264,  264,  264,   59,   -1,   61,   -1,
   -1,   -1,   -1,  264,   -1,   -1,  267,   -1,   -1,   -1,
  271,  272,  273,  274,  275,  276,  277,  278,  279,  280,
  281,   -1,   -1,   93,   -1,   -1,  264,   -1,   -1,  267,
   93,   -1,   -1,  271,  272,  273,  274,  275,  276,  277,
  278,  279,  280,  281,   -1,  277,  278,  279,  280,  264,
   -1,   -1,  267,   -1,   -1,   -1,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,  277,  278,  279,
  280,  281,  264,   42,   43,  267,   45,   -1,   47,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
   -1,   60,   61,   62,   -1,  264,   42,   43,  267,   45,
   -1,   47,  271,  272,  273,  274,  275,  276,  277,  278,
  279,  280,  281,   -1,   60,   -1,   62,  264,   42,   43,
  267,   45,   -1,   47,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  280,  281,   -1,   60,   -1,   62,  264,
   42,   43,  267,   45,   -1,   47,  271,  272,  273,  274,
  275,  276,  277,  278,  279,  280,  281,   -1,   60,   -1,
   62,  264,   -1,   -1,  267,   -1,  264,   -1,  271,  272,
  273,  274,  275,  276,  277,  278,  279,  280,  281,  277,
  278,  279,  280,  281,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   93,   -1,   -1,  264,   -1,   -1,  267,   -1,   -1,
   -1,  264,   -1,   -1,  267,  275,  276,  277,  278,  279,
  280,  281,  275,  276,  277,  278,  279,  280,  281,   41,
   42,   43,   44,   45,   -1,   47,   -1,   -1,   -1,   -1,
   41,   42,   43,   -1,   45,   -1,   47,   59,   60,   61,
   62,   41,   42,   43,  123,   45,  125,   47,   -1,   60,
   -1,   62,   -1,   41,   42,   43,   -1,   45,   -1,   47,
   60,   -1,   62,   41,   42,   43,   -1,   45,   -1,   47,
   -1,   93,   60,   -1,   62,   42,   43,   44,   45,   -1,
   47,   -1,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,
   -1,   42,   43,   60,   45,   62,   47,   -1,   -1,   -1,
   -1,   -1,  271,  272,  273,  274,  275,  276,   -1,   60,
   -1,   62,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  267,   -1,   -1,   -1,  271,  272,  273,  274,  275,
  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  271,  272,  273,
  274,  275,  276,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  271,
  272,  273,  274,  275,  276,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  262,   -1,   -1,  265,  266,   -1,  268,
  269,  270,   -1,   -1,   -1,   -1,   -1,   -1,  277,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  264,   -1,   -1,  267,   -1,   -1,   -1,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  271,  272,  273,  274,  275,  276,   -1,   -1,   -1,   -1,
   -1,  271,  272,  273,  274,  275,  276,   -1,   -1,   -1,
   -1,   -1,   -1,  271,  272,  273,  274,  275,  276,   -1,
   -1,   -1,   -1,  271,  272,  273,  274,  275,  276,   -1,
   -1,   37,   -1,   -1,  271,  272,  273,  274,  275,  276,
   -1,   -1,   -1,   -1,   -1,   -1,   52,   53,   -1,   -1,
  271,  272,  273,  274,   60,   -1,   -1,   -1,   -1,   -1,
   66,   67,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   76,   77,   -1,   79,   80,   81,   82,   83,   84,   85,
   86,   87,   88,   89,   90,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   98,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  115,
   -1,   -1,   -1,   -1,   -1,  121,   -1,   -1,   -1,   -1,
  126,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 282
#define YYUNDFTOKEN 307
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,"'#'",0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,
0,0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_BYTE","KW_SHORT","KW_LONG",
"KW_FLOAT","KW_DOUBLE","KW_WHEN","KW_THEN","KW_ELSE","KW_WHILE","KW_FOR",
"KW_TO","KW_READ","KW_RETURN","KW_PRINT","OPERATOR_LE","OPERATOR_GE",
"OPERATOR_EQ","OPERATOR_NE","OPERATOR_AND","OPERATOR_OR","TK_IDENTIFIER",
"LIT_INTEGER","LIT_REAL","LIT_CHAR","LIT_STRING","TOKEN_ERROR",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : declist",
"declist : dec declist",
"declist :",
"dec : funcdec",
"dec : vardec",
"vardec : TK_IDENTIFIER ':' vartypeandvalue ';'",
"vartypeandvalue : vartype LIT_CHAR",
"vartypeandvalue : vartype LIT_INTEGER",
"vartypeandvalue : vartype LIT_REAL",
"vartypeandvalue : vartype '[' LIT_INTEGER ']' intlist",
"vartypeandvalue : vartype '[' LIT_INTEGER ']' charlist",
"vartypeandvalue : vartype '[' LIT_INTEGER ']' floatlist",
"vartypeandvalue : vartype '[' LIT_INTEGER ']'",
"intlist : LIT_INTEGER intlist",
"intlist : LIT_INTEGER",
"charlist : LIT_CHAR charlist",
"charlist : LIT_CHAR",
"floatlist : LIT_REAL floatlist",
"floatlist : LIT_REAL",
"funcdec : vartype TK_IDENTIFIER '(' parameters ')' funcbody ';'",
"parameters : paramlist",
"parameters :",
"paramlist : param ',' paramlist",
"paramlist : param",
"param : vartype TK_IDENTIFIER",
"vartype : KW_BYTE",
"vartype : KW_SHORT",
"vartype : KW_LONG",
"vartype : KW_FLOAT",
"vartype : KW_DOUBLE",
"funcbody : cmd",
"cmdlist : cmdlist cmd ';'",
"cmdlist :",
"cmd : atrib",
"cmd : '{' cmdlist '}'",
"cmd : KW_READ TK_IDENTIFIER",
"cmd : KW_PRINT printlist",
"cmd : KW_RETURN expr",
"cmd : control",
"cmd :",
"printlist : printelement printlist",
"printlist : printelement",
"printelement : LIT_STRING",
"printelement : expr",
"control : KW_WHEN '(' expr ')' KW_THEN cmd",
"control : KW_WHEN '(' expr ')' KW_THEN cmd KW_ELSE cmd",
"control : KW_WHILE '(' expr ')' cmd",
"control : KW_FOR '(' TK_IDENTIFIER '=' expr KW_TO expr ')' cmd",
"atrib : TK_IDENTIFIER '=' expr",
"atrib : TK_IDENTIFIER '#' expr '=' expr",
"expr : '(' expr ')'",
"expr : TK_IDENTIFIER",
"expr : TK_IDENTIFIER '[' expr ']'",
"expr : TK_IDENTIFIER '(' args ')'",
"expr : LIT_INTEGER",
"expr : LIT_CHAR",
"expr : LIT_REAL",
"expr : expr OPERATOR_LE expr",
"expr : expr OPERATOR_GE expr",
"expr : expr OPERATOR_EQ expr",
"expr : expr OPERATOR_NE expr",
"expr : expr OPERATOR_AND expr",
"expr : expr OPERATOR_OR expr",
"expr : expr '*' expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '/' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"args : expr argstail",
"args :",
"argstail : ',' expr argstail",
"argstail :",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 197 "parser.y"

void yyerror(char *s)
{
    int lineNum = getLineNumber();
    fprintf(stdout, "ERROR\n%s\nna linha: %i\n\n   ", s, lineNum);

    exit(3);
}
#line 492 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 79 "parser.y"
	{ root = yystack.l_mark[0].astree; }
break;
case 2:
#line 81 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_PROGRAM, NULL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 3:
#line 82 "parser.y"
	{ yyval.astree = 0; }
break;
case 4:
#line 84 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 5:
#line 85 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 6:
#line 87 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_VARDEC, yystack.l_mark[-3].symbol, yystack.l_mark[-1].astree, 0, 0, 0); }
break;
case 7:
#line 89 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWCHAR, yystack.l_mark[0].symbol, yystack.l_mark[-1].astree, 0, 0, 0); }
break;
case 8:
#line 90 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWINT, yystack.l_mark[0].symbol, yystack.l_mark[-1].astree, 0, 0, 0); }
break;
case 9:
#line 91 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWREAL, yystack.l_mark[0].symbol, yystack.l_mark[-1].astree, 0, 0, 0); }
break;
case 10:
#line 92 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWARRAYINT, yystack.l_mark[-2].symbol, yystack.l_mark[-4].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 11:
#line 93 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWARRAYCHAR, yystack.l_mark[-2].symbol, yystack.l_mark[-4].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 12:
#line 94 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWARRAYFLOAT, yystack.l_mark[-2].symbol, yystack.l_mark[-4].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 13:
#line 95 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWARRAY, yystack.l_mark[-1].symbol, yystack.l_mark[-3].astree, 0, 0, 0); }
break;
case 14:
#line 97 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_INTLIST, yystack.l_mark[-1].symbol, yystack.l_mark[0].astree, 0, 0, 0); }
break;
case 15:
#line 98 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LITINT, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 16:
#line 101 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CHARLIST, yystack.l_mark[-1].symbol, yystack.l_mark[0].astree, 0, 0, 0); }
break;
case 17:
#line 102 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LITCHAR, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 18:
#line 105 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FLOATLIST, yystack.l_mark[-1].symbol, yystack.l_mark[0].astree, 0, 0, 0); }
break;
case 19:
#line 106 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LITREAL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 20:
#line 109 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_FUNCDEC, yystack.l_mark[-5].symbol, yystack.l_mark[-6].astree, yystack.l_mark[-3].astree, yystack.l_mark[-1].astree, 0); }
break;
case 21:
#line 112 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 22:
#line 113 "parser.y"
	{ yyval.astree = 0; }
break;
case 23:
#line 116 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_PARAMLIST, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 24:
#line 117 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 25:
#line 120 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_PARAM, yystack.l_mark[0].symbol, yystack.l_mark[-1].astree, 0, 0, 0); }
break;
case 26:
#line 123 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWBYTE, NULL, 0, 0, 0, 0); }
break;
case 27:
#line 124 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWSHORT, NULL, 0, 0, 0, 0); }
break;
case 28:
#line 125 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWLONG, NULL, 0, 0, 0, 0); }
break;
case 29:
#line 126 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWFLOAT, NULL, 0, 0, 0, 0); }
break;
case 30:
#line 127 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWDOUBLE, NULL, 0, 0, 0, 0); }
break;
case 31:
#line 130 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 32:
#line 133 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMDLIST, NULL, yystack.l_mark[-2].astree, yystack.l_mark[-1].astree, 0, 0); }
break;
case 33:
#line 134 "parser.y"
	{ yyval.astree = 0; }
break;
case 34:
#line 137 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 35:
#line 138 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_CMDCOLCHETES, NULL, yystack.l_mark[-1].astree, 0, 0, 0); }
break;
case 36:
#line 139 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWREAD, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 37:
#line 140 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWPRINT, NULL, yystack.l_mark[0].astree, 0, 0, 0); }
break;
case 38:
#line 141 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWRETURN, NULL, yystack.l_mark[0].astree, 0, 0, 0); }
break;
case 39:
#line 142 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 40:
#line 143 "parser.y"
	{ yyval.astree = 0; }
break;
case 41:
#line 146 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_PRINTLIST, NULL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 42:
#line 147 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 43:
#line 150 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LITSTRING, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 44:
#line 151 "parser.y"
	{ yyval.astree = yystack.l_mark[0].astree; }
break;
case 45:
#line 154 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWWHENTHEN, NULL, yystack.l_mark[-3].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 46:
#line 155 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWWHENTHENELSE, NULL, yystack.l_mark[-5].astree, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0); }
break;
case 47:
#line 156 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWWHILE, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 48:
#line 157 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_KWFOR, yystack.l_mark[-6].symbol, yystack.l_mark[-4].astree, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0); }
break;
case 49:
#line 160 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ATRIB, yystack.l_mark[-2].symbol, yystack.l_mark[0].astree, 0, 0, 0); }
break;
case 50:
#line 161 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ATRIBARRAY, yystack.l_mark[-4].symbol, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 51:
#line 165 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_EXPRPARENTESIS, NULL, yystack.l_mark[-1].astree, 0, 0, 0); }
break;
case 52:
#line 166 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_TKID, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 53:
#line 167 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_TKIDARRAY, yystack.l_mark[-3].symbol, yystack.l_mark[-1].astree, 0, 0, 0); }
break;
case 54:
#line 168 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_TKIDFUNC, yystack.l_mark[-3].symbol, yystack.l_mark[-1].astree, 0, 0, 0); }
break;
case 55:
#line 169 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LITINT, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 56:
#line 170 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LITCHAR, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 57:
#line 171 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LITREAL, yystack.l_mark[0].symbol, 0, 0, 0, 0); }
break;
case 58:
#line 172 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LESSEQUAL, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 59:
#line 173 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_GREATEREQUAL, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 60:
#line 174 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_EQUAL, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 61:
#line 175 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_NOTEQUAL, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 62:
#line 176 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_AND, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 63:
#line 177 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_OR, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 64:
#line 178 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_MULT, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 65:
#line 179 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ADD, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 66:
#line 180 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_SUB, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 67:
#line 181 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_DIV, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 68:
#line 182 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_LESS, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 69:
#line 183 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_GREATER, NULL, yystack.l_mark[-2].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 70:
#line 186 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ARGS, NULL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 71:
#line 187 "parser.y"
	{ yyval.astree = 0; }
break;
case 72:
#line 190 "parser.y"
	{ yyval.astree = astreeCreate(ASTREE_ARGSTAIL, NULL, yystack.l_mark[-1].astree, yystack.l_mark[0].astree, 0, 0); }
break;
case 73:
#line 191 "parser.y"
	{ yyval.astree = 0; }
break;
#line 986 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
