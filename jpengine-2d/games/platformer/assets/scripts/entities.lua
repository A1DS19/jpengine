function create_player(spawn)
	local e = Entity()
	e:add_component(Transform(vec2(spawn.x, spawn.y), vec2(1, 1), 0))
	local sprite = e:add_component(Sprite("characters", 32, 32, 1, 0, 0, J2D_WHITE))
	sprite:generate_uvs(736, 128)

	local collider = e:add_component(CircleCollider(12, vec2(16, 16)))
	local attrs = PhysicsAttributes()
	attrs.etype = BodyType.Dynamic
	attrs.density = 1.0
	attrs.friction = 0.5
	attrs.restitution = 0.0
	attrs.gravity_scale = 2.0
	attrs.position = vec2(spawn.x, spawn.y)
	attrs.radius = collider.radius
	attrs.offset = collider.offset
	attrs.bcircle = true
	attrs.bfixed_rotation = true
	attrs.object_data = ObjectData("player", "actors", true, false, false, e:id())

	e:add_component(PhysicsComp(attrs))
	return { entity = e }
end

function create_platform(rect)
	local e = Entity()
	e:add_component(Transform(vec2(rect.x, rect.y), vec2(1, 1), 0))
	e:add_component(BoxCollider(rect.w, rect.h, vec2(0, 0)))

	local attrs = PhysicsAttributes()
	attrs.etype = BodyType.Static
	attrs.density = 0.0
	attrs.friction = 0.5
	attrs.position = vec2(rect.x, rect.y)
	attrs.box_size = vec2(rect.w, rect.h)
	attrs.bbox_shape = true
	attrs.bcircle = false
	attrs.object_data = ObjectData("platform", "world", true, false, false, e:id())

	e:add_component(PhysicsComp(attrs))
	return { entity = e, rect = rect, color = rect.color or Color(90, 140, 90, 255) }
end

function create_coin(spawn)
	local e = Entity()
	e:add_component(Transform(vec2(spawn.x, spawn.y), vec2(1, 1), 0))
	local collider = e:add_component(CircleCollider(10, vec2(0, 0)))

	local attrs = PhysicsAttributes()
	attrs.etype = BodyType.Static
	attrs.position = vec2(spawn.x, spawn.y)
	attrs.radius = collider.radius
	attrs.bcircle = true
	attrs.bsensor = true
	attrs.bfixed_rotation = true
	attrs.object_data = ObjectData("coin", "pickups", false, false, true, e:id())

	e:add_component(PhysicsComp(attrs))
	return { entity = e, center = vec2(spawn.x + 10, spawn.y + 10), id = e:id() }
end

function create_goal(spawn)
	local e = Entity()
	e:add_component(Transform(vec2(spawn.x, spawn.y), vec2(1, 1), 0))
	e:add_component(BoxCollider(32, 48, vec2(0, 0)))

	local attrs = PhysicsAttributes()
	attrs.etype = BodyType.Static
	attrs.position = vec2(spawn.x, spawn.y)
	attrs.box_size = vec2(32, 48)
	attrs.bbox_shape = true
	attrs.bcircle = false
	attrs.bsensor = true
	attrs.object_data = ObjectData("goal", "world", false, false, true, e:id())

	e:add_component(PhysicsComp(attrs))
	return { entity = e, rect = { x = spawn.x, y = spawn.y, w = 32, h = 48 } }
end

function create_hud_text(pos, text)
	local e = Entity()
	e:add_component(Transform(vec2(pos.x, pos.y), vec2(1, 1), 0))
	e:add_component(TextComponent("pixel", text, J2D_WHITE))
	return { entity = e }
end
