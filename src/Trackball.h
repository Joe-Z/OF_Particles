#ifndef TRACKBALL_H_INCLUDED
#define TRACKBALL_H_INCLUDED

#include "Vector.h"

class TrackBall {
public:
	enum Button {LEFT_BUTTON, MIDDLE_BUTTON, RIGHT_BUTTON};

private:
    int size, height, width;
    
    Vector start, end;
    Vector eye, up, origin;
    
    int mouseX, mouseY;
    
    const double OFFSET;
	const double ZOOM_FACTOR;
	const double PAN_FACTOR;
	
	bool fitWindow;
    
public:
	TrackBall();
	
	void setWindow(int _width, int _height);
    void setSize(int _size);
    
    void setWindowFitting(bool fit);
	
    void mousePressed(int x, int y, Button button);
    void mouseDragged(int x, int y, Button button);
    
    Vector getEye();
    Vector getOrigin();
    Vector getUp();
    
    void setEye(double x, double y, double z);
    void setOrigin(double x, double y, double z);
    void setUp(double x, double y, double z);
    
private:
	Vector getBallProjection(int x, int y);
};

#endif //TRACKBALL_H_INCLUDED