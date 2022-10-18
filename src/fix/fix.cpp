#include <fix/fix.hpp>

#include <Log.hpp>

#define COMMENT
// #define FULLY_INLINE

/* Primitives */
inline int ufp0(double x) {
    int i=0;
	while(x < pow(2,i))
        i--;
	return i;
}

inline int ufp1(double x) {
    int i=0;
	while(x >= pow(2,i))
		i++;
	return i-1;
}

inline int ufp(double x) {
    x=fabs(x);
	if(!x)
        return 0;
	else
        return (x >= 1.0) ? ufp1(x) : ufp0(x);
}

inline int ulp(int ufp, int length) {
    return ufp - length + 1;
}

/* Same Format */
inline int ufp_add_same_format(int ufp1){ return ufp1; }
inline int ulp_add_same_format(int ulp1){ return ulp1; }

inline int ufp_mult_same_format(int ufp1, int ulp1){ return ufp1 - ulp1; }
inline int ulp_mult_same_format(int ulp1){ return 2 * ulp1; }

inline int ufp_shift_right(int ufp, int k){ return ufp + k; }
inline int ulp_shift_right(int ulp, int k){ return ulp - k; }

inline int ufp_shift_left(int ufp, int k){ return ufp - k; }
inline int ulp_shift_left(int ulp, int k){ return ulp + k; }

inline int ufp_and_same_format(int ufp1){ return ufp1; }
inline int ulp_and_same_format(int ulp1){ return ulp1; }

inline int ufp_or_same_format(int ufp1){ return ufp1; }
inline int ulp_or_same_format(int ulp1){ return ulp1; }

inline int ufp_xor_same_format(int ufp1){ return ufp1; }
inline int ulp_xor_same_format(int ulp1){ return ulp1; }

/* Different Format */
inline int ufp_add_different_format(int ufp1, int ufp2) { return 1 + ( ( ufp1 >= ufp2 ) ? ufp1 : ufp2 ); }
inline int ulp_add_different_format(int ufp, int length) { return length - ufp; }

inline int ufp_mult_different_format(int ufp1, int ulp1, int ufp2, int ulp2){ return ufp1 + ufp2 + 1; }
inline int ulp_mult_different_format(int ufp, int length) { return length - ufp; }

inline int ufp_and_different_format(int ufp1, int ufp2) { return ( (ufp1 >= ufp2) ? ufp1 : ufp2 );	}
inline int ulp_and_different_format(int ufp, int length) { return length - ufp ; }

inline int ufp_or_different_format(int ufp1, int ufp2) { return ( (ufp1 >= ufp2) ? ufp1 : ufp2 );	}
inline int ulp_or_different_format(int ufp, int length) { return length - ufp; }

inline int ufp_xor_different_format(int ufp1, int ufp2) { return ( ( ufp1 >= ufp2) ? ufp1 : ufp2 );	}
inline int ulp_xor_different_format(int ufp, int length) { return length - ufp; }

/* Int Add */
inline int16_t add_16(int16_t a, int16_t b){ return a+b;}
inline int32_t add_32(int32_t a, int32_t b){ return a+b;}
inline int64_t add_64(int64_t a, int64_t b){ return a+b;}

/* Int Mul */
inline int16_t mul_16(int16_t a,int16_t b){ return a*b;}
inline int32_t mul_32(int32_t a,int32_t b){ return a*b;}
inline int64_t mul_64(int64_t a,int64_t b){ return a*b;}

/* Conditionnal Generation Function */
std::string FPGen_condition(LogicalExpression *condition) {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */";
}

