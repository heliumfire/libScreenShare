/*
 *		libScreenShare
 *		
 *              ScreenShare.cpp
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

#include "ScreenShare.hpp"

/*
 *		ScreenShare()
 *
 * 		Constructor to the class. Initializes the class :)
 */

ScreenShare::ScreenShare () {
#ifdef ACCESS_CONTROL
    authDB=NULL;
#endif

}

void *startSource(struct sessionContainer* mes)
{
    //printf("The message is %d",message);
    TaskScheduler* ourScheduler;
    ourScheduler = mes->schd;
    strSrc* src;
    src = new strSrc(mes->schd,mes->mes->vs,"/dev/graphics/fb0");
    src->startEncoding();
    //printf("Triggering the event\n");
    
    //while(1)
    //ourScheduler->triggerEvent(mes->mes->vs->eventTriggerId, mes->mes->vs);
    //fflush(stdout);
}

/*
 *      startServer()
 *
 *      This function starts the server there are basically following steps that are taken in
 *      order to do so. 
 *      ->  Create a TaskScheduler                              [LIVE555]
 *      ->  Create an RTSPServer                                [LIVE555]
 *      ->  Create a MPEG1or2 subsession                        [LIBSCREENSHARE]
 *      ->  Create a ServerMediaSession                         [LIVE555]
 *      ->  Add our MPEG1or2 subsession to ServerMediaSession   [LIVE555]
 *      ->  Add our ServerMediaSession to RTSPServer            [LIVE555]
 *      ->  Create a thread to start our encoding source        [LIBSCREENSHARE]
 *
 *      This is a blocking call and doesn't return. If you want to run as a library you would 
 *      probably want to run this in a seperate thread.
 *
 */


bool ScreenShare::startServer () {
    pthread_mutex_init (&mux, NULL);
    reuseFirstSource = True;
    iFramesOnly = False;
    long thread;
    TaskScheduler* scheduler = BasicTaskScheduler::createNew ();
    env = BasicUsageEnvironment::createNew (*scheduler);
    rtspServer = RTSPServer::createNew (*env, 8554, authDB);
    if (rtspServer == NULL) {
        *env << "Failed to create RTSP server: " << env->getResultMsg() << "\n";
#ifdef EXECUTABLE
        exit(1);
#else
        return false;
#endif
    }
    MPEG1or2VideoScreenMediaSubsession* sub = MPEG1or2VideoScreenMediaSubsession
    ::createNew(*env, reuseFirstSource, iFramesOnly);
    if(sub == NULL)
#ifdef EXECUTABLE
        exit(1);
#else
        return false;
#endif
    ServerMediaSession* sms = ServerMediaSession::createNew(*env, streamName, streamName, descriptionString);
    if(sub == NULL)
#ifdef EXECUTABLE
    exit(1);
#else
    return false;
#endif
    sms->addSubsession(sub);
    rtspServer->addServerMediaSession(sms);
    struct sessionContainer info;
    //info = (sessionContainer*)malloc(sizeof(struct sessionContainer));
    info.schd = scheduler;
    info.mes = sub;
    //void* pass;
    //pass = &info;
    if(pthread_create(&thread,NULL,startSource,(void*)&info))
#ifdef EXECUTABLE
    exit(1);
#else
    return false;
#endif
    env->taskScheduler ().doEventLoop ();
    pthread_exit (NULL);
}




#ifdef ACCESS_CONTROL
ScreenShare::setAuthentication (char* userName, char* password){
    authDB = new UserAuthenticationDatabase;
    if(authDB==NULL) return false;
    authDB->addUserRecord (userName, password);
    return true;
}
#endif