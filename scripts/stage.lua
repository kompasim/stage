--[[

    stage script file

-- api: stage is a SDL2 implementation for lua, u can use these apis below to draw something on the stage ...

-- stage
    -- getVersion
    -- doExit
    -- doDelay
    -- getTick
    -- setClipboard
    -- getClipboard
    -- saveScreenshot

--  window
    -- show
    -- hide
    -- maximaze
    -- minimaze
    -- setTitle
    -- getTitle
    -- setPosition
    -- getPosition
    -- setSize
    -- getSize
    -- setFullscreen
    -- showCursor
    -- setCursor
    -- setIcon
    -- setOpacity

-- audio
    -- initAudio
    -- playMusic
    -- playSound
    -- pauseAudio
    -- resumeAudio
    -- endAudio

-- render
    -- setAuto : true, false auto render after drawing
    -- setBlend : 0 no blending, 1 alpha blending, 2 additive blending, 4 color modulate, 8 color multiply
    -- doRender : render manually after set auto false
    -- doClear : clear stage with current color
    -- setColor
    -- getColor
    -- setScale
    -- getScale
    -- setPort
    -- getPort
    -- setClip
    -- getClip
    -- drawPoint
    -- drawLine
    -- drawRect
    -- fillRect
    -- drawImage
    -- drawText

]]

print("lua Stage file ...")

function Stage_start()
    -- print('lua Stage_start [call once when program start] ...')
    --
    audio.initAudio()
    audio.playMusic('./others/road.wav', 100)
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
    render.drawImage("./others/lua.png", 0, 0, 0, 0, 100, 375, 0, 0, false, false, 0, 0.5, 0.5)
    --
    render.setColor(200, 200, 0, 255)
    local text1 = "Hello World!"
    local text2 = "!ﺎﻴﻧﯗﺩ ﺎﺑﺎﮬﺭﻪﻣ"
    local font = "./others/ukij.ttf";
    render.drawText(text1, 0, 0, 0, 0, 300, 225, 0, 0, font, 24, true, false, 0, 0.5, 0.5)
    render.drawText(text1, 0, 0, 0, 0, 300, 275, 0, 0, font, 24, false, false, 0, 0.5, 0.5)
    render.drawText(text2, 0, 0, 0, 0, 300, 325, 0, 0, font, 24, false, false, 0, 0.5, 0.5)
    --
    render.setColor(200, 250, 250, 200)
    --
    window.setIcon("./others/app.png")
    window.setCursor(11)
    window.setTitle(string.format("Stage %s", os.date("%Y-%m-%d  %H-%M-%S", os.time())))
    --
end

function Stage_stop()
    -- print('lua Stage_stop [call once when program stop] ...')
end

function Stage_before()
    -- print('lua Stage_before [call when per frame start] ...')
end

function Stage_handle(name, value)
    -- print('lua Stage_handle [call when receive an event] ...')
    if name == "SDL_QUIT" then
        stage.doExit()
    elseif name == "SDL_WINDOWEVENT" then
        -- window event, value is event type
    elseif name == "SDL_CLIPBOARDUPDATE" then
        -- clipboard update
    elseif name == "SDL_DROPFILE" then
        -- drop file, value is file name
    elseif name == "SDL_KEYDOWN" then
        -- keyboard down, key: F1
    elseif name == "SDL_KEYUP" then
        -- keyboard up
    elseif name == "SDL_MOUSEBUTTONDOWN" then
        -- mouse down, button : 1
    elseif name == "SDL_MOUSEBUTTONUP" then
        -- mouse up
    elseif name == "SDL_MOUSEMOTION" then
        -- mouse move, position: value.x, value.y
    elseif name == "SDL_MOUSEWHEEL" then
        -- mouse wheel, direction: forward 1, backward -1
    end
    -- print("-->event:", name, value)
end

local x = 0;
local y = 200

local aniIndex = 0
local aniCount = 15
local aniX = 475
local aniY = 325
local aniBg = 75
local aniSpeed = 0.5

function Stage_update()
    -- print('lua Stage_update [call every frame to update] ...')
    if x > 150 then
        render.setColor(100, 10, 10, 200)
        y = 100
    end
    x = x + 25;
    --
    aniIndex = aniIndex > aniCount and 1 or aniIndex + 1 * aniSpeed
end

function Stage_render()
    -- print('lua Stage_render [call every frame to draw] ...')
    render.drawLine(x, y, 0, 0);
    render.drawPoint(x, y + 10);
    render.drawRect(x, y + 20, 20, 20);
    render.fillRect(x, y + 50, 20, 20);
    --
    render.setColor(255, 255, 255, 255)
    render.fillRect(aniX - aniBg, aniY - aniBg, aniBg * 2, aniBg * 2);
    render.drawImage(string.format("./others/animations/img_%02d.jpg", math.floor(aniIndex)), 0, 0, 0 , 0, aniX, aniY, 0, 0, false, false, 0, 0.5, 0.5)
end

function Stage_after()
    -- print('lua Stage_after [call when per frame end] ...')
end
