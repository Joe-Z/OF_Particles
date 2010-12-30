#include "testApp.h"

////////////////////////////////////////
//        Assignment 1                //
// Computer Graphics 2                //
//  Franz J. Lanzendorfer             //
//                                    //
//  Camera Controls by:               //
//   Eberhard Gräther                 //
////////////////////////////////////////


ModelDemo::ModelDemo():
	floorEmitter(new Emitter(10000, 25, 180, spark)) {
}

//========================================================================
void ModelDemo::setup() {
	
	gui.addToggle("wind", windOn);
	gui.addToggle("gravity", gravityOn);
	gui.addSlider("wind-direction", windRotation, 0, 259);
	gui.addSlider("wind-strength", windSpeed, 0.001, 0.05);
	gui.addSlider("particles", maxParticles, 2000, 50000);
	gui.addSlider("splash-factor", splashFactor, 0, 1.0);
	gui.addSlider("bounciness", bounciness, 0, 1.0);
	gui.addTitle("'1' - sparks\n"
				 "'2' - balls\n"
				 "'3' - tornado\n"
				 "'4' - smoke\n"
				 "'f' - fullscreen\n"
				 "drag cursor to change view\n");

	ofSetVerticalSync(true);
	ofDisableSetupScreen();

	windOn = gravityOn = true;

	trackball.setEye(40.0, 40.0, 20.0);
	trackball.setUp(0.0, 0.0, 1.0);
	
	trackball.setWindow(ofGetWidth(), ofGetHeight());

	wind.set(0, 0, 0);
	windRotation = 0;
	windSpeed = 0.002;

	//emitter-controls
	maxParticles = 10000;
	splashFactor = 0.1;
	bounciness = 0.2;

	gravity.set(0, 0, -.02);

	prevMouseX = mouseX;
	prevMouseY = mouseY;

	gui.show();
}

//========================================================================
void ModelDemo::update() {
	eye = trackball.getEye(),
	origin = trackball.getOrigin(),
	up = trackball.getUp();

	//update wind-direction
	wind.x = cos(windRotation) + sin(windRotation);
	wind.y = -sin(windRotation) + cos(windRotation);

	prevMouseX = mouseX;
	prevMouseY = mouseY;

	//set variable parameters in emitter
	floorEmitter->setMaxParticles(maxParticles);
	floorEmitter->setSplashFactor(splashFactor);
	floorEmitter->setBounciness(bounciness);

	floorEmitter->initNewParticles();

	ofPoint force;
	force.set(0, 0, 0);
	if(windOn)
		force += (wind * windSpeed);
	if(gravityOn)
		force += gravity;

	floorEmitter->maintainParticles(force);
}

//========================================================================
void ModelDemo::draw() {
	// set viewport
	int width, height;
	width = ofGetWidth();
	height = ofGetHeight();
	glViewport(0, 0, width, height);

	// clear viewport
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	// set perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)width / height, 0.1, 1000.0);

	// set camera position
	float time = ofGetElapsedTimef();
	gluLookAt(
		eye.x, eye.y, eye.z,
		origin.x, origin.y, origin.z,
		up.x, up.y, up.z
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_CULL_FACE);
	ofPushMatrix();
		glRotatef(ofGetElapsedTimef() * 13, 0, 0, 1);
		glColor3f(.3, .3, .3);
		glBegin(GL_QUADS);
			glVertex3f(20.0, 20.0, 0.0);
			glVertex3f(-20.0, 20.0, 0.0);
			glVertex3f(-20.0, -20.0, 0.0);
			glVertex3f(20.0, -20.0, 0.0);
		glEnd();
		//should smooth the lines a bit
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		floorEmitter->draw();
	ofPopMatrix();

    // set orthogonal mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	ofSetColor(255, 255, 255);

	gui.draw();
}

//========================================================================
void ModelDemo::keyPressed(int key) {
	//TODO: use setType() for switching emitters?
	switch(tolower(key)) {
		case 'f':
			ofToggleFullscreen();
			break;
		case '1':
			delete floorEmitter;
			floorEmitter = new Emitter(10000, 25, 120, spark);
			break;
		case '2':
			delete floorEmitter;
			floorEmitter = new Emitter(10000, 25, 120, ball);
			break;
		case '3':
			delete floorEmitter;
			floorEmitter = new TornadoEmitter(10000, 25, 120, tornado);
			break;
		case '4':
			delete floorEmitter;
			floorEmitter = new TornadoEmitter(10000, 25, 120, smoke);
			break;
	}
	handleKey(key, true);
	ScreenShotApplication::keyPressed(key);
}

//========================================================================
void ModelDemo::keyReleased(int key) {
	handleKey(key, false);
}
//========================================================================
// use a single key handle method for released and pressed events
void ModelDemo::handleKey(int key, bool pressed) {
	switch (key) {
		//here used to be the wind-controls
		default:
			cout << key << endl;
			break;
	}
}
//========================================================================
void ModelDemo::mousePressed(int x, int y, int button) {
	if (button == GLUT_LEFT_BUTTON)
		trackball.mousePressed(x, y, TrackBall::LEFT_BUTTON);
	else if (button == GLUT_MIDDLE_BUTTON)
		trackball.mousePressed(x, y, TrackBall::MIDDLE_BUTTON);
	else if (button == GLUT_RIGHT_BUTTON)
		trackball.mousePressed(x, y, TrackBall::RIGHT_BUTTON);
}

//========================================================================
void ModelDemo::mouseDragged(int x, int y, int button) {
	if (button == GLUT_LEFT_BUTTON)
		trackball.mouseDragged(x, y, TrackBall::LEFT_BUTTON);
	else if (button == GLUT_MIDDLE_BUTTON)
		trackball.mouseDragged(x, y, TrackBall::MIDDLE_BUTTON);
	else if (button == GLUT_RIGHT_BUTTON)
		trackball.mouseDragged(x, y, TrackBall::RIGHT_BUTTON);
}

//========================================================================
void ModelDemo::windowResized(int w, int h) {
	trackball.setWindow(w, h);
}
