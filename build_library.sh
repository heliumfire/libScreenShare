#!/bin/sh


#Change these variables to your setting

NDK=/usr/android/android-ndk-r10b/
TOOLCHAIN=arm-linux-androideabi-4.8
TARGET_ANDROID_VERSION=19
TARGET_ARCH=arm
TARGET_LIBAV_VERSION=11.3
LIBSTDCPP_VERSION=4.8
VERSION=0.1
VERSION_SUFFIX=beta

#Do not change anything below this line, Unless you know what you are doing

TOOLCHAIN_PATH=$NDK/toolchains/$TOOLCHAIN/prebuilt/darwin-x86_64
COMPILER_PREFIX=$TOOLCHAIN_PATH/bin/arm-linux-androideabi-
SYSROOT=$NDK/platforms/android-$TARGET_ANDROID_VERSION/arch-$TARGET_ARCH
CPP_LIBS=$NDK/sources/cxx-stl/gnu-libstdc++/$LIBSTDCPP_VERSION/libs/armeabi-v7a
INTERMEDIATES=libScreenShare-$VERSION-$VERSION_SUFFIX-INTERMEDIATES
CPP=${COMPILER_PREFIX}g++

RED='\033[0;31m'
GREEN='\033[0;34m'
BLUE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'

if [ "$(uname)" == "Darwin" ]; then
    ECHO=echo
    HOST_SYSTEM=DARWIN
    N_CPU=`sysctl -n hw.physicalcpu`
else
    HOST_SYSTEM=LINUX
    ECHO=echo -e
    N_CPU=`nproc`
fi


