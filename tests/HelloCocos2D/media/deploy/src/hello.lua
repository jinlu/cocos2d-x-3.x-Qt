-- package.path = package.path .. './src/?.lua;./?.lua'

require "Cocos2d"
require "Cocos2dConstants"

require "persistence"

color = {    
    r = 1,
    g = 1,
    b = 0 
}

print(" color is defined!")

-- cclog
cclog = function(...)
    print(string.format(...))
end

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    cclog("----------------------------------------")
    cclog("LUA ERROR: " .. tostring(msg) .. "\n")
    cclog(debug.traceback())
    cclog("----------------------------------------")
end

function string.split(str,comma)

    local arr = {}
    
    local expr = "([^"..comma.."]+)"    
    for word in string.gmatch(str, expr) do
        table.insert(arr,word)
    end
    
    return arr
    
end

local gSprite = nil
local gPath = nil

local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)

    --support debug,when used on ios7.1 64bit,these codes should be commented
    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
--    if (cc.PLATFORM_OS_IPHONE == targetPlatform) or (cc.PLATFORM_OS_IPAD == targetPlatform) or
--       (cc.PLATFORM_OS_ANDROID == targetPlatform) or (cc.PLATFORM_OS_WINDOWS == targetPlatform) or
--       (cc.PLATFORM_OS_MAC == targetPlatform) then
--        local host = 'localhost' -- please change localhost to your PC's IP for on-device debugging
--        require('src/mobdebug').start(host)
--    end
    require "src/hello2"
    cclog("result is " .. myadd(1, 1))

    ---------------

    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local origin = cc.Director:getInstance():getVisibleOrigin()


    -- create farm
    local function createLayerFarm()

        local layerFarm = cc.Layer:create()

        -- add in farm background
        local bg = cc.Sprite:create("res/farm.jpg")
        bg:setPosition(origin.x + visibleSize.width / 2 + 80, origin.y + visibleSize.height / 2)
        layerFarm:addChild(bg)
        
        -- add land sprite
        for i = 0, 3 do
            for j = 0, 1 do
                local spriteLand = cc.Sprite:create("res/land.png")
                spriteLand:setPosition(200 + j * 180 - i % 2 * 90, 10 + i * 95 / 2)
                layerFarm:addChild(spriteLand)
            end
        end

        -- add crop
        local frameCrop = cc.SpriteFrame:create("res/crop.png", cc.rect(0, 0, 105, 95))
        for i = 0, 3 do
            for j = 0, 1 do
                local spriteCrop = cc.Sprite:createWithSpriteFrame(frameCrop);
                spriteCrop:setPosition(10 + 200 + j * 180 - i % 2 * 90, 30 + 10 + i * 95 / 2)
                layerFarm:addChild(spriteCrop)
            end
        end

        -- handing touch events
        local function onTouchBegan(touch, event)

        end
        print(" handing touch events")

        local function onTouchMoved(touch, event)

        end

        local function onTouchEnded(touch, event)
            
        end


        local listener = cc.EventListenerTouchOneByOne:create()
        listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
        listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
        listener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
        local eventDispatcher = layerFarm:getEventDispatcher()
        eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layerFarm)

        return layerFarm
    end


    -- create menu
    local function createLayerMenu()
        local layerMenu = cc.Layer:create()

        local menuPopup, menuTools, effectID

        local function menuCallbackClosePopup()
            -- stop test sound effect
            cc.SimpleAudioEngine:getInstance():stopEffect(effectID)
            menuPopup:setVisible(false)
        end

        local function menuCallbackOpenPopup()
            -- loop test sound effect
            local effectPath = cc.FileUtils:getInstance():fullPathForFilename("res/effect1.wav")
            effectID = cc.SimpleAudioEngine:getInstance():playEffect(effectPath)
            menuPopup:setVisible(true)
        end

        -- add a popup menu
        local menuPopupItem = cc.MenuItemImage:create("res/menu2.png", "res/menu2.png")
        menuPopupItem:setPosition(0, 0)
        menuPopupItem:registerScriptTapHandler(menuCallbackClosePopup)
        menuPopup = cc.Menu:create(menuPopupItem)
        menuPopup:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)
        menuPopup:setVisible(false)
        layerMenu:addChild(menuPopup)
        
        -- add the left-bottom "tools" menu to invoke menuPopup
        local menuToolsItem = cc.MenuItemImage:create("res/menu1.png", "res/menu1.png")
        menuToolsItem:setPosition(0, 0)
        menuToolsItem:registerScriptTapHandler(menuCallbackOpenPopup)
        menuTools = cc.Menu:create(menuToolsItem)
        local itemWidth = menuToolsItem:getContentSize().width
        local itemHeight = menuToolsItem:getContentSize().height
        menuTools:setPosition(origin.x + itemWidth/2, origin.y + itemHeight/2)
        layerMenu:addChild(menuTools)

        return layerMenu
    end

    -- play background music, preload effect


--    cc.SimpleAudioEngine:getInstance():playMusic(bgMusicPath, true)
--    local effectPath = cc.FileUtils:getInstance():fullPathForFilename("res/effect1.wav")
--    cc.SimpleAudioEngine:getInstance():preloadEffect(effectPath)

    -- run
    local sceneGame = cc.Scene:create()
    sceneGame:addChild(createLayerFarm())
    sceneGame:addChild(createLayerMenu())

    --ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("res/BillmanDemo/BillmanDemo.ExportJson")
    
    global_config = persistence.load("../Resources/src/config.lua")
    
    print("-----config.lua------")
    print(global_config.unitData.speed)
    print(global_config.skillData.attack_4.skillname)
    print("-----config.lua end ------")

    cc.Director:getInstance():runWithScene(sceneGame)

    local function onEvent()

        -- print("on Event")
        
        -- print(color.r)
        -- print(color.g)
        -- print(color.b)

        -- clear sprite

        if (gPath) then
            ccs.ArmatureDataManager:getInstance():removeArmatureData(gPath)
        end

        
        if (gSprite) then
            gSprite:removeFromParent()
        end


        -- get path
        gPath = dd.LuaBridge:getInstance():getPath() 
        -- print("path : [" .. gPath.."]")

        -- create armature
        if (gPath) then
            ccs.ArmatureDataManager:getInstance():addArmatureFileInfo(gPath)

            string.sub(gPath,1,string.len(gPath) - 11)

            -- get armature name 
            local array = string.split(gPath,'.')
            array = string.split(array[1],'\/')
            local armatureName = array[#array]

            gSprite = ccs.Armature:create(armatureName)

        end        

        if (gSprite == nil) then
            print (" error !")
        end

        gSprite:setPosition(cc.p(480,320))
        sceneGame:addChild(gSprite)

    end

    local eventDispatcher = sceneGame:getEventDispatcher()
    local listener = cc.EventListenerCustom:create("EVENT_TEST",onEvent)
    eventDispatcher:addEventListenerWithFixedPriority(listener,1)

end

xpcall(main, __G__TRACKBACK__)
