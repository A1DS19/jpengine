#pragma once

#include "box2d-wrappers.hpp"
#include "physics-utilities.hpp"
#include "user-data.hpp"

#include <box2d/b2_body.h>
#include <box2d/b2_math.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
#include <sol/sol.hpp>

namespace jpengine {

struct PhysicsAttributes {
    RigidBodyType etype_{RigidBodyType::STATIC};
    // the density of the body, usually in kg/m^2
    float density_{1.F};
    // the coulum (dry) friction coefficient, usually in the range of [0, 1]
    float friction_{0.2F};
    // the restitution (bounciness) usually in range of [0, 1]
    float restitution_{0.2F};
    // if a circle, the radius of the circle shape
    float radius_{0.F};
    // scale the gravity applied to this body
    float gravity_scale_{1.F};
    // initial world position of the body
    glm::vec2 position_{0.F};
    // the amount of scale the body based on its shape's size
    glm::vec2 scale_{1.F};
    // if a box, the w and h of the box shape
    glm::vec2 box_size_{1.F};
    // x/y offset of the collider based on the TL position of the owner
    glm::vec2 offset_{1.F};
    // if set, the circle collider is used in construction for the size
    bool bcircle_{false};
    // if set, the box collider should be used in construction of the size
    bool bbox_shape_{false};
    // should the body be prevented from rotation?
    bool bfixed_rotation_{true};
    // if set the sensor will generate overlap events; however no collisions
    bool bsensor_{false};
    // if set, treat it as a high speed object with continous collision detection
    bool bbullet_{false};
    // do you want to use filters with this body
    bool buse_filters_{false};
    // filter category of the body itself
    std::uint16_t filter_category_{0};
    // the collision mask bits, the categories that this shape will collide with
    std::uint16_t filter_mask_{0};
    // a group index of 0 has no effectm non zero groups follow specific rules
    std::int16_t group_index_{0};
    // user specified data for each body
    ObjectData object_data_{};
};

class PhysicsComponent {

public:
    PhysicsComponent();
    PhysicsComponent(const PhysicsAttributes& physics_attributes);
    ~PhysicsComponent();

    void init(PhysicsWorld pphysics_world, int window_w, int window_h);
    [[nodiscard]] bool is_sensor() const noexcept;
    [[nodiscard]] ObjectData cast_ray(const b2Vec2& point_1, const b2Vec2& point_2) const noexcept;
    [[nodiscard]] std::vector<ObjectData> box_trace(const b2Vec2& lower_bounds,
                                                    const b2Vec2& upper_bounds) const noexcept;
    [[nodiscard]] ObjectData get_current_object_data() const noexcept;
    void set_filter_category(std::uint16_t mask) noexcept;
    void set_filter_category() noexcept;
    void set_filter_mask(std::uint16_t mask) noexcept;
    void set_filter_mask() noexcept;
    void set_group_index(std::int16_t index) noexcept;
    void set_group_index() noexcept;

    [[nodiscard]] bool use_filters() const noexcept { return initial_attribs_.buse_filters_; }

    [[nodiscard]] b2Body* get_body() const noexcept { return prigid_body_.get(); }
    [[nodiscard]] UserData* get_user_data() const noexcept { return puser_data_.get(); }

    [[nodiscard]] const PhysicsAttributes& get_attributes() const noexcept {
        return initial_attribs_;
    }
    [[nodiscard]] const PhysicsAttributes& get_changeable_attributes() const noexcept {
        return initial_attribs_;
    }
    static void create_lua_bind(sol::state& lua, PhysicsWorld& physics_world);

private:
    std::shared_ptr<b2Body> prigid_body_;
    std::shared_ptr<UserData> puser_data_;
    PhysicsAttributes initial_attribs_;
};

} // namespace jpengine
