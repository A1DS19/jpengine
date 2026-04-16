#include "physics/boxtrace-callback.hpp"

namespace jpengine {

bool BoxTraceCallback::ReportFixture(b2Fixture* pfixture) {
    pbodies_.push_back(pfixture->GetBody());
    return pfixture != nullptr;
}

} // namespace jpengine
