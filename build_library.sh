#!/bin/sh


#Change these variables to your setting

NDK=/home/anushruth/tools/android-ndk-r10d
TOOLCHAIN=arm-linux-androideabi-4.9
TARGET_ANDROID_VERSION=21
TARGET_ARCH=arm
TARGET_LIBAV_VERSION=11.3
LIBSTDCPP_VERSION=4.9
VERSION=0.1
VERSION_SUFFIX=beta

#Do not change anything below this line, Unless you know what you are doing

TOOLCHAIN_PATH=$NDK/toolchains/$TOOLCHAIN/prebuilt/linux-x86_64
COMPILER_PREFIX=$TOOLCHAIN_PATH/bin/arm-linux-androideabi-
SYSROOT=$NDK/platforms/android-$TARGET_ANDROID_VERSION/arch-$TARGET_ARCH
CPP_LIBS=$NDK/sources/cxx-stl/gnu-libstdc++/$LIBSTDCPP_VERSION/libs/armeabi-v7a
N_CPU=`nproc`
INTERMEDIATES=libScreenShare-$VERSION-$VERSION_SUFFIX-INTERMEDIATES

RED='\033[0;31m'
GREEN='\033[0;34m'
BLUE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m'


echo -e "$BLUE============================$RED Building libScreenShare V$VERSION-$VERSION_SUFFIX $BLUE==============================$NC"
echo -e " "
echo -e "           $GREEN Android Version   $BLUE= $CYAN $TARGET_ANDROID_VERSION $NC"
echo -e "           $GREEN Architecture      $BLUE= $CYAN $TARGET_ARCH $NC"
echo -e "           $GREEN Toolchain         $BLUE= $CYAN $TOOLCHAIN $NC"
echo -e "           $GREEN LibAV version     $BLUE= $CYAN $TARGET_LIBAV_VERSION $NC"
echo -e "           $GREEN Libstdc++ version $BLUE= $CYAN $LIBSTDCPP_VERSION $NC"
echo " "
echo -e "$BLUE - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - $NC"
echo " "
echo -e "           $GREEN NDK path          $BLUE= $CYAN $NDK $NC"
echo -e "           $GREEN Toolchain path    $BLUE= $CYAN $TOOLCHAIN_PATH $NC"
echo -e "           $GREEN Sysroot Path      $BLUE= $CYAN $SYSROOT $NC"
echo -e "           $GREEN Compiler prefix   $BLUE= $CYAN $COMPILER_PREFIX $NC"
echo -e "           $GREEN Host CPU no       $BLUE= $CYAN $N_CPU $NC"
echo " "
echo -e "$BLUE==============================================================================================$NC"          
rm -r $INTERMEDIATES
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
echo "COMPILE_OPTS=-I$SYSROOT/usr/include \$(INCLUDES) -I. -O2 -DSOCKLEN_T=socklen_t -DNO_SSTREAM=1 -D_LARGEFILE_SOURCE=1 -D_FILE_OFFSET_BITS=64 " >> live/config.android
echo "C=c" >> live/config.android
echo "C_COMPILER=${COMPILER_PREFIX}gcc" >> live/config.android
echo "C_FLAGS=$CFLAGS \${COMPILE_OPTS}" >> live/config.android
echo "CPP=cpp" >> live/config.android
echo "CPLUSPLUS_COMPILER=${COMPILER_PREFIX}g++" >> live/config.android
echo "CPLUSPLUS_FLAGS=${CPPFLAGS} \${COMPILE_OPTS} -Wall -DBSD=1" >> live/config.android
echo "OBJ=o" >> live/config.android
echo "LINK=${COMPILER_PREFIX}g++ -o" >> live/config.android
echo "LINK_OPTS=${LDFLAGS} -L$CPP_LIBS -lgnustl_shared  -L$SYSROOT/usr/lib" >> live/config.android ##Only required to link executables. Library compiles without gnustl_shared
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
