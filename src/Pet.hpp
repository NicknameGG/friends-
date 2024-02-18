#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

enum PetType {
	NA,
	Easy,
	Normal,
	Hard,
	Harder,
	Insane,
	// Demon,
	EasyDemon,
	MediumDemon,
	HardDemon,
	InsaneDemon,
	ExtremeDemon,
	Auto
};

class Pet : public CCSprite {
public: 
	float acceleration = 0.0f;

	static Pet *create(PetType type) {
		Pet *pRet = new Pet();
		if (pRet && pRet->init(type)) {
			pRet->autorelease();
			return pRet;
		} else {
			delete pRet;
			pRet = 0;
			return 0;
		}
	};

    bool init(PetType type) {
		// Set sprite frame
		std::map<PetType, std::string> petTypeToFrame = {
			{PetType::NA, "diffIcon_00_btn_001.png"},
			{PetType::Easy, "diffIcon_01_btn_001.png"},
			{PetType::Normal, "diffIcon_02_btn_001.png"},
			{PetType::Hard, "diffIcon_03_btn_001.png"},
			{PetType::Harder, "diffIcon_04_btn_001.png"},
			{PetType::Insane, "diffIcon_05_btn_001.png"},
			{PetType::EasyDemon, "diffIcon_07_btn_001.png"},
			{PetType::MediumDemon, "diffIcon_08_btn_001.png"},
			{PetType::HardDemon, "diffIcon_06_btn_001.png"},
			{PetType::InsaneDemon, "diffIcon_09_btn_001.png"},
			{PetType::ExtremeDemon, "diffIcon_10_btn_001.png"},
			{PetType::Auto, "diffIcon_auto_btn_001.png"}
		};

		if (!CCSprite::initWithSpriteFrameName(petTypeToFrame[type].c_str())) {
			return false;
		}

		// Activate update
		this->scheduleUpdate();

		return true;
	}

	void move() {
		if (auto action = this->getActionByTag(1)) {
			if (!action->isDone()) {
				return;
			}
		}

		float moveDirection = rand() % 2 == 0 ? 1 : -1;

		// Check if after x + 20 * moveDirection, the sprite will be out of the screen
		if (this->boundingBox().origin.x + 20 * moveDirection <= 0 || this->boundingBox().origin.x + 20 * moveDirection >= CCDirector::sharedDirector()->getWinSize().width) {
			moveDirection *= -1;
		}

		CCRotateBy* rotate = CCRotateBy::create(0.5f, 360 * moveDirection);
		CCMoveBy* move = CCMoveBy::create(0.5f, ccp(100 * moveDirection, 40));
		
		this->stopAllActions();
		
		this->runAction(rotate);
		auto moveAction = this->runAction(move);
		moveAction->setTag(1);

	}

	void update(float dt) {
		// Check if the sprite bounding box is touching the left of the screen
		if (this->boundingBox().origin.x <= 0) {
			// Stop it from doing so by setting the position to the left of the screen + the width of the sprite
			this->setPositionX(this->boundingBox().size.width / 2);
		}

		// Same with the right of the screen
		if (this->boundingBox().origin.x + this->boundingBox().size.width >= CCDirector::sharedDirector()->getWinSize().width) {
			this->setPositionX(CCDirector::sharedDirector()->getWinSize().width - this->boundingBox().size.width / 2);
		}

		// Check if sprite bounding box is touching the bottom of the screen
		if (this->boundingBox().origin.y <= 0) {
			// Reset acceleration
			this->acceleration = 0.0f;

			// Set position to the bottom of the screen
			this->setPositionY(this->boundingBox().getMidY() - this->acceleration);
		}
		else {
			// Accelerate
			this->acceleration += 0.1f;

			// Move
			this->setPosition(this->getPosition() - ccp(0, this->acceleration));
		}

		// Move randomly
		if (rand() % 200 == 0) {
			this->move();
		}
	}

};