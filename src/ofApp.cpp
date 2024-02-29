#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//Let's create our buttons
	RedButton = new Button(ofGetWindowWidth()/2-20,ofGetWindowHeight()/2-260,302,239,"images/RedButton.png","sounds/RedButton.mp3");
	BlueButton = new Button(ofGetWindowWidth()/2+35,ofGetWindowHeight()/2-10,236,290,"images/BlueButton.png","sounds/BlueButton.mp3");
	YellowButton = new Button(ofGetWindowWidth()/2-260,ofGetWindowHeight()/2+40,287,239,"images/YellowButton.png","sounds/YellowButton.mp3");
	GreenButton = new Button(ofGetWindowWidth()/2-260,ofGetWindowHeight()/2-260,234,294,"images/GreenButton.png","sounds/GreenButton.mp3");

	//Load the glowing images for the buttons
	redLight.load("images/RedLight.png");
    blueLight.load("images/BlueLight.png");
    yellowLight.load("images/YellowLight.png");
    greenLight.load("images/GreenLight.png");

	//Load other images
	logo.load("images/Logo.png");
	logoLight.load("images/LogoLight.png");
	startUpScreen.load("images/StartScreen.png");
	gameOverScreen.load("images/GameOverScreen.png");
	
	//Additional images
	selectGamemodetext.load("images/Selectgamemode.png");
	originalgmtxt.load("images/Originalbutton.png");
	recordgmtxt.load("images/Recordbutton.png");
	recordingIndicator.load("images/RecordingIndicator.png");
	playingIndicator.load("images/PlayingIndicator.png");
	multiplayergmtxt.load("images/Multiplayerbutton.png");

    //Load Music
	backgroundMusic.load("sounds/BackgroundMusic.mp3");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();

	//Text string for multiplayer
	myfont.load("AovelSansRounded-rdDL.ttf", 32);
	mybigfont.load("AovelSansRounded-rdDL.ttf", 60);
	// text = "Points:";

	//Initial State
	gameState = StartUp;
}
//--------------------------------------------------------------
void ofApp::update(){
	//If player is selecting gamemode, we tick buttons expecting input
	if(gameState == GameModeSelection){
		RedButton->tick();
		GreenButton->tick();
		YellowButton->tick();		
	}
	//New game mod for future recording and playback
	if(gameState == RecnPlaymode || gameState == Recording) {
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();		
	}
	//We will tick the buttons, aka constantly update them
	//while expecting input from the user to see if anything changed
	if(gameState == PlayerInput){
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();

		//If the amount of user input equals the sequence limit
		//that means the user has successfully completed the whole
		//sequence and we can proceed with the next level
		if(userIndex == sequenceLimit){
			generateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;
			gameState = PlayingSequence;
		}
	}
	if (gameState == P1Input || gameState == P2Input){
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();

		if (gameState == P1Input && userIndex == p1sequencelimit){
			currentplayer = 2;
			multiplayerGenerateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;

			Paused = true;
			Pausetimer = 120;

			gameState = P2Sequence;
		}
		else if (gameState == P2Input && userIndex == p2sequencelimit){
			currentplayer = 1;
			multiplayerGenerateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;

			Paused = true;
			Pausetimer = 120;
		if (!lastTurn){
			gameState = P1Sequence;
		}
		if (lastTurn){
			gameState = MutliplayerGameOver;
		}
	}
	}

	//This will take care of turning on the lights after a few
	//ticks so that they dont stay turned on forever or too long
	if(lightDisplayDuration > 0){
		lightDisplayDuration--;
		if(lightDisplayDuration <= 0){
			lightOff(RED);
			lightOff(BLUE);
			lightOff(YELLOW);
			lightOff(GREEN);
		}
	}
	if (Pausetimer > 0){
		Pausetimer--;
		if (Pausetimer <= 0 ){
			Paused = false;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//Create the background
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	//Draw the buttons
	ofSetColor(255,0,0);
	RedButton->render();
	BlueButton->render();
	YellowButton->render();
	GreenButton->render();

	if(gameState == PlayRecording){

		showingSequenceDuration++;
		if(showingSequenceDuration == 120){
			color = Recorded[Playbackpos];
			lightOn(color);
			lightDisplayDuration = 30;
		}
	
		if(showingSequenceDuration == 140){
			lightOff(color);
			showingSequenceDuration = 60;
			Playbackpos++;
		}
		if(Playbackpos == recordedLimit){
			lightOff(color);
			Playbackpos = 0;
			gameState = RecnPlaymode;
		}
	}


	//This whole if statement will take care of showing
	//the sequence to the user before accepting any input
	if(gameState == PlayingSequence){
		showingSequenceDuration++;
		if(showingSequenceDuration == 120){
			color = Sequence[userIndex];
			lightOn(color);
			lightDisplayDuration = 30;
		}
	
		if(showingSequenceDuration == 140){
			lightOff(color);
			showingSequenceDuration = 60;
			userIndex++;
		}
		if(userIndex == sequenceLimit){
			lightOff(color);
			userIndex = 0;
			gameState = PlayerInput;
		}
	}
	if (gameState == P1Sequence || gameState == P2Sequence){
		showingSequenceDuration++;
		if(showingSequenceDuration == 120){
			if( gameState == P1Sequence){
			color = Player1Sequence[userIndex];
			}
			if (gameState == P2Sequence){
			color = Player2Sequence[userIndex];
			}
			lightOn(color);
			lightDisplayDuration = 30;
		}
	
		if(showingSequenceDuration == 140){
			lightOff(color);
			showingSequenceDuration = 60;
			userIndex++;
		}
			
		if (gameState == P1Sequence && userIndex == p1sequencelimit){
			lightOff(color);
			userIndex = 0;			
			gameState = P1Input;
			}

		if (gameState == P2Sequence && userIndex == p2sequencelimit){
			lightOff(color);
			userIndex = 0;			
			gameState = P2Input;
			}
	
	}

	

	//StartUP (You dont need to pay much attention to this)
	//(This is only to create a animation effect at the start of the game)
	if(gameState == StartUp){
		showingSequenceDuration++;
		startUpSequence(showingSequenceDuration);
	}

	//If the statements to see see if the buttons should be lit up
	//If they are then we will draw the glowing images on top of them
	if (RedButton->GetIsLightUp()) {
		redLight.draw(ofGetWindowWidth()/2-60, ofGetWindowHeight()/2-305, 376, 329);
	}
	if (BlueButton->GetIsLightUp()) {
		blueLight.draw(ofGetWindowWidth()/2+5, ofGetWindowHeight()/2-60, 309, 376);
	} 
	if (YellowButton->GetIsLightUp()) {
		yellowLight.draw(ofGetWindowWidth()/2-300, ofGetWindowHeight()/2+5, 374, 318);
	} 
	if (GreenButton->GetIsLightUp()) {
		greenLight.draw(ofGetWindowWidth()/2-307, ofGetWindowHeight()/2-295, 315, 356);
	}

	//Part of the Start Up
	if(logoIsReady){
		logo.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);
	}

	//Draw the game over screen
	if(gameState == GameOver || gameState == MutliplayerGameOver){
		gameOverScreen.draw(0,0,1024,768);
	}

	//This will draw the "Press to Start" screen at the beginning
	else if(!idle && gameState == StartUp){
		startUpScreen.draw(20,0,1024,768);
	}
	if (gameState == GameModeSelection){
		selectGamemodetext.draw(0,-320,1024,768);
		originalgmtxt.draw(-125,-120,1024,768);
		recordgmtxt.draw(140,-120,1024,768);
		multiplayergmtxt.draw(-95,120,1024,768);
	}
	if(gameState == Recording){
		recordingIndicator.draw(-288,-300,1024,768);
		myfont.drawString("Rec&Play" , 30 , 725);

	}
	if(gameState == PlayRecording){
		playingIndicator.draw(-288,-300,1024,768);
		myfont.drawString("Rec&Play" , 30 , 725);
		
	}
	if( gameState == RecnPlaymode){
		myfont.drawString("Rec&Play" , 30 , 725);
	}

	//Draw string text for multiplayer
	if (gameState == P1Sequence || gameState == P1Input || gameState == P2Sequence || gameState == P2Input){
		myfont.drawString("Player 1 score: " + ofToString(player1Score), 60, 100);
		myfont.drawString("Player 2 score: " + ofToString(player2Score), 60, 150);
	}
	if (gameState == P1Input || gameState == P1Sequence){
		ofSetColor(0, 0, 128);
		ofDrawRectangle(740, 55, myfont.stringWidth("Player 1's turn") + 20, myfont.stringHeight("Player 1's turn") + 20);
		ofSetColor(255, 255, 255);		
		myfont.drawString("Player 1's turn", 750, 100);
		myfont.drawString("Multiplayer" , 30 , 725);

	}
	if (gameState == P2Input || gameState == P2Sequence){
		ofSetColor(139, 0, 0);
		ofDrawRectangle(740, 55, myfont.stringWidth("Player 2's turn") + 20, myfont.stringHeight("Player 2's turn") + 20);
		ofSetColor(255, 255, 255);		
		myfont.drawString("Player 2's turn", 750, 100);
		myfont.drawString("Multiplayer" , 30 , 725);
	}

	if (gameState == MutliplayerGameOver) {
		myfont.drawString("Player 1 score: " + ofToString(player1Score), 30, 40);
		myfont.drawString("Player 2 score: " + ofToString(player2Score), 30, 90);
		if (player1Score > player2Score){
			mybigfont.drawString("Player 1 Wins",(ofGetWindowWidth()/2)-75, (ofGetWindowHeight()/2)-300);
		}
		if (player1Score < player2Score){
			mybigfont.drawString("Player 2 Wins",(ofGetWindowWidth()/2)-75, (ofGetWindowHeight()/2)-300);
		}	
		if(player1Score == player2Score) {
			mybigfont.drawString("It's a Tie!",(ofGetWindowWidth()/2)-80, (ofGetWindowHeight()/2)-150);			
		}	
	}
}
//--------------------------------------------------------------
void ofApp::MultiplayerReset(){

	lightOff(RED);
	lightOff(BLUE);
	lightOff(YELLOW);
	lightOff(GREEN);

	Player1Sequence.clear();
	Player2Sequence.clear();

	player1Score = 0;
	player2Score = 0;

	currentplayer = 1;

	multiplayerGenerateSequence();

	lastTurn = false;

	userIndex = 0;
	gameState = P1Sequence;
	showingSequenceDuration = 0;
}

void ofApp::GameReset(){
	//This function will reset the game to its initial state
	lightOff(RED);
	lightOff(BLUE);
	lightOff(YELLOW);
	lightOff(GREEN);
	Sequence.clear();
	generateSequence();
	userIndex = 0;
	if (gameState == GameOver){
		gameState = PlayingSequence;
	}
	else if (gameState == GameModeSelection) {
		gameState = PlayingSequence; //if player selected original game mode from selection screen, normal game will start
	}

	else {
		gameState = GameModeSelection;
	}
	showingSequenceDuration = 0;
}

//--------------------------------------------------------------
void ofApp::multiplayerGenerateSequence(){

	//This function will generate a random number between 0 and 3 (0,1,2,3)
	int random = ofRandom(4);
	
	//Depending on the random number, we will add a button to the sequence
	if(random == 0){
		if (currentplayer == 1 ){
		Player1Sequence.push_back(RED);
		}
		if (currentplayer == 2 ){
		Player2Sequence.push_back(RED);
		}
	}
	else if(random == 1){
		if (currentplayer == 1 ){
		Player1Sequence.push_back(BLUE);
		}
		if (currentplayer == 2 ){
		Player2Sequence.push_back(BLUE);
		}
	}
	else if(random == 2){
		if (currentplayer == 1 ){
		Player1Sequence.push_back(GREEN);
		}
		if (currentplayer == 2 ){
		Player2Sequence.push_back(GREEN);
		}
	}	
	else if(random == 3){
		if (currentplayer == 1 ){
		Player1Sequence.push_back(YELLOW);
		}
		if (currentplayer == 2 ){
		Player2Sequence.push_back(YELLOW);
		}
	}

	//We will adjust the sequence limits to the new size of the Sequence lists
	p1sequencelimit = Player1Sequence.size();
	p2sequencelimit = Player2Sequence.size();
}
void ofApp::generateSequence(){

	//This function will generate a random number between 0 and 3 (0,1,2,3)
	int random = ofRandom(4);
	
	//Depending on the random number, we will add a button to the sequence
	if(random == 0){
		Sequence.push_back(RED);
	}
	else if(random == 1){
		Sequence.push_back(BLUE);
	}
	else if(random == 2){
		Sequence.push_back(GREEN);
	}	
	else if(random == 3){
		Sequence.push_back(YELLOW);
	}

	//We will adjust the sequence limit to the new size of the Sequence list
	sequenceLimit = Sequence.size();
}
//--------------------------------------------------------------
bool ofApp::checkUserInput(Buttons input) {
    // This function will verify if the user input matches the color
    // of the sequence at the current index

    if (gameState == PlayerInput) {
        if (Sequence[userIndex] == input) {
            return true;
        } else {
            return false;
        }
    }

    // Here are verifiers for multiplayer to see if the current user input is correct
    if (gameState == P1Input) {
        if (Player1Sequence[userIndex] == input) {
			player1Score++; // Adds one point to Player 1
            return true;
        } else {
            return false;
        }
    }

    if (gameState == P2Input) {
        if (Player2Sequence[userIndex] == input) {
			player2Score++; // Adds one point to Player 2
            return true;
        } else {
            return false;
        }
    }

    // If none of the conditions are met, you should decide what to do.
    // In this case, returning false might be appropriate since it's a mismatch.
	else {
    return false;}

}

//--------------------------------------------------------------
void ofApp::lightOn(Buttons color){
	//This function will take care of toggling the "isLightUp" variable to
	//true for the button that matches the color, and also play the button sound
	if(color == RED){
		RedButton->toggleLightOn();
		RedButton->playSound();
	}
	else if(color == BLUE){
		BlueButton->toggleLightOn();
		BlueButton->playSound();
	}
	else if(color == YELLOW){
		YellowButton->toggleLightOn();
        YellowButton->playSound();
	}
	else if(color == GREEN){
		GreenButton->toggleLightOn();
		GreenButton->playSound();
	}
}

//--------------------------------------------------------------
void ofApp::lightOff(Buttons color){
	//This function will take care of toggling the "isLightUp" variable to false
	if(color == RED){
		RedButton->toggleLightOff();
	}
	else if(color == BLUE){
		BlueButton->toggleLightOff();
	}
	else if(color == YELLOW){
		YellowButton->toggleLightOff();
	}
	else if(color == GREEN){
		GreenButton->toggleLightOff();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//As long as we're not in Idle OR the gameState is GameOver;
	//AND we press the SPACEBAR, we will reset the game
	if((!idle && gameState == GameOver) && tolower(key) == ' '){
		GameReset();
	}
	if((!idle && gameState == MutliplayerGameOver) && tolower(key) == ' '){
		MultiplayerReset();
	}

	if((!idle && gameState == StartUp) && tolower(key) == ' '){
		GameReset();
	}

	//if user presses Backspace, user will be sent to gamemode selection screen
	if((!idle) && tolower(key) == '\b'){
		gameState = GameModeSelection;
	}	
	if((!idle && gameState == RecnPlaymode) && tolower(key) == 'r'){ //While in Recnplay, if r is pressed it will start recording mode
			gameState = Recording;
			Paused = true;
			Pausetimer = 30; //timer to stop the program from taking r input so it can change into recording mode (if deleted it will be stuck on recnplay mode)

			lightOff(RED);
			lightOff(BLUE);
			lightOff(YELLOW);
			lightOff(GREEN);

			Recorded.clear();

	}
	if(!Paused && gameState == Recording && tolower(key) == 'r'){
			gameState = RecnPlaymode;
	}
	if(!Paused && gameState == RecnPlaymode && tolower(key) == 'p'){
			Playbackpos = 0;
			showingSequenceDuration = 0;
			gameState = PlayRecording;

	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int mouseX, int mouseY ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	// If we are not in idle and want to select a new gamemode
	//We select one of the buttons the give a new gamemode
	if ((!idle && gameState == GameModeSelection)) {
		//We mark the pressed button as "pressed"
		RedButton->setPressed(x,y);
		GreenButton->setPressed(x,y);
		YellowButton->setPressed(x,y);		

		//We check which button got pressed
		if(RedButton->wasPressed()){
			color = RED;
		}
		else if(GreenButton->wasPressed()){
			color = GREEN;
		}
		else if (YellowButton->wasPressed()){
			color = YELLOW;
		}
		//Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 60;
		if (color == GREEN) {
			GameReset();
		}
		if (color == RED){
			gameState = RecnPlaymode;
		}
		if (color == YELLOW){
			MultiplayerReset();
		}
	}
		if(!idle && gameState == Recording){
		//We mark the pressed button as "pressed"
		RedButton->setPressed(x,y);
		BlueButton->setPressed(x,y);
		YellowButton->setPressed(x,y);
		GreenButton->setPressed(x,y);

		//We check which button got pressed
		if(RedButton->wasPressed()){
			color = RED;
		}
		else if(BlueButton->wasPressed()){
			color = BLUE;
		}
		else if(YellowButton->wasPressed()){
			color = YELLOW;
		}
		else if(GreenButton->wasPressed()){
			color = GREEN;
		}

		//Add pushed button to Recorded sequence
		Recorded.push_back(color);
		recordedLimit = Recorded.size();

		//Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 15;
		}



		//gamemode for future recording and playback
		if(!idle && gameState == RecnPlaymode){
		//We mark the pressed button as "pressed"
		RedButton->setPressed(x,y);
		BlueButton->setPressed(x,y);
		YellowButton->setPressed(x,y);
		GreenButton->setPressed(x,y);

		//We check which button got pressed
		if(RedButton->wasPressed()){
			color = RED;
		}
		else if(BlueButton->wasPressed()){
			color = BLUE;
		}
		else if(YellowButton->wasPressed()){
			color = YELLOW;
		}
		else if(GreenButton->wasPressed()){
			color = GREEN;
		}
		//Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 15;
		}

	//If we're not in Idle and the gameState equals PlayerInput,
	//We will pay attention to the mousePresses from the user
	if(!idle && gameState == PlayerInput){
		//We mark the pressed button as "pressed"
		RedButton->setPressed(x,y);
		BlueButton->setPressed(x,y);
		YellowButton->setPressed(x,y);
		GreenButton->setPressed(x,y);

		//We check which button got pressed
		if(RedButton->wasPressed()){
			color = RED;
		}
		else if(BlueButton->wasPressed()){
			color = BLUE;
		}
		else if(YellowButton->wasPressed()){
			color = YELLOW;
		}
		else if(GreenButton->wasPressed()){
			color = GREEN;
		}
		//Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 15;
			//If the user input is correct, we can continue checking
			if(checkUserInput(color)){
				userIndex++;
			}
			//If not, then we will terminate the game by 
			//putting it in the GameOver state.
			else{
				gameState = GameOver;
			}
	}

	else if (!idle && (gameState == P1Input || gameState == P2Input)){
		//We mark the pressed button as "pressed"
		RedButton->setPressed(x,y);
		BlueButton->setPressed(x,y);
		YellowButton->setPressed(x,y);
		GreenButton->setPressed(x,y);

		//We check which button got pressed
		if(RedButton->wasPressed()){
			color = RED;
		}
		else if(BlueButton->wasPressed()){
			color = BLUE;
		}
		else if(YellowButton->wasPressed()){
			color = YELLOW;
		}
		else if(GreenButton->wasPressed()){
			color = GREEN;
		}
		//Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 15;
			//If the user input is correct, we can continue checking
			if(checkUserInput(color)){
				userIndex++;
			}
			//If not, then we will terminate the game by 
			//putting it in the GameOver state.
			else{
			if( gameState == P1Input){
			currentplayer = 2;
			multiplayerGenerateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;

			Paused = true;
			Pausetimer = 240;
			lastTurn = true;		

			gameState = P2Sequence;
			}
			if (gameState == P2Input){
				gameState = MutliplayerGameOver;
				}
			}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------

//You may honestly ignore this function, shouldnt be something you need
//to change or anything. It's only for the start up animation. But ofc,
//If you wish to make something out of it or make it better, be my guest.
void ofApp::startUpSequence(int count){
	
	if(count < 200){
		GreenButton->toggleLightOn();
	}
	else if(count >= 200 && count < 260){
		GreenButton->toggleLightOff();
		RedButton->toggleLightOn();
	}
	else if(count >= 260 && count < 320){
		RedButton->toggleLightOff();
		BlueButton->toggleLightOn();
	}
	else if(count >= 320 && count < 380){
		BlueButton->toggleLightOff();
		YellowButton->toggleLightOn();
	}
	else if(count >= 380 && count < 440){
		YellowButton->toggleLightOff();
	}
	else if(count >= 440 && count < 500){
		GreenButton->toggleLightOn();
		RedButton->toggleLightOn();
		YellowButton->toggleLightOn();
		BlueButton->toggleLightOn();
	}
	else if(count >= 500 && count < 560){
		GreenButton->toggleLightOff();
		RedButton->toggleLightOff();
		YellowButton->toggleLightOff();
		BlueButton->toggleLightOff();
	}
	else if(count >= 560){
		showingSequenceDuration = 400;
	}

	//Logo Drawing
	if(logoIsReady && logoCounter > 0){
		logoCounter--;
		ofSetColor(256,256,256,logoCounter);
		logoLight.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);
		ofSetColor(256,256,256);
	}
	if((count > 375) && !logoIsReady){
		logoCounter++;

		ofSetColor(256,256,256,logoCounter);
		logoLight.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);

		ofSetColor(256,256,256,logoCounter);
		logo.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);

		ofSetColor(256,256,256);
	}
	if(logoCounter >=255){
		logoIsReady = true;
		idle = false;
	}
}
