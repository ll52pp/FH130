#ifndef __INCLUDE_LIST_H__
#define __INCLUDE_LIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <semLib.h> 

typedef struct list_node
{
    struct list_node *next;
} LIST_NODE;

typedef struct list_str
{
   LIST_NODE * listHead;
   LIST_NODE * listTail;

   int count;
   
   SEM_ID  semList;
   
} LIST_STR;

typedef int (*list_loopfunc)(LIST_NODE *ptr,  UINT32 opaque);

void addNodeToListHead( void * pNode, void **listHead, void **listTail );
void addNodeToListTail( void * pNode, void **listHead, void **listTail );
void * removeNodeFromListHead( void **listHead, void **listTail );
void addListToListTail(void *listHead, void *listTail, void **DestlistHead, void **DestlistTail);
void addListToListHead(void *listHead, void *listTail, void **DestlistHead, void **DestlistTail);
void listInit(LIST_STR * list, int bProtect);
void listExit(LIST_STR * list);
int listIsListEmpty(LIST_STR * list);
void listEmptyList(LIST_STR * list);
void listAddNodeToListHead( void * pNode, LIST_STR * list );
void listAddNodeToListTail( void * pNode, LIST_STR * list );
void * listGetFirstNodeFromList(LIST_STR * list);
void * listGetLastNodeFromList(LIST_STR * list);
void * listRemoveNodeFromListHead(LIST_STR * list);
void listAddListToListHead(LIST_STR * listDest,  LIST_STR * listSrc);
void listAddListToListTail(LIST_STR * listDest,  LIST_STR * listSrc);
int listFuncForeach(LIST_STR * list, list_loopfunc func, UINT32 opaque, int abort_on_failure);

#ifdef __cplusplus
}
#endif

#endif /* __INCLUDE_LIST_H__ */