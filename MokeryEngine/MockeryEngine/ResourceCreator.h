#pragma once
#include "framework.h"
class KSL;

class ResourceCreator
{
public:
	ResourceCreator():m_hInst(nullptr), m_soundCreator(nullptr) {}

public:
	HINSTANCE m_hInst;
	KSL* m_soundCreator;
};

