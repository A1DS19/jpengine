print("running lua script")

local entity_1 = Entity()
entity_1:add_component(Transform(100.0, 150.0, 1, 1, 0.0))
local sprite_1 = entity_1:add_component(Sprite("character", 32, 32, 0, 0, 0, J2D_WHITE))
sprite_1:generate_uvs(32, 32)

local entity_2 = Entity()
entity_2:add_component(Transform(450.0, 75.0, 1, 1, 0.0))
local sprite_2 = entity_2:add_component(Sprite("character", 32, 32, 0, 0, 0, J2D_RED))
sprite_2:generate_uvs(32, 32)

local registry = Registry()
local entity_3 = registry:create_entity()
entity_3:add_component(Transform(96.0, 69.0, 1, 1, 0.0))
local sprite_3 = entity_3:add_component(Sprite("character", 32, 32, 0, 0, 0, J2D_GREEN))
sprite_3:generate_uvs(32, 32)

local registry = Registry()
local entity_4 = registry:create_entity()
entity_4:add_component(Transform(200, 200, 1, 1, 0.0))
entity_4:add_component(TextComponent("pixel", "testing from lua binding"))

local view = registry:get_entities(Transform)

view:for_each(function(entity)
	local transform = entity:get_component(Transform)
	local x, y = transform:get_position()
end)

-- local registry_2 = Registry(RegistryType.LUA)
-- local entity_4 = registry_2:create_entity()
-- entity_4:add_component(Transform(999.0, 999.0, 0.0))
-- local view_2 = registry_2:get_entities(Transform)
-- view_2:for_each(registry_2, function(entity)
-- 	local transform = entity:get_component(Transform)
-- 	local x, y = transform:get_position()
-- end)

main = {
	update = function()
		local transform = entity_1:get_component(Transform)
		if Keyboard.pressed(KEY_W) then
			transform.position.y = transform.position.y - 10
		elseif Keyboard.pressed(KEY_S) then
			transform.position.y = transform.position.y + 10
		elseif Keyboard.pressed(KEY_A) then
			transform.position.x = transform.position.x - 10
		elseif Keyboard.pressed(KEY_D) then
			transform.position.x = transform.position.x + 10
		end
	end,
}
