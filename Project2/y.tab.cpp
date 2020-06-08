/* A Bison parser, made by GNU Bison 3.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "project2.y"

extern int yylex();

#include "project2.h"
#include "stdio.h"

// function declaration
VALUE oper(char operC, VALUE v1, VALUE v2);
SymbolTable symbolTable = SymbolTable();

int yyerror(const char* s);
extern int yylineno;  // defined and maintained in lex
extern int yyparse();
extern FILE* yyin, *yyout;

// function name to dynamic tracking current function scope
ID* functionScopedPtr;
/* function called check parameter index*/
ID* functionCalledPtr;
int parameterIndex;

#line 93 "y.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID_NAME = 258,                 /* ID_NAME  */
    VALUE_TOKEN = 259,             /* VALUE_TOKEN  */
    VALUE_TYPE = 260,              /* VALUE_TYPE  */
    VAR = 261,                     /* VAR  */
    VAL = 262,                     /* VAL  */
    DEF = 263,                     /* DEF  */
    IF = 264,                      /* IF  */
    ELSE = 265,                    /* ELSE  */
    FOR = 266,                     /* FOR  */
    PRINT = 267,                   /* PRINT  */
    PRINTLN = 268,                 /* PRINTLN  */
    READ = 269,                    /* READ  */
    RETURN = 270,                  /* RETURN  */
    TO = 271,                      /* TO  */
    WHILE = 272,                   /* WHILE  */
    OBJECT = 273,                  /* OBJECT  */
    FOR_SET = 274,                 /* FOR_SET  */
    AND = 275,                     /* AND  */
    OR = 276,                      /* OR  */
    NOT = 277,                     /* NOT  */
    LT = 278,                      /* LT  */
    LE = 279,                      /* LE  */
    EQ = 280,                      /* EQ  */
    NQ = 281,                      /* NQ  */
    GE = 282,                      /* GE  */
    GT = 283,                      /* GT  */
    UMINUS = 284                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID_NAME 258
#define VALUE_TOKEN 259
#define VALUE_TYPE 260
#define VAR 261
#define VAL 262
#define DEF 263
#define IF 264
#define ELSE 265
#define FOR 266
#define PRINT 267
#define PRINTLN 268
#define READ 269
#define RETURN 270
#define TO 271
#define WHILE 272
#define OBJECT 273
#define FOR_SET 274
#define AND 275
#define OR 276
#define NOT 277
#define LT 278
#define LE 279
#define EQ 280
#define NQ 281
#define GE 282
#define GT 283
#define UMINUS 284

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "project2.y"


    /* id name */
    string* idName;

    /* constant exp*/
    VALUE* value;

    /* value type*/
    VALUETYPE* valueType;