std::string FPGen_assignment(int depth, VarInstance *var, Expression *expr) {
	std::string result;

	if(FPGen_is_LogicalExpression(expr))
	{
		g_LogConsole->write(LogLevel::ERROR, "Can't generate LogicalExpression assignment");
		result = std::string(depth, '\t') + "/* Can't generate LogicalExpression assignment */" + '\n';
	}
	else if(FPGen_is_ArithmeticExpression(expr))
	{
		result = FPGen_ArithmeticExpression(depth, var, (ArithmeticExpression *) expr);
	}
	else if(FPGen_is_CallExpression(expr))
	{
		result = FPGen_CallExpression(depth, var, (CallExpression *) expr);
	}
	else if(FPGen_is_Scalar(expr))
	{
		result = FPGen_Scalar(depth, var, (Scalar *) expr);
	}
	else if(FPGen_is_SingletonInstance(expr))
	{
		result = FPGen_SingletonInstance(depth, var, (SingletonInstance *) expr);
	}
	else if(FPGen_is_VectorInstance(expr))
	{
		result = FPGen_VectorInstance(depth, var, (VectorInstance *) expr);
	}
	else
	{
		result = std::string(depth, '\t') + "/* Unknown Assignment */" + '\n';
	}

	return result;
}
std::string FPGen_ArithmeticExpression(int depth, VarInstance* var, ArithmeticExpression* expr) {
	std::string result;
	
	Expression * operand1 = expr->GetOperand1();
	Expression * operand2 = expr->GetOperand2();

	int result_ufp = expr->GetUfp();
	int result_length = expr->GetLength();

	std::string result_name = var->ToStringFloat(0);
	std::string operand1_name = operand1->ToStringFixExtended(0);
	std::string operand2_name = operand2->ToStringFixExtended(0);

	if(FPGen_is_ArithmeticExpression(operand1) || FPGen_is_ArithmeticExpression(operand2)) {
		g_LogConsole->write(LogLevel::ERROR, LogError::COMPOSED_EXPRESSION, operand1->m_lineno, "FPGen_ArithmeticExpression");
		result = std::string(depth, '\t') + "/* Can't handle composed expr */" + '\n';
		return result;
	}

	if(FPGen_is_CallExpression(operand1) || FPGen_is_CallExpression(operand2)) {
		g_LogConsole->write(LogLevel::ERROR, LogError::COMPOSED_EXPRESSION, operand1->m_lineno, "FPGen_ArithmeticExpression");
		result = std::string(depth, '\t') + "/* Can't handle function inside binary expr (can only handle unary expression in this case) */" + '\n';
		return result;
	}

	FIX operand1_fix = FPGen_Expression_to_FIX(operand1);
	FIX operand2_fix = FPGen_Expression_to_FIX(operand2);

	switch (expr->GetOp()) {
	case ArithmeticExpression::Operation::PLUS:
		result = FPGen_Add(depth, operand1_fix, operand2_fix, result_ufp, result_length, result_name, operand1_name, operand2_name);
		break;

	case ArithmeticExpression::Operation::MINUS:
		result = FPGen_Sub(depth, operand1_fix, operand2_fix, result_ufp, result_length, result_name, operand1_name, operand2_name);
		break;

	case ArithmeticExpression::Operation::TIMES:
		result = FPGen_Mul(depth, operand1_fix, operand2_fix, result_ufp, result_length, result_name, operand1_name, operand2_name);
		break;

	case ArithmeticExpression::Operation::DIVIDE:
		result = FPGen_Div(depth, operand1_fix, operand2_fix, result_ufp, result_length, result_name, operand1_name, operand2_name);
		break;
	
	default:
		result = std::string(depth, '\t') + "/* Unknown ArithmeticExpression */" + ";\n";
		break;
	}
	
	return result;
}

std::string FPGen_CallExpression(int depth, VarInstance * var, CallExpression * call) {
	std::string result;

	Expression *arg = call->GetArg();

	FIX arg_fix = FPGen_Expression_to_FIX(arg);
	std::string arg_name = arg->ToStringFloat(0);

	int result_ufp = call->GetUfp();
	int result_length = call->GetLength();
	std::string result_name = var->ToStringFloat(0);

	// arg is ConstantExpression ?
		// arg is CallExpression ? -> X
		//
	// else -> X

	if(FPGen_is_ConstantExpression(arg))
	{
		if(FPGen_is_CallExpression(arg))
		{
			g_LogConsole->write(LogLevel::ERROR, LogError::COMPOSED_CALL_EXPRESSION, arg->m_lineno, "FPGen_CallExpression");
			result = std::string(depth, '\t') + "/* Can't handle composed call expr */" + '\n';
			return result;	
		}
	}
	else
	{
		g_LogConsole->write(LogLevel::ERROR, LogError::COMPOSED_CALL_EXPRESSION, arg->m_lineno, "FPGen_CallExpression");
		result = std::string(depth, '\t') + "/* Can't handle composed call expr */" + '\n';
		return result;
	}

	switch (call->GetCallType()) {
	case CallExpression::CallExpressionType::ABS:
		result = FPGen_Abs(depth, arg_fix, result_ufp, result_length, result_name, arg_name);
		break;

	case CallExpression::CallExpressionType::SQRT:
		result = FPGen_Sqrt(depth, arg_fix, result_ufp, result_length, result_name, arg_name);
		break;

	case CallExpression::CallExpressionType::SIN:
		result = FPGen_Sin(depth, arg_fix, result_ufp, result_length, result_name, arg_name);
		break;

	case CallExpression::CallExpressionType::COS:
		result = FPGen_Cos(depth, arg_fix, result_ufp, result_length, result_name, arg_name);
		break;

	case CallExpression::CallExpressionType::ATAN:
		result = FPGen_Atan(depth, arg_fix, result_ufp, result_length, result_name, arg_name);
		break;
	
	default:
		result = std::string(depth, '\t') + "CallExpression" + ";\n";
		break;
	}

	return result;
}

/* Common Generation Function */
std::string FPGen_Scalar(int depth, VarInstance *var, Scalar *scalar) {
	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	// return std::string(depth, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
	return std::string(depth, '\t') + var->ToStringFixExtended(0) + " = " + scalar->ToStringFixExtended(0) + ";\n";
}

std::string FPGen_SingletonInstance(int depth, VarInstance *var, SingletonInstance *singleton) {
	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	// return std::string(depth, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
	return std::string(depth, '\t') + var->ToStringFixExtended(0) + " = " + singleton->ToStringFixExtended(0) + ";\n";
}

