rX = 60*math.pi/180
rY = 0
rZ = 0

closeness = 3

Points = {{-1, -1, -1}, {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1}, {1, 1, -1}, {1, -1, -1}, {1, -1, 1}, {1, 1, 1}}

function draw()
    local DrawPoints = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
    for i = 1, 8, 1 do
        -- Displacing points based on rotation
        local dX = math.cos(rY)*(math.sin(rZ)*Points[i][2]+math.cos(rZ)*Points[i][1])-math.sin(rY)*(Points[i][3])
        local dY = math.sin(rX)*(math.cos(rY)*Points[i][3]+math.sin(rY)*(math.sin(rZ)*Points[i][2]+math.cos(rZ)*Points[i][1]))+math.cos(rX)*(math.cos(rZ)*Points[i][2]-math.sin(rZ)*Points[i][1])
        local dZ = math.cos(rX)*(math.cos(rY)*Points[i][3]+math.sin(rY)*(math.sin(rZ)*Points[i][2]+math.cos(rZ)*Points[i][1]))-math.sin(rX)*(math.cos(rZ)*Points[i][2]-math.sin(rZ)*Points[i][1])+closeness

        -- Projecting onto Screen
        DrawX = (dX*WindowWidth())/(dZ*WindowWidth()/60)
        DrawY = (dY*WindowHeight())/(dZ*WindowHeight()/60)

        DrawPoints[i][1] = WindowWidth()/2+(DrawX)
        DrawPoints[i][2] = WindowHeight()/2+(DrawY)
    end

    DrawQuad(DrawPoints[1][1], DrawPoints[1][2], DrawPoints[2][1], DrawPoints[2][2], DrawPoints[4][1], DrawPoints[4][2], DrawPoints[3][1], DrawPoints[3][2])
    DrawQuad(DrawPoints[5][1], DrawPoints[5][2], DrawPoints[6][1], DrawPoints[6][2], DrawPoints[8][1], DrawPoints[8][2], DrawPoints[7][1], DrawPoints[7][2])
    DrawQuad(DrawPoints[4][1], DrawPoints[4][2], DrawPoints[5][1], DrawPoints[5][2], DrawPoints[3][1], DrawPoints[3][2], DrawPoints[8][1], DrawPoints[8][2])
    DrawQuad(DrawPoints[1][1], DrawPoints[1][2], DrawPoints[2][1], DrawPoints[2][2], DrawPoints[6][1], DrawPoints[6][2], DrawPoints[7][1], DrawPoints[7][2])
    DrawQuad(DrawPoints[1][1], DrawPoints[1][2], DrawPoints[4][1], DrawPoints[4][2], DrawPoints[5][1], DrawPoints[5][2], DrawPoints[7][1], DrawPoints[7][2])
    DrawQuad(DrawPoints[1][1], DrawPoints[1][2], DrawPoints[4][1], DrawPoints[4][2], DrawPoints[6][1], DrawPoints[6][2], DrawPoints[5][1], DrawPoints[5][2])
end

function update()
    rZ = rZ + GetDeltaTime()*50*math.pi/360

    if (InputDown(1)) then closeness = closeness + GetDeltaTime() end
    if (InputDown(0)) then closeness = closeness - GetDeltaTime() end
end