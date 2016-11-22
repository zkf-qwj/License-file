#include <iostream>
using namespace std;

extern "C"
{
#include <stdio.h>
#include "my_list.h"
#include "asd.h"
}


int main()
{

	char  l_zLicenseAcquired = 1;
	int l_iLicRetryCount = 0;
	init_list();	
	init_flexible();

	for ( l_iLicRetryCount=0;
			l_iLicRetryCount < 5;
			++l_iLicRetryCount)
	{
		l_zLicenseAcquired = acquire(
				"arts-rtsp", 1, "1.0", 0,0
				);
		if (l_zLicenseAcquired)
			break;
		sleep(2); // retry after 2 seconds
		printf("****\n*****\n*****\n*****\n");
	}

	if (!l_zLicenseAcquired)
	{
		// qtss_printf("Could not acquire license of rtspserver");
		printf("Could not acquire license of rtspserver\n");
		//return qtssFatalErrorState;
		exit_flexible();
		return -1;
	}
	enableExpiryPoll("arts-rtsp", "1.0"); 
	while(1)
	{
		sleep(1);
		printf("wait...\n");
	}
	printf("Successed to acquire license of rtspserver\n");    
	return 0;
}
