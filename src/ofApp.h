#pragma once

#include "ofMain.h"
#include "Button.h"

class ofApp : public ofBaseApp{

	//enums to represent game states
	enum GameState{
		StartUp,
		PlayingSequence,
		PlayerInput,
		GameOver
	};

	public:
		//Some OpenFrameworks must-have functions
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//Functions for our game
		void lightOn(Buttons color);
		void lightOff(Buttons color);
		void generateSequence();
		bool checkUserInput(Buttons c);
		void GameReset();
		void startUpSequence(int count);
		
	private:
		//This vector will basically act as list of button enums
		//for us to be able to store the sequences
		vector<Buttons> Sequence;

		//Let's declare the buttons we will use
		Button *RedButton;
		Button *BlueButton;
		Button *YellowButton;
		Button *GreenButton;

		//These will be mere images which we will draw on top
		//of the actual buttons to give the mere illusion
		//that the original buttons are lighting up
		ofImage redLight;
		ofImage blueLight;
		ofImage yellowLight;
		ofImage greenLight;
		ofImage logo;
		ofImage logoLight;
		ofImage startUpScreen;
		ofImage gameOverScreen;

		//Few variables we'll need
        ofSoundPlayer backgroundMusic;
		int sequenceLimit = 1;
		int userIndex = 1;
		int showingSequenceDuration = 0;
		int lightDisplayDuration = -1;
		Buttons color;
		GameState gameState;
		bool logoIsReady = false;
		int logoCounter = 0;
		bool idle = true;
		
};