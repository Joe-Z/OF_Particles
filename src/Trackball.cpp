#include "Trackball.h"
#include "Quaternion.h"
#include "Vector.h"

TrackBall::TrackBall() : 
	OFFSET(0.75), 
	ZOOM_FACTOR(0.1), 
	PAN_FACTOR(0.01),
	fitWindow(true) {
}

void TrackBall::setWindow(int _width, int _height) {
    width = _width;
    height = _height;
    
    if (fitWindow) {
		if (width < height)
			size = int(width * OFFSET);
		else
			size = int(height * OFFSET);
    }
}

void TrackBall::setSize(int _size) {
	size = _size;
}

void TrackBall::setWindowFitting(bool fit) {
	fitWindow = fit;
}

void TrackBall::mousePressed(int x, int y, Button button) {
	mouseX = x;
	mouseY = y;
	
	if (button == LEFT_BUTTON)
		start = getBallProjection(x,y);
}

void TrackBall::mouseDragged(int x, int y, Button button) {

	// rotate
    if (button == LEFT_BUTTON) {
        if (x != mouseX || y != mouseY) {
			end = getBallProjection(x, y);
    
			double phi = start.angle(end);
			Vector axis = end.cross(start);
    
			eye = Quaternion::rotate(eye, phi, axis);
			up = Quaternion::rotate(up, phi, axis);
    
			// changes ball behavior
			//start = getBallProjection(x, y);
		}
    }
	
    // zoom
    else if (button == MIDDLE_BUTTON) {
		double factor = eye.norm() + (y - mouseY) * ZOOM_FACTOR;
		
		if (factor <= 0.0)
			factor = 0.1;
    
        eye = eye.toLength(factor);
    }
    
    // move
    else if (button == RIGHT_BUTTON) {
        Vector pan = (eye.cross(up).toLength((x - mouseX) * PAN_FACTOR))
					+ (up.toLength((y - mouseY) * PAN_FACTOR));
					
        origin = origin + pan;
    }
    
    mouseX = x;
    mouseY = y;
}

Vector TrackBall::getEye() {
    return eye + origin;
}

Vector TrackBall::getOrigin() {
	return origin;
}

Vector TrackBall::getUp() {
	return up;
}

void TrackBall::setEye(double x, double y, double z) {
	eye.set(x, y, z);
}

void TrackBall::setOrigin(double x, double y, double z) {
	origin.set(x, y, z);
}

void TrackBall::setUp(double x, double y, double z) {
	up.set(x, y, z);
}

Vector TrackBall::getBallProjection(int x, int y) {
    double xCoord = (double(x) - width / 2) / size,
		yCoord = (height / 2 - double(y)) / size,
		zCoord;
    
    double length = sqrt(xCoord * xCoord + yCoord * yCoord);
    
    if (length > 1) {
        xCoord /= length;
        yCoord /= length;
        zCoord = 0;
    }
    else
        zCoord = sqrt(1 - length * length);

    return up.toLength(yCoord) + 
		up.cross(eye).toLength(xCoord) + 
		eye.toLength( zCoord);
}