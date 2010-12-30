#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include "ofMain.h"

struct Particle {
	ofPoint pos;
	ofPoint prevPos;
	ofPoint vel;

	float weight;
	float bounciness;
	float life;
};

#endif //PARTICLE_H_INCLUDED