#include "PhysicGround.h"
#include "Character/Character.h"
#include "DefineBitmask.h"

USING_NS_CC;


bool PhysicGround::init(TMXObjectGroup* objectGroup) {
    if (!Node::init()) {
        return false;
    }

    if (objectGroup) {
        auto objects = objectGroup->getObjects();
        for (const auto& object : objects) {
            ValueMap lineInfo = object.asValueMap();
            float x = lineInfo["x"].asFloat();
            float y = lineInfo["y"].asFloat();
            float width = lineInfo["width"].asFloat();
            float height = lineInfo["height"].asFloat();
            Vec2 origin(x, y);
            Vec2 topLeft(x, y + height);
            Vec2 topRight(x + width, y + height);
            auto lineNode = Node::create();
            auto physicsBodyGround = PhysicsBody::createBox(Size(width, height));
            physicsBodyGround->setCategoryBitmask(DefineBitmask::GROUND);
            physicsBodyGround->setCollisionBitmask(DefineBitmask::CHARACTER | DefineBitmask::ENEMY);
            physicsBodyGround->setContactTestBitmask(DefineBitmask::CHARACTER | DefineBitmask::ENEMY);
            physicsBodyGround->setPositionOffset(Vec2(width * 0.5f, height * 0.5f));
            physicsBodyGround->setDynamic(false);
            lineNode->setPhysicsBody(physicsBodyGround);
            lineNode->setPosition(origin);
            lineNode->setTag(TAG_GROUND);
            this->addChild(lineNode);
        }
    }

    return true;
}

PhysicGround* PhysicGround::create(TMXObjectGroup* objectGroup) {
    auto ground = new (std::nothrow) PhysicGround();
    if (ground && ground->init(objectGroup)) {
        ground->autorelease();
        return ground;
    }
    else {
        delete ground;
        return nullptr;
    }
}








