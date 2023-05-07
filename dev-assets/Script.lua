Durian = require "Durian"

function OnStart()
    Durian.LogInfo("Entity ID: " .. Durian.GetID())
    tag = Durian.GetTag()
    Durian.LogInfo(tostring(tag)) -- TODO: We need to use tostring() to call __tostring (the metamethod), maybe there is a way to call the metamethod in C++?
    tr = Durian.GetTransform()
    Durian.LogInfo(tostring(tr))
end

function OnUpdate(timestep)
    -- Durian.LogInfo(timestep)
end

function OnEnd()

end