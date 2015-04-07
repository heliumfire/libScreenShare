#include <stdio.h>
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "MPEG1or2VideoScreenMediaSubsession.hh"
#include "VSource.hh"
extern "C"{
#include "libavcodec/avcodec.h"
#include "libavutil/channel_layout.h"
#include "libavutil/common.h"
#include "libavutil/imgutils.h"
#include "libavutil/mathematics.h"
#include "libavutil/samplefmt.h"
#include <libswscale/swscale.h>
#include <linux/fb.h>
#include <asm-generic/fcntl.h>
#include <fcntl.h>
#include <sys/mman.h>
//#include "neon_conv.h"
}

class strSrc{
public:
    strSrc(TaskScheduler *schd, VSource* vs, char* fbDev);
    void startEncoding();
    AVCodec *codec;
    AVCodecContext *c= NULL;
    int i, ret, x, y, got_output;
    AVFrame *picture, *iput;
    AVPacket pkt;
private:
    void EncodeFrame();
    VSource *sink;
    TaskScheduler* tsc;
    uint8_t* fbp;
    int fbfd;
    struct fb_var_screeninfo vscreeninfo;
    struct fb_fix_screeninfo fscreeninfo;
};
