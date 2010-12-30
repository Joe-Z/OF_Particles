#ifndef EMITTER_H_INCLUDED
#define EMITTER_H_INCLUDED

#include "ofMain.h"
#include <vector>
#include "Particle.h"

enum EMIT_TYPE {spark, ball, tornado, smoke, rain};

class Emitter {
public:
	Emitter(int _maxParticles, int _emitRate, int _lifeTime,
			EMIT_TYPE _type = spark);
	~Emitter();
	virtual void setup();
	virtual void initNewParticles();
	virtual void maintainParticles(ofPoint force);

	virtual void draw();

	virtual void setType(EMIT_TYPE newType);
	virtual void setMaxParticles(int max);
	virtual void setSplashFactor(float factor);
	virtual void setBounciness(float bounciness);

protected:
	vector<Particle> particles;
	ofPoint pos, dir;
	int maxParticles;
	int emitRate;
	int lifeTime;
	EMIT_TYPE type;

	//particle-preferences according to type
	ofPoint color;
	float typeBounciness;
	float typeWeight;
	float splashFactor;
};

#endif //EMITTER_H_INCLUDED