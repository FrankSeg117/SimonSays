#pragma once

#include "ofMain.h"

//enums to represent the different buttons
enum Buttons {
    GREEN,
    RED,
    YELLOW,
    BLUE
};
class Button {
public:
    
    //Button constructor and properties
    Button(float x, float y, float width, float height, string imagePath, string soundPath);
    void render();
    void playSound();
    void setPressed(int x, int y);
    bool wasPressed(){return isPressed;}
    int getX(){return x;}
    int getY(){return y;}
    void toggleLightOn(){isLightUp = true;}
    void toggleLightOff(){isLightUp = false;}
    bool GetIsLightUp(){return isLightUp;}
    void tick();

private:
    float x, y, width, height;
    bool isPressed;
    ofImage image;
    ofSoundPlayer buttonSound;
    string imagePath;
    string soundPath;
    int pressCounter = -1;
    bool isLightUp = false;
};