std::string FPGen_VectorInstance(int depth, VarInstance *var, VectorInstance *vector) {
	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	// return std::string(depth, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
	return std::string(depth, '\t') + var->ToStringFixExtended(0) + " = " + vector->ToStringFixExtended(0) + ";\n";
}

/* Class Test */
bool FPGen_is_ArithmeticExpression(Expression * expr) {
	return dynamic_cast <ArithmeticExpression*> (expr) != nullptr;
}

bool FPGen_is_LogicalExpression(Expression * expr) {
	return dynamic_cast <LogicalExpression*> (expr) != nullptr;
}

bool FPGen_is_ConstantExpression(Expression * expr) {
	return dynamic_cast <ConstantExpression*> (expr) != nullptr;
}

bool FPGen_is_CallExpression(Expression * expr) {
	return dynamic_cast <CallExpression*> (expr) != nullptr;
}

bool FPGen_is_Scalar(Expression * expr) {
	return dynamic_cast <Scalar*> (expr) != nullptr;
}

bool FPGen_is_SingletonInstance(Expression * expr) {
	return dynamic_cast <SingletonInstance*> (expr) != nullptr;
}

bool FPGen_is_VectorInstance(Expression * expr) {
	return dynamic_cast <VectorInstance*> (expr) != nullptr;
}

/* Conversion */
double FPGen_FIX_to_float(FIX x) {
	return x.value * pow(2, (-x.format.ulp));
}

FIX FPGen_float_to_FIX(double x, int ufp, int length) {
	FIX result;
    result.format.ufp = ufp;
    result.format.ulp = (ufp == length) ? 1 : length - abs(ufp);
	double v = x / pow(2, ( -1 * result.format.ulp));
	result.value = (int) round(v);
	return result;
}

FIX FPGen_Expression_to_FIX(Expression *expr) {
	FIX result;

	double value = expr->GetEvaluatedValue();

	result.format.ufp = expr->GetUfp();
	result.format.ulp = expr->GetUlp();
	result.format.length = expr->GetLength();
	result.value = (int) round( value / ( pow(2, (result.format.ulp) ) ) );

	g_LogConsole->write(LogLevel::INFO, std::to_string(value) + " -> " + std::to_string(result.value) + " <" + std::to_string(result.format.ufp) + ", " + std::to_string(result.format.ulp) + ", " + std::to_string(result.format.length) + "> at line " + std::to_string(expr->m_lineno) );

	return result;
}

/* Shift */
std::string FPGen_shift_operator(int result_ulp, int operand_ulp) {
	return (operand_ulp <= result_ulp) ? " << " : " >> ";
}

int FPGen_shift_offset(int result_ulp, int operand_ulp) {
	return abs(-result_ulp + operand_ulp);
}

std::string FPGen_shift(int depth, int result_ulp, int operand_ulp, std::string result_name, std::string operand_name) {
	std::string op = FPGen_shift_operator(result_ulp, operand_ulp);
	std::string offset = std::to_string(FPGen_shift_offset(result_ulp, operand_ulp));
	std::string comment = " // " + std::to_string(operand_ulp) + " -> " + std::to_string(result_ulp);

	#ifdef COMMENT
		return std::string(depth, '\t') + result_name + " = " + operand_name + op + offset + ';' + comment + '\n';
	#else
		return std::string(depth, '\t') + result_name + " = " + operand_name + op + offset + ';' + '\n';
	#endif
}

/* Arithmetic Operation */
FIX Add(FIX x1, FIX x2, int result_length) {
	FIX result;

	result.format.ufp = ufp_add_different_format(x1.format.ufp, x2.format.ufp);
	result.format.ulp = ulp_add_different_format(result.format.ufp, result_length);
	result.format.length = result_length;
	x1.value = ( x1.format.ulp < result.format.ulp ) ? x1.value << abs(result.format.ulp - x1.format.ulp) : x1.value >> abs(result.format.ulp - x1.format.ulp);
	x2.value = ( x2.format.ulp < result.format.ulp ) ? x2.value << abs(result.format.ulp - x2.format.ulp) : x2.value >> abs(result.format.ulp - x2.format.ulp);
	result.value = x1.value + x2.value;

	return result;
}

FIX Add(FIX x1, FIX x2, int result_ufp, int result_length) {
	FIX result;

	result.format.ufp = result_ufp;
	result.format.ulp = ulp(result_ufp, result_length);
	result.format.length = result_length;
	x1.value = ( x1.format.ulp < result.format.ulp ) ? x1.value << abs(result.format.ulp - x1.format.ulp) : x1.value >> abs(result.format.ulp - x1.format.ulp);
	x2.value = ( x2.format.ulp < result.format.ulp ) ? x2.value << abs(result.format.ulp - x2.format.ulp) : x2.value >> abs(result.format.ulp - x2.format.ulp);
	result.value = x1.value + x2.value;

	return result;
}

