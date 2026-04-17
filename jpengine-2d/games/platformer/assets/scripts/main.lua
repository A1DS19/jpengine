j2d_run_script("assets/scripts/defs/asset-defs.lua")
j2d_run_script("assets/scripts/utils.lua")
j2d_run_script("assets/scripts/entities.lua")

load_assets(asset_defs)

MusicPlayer.set_volume(0.4)
MusicPlayer.play("the-field-of-dreams", -1)
SoundPlayer.set_volume(0.8, 0)
SoundPlayer.set_volume(0.8, 1)

local level = {
	spawn = { x = 60, y = 440 },
	platforms = {
		{ x = 0, y = 568, w = 800, h = 32 },
		{ x = 140, y = 480, w = 120, h = 16 },
		{ x = 340, y = 400, w = 120, h = 16 },
		{ x = 540, y = 320, w = 120, h = 16 },
		{ x = 260, y = 280, w = 120, h = 16 },
	},
	coins = {
		{ x = 190, y = 440 },
		{ x = 390, y = 360 },
		{ x = 590, y = 280 },
		{ x = 310, y = 240 },
	},
	goal = { x = 700, y = 520 },
}

local game = {
	score = 0,
	coin_count = #level.coins,
	won = false,
	debug = false,
	player = nil,
	platforms = {},
	coins = {},
	goal = nil,
	score_text = nil,
	status_text = nil,
	hint_text = nil,
	coin_spin = 0,
}

local function build_level()
	game.player = create_player(level.spawn)

	for i = 1, #level.platforms do
		table.insert(game.platforms, create_platform(level.platforms[i]))
	end

	for i = 1, #level.coins do
		local coin = create_coin(level.coins[i])
		game.coins[coin.id] = coin
	end

	game.goal = create_goal(level.goal)

	game.score_text = create_hud_text({ x = 16, y = 16 }, "COINS 0 / " .. game.coin_count)
	game.hint_text = create_hud_text({ x = 16, y = 560 }, "A/D move  SPACE jump  F1 debug  R reset")
	game.status_text = create_hud_text({ x = 260, y = 60 }, "")
	game.status_text.entity:get_component(TextComponent).hidden = true
end

local function reset_level()
	if game.player then
		game.player.entity:destroy()
	end
	for _, p in pairs(game.platforms) do
		p.entity:destroy()
	end
	for _, c in pairs(game.coins) do
		c.entity:destroy()
	end
	if game.goal then
		game.goal.entity:destroy()
	end
	if game.score_text then
		game.score_text.entity:destroy()
	end
	if game.hint_text then
		game.hint_text.entity:destroy()
	end
	if game.status_text then
		game.status_text.entity:destroy()
	end

	game.score = 0
	game.won = false
	game.player = nil
	game.platforms = {}
	game.coins = {}
	game.goal = nil

	build_level()
end

local function update_player_movement()
	local physics = game.player.entity:get_component(PhysicsComp)
	local v = physics:get_linear_velocity()
	local move_x = 0
	local speed = 7

	if Keyboard.pressed(KEY_A) or Keyboard.pressed(KEY_LEFT) then
		move_x = -speed
	elseif Keyboard.pressed(KEY_D) or Keyboard.pressed(KEY_RIGHT) then
		move_x = speed
	end

	physics:set_linear_velocity(vec2(move_x, v.y))

	local transform = game.player.entity:get_component(Transform)
	local pos = transform.position
	local ground_hit = physics:cast_ray(vec2(pos.x + 16, pos.y + 33), vec2(pos.x + 16, pos.y + 44))
	local on_ground = ground_hit ~= nil

	if on_ground and (Keyboard.just_pressed(KEY_SPACE) or Keyboard.just_pressed(KEY_W)) then
		physics:set_linear_velocity(vec2(v.x, -18))
		SoundPlayer.play("menu-accept", 0, 0)
	end
end

local function handle_pickups()
	if game.won then
		return
	end

	local physics = game.player.entity:get_component(PhysicsComp)
	local transform = game.player.entity:get_component(Transform)
	local pos = transform.position

	local hits = physics:box_trace(vec2(pos.x + 2, pos.y + 2), vec2(pos.x + 30, pos.y + 30))

	if not hits then
		return
	end

	for i = 1, #hits do
		local obj = hits[i]
		if obj.tag == "coin" then
			local coin = game.coins[obj.entity_id]
			if coin then
				coin.entity:destroy()
				game.coins[obj.entity_id] = nil
				game.score = game.score + 1
				SoundPlayer.play("menu-accept", 0, 1)
			end
		elseif obj.tag == "goal" and not game.won then
			local tc = game.status_text.entity:get_component(TextComponent)
			if game.score == game.coin_count then
				game.won = true
				tc.text = "YOU WIN!"
				tc.color = J2D_YELLOW
			else
				tc.text = "GET ALL COINS!"
				tc.color = J2D_RED
			end
			tc.hidden = false
		end
	end
end

local function refresh_hud()
	local score_tc = game.score_text.entity:get_component(TextComponent)
	score_tc.text = "COINS " .. game.score .. " / " .. game.coin_count
end

local function draw_world()
	for i = 1, #game.platforms do
		local p = game.platforms[i]
		local r = p.rect
		draw_rect(Rect(vec2(r.x, r.y), vec2(r.w, r.h), p.color, false))
		draw_rect(Rect(vec2(r.x, r.y), vec2(r.w, r.h), J2D_BLACK, true))
	end

	game.coin_spin = game.coin_spin + 0.08
	local bob = math.sin(game.coin_spin) * 2
	for _, coin in pairs(game.coins) do
		local c = coin.center
		draw_circle(Circle(vec2(c.x, c.y + bob), 10, J2D_YELLOW, 16, false))
		draw_circle(Circle(vec2(c.x, c.y + bob), 10, Color(120, 90, 0, 255), 16, true))
	end

	if game.goal then
		local g = game.goal.rect
		local flag_color = game.won and J2D_YELLOW or J2D_GREEN
		draw_rect(Rect(vec2(g.x, g.y), vec2(g.w, g.h), flag_color, false))
		draw_line(Line(vec2(g.x + g.w * 0.5, g.y), vec2(g.x + g.w * 0.5, g.y + g.h), J2D_WHITE))
	end
end

local function draw_debug()
	if not game.debug then
		return
	end

	local transform = game.player.entity:get_component(Transform)
	local pos = transform.position
	local collider = game.player.entity:get_component(CircleCollider)
	draw_circle(Circle(vec2(pos.x + 16, pos.y + 16), collider.radius, J2D_RED, 24, true))

	draw_line(Line(vec2(pos.x + 16, pos.y + 33), vec2(pos.x + 16, pos.y + 44), J2D_MAGENTA))

	for i = 1, #game.platforms do
		local r = game.platforms[i].rect
		draw_rect(Rect(vec2(r.x, r.y), vec2(r.w, r.h), J2D_RED, true))
	end
end

local function check_fell_off()
	if not game.player then
		return
	end
	local pos = game.player.entity:get_component(Transform).position
	if pos.y > 700 then
		reset_level()
	end
end

build_level()

main = {
	update = function()
		if Keyboard.just_pressed(KEY_F1) then
			game.debug = not game.debug
		end

		if Keyboard.just_pressed(KEY_R) then
			reset_level()
			return
		end

		if not game.won then
			update_player_movement()
			handle_pickups()
		else
			local physics = game.player.entity:get_component(PhysicsComp)
			local v = physics:get_linear_velocity()
			physics:set_linear_velocity(vec2(0, v.y))
		end

		check_fell_off()
		refresh_hud()
		draw_world()
		draw_debug()
	end,
}
