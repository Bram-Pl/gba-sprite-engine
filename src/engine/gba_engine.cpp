//
// Created by Wouter Groeneveld on 28/07/18.
//

#include <engine/gba/tonc_memdef.h>
#include <engine/background/text_stream.h>
#include "gba_engine.h"
#include "allocator.h"

void GBAEngine::update() {
    vsync();

    if(sceneToTransitionTo) {
        currentEffectForTransition->update();

        if(currentEffectForTransition->isDone()) {
            setScene(sceneToTransitionTo);
        }
    }

    spriteManager.render();
    u16 keys = readKeys();
    this->currentScene->tick(keys);
}

void GBAEngine::transitionIntoScene(Scene *scene, SceneEffect* effect) {
    sceneToTransitionTo = scene;
    currentEffectForTransition = effect;
    currentEffectForTransition->setSceneToAffect(this->currentScene);
}

u16 GBAEngine::readKeys() {
    return ~REG_KEYS & KEY_ANY;
}

GBAEngine::GBAEngine() {
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3;
    Allocator::free();
}

void GBAEngine::cleanupPreviousScene()  {
    delete currentScene;
    sceneToTransitionTo = nullptr;
    delete currentEffectForTransition;
}

void GBAEngine::setScene(Scene* scene) {
    if(this->currentScene) {
        cleanupPreviousScene();
        TextStream::instance().clear();
    }
    scene->load();

    auto fgPalette = scene->getForegroundPalette();
    if(fgPalette) {
        fgPalette->persist();
    }
    auto bgPalette = scene->getBackgroundPalette();
    if(bgPalette) {
        bgPalette->persist();
    }

    Allocator::free();
    TextStream::instance().persist();

    spriteManager.set(scene->sprites());
    spriteManager.persist();

    for(const auto bg : scene->backgrounds()) {
        bg->persist();
    }

    this->currentScene = scene;
}
