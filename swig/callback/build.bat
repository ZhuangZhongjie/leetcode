SET TARGET=_%1
swig -c++ -python %1.i
cl.exe /Z7 /Od /Wall /EHsc /nologo -I C:\Python27\include *.cxx /link -dll -out:%TARGET%.pyd C:\Python27\libs\Python27.lib
del %TARGET%.exp %TARGET%.ilk %TARGET%.pdb %TARGET%.lib