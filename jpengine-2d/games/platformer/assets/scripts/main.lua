j2d_run_script("assets/scripts/defs/asset-defs.lua")
j2d_run_script("assets/scripts/utils.lua")

load_assets(asset_defs)

local gplayer = Entity()
local transform = gplayer:add_component(Transform(vec2(50, 50), vec2(2, 2), 0))
local sprite = gplayer:add_component(Sprite("characters", 32, 32, 0, 0, 1, J2D_WHITE))
sprite:generate_uvs(736, 128)

local circle_collider = gplayer:add_component(CircleCollider(8, vec2(8, 8)))
local physics_attr = PhysicsAttributes()
physics_attr.etype = BodyType.Dynamic
physics_attr.density = 100.0
physics_attr.friction = 0.0
physics_attr.restitution = 0.0
physics_attr.gravity_scale = 0.0
physics_attr.offset = circle_collider.offset
physics_attr.scale = transform.scale
physics_attr.position = transform.position
physics_attr.radius = circle_collider.radius
physics_attr.bcircle = true
physics_attr.bfixed_rotation = true
physics_attr.object_data = ObjectData("g player 1", "", false, false, true, gplayer:id())

gplayer:add_component(PhysicsComp(physics_attr))

local gplayer2 = Entity()
local transform2 = gplayer2:add_component(Transform(vec2(50, 300), vec2(2, 2), 0))
local sprite2 = gplayer2:add_component(Sprite("characters", 32, 32, 0, 0, 1, J2D_WHITE))
sprite2:generate_uvs(736, 128)

local circle_collider2 = gplayer2:add_component(CircleCollider(8, vec2(8, 8)))
local physics_attr2 = PhysicsAttributes()
physics_attr2.etype = BodyType.Dynamic
physics_attr2.density = 1000.0
physics_attr2.friction = 0.0
physics_attr2.restitution = 1.0
physics_attr2.gravity_scale = 0.0
physics_attr2.scale = transform2.scale
physics_attr2.offset = circle_collider2.offset
physics_attr2.position = transform2.position
physics_attr2.radius = circle_collider2.radius
physics_attr2.bcircle = true
physics_attr2.bfixed_rotation = true
physics_attr2.object_data = ObjectData("g player 2", "", false, false, true, gplayer2:id())

gplayer2:add_component(PhysicsComp(physics_attr2))

function update_player(ent)
	local physics = ent:get_component(PhysicsComp)
	physics:set_linear_velocity(vec2(0, 0))

	if Keyboard.pressed(KEY_W) then
		physics:set_linear_velocity(vec2(0, -10))
	elseif Keyboard.pressed(KEY_S) then
		physics:set_linear_velocity(vec2(0, 10))
	elseif Keyboard.pressed(KEY_A) then
		physics:set_linear_velocity(vec2(-10, 10))
	elseif Keyboard.pressed(KEY_D) then
		physics:set_linear_velocity(vec2(10, 0))
	end
end

function update_raycast(ent)
	local physics = ent:get_component(PhysicsComp)
	local transform = ent:get_component(Transform)
	-- local hit_object = physics:cast_ray(
	-- 	vec2(transform.position.x + 32, transform.position.y + 64),
	-- 	vec2(transform.position.x + 200, transform.position.y + 64)
	-- )
	--
	-- draw_line(
	-- 	Line(
	-- 		vec2(transform.position.x + 32, transform.position.y + 64),
	-- 		vec2(transform.position.x + 200, transform.position.y + 64),
	-- 		Color(0, 255, 0, 255)
	-- 	)
	-- )
	--
	-- if hit_object then
	-- 	print(hit_object.tag)
	-- end

	local hit_objects = physics:box_trace(
		vec2(transform.position.x + 32, transform.position.y + 32),
		vec2(transform.position.x + 200, transform.position.y + 64)
	)

	draw_rect(
		Rect(vec2(transform.position.x + 32, transform.position.y + 32), vec2(168, 32), Color(0, 255, 0, 255), false)
	)

	for k, v in ipairs(hit_objects) do
		print(v.tag)
	end
end

main = {
	update = function()
		update_player(gplayer)
		if Keyboard.just_pressed(KEY_SPACE) then
			update_raycast(gplayer)
		end
	end,
}
