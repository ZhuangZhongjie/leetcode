/* File : example.i */
%module(directors="1") example
%{
#include "example.h"
%}

/* turn on director wrapping Callback */
%feature("director") Callback;

// %include "example.h"

class Callback {
public:
	virtual ~Callback();
	virtual void run();	
};

class Caller {
public:
	void delCallback();
	void setCallback(Callback *cb);
	void call();
};

class ScriptObjectContainer {
public:	
	PyObject * getScriptObject();
	void setScriptObject(PyObject * script_obj);
	void clearScriptObject();
};

class SelfProxy {
public:
	PyObject * getSelfProxy();
	void setSelfProxy(PyObject * self_proxy);
};




