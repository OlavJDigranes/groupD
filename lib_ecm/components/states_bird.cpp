#include "states_bird.h"

void WaitingState::execute(Entity* p, double dt) noexcept {
	auto AI = p->get_components<AIBirdComponent>();
	std::shared_ptr<BirdSteering> bc = AI[0]->GetSteeringComponent();
	if (bc != nullptr && bc->IsActive() == true) {
		bc->SetActive(false);
		bc->SetTargetLocation(&AI[0]->GetHomeLocation());
	}
	bc.reset();
}

void ChasingState::execute(Entity* p, double dt) noexcept {
	auto AI = p->get_components<AIBirdComponent>();
	std::shared_ptr<BirdSteering> bc = AI[0]->GetSteeringComponent();
	if (bc != nullptr && bc->IsActive() == false) {
		bc->SetActive(true);
		bc->SetEntityAsTarget(AI[0]->getPlayer().get());
	}
	bc.reset();
}

void ReturningHomeState::execute(Entity* p, double dt) noexcept {
	auto AI = p->get_components<AIBirdComponent>();
	std::shared_ptr<BirdSteering> bc = AI[0]->GetSteeringComponent();
	if (bc != nullptr) {
		if (bc->GetTargetLocation() != AI[0]->GetHomeLocation() || bc->IsTargetingEntity()) {
			bc->SetTargetLocation(&AI[0]->GetHomeLocation());
		}
	}
	bc.reset();
}
