//#include <iostream>
//using namespace std;
//extern "C"
//{
#include <stdio.h>
#include "my_list.h"
#include "asd.h"
#include <pthread.h> 
//}
#define LOG_PATH "/var/log/arts/err_arts_catch.log"
void * thread_fun(void * arg)   
{  
	enableExpiryPoll("arts-rtsp", "1.0");
}  
int main(int argc,const char *argv[])
{
	int l_zLicenseAcquired = 1;
	int l_zIphoneLicenseAcquired = 1;
	pthread_t ntid;
	
	init_list();
	init_flexible();
	int l_iLicRetryCount = 0;
	for ( l_iLicRetryCount=0;
			l_iLicRetryCount < 5;
			++l_iLicRetryCount)
	{
		l_zLicenseAcquired = acquire(
				"arts-rtsp", 1, "1.0",0,0
				);
		if (l_zLicenseAcquired)
			break;
		sleep(2); // retry after 2 seconds
	}

	if (!l_zLicenseAcquired)
	{
		system("./catch.sh");
		printf("Could not acquire license of rtspserver");
		return -1;
	}
	enableExpiryPoll("arts-rtsp", "1.0");
/*	int err;  
	err = pthread_create(&ntid, NULL, thread_fun, NULL);  
	if (err != 0)   
	{  
		printf("%s\n", strerror(err));  
	}
	pthread_join(ntid,NULL);
	*/
	return 0;
}
