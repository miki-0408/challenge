/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "mini.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"

int yylex();
void yyerror(char* msg);
static SYM *switch_end_stack[32];
static int switch_stack_top = 0;

#line 83 "mini.y.c"

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

#include "mini.y.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_EQ = 4,                         /* EQ  */
  YYSYMBOL_NE = 5,                         /* NE  */
  YYSYMBOL_LT = 6,                         /* LT  */
  YYSYMBOL_LE = 7,                         /* LE  */
  YYSYMBOL_GT = 8,                         /* GT  */
  YYSYMBOL_GE = 9,                         /* GE  */
  YYSYMBOL_UMINUS = 10,                    /* UMINUS  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_INPUT = 14,                     /* INPUT  */
  YYSYMBOL_OUTPUT = 15,                    /* OUTPUT  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_INTEGER = 17,                   /* INTEGER  */
  YYSYMBOL_IDENTIFIER = 18,                /* IDENTIFIER  */
  YYSYMBOL_TEXT = 19,                      /* TEXT  */
  YYSYMBOL_SWITCH = 20,                    /* SWITCH  */
  YYSYMBOL_CASE = 21,                      /* CASE  */
  YYSYMBOL_DEFAULT = 22,                   /* DEFAULT  */
  YYSYMBOL_BREAK = 23,                     /* BREAK  */
  YYSYMBOL_FOR = 24,                       /* FOR  */
  YYSYMBOL_DO = 25,                        /* DO  */
  YYSYMBOL_CONTINUE = 26,                  /* CONTINUE  */
  YYSYMBOL_AND = 27,                       /* AND  */
  YYSYMBOL_OR = 28,                        /* OR  */
  YYSYMBOL_CHAR = 29,                      /* CHAR  */
  YYSYMBOL_CHARACTER = 30,                 /* CHARACTER  */
  YYSYMBOL_STRUCT = 31,                    /* STRUCT  */
  YYSYMBOL_TYPEDEF = 32,                   /* TYPEDEF  */
  YYSYMBOL_ARROW = 33,                     /* ARROW  */
  YYSYMBOL_TYPEID = 34,                    /* TYPEID  */
  YYSYMBOL_35_ = 35,                       /* '+'  */
  YYSYMBOL_36_ = 36,                       /* '-'  */
  YYSYMBOL_37_ = 37,                       /* '*'  */
  YYSYMBOL_38_ = 38,                       /* '/'  */
  YYSYMBOL_LOWER_THAN_POSTFIX = 39,        /* LOWER_THAN_POSTFIX  */
  YYSYMBOL_40_ = 40,                       /* '.'  */
  YYSYMBOL_41_ = 41,                       /* '['  */
  YYSYMBOL_42_ = 42,                       /* ']'  */
  YYSYMBOL_LOWER_THAN_ELSE = 43,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_44_ = 44,                       /* '='  */
  YYSYMBOL_45_ = 45,                       /* '{'  */
  YYSYMBOL_46_ = 46,                       /* '}'  */
  YYSYMBOL_47_ = 47,                       /* ';'  */
  YYSYMBOL_48_ = 48,                       /* ','  */
  YYSYMBOL_49_ = 49,                       /* '('  */
  YYSYMBOL_50_ = 50,                       /* ')'  */
  YYSYMBOL_51_ = 51,                       /* ':'  */
  YYSYMBOL_52_ = 52,                       /* '&'  */
  YYSYMBOL_YYACCEPT = 53,                  /* $accept  */
  YYSYMBOL_program = 54,                   /* program  */
  YYSYMBOL_function_declaration_list = 55, /* function_declaration_list  */
  YYSYMBOL_function_declaration = 56,      /* function_declaration  */
  YYSYMBOL_type_spec = 57,                 /* type_spec  */
  YYSYMBOL_field_decl_list = 58,           /* field_decl_list  */
  YYSYMBOL_field_decl = 59,                /* field_decl  */
  YYSYMBOL_field_var_list = 60,            /* field_var_list  */
  YYSYMBOL_field_var_unit = 61,            /* field_var_unit  */
  YYSYMBOL_declaration = 62,               /* declaration  */
  YYSYMBOL_variable_list = 63,             /* variable_list  */
  YYSYMBOL_var_unit = 64,                  /* var_unit  */
  YYSYMBOL_dims = 65,                      /* dims  */
  YYSYMBOL_function = 66,                  /* function  */
  YYSYMBOL_function_head = 67,             /* function_head  */
  YYSYMBOL_parameter_list = 68,            /* parameter_list  */
  YYSYMBOL_param_seq = 69,                 /* param_seq  */
  YYSYMBOL_statement = 70,                 /* statement  */
  YYSYMBOL_switch_statement = 71,          /* switch_statement  */
  YYSYMBOL_setup = 72,                     /* setup  */
  YYSYMBOL_case_list = 73,                 /* case_list  */
  YYSYMBOL_case_item = 74,                 /* case_item  */
  YYSYMBOL_block = 75,                     /* block  */
  YYSYMBOL_declaration_list = 76,          /* declaration_list  */
  YYSYMBOL_statement_list = 77,            /* statement_list  */
  YYSYMBOL_assignment_statement = 78,      /* assignment_statement  */
  YYSYMBOL_expression = 79,                /* expression  */
  YYSYMBOL_laddr = 80,                     /* laddr  */
  YYSYMBOL_argument_list = 81,             /* argument_list  */
  YYSYMBOL_expression_list = 82,           /* expression_list  */
  YYSYMBOL_input_statement = 83,           /* input_statement  */
  YYSYMBOL_output_statement = 84,          /* output_statement  */
  YYSYMBOL_return_statement = 85,          /* return_statement  */
  YYSYMBOL_if_statement = 86,              /* if_statement  */
  YYSYMBOL_while_statement = 87,           /* while_statement  */
  YYSYMBOL_do_while_statement = 88,        /* do_while_statement  */
  YYSYMBOL_for_statement = 89,             /* for_statement  */
  YYSYMBOL_for_init = 90,                  /* for_init  */
  YYSYMBOL_for_cond = 91,                  /* for_cond  */
  YYSYMBOL_for_iter = 92,                  /* for_iter  */
  YYSYMBOL_call_statement = 93,            /* call_statement  */
  YYSYMBOL_call_expression = 94            /* call_expression  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   777

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  250

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


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
       2,     2,     2,     2,     2,     2,     2,     2,    52,     2,
      49,    50,    37,    35,    48,    36,    40,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    47,
       2,    44,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,    46,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      39,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    66,    66,    73,    74,    80,    81,    86,    87,    88,
      90,    92,    94,   106,   107,   111,   115,   116,   120,   121,
     122,   127,   128,   129,   130,   132,   135,   136,   140,   141,
     142,   151,   152,   157,   165,   172,   181,   182,   186,   187,
     188,   189,   190,   191,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   212,   222,
     229,   230,   233,   241,   248,   256,   263,   271,   280,   287,
     290,   296,   297,   305,   309,   313,   317,   321,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   356,   361,   366,   371,   378,   378,   380,   381,   384,
     387,   388,   389,   392,   402,   403,   406,   409,   412,   415,
     415,   415,   416,   416,   417,   417,   417,   419,   421
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "EQ", "NE",
  "LT", "LE", "GT", "GE", "UMINUS", "IF", "ELSE", "WHILE", "INPUT",
  "OUTPUT", "RETURN", "INTEGER", "IDENTIFIER", "TEXT", "SWITCH", "CASE",
  "DEFAULT", "BREAK", "FOR", "DO", "CONTINUE", "AND", "OR", "CHAR",
  "CHARACTER", "STRUCT", "TYPEDEF", "ARROW", "TYPEID", "'+'", "'-'", "'*'",
  "'/'", "LOWER_THAN_POSTFIX", "'.'", "'['", "']'", "LOWER_THAN_ELSE",
  "'='", "'{'", "'}'", "';'", "','", "'('", "')'", "':'", "'&'", "$accept",
  "program", "function_declaration_list", "function_declaration",
  "type_spec", "field_decl_list", "field_decl", "field_var_list",
  "field_var_unit", "declaration", "variable_list", "var_unit", "dims",
  "function", "function_head", "parameter_list", "param_seq", "statement",
  "switch_statement", "setup", "case_list", "case_item", "block",
  "declaration_list", "statement_list", "assignment_statement",
  "expression", "laddr", "argument_list", "expression_list",
  "input_statement", "output_statement", "return_statement",
  "if_statement", "while_statement", "do_while_statement", "for_statement",
  "for_init", "for_cond", "for_iter", "call_statement", "call_expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-125)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-128)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      22,  -125,  -125,  -125,    -3,    21,  -125,    20,   727,  -125,
     -10,  -125,  -125,   -13,    21,     3,  -125,  -125,   -31,    28,
    -125,   142,  -125,    40,    21,    39,     2,  -125,    79,    53,
      80,  -125,  -125,  -125,    48,    21,    44,    -2,    94,   146,
    -125,  -125,  -125,    96,  -125,    68,    83,    -2,  -125,    56,
      77,    95,  -125,  -125,  -125,  -125,    39,    89,  -125,    -2,
     106,   161,   139,    21,  -125,   144,  -125,   153,  -125,  -125,
    -125,    63,  -125,  -125,   151,   145,   179,  -125,   149,   150,
     183,   127,    65,  -125,    91,   169,   163,   170,   139,   173,
    -125,    65,    65,    65,   204,    -9,  -125,  -125,  -125,  -125,
     431,   176,   683,   177,   178,   182,  -125,  -125,  -125,  -125,
     184,  -125,   188,  -125,    65,    65,  -125,  -125,  -125,  -125,
     185,    65,   698,    65,    65,    65,  -125,   445,   213,  -125,
      46,    78,   465,  -125,   120,  -125,  -125,  -125,    65,    65,
      65,    65,    65,    65,    65,    65,   215,    65,    65,    65,
      65,   217,    65,  -125,  -125,  -125,  -125,  -125,   481,   519,
      65,    46,   220,   221,    65,   698,   698,   200,   193,   535,
    -125,   211,  -125,   210,    65,  -125,   242,   244,    65,   497,
     497,   497,   497,   497,   497,   736,   101,   219,   118,   118,
      46,    46,   222,   589,   139,   139,   214,  -125,  -125,   628,
      49,    65,   224,    65,    65,   698,  -125,  -125,   644,    65,
      65,   226,   253,  -125,  -125,  -125,   698,  -125,   698,   227,
     573,  -125,   698,   698,    65,   139,  -125,   445,   228,   698,
    -125,    70,  -125,   223,  -125,  -125,     0,   230,  -125,  -125,
     139,   239,   247,   191,  -125,   231,   271,   311,   351,   391
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    34,     7,     8,     0,     0,    12,     0,     0,     3,
       0,     6,     5,    11,     0,     0,     1,     4,    28,     0,
      25,     0,    26,     0,     0,     0,     0,    13,     0,     0,
       0,    30,    29,    21,     0,    36,     0,    18,     0,     0,
      16,    10,    14,     0,    22,     0,     0,    28,    27,     0,
       0,    37,     9,    20,    19,    15,     0,     0,    23,    32,
      38,     0,     0,     0,    17,     0,    31,     0,    39,    69,
      33,     0,    24,    40,     0,    41,     0,    57,     0,     0,
       0,     0,     0,    97,    99,     0,     0,     0,     0,     0,
      98,     0,     0,     0,     0,     0,    70,    71,    53,    54,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
       0,   100,     0,    42,     0,     0,   109,   110,   111,   112,
      99,     0,   113,     0,   105,     0,    55,   121,     0,    56,
      82,    83,     0,   101,    84,    68,    72,    44,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,    46,    48,    47,    43,     0,     0,
     105,    83,     0,     0,     0,    73,   107,     0,   106,     0,
     119,     0,   120,     0,     0,    96,     0,     0,     0,    88,
      89,    90,    91,    92,    93,    94,    95,    87,    78,    79,
      80,    81,    86,     0,     0,     0,     0,    87,    86,     0,
     128,     0,     0,   123,     0,    74,   104,   103,     0,     0,
       0,    85,   114,   116,   128,    85,   108,    59,   122,     0,
       0,   102,    77,    76,     0,     0,    60,   126,     0,    75,
     115,     0,   124,     0,   125,   117,     0,     0,    58,    61,
       0,     0,     0,     0,   118,     0,     0,     0,     0,     0
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -125,  -125,  -125,   263,    14,   254,   -20,  -125,   243,   205,
    -125,   266,   -30,  -125,  -125,  -125,  -125,   -99,  -125,  -125,
    -125,  -125,   -62,  -125,   -73,  -124,   -80,  -125,   143,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -123,  -125
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     7,     8,     9,    25,    26,    27,    39,    40,    11,
      21,    22,    31,    12,    23,    50,    51,    97,    98,   226,
     231,   239,    99,    74,   100,   101,   102,   134,   167,   168,
     103,   104,   105,   106,   107,   108,   109,   171,   219,   233,
     110,   111
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   136,   122,   170,   172,     2,    42,    53,    18,    47,
      30,   130,   131,   132,    10,    13,    42,   241,   -35,    15,
      16,    28,    10,     1,     2,     2,   128,    19,    19,    66,
     242,     3,    24,     4,   158,   159,     6,    20,    20,    30,
      29,   161,    14,   165,   166,   169,    32,     2,    41,    49,
       3,     3,     4,     4,     5,     6,     6,    37,   179,   180,
     181,   182,   183,   184,   185,   186,    47,   188,   189,   190,
     191,    45,   193,     3,    60,     4,    38,    71,     6,   162,
     166,    75,    83,   120,   199,    19,   163,   164,    95,    35,
      52,   236,   237,    61,   205,    90,  -127,    46,   208,  -127,
      76,    91,   121,   232,   234,   138,   139,   140,   141,   142,
     143,   162,    54,    57,    93,    58,   238,    94,   163,   164,
      43,   216,   174,   218,   220,    59,    44,    62,   144,   222,
     223,    65,   212,   213,   162,   123,   147,   148,   149,   150,
     124,   163,   164,    63,   229,   117,   118,    67,   136,   136,
     136,   162,    77,   176,     2,   149,   150,   119,   163,   164,
     177,   178,    78,   230,    79,    80,    81,    82,    83,    84,
     247,    85,   248,   249,    86,    87,    88,    89,   244,    68,
       3,    90,     4,     5,    69,     6,   112,    91,    92,    33,
      34,    72,    77,    55,    56,    73,    69,   113,   114,   115,
      93,   116,    78,    94,    79,    80,    81,    82,    83,    84,
     126,    85,   -67,   -67,    86,    87,    88,    89,   125,   127,
     129,    90,   133,   137,   153,   154,   173,    91,    92,   155,
     157,   156,    77,   187,   160,   192,    69,   -67,   197,   198,
      93,   201,    78,    94,    79,    80,    81,    82,    83,    84,
     200,    85,   -63,   -63,    86,    87,    88,    89,   203,   204,
     206,    90,   207,   209,   214,   225,   210,    91,    92,   217,
     224,    17,    77,   240,   227,   235,    69,   -63,    36,    96,
      93,   243,    78,    94,    79,    80,    81,    82,    83,    84,
     245,    85,   -65,   -65,    86,    87,    88,    89,   246,    64,
      48,    90,     0,   196,     0,     0,     0,    91,    92,     0,
       0,     0,    77,     0,     0,     0,    69,   -65,     0,     0,
      93,     0,    78,    94,    79,    80,    81,    82,    83,    84,
       0,    85,   -66,   -66,    86,    87,    88,    89,     0,     0,
       0,    90,     0,     0,     0,     0,     0,    91,    92,     0,
       0,     0,    77,     0,     0,     0,    69,   -66,     0,     0,
      93,     0,    78,    94,    79,    80,    81,    82,    83,    84,
       0,    85,   -62,   -62,    86,    87,    88,    89,     0,     0,
       0,    90,     0,     0,     0,     0,     0,    91,    92,     0,
       0,     0,    77,     0,     0,     0,    69,   -62,     0,     0,
      93,     0,    78,    94,    79,    80,    81,    82,    83,    84,
       0,    85,   -64,   -64,    86,    87,    88,    89,     0,     0,
       0,    90,     0,     0,     0,     0,     0,    91,    92,     0,
       0,     0,    77,     0,     0,     0,    69,   -64,     0,     0,
      93,     0,    78,    94,    79,    80,    81,    82,    83,    84,
       0,    85,     0,     0,    86,    87,    88,    89,     0,     0,
       0,    90,    83,    84,     0,     0,     0,    91,    92,   138,
     139,   140,   141,   142,   143,    90,    69,   135,     0,     0,
      93,    91,    92,    94,     0,   138,   139,   140,   141,   142,
     143,     0,   144,   145,    93,     0,     0,    94,   162,     0,
     147,   148,   149,   150,     0,   163,   164,     0,   144,   145,
       0,     0,     0,     0,   162,   175,   147,   148,   149,   150,
       0,   163,   164,   138,   139,   140,   141,   142,   143,     0,
     162,   194,   147,   148,   149,   150,     0,   163,   164,   138,
     139,   140,   141,   142,   143,     0,   144,   145,     0,     0,
       0,     0,   162,     0,   147,   148,   149,   150,     0,   163,
     164,     0,   144,   145,     0,     0,     0,     0,   162,   195,
     147,   148,   149,   150,     0,   163,   164,   138,   139,   140,
     141,   142,   143,     0,     0,   202,     0,     0,     0,     0,
       0,     0,     0,   138,   139,   140,   141,   142,   143,     0,
     144,   145,     0,     0,     0,     0,   162,     0,   147,   148,
     149,   150,     0,   163,   164,     0,   144,   145,     0,     0,
       0,     0,   162,   228,   147,   148,   149,   150,     0,   163,
     164,   211,   138,   139,   140,   141,   142,   143,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,     0,   144,   145,     0,     0,     0,
       0,   162,     0,   147,   148,   149,   150,     0,   163,   164,
     215,   144,   145,     0,     0,     0,     0,   162,     0,   147,
     148,   149,   150,     0,   163,   164,   221,   138,   139,   140,
     141,   142,   143,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   138,   139,   140,   141,   142,   143,     0,     0,
     144,   145,     0,     0,     0,     0,   146,     0,   147,   148,
     149,   150,     0,   151,   152,   144,   145,    -2,     1,     0,
       2,   162,     0,   147,   148,   149,   150,     0,   163,   164,
     138,   139,   140,   141,   142,   143,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     4,     5,
       0,     6,     0,     0,     0,     0,     0,     0,     0,   162,
       0,   147,   148,   149,   150,     0,   163,   164
};

static const yytype_int16 yycheck[] =
{
      62,   100,    82,   127,   127,     3,    26,    37,    18,    18,
      41,    91,    92,    93,     0,    18,    36,    17,    49,     5,
       0,    18,     8,     1,     3,     3,    88,    37,    37,    59,
      30,    29,    45,    31,   114,   115,    34,    47,    47,    41,
      37,   121,    45,   123,   124,   125,    18,     3,    46,    35,
      29,    29,    31,    31,    32,    34,    34,    18,   138,   139,
     140,   141,   142,   143,   144,   145,    18,   147,   148,   149,
     150,    18,   152,    29,    18,    31,    37,    63,    34,    33,
     160,    18,    17,    18,   164,    37,    40,    41,    74,    49,
      46,    21,    22,    37,   174,    30,    47,    17,   178,    50,
      37,    36,    37,   227,   227,     4,     5,     6,     7,     8,
       9,    33,    18,    17,    49,    47,    46,    52,    40,    41,
      41,   201,    44,   203,   204,    42,    47,    50,    27,   209,
     210,    42,   194,   195,    33,    44,    35,    36,    37,    38,
      49,    40,    41,    48,   224,    18,    19,    41,   247,   248,
     249,    33,     1,    33,     3,    37,    38,    30,    40,    41,
      40,    41,    11,   225,    13,    14,    15,    16,    17,    18,
     243,    20,   245,   246,    23,    24,    25,    26,   240,    18,
      29,    30,    31,    32,    45,    34,    41,    36,    37,    47,
      48,    47,     1,    47,    48,    42,    45,    18,    49,    49,
      49,    18,    11,    52,    13,    14,    15,    16,    17,    18,
      47,    20,    21,    22,    23,    24,    25,    26,    49,    49,
      47,    30,    18,    47,    47,    47,    13,    36,    37,    47,
      42,    47,     1,    18,    49,    18,    45,    46,    18,    18,
      49,    48,    11,    52,    13,    14,    15,    16,    17,    18,
      50,    20,    21,    22,    23,    24,    25,    26,    47,    49,
      18,    30,    18,    44,    50,    12,    44,    36,    37,    45,
      44,     8,     1,    50,    47,    47,    45,    46,    24,    74,
      49,    51,    11,    52,    13,    14,    15,    16,    17,    18,
      51,    20,    21,    22,    23,    24,    25,    26,    51,    56,
      34,    30,    -1,   160,    -1,    -1,    -1,    36,    37,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    45,    46,    -1,    -1,
      49,    -1,    11,    52,    13,    14,    15,    16,    17,    18,
      -1,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    45,    46,    -1,    -1,
      49,    -1,    11,    52,    13,    14,    15,    16,    17,    18,
      -1,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    45,    46,    -1,    -1,
      49,    -1,    11,    52,    13,    14,    15,    16,    17,    18,
      -1,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    45,    46,    -1,    -1,
      49,    -1,    11,    52,    13,    14,    15,    16,    17,    18,
      -1,    20,    -1,    -1,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    17,    18,    -1,    -1,    -1,    36,    37,     4,
       5,     6,     7,     8,     9,    30,    45,    46,    -1,    -1,
      49,    36,    37,    52,    -1,     4,     5,     6,     7,     8,
       9,    -1,    27,    28,    49,    -1,    -1,    52,    33,    -1,
      35,    36,    37,    38,    -1,    40,    41,    -1,    27,    28,
      -1,    -1,    -1,    -1,    33,    50,    35,    36,    37,    38,
      -1,    40,    41,     4,     5,     6,     7,     8,     9,    -1,
      33,    50,    35,    36,    37,    38,    -1,    40,    41,     4,
       5,     6,     7,     8,     9,    -1,    27,    28,    -1,    -1,
      -1,    -1,    33,    -1,    35,    36,    37,    38,    -1,    40,
      41,    -1,    27,    28,    -1,    -1,    -1,    -1,    33,    50,
      35,    36,    37,    38,    -1,    40,    41,     4,     5,     6,
       7,     8,     9,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     4,     5,     6,     7,     8,     9,    -1,
      27,    28,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    -1,    40,    41,    -1,    27,    28,    -1,    -1,
      -1,    -1,    33,    50,    35,    36,    37,    38,    -1,    40,
      41,    42,     4,     5,     6,     7,     8,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,
       6,     7,     8,     9,    -1,    27,    28,    -1,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    -1,    40,    41,
      42,    27,    28,    -1,    -1,    -1,    -1,    33,    -1,    35,
      36,    37,    38,    -1,    40,    41,    42,     4,     5,     6,
       7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,     6,     7,     8,     9,    -1,    -1,
      27,    28,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    -1,    40,    41,    27,    28,     0,     1,    -1,
       3,    33,    -1,    35,    36,    37,    38,    -1,    40,    41,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    32,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    35,    36,    37,    38,    -1,    40,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    29,    31,    32,    34,    54,    55,    56,
      57,    62,    66,    18,    45,    57,     0,    56,    18,    37,
      47,    63,    64,    67,    45,    57,    58,    59,    18,    37,
      41,    65,    18,    47,    48,    49,    58,    18,    37,    60,
      61,    46,    59,    41,    47,    18,    17,    18,    64,    57,
      68,    69,    46,    65,    18,    47,    48,    17,    47,    42,
      18,    37,    50,    48,    61,    42,    65,    41,    18,    45,
      75,    57,    47,    42,    76,    18,    37,     1,    11,    13,
      14,    15,    16,    17,    18,    20,    23,    24,    25,    26,
      30,    36,    37,    49,    52,    57,    62,    70,    71,    75,
      77,    78,    79,    83,    84,    85,    86,    87,    88,    89,
      93,    94,    41,    18,    49,    49,    18,    18,    19,    30,
      18,    37,    79,    44,    49,    49,    47,    49,    75,    47,
      79,    79,    79,    18,    80,    46,    70,    47,     4,     5,
       6,     7,     8,     9,    27,    28,    33,    35,    36,    37,
      38,    40,    41,    47,    47,    47,    47,    42,    79,    79,
      49,    79,    33,    40,    41,    79,    79,    81,    82,    79,
      78,    90,    93,    13,    44,    50,    33,    40,    41,    79,
      79,    79,    79,    79,    79,    79,    79,    18,    79,    79,
      79,    79,    18,    79,    50,    50,    81,    18,    18,    79,
      50,    48,    50,    47,    49,    79,    18,    18,    79,    44,
      44,    42,    75,    75,    50,    42,    79,    45,    79,    91,
      79,    42,    79,    79,    44,    12,    72,    47,    50,    79,
      75,    73,    78,    92,    93,    47,    21,    22,    46,    74,
      50,    17,    30,    51,    75,    51,    51,    77,    77,    77
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    58,    58,    59,    60,    60,    61,    61,
      61,    62,    62,    62,    62,    62,    63,    63,    64,    64,
      64,    65,    65,    66,    66,    67,    68,    68,    69,    69,
      69,    69,    69,    69,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    71,    72,
      73,    73,    74,    74,    74,    74,    74,    74,    75,    76,
      76,    77,    77,    78,    78,    78,    78,    78,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    80,    80,    80,    80,    81,    81,    82,    82,    83,
      84,    84,    84,    85,    86,    86,    87,    88,    89,    90,
      90,    90,    91,    91,    92,    92,    92,    93,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     1,     5,
       4,     2,     1,     1,     2,     3,     1,     3,     1,     2,
       2,     3,     4,     5,     7,     2,     1,     3,     1,     2,
       2,     4,     3,     6,     1,     1,     0,     1,     2,     3,
       4,     4,     5,     6,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     8,     0,
       0,     2,     4,     3,     4,     3,     3,     2,     4,     0,
       2,     1,     2,     3,     4,     6,     5,     5,     3,     3,
       3,     3,     2,     2,     2,     4,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     4,     3,     3,     0,     1,     1,     3,     2,
       2,     2,     2,     2,     5,     7,     5,     7,     9,     1,
       1,     0,     1,     0,     1,     1,     0,     4,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
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
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
  case 2: /* program: function_declaration_list  */
