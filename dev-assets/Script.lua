Durian = require "Durian"

function OnStart()
    -- Durian.LogInfo(Durian.GetID())

    if Durian.HasTransform()
    then
        Durian.LogInfo("Has transform")
    else
        Durian.LogInfo("Has no transform, creatig one")
        Durian.AttachTransform()
    end
end

function OnUpdate(timestep)
    Durian.LogInfo(timestep)
end

function OnEnd()

end