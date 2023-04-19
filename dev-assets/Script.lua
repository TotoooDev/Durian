Durian = require "Durian"

function OnStart()
    Durian.LogInfo("Entity ID: " .. Durian.GetID())
end

function OnUpdate(timestep)
    -- Durian.LogInfo(timestep)
    
    local transform = Durian.GetTransform()
    transform.Translation.ChangeX(5)
    transform.Scale.ChangeX(5)
end

function OnEnd()

end