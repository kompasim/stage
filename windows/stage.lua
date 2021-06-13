-- stage script file

--[[

api: stage is a SDL2 implementation for lua, u can use these apis below to draw something on the stage ...

* window
    show
    hide
    maximaze
    minimaze
    setTitle
    getTitle
    setPosition
    getPosition
    setSize
    getSize
    setFullscreen
    showCursor
    setCursor
    setIcon
    setOpacity

* audio
    initAudio
    playMusic
    playSound
    pauseAudio
    resumeAudio
    endAudio

* render
    setAuto : true, false auto render after drawing
    setBlend : 0 no blending, 1 alpha blending, 2 additive blending, 4 color modulate, 8 color multiply
    doRender : render manually after set auto false
    doClear : clear stage with current color
    setColor
    getColor
    setScale
    getScale
    setPort
    getPort
    setClip
    getClip
    drawPoint
    drawLine
    drawRect
    fillRect
    drawImage
    drawText

]]

print("lua Stage file ...")

function Stage_start()
    print('lua Stage_start  ...')
    --
    audio.initAudio()
    audio.playMusic('./road.wav', 100)
    -- 
    render.setColor(10, 10, 10, 200)
    render.doClear()
    -- 
    --
    render.setColor(200, 0, 150, 255)
    render.fillRect(225, 375, 50, 50)
    --
    render.setColor(200, 150, 0, 255)
    render.drawRect(300, 375, 50, 50)
    --
    render.setColor(0, 200, 150, 255);
    render.drawLine(10, 475, 380, 475);
    -- 
    render.drawImage("./lua.png", 0, 0, 0, 0, 100, 375, 0, 0, false, false, 0, 0.5, 0.5)
    --
    render.setColor(200, 200, 0, 255)
    local text1 = "Hello World!"
    local text2 = "!ﺎﻴﻧﯗﺩ ﺎﺑﺎﮬﺭﻪﻣ"
    local font = "ukij.ttf";
    render.drawText(text1, 0, 0, 0, 0, 300, 225, 0, 0, font, 24, true, false, 0, 0.5, 0.5)
    render.drawText(text1, 0, 0, 0, 0, 300, 275, 0, 0, font, 24, false, false, 0, 0.5, 0.5)
    render.drawText(text2, 0, 0, 0, 0, 300, 325, 0, 0, font, 24, false, false, 0, 0.5, 0.5)
    --
    render.setColor(200, 250, 250, 200)
    --
    window.setIcon("app.png")
    window.setCursor(11)
    window.setTitle(string.format("Stage %s", os.date("%Y-%m-%d  %H-%M-%S", os.time())))
    --
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
local y = 200

function Stage_update()
    if x > 150 then
        render.setColor(100, 10, 10, 200)
        y = 100
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
