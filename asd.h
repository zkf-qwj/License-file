#ifndef _ASD_H_
#define _ASD_H_
//#include "my_list.h"
/*---------------define-----------------*/
#define LICPATH "@localhost:license.dat:."  
static const int LIC_EXPIRY_CHECK_INTERVAL = 60*60*1000;
/*-------------global var---------------*/
extern void *m_pFlexHandle ;
void init_flexible();
char acquire(const char *p_pcFeature,
		int p_iNumLicenses,
		const char *p_pcVersion,
		char p_zTerminateOnFail,
		char p_zSilent);
void exit_flexible();
void release(const char *p_pcFeature,const char *p_pcVersion);
void release_1(struct LicenseItem p_Feature,char p_zSilent);
char enableExpiryPoll(const char *p_pcFeature,const char *p_pcVersion);
void handleTimeout();
void run();
#endif
