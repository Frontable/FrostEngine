Player = {
    speed = 100.0
}

function Player:onCreate()
    --print("Player created", self.entity)
end

function Player:onUpdate(dt)
    local x = get_position_x(self.entity)
    local y = get_position_y(self.entity)
    x = x + self.speed * dt
    set_position(self.entity, x, y)
end