#pragma once
#include "script_engine_param.h"
#include <string>

class IComparator
{
public:
	virtual bool TryFindComparator(const std::string& cmd,std::string& leftExp,std::string& rightExp) = 0;
	virtual bool IsTrue(ScriptParam leftResult,ScriptParam rightResult) = 0;
};

class CCompare_Equal : public IComparator
{
public:
	bool TryFindComparator(const std::string& cmd,std::string& leftExp,std::string& rightExp) override
	{
		auto iFind = std::find(cmd.begin(), cmd.end(), '=');
		if (iFind == cmd.end())
		{
			return false;
		}
		leftExp = cmd.substr(0,iFind-cmd.begin());
		rightExp = cmd.substr(iFind-cmd.begin()+1, cmd.end()-iFind);
		return true;
	}
	bool IsTrue(ScriptParam leftResult,ScriptParam rightResult) override
	{
		switch (leftResult.type())
		{
		case ScriptParam::Type::Bool:
			return (bool)leftResult == (bool)rightResult;
			break;
		case ScriptParam::Type::Int:
			return (int)leftResult == (int)rightResult;
		case ScriptParam::Type::String:
			return (strcmp(leftResult,rightResult)==0)?true:false;
		default:
			break;
		}
		return false;
	}
};