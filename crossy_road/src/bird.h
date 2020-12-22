//
// Created by pless on 17/12/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BIRD_H
#define GBA_SPRITE_ENGINE_PROJECT_BIRD_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

///bird class .h file
class bird {
private:
    ///Declaration of sprites
    std::unique_ptr<Sprite> birdForwardSprite;
    std::unique_ptr<Sprite> birdForwardMoveSprite;
    std::unique_ptr<Sprite> birdLeftSprite;
    std::unique_ptr<Sprite> birdLeftMoveSprite;
    std::unique_ptr<Sprite> birdRightSprite;
    std::unique_ptr<Sprite> birdRightMoveSprite;
    std::unique_ptr<Sprite> grassBiomeSprite;

    ///boolean to check the last movement -- influences the sprite displayed
    bool lastMoveForward;
    bool lastMoveLeft;
    bool lastMoveRight;

    ///timer for the fly 'animation'
    int timer;

public:
    ///Constructor
    bird(   std::unique_ptr<Sprite> birdForwardSprite,
            std::unique_ptr<Sprite> birdForwardMoveSprite,
            std::unique_ptr<Sprite> birdLeftSprite,
            std::unique_ptr<Sprite> birdLeftMoveSprite,
            std::unique_ptr<Sprite> birdRightSprite,
            std::unique_ptr<Sprite> birdRightMoveSprite,
            std::unique_ptr<Sprite> grassBiomeSprite) :
            birdForwardSprite(std::move(birdForwardSprite)),
            birdForwardMoveSprite(std::move(birdForwardMoveSprite)),
            birdLeftSprite(std::move(birdLeftSprite)),
            birdLeftMoveSprite(std::move(birdLeftMoveSprite)),
            birdRightSprite(std::move(birdRightSprite)),
            birdRightMoveSprite(std::move(birdRightMoveSprite)),
            grassBiomeSprite(std::move(grassBiomeSprite)) {};


    ///Getters
    Sprite* getBirdForwardSprite() {return birdForwardSprite.get();}
    Sprite* getbirdForwardMoveSprite() {return birdForwardMoveSprite.get();}
    Sprite* getbirdLeftSprite() {return birdLeftSprite.get();}
    Sprite* getbirdLeftMoveSprite() {return birdLeftMoveSprite.get();}
    Sprite* getbirdRightSprite() {return birdRightSprite.get();}
    Sprite* getbirdRightMoveSprite() {return birdRightMoveSprite.get();}
    Sprite* getGrassBiome() {return grassBiomeSprite.get();}

    int score = 0;

    ///tick function for key presses
    void tick(u16 keys);

    ///Declaration start position bird
    double xPosition = (GBA_SCREEN_WIDTH/2 - 16);
    double yPosition = (GBA_SCREEN_HEIGHT - 32);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_BIRD_H
