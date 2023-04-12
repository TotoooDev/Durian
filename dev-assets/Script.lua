Durian = require "Durian"

function OnStart()
    Durian.LogInfo(Durian.GetID())
end

function OnUpdate(timestep)
    Durian.LogInfo(timestep)
end

function OnEnd()

end