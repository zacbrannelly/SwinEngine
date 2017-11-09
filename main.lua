function main.SetupWindow(window)
	window.Title = "Test Game"
	window.Width = 800
	window.Height = 600
	window.Resizable = false
end

function main.LoadMaps(mapLoader, stateManager)
	-- Load the test map
	if mapLoader:IsValid("test_map.json") then
		local testMap = mapLoader:LoadMap("test_map.json")

		-- Register the map to a state and set that as the current state
		stateManager:RegisterMap("main", testMap)
		stateManager.State = "main"
	end
	
end