$ECHO "$BLUE============================$RED Building libScreenShare V$VERSION-$VERSION_SUFFIX $BLUE==============================$NC"
$ECHO " "
$ECHO "           $GREEN Android Version   $BLUE= $CYAN $TARGET_ANDROID_VERSION $NC"
$ECHO "           $GREEN Architecture      $BLUE= $CYAN $TARGET_ARCH $NC"
$ECHO "           $GREEN Toolchain         $BLUE= $CYAN $TOOLCHAIN $NC"
$ECHO "           $GREEN LibAV version     $BLUE= $CYAN $TARGET_LIBAV_VERSION $NC"
$ECHO "           $GREEN Libstdc++ version $BLUE= $CYAN $LIBSTDCPP_VERSION $NC"
$ECHO " "
$ECHO "$BLUE - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - $NC"
$ECHO " "
$ECHO "           $GREEN NDK path          $BLUE= $CYAN $NDK $NC"
$ECHO "           $GREEN Toolchain path    $BLUE= $CYAN $TOOLCHAIN_PATH $NC"
$ECHO "           $GREEN Sysroot Path      $BLUE= $CYAN $SYSROOT $NC"
$ECHO "           $GREEN Compiler prefix   $BLUE= $CYAN $COMPILER_PREFIX $NC"
$ECHO "           $GREEN HOST SYSTEM       $BLUE= $CYAN $HOST_SYSTEM $NC"
$ECHO "           $GREEN Host CPU no       $BLUE= $CYAN $N_CPU $NC"
$ECHO " "
$ECHO "$BLUE==============================================================================================$NC"
#rm -r $INTERMEDIATES
$CPP -oscreenshare -I. --sysroot=$SYSROOT main.cpp ScreenShare.cpp MPEG1or2VideoScreenMediaSubsession.cpp VSource.cpp strSrc.cpp $INTERMEDIATES/lib/*.a -I$INTERMEDIATES/include -I$INTERMEDIATES/include/groupsock -I$INTERMEDIATES/include/UsageEnvironment -I$INTERMEDIATES/include/liveMedia -I$INTERMEDIATES/include/BasicUsageEnvironment -D__STDC_CONSTANT_MACROS -fpermissive -lz -lm -lgnustl_static -lsupc++
rm -r libav_build_$TARGET_LIBAV_VERSION
mkdir -p libav_build_$TARGET_LIBAV_VERSION
cd libav_build_$TARGET_LIBAV_VERSION
../libav-$TARGET_LIBAV_VERSION/configure \
			--arch=$TARGET_ARCH 				\
			--target-os=android				\
			--cross-prefix=$COMPILER_PREFIX			\
			--sysroot=$SYSROOT				\
			--sysinclude=$SYSROOT/usr/include		\
			--extra-cflags="-I$SYSROOT/include"		\
			--prefix=`pwd`/../$INTERMEDIATES		\
			--disable-programs			
make -j$N_CPU
make install
make distclean

cd ..
rm live/config.android
echo "CROSS_COMPILE=$COMPILER_PREFIX " > live/config.android
echo "COMPILE_OPTS=-I$SYSROOT/usr/include \${INCLUDES} -I. -O2 -DSOCKLEN_T=socklen_t -DNO_SSTREAM=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 -DLOCALE_NOT_USED -DXLOCALE_NOT_USED -D__STDC_CONSTANT_MACROS" >> live/config.android
echo "C=c" >> live/config.android
echo "C_COMPILER=${COMPILER_PREFIX}gcc" >> live/config.android
echo "C_FLAGS=$CFLAGS \${COMPILE_OPTS} " >> live/config.android
echo "CPP=cpp" >> live/config.android
echo "CPLUSPLUS_COMPILER=${COMPILER_PREFIX}g++" >> live/config.android
echo "CPLUSPLUS_FLAGS=${CPPFLAGS} \${COMPILE_OPTS} -Wall -DBSD=1" >> live/config.android
echo "OBJ=o" >> live/config.android
echo "LINK=${COMPILER_PREFIX}g++ -o" >> live/config.android
echo "LINK_OPTS=${LDFLAGS} -L$CPP_LIBS -lgnustl_shared --sysroot=$SYSROOT" >> live/config.android ##Only required to link executables. Library compiles without gnustl_shared
echo "CONSOLE_LINK_OPTS=\${LINK_OPTS}" >> live/config.android
echo "LIBRARY_LINK=${COMPILER_PREFIX}ar cr " >> live/config.android
#echo "LIBRARY_LINK_OPTS=\${LINK_OPTS}" >> live/config.android
echo "LIB_SUFFIX=a" >> live/config.android
echo "LIBS_FOR_CONSOLE_APPLICATION=" >> live/config.android
echo "LIBS_FOR_GUI_APPLICATION=" >> live/config.android
echo "EXE=" >> live/config.android
cd live
./genMakefiles android
make clean -j$N_CPU
make -j$N_CPU	

cd ..
mkdir -p $INTERMEDIATES/include/groupsock
mkdir -p $INTERMEDIATES/include/UsageEnvironment
mkdir -p $INTERMEDIATES/include/liveMedia
mkdir -p $INTERMEDIATES/include/BasicUsageEnvironment
cp live/liveMedia/libliveMedia.a $INTERMEDIATES/lib/
cp live/BasicUsageEnvironment/libBasicUsageEnvironment.a $INTERMEDIATES/lib/
cp live/UsageEnvironment/libUsageEnvironment.a $INTERMEDIATES/lib/
cp live/groupsock/libgroupsock.a $INTERMEDIATES/lib/
cp -r live/groupsock/include/* $INTERMEDIATES/include/groupsock
cp -r live/UsageEnvironment/include/* $INTERMEDIATES/include/UsageEnvironment
cp -r live/liveMedia/include/* $INTERMEDIATES/include/liveMedia
cp -r live/BasicUsageEnvironment/include/* $INTERMEDIATES/include/BasicUsageEnvironment
cd live
make clean
cd ..

rm -r libav_build_$TARGET_LIBAV_VERSION


$CPP -oscreenshare -I. --sysroot=$SYSROOT main.cpp ScreenShare.cpp MPEG1or2VideoScreenMediaSubsession.cpp VSource.cpp strSrc.cpp $INTERMEDIATES/lib/*.a -I$INTERMEDIATES/include -I$INTERMEDIATES/include/groupsock -I$INTERMEDIATES/include/UsageEnvironment -I$INTERMEDIATES/include/liveMedia -I$INTERMEDIATES/include/BasicUsageEnvironment -D__STDC_CONSTANT_MACROS