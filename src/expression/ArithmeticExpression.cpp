#include <expression/ArithmeticExpression.hpp>

/* Constructors & Destructor */

ArithmeticExpression::ArithmeticExpression(Expression *lExpr, Operation op, Expression *rExpr) : BinaryExpression(lExpr, rExpr) {
	m_op = op;
}

ArithmeticExpression::ArithmeticExpression(Expression *lExpr, Operation op, Precision *precision, Expression *rExpr) : BinaryExpression(lExpr, precision, rExpr) {
	m_op = op;
	m_precision = precision;
}

ArithmeticExpression::Operation ArithmeticExpression::GetOp() {
	return m_op;
}

Expression * ArithmeticExpression::GetOperand1() {
	return m_leftExpression;
}

Expression * ArithmeticExpression::GetOperand2() {
	return m_rightExpression;
}

/* Statement Methods */

bool ArithmeticExpression::NameResolution() {
	return m_leftExpression->NameResolution() && m_rightExpression->NameResolution();
}

bool ArithmeticExpression::TypeSolving() {
	return m_leftExpression->TypeSolving() && m_rightExpression->TypeSolving();
}

bool ArithmeticExpression::CollectAnalysisItem() {
	return m_leftExpression->CollectAnalysisItem() && m_rightExpression->CollectAnalysisItem();
}

double ArithmeticExpression::EvaluateFloat() {
	double leftValue = m_leftExpression->EvaluateFloat();
	double rightValue = m_rightExpression->EvaluateFloat();
	double result;
	switch (m_op) {
		case Operation::PLUS : result = leftValue + rightValue; break;
		case Operation::MINUS : result = leftValue - rightValue; break;
		case Operation::TIMES : result = leftValue * rightValue; break;
		case Operation::DIVIDE : result = leftValue / rightValue; break;
	}
	m_evaluatedValue = result;
	return result;
}

std::string ArithmeticExpression::ToStringPOP(int depth) {
	std::string leftExpressionString = m_leftExpression->ToStringPOP(0);
	std::string opString;
	std::string precisonString = m_precision->ToStringPOP(0);
	std::string rightExpressionString = m_rightExpression->ToStringPOP(0);

	switch (this->m_op) {
		case Operation::PLUS : opString = " +"; break;
		case Operation::MINUS : opString = " -"; break;
		case Operation::TIMES : opString = " *"; break;
		case Operation::DIVIDE : opString = " /"; break;
	}

	return leftExpressionString + opString + precisonString + " " + rightExpressionString;
}

std::string ArithmeticExpression::ToStringFloat(int depth) {
	std::string leftExpressionString = m_leftExpression->ToStringFloat(0);
	std::string opString;
	std::string rightExpressionString = m_rightExpression->ToStringFloat(0);
	switch (this->m_op) {
		case Operation::PLUS : opString = " + "; break;
		case Operation::MINUS : opString = " - "; break;
		case Operation::TIMES : opString = " * "; break;
		case Operation::DIVIDE : opString = " / "; break;
	}
	return leftExpressionString + opString + rightExpressionString;
}

std::string ArithmeticExpression::ToStringFixExtended(int depth) {
	std::string leftExpressionString;
	std::string opString;
	std::string rightExpressionString;

	if(IsIntegerExpression()) {
		leftExpressionString = m_leftExpression->ToStringFixExtended(0);
		switch (this->m_op) {
			case Operation::PLUS : opString = " + "; break;
			case Operation::MINUS : opString = " - "; break;
			case Operation::TIMES : opString = " * "; break;
			case Operation::DIVIDE : opString = " / "; break;
		}
		rightExpressionString = m_rightExpression->ToStringFixExtended(0);
	}
	else {
		leftExpressionString = m_leftExpression->ToStringFixExtended(0);
	}
	
	return leftExpressionString + opString + rightExpressionString;
}