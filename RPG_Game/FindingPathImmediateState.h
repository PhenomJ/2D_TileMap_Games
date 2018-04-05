#pragma once
#include "FindingPathState.h"

class FindingPathImmediateState : public FindingPathState
{
public:
	FindingPathImmediateState();
	~FindingPathImmediateState();

public:
	void Start();
};