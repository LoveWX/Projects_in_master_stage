
//---------------okapi32.h---------------------------------
//
// ok api32 header file for user
//
//---------------------------------------------------------

#ifndef __JOINHOPE__
#define __JOINHOPE__


//----contant defines----


//--defines of ok series image board identity
//Mono series
#define		OK_M10					1010
#define		OK_M10N					1010
#define		OK_M10M					1013
#define		OK_M10F					1011
#define		OK_M10L					1014
#define		OK_M10H					1012
#define		OK_M20					1020
#define		OK_M2KC					1021

#define		OK_M20H					1022
#define		OK_M30					1030
#define		OK_M40					1040
#define		OK_M50					1050
#define		OK_M60					1060
#define		OK_M70					1070
#define		OK_M80					1080
#define		OK_M80K					1081

//--new updated series
#define		OK_M10A					1212	//OK_M10M:1013
#define		OK_M10B					1213	//OK_M10L/N:1014
#define		OK_M10C					1214	//
#define		OK_M10D					1215
#define		OK_M10K					1218	//OK_M80K


#define		OK_M20A					1222	//OK_M20H:1022
#define		OK_M20B					1223	//110M
#define		OK_M20C					1224	//160M
#define		OK_M20D					1225	//2050M

#define		OK_M40A					1240	//OK_M40:1041
#define		OK_M40B					1243	//110M
#define		OK_M40C					1244	//160M
#define		OK_M40D					1245	//205M

#define		OK_M60A					1260	//OK_M60:1060
#define		OK_M60B					1263	//110M
#define		OK_M60C					1264	//160M
#define		OK_M60D					1265	//205M

#define		OK_M50A					1250
#define		OK_M50K					1258
#define		OK_M51K					1257

#define		OK_M30A					1230
#define		OK_M30K					1238
#define		OK_M31K					1237
#define		OK_M70A					1270


//Color series
#define		OK_C20					2020
#define		OK_C20C					2021
#define		OK_C30					2030
#define		OK_C32					2032
#define		OK_C30S					2031
#define		OK_C40					2040
#define		OK_C50					2050
#define		OK_C70					2070
#define		OK_C80					2080
#define		OK_C80M					2081
#define		OK_M90					1090

//RGB series
#define		OK_RGB10				3010
#define		OK_RGB20				3020
#define		OK_RGB30				3030

//Monitor Control series
#define		OK_MC10					4010
#define		OK_MC16					4016
#define		OK_MC20					4020
#define		OK_MC30					4030

//--new updated series
#define		OK_C20A					2220
#define		OK_C23A					2221
#define		OK_C20B					2223
#define		OK_C30A					2230
#define		OK_C31A					2231
#define		OK_C30B					2233
#define		OK_C40A					2240
#define		OK_C50A					2250
#define		OK_C60A					2260
#define		OK_C60B					2263
#define		OK_C80A					2280
#define		OK_C80K					2288

#define		OK_RGB10A				3210
#define		OK_RGB10B				3213

#define		OK_RGB20A				3220
#define		OK_RGB21A				3221
#define		OK_RGB20B				3223
#define		OK_RGB20C				3224

#define		OK_RGB30A				3230
#define		OK_RGB30B				3233
#define		OK_RGB30C				3234

#define		OK_MC10A				4210
#define		OK_MC12A				4212
#define		OK_MC16A				4216


//---pc/104+ series
#define		OK_PC10A				5210

//---usb series
#define		OK_USB20A				5220

//---cPCI series
#define		OK_CPC16A				5230



//---Ok sereis Camera
#define		OK_AM1310				201310

#define		OK_AC1210				211210
#define		OK_AC1310				211310


#define		OK_SC1310				311310




//--error code

#define		ERR_NOERROR				0	//no error 
#define		ERR_NOTFOUNDBOARD		1	//not found available ok board 

#define		ERR_NOTFOUNDVXDDRV		2	//not found ok vxd/ntsys driver
#define		ERR_NOTALLOCATEDBUF		3	//not pre-allocated buffer from host memory
#define		ERR_BUFFERNOTENOUGH		4	//available buffer not enough for requirment
#define		ERR_BEYONDFRAMEBUF		5	//capture iamge size beyond buffer

#define		ERR_NOTFOUNDDRIVER		6	//not found the driver responded the card
#define		ERR_NOTCORRECTDRIVER	7	//the needed driver not correct

#define		ERR_MEMORYNOTENOUGH		8	//host memory not enough for DLL
#define		ERR_FUNNOTSUPPORT		9	//the function is not supported
#define		ERR_OPERATEFAILED		10	//something wrong with this function call

#define		ERR_HANDLEAPIERROR		11	//the handle to okapi32 function wrong
#define		ERR_DRVINITWRONG		12	//something wrong with this card's driver on initializing

#define		ERR_RECTVALUEWRONG		13	//the rect's parameters set wrong
#define		ERR_FORMNOTSUPPORT		14	//the format set not supported by this board

#define		ERR_TARGETNOTSUPPORT	15	//the target not support by this function

#define		ERR_NOSPECIFIEDBOARD	16	//not found specified board correctly sloted


//--format defines
#define		FORM_RGB888				1	
#define		FORM_RGB565				2
#define		FORM_RGB555				3
#define		FORM_RGB8888			4
#define		FORM_RGB332				5	
#define		FORM_RGB8886			18	

#define		FORM_YUV422				6	
#define		FORM_YUV411				7	
#define		FORM_YUV16				8	
#define		FORM_YUV12				9	
#define		FORM_YUV9				10	
#define		FORM_YUV8				11	

#define		FORM_GRAY888			12
#define		FORM_GRAY8888			13
#define		FORM_GRAY8				14
#define		FORM_GRAY10				15
#define		FORM_GRAY12				16
#define		FORM_GRAY16				17



//--mask command
#define		MASK_DISABALE			0	//turn of mask
#define		MASK_POSITIVE			1	//0 win clients visible, 1 video visible
#define		MASK_NEGATIVE			2	//0 for video 1 for win client (graph)


//--tv system standard
#define		TV_PALSTANDARD			0	//PAL
#define		TV_NTSCSTANDARD			1	//NTSC
#define		TV_NONSTANDARD			2	//NON_STD
#define		TV_HDTVSTANDARD			3	//HDTV_STD
//#define		TV_SECAMSTANDARD		4	//SECAM

//--HDTV sub mode
#define		HDTV_480P				1  //480 Lines Progressive scan
#define		HDTV_720P				2  //720 Lines Progressive scan
#define		HDTV_1080I				3  //1080 Lines Interlaced scan
#define		HDTV_1080P				4  //1080 Lines Interlaced scan

#define		TV_PALMAXWIDTH			768
#define		TV_PALMAXHEIGHT			576

#define		TV_NTSCMAXWIDTH			640 //720
#define		TV_NTSCMAXHEIGHT		480


//-----defines lParam for get param
#define		GETCURRPARAM			-1 

//-----sub-function defines for wParam of SetVideoParam
		//wParam cab be one of the follow
#define		VIDEO_RESETALL			0 //reset all to sys default
#define		VIDEO_SOURCECHAN		1 
			// lParam=0,1.. Comp.Video; 0x100,101...to Y/C(S-Video), 0x200,0x201 to RGB Chan.Input
