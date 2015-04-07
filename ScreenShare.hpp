/*
 *              libScreenShare
 *
 *              Author:         regnarts
 *              Owner:          Musumbii
 *              Email:          regnarts299792458@gmail.com
 *              Bugs:
 *              Phone:
 *
 *              Description:
 *
 *                      This is the definition file for ScreenShare class. For full description
 *                      please check the docs. For a quick look into what this can do and for compile
 *                      instructions please see README.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include "liveMedia.hh"
#include "BasicUsageEnvironment.hh"
#include "MPEG1or2VideoScreenMediaSubsession.hh"
#include "strSrc.hh"

#define DESCRIPTION "SCREENSHARE"
#define STREAM_NAME "ScreenShare"

struct sessionContainer{
    TaskScheduler *schd;
    MPEG1or2VideoScreenMediaSubsession* mes;
};

class ScreenShare{

	public:
				ScreenShare ();
			bool	setFrameBufferPath (char* fbPath); 			//Sets the fb device path, defaulted to /dev/graphics/fb
			#ifdef ACCESS_CONTROL
			bool	setAuthentication (char* userName, char* password);	//Sets the Authentication, Only if ACCESS_CONTROL is set
			#endif
			char*	getRTSPURL();						//Returns pointer to the URL that can be used to play the video
            bool startServer();

	private:
            UserAuthenticationDatabase* authDB = NULL;                  //Container for Auth DB
            char const* descriptionString = DESCRIPTION;
            char const* streamName = STREAM_NAME;
            RTSPServer* rtspServer = NULL;
            bool iFramesOnly;
            bool reuseFirstSource;
            BasicUsageEnvironment* env;
//          void startSource(struct sessionContainer* mes);


};
