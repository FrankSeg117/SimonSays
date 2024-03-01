#pragma once

#include "ofMain.h"
#include "Button.h"

class ofApp : public ofBaseApp{

	//enums to represent game states
	enum GameState{

		StartUp, //Startup :)

		//Original gamestates
		PlayingSequence,
		GameModeSelection,
		PlayerInput,
		GameOver,

		//Recnplay gamestates
		RecnPlaymode,
		Recording,
		PlayRecording,

		//Multiplayer gameStates
		P1Sequence,
		P1Input,
		P2Sequence,
		P2Input,
		MutliplayerGameOver,

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

		//Added Functions
		void MultiplayerReset();
		void multiplayerGenerateSequence();
		
	private:
		//This vector will basically act as list of button enums
		//for us to be able to store the sequences
		vector<Buttons> Sequence;

		//Vector for Replaying
		vector<Buttons> Recorded;

		//Vector for multiplayer sequences
		vector<Buttons> Player1Sequence;
		vector<Buttons> Player2Sequence;

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
		
		//Additional images
		ofImage selectGamemodetext;
		ofImage originalgmtxt;
		ofImage recordgmtxt;
		ofImage recordingIndicator;
		ofImage playingIndicator;
		ofImage multiplayergmtxt;

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
		
		//Added Variables
		int Pausetimer = -1; //Timer variables (similar to idle) to have pauses for a specified amount of ticks
		bool Paused = true;
		int Playbackpos = 1;//Variable for the playback of the recording vector
		int recordedLimit = 1;

		string text;
		ofTrueTypeFont myfont;
		ofTrueTypeFont mybigfont;


		int p1sequencelimit = 1;
		int p2sequencelimit = 1;

		//This variable tells which player is going to go now so the generate sequence method generates a new button for that player
		int currentplayer = 1;

		//Variables to store player scores
		int player1Score = 0;
		int player2Score = 0;

		bool lastTurn = false; //Variable to give player 2 a chance to win if player 1 misses (so they each had the same amount of turns)
};