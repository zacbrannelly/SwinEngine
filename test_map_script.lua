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

