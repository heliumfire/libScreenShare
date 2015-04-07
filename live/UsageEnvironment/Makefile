INCLUDES = -Iinclude -I../groupsock/include
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

NAME = libUsageEnvironment
USAGE_ENVIRONMENT_LIB = $(NAME).$(LIB_SUFFIX)
ALL = $(USAGE_ENVIRONMENT_LIB)
all:	$(ALL)

OBJS = UsageEnvironment.$(OBJ) HashTable.$(OBJ) strDup.$(OBJ)

$(USAGE_ENVIRONMENT_LIB): $(OBJS)
	$(LIBRARY_LINK)$@ $(LIBRARY_LINK_OPTS) $(OBJS)

.$(C).$(OBJ):
	$(C_COMPILER) -c $(C_FLAGS) $<       

.$(CPP).$(OBJ):
	$(CPLUSPLUS_COMPILER) -c $(CPLUSPLUS_FLAGS) $<

UsageEnvironment.$(CPP):	include/UsageEnvironment.hh
include/UsageEnvironment.hh:	include/UsageEnvironment_version.hh include/Boolean.hh include/strDup.hh
HashTable.$(CPP):		include/HashTable.hh
include/HashTable.hh:		include/Boolean.hh
strDup.$(CPP):			include/strDup.hh

clean:
	-rm -rf *.$(OBJ) $(ALL) core *.core *~ include/*~

install: install1 $(INSTALL2)
install1: $(USAGE_ENVIRONMENT_LIB)
	  install -d $(DESTDIR)$(PREFIX)/include/UsageEnvironment $(DESTDIR)$(LIBDIR)
	  install -m 644 include/*.hh $(DESTDIR)$(PREFIX)/include/UsageEnvironment
	  install -m 644 $(USAGE_ENVIRONMENT_LIB) $(DESTDIR)$(LIBDIR)
install_shared_libraries: $(USAGE_ENVIRONMENT_LIB)
	  ln -s $(NAME).$(LIB_SUFFIX) $(DESTDIR)$(LIBDIR)/$(NAME).$(SHORT_LIB_SUFFIX)
	  ln -s $(NAME).$(LIB_SUFFIX) $(DESTDIR)$(LIBDIR)/$(NAME).so

##### Any additional, platform-specific rules come here:
