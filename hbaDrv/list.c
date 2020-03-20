#include <stdlib.h>
#include <stdio.h>
#include <logLib.h>
#include "list.h"

void addNodeToListHead( void * pNode, void **listHead, void **listTail )
{
   LIST_NODE    *ptr;

   if ((pNode == NULL) || (listHead == NULL) || (listTail == NULL))
        {
            return;
        }
    
   ptr = (LIST_NODE *) pNode;

   /*If this is the first pointer in list...*/
   if ( *listHead == NULL )
   {      
      /*  *listHead = *listTail = ptr;*/
      *listHead = ptr;
      *listTail = ptr;

      ptr->next = NULL;
   }
   else
   {
      ptr->next = (LIST_NODE *) (*listHead);

      (*listHead) = ptr; 
   }

}




void addNodeToListTail( void * pNode, void **listHead, void **listTail )
{
    LIST_NODE    *ptr;
    LIST_NODE    *tempPtr;

    if ((pNode == NULL) || (listHead == NULL) || (listTail == NULL))
    {
        return;
    }
    ptr = (LIST_NODE *) pNode;

    /*If this is the first pointer in list...*/
    if ( *listTail == NULL )
    {
      
      /* *listHead = *listTail = ptr;*/
      *listHead = ptr;
      *listTail = ptr;

      ptr->next = NULL;
    }
    else
    {
         tempPtr = (LIST_NODE *) *listTail; 
         tempPtr->next = ptr;
         ptr->next = NULL;  

      (*listTail) = ptr;
    }
}


void * removeNodeFromListHead( void **listHead, void **listTail )
{
   LIST_NODE    *ptr;

   if ((listHead == NULL) || (listTail == NULL))
    {
        return NULL;
    }
   
   if ((*listHead == NULL) || (*listTail == NULL ))
   {
           return NULL;
   }
   ptr = (LIST_NODE *) (*listHead);
    
   /*If this is the first pointer in list...*/
   if ( *listHead == *listTail )
   {
      /* *listHead = *listTail = NULL;*/
      *listHead = NULL;
      *listTail = NULL;

      return ptr;
   }
   else
   {
      *listHead = ptr->next;
      ptr->next = NULL;
        
      return ptr;   
   }

   /* cannot run to here */
   return NULL; 
}



void addListToListTail(void *listHead, void *listTail, void **DestlistHead, void **DestlistTail)
{
   LIST_NODE    *ptr;

   if ((DestlistHead == NULL) || (DestlistTail == NULL) || (listHead == NULL) || (listTail == NULL))
      {
          return;
            }
   if ((listHead == NULL) || (listTail == NULL))
      {
          return;
            }

   /*If this is the first pointer in list...*/
   if ( *DestlistTail == NULL )
   {
         /* Destination list is empty, just copy the pointer */
      
      *DestlistHead = listHead;
      *DestlistTail = listTail;

   }
   else
   {
         ptr = (LIST_NODE *) *DestlistTail; 
      ptr ->next = listHead;

      *DestlistTail = listTail;  /* fixed by Huilin, 2014-6-17 */
   }
}


void addListToListHead(void *listHead, void *listTail, void **DestlistHead, void **DestlistTail)
{
    LIST_NODE    *ptr;

    if ((DestlistHead == NULL) || (DestlistTail == NULL) || (listHead == NULL) || (listTail == NULL))
    {
          return;
    }
    if ((listHead == NULL) || (listTail == NULL))
    {
        return;
    }

    /*If this is the first pointer in list...*/
    if ( *DestlistHead == NULL )
    {
        /* Destination list is empty, just copy the pointer */
      
        *DestlistHead = listHead;
        *DestlistTail = listTail;

    }
    else
    {
        ptr = (LIST_NODE *) listTail; 
        ptr ->next = (LIST_NODE *)*DestlistHead;

        *DestlistHead = listHead;  
    }
}


void listInit(LIST_STR * list, int bProtect)
{    
    list->listHead = NULL;
    list->listTail = NULL;
    list->count = 0;

    if (bProtect)
    {
        list->semList = semBCreate(SEM_Q_FIFO, SEM_FULL);
    }
    else
    {
        list->semList = NULL;
    }
}


void listExit(LIST_STR * list)
{    
    if (list->semList != NULL)
    {
        semDelete(list->semList);    
        list->semList = NULL;
    }
}


int listIsListEmpty(LIST_STR * list)
{    
    if (list->listHead == NULL)
    {
        return 1;
    }

    return 0;
}

