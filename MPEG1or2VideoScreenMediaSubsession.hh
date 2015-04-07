/*
 *		libScreenShare
 *
 *              MPEG1or2VideoScreenMediaSubsession.hh
 *
 *
 *		Author: 	regnarts
 *		Owner: 		Musumbii
 *		Email:		regnarts299792458@gmail.com
 *		Bugs:
 *		Phone:
 *
 *		Description:
 *
 *			This class encapsulates everything that the library intends to do. The logic to
 *			grab the framebuffer, encoding logic and the transmission. The class can be built
 *			along with an executable or used as a jni binding library. For full description
 *			please check the docs. For a quick look into what this can do and for compile
 * 			instructions please see README.
 *
 */




#ifndef _MPEG_1OR2_VIDEO_SCREEN_MEDIA_SUBSESSION_HH
#define _MPEG_1OR2_VIDEO_SCREEN_MEDIA_SUBSESSION_HH
#include "VSource.hh"
#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "OnDemandServerMediaSubsession.hh"
#endif

class MPEG1or2VideoScreenMediaSubsession: public OnDemandServerMediaSubsession{
public:
    static MPEG1or2VideoScreenMediaSubsession*
    createNew(UsageEnvironment& env, Boolean reuseFirstSource,
              Boolean iFramesOnly = False,
              double vshPeriod = 5.0
    /* how often (in seconds) to inject a Video_Sequence_Header,
     if one doesn't already appear in the stream */);
    static VSource* vs;
    
private:
    MPEG1or2VideoScreenMediaSubsession(UsageEnvironment& env,
                                       Boolean reuseFirstSource,
                                           Boolean iFramesOnly,
                                           double vshPeriod);
    // called only by createNew();
public:
    virtual ~MPEG1or2VideoScreenMediaSubsession();
    
private: // redefined virtual functions
    virtual FramedSource* createNewStreamSource(unsigned /*clientSessionId*/,unsigned& estBitrate);
                                                //ScreenParameters params);
    virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                      unsigned char rtpPayloadTypeIfDynamic,
                                      FramedSource* inputSource);
    
private:
    UsageEnvironment& t_env;
    Boolean fIFramesOnly;
    double fVSHPeriod;
};

#endif
