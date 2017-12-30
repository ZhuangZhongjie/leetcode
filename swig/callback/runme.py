# file: runme.py

# This file illustrates the cross language polymorphism using directors.

import example


class PyCallback(example.Callback):

    def __init__(self):
        example.Callback.__init__(self)

    def run(self):
        print "PyCallback.run()"

# Create an Caller instance

caller = example.Caller()

# Add a simple C++ callback (caller owns the callback, so
# we disown it first by clearing the .thisown flag).

print "Adding and calling a normal C++ callback"
print "----------------------------------------"

callback = example.Callback()
callback.thisown = 0
caller.setCallback(callback)
caller.call()
caller.delCallback()

print
print "Adding and calling a Python callback"
print "------------------------------------"

# Add a Python callback (caller owns the callback, so we
# disown it first by calling __disown__).

caller.setCallback(PyCallback().__disown__())
caller.call()
caller.delCallback()

print
print "Adding and calling another Python callback"
print "------------------------------------------"

# Let's do the same but use the weak reference this time.

callback = PyCallback().__disown__()
caller.setCallback(callback)
caller.call()
caller.delCallback()

print
print "Test ScriptObjectContainer"
print "--------------------------"

# Test ScriptObjectContainer
class A(object):
	def __init__(self):
		print 'A init', self

	def __del__(self):
		print 'A del', self

	def run(self):
		print 'A run', self

soc = example.ScriptObjectContainer()
a = A()
# a = PyCallback()
soc.setScriptObject(a)
print a
a = None
print soc.getScriptObject()
soc.getScriptObject().run()
soc.clearScriptObject()

print
print "Test self proxy"
print "---------------"

s = example.SelfProxy()
s.setSelfProxy(s)
soc.setScriptObject(s)
s = None
print '1'


# All done.

print
print "python exit"
