#pragma once
#include <string>
class FBXBuilder;

class FBX
{
public:
	std::wstring FBXPathw;
	std::string FBXPath;
	
	// builder
	static FBXBuilder* m_builder;
};

