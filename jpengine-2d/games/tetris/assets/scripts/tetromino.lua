Tetromino = {}

function Tetromino:create(params)
	params = params or {}
	local this = {
		etype = params.etype or ETetrominoType.LType,
		blocks = {},
		row_offset = 0,
		col_offset = 0,
		rotation_state = 1,
		color = params.color or get_random_color(),
		num_states = params.num_states or 4,
		states = params.states or {},
		binitialized = false,
	}

	setmetatable(this, self)
	self.__index = self
	return this
end

function Tetromino:rotate_clockwise()
	self.rotation_state = self.rotation_state + 1
	if self.rotation_state == self.num_states + 1 then
		self.rotation_state = 1
	end
end

function Tetromino:rotate_counter_clockwise()
	self.rotation_state = self.rotation_state - 1
	if self.rotation_state == 0 then
		self.rotation_state = self.num_states
	end
end

function Tetromino:get_block_positions()
	local moved_tiles = {}
	for i = 1, #self.blocks do
		local block = self.blocks[i]
		local pos = Position:create(block.row + self.row_offset, block.col + self.col_offset)
		moved_tiles[i] = pos
	end

	return moved_tiles
end

function Tetromino:can_move(grid, row, col)
	local positions = self:get_block_positions()
	for i = 1, #positions do
		local pos = positions[i]
		if not grid:inside_grid(pos.row + row - grid.offset.y, pos.col + col - grid.offset.x) then
			return false
		end

		if not grid:is_cell_empty(pos.row + row - grid.offset.y, pos.col + col - grid.offset.x) then
			return false
		end
	end

	return true
end

function Tetromino:can_rotate(grid, cw)
	local tetromino = deep_clone(self)
	if cw then
		tetromino:rotate_clockwise()
	else
		tetromino:rotate_counter_clockwise()
	end

	local curr_state = tetromino.states[tetromino.rotation_state]
	for i = 1, #tetromino.blocks do
		local block = tetromino.blocks[i]
		local pos = curr_state[i]
		block.row = pos.row
		block.col = pos.col
	end

	local positions = tetromino:get_block_positions()
	for i = 1, #positions do
		local pos = positions[i]
		if not grid:inside_grid(pos.row - grid.offset.y, pos.col - grid.offset.x) then
			return false
		end

		if not grid:is_cell_empty(pos.row - grid.offset.y, pos.col - grid.offset.x) then
			return false
		end
	end

	return true
end

function Tetromino:move(rows, cols)
	self.row_offset = self.row_offset + rows
	self.col_offset = self.col_offset + cols

	for i = 1, #self.blocks do
		self.blocks[i]:set_position(self.row_offset, self.col_offset)
	end
end

function Tetromino:do_rotate_clockwise()
	self:rotate_clockwise()
	local curr_state = self.states[self.rotation_state]
	for i = 1, #self.blocks do
		local block = self.blocks[i]
		local pos = curr_state[i]
		block.row = pos.row
		block.col = pos.col
		block:set_position(self.row_offset, self.col_offset)
	end
end

function Tetromino:do_rotate_counter_clockwise()
	self:rotate_counter_clockwise()
	local curr_state = self.states[self.rotation_state]
	for i = 1, #self.blocks do
		local block = self.blocks[i]
		local pos = curr_state[i]
		block.row = pos.row
		block.col = pos.col
		block:set_position(self.row_offset, self.col_offset)
	end
end

function Tetromino:init_blocks()
	if self.binitialized then
		print("error: tetromino blocks already initialized")
		return
	end

	for i = 1, #self.blocks do
		local block = self.blocks[i]
		block.entity = Entity()
		block.entity:add_component(
			Transform(vec2(block.col * block.cell_size, block.row * block.cell_size), vec2(1, 1), 0.0)
		)

		local sprite = block.entity:add_component(Sprite("blocks", 32, 32, 1, 1, 0, self.color))

		sprite:generate_uvs(64, 32)
	end

	self.binitialized = true
end

function Tetromino:init()
	-- to be overriden
end

function Tetromino:reset()
	self.row_offset = 0
	self.col_offset = 0
	self.rotation_state = 1
end

function Tetromino:lock_to_grid(grid)
	local positions = self:get_block_positions()
	for i = 1, #self.blocks do
		local block = self.blocks[i]
		local position = positions[i]
		if not grid:set_cell(position.row - grid.offset.y, position.col - grid.offset.x, block) then
			return false
		end
	end

	return true
end

JTetromino = setmetatable({}, { __index = Tetromino })

function JTetromino:create()
	local this = Tetromino.create(self, {
		etype = ETetrominoType.JType,
		num_states = 4,
	})

	setmetatable(this, self)
	self.__index = self
	return this
end

function JTetromino:init()
	self.blocks[1] = Block:create({ row = 2, col = 0 })
	self.blocks[2] = Block:create({ row = 2, col = 1 })
	self.blocks[3] = Block:create({ row = 1, col = 1 })
	self.blocks[4] = Block:create({ row = 0, col = 1 })

	self.states[1] = {
		[1] = Position:create(2, 0),
		[2] = Position:create(2, 1),
		[3] = Position:create(1, 1),
		[4] = Position:create(0, 1),
	}

	self.states[2] = {
		[1] = Position:create(0, 0),
		[2] = Position:create(1, 0),
		[3] = Position:create(1, 1),
		[4] = Position:create(1, 2),
	}

	self.states[3] = {
		[1] = Position:create(0, 2),
		[2] = Position:create(0, 1),
		[3] = Position:create(1, 1),
		[4] = Position:create(2, 1),
	}

	self.states[4] = {
		[1] = Position:create(2, 2),
		[2] = Position:create(1, 2),
		[3] = Position:create(1, 1),
		[4] = Position:create(1, 0),
	}

	self:init_blocks()
end