/** @todo verify result.format.ulp */
FIX Sub(FIX x1, FIX x2, int result_length) {
	FIX result;
	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);

	result.format.ufp = ufp_add_different_format(x1.format.ufp, x2.format.ufp);
	result.format.ulp = ulp_add_different_format(result.format.ufp, result_length);
	result.format.length = result_length;
	x1.value = ( x1.format.ulp < result.format.ulp ) ? x1.value << abs(result.format.ulp - x1.format.ulp) : x1.value >> abs(result.format.ulp - x1.format.ulp);
	x2.value = ( x2.format.ulp < result.format.ulp ) ? x2.value << abs(result.format.ulp - x2.format.ulp) : x2.value >> abs(result.format.ulp - x2.format.ulp);
	result.value = x1.value + x2.value;
	
	return result;
}

FIX Sub(FIX x1, FIX x2, int result_ufp, int result_length) {
	FIX result;
	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);

	result.format.ufp = result_ufp;
	result.format.ulp = ulp(result_ufp, result_length);
	result.format.length = result_length;
	x1.value = ( x1.format.ulp < result.format.ulp ) ? x1.value << abs(result.format.ulp - x1.format.ulp) : x1.value >> abs(result.format.ulp - x1.format.ulp);
	x2.value = ( x2.format.ulp < result.format.ulp ) ? x2.value << abs(result.format.ulp - x2.format.ulp) : x2.value >> abs(result.format.ulp - x2.format.ulp);
	result.value = x1.value - x2.value;

	return result;
}

FIX Mul(FIX x1, FIX x2, int result_length) {
	FIX result;
	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);

	result.format.ufp = ufp_mult_different_format(x1.format.ufp, x1.format.ulp, x2.format.ufp, x2.format.ulp);
	result.format.ulp = ulp_mult_different_format(result.format.ufp, result_length);
	result.format.length = result_length;
	result.value = 0;

	return result;
}

FIX Mul(FIX x1, FIX x2, int result_ufp, int result_length) {
	FIX result;
	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);

	result.value = 0;
	result.format.ufp = result_ufp;
	result.format.ulp = ulp(result_ufp, result_length);
	result.format.length = result_length;

	return result;
}

FIX Div(FIX x1, FIX x2, int result_length) {
	FIX result;
	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);

	result.value = 0;
	result.format.ufp = 0;
	result.format.ulp = 0;
	result.format.length = 0;

	return result;
}

FIX Div(FIX x1, FIX x2, int result_ufp, int result_length) {
	FIX result;
	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);

	result.value = 0;
	result.format.ufp = result_ufp;
	result.format.ulp = ulp(result_ufp, result_length);
	result.format.length = result_length;

	return result;
}

/* Boolean Operation */
bool And() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}     

bool Or() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}      

bool Xor() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}     

bool Eq() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}

bool Neq() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}

bool Less() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}

bool Leq() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}

bool Great() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}

bool Geq() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}

bool Neg() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return false;
}

/* Call */

FIX Abs(FIX arg, int result_ufp, int result_length) {
	FIX result;
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return result;
}

FIX Sqrt(FIX arg, int result_ufp, int result_length) {
	FIX result;
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return result;
}

FIX Sin(FIX arg, int result_ufp, int result_length) {
	FIX result;
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return result;
}

FIX Cos(FIX arg, int result_ufp, int result_length) {
	FIX result;
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return result;
}

FIX Atan(FIX arg, int result_ufp, int result_length) {
	FIX result;
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return result;
}

/* Arithmetic Operation Generation */
std::string FPGen_arithmetic_comment(int result_ufp, int result_length, std::string op, int op1_ufp, int op1_length, int op2_ufp, int op2_length) {
	return " // <" + std::to_string(result_ufp) + ", " + std::to_string(result_length) + 
			  "> = <" + std::to_string(op1_ufp) + ", " + std::to_string(op1_length) +
			  "> "+ op +" <" + std::to_string(op2_ufp) + ", " + std::to_string(op2_length) + ">";
}

std::string FPGen_Add(int depth, FIX x1, FIX x2, int result_ufp, int result_length, std::string result_name, std::string x1_name, std::string x2_name) {
	std::string shift_op1, shift_op2, op, comment;

	shift_op1 = FPGen_shift(depth, ulp(result_ufp, result_length), x1.format.ulp, REGISTER_1, x1_name);
	shift_op2 = FPGen_shift(depth, ulp(result_ufp, result_length), x2.format.ulp, REGISTER_2, x2_name);
	op = std::string(depth, '\t') + result_name + " = " + REGISTER_1 + " + " + REGISTER_2 + ';';
	comment = FPGen_arithmetic_comment(result_ufp, result_length, "+", x1.format.ufp, x1.format.length, x2.format.ufp, x2.format.length);

	#ifdef COMMENT
		return shift_op1 + shift_op2 + op + comment + '\n' + '\n';
	#else
		return shift_op1 + shift_op2 + op + '\n' + '\n';
	#endif
}

