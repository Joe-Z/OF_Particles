////////////////////////////////////////
//        Assignment 1                //
// Computer Graphics 2                //
//  Franz J. Lanzendorfer             //
//                                    //
//  Camera Controls by:               //
//   Eberhard Gräther                 //
////////////////////////////////////////

#include "ofMain.h"
#include "Vector.h"
#include "Trackball.h"

#include "Emitter.h"
#include "TornadoEmitter.h"

#include "ofxSimpleGuiToo.h"

class ScreenShotApplication: public ofBaseApp {
public:
	virtual void keyPressed(int key) {
		switch (tolower(key)) {
			case 'p':
				ofImage screenShot;
				screenShot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
				screenShot.saveImage("screenShot.png");
		}
	}
};

class ModelDemo: public ScreenShotApplication {
public:
	ModelDemo();
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	// use a single key handle method for released and pressed events
	void handleKey(int key, bool pressed);
	void mousePressed(int x, int y, int button);
	void mouseDragged(int x, int y, int button);
	void windowResized(int w, int h);

private:
	// keyboard controls
	bool windOn, gravityOn;

	TrackBall trackball;
	Vector eye, origin, up;

	ofPoint wind;
	float windRotation;
	float windSpeed;
	ofPoint gravity;

	//emitter-controls
	int maxParticles;
	float splashFactor, bounciness;

	//mouse coordinates
	int prevMouseX, prevMouseY;

	//particle-emitter
	Emitter* floorEmitter;
};
