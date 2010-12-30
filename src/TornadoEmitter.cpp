#include "TornadoEmitter.h"

TornadoEmitter::TornadoEmitter(int _maxParticles, int _emitRate, int _lifeTime, EMIT_TYPE _type):
	Emitter(_maxParticles, _emitRate, _lifeTime, _type) {
	setup();
}

void TornadoEmitter::setup() {
	switch(type) {
		case smoke:
			color.set(0.6, 0.6, 0.6);
			typeBounciness = 0;
			typeWeight = 0.1;
			splashFactor = 0.5;
			break;
		//in this case default = tornado
		default:
			color.set(1, 0.5, 0);
			typeBounciness = 0.8;
			typeWeight = 0.7;
			splashFactor = 0.3;
			break;
	}
}

void TornadoEmitter::maintainParticles(ofPoint force) {
	vector<Particle>::iterator it = particles.begin();
	ofPoint normal;
	normal.set(0, 0, 0);
	while(it != particles.end()) {
		if(it->life > 0) {
			it->prevPos.x = it->pos.x;
			it->prevPos.y = it->pos.y;
			it->prevPos.z = it->pos.z;

			it->pos.x += it->vel.x;
			it->pos.y += it->vel.y;
			it->pos.z += it->vel.z;

			normal.x = it->pos.y * (-1);
			normal.y = it->pos.x;

			float magnitude = 1 / sqrt(normal.x * normal.x + normal.y * normal.y);

			it->pos.x += normal.x * magnitude;
			it->pos.y += normal.y * magnitude;

			if(it->pos.z <= -pos.z) {
				//smoke behaves a bit different
				switch(type) {
					case smoke:
						it->life = 0;
						break;
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

void TornadoEmitter::draw() {
	switch(type) {
		case smoke:
			glPushMatrix();
				glTranslatef(pos.x, pos.y, pos.z);
				//that's the emitter
				glColor3f(.5, .3, .8);
				glutSolidCube(1.0);

				for(vector<Particle>::iterator it = particles.begin(); it != particles.end(); it++) {
					glColor4f(color.x, color.y, color.z, it->life / lifeTime);
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glPushMatrix();
						glTranslatef(it->pos.x, it->pos.y, it->pos.z);
						glutSolidSphere(3.5, 5, 5);
					glPopMatrix();

					glDisable(GL_BLEND);
				}
			glPopMatrix();
			break;
		//in this case default = tornado
		default:
			glPushMatrix();
				glTranslatef(pos.x, pos.y, pos.z);
				//that's the emitter
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