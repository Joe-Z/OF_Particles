#ifndef TornadoEmitter_H_INCLUDED
#define TornadoEmitter_H_INCLUDED

#include "Emitter.h"

class TornadoEmitter : public Emitter {
public:
	TornadoEmitter(int _maxParticles, int _emitRate, int _lifeTime,
				   EMIT_TYPE _type = tornado);
	~TornadoEmitter();
	virtual void setup();
	virtual void maintainParticles(ofPoint force);
	virtual void draw();

	//all attributes from emitter-class
};

#endif //TornadoEmitter_H_INCLUDED