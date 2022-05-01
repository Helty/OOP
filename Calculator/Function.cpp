#include "Function.h"

�Function::�Function()
{
}

�Function::�Function(std::string const& identifier)
	: m_identifier1(identifier), m_operation(�Function::Operation::None), m_value(std::nullopt)
{
}

�Function::�Function(std::string const& identifier1, Operation const& operation, std::string const& identifier2)
	: m_identifier1(identifier1), m_operation(operation), m_identifier2(identifier2), m_value(std::nullopt)
{
}

void �Function::SetValue(std::optional<double> value)
{
	m_value = value;
}

std::optional<double> �Function::GetValue() const
{
	return m_value;
}

std::string �Function::GetIdentifier1() const
{
	return m_identifier1;
}

�Function::Operation �Function::GetOperation() const
{
	return m_operation;
}

std::string �Function::GetIdentifier2() const
{
	return m_identifier2;
}
