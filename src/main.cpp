////////////////////////////////////////
//        Assignment 1                //
// Computer Graphics 2                //
//  Franz J. Lanzendorfer             //
//                                    //
//  Camera Controls by:               //
//   Eberhard Gräther                 //
////////////////////////////////////////

#include "testApp.h"

int main() {
ofAppGlutWindow window;
ofSetupOpenGL(&window, 640, 480, OF_WINDOW);
ofBaseApp *application;

application = new ModelDemo();

ofRunApp(application);
}
