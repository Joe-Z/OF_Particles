#include "Emitter.h"

Emitter::Emitter(int _maxParticles, int _emitRate, int _lifeTime, EMIT_TYPE _type):
	maxParticles(_maxParticles),
	emitRate(_emitRate),
	lifeTime(_lifeTime),
	typeBounciness(0),
	typeWeight(0),
	type(_type) {
		color.set(0, 0, 0);
		pos.set(0, 0, 0);
		dir.set(0, 0, 1);

		setup();
}

Emitter::~Emitter() {
}


void Emitter::setup() {
	switch(type) {
		case rain:
			color.set(0, 0.5, 1.0);
			typeBounciness = 0;
			typeWeight = 4.0;
			//splashFactor for rain means the area
			//where drops fall off
			splashFactor = 50.0;
			break;
		case ball:
			color.set(0, 1.0, 0.3);
			typeBounciness = 0.8;
			typeWeight = 0.7;
			splashFactor = 0.5;
			break;
		//in this case default = spark
		default:
			color.set(1.0, 0.8, 0);
			typeBounciness = 0.2;
			typeWeight = 0.5;
			splashFactor = 0.1;
			break;
	}
}

void Emitter::initNewParticles() {
	//bring some randomness to the number of spawning particles
	int emitThisFrame = int(emitRate * ofRandom(0.6, 1.4));

	if(particles.size() + emitThisFrame > maxParticles) {
		particles.erase(particles.begin(), particles.begin() + emitThisFrame - 1);
	}

	for(int i = 0; i < emitThisFrame; i++) {
		Particle tempParticle;
		//rain behaves a bit different then the other types
		switch(type) {
			case rain:
				tempParticle.pos.set(ofRandomf() * splashFactor, ofRandomf() * splashFactor, pos.z);
				tempParticle.vel.set(0, 0, 0);
				break;
			//in this case default = spark & balls
			default:
				tempParticle.pos.set(pos.x, pos.y, pos.z);
				tempParticle.vel.set(ofRandomf() * splashFactor, ofRandomf() * splashFactor, ofRandom(.6, .9));
				break;
		}
		
		tempParticle.bounciness = typeBounciness;
		tempParticle.weight = typeWeight;
		tempParticle.life = int(lifeTime * ofRandom(0.6, 1.4));

		particles.push_back(tempParticle);
	}
}

void Emitter::maintainParticles(ofPoint force) {
	vector<Particle>::iterator it = particles.begin();
	while(it != particles.end()) {
		if(it->life > 0) {
			it->prevPos.x = it->pos.x;
			it->prevPos.y = it->pos.y;
			it->prevPos.z = it->pos.z;

			it->pos.x += it->vel.x;
			it->pos.y += it->vel.y;
			it->pos.z += it->vel.z;

			if(it->pos.z <= -pos.z) {
				//again: rain behaves different
				switch(type) {
					case rain:
						it->life = 0;
						break;
					//in this case default = spark & balls
					default:
						it->pos.z = 0;
						it->vel.z *= (-1) * it->bounciness;				
						break;
				}				
			}

			it->vel.x += force.x / it->weight;
			it->vel.y += force.y / it->weight;
			it->vel.z += force.z * it->weight;

			it->life--;
		
			++it;
		}
		else {
			it = particles.erase(it);
		}
	}
}

void Emitter::draw() {
	switch(type) {
		case rain:
			glPushMatrix();
				glTranslatef(pos.x, pos.y, pos.z);
				glColor3f(.5, .3, .8);
				glutSolidCube(1.0);

				glColor3f(color.x, color.y, color.z);
				for(int i = 0; i < particles.size() - 1; i++) {
					glBegin(GL_LINES);
						glVertex3f(particles[i].pos.x, particles[i].pos.y, particles[i].pos.z);
						glVertex3f(particles[i].prevPos.x, particles[i].prevPos.y, particles[i].prevPos.z);
					glEnd();
				}	
			glPopMatrix();
			break;
		case ball:
			glPushMatrix();
				glTranslatef(pos.x, pos.y, pos.z);
				glColor3f(.5, .3, .8);
				glutSolidCube(1.0);

				glColor3f(color.x, color.y, color.z);
				for(int i = 0; i < particles.size() - 1; i++) {
					glPushMatrix();
						glTranslatef(particles[i].pos.x, particles[i].pos.y, particles[i].pos.z);
						glutSolidSphere(.375, 5, 5);
					glPopMatrix();
				}	
			glPopMatrix();
			break;
		//in this case default = spark
		default:
			glPushMatrix();
				glTranslatef(pos.x, pos.y, pos.z);
				glColor3f(.5, .3, .8);
				glutSolidCube(1.0);

				glColor3f(color.x, color.y, color.z);
				for(int i = 0; i < particles.size() - 1; i++) {
					glBegin(GL_LINES);
						glVertex3f(particles[i].pos.x, particles[i].pos.y, particles[i].pos.z);
						glVertex3f(particles[i].prevPos.x, particles[i].prevPos.y, particles[i].prevPos.z);
					glEnd();
				}	
			glPopMatrix();
			break;
	}
}

void Emitter::setType(EMIT_TYPE newType) {
	type = newType;
	setup();
}

void Emitter::setMaxParticles(int max) {
	maxParticles = max;
}

void Emitter::setSplashFactor(float factor) {
	splashFactor = factor;
}

void Emitter::setBounciness(float bounciness) {
	typeBounciness = bounciness;
}
