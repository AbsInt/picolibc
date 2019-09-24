#define HAVE_FLOAT 1
#define X(x) (char *)x

#include <math.h>
#include <float.h>
//#include <ieeefp.h>
#include <stdio.h>
#include <stdint.h>

/* FIXME FIXME FIXME:
   Neither of __ieee_{float,double}_shape_type seem to be used anywhere
   except in libm/test.  If that is the case, please delete these from here.
   If that is not the case, please insert documentation here describing why
   they're needed.  */

#ifdef __IEEE_BIG_ENDIAN

typedef union 
{
  double value;
  struct 
  {
    unsigned int sign : 1;
    unsigned int exponent: 11;
    unsigned int fraction0:4;
    unsigned int fraction1:16;
    unsigned int fraction2:16;
    unsigned int fraction3:16;
    
  } number;
  struct 
  {
    unsigned int sign : 1;
    unsigned int exponent: 11;
    unsigned int quiet:1;
    unsigned int function0:3;
    unsigned int function1:16;
    unsigned int function2:16;
    unsigned int function3:16;
  } nan;
  struct 
  {
    uint32_t msw;
    uint32_t lsw;
  } parts;
    int32_t aslong[2];
} __ieee_double_shape_type;

#else

typedef union 
{
  double value;
  struct 
  {
#ifdef __SMALL_BITFIELDS
    unsigned int fraction3:16;
    unsigned int fraction2:16;
    unsigned int fraction1:16;
    unsigned int fraction0: 4;
#else
    unsigned int fraction1:32;
    unsigned int fraction0:20;
#endif
    unsigned int exponent :11;
    unsigned int sign     : 1;
  } number;
  struct 
  {
#ifdef __SMALL_BITFIELDS
    unsigned int function3:16;
    unsigned int function2:16;
    unsigned int function1:16;
    unsigned int function0:3;
#else
    unsigned int function1:32;
    unsigned int function0:19;
#endif
    unsigned int quiet:1;
    unsigned int exponent: 11;
    unsigned int sign : 1;
  } nan;
  struct 
  {
    uint32_t lsw;
    uint32_t msw;
  } parts;

  int32_t aslong[2];

} __ieee_double_shape_type;

#endif /* __IEEE_LITTLE_ENDIAN */

#ifdef __IEEE_BIG_ENDIAN

typedef union
{
  float value;
  struct 
  {
    unsigned int sign : 1;
    unsigned int exponent: 8;
    unsigned int fraction0: 7;
    unsigned int fraction1: 16;
  } number;
  struct 
  {
    unsigned int sign:1;
    unsigned int exponent:8;
    unsigned int quiet:1;
    unsigned int function0:6;
    unsigned int function1:16;
  } nan;
  int32_t p1;
  
} __ieee_float_shape_type;

#else

typedef union
{
  float value;
  struct 
  {
    unsigned int fraction0: 7;
    unsigned int fraction1: 16;
    unsigned int exponent: 8;
    unsigned int sign : 1;
  } number;
  struct 
  {
    unsigned int function1:16;
    unsigned int function0:6;
    unsigned int quiet:1;
    unsigned int exponent:8;
    unsigned int sign:1;
  } nan;
  int32_t p1;
  
} __ieee_float_shape_type;

#endif /* __IEEE_LITTLE_ENDIAN */

void checkf();
void enter();


double translate_from();

typedef struct 
{
  uint32_t msw, lsw;
} question_struct_type;


typedef struct 
{
  char error_bit;
  char errno_val;
  char merror;
  int line;
  
  question_struct_type qs[3];
} one_line_type;


#define MVEC_START(x) one_line_type x[] =  {
#define MVEC_END    0,};


int mag_of_error (double, double);


#define ERROR_PERFECT 20
#define ERROR_FAIL -1

#define AAAA 15
#define AAA 10
#define AA  6
#define A   5
#define B   3
#define C   1 
#define VECOPEN(x,f) \
{\
  char buffer[100];\
   sprintf(buffer,"%s_vec.c",x);\
    f = fopen(buffer,"w");\
     fprintf(f,"#include \"test.h\"\n");\
      fprintf(f," one_line_type %s_vec[] = {\n", x);\
}

#define VECCLOSE(f,name,args)\
{\
  fprintf(f,"0,};\n");      \
   fprintf(f,"test_%s(m)   {run_vector_1(m,%s_vec,(char *)(%s),\"%s\",\"%s\");   }	\n",\
	   name,\
	   name,name,name,args);\
	    fclose(f);\
}



typedef struct 
{
  int line;
  
  char *string;
  double value;
  int endscan;
} double_type;


typedef struct {
  long int value;
  char end;
  char errno_val;
} int_scan_type;

typedef struct 
{
  int line;
  int_scan_type octal;
  int_scan_type decimal;
  int_scan_type hex;
  int_scan_type normal;
  int_scan_type alphabetical;
  char *string;
} int_type;


typedef struct 
{
  int line;
  double value;
  char *estring;
  int e1;
  int e2;
  int e3;
  char *fstring;
  int f1;
  int f2;
  int f3;
  char *gstring;
  int g1;
} ddouble_type;

typedef struct
{
  int line;
  double value;
  char *result;
  char *format_string;
} sprint_double_type;


typedef struct
{
  int line;
  int value;
  char *result;
  char *format_string;
} sprint_int_type;


void test_ieee (void);
void test_math2 (void);
void test_math (int vector);
void test_string (void);
void test_is (void);
void test_cvt (void);

void line (int);

void test_mok (double, double, int);
void test_iok (int, int);
void test_eok (int, int);
void test_sok (char *, char*);
void test_scok (char *, char*, int);
void newfunc (const char *);

void
run_vector_1 (int vector,
	      one_line_type *p,
	      char *func,
	      char *name,
	      char *args);
