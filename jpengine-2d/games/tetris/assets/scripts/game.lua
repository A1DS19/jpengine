Game = {}
Game.__index = Game

function Game:create(params)
	params = params or {}
	local this = {
		grid = params.grid or Grid:create({ num_rows = 17, offset = vec2(7, 1) }),
		current_tet = get_random_tetromino(),
		next_tet = get_random_tetromino(),
		game_timer = Timer(),
		drop_time = 2000,
		start_pos = vec2(0, 0),
		next_pos = vec2(0, 0),

		game_over = false,
		game_over_text = nil,

		score_label = nil,
		score_text = nil,
		score_value = 0,

		level_label = nil,
		level_text = nil,
		level = 1,

		lines_cleared = 0,
	}

	local grid_offset = this.grid.offset
	this.start_pos = vec2(grid_offset.x + math.floor(this.grid.num_cols / 2), grid_offset.y + 1)

	this.current_tet:move(this.start_pos.y, this.start_pos.x)

	this.next_pos = vec2(grid_offset.x + this.grid.num_cols + 3, 5)

	this.next_tet:move(this.next_pos.y, this.next_pos.x)

	this.game_over_text = Entity()
	this.game_over_text:add_component(Transform(vec2(400, 300), vec2(1, 1), 0))
	local text = this.game_over_text:add_component(TextComponent("pixel32", "Game Over"))
	text.hidden = true

	this.score_label = Entity()
	local score_transform = this.score_label:add_component(Transform(vec2(16, 32), vec2(1.5, 1.5), 0))
	this.score_label:add_component(TextComponent("pixel16", "Score: "))

	local score_text_w = j2d_measure_text("Score: ", "pixel16")
	this.score_text = Entity()
	this.score_text:add_component(
		Transform(vec2(score_transform.position.x + score_text_w, score_transform.position.y), vec2(1, 1), 0)
	)
	this.score_text:add_component(TextComponent("pixel16", "0"))

	local level_text_w = j2d_measure_text("Level: ", "pixel32")
	this.level_label = Entity()
	local level_transform =
		this.level_label:add_component(Transform(vec2(400 - (level_text_w / 2), 20), vec2(1.5, 1.5), 0))
	this.level_label:add_component(TextComponent("pixel32", "Level: "))

	this.level_text = Entity()
	this.level_text:add_component(
		Transform(vec2(level_transform.position.x + level_text_w, level_transform.position.y), vec2(1, 1), 0)
	)
	this.level_text:add_component(TextComponent("pixel32", "1"))

	this.game_timer:start()
	setmetatable(this, self)
	return this
end
