Durian = require "Durian"

function OnStart()
    Durian.LogInfo("Entity ID: " .. Durian.GetID())
    tag = Durian.GetTag()
    Durian.LogInfo(tag)
end

function OnUpdate(timestep)
    -- Durian.LogInfo(timestep)
end

function OnEnd()

end