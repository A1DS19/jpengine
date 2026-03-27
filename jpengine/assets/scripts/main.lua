print("running lua script")

print("step 1: entity_1")
local entity_1 = Entity()
print("step 2: add_component entity_1")
entity_1:add_component(Transform(100.0, 150.0, 0.0))

print("step 3: entity_2")
local entity_2 = Entity()
print("step 4: add_component entity_2")
entity_2:add_component(Transform(450.0, 75.0, 0.0))

print("step 5: registry")
local registry = Registry()
print("step 6: entity_3")
local entity_3 = registry:create_entity()
print("step 7: add_component entity_3")
entity_3:add_component(Transform(96.0, 69.0, 0.0))

print("step 8: get_entities")
local view = registry:get_entities(Transform)

print("step 9: for_each")
view:for_each(function(entity)
	print("step 9a: get_component")
	local transform = entity:get_component(Transform)
	print("step 9b: get_position")
	local x, y = transform:get_position()
	print("reg 1: ")
	print("position: [x = " .. x .. ", y = " .. y .. "]")
end)

print("create second registry")

local registry_2 = Registry(RegistryType.LUA)
local entity_4 = registry_2:create_entity()
entity_4:add_component(Transform(999.0, 999.0, 0.0))
local view_2 = registry_2:get_entities(Transform)
view_2:for_each(registry_2, function(entity)
	local transform = entity:get_component(Transform)
	local x, y = transform:get_position()
	print("reg 2: ")
	print("position: [x = " .. x .. ", y = " .. y .. "]")
end)

local g_cam = Camera.get()

return function()
	if g_cam then
		local x, y = g_cam:get_position()
		g_cam:set_position(x - 0.5, y - 0.5)
		g_cam:set_scale(g_cam:get_scale() * 1.001)
	end
end
