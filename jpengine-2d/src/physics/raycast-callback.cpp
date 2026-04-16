#include "physics/raycast-callback.hpp"

namespace jpengine {
RayCastCallback::RayCastCallback()
    : phit_fixture_{nullptr}, point_{}, normal_{}, fraction_{0.F}, bhit_{false} {}

RayCastCallback::~RayCastCallback() = default;

float RayCastCallback::ReportFixture(b2Fixture* pfixture, const b2Vec2& point, const b2Vec2& normal,
                                     float fraction) {
    bhit_ = pfixture != nullptr;
    phit_fixture_ = pfixture;
    point_ = point;
    normal_ = normal;
    fraction_ = fraction;

    return 0.F;
}
} // namespace jpengine
