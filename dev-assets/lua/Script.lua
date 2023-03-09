require "DurianEngine"

Movement =
{
    Right = false,
    Left = false,
    Up = false,
    Down = false
}

Speed =
{
    x = 0.0,
    y = 0.0
}

function ProcessMovementInput()
    if Durian_EventKeyDown() == Durian.Keycode.DURIAN_SCANCODE_RIGHT
    then
        Movement.Right = true
    end
    if Durian_EventKeyDown() == Durian.Keycode.DURIAN_SCANCODE_LEFT
    then
        Movement.Left = true
    end
    if Durian_EventKeyDown() == Durian.Keycode.DURIAN_SCANCODE_UP
    then
        Movement.Up = true
    end
    if Durian_EventKeyDown() == Durian.Keycode.DURIAN_SCANCODE_DOWN
    then
        Movement.Down = true
    end

    if Durian_EventKeyUp() == Durian.Keycode.DURIAN_SCANCODE_RIGHT
    then
        Movement.Right = false
    end
    if Durian_EventKeyUp() == Durian.Keycode.DURIAN_SCANCODE_LEFT
    then
        Movement.Left = false
    end
    if Durian_EventKeyUp() == Durian.Keycode.DURIAN_SCANCODE_UP
    then
        Movement.Up = false
    end
    if Durian_EventKeyUp() == Durian.Keycode.DURIAN_SCANCODE_DOWN
    then
        Movement.Down = false
    end
end

function ProcessMovement(timestep)
    gravity = 9.81

    Speed.y = Speed.y + gravity

    Durian.Transform.Translation.y = Durian.Transform.Translation.y + Speed.y * timestep
    Durian.Transform.Translation.x = Durian.Transform.Translation.x + Speed.x * timestep

    if Speed.x > 0
    then
        Speed.x = Speed.x - 1
    else
        Speed.x = Speed.x + 1
    end
    if Speed.y > 0
    then
        Speed.y = Speed.y - 1
    else
        Speed.y = Speed.y + 1
    end
end

function ProcessScreenBoundaries()
    width, height = Durian_EventWindowSize()
    Durian_LogInfo(width .. " " .. height)

    if Durian.Transform.Translation.x > width / 2
    then
        Durian.Transform.Translation.x = width / 2
        Speed.x = 0;
    end
    if Durian.Transform.Translation.x < -(width / 2)
    then
        Durian.Transform.Translation.x = -(width / 2)
        Speed.x = 0;
    end
    if Durian.Transform.Translation.y > height / 2
    then
        Durian.Transform.Translation.y = height / 2
        Speed.y = 0;
    end
    if Durian.Transform.Translation.y < -(height / 2)
    then
        Durian.Transform.Translation.y = -(height / 2)
        Speed.y = 0;
    end
end

function OnStart()
    Durian.Transform.Scale.x = 64
    Durian.Transform.Scale.y = 64
end

function OnUpdate(timestep)
    ProcessMovementInput()
    ProcessMovement(timestep);
    ProcessScreenBoundaries();

    if Movement.Right
    then
        Speed.x = Speed.x + 5
    end
    if Movement.Left
    then
        Speed.x = Speed.x - 5
    end
    if Movement.Up
    then
        Speed.y = Speed.y - 100
    end
    if Movement.Down
    then
        Durian.Transform.Translation.y = Durian.Transform.Translation.y + 1
    end
end