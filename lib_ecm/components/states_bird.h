#pragma once

#include "cmp_state_machine.h"
#include "cmp_ai_bird.h"

class WaitingState : public State {
public:
	WaitingState() = default;
	void execute(Entity* p, double dt) noexcept override;
};

class ChasingState : public State {
public:
	ChasingState() = default;
	void execute(Entity* p, double dt) noexcept override;
};

class ReturningHomeState : public State {
public:
	ReturningHomeState() = default;
	void execute(Entity* p, double dt) noexcept override;
};
