#pragma once

#include <box2d/box2d.h>
#include <vector>

namespace jpengine {

class BoxTraceCallback : public b2QueryCallback {

public:
    BoxTraceCallback() = default;
    ~BoxTraceCallback() = default;

    bool ReportFixture(b2Fixture* pfixture) override;
    [[nodiscard]] std::vector<b2Body*>& get_bodies() noexcept { return pbodies_; }

private:
    std::vector<b2Body*> pbodies_;
};

} // namespace jpengine