std::string FPGen_Add(int depth, int result_length, std::string result_name, std::string x1_name, std::string x2_name) {
	std::string shift_op1, shift_op2, op, comment;

	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);

	shift_op1 = std::string(depth, '\t') + "/* result_ufp calculation */" + '\n' +
				std::string(depth, '\t') + "/* result_ulp calculation */" + '\n' +
				std::string(depth, '\t') + "/* result_length calculation */" + '\n' +
				std::string(depth, '\t') + REGISTER_1 + " = (" + "__CONDITION__" + ") ? " + REGISTER_1 + " << " + "__offset__" + " : " + REGISTER_1 + " >> " + "__offset__" + ";"  + '\n';
	shift_op2 = std::string(depth, '\t') + REGISTER_2 + " = (" + "__CONDITION__" + ") ? " + REGISTER_2 + " << " + "__offset__" + " : " + REGISTER_2 + " >> " + "__offset__" + ";"  + '\n';
	op = std::string(depth, '\t') + result_name + " = " + REGISTER_1 + " + " + REGISTER_2 + ';';
	comment = " // comment";

	
	// shift_op1 = FPGen_shift(depth, ulp(result_ufp, result_length), x1.format.ulp, REGISTER_1, x1_name);
	// shift_op2 = FPGen_shift(depth, ulp(result_ufp, result_length), x2.format.ulp, REGISTER_2, x2_name);
	// op = std::string(depth, '\t') + result_name + " = " + REGISTER_1 + " + " + REGISTER_2 + ';';
	// comment = FPGen_arithmetic_comment(result_ufp, result_length, "+", x1.format.ufp, x1.format.length, x2.format.ufp, x2.format.length);

	#ifdef COMMENT
		return shift_op1 + shift_op2 + op + comment + '\n' + '\n';
	#else
		return shift_op1 + shift_op2 + op + '\n' + '\n';
	#endif
}

std::string FPGen_Sub(int depth, FIX x1, FIX x2, int result_ufp, int result_length, std::string result_name, std::string x1_name, std::string x2_name) {
	std::string shift_op1, shift_op2, op, comment;

	shift_op1 = FPGen_shift(depth, ulp(result_ufp, result_length), x1.format.ulp, REGISTER_1, x1_name);
	shift_op2 = FPGen_shift(depth, ulp(result_ufp, result_length), x2.format.ulp, REGISTER_2, x2_name);
	op = std::string(depth, '\t') + result_name + " = " + REGISTER_1 + " - " + REGISTER_2 + ';';
	comment = FPGen_arithmetic_comment(result_ufp, result_length, "-", x1.format.ufp, x1.format.length, x2.format.ufp, x2.format.length);

	#ifdef COMMENT
		return shift_op1 + shift_op2 + op + comment + '\n' + '\n';
	#else
		return shift_op1 + shift_op2 + op + '\n' + '\n';
	#endif
}

std::string FPGen_Sub(int depth, int result_length, std::string result_name, std::string x1_name, std::string x2_name) {
	std::string shift_op1, shift_op2, op, comment;

	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);

	shift_op1 = std::string(depth, '\t') + "/* result_ufp calculation */" + '\n' +
				std::string(depth, '\t') + "/* result_ulp calculation */" + '\n' +
				std::string(depth, '\t') + "/* result_length calculation */" + '\n' +
				std::string(depth, '\t') + REGISTER_1 + " = (" + "__CONDITION__" + ") ? " + REGISTER_1 + " << " + "__offset__" + " : " + REGISTER_1 + " >> " + "__offset__" + ";"  + '\n';
	shift_op2 = std::string(depth, '\t') + REGISTER_2 + " = (" + "__CONDITION__" + ") ? " + REGISTER_2 + " << " + "__offset__" + " : " + REGISTER_2 + " >> " + "__offset__" + ";"  + '\n';
	op = std::string(depth, '\t') + result_name + " = " + REGISTER_1 + " - " + REGISTER_2 + ';';
	comment = " // comment";

	// shift_op1 = FPGen_shift(depth, ulp(result_ufp, result_length), x1.format.ulp, REGISTER_1, x1_name);
	// shift_op2 = FPGen_shift(depth, ulp(result_ufp, result_length), x2.format.ulp, REGISTER_2, x2_name);
	// op = std::string(depth, '\t') + result_name + " = " + REGISTER_1 + " - " + REGISTER_2 + ';';
	// comment = FPGen_arithmetic_comment(result_ufp, result_length, "-", x1.format.ufp, x1.format.length, x2.format.ufp, x2.format.length);

	#ifdef COMMENT
		return shift_op1 + shift_op2 + op + comment + '\n' + '\n';
	#else
		return shift_op1 + shift_op2 + op + '\n' + '\n';
	#endif
}

std::string FPGen_Mul(int depth, FIX x1, FIX x2, int result_ufp, int result_length, std::string result_name, std::string x1_name, std::string x2_name) {
	std::string op, shift, affect, comment;

	int frac_len = x1.format.ulp + x2.format.ulp;

	op = std::string(depth, '\t') + REGISTER_1 + " = (int32_t) " + x1_name + " * " + x2_name + ';';
	shift = FPGen_shift(depth, ulp(result_ufp, result_length), frac_len, REGISTER_1, REGISTER_1);
	affect = std::string(depth, '\t') + result_name + " = (int32_t) " + REGISTER_1 + ';' + '\n';
	comment = FPGen_arithmetic_comment(result_ufp, result_length, "*", x1.format.ufp, x1.format.length, x2.format.ufp, x2.format.length);

	#ifdef COMMENT
		return op + comment + '\n' + shift + affect + '\n';
	#else
		return op + '\n' + shift + affect + '\n';
	#endif
}

std::string FPGen_Mul(int depth, int result_length, std::string result_name, std::string x1_name, std::string x2_name) {
	std::string op, shift, affect, comment;

	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__); // LOG

	// Op -> OK
	op = std::string(depth, '\t') + REGISTER_1 + " = (int32_t) " + x1_name + " * " + x2_name + ';';

	// Shift ->	PAS OK
	shift = std::string(depth, '\t') + "/* result_ufp calculation */" + '\n' +
			std::string(depth, '\t') + "/* result_ulp calculation */" + '\n' +
			std::string(depth, '\t') + "/* result_length calculation */" + '\n' +
			std::string(depth, '\t') + REGISTER_1 + " = (" + "__CONDITION__" + ") ? " + REGISTER_1 + " << " + "__offset__" + " : " + REGISTER_1 + " >> " + "__offset__" + ";"  + '\n';

	// Affect -> OK
	affect = std::string(depth, '\t') + result_name + " = (int32_t) " + REGISTER_1 + ';' + '\n';

	// int frac_len = x1.format.ulp + x2.format.ulp;
	

	// shift = FPGen_shift(depth, ulp(result_ufp, result_length), frac_len, REGISTER_1, REGISTER_1);
	// comment = FPGen_arithmetic_comment(result_ufp, result_length, "*", x1.format.ufp, x1.format.length, x2.format.ufp, x2.format.length);

	#ifdef COMMENT
		return op + comment + '\n' + shift + affect + '\n';
	#else
		return op + '\n' + shift + affect + '\n';
	#endif

	return std::string(depth, '\t') + "/* " + __FUNCTION__ + " */" + '\n' + '\n';
}

std::string FPGen_Div(int depth, FIX x1, FIX x2, int result_ufp, int result_length, std::string result_name, std::string x1_name, std::string x2_name) {
	std::string shift_op1, shift_op2, op, comment;

	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	
	shift_op1 = FPGen_shift(depth, ulp(result_ufp, result_length), x1.format.ulp, REGISTER_1, x1_name);
	shift_op2 = FPGen_shift(depth, ulp(result_ufp, result_length), x2.format.ulp, REGISTER_2, x2_name);
	op = std::string(depth, '\t') + result_name + " = (int) ( " + REGISTER_1 + " * ( 1 << " + std::to_string(ulp(result_ufp, result_length)) + " ) ) / " + REGISTER_2 + ';';
	comment = FPGen_arithmetic_comment(result_ufp, result_length, "/", x1.format.ufp, x1.format.length, x2.format.ufp, x2.format.length);

	#ifdef COMMENT
		return shift_op1 + shift_op2 + op + comment + '\n' + '\n';
	#else
		return shift_op1 + shift_op2 + op + '\n' + '\n';
	#endif
}

std::string FPGen_Div(int depth, int result_length, std::string result_name, std::string x1_name, std::string x2_name) {
	std::string shift_op1, shift_op2, op, comment;

	// g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	
	shift_op1 = std::string(depth, '\t') + "/* result_ufp calculation */" + '\n' +
				std::string(depth, '\t') + "/* result_ulp calculation */" + '\n' +
				std::string(depth, '\t') + "/* result_length OK */" + '\n' +
				std::string(depth, '\t') + REGISTER_1 + " = (" + "__CONDITION__" + ") ? " + REGISTER_1 + " << " + "__offset__" + " : " + REGISTER_1 + " >> " + "__offset__" + ";"  + '\n';
	shift_op2 = std::string(depth, '\t') + REGISTER_2 + " = (" + "__CONDITION__" + ") ? " + REGISTER_2 + " << " + "__offset__" + " : " + REGISTER_2 + " >> " + "__offset__" + ";"  + '\n';
	op = std::string(depth, '\t') + result_name + " = (int) ( " + REGISTER_1 + " * ( 1 << " + "result_ulp" + " ) ) / " + REGISTER_2 + ';';
	comment = " // comment";

	// shift_op1 = FPGen_shift(depth, ulp(result_ufp, result_length), x1.format.ulp, REGISTER_1, x1_name);
	// shift_op2 = FPGen_shift(depth, ulp(result_ufp, result_length), x2.format.ulp, REGISTER_2, x2_name);
	// op = std::string(depth, '\t') + result_name + " = (int) ( " + REGISTER_1 + " * ( 1 << " + std::to_string(ulp(result_ufp, result_length)) + " ) ) / " + REGISTER_2 + ';';
	// comment = FPGen_arithmetic_comment(result_ufp, result_length, "/", x1.format.ufp, x1.format.length, x2.format.ufp, x2.format.length);

	#ifdef COMMENT
		return shift_op1 + shift_op2 + op + comment + '\n' + '\n';
	#else
		return shift_op1 + shift_op2 + op + '\n' + '\n';
	#endif
}

