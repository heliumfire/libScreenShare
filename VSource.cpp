#include "VSource.hh"
#include <GroupsockHelper.hh>
#include <time.h>// for "gettimeofday()"
//pthread_mutex_t mux;
//bool flag;
VSource*
VSource::createNew(UsageEnvironment& env,
                        VDeviceParameters params) {
    return new VSource(env, params);
}

EventTriggerId VSource::eventTriggerId = 0;
uint8_t* VSource::frameDataStartAddress = 0;
bool VSource::frameAccess = false;
unsigned int VSource::frameSize = 0;
VSource* VSource::instance = NULL;

unsigned VSource::referenceCount = 0;

VSource::VSource(UsageEnvironment& env,
                           VDeviceParameters params)
: FramedSource(env) {
    if (referenceCount == 0) {
        // Any global initialization of the device would be done here:
        //%%% TO BE WRITTEN %%%
    }
    ++referenceCount;
    VSource::instance = this;
    // Any instance-specific initialization of the device would be done here:
    //%%% TO BE WRITTEN %%%
    
    // We arrange here for our "deliverFrame" member function to be called
    // whenever the next frame of data becomes available from the device.
    //
    // If the device can be accessed as a readable socket, then one easy way to do this is using a call to
    //     envir().taskScheduler().turnOnBackgroundReadHandling( ... )
    // (See examples of this call in the "liveMedia" directory.)
    //
    // If, however, the device *cannot* be accessed as a readable socket, then instead we can implement it using 'event triggers':
    // Create an 'event trigger' for this device (if it hasn't already been done):
    if (eventTriggerId == 0) {
        eventTriggerId = envir().taskScheduler().createEventTrigger(deliverFrame0);
    }
}

VSource::~VSource() {
    // Any instance-specific 'destruction' (i.e., resetting) of the device would be done here:
    //%%% TO BE WRITTEN %%%
    
    --referenceCount;
    if (referenceCount == 0) {
        // Any global 'destruction' (i.e., resetting) of the device would be done here:
        //%%% TO BE WRITTEN %%%
        
        // Reclaim our 'event trigger'
        envir().taskScheduler().deleteEventTrigger(eventTriggerId);
        eventTriggerId = 0;
    }
}

void VSource::doGetNextFrame() {
    //printf("Sometimes \n");
    // This function is called (by our 'downstream' object) when it asks for new data.
    
    // Note: If, for some reason, the source device stops being readable (e.g., it gets closed), then you do the following:
    if (0 /* the source stops being readable */ /*%%% TO BE WRITTEN %%%*/) {
        handleClosure();
        return;
    }
   // printf("Lock: %d\n",lock);
    // If a new frame of data is immediately available to be delivered, then do this now:
    if (lock==1) {
        deliverFrame();
        lock=0;
    }
    //printf("Lock: %d\n",lock);
    // No new data is immediately available to be delivered.  We don't do anything more here.
    // Instead, our event trigger must be called (e.g., from a separate thread) when new data becomes available.
}

void VSource::deliverFrame0(void* clientData) {
    //printf("Triggered from another thread\n");
    fflush(stdout);
    //printf("Lock: %d\n",lock);
    if(lock==1)
    VSource::instance->deliverFrame();
    //((VSource*)clientData)->deliverFrame();
}

