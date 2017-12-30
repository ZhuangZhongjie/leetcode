SET TARGET=%1
SET BOOST_INC=F:\MobileServer\trunk\mobileasyncore\build_win\build_win
SET BOOST_LIB=F:\MobileServer\trunk\mobileasyncore\build_win\build_win\libs\win32

cl.exe /Od /EHsc /nologo -I %BOOST_INC% -D_WIN32_WINDOWS -DBOOST_ALL_NO_LIB %TARGET% /link /LIBPATH:"%BOOST_LIB%" boost_system-vc140-mt-1_59.lib boost_thread-vc140-mt-1_59.lib