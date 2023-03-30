TransformComponent = {}
TransformComponent.__index = TransformComponent

setmetatable(TransformComponent, {
    __call = function(cls, ...)
        return cls.new(...)
    end,
})

function TransformComponent.new()
    Durian_AttachTransform()
    local self = setmetatable({
        Translation = { x = 0, y = 0 },
        Rotation = { x = 0, y = 0 },
        Scale = { x = 1, y = 1 }
    }, TransformComponent)
    return self
end

function TransformComponent:SetTranslation(x, y)
    self.Translation.x = x
    self.Translation.y = y
end

function TransformComponent:SetRotation(x, y)
    self.Rotation.x = x
    self.Rotation.y = y
end

function TransformComponent:SetScale(x, y)
    self.Scale.x = x
    self.Scale.y = y
end

function TransformComponent:GetTranslation()
    return self.Translation
end

function TransformComponent:GetRotation()
    return self.Rotation
end

function TransformComponent:GetScale()
    return self.Scale
end