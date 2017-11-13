#pragma once
#include <string>

class Component;
struct sComponentMsgParam
{
	Component* sender;
	Component* receiver;
	std::wstring message;
	int attackPoint = 1;
};