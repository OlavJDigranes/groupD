#pragma once

#include "../lib_ecm/ecm.h"
#include "components/cmp_state_machine.h"
#include "components/cmp_drive.h"

class AcceleratingState : public State {
private:
	

public:
	AcceleratingState() = default;
	void execute(Entity*, double) noexcept override;
};

class BrakingState : public State {
private:
	

public:
	BrakingState() = default;
	void execute(Entity*, double) noexcept override;
};

class TurningLeftState : public State {
private:
	
	std::shared_ptr<double> _angle;

public:
	TurningLeftState(std::shared_ptr<double> angle) :_angle(angle) { }
	void execute(Entity*, double) noexcept override;
};

class TurningRightState : public State {
private:
	
	std::shared_ptr<double> _angle;

public:
	TurningRightState(std::shared_ptr<double> angle) :_angle(angle) { };
	void execute(Entity*, double) noexcept override;
};