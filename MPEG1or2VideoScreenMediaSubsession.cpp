#include "MPEG1or2VideoScreenMediaSubsession.hh"
#include "MPEG1or2VideoRTPSink.hh"
#include "VSource.hh"
#include "MPEG1or2VideoStreamDiscreteFramer.hh"

MPEG1or2VideoScreenMediaSubsession*
MPEG1or2VideoScreenMediaSubsession::createNew(UsageEnvironment& env,
                                                  Boolean reuseFirstSource,
                                                  Boolean iFramesOnly,
                                                  double vshPeriod) {
    return new MPEG1or2VideoScreenMediaSubsession(env, reuseFirstSource, iFramesOnly, vshPeriod);
}

VSource* MPEG1or2VideoScreenMediaSubsession::vs = NULL;

MPEG1or2VideoScreenMediaSubsession
::MPEG1or2VideoScreenMediaSubsession(UsageEnvironment& env,
                                         Boolean reuseFirstSource,
                                         Boolean iFramesOnly,
                                         double vshPeriod)
: OnDemandServerMediaSubsession(env, reuseFirstSource),
fIFramesOnly(iFramesOnly), fVSHPeriod(vshPeriod), t_env(env) {
    vs = NULL;
}

MPEG1or2VideoScreenMediaSubsession
::~MPEG1or2VideoScreenMediaSubsession() {
}

FramedSource* MPEG1or2VideoScreenMediaSubsession
::createNewStreamSource(unsigned /*clientSessionId*/,unsigned& estBitrate) {
    estBitrate = 500; // kbps, estimate
    VDeviceParameters params;
    VSource* retvs = VSource::createNew(envir(),params);
    vs = retvs;
    return MPEG1or2VideoStreamDiscreteFramer::createNew(t_env,
                                                        retvs,
                                                        fIFramesOnly,
                                                        fVSHPeriod,
                                                        1);//retvs;//, fIFramesOnly, fVSHPeriod); //TODO: Need some corrections here
    /*return MPEG1or2VideoStreamFramer
    ::createNew(envir(), ScreenSource
                ::createNew(envir()), fIFramesOnly, fVSHPeriod);*/
}

RTPSink* MPEG1or2VideoScreenMediaSubsession
::createNewRTPSink(Groupsock* rtpGroupsock,
                   unsigned char /*rtpPayloadTypeIfDynamic*/,
                   FramedSource* /*inputSource*/) {
    return MPEG1or2VideoRTPSink::createNew(envir(), rtpGroupsock);
}
