INCLUDES = -I../UsageEnvironment/include -I../groupsock/include -I../liveMedia/include -I../BasicUsageEnvironment/include
# Default library filename suffixes for each library that we link with.  The "config.*" file might redefine these later.
libliveMedia_LIB_SUFFIX = $(LIB_SUFFIX)
libBasicUsageEnvironment_LIB_SUFFIX = $(LIB_SUFFIX)
libUsageEnvironment_LIB_SUFFIX = $(LIB_SUFFIX)
libgroupsock_LIB_SUFFIX = $(LIB_SUFFIX)
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

PROXY_SERVER = live555ProxyServer$(EXE)

PREFIX = /usr/local
ALL = $(PROXY_SERVER)
all: $(ALL)

.$(C).$(OBJ):
	$(C_COMPILER) -c $(C_FLAGS) $<
.$(CPP).$(OBJ):
	$(CPLUSPLUS_COMPILER) -c $(CPLUSPLUS_FLAGS) $<

PROXY_SERVER_OBJS = live555ProxyServer.$(OBJ)

USAGE_ENVIRONMENT_DIR = ../UsageEnvironment
USAGE_ENVIRONMENT_LIB = $(USAGE_ENVIRONMENT_DIR)/libUsageEnvironment.$(libUsageEnvironment_LIB_SUFFIX)
BASIC_USAGE_ENVIRONMENT_DIR = ../BasicUsageEnvironment
BASIC_USAGE_ENVIRONMENT_LIB = $(BASIC_USAGE_ENVIRONMENT_DIR)/libBasicUsageEnvironment.$(libBasicUsageEnvironment_LIB_SUFFIX)
LIVEMEDIA_DIR = ../liveMedia
LIVEMEDIA_LIB = $(LIVEMEDIA_DIR)/libliveMedia.$(libliveMedia_LIB_SUFFIX)
GROUPSOCK_DIR = ../groupsock
GROUPSOCK_LIB = $(GROUPSOCK_DIR)/libgroupsock.$(libgroupsock_LIB_SUFFIX)
LOCAL_LIBS =	$(LIVEMEDIA_LIB) $(GROUPSOCK_LIB) \
		$(BASIC_USAGE_ENVIRONMENT_LIB) $(USAGE_ENVIRONMENT_LIB)
LIBS =			$(LOCAL_LIBS) $(LIBS_FOR_CONSOLE_APPLICATION)

live555ProxyServer$(EXE):	$(PROXY_SERVER_OBJS) $(LOCAL_LIBS)
	$(LINK)$@ $(CONSOLE_LINK_OPTS) $(PROXY_SERVER_OBJS) $(LIBS)

clean:
	-rm -rf *.$(OBJ) $(ALL) core *.core *~ include/*~

install: $(PROXY_SERVER)
	  install -d $(DESTDIR)$(PREFIX)/bin
	  install -m 755 $(PROXY_SERVER) $(DESTDIR)$(PREFIX)/bin

##### Any additional, platform-specific rules come here:
