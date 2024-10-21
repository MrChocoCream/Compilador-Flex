
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "sintactico.y"


/*
Este es un analizador sintáctico y léxico para el lenguaje de programación C.
El código se divide en varias secciones:
- Definiciones de estructuras y funciones auxiliares
- Definiciones de tokens
- Reglas de gramática
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int yylex(void);
void add_syntax_token(char* type);

void yyerror(char *s) {
    add_syntax_token("ERROR DE SINTAXIS");
}



//***************definiciones de constantes***************
#define MAX_ERRORS 1000
#define MAX_TOKENS 1000
#define MAX_SIMBOLOS 1000
#define MAX_SYNTAX_TOKENS 1000


//***************Estructuras de datos***************

// Estructura para almacenar los mensajes de error
typedef struct {
    char* message;
} Error;

// Estructura para las entradas en la tabla de símbolos
typedef struct {
    char* tipo;
    char* identificador;
    char* valor;
} EntradaTablaSimbolos;

// Estructura para los tokens generados por el análisis léxico
typedef struct {
    char* type;
    char* value;
} Token;

// Estructura para los tokens generados por el análisis sintáctico
typedef struct {
    char* type;
} SyntaxToken;



//***************Funciones de impresion***************

void print_error_messages() {
    printf(",\"errores\": [");
    for (int i = 0; i < num_errors; i++) {
        printf("\"%s\"", error_messages[i].message);
        if (i < num_errors - 1) {
            printf(", ");
        }
    }
    printf("]");
}

// Imprime la tabla de símbolos
void print_tabla_simbolos() {
    printf(",\"tabla_simbolos\": [");
    for (int i = 0; i < num_simbolos; i++) {
        printf("{\"tipo\": \"%s\", \"identificador\": \"%s\", \"valor\": \"%s\"}", tabla_simbolos[i].tipo, tabla_simbolos[i].identificador, tabla_simbolos[i].valor);
        if (i < num_simbolos - 1) {
            printf(", ");
        }
    }
    printf("]");
}

// Imprime los tokens del análisis léxico
void print_tokens() {
    printf("\"lexico\":[");
    for (int i = 0; i < num_tokens; i++) {
        char *escaped_value = malloc(strlen(tokens[i].value) * 2 + 1); // Allocate enough space for the escaped string
        char *p = tokens[i].value;
        char *q = escaped_value;
        while (*p) {
            if (*p == '"') {
                *q++ = '\\';
            }
            *q++ = *p++;
        }
        *q = '\0';
        printf("{\"type\": \"%s\", \"value\": \"%s\"}%s", tokens[i].type, escaped_value, i < num_tokens - 1 ? ", " : "");
        free(escaped_value);
    }
    printf("]");
}

// Imprime los tokens del análisis sintáctico
void print_syntax_tokens() {
    printf(",\"sintactico\":[");
    for (int i = 0; i < num_syntax_tokens; i++) {
        printf("{\"type\": \"%s\"}", syntax_tokens[i].type);
        if (i < num_syntax_tokens - 1) {
            printf(", ");
        }
    }
    printf("]");
}


//***************Datos iniciales*****************

EntradaTablaSimbolos tabla_simbolos[MAX_SIMBOLOS];
int num_simbolos = 0;

Token tokens[MAX_TOKENS];
int num_tokens = 0;

Error error_messages[MAX_ERRORS];
int num_errors = 0;

SyntaxToken syntax_tokens[MAX_SYNTAX_TOKENS];
int num_syntax_tokens = 0;

char* tipo_dato_global;



//***************Funciones auxiliares*****************

// Verifica si un valor es compatible con un tipo de dato
int es_tipo_compatible(char* tipo_dato, char* valor) {
    if (strcmp(tipo_dato, "int") == 0 || strcmp(tipo_dato, "float") == 0) {
        // Verificar si valor es un número

        char* end;
        strtod(valor, &end);
        return end != valor && *end == '\0';
        
    } else if (strcmp(tipo_dato, "char") == 0) {
        // Verificar si valor es una cadena
        int longitud = strlen(valor);
        if (longitud >= 2 && strncmp(valor, "'", 1) == 0 && strncmp(valor + longitud - 1, "'", 1) == 0) {
            return 1;
        } else {
            return 0;
        }
    } else if (strcmp(tipo_dato, "bool") == 0) {
        // Verificar si valor es "verdadero" o "falso"
        return strcmp(valor, "0") == 0 || strcmp(valor, "1") == 0;
    }else {
        // Tipo de dato desconocido
        return 1;
    }
}

// Busca el índice de un símbolo en la tabla de símbolos
int buscar_indice_simbolo(char* identificador) {
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabla_simbolos[i].identificador, identificador) == 0) {
            return i;
        }
    }
    return -1;
}

// Busca el valor de un símbolo en la tabla de símbolos
char* buscar_valor(char* identificador) {
    for (int i = 0; i < num_simbolos; i++) {
        if (strcmp(tabla_simbolos[i].identificador, identificador) == 0) {
            return tabla_simbolos[i].valor;
        }
    }
    // Devuelve -1 si el identificador no se encuentra en la tabla de símbolos
    return NULL;
}



//***************Funciones de registro***************
// Agrega un valor a un símbolo en la tabla de símbolos
void agregar_valor(char *identificador, char* valor) {
    int indice = buscar_indice_simbolo(identificador);
    if (indice == -1) {
        char error_message[256];
        sprintf(error_message, "ERROR: La variable '%s' no ha sido declarada", identificador);
        add_error_message(error_message);
    } else {
         
        if (!es_tipo_compatible(tabla_simbolos[indice].tipo, valor)) {
            char error_message[256];
            sprintf(error_message, "ERROR: Tipo de dato incorrecto para la variable '%s'", identificador);
            add_error_message(error_message);
        } else {   
            if(strcmp(tabla_simbolos[indice].tipo, "int")  ==  0)  {
            double valor_double = strtod(valor, NULL);
            int valor_int = round(valor_double);
            char valor_redondeado[256];
            sprintf(valor_redondeado, "%d", valor_int);
            valor = valor_redondeado;
        }    
            tabla_simbolos[indice].valor = strdup(valor); 
            add_syntax_token("ASIGNACION"); 
        }
    }
}

// Agrega un nuevo símbolo a la tabla de símbolos
void agregar_simbolo(char* tipo, char* identificador, char* valor) {
    if (num_simbolos < MAX_SIMBOLOS) {
        int indice = buscar_indice_simbolo(identificador);
        if (indice != -1) {
            char error_message[256];
            sprintf(error_message, "ERROR: variable '%s' ya declarada", identificador);
            add_error_message(error_message);
        } else {
            tabla_simbolos[num_simbolos].tipo = strdup(tipo);
            tabla_simbolos[num_simbolos].identificador = strdup(identificador);
             num_simbolos++;
             
            if (valor != NULL) {
                agregar_valor(identificador, valor);
            } 
            add_syntax_token("DECLARACION");
        }
    }
}

// Agrega un nuevo token al análisis léxico
void add_token(char* type, char* value) {
    if (num_tokens < MAX_TOKENS) {
        tokens[num_tokens].type = type;
        tokens[num_tokens].value = strdup(value);
        num_tokens++;
    }
}

// Agrega un nuevo token al análisis sintáctico
void add_syntax_token(char* type) {
    if (num_syntax_tokens < MAX_SYNTAX_TOKENS) {
        syntax_tokens[num_syntax_tokens].type = strdup(type);
        num_syntax_tokens++;
    }
}

// Agrega un error al análisis semantico
void add_error_message(char* message) {
    if (num_errors < MAX_ERRORS) {
        error_messages[num_errors].message = strdup(message);
        num_errors++;
    }
}



/* Line 189 of yacc.c  */
#line 335 "sintactico.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ERROR = 258,
     NUMERO = 259,
     TIPO_DE_DATO = 260,
     COMPARACION = 261,
     PALABRA_RESERVADA = 262,
     IDENTIFICADOR = 263,
     CONST_CADENA = 264,
     SIMBOLO_ASIGNACION = 265,
     SIGNO_NEGATIVO = 266,
     INCREMENTO = 267,
     FIN = 268,
     IMPRIMIR_VAR = 269
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 264 "sintactico.y"

    double entero;
    char* str; 



/* Line 214 of yacc.c  */
#line 392 "sintactico.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 404 "sintactico.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  37
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  41
/* YYNRULES -- Number of states.  */
#define YYNSTATES  103

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   269

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      21,    22,    17,    15,    29,    16,     2,    18,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    19,     2,     2,     2,     2,     2,
      25,    23,    26,     2,     2,    20,     2,     2,     2,    27,
       2,     2,    28,     2,     2,    30,     2,     2,     2,    24,
       2,     2,     2,    31,     2,    32,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    14,    17,    20,    23,
      25,    31,    39,    45,    52,    63,    69,    74,    81,    88,
      90,    94,    98,   102,   103,   107,   109,   113,   117,   123,
     127,   131,   135,   138,   140,   142,   144,   148,   152,   154,
     156,   158
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      34,     0,    -1,    35,    -1,    34,    35,    -1,    45,    13,
      -1,    41,    13,    -1,    44,    13,    -1,    37,    13,    -1,
      40,    13,    -1,    36,    -1,    20,    21,    40,    22,    39,
      -1,    20,    21,    40,    22,    39,    23,    39,    -1,    24,
      21,    40,    22,    39,    -1,    25,    39,    24,    21,    40,
      22,    -1,    26,    21,    44,    13,    40,    13,    12,     8,
      22,    39,    -1,     5,    27,    21,    22,    39,    -1,    28,
      21,     9,    22,    -1,    28,    21,     9,    29,    38,    22,
      -1,    30,    21,     9,    29,    14,    22,    -1,     8,    -1,
       8,    29,    38,    -1,    31,    34,    32,    -1,    45,     6,
      45,    -1,    -1,     5,    42,    43,    -1,     8,    -1,     8,
      10,    45,    -1,     8,    29,    43,    -1,     8,    10,    45,
      29,    43,    -1,     8,    10,    45,    -1,    45,    15,    46,
      -1,    45,    16,    46,    -1,    16,    45,    -1,    46,    -1,
       9,    -1,     3,    -1,    46,    17,    47,    -1,    46,    18,
      47,    -1,    47,    -1,     4,    -1,     8,    -1,    21,    45,
      22,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   298,   298,   299,   304,   305,   306,   307,   308,   309,
     313,   314,   315,   316,   317,   318,   321,   322,   323,   327,
     327,   330,   333,   337,   337,   342,   343,   344,   345,   348,
     350,   354,   358,   362,   365,   369,   372,   373,   374,   378,
     379,   380
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ERROR", "NUMERO", "TIPO_DE_DATO",
  "COMPARACION", "PALABRA_RESERVADA", "IDENTIFICADOR", "CONST_CADENA",
  "SIMBOLO_ASIGNACION", "SIGNO_NEGATIVO", "INCREMENTO", "FIN",
  "IMPRIMIR_VAR", "'+'", "'-'", "'*'", "'/'", "'^'", "'i'", "'('", "')'",
  "'e'", "'w'", "'d'", "'f'", "'m'", "'p'", "','", "'s'", "'{'", "'}'",
  "$accept", "programa", "sentencia", "funcion", "instruccion", "imprimir",
  "bloque", "comparacion", "declaracion", "$@1", "lista_identificadores",
  "asignacion", "expresion", "termino", "factor", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    43,    45,    42,    47,    94,
     105,    40,    41,   101,   119,   100,   102,   109,   112,    44,
     115,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    33,    34,    34,    35,    35,    35,    35,    35,    35,
      36,    36,    36,    36,    36,    36,    37,    37,    37,    38,
      38,    39,    40,    42,    41,    43,    43,    43,    43,    44,
      45,    45,    45,    45,    45,    45,    46,    46,    46,    47,
      47,    47
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     2,     2,     2,     1,
       5,     7,     5,     6,    10,     5,     4,     6,     6,     1,
       3,     3,     3,     0,     3,     1,     3,     3,     5,     3,
       3,     3,     2,     1,     1,     1,     3,     3,     1,     1,
       1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    35,    39,    23,    40,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     2,     9,     0,     0,     0,
       0,     0,    33,    38,     0,     0,     0,    40,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     3,     7,
       8,     5,     6,     0,     4,     0,     0,     0,     0,     0,
      25,    24,    29,     0,     0,    41,     0,     0,     0,     0,
       0,     0,     0,    22,    30,    31,    36,    37,     0,     0,
       0,     0,     0,    21,     0,     0,    16,     0,     0,    15,
      26,    27,    10,    12,     0,     0,    19,     0,     0,     0,
       0,    13,     0,     0,    17,    18,    28,    11,     0,    20,
       0,     0,    14
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    14,    15,    16,    17,    87,    33,    18,    19,    25,
      51,    20,    21,    22,    23
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -63
static const yytype_int8 yypact[] =
{
      78,   -63,   -63,   -23,    -3,   -63,     8,     0,     8,    31,
      25,    46,    64,    69,    50,   -63,   -63,    80,    82,    83,
      84,    94,    15,   -63,    90,    93,     8,   -63,   -63,     8,
      57,     8,    78,    81,   104,   105,   106,   -63,   -63,   -63,
     -63,   -63,   -63,     8,   -63,    41,    41,    41,    41,    91,
      -2,   -63,    49,    95,    45,   -63,    96,    10,    98,    -3,
     103,    55,    92,    49,    15,    15,   -63,   -63,    25,     8,
      93,    25,    25,   -63,     8,     8,   -63,   112,   108,   -63,
      28,   -63,   100,   -63,   102,   113,    99,   107,   109,    93,
      25,   -63,   115,   112,   -63,   -63,   -63,   -63,   117,   -63,
     110,    25,   -63
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -63,   101,    -9,   -63,   -63,    37,   -62,   -28,   -63,   -63,
     -48,   111,    -6,    43,    44
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      28,    53,    30,    56,    24,    38,    79,    26,    69,    82,
      83,     1,     2,     1,     2,     3,    27,     5,     4,     5,
      52,    29,    81,    54,     6,    54,     6,    70,    97,     8,
       7,     8,    47,    48,     9,    10,    11,    63,    12,   102,
      13,    96,    73,    45,    46,     2,    84,    85,    38,    27,
      37,    43,    31,     1,     2,     3,    32,    89,     4,     5,
      45,    46,     8,    80,    45,    46,     6,    34,    54,    54,
       7,     8,    45,    46,     9,    10,    11,    76,    12,    55,
      13,     1,     2,     3,    77,    35,     4,     5,    64,    65,
      36,    66,    67,    39,     6,    40,    41,    42,     7,     8,
      43,    50,     9,    10,    11,    58,    12,    44,    13,    45,
      46,    49,    59,    68,    61,    62,    75,    71,    72,    74,
      86,    78,    88,    90,    91,   100,    92,    98,    93,    94,
      99,    95,   101,    57,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    60
};

static const yytype_int8 yycheck[] =
{
       6,    29,     8,    31,    27,    14,    68,    10,    10,    71,
      72,     3,     4,     3,     4,     5,     8,     9,     8,     9,
      26,    21,    70,    29,    16,    31,    16,    29,    90,    21,
      20,    21,    17,    18,    24,    25,    26,    43,    28,   101,
      30,    89,    32,    15,    16,     4,    74,    75,    57,     8,
       0,     6,    21,     3,     4,     5,    31,    29,     8,     9,
      15,    16,    21,    69,    15,    16,    16,    21,    74,    75,
      20,    21,    15,    16,    24,    25,    26,    22,    28,    22,
      30,     3,     4,     5,    29,    21,     8,     9,    45,    46,
      21,    47,    48,    13,    16,    13,    13,    13,    20,    21,
       6,     8,    24,    25,    26,    24,    28,    13,    30,    15,
      16,    21,     8,    22,     9,     9,    13,    22,    22,    21,
       8,    29,    14,    23,    22,     8,    13,    12,    29,    22,
      93,    22,    22,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     8,     9,    16,    20,    21,    24,
      25,    26,    28,    30,    34,    35,    36,    37,    40,    41,
      44,    45,    46,    47,    27,    42,    10,     8,    45,    21,
      45,    21,    31,    39,    21,    21,    21,     0,    35,    13,
      13,    13,    13,     6,    13,    15,    16,    17,    18,    21,
       8,    43,    45,    40,    45,    22,    40,    34,    24,     8,
      44,     9,     9,    45,    46,    46,    47,    47,    22,    10,
      29,    22,    22,    32,    21,    13,    22,    29,    29,    39,
      45,    43,    39,    39,    40,    40,     8,    38,    14,    29,
      23,    22,    13,    29,    22,    22,    43,    39,    12,    38,
       8,    22,    39
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 10:

/* Line 1455 of yacc.c  */
#line 313 "sintactico.y"
    { add_syntax_token("FUNCION"); ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 314 "sintactico.y"
    { add_syntax_token("FUNCION"); ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 315 "sintactico.y"
    { add_syntax_token("FUNCION"); ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 316 "sintactico.y"
    { add_syntax_token("FUNCION"); ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 317 "sintactico.y"
    { add_syntax_token("FUNCION"); ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 318 "sintactico.y"
    { add_syntax_token("MAIN"); ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 321 "sintactico.y"
    { add_syntax_token("INSTRUCCION"); ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 322 "sintactico.y"
    { add_syntax_token("INSTRUCCION"); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 323 "sintactico.y"
    { add_syntax_token("INSTRUCCION"); ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 330 "sintactico.y"
    { add_syntax_token("BLOQUE"); ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 333 "sintactico.y"
    { add_syntax_token("COMPARACION"); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 337 "sintactico.y"
    { tipo_dato_global = strdup((yyvsp[(1) - (1)].str)); ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 342 "sintactico.y"
    { agregar_simbolo(tipo_dato_global, (yyvsp[(1) - (1)].str), NULL); ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 343 "sintactico.y"
    {agregar_simbolo(tipo_dato_global, (yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].str)); ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 344 "sintactico.y"
    { agregar_simbolo(tipo_dato_global, (yyvsp[(1) - (3)].str), NULL); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 345 "sintactico.y"
    { agregar_simbolo(tipo_dato_global, (yyvsp[(1) - (5)].str),(yyvsp[(3) - (5)].str)); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 348 "sintactico.y"
    {   agregar_valor((yyvsp[(1) - (3)].str),(yyvsp[(3) - (3)].str));;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 350 "sintactico.y"
    { char* str = malloc(30); 
                   sprintf(str, "%f", atof((yyvsp[(1) - (3)].str)) + (yyvsp[(3) - (3)].entero)); 
                   (yyval.str) = str; 
                   add_syntax_token("SUMA"); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 354 "sintactico.y"
    { char* str = malloc(30); 
                   sprintf(str, "%f", atof((yyvsp[(1) - (3)].str)) - (yyvsp[(3) - (3)].entero)); 
                   (yyval.str) = str; 
                   add_syntax_token("RESTA"); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 358 "sintactico.y"
    { char* str = malloc(30); 
                        sprintf(str, "%f", -atof((yyvsp[(2) - (2)].str))); 
                        (yyval.str) = str;  
                        add_syntax_token("NEGATIVO"); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 362 "sintactico.y"
    { char* str = malloc(12); 
                                   sprintf(str, "%f", (yyvsp[(1) - (1)].entero)); 
                                   (yyval.str) = str;  ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 365 "sintactico.y"
    {char* str = malloc(strlen((yyvsp[(1) - (1)].str)) + 3); 
            sprintf(str, "'%s'", (yyvsp[(1) - (1)].str)); 
            (yyval.str) = str; 
            add_syntax_token("CONST_CADENA");;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 369 "sintactico.y"
    { yyerror("Error sintactico: caracter no reconocido"); YYERROR; ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 372 "sintactico.y"
    { (yyval.entero) = (yyvsp[(1) - (3)].entero) * (yyvsp[(3) - (3)].entero); add_syntax_token("MULTIPLICACION"); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 373 "sintactico.y"
    { (yyval.entero) = (yyvsp[(1) - (3)].entero) / (yyvsp[(3) - (3)].entero); add_syntax_token("DIVISION"); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 374 "sintactico.y"
    { (yyval.entero) = (yyvsp[(1) - (1)].entero); ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 378 "sintactico.y"
    {(yyval.entero) = (yyvsp[(1) - (1)].entero); add_syntax_token("NUMERO");;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 379 "sintactico.y"
    {(yyval.entero) = atof(buscar_valor((yyvsp[(1) - (1)].str))); add_syntax_token("IDENTIFICADOR");;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 380 "sintactico.y"
    {(yyval.entero) = atof((yyvsp[(2) - (3)].str)); add_syntax_token("BLOQUE");;}
    break;



/* Line 1455 of yacc.c  */
#line 1900 "sintactico.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 382 "sintactico.y"