#define		VIDEO_BRIGHTNESS		2 //LOWORD is brightness, for RGB HIWORD is channel (0:red, 1:green, 2:blue)
#define		VIDEO_CONTRAST			3 //LOWORD is contrast, for RGB HIWORD is channel (0:red, 1:green, 2:blue)
#define		VIDEO_COLORHUE			4
#define		VIDEO_SATURATION		5
#define		VIDEO_RGBFORMAT			6	//when return low word  is code high word is bitcount
#define		VIDEO_TVSTANDARD		7	//Main Mode:LOWORD 0 PAL, 1 NTSC, 2 Non-stadard, HDTVSTANDARD,
										//Sub Mode: HIWORD 1 HDTV_480P, ...
#define		VIDEO_SIGNALTYPE		8	//LOWORD 0 non-interlaced, 1 interlaced
										//HIWORD 0 no slot in field header, 1 yes
#define		VIDEO_RECTSHIFT			9	//video rect shift,  makelong (x,y)
#define		VIDEO_SYNCSIGCHAN		10  //LOWORD 0:Red,1:Grn,2:Blue, 3:Sync,4 H.V.Sync; 
										//HIWORD is source 0,1,..for RGB input,  
										// 0x100,0x101,... for comp.video input 
										// (in this case LOWORD has no mean more)
#define		VIDEO_AUXMONCHANN		11 //monitor video source chann on aux monitor
#define		VIDEO_AVAILRECTSIZE		12	//makelong(horz,vert)
				//horz available pixels per scan line and
				//vert available lines per frame
#define		VIDEO_FREQSEG			13	// set horz video frequency range
										//0:Low(7.5~15MHz),  1:middle(15~30), 2:High(30~60)
#define		VIDEO_LINEPERIOD		14 //line period (in 0.5 us) generated by board
#define		VIDEO_FRAMELINES		15 //lines per frame  generated by board

#define		VIDEO_MISCCONTROL		16 //miscellaneous control bits
									//b0:-satur, b1:- contr for c20, c30
									//b2:agc, b3:gama, b4:b/w,

#define		VIDEO_ENABLEGRAPHS		17 //enable graph 
#define		VIDEO_GAINADJUST		18 //gain adjust 

#define		VIDEO_RECTSHIFTEX		19	//general video active rect shift,  makelong (x,y)
										//replace for VIDEO_RECTSHIFT
#define		VIDEO_PHASEADJUST		20 //phase adjust 

	
//-----sub-function defines for wParam of SetCaptureParam
		//wParam cab be one of the follow
#define		CAPTURE_RESETALL		0 //reset all to sys default
#define		CAPTURE_INTERVAL		1
#define		CAPTURE_CLIPMODE		2 //LOWORD: clip mode when video and dest rect not same size
									  //HIWORD: if captrure odd and even field crosslly
#define		CAPTURE_SCRRGBFORMAT	3 //when return, loword=code, hiword=bits 
#define		CAPTURE_BUFRGBFORMAT	4 
#define		CAPTURE_FRMRGBFORMAT	5
#define		CAPTURE_BUFBLOCKSIZE	6 //lParam=MAKELONG(width,height)
									  //if set it 0 (default), the rect set by user will be as block size 
#define		CAPTURE_HARDMIRROR		7   //bit0 x, bit1 y; 
#define		CAPTURE_VIASHARPEN		8	//sample via sharpen filter
#define		CAPTURE_VIAKFILTER		9  //sample via recursion filter
#define		CAPTURE_SAMPLEFIELD		10  //0 in field (non-interlaced), 1 in frame (interlaced), (0,1 are basic)
										//2 in field but keep expend row,3 in field but interlaced one frame
										//(2,4 can affect only sampllng field(frame) by field(frame) )
										//in 3 up-dn frame
#define		CAPTURE_HORZPIXELS		11	// set max horz pixel per scan line
#define		CAPTURE_VERTLINES		12	// set max vert lines per frame

#define		CAPTURE_ARITHMODE		13 //arithmatic mode
#define		CAPTURE_TO8BITMODE		14 //the mode of high (eg. 10 bits) converted to 8bit 
										//HIWORD(lParam)=0: linear scale, 
										//HIWORD(lParam)!=0:clip mode, LOWORD(lParam)=offset
#define		CAPTURE_SEQCAPWAIT		15 	// bit0 if waiting finished for functions of sequence capturing and playbacking
										//bit1 if waiting finished capture then call callback function 

#define		CAPTURE_MISCCONTROL		16 //miscellaneous control bits
										//bit0: 1: take one by one |okCapturByBuffer,okGetSeqCapture by interrupt control
										//bit1: 1: take last one 
									    //bit2: 1: one by one for usb20

#define		CAPTURE_TRIGCAPTURE		17 //set triggered capture, LOWORD cap no of fields, HIWORD delay fields after trigger
#define		CAPTURE_TURNCHANNELS	18 //turn channel when sequence capture



#define		SAMPLE_INFIELD			0 //in field (non-interlaced)
#define		SAMPLE_INFRAME			1 //in frame of interlaced fields
					//the above two (0,1) are basic
#define		SAMPLE_FIELDEXP			2 //in field but expend (keep expend row)
#define		SAMPLE_UPDNFRAME		3 //in frame of up-downed fields 
#define		SAMPLE_FIELDINTER		4 //in field but interlaced to one frame
#define		SAMPLE_INTOPFIELD		5 //

//-----defines lParam for CAPTURE_CLIPMODE
#define		RECT_SCALERECT			0 
#define		RECT_CLIPCENTER			1 
#define		RECT_FIXLEFTTOP			2 
		//in condition video rect great than screen rect:
		//if RECT_SCALERECT video rect will be scaled to match screen rect if it can. else
		//video rect will be adjusted to match screen rect
		//(1: center, take center video rect  2: left-top fixed, take same size rect)


//-----sub-function defines for lParam of GetSignalParam
#define		SIGNAL_VIDEOEXIST		1 //0 video  absent, 1 exist
#define		SIGNAL_VIDEOTYPE		2 //0 field, 1 interlaced
#define		SIGNAL_SCANLINES		3 //scan lines per frame
#define		SIGNAL_LINEFREQ			4 //line frequency
#define		SIGNAL_FIELDFREQ		5 //frame frequency
#define		SIGNAL_FRAMEFREQ		6 //frame frequency
#define		SIGNAL_EXTTRIGGER		7 //extern trigger status, 1 trigger
#define		SIGNAL_FIELDID			8 //Field ID 0 odd, 1 even
#define		SIGNAL_VIDEOCOLOR		9 //color(1) or B/W(0)
#define		SIGNAL_TRANSFERING		10 //1 transfering video data

//-----sub-function defines for lEvent of WaitSignalEvent
#define		EVENT_FIELDHEADER		1 //field header
#define		EVENT_FRAMEHEADER		2 //frame header
#define		EVENT_ODDFIELD			3 //odd field come
#define		EVENT_EVENFIELD			4 //even field come
#define		EVENT_EXTTRIGGER		5 //extern trigger come, 
									  //(HIWORD(lEvent) is pole)

//-----sub-function defines for lParam of PutSignalParam
#define		PUTSIGNAL_TRIGGER		1 //put trigger signal, 1 trigger
#define		PUTSIGNAL_VERTSYNC		2 //enbale vertic sync. output


//-----sub-function defines for lParam of okSetConvertParam
#define		CONVERT_RESETALL		0 //reset all to sys default
#define		CONVERT_FIELDEXTEND		1 //field extend				
#define		CONVERT_PALETTE			2 //set convert palette (just for 8 to 24 or 32)
					//lParam=0: restore system default, >0: new palette pointer 
