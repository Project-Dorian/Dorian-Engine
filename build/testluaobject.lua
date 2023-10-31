X = 10
Y = 10

function draw()
    DrawRect(X, Y, 100, 100)
end

function update()
    if (InputDown(3)) then X = X + GetDeltaTime()*20 end
    if (InputDown(2)) then X = X - GetDeltaTime()*20 end
    if (InputDown(1)) then Y = Y + GetDeltaTime()*20 end
    if (InputDown(0)) then Y = Y - GetDeltaTime()*20 end
end