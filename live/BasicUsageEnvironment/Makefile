INCLUDES = -Iinclude -I../UsageEnvironment/include -I../groupsock/include
PREFIX = /usr/local
LIBDIR = $(PREFIX)/lib
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

NAME = libBasicUsageEnvironment
LIB = $(NAME).$(LIB_SUFFIX)
ALL = $(LIB)
all:	$(ALL)

OBJS = BasicUsageEnvironment0.$(OBJ) BasicUsageEnvironment.$(OBJ) \
	BasicTaskScheduler0.$(OBJ) BasicTaskScheduler.$(OBJ) \
	DelayQueue.$(OBJ) BasicHashTable.$(OBJ)

libBasicUsageEnvironment.$(LIB_SUFFIX): $(OBJS)
	$(LIBRARY_LINK)$@ $(LIBRARY_LINK_OPTS) \
		$(OBJS)

.$(C).$(OBJ):
	$(C_COMPILER) -c $(C_FLAGS) $<       

.$(CPP).$(OBJ):
	$(CPLUSPLUS_COMPILER) -c $(CPLUSPLUS_FLAGS) $<

BasicUsageEnvironment0.$(CPP):	include/BasicUsageEnvironment0.hh
include/BasicUsageEnvironment0.hh:	include/BasicUsageEnvironment_version.hh include/DelayQueue.hh
BasicUsageEnvironment.$(CPP):	include/BasicUsageEnvironment.hh
include/BasicUsageEnvironment.hh:	include/BasicUsageEnvironment0.hh
BasicTaskScheduler0.$(CPP):	include/BasicUsageEnvironment0.hh include/HandlerSet.hh
BasicTaskScheduler.$(CPP):	include/BasicUsageEnvironment.hh include/HandlerSet.hh
DelayQueue.$(CPP):		include/DelayQueue.hh
BasicHashTable.$(CPP):		include/BasicHashTable.hh

clean:
	-rm -rf *.$(OBJ) $(ALL) core *.core *~ include/*~

install: install1 $(INSTALL2)
install1: libBasicUsageEnvironment.$(LIB_SUFFIX)
	  install -d $(DESTDIR)$(PREFIX)/include/BasicUsageEnvironment $(DESTDIR)$(LIBDIR)
	  install -m 644 include/*.hh $(DESTDIR)$(PREFIX)/include/BasicUsageEnvironment
	  install -m 644 libBasicUsageEnvironment.$(LIB_SUFFIX) $(DESTDIR)$(LIBDIR)
install_shared_libraries: libBasicUsageEnvironment.$(LIB_SUFFIX)
	  ln -s $(NAME).$(LIB_SUFFIX) $(DESTDIR)$(LIBDIR)/$(NAME).$(SHORT_LIB_SUFFIX)
	  ln -s $(NAME).$(LIB_SUFFIX) $(DESTDIR)$(LIBDIR)/$(NAME).so

##### Any additional, platform-specific rules come here:
