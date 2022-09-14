#include <expression/LogicalExpression.hpp>

#include <expression/ConstantExpression.hpp>

#include <fix/fix.hpp>

LogicalExpression::LogicalExpression(Expression *lExpr, Operation op, Expression *rExpr) : BinaryExpression(lExpr, rExpr) {
	m_op = op;
}

/* Statement Methods */

bool LogicalExpression::NameResolution() {
	return m_leftExpression->NameResolution() && m_rightExpression->NameResolution();
}

bool LogicalExpression::TypeSolving() {
	return m_leftExpression->TypeSolving() && m_rightExpression->TypeSolving();
}

bool LogicalExpression::CollectAnalysisItem() {
	return m_leftExpression->CollectAnalysisItem() && m_rightExpression->CollectAnalysisItem();
}

double LogicalExpression::EvaluateFloat() {
	double leftValue = m_leftExpression->EvaluateFloat();
	double rightValue = m_rightExpression->EvaluateFloat();
	double result;
	switch (m_op) {
		case Operation::EQ : result = leftValue == rightValue; break;
		case Operation::NEQ : result = leftValue != rightValue; break;
		case Operation::LESS : result = leftValue < rightValue; break;
		case Operation::LEQ : result = leftValue <= rightValue; break;
		case Operation::GREAT : result = leftValue > rightValue; break;
		case Operation::GEQ : result = leftValue >= rightValue; break;
	}
	return result;
}

std::string LogicalExpression::ToStringPOP(int depth) {
	std::string leftExpressionString;
	std::string opString;
	std::string rightExpressionString;

	leftExpressionString = m_leftExpression->ToStringPOP(0);
	switch (this->m_op) {
		case Operation::EQ : opString = " == "; break;
		case Operation::NEQ : opString = " != "; break;
		case Operation::LESS : opString = " < "; break;
		case Operation::LEQ : opString = " <= "; break;
		case Operation::GREAT : opString = " > "; break;
		case Operation::GEQ : opString = " >= "; break;
	}
	rightExpressionString = m_rightExpression->ToStringPOP(0);

	return leftExpressionString + opString + rightExpressionString;
}

std::string LogicalExpression::ToStringFloat(int depth) {
	std::string leftExpressionString;
	std::string opString;
	std::string rightExpressionString;

	leftExpressionString = m_leftExpression->ToStringFloat(0);
	switch (this->m_op) {
		case Operation::EQ : opString = " == "; break;
		case Operation::NEQ : opString = " != "; break;
		case Operation::LESS : opString = " < "; break;
		case Operation::LEQ : opString = " <= "; break;
		case Operation::GREAT : opString = " > "; break;
		case Operation::GEQ : opString = " >= "; break;
	}
	rightExpressionString = m_rightExpression->ToStringFloat(0);

	return leftExpressionString + opString + rightExpressionString;
}

std::string LogicalExpression::ToStringFixExtended(int depth) {
	std::string leftExpressionString;
	std::string opString;
	std::string rightExpressionString;

	if(IsIntegerExpression()) {
		leftExpressionString = m_leftExpression->ToStringFixExtended(0);
		rightExpressionString = m_rightExpression->ToStringFixExtended(0);
		switch (this->m_op) {
			case Operation::EQ : opString = " == "; break;
			case Operation::NEQ : opString = " != "; break;
			case Operation::LESS : opString = " < "; break;
			case Operation::LEQ : opString = " <= "; break;
			case Operation::GREAT : opString = " > "; break;
			case Operation::GEQ : opString = " >= "; break;
		}

		return leftExpressionString + opString + rightExpressionString;
	}
	else {
		return FPGen_condition(this);
	}
}