void listEmptyList(LIST_STR * list)
{
    if (list->semList != NULL)
    {
        semTake(list->semList, WAIT_FOREVER);
    }
    list->listHead = NULL;
    list->listTail = NULL;
    list->count = 0;

    if (list->semList != NULL)
    {
        semGive(list->semList);    
    }
}



void listAddNodeToListHead( void * pNode, LIST_STR * list )
{
    if ((pNode == NULL) || (list == NULL))
    {
        return;
    }
    if (list->semList != NULL)
    {
        semTake(list->semList, WAIT_FOREVER);
    }
    addNodeToListHead(pNode, (void **)&list->listHead, (void **)&list->listTail);
    list->count ++;
    
    if (list->semList != NULL)
    {
        semGive(list->semList);    
    }
}

void listAddNodeToListTail( void * pNode, LIST_STR * list )
{
    if ((pNode == NULL) || (list == NULL))
    {
        return;
    }
    if (list->semList != NULL)
    {
        semTake(list->semList, WAIT_FOREVER);
    }
    addNodeToListTail(pNode, (void **)&list->listHead, (void **)&list->listTail);
    list->count ++;
    
    if (list->semList != NULL)
    {
        semGive(list->semList);    
    }
}


void * listGetFirstNodeFromList(LIST_STR * list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->listHead;
}


void * listGetLastNodeFromList(LIST_STR * list)
{
    if (list == NULL)
    {
        return NULL;
    }
    return list->listTail;
}


void * listRemoveNodeFromListHead(LIST_STR * list)
{
    void *ptr;
    
    if (list == NULL)
    {
        return NULL;
    }
    if (list->semList != NULL)
    {
        semTake(list->semList, WAIT_FOREVER);
    }
    ptr = removeNodeFromListHead((void **)&list->listHead, (void **)&list->listTail);
    if (ptr != NULL)
    {
        list->count --;
    }
    
    if (list->semList != NULL)
    {
        semGive(list->semList);    
    }
    return ptr;
}


void listAddListToListHead(LIST_STR * listDest,  LIST_STR * listSrc)
{
    if ((listDest == NULL) || (listSrc == NULL))
    {
        return;
    }
    if (listDest->semList != NULL)
    {
        semTake(listDest->semList, WAIT_FOREVER);
    }
    if (listSrc->semList != NULL)
    {
        semTake(listSrc->semList, WAIT_FOREVER);
    }
    addListToListHead((void *)listSrc->listHead, (void *)listSrc->listTail, (void **)&listDest->listHead, (void **)&listDest->listTail);
    listDest->count += listSrc->count;

    if (listSrc->semList != NULL)
    {
        semGive(listSrc->semList);    
    }
    if (listDest->semList != NULL)
    {
        semGive(listDest->semList);    
    }
} 



void listAddListToListTail(LIST_STR * listDest,  LIST_STR * listSrc)
{
    if ((listDest == NULL) || (listSrc == NULL))
    {
        return;
    }
    if (listDest->semList != NULL)
    {
        semTake(listDest->semList, WAIT_FOREVER);
    }
    if (listSrc->semList != NULL)
    {
        semTake(listSrc->semList, WAIT_FOREVER);
    }
    addListToListTail((void *)listSrc->listHead, (void *)listSrc->listTail, (void **)&listDest->listHead, (void **)&listDest->listTail);
    listDest->count += listSrc->count;
    
    if (listSrc->semList != NULL)
    {
        semGive(listSrc->semList);    
    }
    if (listDest->semList != NULL)
    {
        semGive(listDest->semList);    
    }
}


/* when used to count the number of list, func can be NULL */
/* return the count for loop */
int listFuncForeach(LIST_STR * list, list_loopfunc func, UINT32 opaque, int abort_on_failure)
{
    LIST_NODE * ptr;
    int rc = 0;
    int count = 0;

    if (list == NULL)
    {
        return 0;
    }
    if (list->semList != NULL)
    {
        if (semTake(list->semList, /* WAIT_FOREVER */ 100) != OK)
        {
            /*printf("List(%p) is locked. \n", list);*/
            return 0;
        }
    }

    ptr = list->listHead;
    while(ptr != NULL)
    {
        count ++;

        if (func)
        {
            rc = func(ptr, opaque);
            if ((abort_on_failure)  &&  (rc != 0))
            {
                break;
            }
        }

        ptr = ptr->next;
    }

    if (list->semList != NULL)
    {
        semGive(list->semList);    
    }
    return count;
}

