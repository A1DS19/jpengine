#include "physics/box2d-wrappers.hpp"

using namespace jpengine;

void BodyDestroyer::operator()(b2Body* pbody) const {
    pbody->GetWorld()->DestroyBody(pbody);
}
