#ifndef _VSOURCE_HH
#define _VSOURCE_HH

#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif
extern "C" {
#include <pthread.h>
}

/*#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

extern "C"{
#include "libavcodec/avcodec.h"
#include "libavutil/channel_layout.h"
#include "libavutil/common.h"
#include "libavutil/imgutils.h"
#include "libavutil/mathematics.h"
#include "libavutil/samplefmt.h"
}*/
class VDeviceParameters {
    //%%% TO BE WRITTEN %%%
};
extern bool lock;
extern pthread_mutex_t mux;
class VSource : public FramedSource {


public:
    static VSource* createNew(UsageEnvironment& env, VDeviceParameters params);
    static EventTriggerId eventTriggerId;
    static uint8_t* frameDataStartAddress;
    static bool frameAccess;
    static unsigned int frameSize;
    static VSource* instance;
    bool isCurrentlyAwaitingData();
    
protected:
    VSource(UsageEnvironment& env, VDeviceParameters params);
    virtual ~VSource();
private:
    virtual void doGetNextFrame();
    static void deliverFrame0(void *clientData);
    void deliverFrame();
    static unsigned referenceCount;
};
#endif