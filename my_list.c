#include "my_list.h"

struct stu *list_node ;
struct list_head *pos,*n;
struct stu *pnode;
struct stu *head; 
//-------------------------------------------------------------------
#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
	struct list_head name = LIST_HEAD_INIT(name)

static  void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}
//------------------------------------------------------------------
static inline void __list_add(struct list_head *new,
                   struct list_head *prev,
                    struct list_head *next)
{
      next->prev = new;
      new->next = next;
      new->prev = prev;
      prev->next = new;
}


/**
 * list_add_tail - add a new entry
 * @new: new entry to be added
 * @head: list head to add it before
 *
 * Insert a new entry before the specified head.
 * This is useful for implementing queues.
 */
 static void list_add_tail(struct list_head *new, struct list_head *head)
 {
      __list_add(new, head->prev, head);
 } 

//-------------------------------------------------------------------

#define prefetch(x) __builtin_prefetch(x)

/**
  * list_for_each    -   iterate over a list
  * @pos:    the &struct list_head to use as a loop cursor.
  * @head:   the head for your list.
  */
#define list_for_each(pos, head) \
     for (pos = (head)->next; prefetch(pos->next), pos != (head); \
             pos = pos->next)

/**
  * list_entry - get the struct for this entry
  * @ptr:    the &struct list_head pointer.
  * @type:   the type of the struct this is embedded in.
  * @member: the name of the list_struct within the struct.
  */
#define list_entry(ptr, type, member) \
       container_of(ptr, type, member)

#ifndef container_of
/**
 * container_of - cast a member of a structure out to the containing structure
 *     
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({                      \
         const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
          (type *)( (char *)__mptr - offsetof(type,member) );})
#endif

#undef offsetof
#ifdef __compiler_offsetof
#define offsetof(TYPE,MEMBER) __compiler_offsetof(TYPE,MEMBER)
#else
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

//-----------------------------------------------------------------------

/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:    the &struct list_head to use as a loop cursor.
 * @n:      another &struct list_head to use as temporary storage
 * @head:   the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)

 /*
  * Architectures might want to move the poison pointer offset
  * into some well-recognized area such as 0xdead000000000000,
  * that is also not mappable by user-space exploits:
  */
 #ifdef CONFIG_ILLEGAL_POINTER_VALUE
 # define POISON_POINTER_DELTA _AC(CONFIG_ILLEGAL_POINTER_VALUE, UL)
 #else
 # define POISON_POINTER_DELTA 0
 #endif
 
 /*
  * These are non-NULL pointers that will result in page faults
  * under normal circumstances, used to verify that nobody uses
  * non-initialized list entries.
  */ 
 #define LIST_POISON1  ((void *) 0x00100100 + POISON_POINTER_DELTA)
 #define LIST_POISON2  ((void *) 0x00200200 + POISON_POINTER_DELTA)

/*
 * Delete a list entry by making the prev/next entries
 * point to each other.
 *
 * This is only for internal list manipulation where we know
 * the prev/next entries already!
 */
static inline void __list_del(struct list_head * prev, struct list_head * next)
{
     next->prev = prev;
     prev->next = next;
}


static inline void list_del(struct list_head *entry)
{
     __list_del(entry->prev, entry->next);
     entry->next = LIST_POISON1;
     entry->prev = LIST_POISON2;
}
//-------------------------------------------------------------------------

/**
 * list_empty - tests whether a list is empty
 * @head: the list to test.
 */
static inline int list_empty(const struct list_head *head)
{
    return head->next == head;
}
//////////////////////////////////////////////////////////////
void init_list(){
	head = (struct stu *)malloc(sizeof(struct stu));
	if (head == NULL) {
		printf("file,%s line ,%d: malloc error!\n",__FILE__,__LINE__);
		exit(1);
	}
	INIT_LIST_HEAD(&head->list);
}
void add_list(int num,char *s,struct LicenseItem *License)
{
	list_node = (struct stu *)malloc(sizeof(struct stu));
	if (list_node == NULL) {
		printf("file,%s,line,%d:malloc error!\n",__FILE__,__LINE__);
		exit(1);
	}
	list_node->num = num;
	if(License != NULL){
	 strcpy(list_node->list_L_Item.m_Feature,License->m_Feature);
	 strcpy(list_node->list_L_Item.m_Version,License->m_Version);
	list_node-> list_L_Item.m_iNumLicenses = License->m_iNumLicenses;
	list_node-> list_L_Item.m_pJob = License->m_pJob;
 	list_node-> list_L_Item.m_iDaysRemaining = License->m_iDaysRemaining;
	}
	strcpy(list_node->key,s);
	list_add_tail(&list_node->list,&head->list);
}
void del_list(char *s)
{
	list_for_each_safe(pos,n,&head->list) {
		pnode = list_entry(pos,struct stu,list);
		if (!strcmp(pnode->name,s)) {
		list_del(pos);
		printf("num %d has removed from the list !\n",pnode->num);
		free(pnode);
		}
	} 
}
struct LicenseItem *select_list(char *key)
{
	if (list_empty(&head->list)) {
		return NULL;	
	}else {
		list_for_each(pos,&head->list) {
			pnode = list_entry(pos,struct stu,list);
			if (!strcmp(key,pnode->key))
				return &(pnode->list_L_Item);
		}
	}
	return NULL;
}
void search_list()
{
	if (list_empty(&head->list)) {
	//	printf("list is empty!\n");
	}else {
		list_for_each(pos,&head->list) {
			pnode = list_entry(pos,struct stu,list);
		//	printf("num:%d,name %s\n",pnode->num,pnode->name);
		}
	}
}
void free_list()
{
	list_for_each_safe(pos,n,&head->list) {
		list_del(pos);
		pnode = list_entry(pos,struct stu,list);
	//	printf("num %d has removed from the list !\n",pnode->num);
		free(pnode);
	} 
	free(head);
}