#line 67 "mini.y"
{
    tac_last=(yyvsp[0].tac);
    tac_complete();
}
#line 1442 "mini.y.c"
    break;

  case 4: /* function_declaration_list: function_declaration_list function_declaration  */
#line 75 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1450 "mini.y.c"
    break;

  case 7: /* type_spec: INT  */
#line 86 "mini.y"
       { current_type = T_INT;  current_sdef = NULL; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
#line 1456 "mini.y.c"
    break;

  case 8: /* type_spec: CHAR  */
#line 87 "mini.y"
       { current_type = T_CHAR; current_sdef = NULL; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
#line 1462 "mini.y.c"
    break;

  case 9: /* type_spec: STRUCT IDENTIFIER '{' field_decl_list '}'  */
#line 89 "mini.y"
  { SDEF *d = struct_define((yyvsp[-3].string), (yyvsp[-1].field)); current_type = T_STRUCT; current_sdef = d; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
#line 1468 "mini.y.c"
    break;

  case 10: /* type_spec: STRUCT '{' field_decl_list '}'  */
#line 91 "mini.y"
  { SDEF *d = struct_define(NULL, (yyvsp[-1].field)); current_type = T_STRUCT; current_sdef = d; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
#line 1474 "mini.y.c"
    break;

  case 11: /* type_spec: STRUCT IDENTIFIER  */
#line 93 "mini.y"
  { SDEF *d = struct_forward((yyvsp[0].string)); current_type = T_STRUCT; current_sdef = d; current_elem_dtype=T_UNDEF; current_elem_sdef=NULL; current_ptr_level=0; current_array_len=0; }
#line 1480 "mini.y.c"
    break;

  case 12: /* type_spec: TYPEID  */
#line 95 "mini.y"
  {
    int dt, edt, pl, al; SDEF *sd, *esd;
    if (!typedef_get((yyvsp[0].string), &dt, &edt, &pl, &al, &sd, &esd)) yyerror("unknown typedef");
    current_type = dt; current_sdef = sd;
    current_elem_dtype = edt; current_elem_sdef = esd;
    current_ptr_level = pl; current_array_len = al;
  }
#line 1492 "mini.y.c"
    break;

  case 13: /* field_decl_list: field_decl  */
#line 106 "mini.y"
                                       { (yyval.field) = (yyvsp[0].field); }
#line 1498 "mini.y.c"
    break;

  case 14: /* field_decl_list: field_decl_list field_decl  */
#line 107 "mini.y"
                                       { (yyval.field) = field_join((yyvsp[-1].field), (yyvsp[0].field)); }
#line 1504 "mini.y.c"
    break;

  case 15: /* field_decl: type_spec field_var_list ';'  */
#line 111 "mini.y"
                                       { (yyval.field) = (yyvsp[-1].field); }
#line 1510 "mini.y.c"
    break;

  case 16: /* field_var_list: field_var_unit  */
#line 115 "mini.y"
                                       { (yyval.field) = (yyvsp[0].field); }
#line 1516 "mini.y.c"
    break;

  case 17: /* field_var_list: field_var_list ',' field_var_unit  */
#line 116 "mini.y"
                                       { (yyval.field) = field_join((yyvsp[-2].field), (yyvsp[0].field)); }
#line 1522 "mini.y.c"
    break;

  case 18: /* field_var_unit: IDENTIFIER  */
#line 120 "mini.y"
                                       { (yyval.field) = field_from_current((yyvsp[0].string), 0, 0); }
#line 1528 "mini.y.c"
    break;

  case 19: /* field_var_unit: '*' IDENTIFIER  */
#line 121 "mini.y"
                                       { (yyval.field) = field_from_current((yyvsp[0].string), 1, 0); }
#line 1534 "mini.y.c"
    break;

  case 20: /* field_var_unit: IDENTIFIER dims  */
#line 122 "mini.y"
                                        { (yyval.field) = field_from_current_dl((yyvsp[-1].string), 0, (yyvsp[0].dims)); }
#line 1540 "mini.y.c"
    break;

  case 21: /* declaration: type_spec variable_list ';'  */
#line 127 "mini.y"
                                 { (yyval.tac) = (yyvsp[-1].tac); }
#line 1546 "mini.y.c"
    break;

  case 22: /* declaration: TYPEDEF type_spec IDENTIFIER ';'  */
#line 128 "mini.y"
                                             { typedef_add((yyvsp[-1].string), current_type, T_UNDEF, 0, 0, current_sdef, NULL); (yyval.tac) = NULL; }
#line 1552 "mini.y.c"
    break;

  case 23: /* declaration: TYPEDEF type_spec '*' IDENTIFIER ';'  */
#line 129 "mini.y"
                                             { typedef_add((yyvsp[-1].string), T_PTR, current_type, 1, 0, NULL, current_sdef); (yyval.tac) = NULL; }
#line 1558 "mini.y.c"
    break;

  case 24: /* declaration: TYPEDEF type_spec IDENTIFIER '[' INTEGER ']' ';'  */
#line 131 "mini.y"
  { typedef_add((yyvsp[-4].string), T_ARRAY, current_type, 0, atoi((yyvsp[-2].string)), NULL, current_sdef); (yyval.tac) = NULL; }
#line 1564 "mini.y.c"
    break;

  case 25: /* declaration: type_spec ';'  */
#line 132 "mini.y"
                                { (yyval.tac) = NULL; }
#line 1570 "mini.y.c"
    break;

  case 26: /* variable_list: var_unit  */
#line 135 "mini.y"
                                { (yyval.tac) = (yyvsp[0].tac); }
#line 1576 "mini.y.c"
    break;

  case 27: /* variable_list: variable_list ',' var_unit  */
#line 136 "mini.y"
                                { (yyval.tac) = join_tac((yyvsp[-2].tac), (yyvsp[0].tac)); }
#line 1582 "mini.y.c"
    break;

  case 28: /* var_unit: IDENTIFIER  */
#line 140 "mini.y"
                                { (yyval.tac) = declare_var((yyvsp[0].string)); }
#line 1588 "mini.y.c"
    break;

  case 29: /* var_unit: '*' IDENTIFIER  */
#line 141 "mini.y"
                                { (yyval.tac) = declare_var_ptr((yyvsp[0].string), 1); }
#line 1594 "mini.y.c"
    break;

  case 30: /* var_unit: IDENTIFIER dims  */
#line 142 "mini.y"
                                {
    int n = dl_count((yyvsp[0].dims));
    int *lens = (int*)malloc(sizeof(int)*n);
    dl_to_array((yyvsp[0].dims), lens);
    (yyval.tac) = declare_var_array_multi_lens((yyvsp[-1].string), lens, n);
}
#line 1605 "mini.y.c"
    break;

  case 31: /* dims: '[' INTEGER ']' dims  */
#line 151 "mini.y"
                                { (yyval.dims) = dl_new(atoi((yyvsp[-2].string)), (yyvsp[0].dims)); }
#line 1611 "mini.y.c"
    break;

  case 32: /* dims: '[' INTEGER ']'  */
#line 152 "mini.y"
                                { (yyval.dims) = dl_new(atoi((yyvsp[-1].string)), NULL); }
#line 1617 "mini.y.c"
    break;

  case 33: /* function: type_spec function_head '(' parameter_list ')' block  */
#line 158 "mini.y"
{
    current_function = (yyvsp[-4].sym);
    current_function->dtype = current_type;       /* 设置返回类型 */
    current_function->sdef  = (current_type == T_STRUCT) ? current_sdef : NULL;
    (yyval.tac) = do_func((yyvsp[-4].sym), (yyvsp[-2].tac), (yyvsp[0].tac));
    scope = 0; sym_tab_local = NULL; current_function = NULL;
}
#line 1629 "mini.y.c"
    break;

  case 34: /* function: error  */
#line 166 "mini.y"
{
    error("Bad function syntax");
    (yyval.tac) = NULL;
}
#line 1638 "mini.y.c"
    break;

  case 35: /* function_head: IDENTIFIER  */
#line 173 "mini.y"
{
    (yyval.sym)=declare_func((yyvsp[0].string));
    scope=1; /* Enter local scope. */
    sym_tab_local=NULL; /* Init local symbol table. */
}
#line 1648 "mini.y.c"
    break;

  case 36: /* parameter_list: %empty  */
#line 181 "mini.y"
              { (yyval.tac) = NULL; }
#line 1654 "mini.y.c"
    break;

  case 38: /* param_seq: type_spec IDENTIFIER  */
#line 186 "mini.y"
                                                { (yyval.tac) = declare_para((yyvsp[0].string)); }
#line 1660 "mini.y.c"
    break;

  case 39: /* param_seq: type_spec '*' IDENTIFIER  */
#line 187 "mini.y"
                                                { (yyval.tac) = declare_para_ptr((yyvsp[0].string), 1); }
#line 1666 "mini.y.c"
    break;

  case 40: /* param_seq: type_spec IDENTIFIER '[' ']'  */
#line 188 "mini.y"
                                                { (yyval.tac) = declare_para_array((yyvsp[-2].string), 0); }
#line 1672 "mini.y.c"
    break;

  case 41: /* param_seq: param_seq ',' type_spec IDENTIFIER  */
#line 189 "mini.y"
                                                { (yyval.tac) = join_tac((yyvsp[-3].tac), declare_para((yyvsp[0].string))); }
#line 1678 "mini.y.c"
    break;

  case 42: /* param_seq: param_seq ',' type_spec '*' IDENTIFIER  */
#line 190 "mini.y"
                                                { (yyval.tac) = join_tac((yyvsp[-4].tac), declare_para_ptr((yyvsp[0].string), 1)); }
#line 1684 "mini.y.c"
    break;

  case 43: /* param_seq: param_seq ',' type_spec IDENTIFIER '[' ']'  */
#line 191 "mini.y"
                                                { (yyval.tac) = join_tac((yyvsp[-5].tac), declare_para_array((yyvsp[-2].string), 0)); }
#line 1690 "mini.y.c"
    break;

  case 55: /* statement: BREAK ';'  */
#line 206 "mini.y"
            { (yyval.tac) = mk_tac(TAC_BREAK, NULL, NULL, NULL); }
#line 1696 "mini.y.c"
    break;

  case 56: /* statement: CONTINUE ';'  */
#line 207 "mini.y"
               { (yyval.tac) = mk_tac(TAC_CONTINUE, NULL, NULL, NULL); }
#line 1702 "mini.y.c"
    break;

  case 57: /* statement: error  */
#line 208 "mini.y"
        { error("Bad statement syntax"); (yyval.tac)=NULL; }
#line 1708 "mini.y.c"
    break;

  case 58: /* switch_statement: SWITCH '(' expression ')' '{' setup case_list '}'  */
#line 213 "mini.y"
{
    TAC *res = do_switch((yyvsp[-5].exp), (yyvsp[-1].tac));
    parser_switch_end = NULL;
    (yyval.tac) = res;
}
#line 1718 "mini.y.c"
    break;

  case 59: /* setup: %empty  */
#line 222 "mini.y"
{
    SYM *end_label = mk_label(mk_lstr(next_label++));
    parser_switch_end = end_label;
    (yyval.tac) = NULL;
}
#line 1728 "mini.y.c"
    break;

  case 60: /* case_list: %empty  */
#line 229 "mini.y"
                        { (yyval.tac) = NULL; }
#line 1734 "mini.y.c"
    break;

  case 61: /* case_list: case_list case_item  */
#line 230 "mini.y"
                      { (yyval.tac) = join_tac((yyvsp[-1].tac), (yyvsp[0].tac)); }
#line 1740 "mini.y.c"
    break;

  case 62: /* case_item: CASE INTEGER ':' statement_list  */
#line 234 "mini.y"
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *body = (yyvsp[0].tac);
    TAC *case_tac = mk_tac(TAC_CASE, mk_const(atoi((yyvsp[-2].string))), lbl, NULL);
    case_tac->etc = (void *)body;
    (yyval.tac) = case_tac;
}
#line 1752 "mini.y.c"
    break;

  case 63: /* case_item: CASE INTEGER ':'  */
#line 242 "mini.y"
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *case_tac = mk_tac(TAC_CASE, mk_const(atoi((yyvsp[-1].string))), lbl, NULL);
    case_tac->etc = NULL;
    (yyval.tac) = case_tac;
}
#line 1763 "mini.y.c"
    break;

  case 64: /* case_item: CASE CHARACTER ':' statement_list  */
#line 249 "mini.y"
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *body = (yyvsp[0].tac);
    TAC *case_tac = mk_tac(TAC_CASE, mk_char((int)(yyvsp[-2].character)), lbl, NULL);
    case_tac->etc = (void *)body;
    (yyval.tac) = case_tac;
}
#line 1775 "mini.y.c"
    break;

  case 65: /* case_item: CASE CHARACTER ':'  */
#line 257 "mini.y"
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *case_tac = mk_tac(TAC_CASE, mk_char((int)(yyvsp[-1].character)), lbl, NULL);
    case_tac->etc = NULL;
    (yyval.tac) = case_tac;
}
#line 1786 "mini.y.c"
    break;

  case 66: /* case_item: DEFAULT ':' statement_list  */
