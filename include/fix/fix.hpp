#pragma once

/* common library */
#include <inttypes.h>
#include <string>
#include <math.h>

/* class */
#include <expression/ArithmeticExpression.hpp>
#include <expression/LogicalExpression.hpp>
// #include <expression/ConstantExpression.hpp>
#include <expression/CallExpression.hpp>
#include <expression/Scalar.hpp>
#include <expression/VarInstance.hpp>
#include <expression/SingletonInstance.hpp>
#include <expression/VectorInstance.hpp>

#define REGISTER_1 std::string("__register1__")
#define REGISTER_2 std::string("__register2__")
#define REGISTER_3 std::string("__register3__")
#define REGISTER_4 std::string("__register4__")
#define REGISTER_5 std::string("__register5__")

/* Primitives */
inline int ufp0(double);
inline int ufp1(double );
inline int ufp(double);

inline int ulp(int, int);

/* Same Format */
inline int ufp_add_same_format(int);
inline int ulp_add_same_format(int);

inline int ufp_mult_same_format(int, int);
inline int ulp_mult_same_format(int, int);

inline int ufp_shift_right(int, int);
inline int ulp_shift_right(int, int);

inline int ufp_shift_left(int, int);
inline int ulp_shift_left(int,int);

inline int ufp_and_same_format(int);
inline int ulp_and_same_format(int);

inline int ufp_or_same_format(int);
inline int ulp_or_same_format(int);

inline int ufp_xor_same_format(int);
inline int ulp_xor_same_format(int);

/* Different Format */
inline int ufp_add_different_format(int, int);
inline int ulp_add_different_format(int, int);

inline int ufp_mult_different_format(int, int, int, int);
inline int ulp_mult_different_format(int, int);

inline int ufp_and_different_format(int, int);
inline int ulp_and_different_format(int, int);

inline int ufp_or_different_format(int, int);
inline int ulp_or_different_format(int, int);

inline int ufp_xor_different_format(int, int);
inline int ulp_xor_different_format(int, int);

/* Int Add */
inline int16_t add_16(int16_t, int16_t);
inline int32_t add_32(int32_t, int32_t);
inline int64_t add_64(int64_t, int64_t);

/* Int Mul */
inline int16_t mul_16(int16_t, int16_t);
inline int32_t mul_32(int32_t, int32_t);
inline int64_t mul_64(int64_t, int64_t);

/* Fixed-point Representation */
struct FIX
{
    int32_t value;
    struct FORMAT
    {
        int32_t ufp;
        int32_t ulp;
        int32_t length;
    }format;
};
typedef struct FIX FIX;

/* Conditionnal Generation Function */
std::string FPGen_condition(LogicalExpression *);
std::string FPGen_assignment(int, VarInstance *, Expression *);
std::string FPGen_ArithmeticExpression(int, VarInstance*, ArithmeticExpression*);
std::string FPGen_CallExpression(int, VarInstance*, CallExpression*);

/* Common Generation Function */
std::string FPGen_Scalar(int, VarInstance*, Scalar*);
std::string FPGen_SingletonInstance(int, VarInstance*, SingletonInstance*);
std::string FPGen_VectorInstance(int, VarInstance*, VectorInstance*);

/* Class Test */
bool FPGen_is_ArithmeticExpression(Expression *);
bool FPGen_is_LogicalExpression(Expression *);
bool FPGen_is_ConstantExpression(Expression *);
bool FPGen_is_CallExpression(Expression *);
bool FPGen_is_Scalar(Expression *);
bool FPGen_is_SingletonInstance(Expression *);
bool FPGen_is_VectorInstance(Expression *);

/* Conversion */
double FPGen_FIX_to_float(FIX);
FIX FPGen_float_to_FIX(double, int, int);
FIX FPGen_Expression_to_FIX(Expression *);

/* Shift */
std::string FPGen_shift_operator(int, int);
int FPGen_shift_offset(int, int);
std::string FPGen_shift(int, int, int, std::string, std::string);

/* Arithmetic Operation */
FIX Add(FIX, FIX, int);
FIX Add(FIX, FIX, int, int);
FIX Sub(FIX, FIX, int);
FIX Sub(FIX, FIX, int, int);
FIX Mul(FIX, FIX, int);
FIX Mul(FIX, FIX, int, int);
FIX Div(FIX, FIX, int);
FIX Div(FIX, FIX, int, int);

/* Boolean Operation */
bool And();     /* unimplemented for now */
bool Or();      /* unimplemented for now */
bool Xor();     /* unimplemented for now */

bool Eq();
bool Neq();
bool Less();
bool Leq();
bool Great();
bool Geq();

bool Neg();     /* unimplemented for now */

/* Call */
FIX Abs(FIX, int, int);      /* unimplemented for now */
FIX Sqrt(FIX, int, int);      /* unimplemented for now */
FIX Sin(FIX, int, int);       /* unimplemented for now */
FIX Cos(FIX, int, int);       /* unimplemented for now */
FIX Atan(FIX, int, int);      /* unimplemented for now */

/* Arithmetic Operation Generation */
std::string FPGen_Add(int, FIX, FIX, int, int, std::string, std::string, std::string);
std::string FPGen_Add(int, int, std::string, std::string, std::string);

std::string FPGen_Sub(int, FIX, FIX, int, int, std::string, std::string, std::string);
std::string FPGen_Sub(int, int, std::string, std::string, std::string);

std::string FPGen_Mul(int, FIX, FIX, int, int, std::string, std::string, std::string);
std::string FPGen_Mul(int, int, std::string, std::string, std::string);

std::string FPGen_Div(int, FIX, FIX, int, int, std::string, std::string, std::string);
std::string FPGen_Div(int, int, std::string, std::string, std::string);

/* Boolean Operation Generation */

std::string FPGen_And();     /* unimplemented for now */
std::string FPGen_Or();      /* unimplemented for now */
std::string FPGen_Xor();     /* unimplemented for now */

std::string FPGen_Eq();
std::string FPGen_Neq();
std::string FPGen_Less();
std::string FPGen_Leq();
std::string FPGen_Great();
std::string FPGen_Geq();

std::string FPGen_Neg();     /* unimplemented for now */

/* Call Generation */
std::string FPGen_Abs(int, FIX, int, int, std::string, std::string);
std::string FPGen_Sqrt(int, FIX, int, int, std::string, std::string);
std::string FPGen_Sin(int, FIX, int, int, std::string, std::string);
std::string FPGen_Cos(int, FIX, int, int, std::string, std::string);
std::string FPGen_Atan(int, FIX, int, int, std::string, std::string);