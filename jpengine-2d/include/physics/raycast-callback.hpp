#pragma once

#include <box2d/box2d.h>

namespace jpengine {

class RayCastCallback : public b2RayCastCallback {

public:
    RayCastCallback();
    ~RayCastCallback();

    float ReportFixture(b2Fixture* pfixture, const b2Vec2& point, const b2Vec2& normal,
                        float fraction) override;
    [[nodiscard]] bool is_hit() const noexcept { return bhit_; }
    [[nodiscard]] b2Fixture* hit_fixture() const noexcept { return phit_fixture_; }
    [[nodiscard]] b2Vec2& hit_point() noexcept { return point_; }
    [[nodiscard]] b2Vec2& hit_normal() noexcept { return normal_; }
    [[nodiscard]] float fraction() const noexcept { return fraction_; }

private:
    // fixture hit by the ray
    b2Fixture* phit_fixture_;
    // point of initial intersection
    b2Vec2 point_;
    // the normal vector at the point of intersection
    b2Vec2 normal_;
    // the fraction along the ray at the point of intersection
    float fraction_;
    // did the ray hit something?
    bool bhit_;
};

} // namespace jpengine
