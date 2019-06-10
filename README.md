# SwinEngine
Basic 2D Game Engine with minimal scripting.

## Technologies used
- SDL - Display creation
- OpenGL - Rendering
- Lua - Scripting
- JSON - Map/World representation

Built for an assignment where I wrote a tutorial on creating a 2D Game Engine in C++.

The tutorial can be seen here: [How to create a 2D Game Engine in C++ using OpenGL, SDL, Lua, and JSON](https://101668878.bitbucket.io/GameEngineTutorial/).

## Example
Example `main.lua` code:
```lua
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
```

Example map/world (`test_map.json`):
```
{
	"name": "test_map",
	"backgroundColor": [ 0.0, 0.0, 0.0 , 1.0 ],
	"scriptPath": "test_map_script.lua",
	"scriptName": "test_map",
	"objects": [
		{
			"name": "test rectangle",
			"position": [0, 0],
			"type": "rectangle",
			"width": 100,
			"height": 100,
			"color": [1, 0, 0, 1]
		},
		{
			"name": "test circle",
			"position": [0, 0],
			"type": "circle",
			"radius": 50,
			"color": [1, 1, 1, 1]
		}
	]
}
```

Example map/world script code:
```lua
function test_map.Initialize(map)
	local rectangle = map:GetObject("test rectangle")
	
	rectangle.Position = vec2(400 - 25, 300 - 25)
	rectangle.Origin = vec2(50, 50)
	rectangle.AngularVelocity = 0.05	

	test_map.counter = 0
end

function test_map.Update(map)
	
	local rectangle = map:GetObject("test rectangle")
		
	test_map.counter = test_map.counter + 0.05
	
	if Keyboard.IsKeyDown("left") then
		rectangle.Velocity = vec2(-5, 0)
	elseif Keyboard.IsKeyDown("right") then
		rectangle.Velocity = vec2(5, 0)
	end
	
	if rectangle.Position.x + rectangle.Velocity.x <= 0 then
		rectangle.Velocity = vec2(5, 0)
	elseif rectangle.Position.x + rectangle.Width + rectangle.Velocity.x >= 800 then
		rectangle.Velocity = vec2(-5, 0)
	end
end

function test_map.Render(renderingContext, interpolation)

end
```

Result:

![](https://101668878.bitbucket.io/GameEngineTutorial/How%20to%20create%20a%202D%20Game%20Engine%20in%20C_files/image130.jpg)

This example code results in a stationary circle and a rotating rectangle that bounces off the walls or changes horizontal direction when the left/right keys are pressed.
