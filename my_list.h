#ifndef _LINUX_MYLIST_H
#define _LINUX_MYLIST_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct list_head {
	struct list_head *next, *prev;
};

struct LicenseItem {
	char m_Feature[20];
	char m_Version[20];
	int  m_iNumLicenses;
	void *m_pJob;
	int  m_iDaysRemaining;
};

struct stu{
	int num;
	char name[20];
	char key[40];
	struct LicenseItem list_L_Item;
	struct list_head list;
};

extern struct stu *list_node;
extern struct list_head *pos,*n;
extern struct stu *pnode;
extern struct stu *head; 
//////////////////////////////////////////////////////////////
extern  void init_list();

extern  void add_list(int num,char *s,struct LicenseItem *License);

extern  void del_list(char *s);

extern  struct LicenseItem *select_list(char *key);

extern  void search_list();

extern  void free_list();

#endif
