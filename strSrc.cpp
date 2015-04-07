#include "strSrc.hh"
extern "C" {
#include <linux/fb.h>
#include <asm-generic/fcntl.h>
#include <fcntl.h>
#include <sys/mman.h>
}

#define U8 uint8_t
extern pthread_mutex_t mux;
extern bool lock;

/*
 *      strSrc (TaskScheduler* schd, VSource* vs, char* fbDev)
 *      
 *      This function takes in instances of a taskscheduler, a Video source and fbdev address
 *
 *
 */


strSrc::strSrc(TaskScheduler* schd, VSource* vs, char* fbDev){
    fbfd = open (fbDev, O_RDONLY);
    if(fbfd==NULL){
        exit(1);   
    }
    ioctl(fbfd,FBIOGET_VSCREENINFO,&vscreeninfo);
    ioctl(fbfd,FBIOGET_FSCREENINFO,&fscreeninfo);
    fbp = (uint8_t *)mmap(0, fscreeninfo.smem_len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fbfd, 0);
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory\n");
        exit(1);
    }
    avcodec_register_all();
    /* find the mpeg1 video encoder */
    codec = avcodec_find_encoder(AV_CODEC_ID_MPEG1VIDEO);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }
    //pthread_mutex_init(&_mutex, 0);
    c = avcodec_alloc_context3(codec);
    picture = av_frame_alloc();
    iput = av_frame_alloc();
    
    /* put sample parameters */
    c->bit_rate = 400000;
    /* resolution must be a multiple of two */
    c->width = vscreeninfo.xres;
    c->height = vscreeninfo.yres;
    /* frames per second */
    c->time_base= (AVRational){1,25};
    c->gop_size = 10; /* emit one intra frame every ten frames */
    c->max_b_frames=1;
    c->global_quality = 1;
    c->pix_fmt = AV_PIX_FMT_YUV420P;
    
    /* open it */
    if (avcodec_open2(c, codec, NULL) < 0) {
        fprintf(stderr, "could not open codec\n");
        exit(1);
    }
    
    ret = av_image_alloc(picture->data, picture->linesize, c->width, c->height,
                         c->pix_fmt, 32);
    if (ret < 0) {
        fprintf(stderr, "could not alloc raw picture buffer\n");
        exit(1);
    }
    picture->format = c->pix_fmt;
    picture->width  = c->width;
    picture->height = c->height;
    //Init the links
    sink = vs;
    //VSource::instance = vs;
    tsc = schd;
    fflush(stdout);
}

void strSrc::startEncoding(){
    //sink->frameAccess=1;
    EncodeFrame();
    sink = VSource::instance;
    while(1){
        //printf("Encoding \n");
        fflush(stdout);
        //while(lock){printf("Blocked access \n");}
        if(lock==1) continue;
        //lock = 1;
        pthread_mutex_lock(&mux);
        EncodeFrame();
        //printf("Packet: %d : %d + %d\n",pkt.data,pkt.data,pkt.size);
        VSource::frameDataStartAddress = pkt.data;
        VSource::frameSize = pkt.size;
        lock = 1;
        pthread_mutex_unlock(&mux);
        tsc->triggerEvent(sink->eventTriggerId,sink);
    }
}

void strSrc::EncodeFrame(){
    //open the fb
    
    
    av_init_packet(&pkt);
    pkt.data = NULL;    // packet data will be allocated by the encoder
    pkt.size = 0;
    //static int j = 0;
    //printf("%d\n",j);
    //i=j;
    //fflush(stdout);
    if(vscreeninfo.bits_per_pixel==16){
        //const uint8_t* const pixel[fscreeninfo.smem_len];
        //uint16_t* pixel;//= &fbp;
        //int i,j;
        //pixel = (uint16_t*)fbp;
        //iput->data[0] = fbp;
        uint8_t* ipdata[1];
        ipdata[0] = (uint8_t*)fbp;
        int linesize;
        linesize = vscreeninfo.xres*2;
        //printf("Good until here!!\n");
        //memcpy(fbp,pixel,fscreeninfo.smem_len);
        //printf("Before %d %d %d\n",picture->linesize[0],picture->linesize[1],picture->linesize[2]);
        //picture->linesize[0] = vscreeninfo.xres;
        //picture->linesize[1] = vscreeninfo.xres/2;
        //picture->linesize[1] = vscreeninfo.xres/2;
        //printf("Linesize is at %x\n",picture->linesize);
        //picture->data[0][0]=0x00;
        //picture->data[0][1]=0x00;
        //picture->data[0][2]=0x00;
        //picture->data[0][3]=0x00;
        //picture->data[0][4]=0x00;
        //picture->data[0][5]=0x00;
        //picture->data[0][6]=0x00;
        //picture->data[0][7]=0x00;
        //neon_rgb565_2_yuv420(fbp,picture->data[0],vscreeninfo.xres*2,vscreeninfo.yres,picture->data[1],picture->data[2]);
        //printf("Linesize is at after encoding %x\n",picture->linesize);
        SwsContext * ctx = sws_getContext(vscreeninfo.xres, vscreeninfo.yres,
                                          AV_PIX_FMT_RGB565, vscreeninfo.xres, vscreeninfo.yres,
                                          AV_PIX_FMT_YUV420P, SWS_BICUBIC, 0, 0, 0);
        //printf("Good until here!! %d %d\n",ctx,iput->data[0]);
        sws_scale(ctx,ipdata,&linesize,0,vscreeninfo.yres,picture->data,picture->linesize);
        //printf("This might be the issue \n");
        //printf("Encoding passed %d %d %d\n",picture->linesize[0],picture->linesize[1],picture->linesize[2]);
    }
    if(vscreeninfo.bits_per_pixel==24){
        uint8_t* ipdata[1];
        ipdata[0] = (uint8_t*)fbp;
        int linesize;
        linesize = vscreeninfo.xres*3;
        SwsContext * ctx = sws_getContext(vscreeninfo.xres, vscreeninfo.yres, AV_PIX_FMT_RGB24, vscreeninfo.xres, vscreeninfo.yres, AV_PIX_FMT_YUV420P, SWS_BICUBIC, 0, 0, 0);
    }
    if(vscreeninfo.bits_per_pixel==32){
        uint8_t* ipdata[1];
        ipdata[0] = (uint8_t*)fbp;
        int linesize;
        linesize = vscreeninfo.xres*4;
        SwsContext * ctx = sws_getContext(vscreeninfo.xres, vscreeninfo.yres, AV_PIX_FMT_RGB24, vscreeninfo.xres, vscreeninfo.yres, AV_PIX_FMT_ARGB , SWS_BICUBIC, 0, 0, 0);
    }

        /* encode the image */
    ret = avcodec_encode_video2(c, &pkt, picture, &got_output);
    if (ret < 0) {
        fprintf(stderr, "error encoding frame\n");
        exit(1);
    }
   // printf("Encoded Packet: %d : %d + %d\n",pkt.data,pkt.data,pkt.size);
    
}