#define		CONVERT_HORZEXTEND		3 //horzental extend (integer times)
#define		CONVERT_HORZSTRETCH		4 //horzental stretch (arbitrary number times)
#define		CONVERT_MIRROR			5 //x(=1) and y(=2) mirror (note:just to convert data with BUFFER)
#define		CONVERT_UPRIGHT			6 //up to righ(=1)(rotate right 90 D) or left (=2) (rotate left 90 D


//when wParam=CONVERT_FIELDEXTEND
//field extend mode
#define		FIELD_JUSTCOPY			0 //just copy row by row 
#define		FIELD_COPYEXTEND		1 //copy one row and expend one row (x2)
#define		FIELD_INTERLEAVE		2 //just copy odd(1.) rows (/2)
#define		FIELD_INTEREXTEND		3 //copy one odd row and expend one row 
#define		FIELD_COPYINTERPOL		4 //copy one odd row and interpolate one row
#define		FIELD_INTERINTERPOL		5 //copy odd row and interpolate even row

#define		FIELD_INTEREVEN			6 //just copy even(2.) rows (/2)
#define		FIELD_INTEREXTEVEN		7 //copy one even row and expend one row 
#define		FIELD_JUSTCOPYODD		8 //just copy odd rows to odd rows  
#define		FIELD_JUSTCOPYEVEN		9 //just copy even rows to even rows  
#define		FIELD_ODDEVENCROSS		10 //copy odd and even cross 

									//just for the case without bit converting



//-----defines for several target we can support 
typedef	LPARAM	TARGET;

#define		BUFFER		(TARGET)1	//Buffer(physical) allocated from host memory
#define		VIDEO		(TARGET)0	//Video source input to the board 
#define		SCREEN		(TARGET)-1	//Screen supported by VGA
#define		FRAME		(TARGET)-2	//Frame buffer on the board
#define		MONITOR		(TARGET)-3	//Monitor supported by (D/A) TV standard


#define		SEQFILE			0x5153	//SQ 
#define		BMPFILE			0x4d42	//BM
#define		JPGFILE			0x504A	//JP 

#define		BLKHEADER		0x4b42	//BK
#define		BMPHEADER		0x4d42	//BM
#define		BUFHEADER		0x4642	//BF

//-----defines messages for user 

#define	WM_CLOSEREPLAY			WM_USER+100
		//send this message when close replay dlg

#define	WM_BEGINSEQPROC			WM_USER+101
		//begin seq proc, wParam=hBaord
#define	WM_SEQPROGRESS			WM_USER+102
		//seq in progress, wParam=hBaord, lParam=No. to
#define	WM_ENDSEQPROC			WM_USER+103
		//end seq proc, wParam=hBaord

//-----------struct defines---------------

//--app user used struct



typedef struct _okdevtype { //added after 28/02/2005, to replace struct _boardtype
	long	iBoardTypeCode; //ok image device type code (e.g. 2030(capture card), 201100(camera))
	long	iBoardIdentCode; //ok image device identity code (e.g. 2130)
	long	iBoardRankCode; //ok image device model code 0,1,..
	char	szBoardName[116]; //ok image device name (eg."OK_M20H", "OK_AM1100"...)
} OKDEVTYPE, *LPOKDEVTYPE; //128 bytes 

typedef struct _boardtype {
	short	iBoardTypeCode; //ok board type code (e.g. 2030)
	char	szBoardName[18]; //board name (eg."OK_M20H")
	short	iBoardIdentCode; //ok board identity code (e.g. 2130)
	short	iBoardRankCode; //ok board model code 0,1,..
} BOARDTYPE, *LPBOARDTYPE; //24 bytes

//image file block size
typedef struct _blocksize {
	short	iWidth;		//width
	short	iHeight;	//height
	short	iBitCount; //pixel bytes iBitCount
	short	iFormType;	//rgb format type, need to fill when RGB565 or RGB 555
	long	lBlockStep; //block stride (step to next image header)
						//need to fill when treat multi block else set 0
}BLOCKSIZE;



//image block info
typedef struct _blockinfo {
	short	iType;	//=BK or SQ, BM
	//struct _blocksize;
	short	iWidth;		//width
	short	iHeight;	//height
	short	iBitCount; //pixel bytes iBitCount
	short	iFormType;	//rgb format type, need to fill when RGB565 or RGB 555
	short	lBlockStep; //block stride (step to next image header)
	short	iHiStep;// HIWORD of block stride
	short	lTotal;	//frame num
	short	iHiTotal;// HIWORD of total
	short	iInterval; //frame interval
	LPBYTE	lpBits;// image data pointer / file path name
	LPBYTE	lpExtra;// extra data (like as palette, mask) pointer
} BLOCKINFO, *LPBLOCKINFO;

//sequence file info
typedef struct { //file info for seq
	short	iType;	//=SQ or BM
	//struct _blocksize;
	short	iWidth;		//width
	short	iHeight;	//height
	short	iBitCount; //pixel bytes iBitCount
	short	iFormType;	//rgb format type, need to fill when RGB565 or RGB 555
	short	lBlockStep; //block stride (step to next image header)
	short	iHiStep;// HIWORD of block stride
	short	lTotal;	//frame num
	short	iHiTotal;// HIWORD of total
	short	iInterval; //frame interval
} SEQINFO;


//for replay
typedef struct { //file info for seq
	LPBITMAPINFOHEADER	lpbi; //bitmap info
	BYTE			*lpdib; //dib data
	HWND			hwndPlayBox; //1 replaying, 0 quit
	short			iCurrFrame; //current frame in buffer
	short			iReserved; //
} DIBINFO, *LPDIBINFO;


//---set text mode----
typedef struct _settextmode {
	DWORD	dwForeColor; // forecolor, see macro RGB in win
	DWORD	dwBackColor; // backcolor, see macro RGB in win
	DWORD	dwSetMode; // 0:FULLCOPY, 1: FULLXOR, ...
	WORD	wFrameNo; // place which frame of target
	WORD	wReserved; // not used
} SETTEXTMODE;

#define		FULLCOPY		0		//copy full text region into target
#define		FULLXOR			1		//xor full text region and target
#define		COPYFONT		2		//just copy fonts strokes to target
#define		XORFONT			3		//just xor fonts strokes and target


//---encode and decode-----------------------------

//---get image size for jpeg------
typedef struct _imagesize {
	DWORD	dwWidth;
	DWORD	dwHeight;
	DWORD	dwBitCount;
	DWORD	dwTotal;
}IMAGESIZE, *LPIMAGESIZE;

//--set jpeg params
typedef struct _jpegparam {
	DWORD		dwSize; // the size of this strcut, must be set
	LPSTR		lpstrName;	//must be NULL if not use
	DWORD		dwQuality; //
	DWORD		dwReserved1;
} JPEGPARAM, *LPJPEGPARAM;



//----------
struct _imagesize_info {
	long	lHeadSize;      //struct header size
	long	lHorzSize;		//width, (default=768 when it as input)
	long	lVertSize;		//height, (default=768 when it as input)
	long	lBitCount;      //bit count (default=24 when it as input)
	long	lTotalFrame;    //total frames 
	long	reserved0;      //reserved
};

//---used to set and get image info ------
typedef struct _jpg2k_header_info {
	struct _imagesize_info;

	long	lQuality;     //jpeg quality factor (default=75)£¬

	long	reserved1;    //reserved
	long	reserved2;    //reserved
	long	reserved3;    //reserved
	long	reserved4;    //reserved
} JPG2KHEADER;