#line 264 "mini.y"
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *body = (yyvsp[0].tac);
    TAC *case_tac = mk_tac(TAC_CASE, NULL, lbl, NULL);
    case_tac->etc = (void *)body;
    (yyval.tac) = case_tac;
}
#line 1798 "mini.y.c"
    break;

  case 67: /* case_item: DEFAULT ':'  */
#line 272 "mini.y"
{
    SYM *lbl = mk_label(mk_lstr(next_label++));
    TAC *case_tac = mk_tac(TAC_CASE, NULL, lbl, NULL);
    case_tac->etc = NULL;
    (yyval.tac) = case_tac;
}
#line 1809 "mini.y.c"
    break;

  case 68: /* block: '{' declaration_list statement_list '}'  */
#line 281 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-2].tac), (yyvsp[-1].tac));
}
#line 1817 "mini.y.c"
    break;

  case 69: /* declaration_list: %empty  */
#line 287 "mini.y"
{
    (yyval.tac)=NULL;
}
#line 1825 "mini.y.c"
    break;

  case 70: /* declaration_list: declaration_list declaration  */
#line 291 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1833 "mini.y.c"
    break;

  case 72: /* statement_list: statement_list statement  */
#line 298 "mini.y"
{
    (yyval.tac)=join_tac((yyvsp[-1].tac), (yyvsp[0].tac));
}
#line 1841 "mini.y.c"
    break;

  case 73: /* assignment_statement: IDENTIFIER '=' expression  */
