##### Change the following for your environment:
CROSS_COMPILE=/usr/android/android-ndk-r10b//toolchains/arm-linux-androideabi-4.8/prebuilt/darwin-x86_64/bin/arm-linux-androideabi- 
COMPILE_OPTS=-I/usr/android/android-ndk-r10b//platforms/android-19/arch-arm/usr/include ${INCLUDES} -I. -O2 -DSOCKLEN_T=socklen_t -DNO_SSTREAM=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -DLOCALE_NOT_USED -DXLOCALE_NOT_USED -D__STDC_CONSTANT_MACROS
C=c
C_COMPILER=/usr/android/android-ndk-r10b//toolchains/arm-linux-androideabi-4.8/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc
C_FLAGS= ${COMPILE_OPTS} 
CPP=cpp
CPLUSPLUS_COMPILER=/usr/android/android-ndk-r10b//toolchains/arm-linux-androideabi-4.8/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-g++
CPLUSPLUS_FLAGS= ${COMPILE_OPTS} -Wall -DBSD=1
OBJ=o
LINK=/usr/android/android-ndk-r10b//toolchains/arm-linux-androideabi-4.8/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-g++ -o
LINK_OPTS= -L/usr/android/android-ndk-r10b//sources/cxx-stl/gnu-libstdc++/4.8/libs/armeabi-v7a -lgnustl_shared --sysroot=/usr/android/android-ndk-r10b//platforms/android-19/arch-arm
CONSOLE_LINK_OPTS=${LINK_OPTS}
LIBRARY_LINK=/usr/android/android-ndk-r10b//toolchains/arm-linux-androideabi-4.8/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-ar cr 
LIB_SUFFIX=a
LIBS_FOR_CONSOLE_APPLICATION=
LIBS_FOR_GUI_APPLICATION=
EXE=
##### End of variables to change

LIVEMEDIA_DIR = liveMedia
GROUPSOCK_DIR = groupsock
USAGE_ENVIRONMENT_DIR = UsageEnvironment
BASIC_USAGE_ENVIRONMENT_DIR = BasicUsageEnvironment

TESTPROGS_DIR = testProgs

MEDIA_SERVER_DIR = mediaServer

PROXY_SERVER_DIR = proxyServer

all:
	cd $(LIVEMEDIA_DIR) ; $(MAKE)
	cd $(GROUPSOCK_DIR) ; $(MAKE)
	cd $(USAGE_ENVIRONMENT_DIR) ; $(MAKE)
	cd $(BASIC_USAGE_ENVIRONMENT_DIR) ; $(MAKE)
	cd $(TESTPROGS_DIR) ; $(MAKE)
	cd $(MEDIA_SERVER_DIR) ; $(MAKE)
	cd $(PROXY_SERVER_DIR) ; $(MAKE)

install:
	cd $(LIVEMEDIA_DIR) ; $(MAKE) install
	cd $(GROUPSOCK_DIR) ; $(MAKE) install
	cd $(USAGE_ENVIRONMENT_DIR) ; $(MAKE) install
	cd $(BASIC_USAGE_ENVIRONMENT_DIR) ; $(MAKE) install
	cd $(TESTPROGS_DIR) ; $(MAKE) install
	cd $(MEDIA_SERVER_DIR) ; $(MAKE) install
	cd $(PROXY_SERVER_DIR) ; $(MAKE) install

clean:
	cd $(LIVEMEDIA_DIR) ; $(MAKE) clean
	cd $(GROUPSOCK_DIR) ; $(MAKE) clean
	cd $(USAGE_ENVIRONMENT_DIR) ; $(MAKE) clean
	cd $(BASIC_USAGE_ENVIRONMENT_DIR) ; $(MAKE) clean
	cd $(TESTPROGS_DIR) ; $(MAKE) clean
	cd $(MEDIA_SERVER_DIR) ; $(MAKE) clean
	cd $(PROXY_SERVER_DIR) ; $(MAKE) clean

distclean: clean
	-rm -f $(LIVEMEDIA_DIR)/Makefile $(GROUPSOCK_DIR)/Makefile \
	  $(USAGE_ENVIRONMENT_DIR)/Makefile $(BASIC_USAGE_ENVIRONMENT_DIR)/Makefile \
	  $(TESTPROGS_DIR)/Makefile $(MEDIA_SERVER_DIR)/Makefile \
	  $(PROXY_SERVER_DIR)/Makefile Makefile
