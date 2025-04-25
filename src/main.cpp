#include <Geode/Geode.hpp>
#include <Geode/modify/AppDelegate.hpp>

#include "PetLayer.hpp"

using namespace geode::prelude;

PetLayer* petLayer = nullptr;

class $modify(AppDelegate) {
	void willSwitchToScene(CCScene* scene) {
		AppDelegate::willSwitchToScene(scene);

		auto disableInGame = Mod::get()->getSettingValue<bool>("Disable In Game");
		auto disableInEditor = Mod::get()->getSettingValue<bool>("Disable In Editor");

		if (disableInGame || disableInEditor) {
			if (!scene->getChildren()) {
				petLayer->removeFromParentAndCleanup(false);
				return;	
			} 

			if (auto firstChild = scene->getChildren()->objectAtIndex(0)) {
				if (auto layer = dynamic_cast<CCLayer*>(firstChild)) {
					if (disableInGame) {
						if (typeinfo_cast<PlayLayer*>(layer)) {
							petLayer->removeFromParentAndCleanup(false);
							return;
						}
					}
					
					if (disableInEditor) {
						if (typeinfo_cast<LevelEditorLayer*>(layer)) {
							petLayer->removeFromParentAndCleanup(false);
							return;
						}
					}
				}
			}
		}

		if (!petLayer) {
			petLayer = PetLayer::create();
			petLayer->retain();
		}

		petLayer->removeFromParentAndCleanup(false);
		scene->addChild(petLayer, 100);
	}
};


$execute {
	listenForAllSettingChanges([](auto v) {
		if (petLayer) {
			petLayer->updateValues();
		}
	});
}