//---used to set and get image info ------
typedef struct _mpg2_header_info {
	struct _imagesize_info;

	double	dbFrameRate;      //frame rate (default=25, and it is expected rate when it as input)
	double	dbBitRate;        //bits rate

	long	reserved1;        //reserved
	long	reserved2;        //reserved
	long	reserved3;        //reserved
	long	reserved4;        //reserved
} MPEG2HEADER;


//---used to set and get image info ------
typedef struct _mpg4_header_info  
{
	struct _imagesize_info;

	double	dbFrameRate;	//frame rate (default=25, and it is expected rate when it as input)
	double	dbBitRate;		//bits rate, (default=4000000, and it is recommended)
	long	lEncodeMode;    //Encode mode, (value range 0~1, 0: double channels, 1:fix code rate as dbBitRate preset.
							//default=0, when it as input) 
	long	lInterval;      //Interval between key frame, (range: 1--300, default =100)
	long	lBFrameNum;		//B frame mode, (value range:0~2,  default=0. It is compatible as divx5.0
							//=2, little coded data but more encoding times
	long	lQualityIdx;	//mpeg4 quality control index, (value range: 0~6, default=0)
							//It will be better quality if value greater, but it will need longer times

	long	reserved1;        //reserved
	long	reserved2;        //reserved
	long	reserved3;        //reserved
	long	reserved4;        //reserved
} MPEG4HEADER;


//---used to set and get image info ------
typedef struct _mjpg_header_info   
{
	struct _imagesize_info;

	long	lQuality;     //jpeg quality factor (default=75) 
	double	dbFrameRate;  //frame rate (default=25, and it is expected rate when it as input)

	long	reserved1;    //reserved
	long	reserved2;    //reserved
	long	reserved3;    //reserved
	long	reserved4;    //reserved
} MJPGHEADER;


//--get frame type decoded 
typedef struct _mpeg_frame_info    
{
	long	lHeadSize;       //struct size
	long	lFrameType;		//current frame type
	long	lSkip;  		//input
	long	reserved1;      //reserved
	long	reserved2;      //reserved
	long	reserved3;      //reserved
	long	reserved4;      //reserved
} MPEGFRAMEINFO;



//------ okapi32 functions list -----------