#line 215 "y.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID_NAME = 3,                    /* ID_NAME  */
  YYSYMBOL_VALUE_TOKEN = 4,                /* VALUE_TOKEN  */
  YYSYMBOL_VALUE_TYPE = 5,                 /* VALUE_TYPE  */
  YYSYMBOL_VAR = 6,                        /* VAR  */
  YYSYMBOL_VAL = 7,                        /* VAL  */
  YYSYMBOL_DEF = 8,                        /* DEF  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_PRINT = 12,                     /* PRINT  */
  YYSYMBOL_PRINTLN = 13,                   /* PRINTLN  */
  YYSYMBOL_READ = 14,                      /* READ  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_TO = 16,                        /* TO  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_OBJECT = 18,                    /* OBJECT  */
  YYSYMBOL_FOR_SET = 19,                   /* FOR_SET  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_OR = 21,                        /* OR  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_LT = 23,                        /* LT  */
  YYSYMBOL_LE = 24,                        /* LE  */
  YYSYMBOL_EQ = 25,                        /* EQ  */
  YYSYMBOL_NQ = 26,                        /* NQ  */
  YYSYMBOL_GE = 27,                        /* GE  */
  YYSYMBOL_GT = 28,                        /* GT  */
  YYSYMBOL_UMINUS = 29,                    /* UMINUS  */
  YYSYMBOL_30_ = 30,                       /* '='  */
  YYSYMBOL_31_ = 31,                       /* '-'  */
  YYSYMBOL_32_ = 32,                       /* '+'  */
  YYSYMBOL_33_ = 33,                       /* '*'  */
  YYSYMBOL_34_ = 34,                       /* '/'  */
  YYSYMBOL_35_ = 35,                       /* '{'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_38_ = 38,                       /* ')'  */
  YYSYMBOL_39_ = 39,                       /* ':'  */
  YYSYMBOL_40_ = 40,                       /* ','  */
  YYSYMBOL_41_ = 41,                       /* '['  */
  YYSYMBOL_42_ = 42,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_PROGRAM = 44,                   /* PROGRAM  */
  YYSYMBOL_45_1 = 45,                      /* $@1  */
  YYSYMBOL_46_2 = 46,                      /* $@2  */
  YYSYMBOL_OBJCONTENT = 47,                /* OBJCONTENT  */
  YYSYMBOL_FUNCTION_DEFINITIONS = 48,      /* FUNCTION_DEFINITIONS  */
  YYSYMBOL_FUNCTION_DEFINITION = 49,       /* FUNCTION_DEFINITION  */
  YYSYMBOL_50_3 = 50,                      /* $@3  */
  YYSYMBOL_51_4 = 51,                      /* $@4  */
  YYSYMBOL_FUNCTION_DEFINITION2 = 52,      /* FUNCTION_DEFINITION2  */
  YYSYMBOL_FORMAL_ARGS = 53,               /* FORMAL_ARGS  */
  YYSYMBOL_ARG = 54,                       /* ARG  */
  YYSYMBOL_RETURN_STMT = 55,               /* RETURN_STMT  */
  YYSYMBOL_STMTS = 56,                     /* STMTS  */
  YYSYMBOL_STMT = 57,                      /* STMT  */
  YYSYMBOL_58_5 = 58,                      /* $@5  */
  YYSYMBOL_VALDECLARATION = 59,            /* VALDECLARATION  */
  YYSYMBOL_VARDECLARATION = 60,            /* VARDECLARATION  */
  YYSYMBOL_EXP = 61,                       /* EXP  */
  YYSYMBOL_FUNCTION_CALLED = 62,           /* FUNCTION_CALLED  */
  YYSYMBOL_63_6 = 63,                      /* $@6  */
  YYSYMBOL_FUNCTION_CALLED_ARGS = 64,      /* FUNCTION_CALLED_ARGS  */
  YYSYMBOL_FUNCTION_CALLED_ARG = 65,       /* FUNCTION_CALLED_ARG  */
  YYSYMBOL_IF_STMT = 66,                   /* IF_STMT  */
  YYSYMBOL_67_7 = 67,                      /* $@7  */
  YYSYMBOL_68_8 = 68,                      /* $@8  */
  YYSYMBOL_69_9 = 69,                      /* $@9  */
  YYSYMBOL_ELSE_STMT = 70,                 /* ELSE_STMT  */
  YYSYMBOL_71_10 = 71,                     /* $@10  */
  YYSYMBOL_WHILE_STMT = 72,                /* WHILE_STMT  */
  YYSYMBOL_73_11 = 73,                     /* $@11  */
  YYSYMBOL_74_12 = 74,                     /* $@12  */
  YYSYMBOL_FOR_STMT = 75,                  /* FOR_STMT  */
  YYSYMBOL_76_13 = 76                      /* $@13  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   278

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  153

#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,    33,    32,    40,    31,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    39,     2,
       2,    30,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    91,    91,    99,    90,   120,   123,   124,   129,   140,
     128,   162,   167,   175,   176,   179,   190,   194,   204,   217,
     218,   219,   223,   234,   235,   236,   237,   238,   242,   246,
     253,   252,   260,   261,   262,   266,   284,   302,   320,   338,
     356,   371,   396,   402,   414,   415,   416,   417,   419,   422,
     423,   425,   426,   427,   428,   429,   430,   431,   432,   433,
     438,   437,   464,   465,   469,   481,   486,   491,   491,   485,
     495,   495,   496,   502,   507,   501,   512,   511
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID_NAME",
  "VALUE_TOKEN", "VALUE_TYPE", "VAR", "VAL", "DEF", "IF", "ELSE", "FOR",
  "PRINT", "PRINTLN", "READ", "RETURN", "TO", "WHILE", "OBJECT", "FOR_SET",
  "AND", "OR", "NOT", "LT", "LE", "EQ", "NQ", "GE", "GT", "UMINUS", "'='",
  "'-'", "'+'", "'*'", "'/'", "'{'", "'}'", "'('", "')'", "':'", "','",
  "'['", "']'", "$accept", "PROGRAM", "$@1", "$@2", "OBJCONTENT",
  "FUNCTION_DEFINITIONS", "FUNCTION_DEFINITION", "$@3", "$@4",
  "FUNCTION_DEFINITION2", "FORMAL_ARGS", "ARG", "RETURN_STMT", "STMTS",
  "STMT", "$@5", "VALDECLARATION", "VARDECLARATION", "EXP",
  "FUNCTION_CALLED", "$@6", "FUNCTION_CALLED_ARGS", "FUNCTION_CALLED_ARG",
  "IF_STMT", "$@7", "$@8", "$@9", "ELSE_STMT", "$@10", "WHILE_STMT",
  "$@11", "$@12", "FOR_STMT", "$@13", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
      61,    45,    43,    42,    47,   123,   125,    40,    41,    58,
      44,    91,    93
};
#endif

#define YYPACT_NINF (-115)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-61)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -13,    11,    19,  -115,  -115,    -1,  -115,    47,   -28,  -115,
      18,    52,     0,    20,    26,    33,    68,     4,    35,     4,
       4,  -115,    37,  -115,    66,    47,  -115,  -115,   229,  -115,
    -115,  -115,  -115,     4,     4,    38,   -24,   -19,     4,    73,
       4,     4,  -115,    -9,   229,     4,    74,  -115,    47,  -115,
      76,  -115,    66,  -115,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   229,    91,     4,    77,
      72,    79,    75,   131,    65,   147,   163,   179,    49,  -115,
    -115,    74,   244,    34,    34,    34,    34,    34,    34,    -3,
      -3,  -115,  -115,    57,   229,    50,    51,  -115,   -14,  -115,
      59,  -115,     4,  -115,  -115,  -115,  -115,    53,     4,  -115,
       4,    89,     4,    99,  -115,   198,  -115,    92,    69,   229,
    -115,  -115,   111,  -115,    47,     4,    47,    71,    82,    81,
    -115,  -115,  -115,   213,  -115,   121,    88,    92,    47,   118,
    -115,  -115,   124,  -115,    94,  -115,  -115,    47,  -115,  -115,
      47,  -115,  -115
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     1,     0,     3,    21,    42,    49,
       0,     0,     0,     0,     0,     0,     0,    18,     0,     0,
       0,    30,     0,    26,     0,    19,    24,    25,    23,    50,
      32,    33,    34,     0,     0,     0,    40,     0,     0,     0,
       0,     0,    29,    42,    17,     0,    51,    48,    21,     4,
       0,     5,     7,    20,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,     0,    65,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
       6,    53,    52,    54,    55,    56,    57,    58,    59,    45,
      44,    46,    47,     0,    64,     0,    63,    38,    37,    36,
       0,    66,     0,    27,    28,    73,    31,     0,     0,    61,
      65,     0,     0,     0,    67,     0,    74,    16,     0,    43,
      62,    39,     0,    35,     0,     0,     0,     0,     0,    14,
       9,    41,    68,     0,    75,     0,    12,    16,    21,    72,
      76,    15,     0,    13,     0,    70,    69,     0,    11,    10,
       0,    77,    71
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -115,  -115,  -115,  -115,  -115,    95,  -115,  -115,  -115,  -115,
       3,  -115,  -115,   -25,  -114,  -115,  -115,  -115,   -16,  -115,
    -115,    31,  -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,
    -115,  -115,  -115,  -115
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     5,     7,    22,    51,    52,   107,   138,   118,
     128,   129,    23,    24,    25,    48,    26,    27,    28,    29,
      35,    95,    96,    30,   114,   124,   139,   146,   150,    31,
     116,   126,    32,   147
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      53,    44,    33,    46,    47,     1,    69,    43,     9,   -60,
     132,    71,   134,    34,     3,    70,   111,    66,    67,     4,
      72,    36,    73,    78,    75,    76,    19,   112,   -60,    77,
      64,    65,    34,   151,     6,    20,   152,    38,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       8,     9,    94,    10,    11,    37,    12,    39,    13,    14,
      15,    16,    17,    40,    18,    62,    63,    64,    65,    19,
      41,    42,    45,    49,    50,    68,    74,    98,    20,    79,
     100,    97,    21,    99,   102,   106,   115,   108,   109,   113,
     117,   110,   119,   121,    94,   127,   122,    56,    57,    58,
      59,    60,    61,   123,   130,    62,    63,    64,    65,   133,
     135,    54,    55,   144,    56,    57,    58,    59,    60,    61,
     136,   137,    62,    63,    64,    65,   141,   142,   145,   148,
     149,    54,    55,    93,    56,    57,    58,    59,    60,    61,
     143,   120,    62,    63,    64,    65,     0,    80,     0,     0,
       0,    54,    55,   131,    56,    57,    58,    59,    60,    61,
       0,     0,    62,    63,    64,    65,     0,    54,    55,   101,
      56,    57,    58,    59,    60,    61,     0,     0,    62,    63,
      64,    65,     0,    54,    55,   103,    56,    57,    58,    59,
      60,    61,     0,     0,    62,    63,    64,    65,     0,    54,
      55,   104,    56,    57,    58,    59,    60,    61,     0,     0,
      62,    63,    64,    65,   125,     0,     0,   105,    54,    55,
       0,    56,    57,    58,    59,    60,    61,     0,     0,    62,
      63,    64,    65,    54,    55,     0,    56,    57,    58,    59,
      60,    61,     0,     0,    62,    63,    64,    65,     0,    54,
      55,   140,    56,    57,    58,    59,    60,    61,     0,     0,
      62,    63,    64,    65,    54,     0,     0,    56,    57,    58,
      59,    60,    61,     0,     0,    62,    63,    64,    65
};

static const yytype_int16 yycheck[] =
{
      25,    17,    30,    19,    20,    18,    30,     3,     4,    37,
     124,    30,   126,    41,     3,    39,    30,    33,    34,     0,
      39,     3,    38,    48,    40,    41,    22,    41,    37,    45,
      33,    34,    41,   147,    35,    31,   150,    37,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
       3,     4,    68,     6,     7,     3,     9,    37,    11,    12,
      13,    14,    15,    37,    17,    31,    32,    33,    34,    22,
      37,     3,    37,    36,     8,    37,     3,     5,    31,     3,
       5,     4,    35,     4,    19,    36,   102,    30,    38,    30,
      37,    40,   108,     4,   110,     3,   112,    23,    24,    25,
      26,    27,    28,     4,    35,    31,    32,    33,    34,   125,
      39,    20,    21,   138,    23,    24,    25,    26,    27,    28,
      38,    40,    31,    32,    33,    34,     5,    39,    10,     5,
      36,    20,    21,    42,    23,    24,    25,    26,    27,    28,
     137,   110,    31,    32,    33,    34,    -1,    52,    -1,    -1,
      -1,    20,    21,    42,    23,    24,    25,    26,    27,    28,
      -1,    -1,    31,    32,    33,    34,    -1,    20,    21,    38,
      23,    24,    25,    26,    27,    28,    -1,    -1,    31,    32,
      33,    34,    -1,    20,    21,    38,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    32,    33,    34,    -1,    20,
      21,    38,    23,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    16,    -1,    -1,    38,    20,    21,
      -1,    23,    24,    25,    26,    27,    28,    -1,    -1,    31,
      32,    33,    34,    20,    21,    -1,    23,    24,    25,    26,
      27,    28,    -1,    -1,    31,    32,    33,    34,    -1,    20,
      21,    38,    23,    24,    25,    26,    27,    28,    -1,    -1,
      31,    32,    33,    34,    20,    -1,    -1,    23,    24,    25,
      26,    27,    28,    -1,    -1,    31,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    18,    44,     3,     0,    45,    35,    46,     3,     4,
       6,     7,     9,    11,    12,    13,    14,    15,    17,    22,
      31,    35,    47,    55,    56,    57,    59,    60,    61,    62,
      66,    72,    75,    30,    41,    63,     3,     3,    37,    37,
      37,    37,     3,     3,    61,    37,    61,    61,    58,    36,
       8,    48,    49,    56,    20,    21,    23,    24,    25,    26,
      27,    28,    31,    32,    33,    34,    61,    61,    37,    30,
      39,    30,    39,    61,     3,    61,    61,    61,    56,     3,
      48,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    42,    61,    64,    65,     4,     5,     4,
       5,    38,    19,    38,    38,    38,    36,    50,    30,    38,
      40,    30,    41,    30,    67,    61,    73,    37,    52,    61,
      64,     4,    61,     4,    68,    16,    74,     3,    53,    54,
      35,    42,    57,    61,    57,    39,    38,    40,    51,    69,
      38,     5,    39,    53,    56,    10,    70,    76,     5,    36,
      71,    57,    57
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    45,    46,    44,    47,    48,    48,    50,    51,
      49,    52,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    57,    57,    57,    57,    59,    59,    60,    60,    60,
      60,    60,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      63,    62,    64,    64,    65,    65,    67,    68,    69,    66,
      71,    70,    70,    73,    74,    72,    76,    75
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     0,     7,     2,     2,     1,     0,     0,
       8,     5,     3,     3,     1,     3,     0,     2,     1,     1,
       2,     0,     3,     1,     1,     1,     1,     4,     4,     2,
       0,     4,     1,     1,     1,     6,     4,     4,     4,     6,
       2,     7,     1,     6,     3,     3,     3,     3,     2,     1,
       1,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       0,     5,     3,     1,     1,     0,     0,     0,     0,     9,
       0,     3,     0,     0,     0,     7,     0,    10
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize;

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yynerrs = 0;
  yystate = 0;
  yyerrstatus = 0;

  yystacksize = YYINITDEPTH;
  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;


  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 91 "project2.y"
            {
                DebugLog("Object definition start!");
                ID objectId = ID();
                objectId.IDName = *(yyvsp[0].idName);
                objectId.idType = IDTYPE::OBJECTID;
                symbolTable.Insert(objectId);
            }
#line 1410 "y.tab.cpp"
    break;

  case 3:
#line 99 "project2.y"
            {
                // create new scope
                symbolTable.CreateSymbol();
            }
#line 1419 "y.tab.cpp"
    break;

  case 4:
#line 104 "project2.y"
            {
                // check whether their are main function inside
                try{
                    symbolTable.LookUp("main");
                }
                catch(string s){
                    yyerror("The object content must have the main function!");
                }

                // drop the symbol table
                symbolTable.DropSymbol();
                DebugLog("Object definition end!");
            }
#line 1437 "y.tab.cpp"
    break;

  case 8:
#line 129 "project2.y"
                        {
                            // insert function name
                            ID functionID = ID();
                            functionID.SetToFunction(*(yyvsp[0].idName));

                            ID& functionRef = symbolTable.Insert(functionID);
                            // set the functionScopedPtr to current function
                            functionScopedPtr = &functionRef;
                        }
#line 1451 "y.tab.cpp"
    break;

  case 9:
#line 140 "project2.y"
                        {
                            // create the scope
                            symbolTable.CreateSymbol();

                            // put all parameter into the current scope
                            for(int i=0; i< functionScopedPtr->parameters.size(); i++){
                                symbolTable.Insert(*(functionScopedPtr->parameters[i]));
                            }
                        }
#line 1465 "y.tab.cpp"
    break;

  case 10:
#line 151 "project2.y"
                        {
                            // dump to check that we set the correct function
                            // functionScopedPtr->Dump();
                            // drop the current scope
                            symbolTable.DropSymbol();
                            // set the functionScopedPtr to null
                            functionScopedPtr = NULL;
                        }
#line 1478 "y.tab.cpp"
    break;

  case 11:
#line 163 "project2.y"
                        {
                            // set the return type for the function
                            functionScopedPtr->SetReturnType(*(yyvsp[0].valueType));
                        }
#line 1487 "y.tab.cpp"
    break;

  case 12:
#line 168 "project2.y"
                        {
                            // set the return type for the function
                            functionScopedPtr->SetReturnType(VALUETYPE::VOID);
                        }
#line 1496 "y.tab.cpp"
    break;

  case 15:
#line 180 "project2.y"
            {
                // recreate a new ID as the function parameter
                ID parameterID = ID();
                parameterID.SetToVar(*(yyvsp[-2].idName));
                // set the value type too
                parameterID.SetValueType(*(yyvsp[0].valueType));

                // set the parameter to the function id
                functionScopedPtr->AddParameter(parameterID);
            }
#line 1511 "y.tab.cpp"
    break;

  case 17:
#line 195 "project2.y"
            {
                // check whether we are in the function scope
                if(functionScopedPtr == NULL) 
                    yyerror("Return can only called inside the function scope!");

                // check whether the return exp's type is same as the current function type
                if((yyvsp[0].value)->valueType != functionScopedPtr->retVal.valueType) 
                    yyerror("The function return type definition is different as the function return type declaration!"); 
            }
#line 1525 "y.tab.cpp"
    break;

  case 18:
#line 205 "project2.y"
            {
                // check whether we are in the function scope
                if(functionScopedPtr == NULL) 
                    yyerror("Return can only called inside the function scope!");

                // check whether the return exp's type is same as the current function type
                if(VALUETYPE::VOID != functionScopedPtr->retVal.valueType) 
                    yyerror("The function return type is void!"); 
            }
#line 1539 "y.tab.cpp"
    break;

  case 22:
#line 224 "project2.y"
                {
                    // check whether the exp has the same value type with the id name
                    VALUE rvalue = symbolTable.LookUp(*(yyvsp[-2].idName)).value;
                    if(rvalue.valueType == (yyvsp[0].value)->valueType){
                        DebugLog("Assignment operation done!");
                    }
                    else{
                        yyerror("Different type of value can't do the assignment operation!");
                    }
                }
#line 1554 "y.tab.cpp"
    break;

  case 27:
#line 239 "project2.y"
                {
                    DebugLog("Print function Called!");
                }
#line 1562 "y.tab.cpp"
    break;

  case 28:
#line 243 "project2.y"
                {
                    DebugLog("Println function Called!");
                }
#line 1570 "y.tab.cpp"
    break;

  case 29:
#line 247 "project2.y"
                {
                    DebugLog("Read function Called!");
                }
#line 1578 "y.tab.cpp"
    break;

  case 30:
#line 253 "project2.y"
                {
                    symbolTable.CreateSymbol();
                }
#line 1586 "y.tab.cpp"
    break;

  case 31:
#line 257 "project2.y"
                {
                    symbolTable.DropSymbol();
                }
#line 1594 "y.tab.cpp"
    break;

  case 35:
#line 267 "project2.y"
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToConstVar(*(yyvsp[-4].idName));
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);

                                // check VALUE_TOKEN's value type same as VALUE_TYPE
                                idRef.SetValueType(*(yyvsp[-2].valueType));
                                idRef.InitValue(*(yyvsp[0].value));
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
#line 1616 "y.tab.cpp"
    break;

  case 36:
#line 285 "project2.y"
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToConstVar(*(yyvsp[-2].idName));
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);
                                idRef.InitValue(*(yyvsp[0].value));
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
#line 1635 "y.tab.cpp"
    break;

  case 37:
#line 303 "project2.y"
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*(yyvsp[-2].idName));
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);

                                // set value type
                                idRef.SetValueType(*(yyvsp[0].valueType));
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                            
                        }
#line 1657 "y.tab.cpp"
    break;

  case 38:
#line 321 "project2.y"
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*(yyvsp[-2].idName));
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);

                                // set type
                                idRef.InitValue(*(yyvsp[0].value));
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
#line 1678 "y.tab.cpp"
    break;

  case 39:
#line 339 "project2.y"
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*(yyvsp[-4].idName));
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);

                                // check VALUE_TOKEN's value type same as VALUE_TYPE
                                idRef.SetValueType(*(yyvsp[-2].valueType));
                                idRef.InitValue(*(yyvsp[0].value));
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
#line 1700 "y.tab.cpp"
    break;

  case 40:
#line 357 "project2.y"
                        {
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*(yyvsp[0].idName));

                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID& idRef = symbolTable.Insert(newId);
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
#line 1719 "y.tab.cpp"
    break;

  case 41:
#line 372 "project2.y"
                        {
                            
                            // error checking first
                            try{
                                ID newId = ID();
                                newId.SetToVar(*(yyvsp[-5].idName));
                                
                                // check ID is already used in this scope or not
                                // insert id with name to the symbol table
                                ID* idRef = &symbolTable.Insert(newId);

                                // the value_token must be type int
                                if((yyvsp[-1].value)->valueType != VALUETYPE::INT) yyerror("array declaration's number value must be integer!");
                                // set the array range for id name
                                // and resize
                                idRef->value = VALUE(*(yyvsp[-3].valueType), (yyvsp[-1].value)->ival);
                            }
                            catch(string s){
                                yyerror(s.c_str());
                            }
                        }
#line 1745 "y.tab.cpp"
    break;

  case 42:
#line 396 "project2.y"
                           {
            // find the id in the symbol table
                VALUE& idVal = symbolTable.LookUp(*(yyvsp[0].idName)).value;
                (yyval.value) = new VALUE(idVal);
            }
#line 1755 "y.tab.cpp"
    break;

  case 43:
#line 403 "project2.y"
        {
            // id name must be valid
            VALUE& arrID = symbolTable.LookUp(*(yyvsp[-5].idName)).value;

            // 1st exp should only be int type
            if((yyvsp[-3].value)->valueType != VALUETYPE::INT) yyerror("Array index must be integer type!");

            // set value to the array content
            arrID[(yyvsp[-3].value)->ival] = *(yyvsp[0].value);

        }
#line 1771 "y.tab.cpp"
    break;

  case 44:
#line 414 "project2.y"
                        {(yyval.value) = new VALUE(*(yyvsp[-2].value) + *(yyvsp[0].value));}
#line 1777 "y.tab.cpp"
    break;

  case 45:
#line 415 "project2.y"
                        {(yyval.value) = new VALUE(*(yyvsp[-2].value) - *(yyvsp[0].value));}
#line 1783 "y.tab.cpp"
    break;

  case 46:
#line 416 "project2.y"
                        {(yyval.value) = new VALUE(*(yyvsp[-2].value) * *(yyvsp[0].value));}
#line 1789 "y.tab.cpp"
    break;

  case 47:
#line 417 "project2.y"
                        {(yyval.value) = new VALUE(*(yyvsp[-2].value) / *(yyvsp[0].value));}
#line 1795 "y.tab.cpp"
    break;

  case 48:
#line 419 "project2.y"
                                 {
                (yyval.value) = new VALUE(-(*(yyvsp[0].value)));
            }
#line 1803 "y.tab.cpp"
    break;

  case 51:
#line 425 "project2.y"
                        { (yyval.value) = new VALUE(!(*(yyvsp[0].value)));}
#line 1809 "y.tab.cpp"
    break;

  case 52:
#line 426 "project2.y"
                       { (yyval.value) = new VALUE(*(yyvsp[-2].value) || *(yyvsp[0].value));}
#line 1815 "y.tab.cpp"
    break;

  case 53:
#line 427 "project2.y"
                        { (yyval.value) = new VALUE(*(yyvsp[-2].value) && *(yyvsp[0].value));}
#line 1821 "y.tab.cpp"
    break;

  case 54:
#line 428 "project2.y"
                        { (yyval.value) = new VALUE(*(yyvsp[-2].value) < *(yyvsp[0].value));}
#line 1827 "y.tab.cpp"
    break;

  case 55:
#line 429 "project2.y"
                        { (yyval.value) = new VALUE(*(yyvsp[-2].value) <= *(yyvsp[0].value));}
#line 1833 "y.tab.cpp"
    break;

  case 56:
#line 430 "project2.y"
                        { (yyval.value) = new VALUE(*(yyvsp[-2].value) == *(yyvsp[0].value));}
#line 1839 "y.tab.cpp"
    break;

  case 57:
#line 431 "project2.y"
                        { (yyval.value) = new VALUE(*(yyvsp[-2].value) != *(yyvsp[0].value));}
#line 1845 "y.tab.cpp"
    break;

  case 58:
#line 432 "project2.y"
                        { (yyval.value) = new VALUE(*(yyvsp[-2].value) >= *(yyvsp[0].value));}
#line 1851 "y.tab.cpp"
    break;

  case 59:
#line 433 "project2.y"
                        { (yyval.value) = new VALUE(*(yyvsp[-2].value) > *(yyvsp[0].value));}
#line 1857 "y.tab.cpp"
    break;

  case 60:
#line 438 "project2.y"
                        {
                            // start to find the id name in the current scope
                            ID& functionID = symbolTable.LookUp(*(yyvsp[0].idName));
                            // check the id type to be function
                            if(functionID.idType == IDTYPE::FUNCTION)
                                DebugLog("Function Called Detected. Function name is " + functionID.IDName + "......OK");
                            else    yyerror("ID Called wasn't function!");

                            // initialize function ptr
                            functionCalledPtr = &functionID;

                            // initialize function parameter index
                            parameterIndex = 0;
                        }
#line 1876 "y.tab.cpp"
    break;

  case 61:
#line 453 "project2.y"
                        {   
                            // set the function return value to $$, to get change to exp
                            (yyval.value) = new VALUE(functionCalledPtr->retVal);
                            
                            // finish checking all function parameter, reset the parameter index and function pointer
                            parameterIndex = 0;
                            functionCalledPtr = NULL;
                        }
#line 1889 "y.tab.cpp"
    break;

  case 64:
#line 470 "project2.y"
                        {
                            // check the value token value type against the function paramter index value type
                            if((yyvsp[0].value)->valueType != functionCalledPtr->parameters[parameterIndex]->value.valueType){
                                yyerror(("Function called parameter " + to_string(parameterIndex) + ", doesn't have the correct value type!").c_str());
                            }
                            else{
                                DebugLog("Function called parameter " + to_string(parameterIndex) + ", Checked......OK");
                            }
                            // finish checking, add paramterIndex
                            parameterIndex++;
                        }
#line 1905 "y.tab.cpp"
    break;

  case 66:
#line 486 "project2.y"
                        {
                            // the exp must be boolean only
                            if((yyvsp[-1].value)->valueType != VALUETYPE::BOOLEAN) yyerror("If Statement only accept boolean expression!");
                            else    DebugLog("IF statement detected.......OK");
                        }
#line 1915 "y.tab.cpp"
    break;

  case 67:
#line 491 "project2.y"
                        { symbolTable.CreateSymbol(false);}
#line 1921 "y.tab.cpp"
    break;

  case 68:
#line 491 "project2.y"
                                                                 { symbolTable.DropSymbol(false);}
#line 1927 "y.tab.cpp"
    break;

  case 70:
#line 495 "project2.y"
                                 { symbolTable.CreateSymbol(false);}
#line 1933 "y.tab.cpp"
    break;

  case 71:
#line 495 "project2.y"
                                                                          { symbolTable.DropSymbol(false);}
#line 1939 "y.tab.cpp"
    break;

  case 73:
#line 502 "project2.y"
                        {
                            // the exp must be boolean only
                            if((yyvsp[-1].value)->valueType != VALUETYPE::BOOLEAN) yyerror("While Statement only accept boolean expression!");
                            else    DebugLog("While statement detected.......OK");

                        }
#line 1950 "y.tab.cpp"
    break;

  case 74:
#line 507 "project2.y"
                         { symbolTable.CreateSymbol(false);}
#line 1956 "y.tab.cpp"
    break;

  case 75:
#line 507 "project2.y"
                                                                  { symbolTable.DropSymbol(false);}
#line 1962 "y.tab.cpp"
    break;

  case 76:
#line 512 "project2.y"
                        {
                            // both exp must be only int expression
                            if((yyvsp[-3].value)->valueType != VALUETYPE::INT){
                                yyerror("Assignment of for loop only can be int!");
                            }
                            if((yyvsp[-1].value)->valueType != VALUETYPE::INT){
                                yyerror("Terminate value of for loop only can be int!");
                            }
                            // create a new symbol first
                            symbolTable.CreateSymbol(false);

                            ID forID;
                            forID.SetToVar(*(yyvsp[-5].idName));
                            forID.value = *(yyvsp[-3].value);
                            symbolTable.Insert(forID);

                        }
#line 1984 "y.tab.cpp"
    break;

  case 77:
#line 528 "project2.y"
                               { symbolTable.DropSymbol(false);}
#line 1990 "y.tab.cpp"
    break;


#line 1994 "y.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  // Pop stack until we find a state that shifts the error token.
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 531 "project2.y"

#include "lex.yy.cpp"

VALUE oper(char operC, VALUE v1, VALUE v2){
    // type should be the same
    if(v1.valueType != v2.valueType){
        yyerror("Different type the value cant do mathematics operation!");
    }

    // only float and int can do the operation
    if(v1.valueType != VALUETYPE::FLOAT && v1.valueType != VALUETYPE::INT){
        yyerror("Only float and int can do the mathematics operation!");
    }

    // add operation
    // add operation for float
    if(operC == '+' && v1.valueType == VALUETYPE::FLOAT){
        DebugLog("+ operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval + v2.fval;
        return answer;
    }
    // add operation for int
    if(operC == '+' && v1.valueType == VALUETYPE::INT){
        DebugLog("+ operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::INT;
        // set answer value
        answer.ival = v1.ival + v2.ival;
        return answer;
    }

    // minus operation
    // minus operation for float
    if(operC == '-' && v1.valueType == VALUETYPE::FLOAT){
        DebugLog("- operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval - v2.fval;
        return answer;
    }
    // minus operation for int
    if(operC == '-' && v1.valueType == VALUETYPE::INT){
        DebugLog("- operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::INT;
        // set answer value
        answer.ival = v1.ival - v2.ival;
        return answer;
    }

    // multiple operation
    // multiple operation for float
    if(operC == '*' && v1.valueType == VALUETYPE::FLOAT){
        DebugLog("* operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval * v2.fval;
        return answer;
    }
    // multiple operation for int
    if(operC == '*' && v1.valueType == VALUETYPE::INT){
        DebugLog("* operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::INT;
        // set answer value
        answer.ival = v1.ival / v2.ival;
        return answer;
    }

    // divide operation
    // divide operation for float
    if(operC == '/' && v1.valueType == VALUETYPE::FLOAT){
        DebugLog("/ operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::FLOAT;
        // set answer value
        answer.fval = v1.fval / v2.fval;
        return answer;
    }
    // divide operation for int
    if(operC == '/' && v1.valueType == VALUETYPE::INT){
        DebugLog("/ operator found! Checking Result......OK");
        VALUE answer;
        // set answer value type
        answer.valueType = VALUETYPE::INT;
        // set answer value
        answer.ival = v1.ival / v2.ival;
        return answer;
    }

    // shoudn't run till here
    yyerror("Invalid operation character passed!");
    return VALUE();
}

int yyerror(const char* s){
    // fprintf(stderr, "Error, Line%d: %s\n", yylineno, s);
    DebugLog("Error Message: " + string(s));
    exit(1);
}

// the main function to execute
int main(int argc, char* argv[]) {
    // set input and output file
    yyin = fopen(argv[1], "r");
    yyout = fopen(argv[2], "w");
    // init symbol table
    symbolTable.CreateSymbol();

    if(yyin != NULL){
        // perform parsing
        // error parsing
        try{
            if(yyparse() == 1)
            {
                yyerror("Parsing error! ");
            }
        }
        catch(string s){
            yyerror(s.c_str());
        } 
        

        fclose(yyin);
        fclose(yyout);
    }
    else if(yyin == NULL){
        printf("Input file not found!\n");
    }
    return 0;
}
