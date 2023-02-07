#include "../../include/entities/entity.h"

Entity::Entity(std::initializer_list<std::string> args, int x, int y) : SpriteAnimation(args) {

}

Entity::~Entity() = default;