#line 306 "mini.y"
{
    (yyval.tac) = do_assign(get_var((yyvsp[-2].string)), (yyvsp[0].exp));
}
#line 1849 "mini.y.c"
    break;

  case 74: /* assignment_statement: '*' expression '=' expression  */
#line 310 "mini.y"
{
    (yyval.tac) = do_assign_deref((yyvsp[-2].exp), (yyvsp[0].exp));
}
#line 1857 "mini.y.c"
    break;

  case 75: /* assignment_statement: expression '[' expression ']' '=' expression  */
#line 314 "mini.y"
{
    (yyval.tac) = do_assign_index_exp((yyvsp[-5].exp), (yyvsp[-3].exp), (yyvsp[0].exp));
}
#line 1865 "mini.y.c"
    break;

  case 76: /* assignment_statement: expression '.' IDENTIFIER '=' expression  */
#line 318 "mini.y"
{
    (yyval.tac) = do_assign_field_select((yyvsp[-4].exp), (yyvsp[-2].string), 0, (yyvsp[0].exp));
}
#line 1873 "mini.y.c"
    break;

  case 77: /* assignment_statement: expression ARROW IDENTIFIER '=' expression  */
#line 322 "mini.y"
{
    (yyval.tac) = do_assign_field_select((yyvsp[-4].exp), (yyvsp[-2].string), 1, (yyvsp[0].exp));
}
#line 1881 "mini.y.c"
    break;

  case 78: /* expression: expression '+' expression  */