void VSource::deliverFrame() {
    // This function is called when new frame data is available from the device.
    // We deliver this data by copying it to the 'downstream' object, using the following parameters (class members):
    // 'in' parameters (these should *not* be modified by this function):
    //     fTo: The frame data is copied to this address.
    //         (Note that the variable "fTo" is *not* modified.  Instead,
    //          the frame data is copied to the address pointed to by "fTo".)
    //     fMaxSize: This is the maximum number of bytes that can be copied
    //         (If the actual frame is larger than this, then it should
    //          be truncated, and "fNumTruncatedBytes" set accordingly.)
    // 'out' parameters (these are modified by this function):
    //     fFrameSize: Should be set to the delivered frame size (<= fMaxSize).
    //     fNumTruncatedBytes: Should be set iff the delivered frame would have been
    //         bigger than "fMaxSize", in which case it's set to the number of bytes
    //         that have been omitted.
    //     fPresentationTime: Should be set to the frame's presentation time
    //         (seconds, microseconds).  This time must be aligned with 'wall-clock time' - i.e., the time that you would get
    //         by calling "gettimeofday()".
    //     fDurationInMicroseconds: Should be set to the frame's duration, if known.
    //         If, however, the device is a 'live source' (e.g., encoded from a camera or microphone), then we probably don't need
    //         to set this variable, because - in this case - data will never arrive 'early'.
    // Note the code below.
    //printf("We might be stuck here\n");
    //while(isCurrentlyAwaitingData()){printf("Waiting to access\n");} // we're not ready for the data yet
    //printf("Acessing data %d %d %d\n",fTo,frameDataStartAddress,frameSize);
    //lock = 1;
    static int avgBW = 0;
    static int frameCount = 1;
    static struct timeval te;
    struct timeval  tv;
    gettimeofday(&tv, NULL);
    
    //double time_in_mill =
    //(tv.tv_sec) * 1000 + (tv.tv_usec) / 1000
    pthread_mutex_lock(&mux);
    //printf("Looks fine \n");
    fflush(stdout);
    u_int8_t* newFrameDataStart = VSource::frameDataStartAddress; //(u_int8_t*)0xDEADBEEF; //%%% TO BE WRITTEN %%%
    //printf("Looks fine \n");
    unsigned newFrameSize = frameSize; //%%% TO BE WRITTEN %%%
    //printf("Looks fine \n");
    // Deliver the data here:
    if (newFrameSize > fMaxSize) {
        //printf("Looks fine \n");
        fFrameSize = fMaxSize;
        fNumTruncatedBytes = newFrameSize - fMaxSize;
    } else {
        fFrameSize = newFrameSize;
    }
    //printf("Looks fine \n");
    gettimeofday(&fPresentationTime, NULL); // If you have a more accurate time - e.g., from an encoder - then use that instead.
    // If the device is *not* a 'live source' (e.g., it comes instead from a file or buffer), then set "fDurationInMicroseconds" here.
    memmove(fTo, newFrameDataStart, fFrameSize);
    //printf("Done acessing data \n");
    lock = 0;
    pthread_mutex_unlock(&mux);
    // After delivering the data, inform the reader that it is now available:
    FramedSource::afterGetting(this);
    //gettimeofday(&tv, NULL);
    //te = tv;
    struct timeval res;
    timersub(&tv,&te,&res);
    avgBW = (avgBW*(frameCount-1)+(frameSize/(1000*(res.tv_sec)+(res.tv_usec/1000))))/frameCount;
    frameCount++;
    //printf("We are transmitting at %ld fps %d kbps \n",(1000/(1000*(res.tv_sec)+(res.tv_usec/1000))),(frameSize/(1000*(res.tv_sec)+(res.tv_usec/1000))));
    te = tv;
}

bool VSource::isCurrentlyAwaitingData(){
    //bool wait = VSource::frameAccess;
    return lock;
}

// The following code would be called to signal that a new frame of data has become available.
// This (unlike other "LIVE555 Streaming Media" library code) may be called from a separate thread.
// (Note, however, that "triggerEvent()" cannot be called with the same 'event trigger id' from different threads.
// Also, if you want to have multiple device threads, each one using a different 'event trigger id', then you will need
// to make "eventTriggerId" a non-static member variable of "VSource".)
void signalNewFrameData() {
    TaskScheduler* ourScheduler = NULL; //%%% TO BE WRITTEN %%%
    VSource* ourDevice  = NULL; //%%% TO BE WRITTEN %%%
    
    if (ourScheduler != NULL) { // sanity check
        ourScheduler->triggerEvent(VSource::eventTriggerId, ourDevice);
    }
}
