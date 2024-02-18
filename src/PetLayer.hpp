#pragma once

#include <Geode/Geode.hpp>
#include "Pet.hpp"

using namespace geode::prelude;

class PetLayer : public CCLayer {
public:
	float sizeMult = Mod::get()->getSettingValue<double>("Friend Scale");

	static PetLayer *create() {
		PetLayer *pRet = new PetLayer();
		if (pRet && pRet->init()) {
				pRet->autorelease();
				return pRet;
		} else {
				delete pRet;
				pRet = 0;
				return 0;
		}
	};

	Pet *createPet(PetType type, int div = 2) {
		auto pet = Pet::create(type);
		pet->setPosition(CCDirector::get()->getWinSize() / div);

		pet->setScale(this->sizeMult);
		this->sizeMult += 0.05f;

		this->addChild(pet, 100);
		return pet;
	}

	void updateValues() {
		this->sizeMult = Mod::get()->getSettingValue<double>("Friend Scale");

		for (auto child : CCArrayExt<CCNode*>(this->getChildren())) {
			auto pet = dynamic_cast<Pet*>(child);
			if (pet) {
				pet->setScale(this->sizeMult);
				this->sizeMult += 0.05f;
			}
		}
	}

	bool init() {
		if (!CCLayer::init()) {
			return false;
		}

		this->createPet(PetType::Auto);
		this->createPet(PetType::Easy);
		this->createPet(PetType::Normal);
		this->createPet(PetType::Hard);
		this->createPet(PetType::Harder);
		this->createPet(PetType::Insane);
		this->createPet(PetType::EasyDemon);
		this->createPet(PetType::MediumDemon);
		this->createPet(PetType::HardDemon);
		this->createPet(PetType::InsaneDemon);
		this->createPet(PetType::ExtremeDemon);

		this->updateValues();

		return true;
	}
};