#ifdef __cplusplus
extern "C" {            /* Assume C declarations for C++ */
#endif /* __cplusplus */


//--1. basic routines--------------

//prolog and epilog
HANDLE	WINAPI okOpenBoard(long *iIndex); //okLockBoard
		//open a Ok series board in specified index(0 based), return 0 if not found any
		//if success, return a handle to control specified board
		//if set index=-1, mean takes default index no. (default is 0 
		//if user not specified by 'Ok Device Manager' in Control Pannel)
		//this index can be also a specified board type code
		//this function will change iIndex to the true used index, 
		//if index input is -1 or type code 

BOOL	WINAPI okCloseBoard(HANDLE hBoard); //okCloseBoard
		//Unlock and close Ok board specified handle

long	WINAPI okGetLastError();
		//Get last error msg

long	WINAPI okGetDriverVer(LPSTR lpString, int iSize);
		//get version of current ok cards driver
		//lpString return version char string (e.g "5.08"),  iSize is lpString' size


long	WINAPI okGetBufferSize(HANDLE hBoard, void **lpLinear, DWORD *dwSize);
		//get base address and size of pre-allocated buffer,
		//if success return the max. frame num in which can be store according to current set
		//else return false;
LPVOID  WINAPI okGetBufferAddr(HANDLE hBoard, long lNoFrame);
		//get base address of specified frame No. in BUFFER
		//if success return the linear base address 
		//else return false;

LPVOID  WINAPI okGetTargetInfo(HANDLE hBoard, TARGET tgt, long lNoFrame, short * wid, short * ht, long *stride);
		//get target info include base address, width, height and stride specified frame No. 
		//if success return the linear base address and other infos, else return false;

long	WINAPI okGetTypeCode(HANDLE hBoard, LPSTR lpBoardName);
		//return type code and name of specified handle 


//set rect and capture 
long	WINAPI okSetTargetRect(HANDLE hBoard, TARGET target, LPRECT lpTgtRect);
		//set target (VIDEO, SCREEN, BUFFER, FRAME)capture to or from
		//if Rect.right or .bottom) are -1 , they will be filled current value
		//special note for target=BUFFER:
		//if never set CAPTURE_BUFBLOCKSIZE, the block size(W,H) of buffer will be changed 
		//according to size of right x bottom of lpRect, else the size will not changed 
		//if success return max frames this target can support, else return <=0

BOOL	WINAPI okSetToWndRect(HANDLE hBoard, HWND hWnd);
		//set client rect of hwnd as screen rect


BOOL	WINAPI okCaptureSingle(HANDLE hBoard, TARGET Dest, LONG lStart);
		//capture video source to target which can be BUFFER, SCREEN, FRAME, MONITOR 
		//start(o based).if success return 1, if failed return 0, if not support target -1
		//when this function sent command to grabber, then return immediately not wait to finish.
		//this function same as okCaptureTo(hBoard, Dest, wParam, 1);

BOOL	WINAPI okCaptureActive(HANDLE hBoard, TARGET Dest, LONG lStart);
		//capture continuous active video to same position in target which can be BUFFER, SCREEN, FRAME, MONITOR 
		//start(o based).if success return 1, if failed return 0, if not support target -1
		//when this function sent continuous command to grabber, then return immediately
		//but note that some card like RGB30. when target is SCREEN, this function is a thread.
		//this function same as okCaptureTo(hBoard, Dest, wParam, 0);

BOOL	WINAPI okCaptureThread(HANDLE hBoard, TARGET Dest, LONG lStart, LPARAM lNoFrame);
		//capture sequencely video to target which can be BUFFER, SCREEN, FRAME, MONITOR 
		//start(o based). lParam>0: number of frame to capture to,
 		//if lParam > total frames in BUFER, it will loop in rewind mode(i%total)
		//if lParam=-N mean it loop in buffer of N frame infinitely until call okStopCapture, 
		//when -1 mean loop in all buffer.
		//return max num frame can be stored in the target if success,
		// return 0 if failed(eg. format not matched). -1 not support target
		//this call will create a thread to manage to capture sequencely then
		//return immediately not wait to finish. This thread will callback if need
		//this function same as okCaptureTo(hBoard, Dest, wParam, n);
		//but it is not same, when n=1 this function is also a thread and still support callback

BOOL	WINAPI okCaptureToScreen(HANDLE hBoard);
		//Start to capture to screen (video real-time display on screen) and return immediately
		//this is just a special routine of okCaptureTo(hBoard,SCREEN,0,0)

BOOL	WINAPI okCaptureTo(HANDLE hBoard, TARGET Dest, long start, LPARAM lParam);
		//capture video source to target which can be BUFFER, SCREEN, FRAME, MONITOR 
		//start(o based), lParam>0: number of frame to capture to, =0: cont. mode,
 		//if lParam > total frames in BUFER, it will loop in rewind mode(i%total)
		//if lParam=-1 mean it loop infinitely until call okStopCapture
		//return max num frame can be stored in the target if success,
		// return 0 if failed(eg. format not matched). -1 not support target
		//this call will return immediately not wait to finish.
		//This function is not recomended to use for new user 


BOOL	WINAPI okPlaybackFrom(HANDLE hBoard, TARGET src, long start, LPARAM lParam);
		//playback on monitor from target which can be BUFFER, FRAME
		//start(o based), lParam>0: number of frame to capture to, =0: cont. mode 
		//if lParam > total frames in BUFER, it will loop in rewind mode (i%total)
		//if lParam=-1 mean it loop infinitely until call okStopCapture
		//return max num frame be stored in the target if success, 
		//return 0 if wrong. -1 not support target
		//this call will return immediately not wait to finish.
		//

//get status and stop capture
long	WINAPI okGetCaptureStatus(HANDLE hBoard, BOOL bWait);
		//query capturing status, if bWait then wait to finish capturing, else return immediately.
		//return 0 if finished, if cont. mode capturing return target capture to
		//(which include SCREEN -1, FRAME -2, MONITOR -3)
		//if capturing to/from BUFFER or file, return the frame No.(1 based) being capturing 

BOOL	WINAPI okStopCapture(HANDLE hBoard);
		//Stop capturing to or playback from SCREEN, BUFFER or other targets 
		//return target just captured to or from. 
		//if capturing to/from BUFFER or file, return the frame No.(1 based) being capturing 

long	WINAPI okGetSeqCapture(HANDLE hBoard, long start, long count);
		//get current frame no. of sequence capturing to buffer
		//start: set buffer no. to use, effecting only count==0
		//count: count no. to catpure
		//return frame no finished


//capture by to /from 
BOOL	WINAPI okCaptureByBuffer(HANDLE hBoard, TARGET dest, long start, long num);
		//capture sequence images to dest by way of two frame buffers (in BUFFER), 
		//the frame size and format is taken as same as current config of BUFFER
		//if dest is file name which can be .seq or .bmp (will generate multi bmp files)
		//dest can be also a user memory pointer or a BLOCKINFO pointer (with user memory pointer)
		//retrun true immediately if success. num should be great than 0

BOOL	WINAPI okCaptureByBufferEx(HANDLE hBoard, long fileset, TARGET dest, long start, long num);
		// all are same as okCaptureByBuffer except for fileset which is quality when to jpg file

		
BOOL	WINAPI okPlaybackByBuffer(HANDLE hBoard, TARGET src, long start, long num);
		//playback sequence images on monitor from src by way of two frame buffers (in BUFFER)
		//the size and format of BUFFER will be changed to same as src
		//src can be a file name which may be .seq or .bmp (first orderd bmp files) 
		////src can be also a BLOCKINFO pointer (with infos of user memory pointer,size and format)
		//if src is just user memory pointer, this function will think its block size and format 
		//are same as current config of BUFFER (in this case can not support loop function).
		//retrun true immediately if success 
		//if num is great than the true frame number in src, it will loop back
		//if num=-1 mean it will loop infinitely until call okStopCapture

//set and get params
long	WINAPI okSetVideoParam(HANDLE hBoard, WORD wParam, long lParam);
		//----set video param sub-function defines
		//set video param and return previous param; 
		//if input lParam=-1, just return previous param 			
		//if not support return -1, if error return -2 

long	WINAPI okSetCaptureParam(HANDLE hBoard, WORD wParam, long lParam);
		//set capture param and return previous param; 
		//if input lParam=-1, just return previous param 			
		//if not support return -1, if error return -2 


//transfer and convert rect
long	WINAPI	okReadPixel(HANDLE hBoard, TARGET src, long start, short x, short y);
		//read value of one pixel specified (x,y) in frame start of src (SCREEN, BUFFER, FRAME...)
		//return is this pixel value, it may be with bits 8,16,24,or 32 depend on the src's format

long	WINAPI	okWritePixel(HANDLE hBoard, TARGET tgt, long start, short x, short y, long lValue);
		//write value into specified (x,y) in the frame start of tgt (SCREEN, BUFFER, FRAME...)
		//

long	WINAPI okSetConvertParam(HANDLE hBoard, WORD wParam, long lParam);
		//set convert param for for function okConvertRect 
		//if not support return -1, if error return -2 

long	WINAPI okReadRect(HANDLE hBoard, TARGET src, long start, LPBYTE lpBuf);
		//read data into lpBuf from rect(set previous) in frame start of dst (SCREEN, BUFFER, FRAME)
		//the data in lpBuf stored in way row by row
		//if src not supported return -1, if failed return 0, 
		//return -1 if not support, return 0 failed, 
		//if success return data length read in byte
		//if lpBuf=NULL, just return data length to read

long	WINAPI okWriteRect(HANDLE hBoard, TARGET dst, long start, LPBYTE lpBuf);
		//write data in lpBuf to rect(set previous) of dst (SCREEN, BUFFER, FRAME)
		//the data in lpBuf stored in way row by row
		//return -1 if not support, return 0 failed, 
		//if success return data length written in byte

long	WINAPI okReadRectEx(HANDLE hBoard, TARGET src, long start, LPBYTE lpBuf, LPARAM lParam);
		//read data into lpBuf from rect(set previous) in frame start of dst (SCREEN, BUFFER, FRAME)
		//the data in lpBuf stored in way row by row
		//if src not supported return -1, if failed return 0, 
		//return -1 if not support, return 0 failed, 
		//if success return data length read in byte
		//if lpBuf=NULL, just return data length to read
		//LOWORD(lParam£©is form code for bits of lpBuf (e.g.£ºFORM_GRAY8£©£¬if it is 0 mean: as same as src
        //HIWORD(LParam) is the mode of taking channels. mode=0 take all, =1 red, =2 green, =3 blue;

long	WINAPI okWriteRectEx(HANDLE hBoard, TARGET dst, long start, LPBYTE lpBuf, LPARAM lParam);
		//write data in lpBuf to rect(set previous) of dst (SCREEN, BUFFER, FRAME)
		//the data in lpBuf stored in way row by row
		//return -1 if not support, return 0 failed, 
		//if success return data length written in byte
		//LOWORD(lParam£©is form code for bits of lpBuf (e.g.£ºFORM_GRAY8£©£¬if it is 0 mean: as same as dst
        //HIWORD(LParam) is the mode of taking channels. mode=0 take all, =1 red, =2 green, =3 blue;

long	WINAPI okTransferRect(HANDLE hBoard, TARGET dest, long iFirst, TARGET src, long iStart, long lNum);
		//transfer source rect to dest rect (here target can be SCREEN, BUFFER, FRAME, also BLOCKINFO point to user memory) 
		//if total in dest or src less than lNum, it will rewind to begin then continue
		//this function transfer in format of src, that means it don't convert pixel bits if dst and src are not same 
		//if src or dst not supported return -1, if failed return 0, 
		//if success return data length of one block image in byte

long	WINAPI okConvertRect(HANDLE hBoard, TARGET dst, long first, TARGET src, long start, LPARAM lParam);
		//transfer source rect to dest rect (here target can be SCREEN, BUFFER, FRAME, also BLOCKINFO point to user memory) 
		//LOWORD(lParam)=lNum, total num, HIWORD(lParam)=mode, channels to convert
		//mode=0 take all, =1 red, =2 green, =3 blue;
		//if total in dest or src < lNum, it will rewind to begin then continue
		//this function convert to pixel foramt of dst if dst has not same bits format as src 
		//if src or dst not supported return -1, if failed return 0, 
		//if success return image size of one block in pixel

long	WINAPI okConvertRectEx(HANDLE hDstBoard, TARGET dst, long first, HANDLE hSrcBoard, TARGET src, long start, LPARAM no);
		//same as the above function okConvertRect except with src handle


//get and put signals	
long	WINAPI okGetSignalParam(HANDLE hBoard, WPARAM wParam);
		//Get specified param of video signal source
		//if not support return -1, if error return -2, else return param

long	WINAPI okWaitSignalEvent(HANDLE hBoard, WPARAM wParam, LPARAM lMilliSecond);
		//Wait specified signal come
		//lMilliSecond is time-out time in milliseconds for to wait
		//if lMilliSecond is zero, the function returns current state immediately
		//if lMilliSecond is INFINITE(-1) wait forever until event come
		//return -1 not support, 0 speicfied signal not come, 1 come

long	WINAPI okPutSignalParam(HANDLE hBoard, WPARAM wParam, LPARAM lParam);
		//put specified signal param  
		//if not support return -1, if error return -2, 


//treat callback functions
BOOL	WINAPI okSetSeqProcWnd(HANDLE hBoard, HWND hwndMain);
		//set proc hwnd for receive message about sequence capture

BOOL	WINAPI okSetSeqCallback(HANDLE hBoard, 
								BOOL CALLBACK BeginProc(HANDLE hBoard), 
								BOOL CALLBACK SeqProc(HANDLE hBoard, long No), 
								BOOL CALLBACK EndProc(HANDLE hBoard));
		//set callback function for multi-frame capturing function 
		//(which are okCaptureTo, okCaptureFrom,okCaptureToFile, okCaptureFromFile)
		//see follow 

BOOL	CALLBACK BeginProc(HANDLE hBoard); //user defined callback function
		//callback this function before to capture
BOOL	CALLBACK SeqProc(HANDLE hBoard, long No); //user defined callback function
		// callback this function after finish capturing one frame
		// No is the number(0 based) frame just finished or being playbacked. 
BOOL	CALLBACK EndProc(HANDLE hBoard); //user defined callback function
		// callback this function after end capturing


//save and load files
long	WINAPI okSaveImageFile(HANDLE hBoard, LPSTR szFileName, long first, TARGET target, long start, long num);
		//here target can be BUFFER, SCREEN, FRAME or user buffer pointor
		//1.if ext name=".bmp":
		//create new file and than save one frame in start position of target as bmp file 
		//
		//2.if ext name=".seq":
		//save no frame from (start) in target into (first) frame pos in seq(sequence) file in sequencely.
		//if the file already exist the function will not delete it, that mean old contents in the file will be kept.
		//So if you want create a new seq file with a existed file name you must delete before this call .
		//
	
long	WINAPI okLoadImageFile(HANDLE hBoard, LPSTR szFileName, long first, TARGET target, long start, long num);
		//here target can be BUFFER, SCREEN, FRAME or user buffer pointor
		//1.if ext name=".bmp":
		//load one frame into start position of target from bmp file 
		//
		//2.if ext name=".seq":
		//load no frame into (start) in target from (first) frame pos in seq(sequence) file in sequencely.

//load and save config files with all parameters
BOOL	WINAPI okSaveConfigFile(HANDLE hBoard, LPSTR szFileName);
		//save all current parameters set to specified config file (*.okf)

BOOL	WINAPI okLoadConfigFile(HANDLE hBoard, LPSTR szFileName);
		//load specified config file to set current all paramters




//--2. special routines supported by some cards--------------

//overlay mask:
long	WINAPI okEnableMask(HANDLE hBoard, BOOL bMask);
		//0: disable mask; 1: positive mask, 2: negative mask
		//positive: 0 for win clients visible, 1 video visible
		//negative: 0 for video visible,  1 for win client (graph) visible
		//if bMask=-1 actually not set just get status previous set
		//return last mask status,
 
long	WINAPI okSetMaskRect(HANDLE hBoard, LPRECT lpRect, LPBYTE lpMask);
		//Set mask rect(lpRect is relative to lpDstRect in SetScreenRect or
		//SetBufferRect, lpMask is mask code (in byte 0 or 1). one byte for one pixel
		//if lpMask==1, set all rect region in lpRect video visible
		//if lpMask==0, set all rect region in lpRect video unvisible
		//return base linear address of inner mask bit 

//set out LUT:
long	WINAPI okFillOutLUT(HANDLE hBoard,  LPBYTE bLUT, short start, short num);
		//fill specified playback out LUT. 
		//bLut stored values to fill, (r0,g0,b0, r1,g1,b1 ...)
		//start: offset pos in LUT(based 0), num: num items to fill

//set input LUT:
long	WINAPI okFillInputLUT(HANDLE hBoard,  LPBYTE bLUT, short start, short num);
		//fill specified input LUT. 
		//bLut stored values to fill, (r0,g0,b0, r1,g1,b1 ...)
		//start: offset pos in LUT(based 0), num: num items to fill

BOOL	WINAPI okCaptureSequence(HANDLE hBoard, LONG lStart, LPARAM lNoFrame);
		//capture sequence to BUFFER by way of Interrupt Service Routine 
		//Note: Only M10 series, M20H,M40, M60, M30, M70 and RGB20 support this way 
		//wParam=start(o based). lParam>0: number of frame to capture to,
 		//if lParam > total frames in BUFER, it will loop in rewind mode(i%total)
		//when -1 mean loop in all buffer. infinitely until call okStopCapture, 
		//return max num frame can be stored in the target in this way if success,
		// return 0 if failed(eg. format not matched). -1 not support target
		//this call will start a Interrupt Service Routine to manage to capture sequencely then
		//return immediately not wait to finish. This routine not support callback 

BOOL	WINAPI okPlaybackSequence(HANDLE hBoard, LONG lStart, LONG lNoFrame);
		//playback on monitor from BUFFER
		//start(0 based), lNoFrame>0: number of frame to capture to,  
		//if lParam > total frames in BUFER, it will loop in rewind mode (i%total)
		//if lParam=-1 mean it loop infinitely until call okStopCapture
		//return max num frame be stored in the target if success, 
		//return 0 if wrong. -1 not support 
		//this call will start a Interrupt Service Routine to manage to playback sequencely then
		//return immediately not wait to finish. This routine not support callback 
		//

//
long	WINAPI okSetDriverParam(long lWhich, long lParam); 
		//lWhich defined as the follow
#define		STATICVXD		1
#define		INSTNTDRV		2
#define		ALLOCBUFFER		3
#define		MEMBLOCKSIZE	4
#define		MEMBLOCKCOUNT	5
#define		UNREGISTER		6


//set pre-allocate buffer size in k byte
long	WINAPI okSetAllocBuffer(long lSize);
		//set the new size to preallocate in  k bytes, 
		//if new size is not same as current, 
		//then the functuion will restart the window system

BOOL	WINAPI okSetStaticVxD(long lMode); //just for win95/98
		//lMode=0: check if static vxd registered.
		//=1: create static vxd register
		//=2: delete static vxd register

BOOL	WINAPI okSetNTDriver(BOOL bCmd);	//just for winNT/2K
		//bCmd=0: check if nt driver installed.
		//=1: install nt driver
		//=2: remove nt driver

BOOL	WINAPI okUnRegister(DWORD dwCmd);
		//uninstall all registered and generated infos

long	WINAPI	okGetProgramInfo(int iItem, LPSTR lpString, int iSize);
		//get program info
#define	PROGRAM		1
#define	VERSION		2
#define	PREFIX		3
#define	COMPANY		4
#define	TELFAX		5
#define	WEBEMAIL	6

long	WINAPI okSetLangResource(long langcode); //1252 for English, 936 for Simple Chinese



//--3. multi cards, channels, memories --------------

//multi cards access:
long	WINAPI okGetImageDevice(OKDEVTYPE **lpOkDevInfo, LPARAM lParam);
		//Query all Ok series Image devices available in PCI bus, USB, ... return total number
		//lParam should be 0
short	WINAPI okGetSlotBoard(BOARDTYPE **lpOkInfo);
		//Query all Ok boards available in PCI bus, return total number
short	WINAPI okGetBoardIndex(char *szBoardName, short iNo);
		//Get index (start 0) of specified board name string (it can also be typcode string)
		// and order in same name (start 0), 
		//return -1 if no this specified ok board
long	WINAPI okGetBoardName(long lIndex, LPSTR szBoardName);
		//get the board code and name of the specified index 
		//return the type code if success else return 0 if no card

//multi cards capture
BOOL	WINAPI 	okMulCaptureTo(HANDLE *lphBaord,TARGET Dest, long start, LPARAM lParam);
		//control multi boards to capture to target simultaneously, lphBaord are pointer of hBoard of multi board  
		//other functions are same as okCaptureByBuffer
BOOL	WINAPI 	okMulCaptureByBuffer(HANDLE *lphBaord,TARGET tgt, long start, long num);
		//control multi boards to capture by buffer simultaneously, lphBaord are pointer of hBoard of multi board  
		//other functions are same as okCaptureByBuffer

//multi channels:
BOOL	WINAPI okLoadInitParam(HANDLE hBoard, short iChannNo);
		//load specified chann (and as current chann.)of initial params
BOOL	WINAPI okSaveInitParam(HANDLE hBoard, short iChannNo);
		//save current init param to specified chann (and as current chann.)

//get and lock buffer
long	WINAPI okGetAvailBuffer(void **lpLinear, DWORD *dwSize);
		//Get free meomery buffers pre-allocated . 
		//call it when user hope to access buffer directly or lock for some one board 
long	WINAPI okLockBuffer(HANDLE hBoard, DWORD dwSizeByte, void **lpBasLinear);
		//Lock speicfiled size meomery buffers, then other handle can not use them
		//return the size of locked buffer in fact
BOOL	WINAPI okUnlockAllBuffer(void);
		//Unlock all buffer for all handle


//Mem Block Buffer appended to BUFFER 
long	WINAPI okApplyMemBlock(DWORD dwBlockSize, DWORD dwBlockNo);
		//apply mem block used as buffer appended to BUFFER
		//return the number of blocks allocated actually

BOOL	WINAPI okFreeMemBlock();
		//release appended MemBlock by okApplyMemBlock

long	WINAPI okGetMemBlock(HANDLE hBoard, DWORD *dwEachSize,  DWORD *dwBlockNo);
		//get the number of MemBlock and size per block applied by okApplyMemBlock 
		//and return the number can be as buffer as to cureent set size of BUFFER

long	WINAPI okLockMemBlock(HANDLE hBoard, long lBlockNo);
		//lock number of MemBlock to specified handle

BOOL	WINAPI okUnlockMemBlock(void);
		//unlcok all locked MemBlock



//--4. apps utilities-----------------


//apps setup dialog 
BOOL	WINAPI okOpenSetParamDlg( HANDLE hBoard, HWND hParentWnd);
		//dialog to setup video param 
BOOL	WINAPI okOpenSeqCaptureDlg( HANDLE hBoard, HWND hParentWnd);
		//dialog to capture sequence image

LPDIBINFO WINAPI okOpenReplayDlg( HANDLE hBoard, HWND hWnd, TARGET src, long total);
		//open modeless dialog to replay sequence images(in BUFFER, USERBUF or seq file) on SCREEN or MONITOR

HWND	WINAPI okOpenReplayDlgEx( HANDLE hBoard, HWND hWnd, TARGET src, long total, LPBITMAPINFOHEADER lpbi, LPBYTE lpdib);
		//open modeless dialog to replay sequence images(in BUFFER, USERBUF or seq file) on SCREEN or MONITOR

//-------
BOOL	WINAPI okUnifyFields(HANDLE hBoard, TARGET target, long start);
		//unify odd and even two fields which have different intensive brightness 
		//

//text and graphics
BOOL	WINAPI okSetTextTo(HANDLE hBoard, TARGET target, LPRECT lpRect, LOGFONT *lfLogFont, SETTEXTMODE *textMode, LPSTR lpString, long lLength); 
		//set text into the image of specified target
		//target can be SCREEN, BUFFER, FRAME, also BLOCKINFO
		//lpRect: just use its (left,top) to points start posision
		//lfLogFont: windows font definition, see window's document
		//textMode: specify forecolor, backcolor and set mode
		//lpString, lLength: text string and it's length

long	WINAPI okDrawEllipsTo(HANDLE hBoard, TARGET target, long lStart, LPRECT lpRect, long iForeColor);
		//draw a ellips into specified target
		//target can be SCREEN, BUFFER, FRAME, also BLOCKINFO
		//lpRect: specify the rect region of expected ellips
		//iForeColor: draw value on to target
		//return the pixel count of ellips

HDC		WINAPI okCreateDCBitmap(HANDLE hBoard, TARGET target, HANDLE *hDCBitmap);
		//create a memory DC compatible with windows's GDI, draw graphic and text etc. with GDI functions
		//target can be SCREEN, BUFFER, FRAME, also BLOCKINFO
		//hDCBitmap: return a handle with which we can map the graphics on the memory DC
		//to our target.
		//return the memory DC with which you can use windows"s GDI functions

BOOL	WINAPI okMapDCBitmapTo(HANDLE hDCBitmap, long lStart);
		//map the graphics of memory DC created by okCreateDCBitmap into specified target
		//hDCBitmap: the handle created by okCreateDCBitmap

BOOL	WINAPI okFreeDCBitmap(HANDLE hDCBitmap);
		//free the allocated resource by okCreateDCBitmap
		//hDCBitmap: the handle created by okCreateDCBitmap

//-----

//-----sub-function defines for wParam of okBeginEncode and okBeginDecode
#define		CODE_JPEG		1
#define		CODE_MPEG2		2
#define		CODE_MJPG		3
#define		CODE_MPEG4		4
#define		CODE_JPG2K		5


//encode and decode
HANDLE	WINAPI okBeginEncode(HANDLE hBoard, DWORD dwCodeWay, LPARAM lpImageInfo);
		//start to encode images. wCodeWay is CODE_JPEG or other compress, 
		//lpImageInfo is address of  preset parameters like size to encode
		//return a handle of encoder if sucessful, else  return 0
long	WINAPI okEncodeImage(HANDLE hCoder, TARGET src, long start, LPBYTE lpData, long maxlen);
		//encode one frame image . src is source like BUFFER, SCREEN, FRAME and BLOCK.
		//lpData to store coded data,  maxlen is maximum length of lpCodedData
		//return the length coded data
long	WINAPI okEndEncode(HANDLE hCoder);
		//end encode and release resources of encoder

HANDLE	WINAPI okBeginDecode(HANDLE hBoard, DWORD dwCodeWay, LPBYTE lpData, LPARAM lpImageInfo);
		//start to decode images. wCodeWay is CODE_JPEG or other compress, 
		//lpData is current start pos of coded data, 
		//lpImageInfo will return image info like size, no return when it is NULL
		//return a handle of decoder if sucessful, else  return 0
long	WINAPI okDecodeImage(HANDLE hCoder, LPBYTE lpData, long *length, TARGET target, long start);
		//decode coded data to image. 
		//lpData is pointer with coded data 
		//length is input length of coded data, it also output length of real used data 
		//target is aim to decode, like BUFFER, SCREEN, FRAME,BLOCK or memory pointer 
		//start is pos of specified target
		//return TRUE if one image finished, else return 0
long	WINAPI okEndDecode(HANDLE hCoder);
		//end decoder and release resources of decoder


//protect
long	WINAPI okReadProtCode(HANDLE hBoard, short iIndex);

long	WINAPI okWriteProtCode(HANDLE hBoard, short iIndex, long code);

//


//--5. audio section routines--------------

//-----defines wParam in okSetAudioParam
#define		AUDIO_RESETALL			0 //reset all to sys default
#define		AUDIO_SAMPLEFRQ			1 //Sample rate, in samples per second
#define		AUDIO_SAMPLEBITS		2 //Bits per sample 
#define		AUDIO_INVOLUME			3 //Audio input gain control
#define		AUDIO_CALLINTERVAL		4 //callback after interval times


//prolog and epilog
HANDLE	WINAPI okOpenAudio(HANDLE hBoard, LPARAM lParam);
		//open audio device owned by the video capture board 
		//hBoard is handle of image board, lParam reserved argument must ne set to 0
		//return handle of the audio device

BOOL	WINAPI okCloseAudio(HANDLE hAudio);
		//close audio device

//capture and stop
long	WINAPI okCaptureAudio(HANDLE hAudio, TARGET target, FARPROC lpfnUserProc, LPARAM lParam);
		//start to capture audio data, target can be BUFFER(audio data buffer) or file name
		//lpfnUserProc is callback function pointer, it must be NULL if not using callback 
		// lParam reserved argument must be set to 0
		//return the maximum times in miliseconds the inner audio data memory can be stored for

BOOL	CALLBACK WriteAudioProc(HANDLE hAudio, LPBYTE lpAudBuf, long length);
		//this callback function must written as the above protype by user 
		//call this function when there are enough audio data (the length in byte)
		//call this function when capture ended with argument length=0;

BOOL	WINAPI okStopCaptureAudio(HANDLE hAudio);
		//stop capturing audio data
		//return total length of read out by okReadAudioData 

//set and get audio
long	WINAPI okSetAudioParam(HANDLE hAudio, WORD wParam, LPARAM lParam);
		//set the parameters to sample audio,  wParam see above defines
		//return the new set value if success
		//if not support return -1, if error return -2 
		//if input lParam=-1, just return previous param 			

long	WINAPI okReadAudioData(HANDLE hAudio, LPBYTE lpAudioBuf, long lReadSize);
		//read audio captured from inner data buffer
		//lpAudioBuf is your memory address to store
		//lReadSize is data length (in byte) you expect to read
		//return the data length (in byte) truelly read 


//--6. stream section routines--------------

#define		NONE			0 //

//-----defines wParam in okSetStreamParam

#define		STREAM_RESETALL			0 //reset all to sys default
#define		STREAM_RESOLUTION		1 //Sample resolution, 0=D1,1=2/3D1,2=1/2D1,3=SIF
#define		STREAM_BITRATEMODE		2 //Bit Rate mode 0: VBR(Variable BR), 1: CBR(Constant)
#define		STREAM_MAXBITRATE		3 //Max Bit Rate, it is BR for CBR, it is max BR for VBR
#define		STREAM_CALLINTERVAL		4 //callback after interval times

//prolog and epilog
HANDLE	WINAPI okOpenStream(HANDLE hBoard, LPARAM lParam);
		//open stream device owned by the video capture board 
		//hBoard is handle of image board, lParam reserved argument must ne set to 0
		//return handle of the stream device

BOOL	WINAPI okCloseStream(HANDLE hStream);
		//close audio device

//capture and stop
long	WINAPI okCaptureStream(HANDLE hStream, TARGET target, FARPROC lpfnUserProc, long lMiliSeconds);
		//start to capture stream data, target can be NONE(0)/BUFFER(stream buffer), or file name
		//lpfnUserProc is callback function pointer, it must be NULL if not using callback 
		//lMiliSeconds=0: forever capturing until stop by okStopCaptureStream; 
		// non 0: specified periods to capture in mili-second
		//success if return non 0 

BOOL	CALLBACK WriteStreamProc(HANDLE hStream, LPBYTE lpStreamBuf, long length);
		//this callback function must written as the above protype by user 
		//call this function when there are enough stream data (the length in byte)
		//call this function when capture ended with argument length=0;

BOOL	WINAPI okStopCaptureStream(HANDLE hStream, DWORD dwPause);
		//stop or pause/re-encode capturing stream data
		//dwPause=0: stop, dwPause=1: pause, dwPause:=2: re-encode
		//return total length of read out by okReadStreamData 

//set and get stream
long	WINAPI okSetStreamParam(HANDLE hStream, WORD wParam, LPARAM lParam);
		//set the parameters to sample stream,  wParam see above defines
		//return the new set value if success
		//if not support return -1, if error return -2 
		//if input lParam=-1, just return previous param 			

long	WINAPI okReadStreamData(HANDLE hStream, LPBYTE lpStreamBuf, long lReadSize);
		//read stream captured from inner data buffer
		//lpStreamBuf is your memory address to store
		//lReadSize is data length (in byte) you expect to read
		//return the data length (in byte) truelly read 



//--7. ports io utilities--------------
// for Non-PCI IO cards on WinNT/Win2000 
// you must call this function before using follow port io functions 
BOOL	WINAPI okSetPortBase(WORD wPortBase, short iPortCount);
		//preset ports to use by setting port base address and port count 
		//to use some ports (default port=0x300, count=4) must preset by calling this one  
		//and these ports can be used correctly only after system restarted
		
		//this function only used for OK PCI GPIO20
short	WINAPI okGetGPIOPort(short index, WORD *wPortBase);
		//get port base and count of ok PCI GPIO20 
		//index is the nomber (0 based) of gpio cards,  
		//wPortBase: port base,  return port count if success else return 0

BOOL	WINAPI okOutputByte(WORD wPort, BYTE data);
		//output a byte at specified port 

BOOL	WINAPI okOutputShort(WORD wPort, short data);
		//output a word at specified port 

BOOL	WINAPI okOutputLong(WORD wPort, long data);
		//output a dword at specified port 

//----------- input data at port
BYTE	WINAPI okInputByte(WORD wPort);
		//input a byte at specified port 

short	WINAPI okInputShort(WORD wPort);
		//input a word at specified port 

long	WINAPI okInputLong(WORD wPort);
		//input a dword at specified port 

#define okGetDriverVer(a, b) okGetProgramInfo(2, a, b)

DWORD	WINAPI okGetAddrForVB(void *);
		//return array address for VB

//-----------get time elapse
DWORD	WINAPI okGetTickCount(void);
		//same as GetTickCount but exactly than it on Win2k

void	WINAPI okSleep(DWORD dwMill);
		//same as Sleep but exactly than it on Win2k


#ifdef __cplusplus
}
#endif    /* __cplusplus */


#endif

//-------------------end-------------------------------------------------------------------

