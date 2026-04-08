j2d_run_script("assets/scripts/defs/asset-defs.lua")
j2d_run_script("assets/scripts/block.lua")
j2d_run_script("assets/scripts/grid.lua")
j2d_run_script("assets/scripts/utils.lua")
j2d_run_script("assets/scripts/tetromino.lua")

load_assets(asset_defs)

gGrid = Grid:create()

main = {
	update = function() end,
}
