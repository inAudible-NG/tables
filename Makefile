alglib1.so:
	g++ -Wall -O3 -shared -fPIC alglib1.cpp sha1.c -o alglib1.so

windows:
	# yum install mingw32-openssl mingw32-openssl-static mingw32-gcc mingw32-gcc-c++ mingw32-winpthreads-static -y
	i686-w64-mingw32-g++ -c alglib1.cpp
	i686-w64-mingw32-g++ -static -shared -o alglib1.dll alglib1.o -lcrypto -lpthread

	# yum install mingw64-openssl mingw64-openssl-static mingw64-gcc mingw64-gcc-c++ mingw64-winpthreads-static mingw64-zlib-static mingw64-libgomp -y
	x86_64-w64-mingw32-g++ -c alglib1.cpp -lcrypto
	x86_64-w64-mingw32-g++ -static -shared -o alglib1.dll alglib1.o -lcrypto -lpthread
