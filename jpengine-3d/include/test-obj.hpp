#pragma once
#include "engine/engine.hpp"
#include "engine/src/render/mesh.hpp"
#include "engine/src/scene/game-object.hpp"

#include <memory>

class TestObject : public engine::GameObject {
public:
    TestObject();
    void update(float deltatime) override;

private:
    engine::Material material_;
    std::unique_ptr<engine::Mesh> mesh_;
};