/* Boolean Operation Generation */

std::string FPGen_And() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

std::string FPGen_Or() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

std::string FPGen_Xor() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

std::string FPGen_Eq() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

std::string FPGen_Neq() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

std::string FPGen_Less() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

std::string FPGen_Leq() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

std::string FPGen_Great() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

std::string FPGen_Geq() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

std::string FPGen_Neg() {
	g_LogConsole->write(LogLevel::ERROR, LogError::UNIMPLEMENTED, __FUNCTION__);
	return std::string(0, '\t') + "/* " + __FUNCTION__ + " */" + '\n';
}

/* Call Generation */
std::string FPGen_Abs(int depth, FIX arg, int result_ufp, int result_length, std::string result_name, std::string arg_name) {
	return std::string(depth, '\t') + result_name + " = abs(" + arg_name + ");" + '\n';
}

//
std::string FPGen_Sqrt(int depth, FIX arg, int result_ufp, int result_length, std::string result_name, std::string arg_name) {
	std::string comment_begin, comment_end;
	std::string code;
	
	comment_begin = std::string(0, '\t') + "/* " + __FUNCTION__ + " Begin */" + '\n' + '\n';
	comment_end = std::string(0, '\t') + "/* " + __FUNCTION__ + " End */" + '\n' + '\n';

	code = 	std::string(depth, '\t') + REGISTER_3 + " = ((uint32_t) " + arg_name + ") << " + std::to_string(result_length) + ";" + '\n' +
		   	std::string(depth, '\t') + REGISTER_4 + " = 0;" + '\n' +
		   	std::string(depth, '\t') + REGISTER_5 + " = 0x40000000ll;" + '\n' +
		   	std::string(depth, '\t') + "while(" + REGISTER_5 + " != 0) {" + '\n' +
		   	std::string(depth, '\t') + "	if(" + REGISTER_3 + " >= " + REGISTER_4 + " + " + REGISTER_5 + ") {" + '\n' +
		   	std::string(depth, '\t') + "		" + REGISTER_3 + " -= (" + REGISTER_4 + " + " + REGISTER_5 + ");" + '\n' +
		   	std::string(depth, '\t') + "		" + REGISTER_4 + " += " + REGISTER_5 + " << 1;" + '\n' +
		   	std::string(depth, '\t') + "	}" + '\n' +
		   	std::string(depth, '\t') + REGISTER_4 + " >>= 1;" + '\n' +
		   	std::string(depth, '\t') + REGISTER_5 + " >>= 2;" + '\n' +
		   	std::string(depth, '\t') + "}" + '\n' +
		   	std::string(depth, '\t') + result_name + " = (int32_t) " + REGISTER_3 + '\n' + '\n';

	return comment_begin + code + comment_end;
}

// x - ( ( x * x * x ) / 6 )
std::string FPGen_Sin(int depth, FIX arg, int result_ufp, int result_length, std::string result_name, std::string arg_name) {
	std::string comment_begin, comment_end;
	std::string op1, op2, op3, op4;
	FIX op1_fix, op2_fix, op3_fix, op4_fix;
	FIX cst_fix;

	comment_begin = std::string(0, '\t') + "/* " + __FUNCTION__ + " Begin */" + '\n' + '\n';
	comment_end = std::string(0, '\t') + "/* " + __FUNCTION__ + " End */" + '\n' + '\n';

	// x * x
	#ifdef FULLY_INLINE
		op1 = FPGen_Mul(depth, result_length, REGISTER_3, arg_name, arg_name);
	#else
		op1_fix = Mul(arg, arg, result_length);
		op1 = FPGen_Mul(depth, arg, arg, op1_fix.format.ufp, result_length, REGISTER_3, arg_name, arg_name);
	#endif

	// 6
	cst_fix = FPGen_float_to_FIX(6.0, ufp(6.0), 10);

	// ( x * x ) / 6
	#ifdef FULLY_INLINE
		op2 = FPGen_Div(depth, result_length, REGISTER_4, REGISTER_3, std::to_string(cst_fix.value));
	#else
		op2_fix = Div(op1_fix, cst_fix, result_length);
		op2 = FPGen_Div(depth, op1_fix, cst_fix, op2_fix.format.ufp, result_length, REGISTER_4, REGISTER_3, std::to_string(cst_fix.value));
	#endif

	// 1
	cst_fix = FPGen_float_to_FIX(1.0, ufp(1.0), 10);

	// 1 - ( ( x * x ) / 6 )
	#ifdef FULLY_INLINE
		op3 = FPGen_Sub(depth, result_length, REGISTER_5, std::to_string(cst_fix.value), REGISTER_4);
	#else
		op3_fix = Sub(cst_fix, op2_fix, result_length);
		op3 = FPGen_Sub(depth, cst_fix, op2_fix, op3_fix.format.ufp, result_length, REGISTER_5, std::to_string(cst_fix.value), REGISTER_4);
	#endif

	// x * ( 1 - ( ( x * x ) / 6 ) )
	#ifdef FULLY_INLINE
		op4 = FPGen_Mul(depth, result_length, REGISTER_3, arg_name, arg_name);
	#else
		op4_fix = Mul(arg, op3_fix, result_length);
		op4 = FPGen_Mul(depth, arg, op3_fix, op4_fix.format.ufp, result_length, result_name, arg_name, REGISTER_5);
	#endif

	return comment_begin + op1 + op2 + op3 + op4 + comment_end;
}

// 1 - ( x * x * 0.25)
std::string FPGen_Cos(int depth, FIX arg, int result_ufp, int result_length, std::string result_name, std::string arg_name) {
	std::string comment_begin, comment_end;
	std::string op1, op2, op3;
	FIX op1_fix, op2_fix, op3_fix;
	FIX cst_fix;

	comment_begin = std::string(0, '\t') + "/* " + __FUNCTION__ + " Begin */" + '\n' + '\n';
	comment_end = std::string(0, '\t') + "/* " + __FUNCTION__ + " End */" + '\n' + '\n';

	// x * x
	#ifdef FULLY_INLINE
		op1 = FPGen_Mul(depth, result_length, REGISTER_3, arg_name, arg_name);
	#else
		op1_fix = Mul(arg, arg, result_length);
		op1 = FPGen_Mul(depth, arg, arg, op1_fix.format.ufp, result_length, REGISTER_3, arg_name, arg_name);
	#endif

	// 0.25
	cst_fix = FPGen_float_to_FIX(0.25, ufp(0.25), 10);

	// ( x * x ) * 0.25
	#ifdef FULLY_INLINE
		op2 = FPGen_Mul(depth, result_length, REGISTER_4, REGISTER_3, std::to_string(cst_fix.value));
	#else
		op2_fix = Mul(op1_fix, cst_fix, result_length);
		op2 = FPGen_Mul(depth, op1_fix, cst_fix, op2_fix.format.ufp, result_length, REGISTER_4, REGISTER_3, std::to_string(cst_fix.value));
	#endif

	// 1
	cst_fix = FPGen_float_to_FIX(1.0, ufp(1.0), 10);

	// 1 - ( ( x * x ) * 0.25 )
	#ifdef FULLY_INLINE
		op3 = FPGen_Sub(depth, result_length, result_name, std::to_string(cst_fix.value), REGISTER_4);
	#else
		op3_fix = Sub(cst_fix, op2_fix, result_length);
		op3 = FPGen_Sub(depth, cst_fix, op2_fix, op3_fix.format.ufp, result_length, result_name, std::to_string(cst_fix.value), REGISTER_4);
	#endif

	return comment_begin + op1 + op2 + op3 + comment_end;
}

// x - ( ( x * x * x ) / 3 )
// x between -1 and 1
std::string FPGen_Atan(int depth, FIX arg, int result_ufp, int result_length, std::string result_name, std::string arg_name) {
	std::string comment_begin, comment_end;
	std::string op1, op2, op3, op4;
	FIX op1_fix, op2_fix, op3_fix, op4_fix;
	FIX cst_fix;

	comment_begin = std::string(0, '\t') + "/* " + __FUNCTION__ + " Begin */" + '\n' + '\n';
	comment_end = std::string(0, '\t') + "/* " + __FUNCTION__ + " End */" + '\n' + '\n';

	// x * x
	#ifdef FULLY_INLINE
		op1 = FPGen_Mul(depth, result_length, REGISTER_3, arg_name, arg_name);
	#else
		op1_fix = Mul(arg, arg, result_length);
		op1 = FPGen_Mul(depth, arg, arg, op1_fix.format.ufp, result_length, REGISTER_3, arg_name, arg_name);
	#endif

	// 3
	cst_fix = FPGen_float_to_FIX(3.0, ufp(3.0), 10);

	// x / 3
	#ifdef FULLY_INLINE
		op2 = FPGen_Div(depth, result_length, REGISTER_4, arg_name, std::to_string(cst_fix.value));
	#else
		op2_fix = Div(arg, cst_fix, result_length);
		op2 = FPGen_Div(depth, arg, cst_fix, op2_fix.format.ufp, result_length, REGISTER_4, arg_name, std::to_string(cst_fix.value));
	#endif

	// ( x * x ) * ( x / 3 )
	#ifdef FULLY_INLINE
		op3 = FPGen_Mul(depth, result_length, REGISTER_5, REGISTER_3, REGISTER_4);
	#else
		op3_fix = Mul(op1_fix, op2_fix, result_length);
		op3 = FPGen_Mul(depth, op1_fix, op2_fix, op3_fix.format.ufp, result_length, REGISTER_5, REGISTER_3, REGISTER_4);
	#endif

	// x - ( ( x * x ) * ( x / 3 ) )
	#ifdef FULLY_INLINE
		op4 = FPGen_Sub(depth, result_length, result_name, arg_name, REGISTER_5);
	#else
		op4_fix = Sub(arg, op3_fix, result_length);
		op4 = FPGen_Sub(depth, arg, op3_fix, op4_fix.format.ufp, result_length, result_name, arg_name, REGISTER_5);
	#endif

	return comment_begin + op1 + op2 + op3 + op4 + comment_end;
}