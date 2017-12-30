/* File : example.h */
#include "Python.h"
#include <iostream>

class Callback {
public:
	virtual ~Callback() { std::cout << "Callback::~Callback()" << std:: endl; }
	virtual void run() { std::cout << "Callback::run()" << std::endl; }
};


class Caller {
private:
	Callback *_callback;
public:
	Caller(): _callback(0) {}
	~Caller() { delCallback(); }
	void delCallback() { delete _callback; _callback = 0; }
	void setCallback(Callback *cb) { delCallback(); _callback = cb; }
	void call() { if (_callback) _callback->run(); }
};

class ScriptObjectContainer {
private:
	PyObject * _script_obj;

public:
	ScriptObjectContainer(): _script_obj(nullptr) {}
	PyObject * getScriptObject() 
	{ 
		if (_script_obj == nullptr) {
			Py_RETURN_NONE;
		}
		Py_INCREF(_script_obj); 
		return _script_obj; 
	}
	void setScriptObject(PyObject * script_obj) { _script_obj = script_obj; Py_INCREF(_script_obj); }
	void clearScriptObject() {
		if (_script_obj != nullptr) {
			Py_DECREF(_script_obj); 
			_script_obj = nullptr; 
		}
	}
	~ScriptObjectContainer() { clearScriptObject(); }
};

class SelfProxy {
private:
	PyObject * self;

public:
	SelfProxy(): self(nullptr) {  std::cout << "SelfProxy ctor" << std::endl;  }

	PyObject * getSelfProxy() { 
		if (self == nullptr) {
			Py_RETURN_NONE;
		}
		Py_INCREF(self); 
		return self; 
	}

	void setSelfProxy(PyObject * self_proxy) {
		self = self_proxy;
	}

	~SelfProxy() { self = nullptr; std::cout << "SelfProxy dtor" << std::endl;  }

};
