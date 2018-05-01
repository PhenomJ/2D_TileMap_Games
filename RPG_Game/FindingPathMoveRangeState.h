#pragma once
#include "FindingPathState.h"

class FindingPathMoveRangeState : public FindingPathState

{
public:
	FindingPathMoveRangeState();
	~FindingPathMoveRangeState();

public:
	void Start();
	void InputClick();
};