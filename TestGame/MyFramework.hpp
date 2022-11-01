#include "inc/Framework.h"

#include "MovingObject.hpp"
#include "PlayerObject.hpp"
#include "BallObject.hpp"
#include "BlockObject.hpp"
#include "WallObject.hpp"
#include "AbilityObject.hpp"
#include "SavingWall.hpp"

#include <string>
#include <list>

class MyFramework : public Framework {

public:
    MyFramework() = default;
    inline static bool restart = true;
    PlayerObject* Player;
    BallObject* Ball;
    Object* Background;
    inline static vector<Object*> allObjectsToCollideVec = {};
    inline static list<BlockObject*> allBlocksList = {};
    inline static list<AbilityObject*> allAbilitiesList = {};
    inline static list<SavingWall*> allSavingWalls = {};
    inline static list<WallObject*> allWalls = {};
    
    void endOfSession();
    
    void SetWindowParameters(int width, int height);
    
    virtual void PreInit (int& width, int& height, bool& fullscreen) override;

    virtual bool Init() override;

    virtual void Close() override;

    virtual bool Tick() override;

    virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override;

    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

    virtual void onKeyPressed(FRKey k) override;

    virtual void onKeyReleased(FRKey k) override;

    virtual const char* GetTitle() override;
    
    void setWWidth(int width);
    
    void setWHeight(int height);
    
    void initWHUnits1000();
    
    int getWWidth();
    
    int getWHeight();
    
    static float getWUnit();
    
    static float getHUnit();
    
    
    bool cursorToDirectionEnable = true;
    inline static int cursorX = 0;
    inline static int cursorY = 0;
    
private:
    inline static int wWidth = 800;
    inline static int wHeight = 600;
    inline static float wUnit = 0.0f;
    inline static float hUnit = 0.0f;
};
