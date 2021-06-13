-- stage script file

--[[

api: stage is a SDL2 implementation for lua, u can use these apis below to draw something on the stage ...

* window

* audio

* render
    setAuto : true, false auto render after drawing
    setBlend : 0 no blending, 1 alpha blending, 2 additive blending, 4 color modulate, 8 color multiply
    doRender : render manually after set auto false
    doClear : clear stage with current color
    setColor
    setScale
    setPort
    setClip
    drawPoint
    drawLine
    drawRect
    fillRect
    drawImage
    drawText

]]

print("stage lua file ...")

function Stage_start()
    print('lua Stage_start  ...')
    -- render.setClip(50, 50, 200, 200)
end

function Stage_stop()
    print('lua Stage_stop ...')
end

function Stage_before()
    -- print('lua Stage_before ...')
end

function Stage_handle()
    -- print('lua Stage_handle ...')
end

local x = 0;
local y = 100

function Stage_update()
    if x > 150 then
        render.setScale(1, 2)
        render.setBlend(1)
        render.setColor(100, 10, 10, 200)
    end
    x = x + 25;
end

function Stage_render()
    render.drawLine(x, y, 0, 0);
    render.drawPoint(x, y + 10);
    render.drawRect(x, y + 20, 20, 20);
    render.fillRect(x, y + 50, 20, 20);
end

function Stage_after()
    -- print('lua Stage_after ...')
end
