#include "Button.h"

Button::Button(float x, float y, float width, float height, string imagePath = "", string soundPath = "") {
    //Construct the button with the given Parameters
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    //Button is not pressed at first 
    isPressed = false;

    //Load the image and the sound
    image.load(imagePath);
    buttonSound.load(soundPath);
}

void Button::render() {
    ofSetColor(255);
    //If the image path is correct and the image variable was able to
    //to load something, draw that image
    if (image.isAllocated()) {
        image.draw(x, y, width, height);
    } 
    //If the image path was not incorrect or the image variable was not able to
    //to load something, draw a rectangle in its place
    else {
        ofSetColor(255, 0, 0);
        ofDrawRectangle(x, y, width, height);
    }
}

void Button::playSound() {
    //If the sound path was correct, and the buttonSound variable has a
    //sound loaded, then play it
    if (buttonSound.isLoaded()) {
        buttonSound.play();
    }

}

void Button::setPressed(int mouseX, int mouseY) {
    //If the mouse is inside the button, set the button as pressed
    if (ofRectangle(x, y, width, height).inside(mouseX, mouseY)) {
        isPressed = true;
        pressCounter = 1; //You may change that pressCounter variable to a higher number
        //If you wish for it to stay pressed for a longer time
    }
}

void Button::tick(){
    //We will call this function every single frame in ofApp::update();
    //and in every call, if isPressed is true then we will decrease 
    //the pressCounter variable 1 by 1 until pressCounter reaches 0, 
    //we will then set the buttin as not pressed
    if(isPressed){
        pressCounter--;
        if(pressCounter == 0){
            isPressed = false;
            pressCounter = -1;
        }
    }

    //FUNFACT; each called frame called can also be known as a "tick"
    //And 60 ticks is the same as 1 second. (That's why they call it 60fps in games)
    //Might differ a bit from one computer to another, but it's a good rule of thumb

}