#line 329 "mini.y"
                            { (yyval.exp)=do_bin(TAC_ADD, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1887 "mini.y.c"
    break;

  case 79: /* expression: expression '-' expression  */
#line 330 "mini.y"
                            { (yyval.exp)=do_bin(TAC_SUB, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1893 "mini.y.c"
    break;

  case 80: /* expression: expression '*' expression  */
#line 331 "mini.y"
                            { (yyval.exp)=do_bin(TAC_MUL, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1899 "mini.y.c"
    break;

  case 81: /* expression: expression '/' expression  */
#line 332 "mini.y"
                            { (yyval.exp)=do_bin(TAC_DIV, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1905 "mini.y.c"
    break;

  case 82: /* expression: '-' expression  */
#line 333 "mini.y"
                               { (yyval.exp)=do_un(TAC_NEG, (yyvsp[0].exp)); }
#line 1911 "mini.y.c"
    break;

  case 83: /* expression: '*' expression  */
#line 334 "mini.y"
                               { (yyval.exp)=do_deref((yyvsp[0].exp)); }
#line 1917 "mini.y.c"
    break;

  case 84: /* expression: '&' laddr  */
#line 335 "mini.y"
                              { (yyval.exp)=(yyvsp[0].exp); }
#line 1923 "mini.y.c"
    break;

  case 85: /* expression: expression '[' expression ']'  */
#line 336 "mini.y"
                                { (yyval.exp)=do_index((yyvsp[-3].exp), (yyvsp[-1].exp)); }
#line 1929 "mini.y.c"
    break;

  case 86: /* expression: expression '.' IDENTIFIER  */
#line 337 "mini.y"
                              { (yyval.exp)=do_field_select((yyvsp[-2].exp), (yyvsp[0].string), 0); }
#line 1935 "mini.y.c"
    break;

  case 87: /* expression: expression ARROW IDENTIFIER  */
#line 338 "mini.y"
                              { (yyval.exp)=do_field_select((yyvsp[-2].exp), (yyvsp[0].string), 1); }
#line 1941 "mini.y.c"
    break;

  case 88: /* expression: expression EQ expression  */
#line 339 "mini.y"
                           { (yyval.exp)=do_cmp(TAC_EQ, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1947 "mini.y.c"
    break;

  case 89: /* expression: expression NE expression  */
#line 340 "mini.y"
                           { (yyval.exp)=do_cmp(TAC_NE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1953 "mini.y.c"
    break;

  case 90: /* expression: expression LT expression  */
#line 341 "mini.y"
                           { (yyval.exp)=do_cmp(TAC_LT, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1959 "mini.y.c"
    break;

  case 91: /* expression: expression LE expression  */
#line 342 "mini.y"
                           { (yyval.exp)=do_cmp(TAC_LE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1965 "mini.y.c"
    break;

  case 92: /* expression: expression GT expression  */
#line 343 "mini.y"
                           { (yyval.exp)=do_cmp(TAC_GT, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1971 "mini.y.c"
    break;

  case 93: /* expression: expression GE expression  */
#line 344 "mini.y"
                           { (yyval.exp)=do_cmp(TAC_GE, (yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1977 "mini.y.c"
    break;

  case 94: /* expression: expression AND expression  */
#line 345 "mini.y"
                            { (yyval.exp)=do_logic_and((yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1983 "mini.y.c"
    break;

  case 95: /* expression: expression OR expression  */
#line 346 "mini.y"
                            { (yyval.exp)=do_logic_or((yyvsp[-2].exp), (yyvsp[0].exp)); }
#line 1989 "mini.y.c"
    break;

  case 96: /* expression: '(' expression ')'  */
#line 347 "mini.y"
                     { (yyval.exp)=(yyvsp[-1].exp); }
#line 1995 "mini.y.c"
    break;

  case 97: /* expression: INTEGER  */
#line 348 "mini.y"
           { (yyval.exp)=mk_exp(NULL, mk_const(atoi((yyvsp[0].string))), NULL); }
#line 2001 "mini.y.c"
    break;

  case 98: /* expression: CHARACTER  */
#line 349 "mini.y"
            { (yyval.exp)=mk_exp(NULL, mk_char((int)(yyvsp[0].character)), NULL); }
#line 2007 "mini.y.c"
    break;

  case 99: /* expression: IDENTIFIER  */
#line 350 "mini.y"
                                      { (yyval.exp)=exp_from_symbol(get_var((yyvsp[0].string))); }
#line 2013 "mini.y.c"
    break;

  case 100: /* expression: call_expression  */
#line 351 "mini.y"
                  { (yyval.exp)=(yyvsp[0].exp); }
#line 2019 "mini.y.c"
    break;

  case 101: /* laddr: IDENTIFIER  */
#line 357 "mini.y"
{
    /* &IDENTIFIER 等价于取该变量地址 */
    (yyval.exp) = do_addr_var(get_var((yyvsp[0].string)));
}
#line 2028 "mini.y.c"
    break;

  case 102: /* laddr: laddr '[' expression ']'  */
#line 362 "mini.y"
{
    /* 在已有地址（指针值）基础上，计算元素地址 */
    (yyval.exp) = addr_index((yyvsp[-3].exp), (yyvsp[-1].exp));
}
#line 2037 "mini.y.c"
    break;

  case 103: /* laddr: laddr '.' IDENTIFIER  */
#line 367 "mini.y"
{
    /* 已有的是地址（指针），对后续 .name 当作指针访问处理（等价于 ->） */
    (yyval.exp) = addr_field_select((yyvsp[-2].exp), (yyvsp[0].string), 1);
}
#line 2046 "mini.y.c"
    break;

  case 104: /* laddr: laddr ARROW IDENTIFIER  */
#line 372 "mini.y"
{
    /* 仅允许在“地址链”上进行 -> 选择，避免与通用 expression 冲突 */
    (yyval.exp) = addr_field_select((yyvsp[-2].exp), (yyvsp[0].string), 1);
}
#line 2055 "mini.y.c"
    break;

  case 105: /* argument_list: %empty  */
#line 378 "mini.y"
                            { (yyval.exp)=NULL; }
#line 2061 "mini.y.c"
    break;

  case 108: /* expression_list: expression_list ',' expression  */
#line 381 "mini.y"
                                  { (yyvsp[0].exp)->next=(yyvsp[-2].exp); (yyval.exp)=(yyvsp[0].exp); }
#line 2067 "mini.y.c"
    break;

  case 109: /* input_statement: INPUT IDENTIFIER  */
#line 384 "mini.y"
                                   { (yyval.tac)=do_input(get_var((yyvsp[0].string))); }
#line 2073 "mini.y.c"
    break;

  case 110: /* output_statement: OUTPUT IDENTIFIER  */
#line 387 "mini.y"
                                     { (yyval.tac)=do_output(get_var((yyvsp[0].string))); }
#line 2079 "mini.y.c"
    break;

  case 111: /* output_statement: OUTPUT TEXT  */
#line 388 "mini.y"
              { (yyval.tac)=do_output(mk_text((yyvsp[0].string))); }
#line 2085 "mini.y.c"
    break;

  case 112: /* output_statement: OUTPUT CHARACTER  */
#line 389 "mini.y"
                   { (yyval.tac)=do_output(mk_char((int)(yyvsp[0].character))); }
#line 2091 "mini.y.c"
    break;

  case 113: /* return_statement: RETURN expression  */
#line 393 "mini.y"
{
    if (current_function && current_function->dtype != (yyvsp[0].exp)->ret->dtype)
        error("return type mismatch");
    TAC *t=mk_tac(TAC_RETURN, (yyvsp[0].exp)->ret, NULL, NULL);
    t->prev=(yyvsp[0].exp)->tac;
    (yyval.tac)=t;
}
#line 2103 "mini.y.c"
    break;

  case 114: /* if_statement: IF '(' expression ')' block  */
#line 402 "mini.y"
                                                                 { (yyval.tac)=do_if((yyvsp[-2].exp), (yyvsp[0].tac)); }
#line 2109 "mini.y.c"
    break;

  case 115: /* if_statement: IF '(' expression ')' block ELSE block  */
#line 403 "mini.y"
                                           { (yyval.tac)=do_test((yyvsp[-4].exp), (yyvsp[-2].tac), (yyvsp[0].tac)); }
#line 2115 "mini.y.c"
    break;

  case 116: /* while_statement: WHILE '(' expression ')' block  */
#line 406 "mini.y"
                                                 { (yyval.tac)=do_while((yyvsp[-2].exp), (yyvsp[0].tac)); }
#line 2121 "mini.y.c"
    break;

  case 117: /* do_while_statement: DO block WHILE '(' expression ')' ';'  */
#line 409 "mini.y"
                                                           { (yyval.tac)=do_do_while((yyvsp[-2].exp), (yyvsp[-5].tac)); }
#line 2127 "mini.y.c"
    break;

  case 118: /* for_statement: FOR '(' for_init ';' for_cond ';' for_iter ')' block  */
#line 412 "mini.y"
                                                                     { (yyval.tac)=do_for((yyvsp[-6].tac), (yyvsp[-4].exp), (yyvsp[-2].tac), (yyvsp[0].tac)); }
#line 2133 "mini.y.c"
    break;

  case 119: /* for_init: assignment_statement  */
#line 415 "mini.y"
                                { (yyval.tac)=(yyvsp[0].tac); }
#line 2139 "mini.y.c"
    break;

  case 120: /* for_init: call_statement  */
#line 415 "mini.y"
                                                            { (yyval.tac)=(yyvsp[0].tac); }
#line 2145 "mini.y.c"
    break;

  case 121: /* for_init: %empty  */
#line 415 "mini.y"
                                                                         { (yyval.tac)=NULL; }
#line 2151 "mini.y.c"
    break;

  case 122: /* for_cond: expression  */
#line 416 "mini.y"
                      { (yyval.exp)=(yyvsp[0].exp); }
#line 2157 "mini.y.c"
    break;

  case 123: /* for_cond: %empty  */
#line 416 "mini.y"
                                   { (yyval.exp)=mk_exp(NULL, mk_const(1), NULL); }
#line 2163 "mini.y.c"
    break;

  case 124: /* for_iter: assignment_statement  */
#line 417 "mini.y"
                                { (yyval.tac)=(yyvsp[0].tac); }
#line 2169 "mini.y.c"
    break;

  case 125: /* for_iter: call_statement  */
#line 417 "mini.y"
                                                            { (yyval.tac)=(yyvsp[0].tac); }
#line 2175 "mini.y.c"
    break;

  case 126: /* for_iter: %empty  */
#line 417 "mini.y"
                                                                         { (yyval.tac)=NULL; }
#line 2181 "mini.y.c"
    break;

  case 127: /* call_statement: IDENTIFIER '(' argument_list ')'  */
#line 419 "mini.y"
                                                  { (yyval.tac)=do_call((yyvsp[-3].string), (yyvsp[-1].exp)); }
#line 2187 "mini.y.c"
    break;

  case 128: /* call_expression: IDENTIFIER '(' argument_list ')'  */
#line 421 "mini.y"
                                                   { (yyval.exp)=do_call_ret((yyvsp[-3].string), (yyvsp[-1].exp)); }
#line 2193 "mini.y.c"
    break;


#line 2197 "mini.y.c"

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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 424 "mini.y"


void yyerror(char* msg) 
{
    fprintf(stderr, "%s: line %d\n", msg, yylineno);
    exit(0);
}
