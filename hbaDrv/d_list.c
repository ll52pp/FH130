#include <stdlib.h>
#include <stdio.h>
#include <logLib.h>
#include "fc_asm.h"
#include "d_list.h"
#include "hba.h"
#include "hba_els.h"
#include "endian.h"

/***************************************************
用于把缓冲区中保存的连续帧
展开到以单个帧保存的双向链表中
***************************************************/

/* 初始化链表 */
int InitRawFrameList(PRAW_FRAME_CTRL ctrl)
{
    int ret, idx, count, node_len;
    PLIST_ENTRY entry=NULL, prev_entry=NULL, first_entry=NULL;

    if(ctrl == NULL)
    {
        return 1;
    }
    
    ctrl->count = 0;
    ctrl->used_count = 0;
    ctrl->threshold_count = RAW_FRAME_THRESHOLD_COUNT;
    ctrl->read_entry = NULL;
    ctrl->write_entry = NULL;
    ctrl->lock = semBCreate(SEM_Q_FIFO, SEM_FULL);
    ret = 0;
    node_len = sizeof(RAW_FRAME_NODE);
    count = RAW_FRAME_NODE_COUNT;
    for (idx = 0; idx < count; ++idx)
    {
        entry = (PLIST_ENTRY)malloc(node_len);
        /*printf("entry=0x%08x\n", (int)entry);*/
        if (entry == NULL)
        {
            ret = 1;
            break;
        }
        memset(entry, 0, node_len);
        
        if (ctrl->count == 0)
        {
            /* 第一个节点 */
            first_entry = entry;
            prev_entry = entry;
            /*printf("f entry[%d f_link=0x%08x b_link=0x%08x]\n", idx, (int)entry->f_link, (int)entry->b_link);*/
        }
        else if (ctrl->count < count - 1)
        {
            /* 中间的节点 */
            entry->f_link = NULL;
            entry->b_link = prev_entry;
            prev_entry->f_link = entry;
            prev_entry = entry;
            /*printf("m entry[%d f_link=0x%08x b_link=0x%08x]\n", idx, (int)entry->f_link, (int)entry->b_link);*/
        }
        else
        {
            /* 最后一个节点 */
            entry->b_link = prev_entry;
            entry->f_link = first_entry;
            first_entry->b_link = entry;            
            prev_entry->f_link = entry;
            /*printf("e entry[%d f_link=0x%08x b_link=0x%08x]\n", idx, (int)entry->f_link, (int)entry->b_link);*/
        }
        ctrl->count++;
    }
    /* 设置读写节点的指向 从任意一个节点开始 */
    /*ctrl->read_entry = ctrl->write_entry = entry;*/
    ctrl->read_entry  = entry;
    ctrl->write_entry = entry;
/*
    {
        PLIST_ENTRY k_entry;

        idx = 0;
        k_entry = ctrl->read_entry;
        do {
            printf("entry[%02d]=%p\n", idx, k_entry);
            k_entry = k_entry->f_link;
            idx++;
        } while (k_entry != ctrl->read_entry);
    }
*/
    return ret;
}

/* 释放链表 */
void UnInitRawFrameList(PRAW_FRAME_CTRL ctrl)
{
    int idx;
    PLIST_ENTRY entry, cur_entry;

    idx = 0;
    /* lock */
    semTake(ctrl->lock, WAIT_FOREVER);
    cur_entry = ctrl->write_entry;
    do {
        if(cur_entry == NULL)
        {
            break;
        }

        entry = cur_entry;
        cur_entry = cur_entry->f_link;
        /*printf("[%02d]entry=0x%08x\n", idx++, (int)entry);*/
        free(entry);
    } while (cur_entry != ctrl->write_entry);
    ctrl->count = 0;
    ctrl->used_count = 0;
    /*ctrl->write_entry = ctrl->read_entry = NULL;*/
    ctrl->write_entry = NULL;
    ctrl->read_entry = NULL;
    semGive(ctrl->lock);
    semDelete(ctrl->lock);
}

/* 判断链表是否已满 */
int RawFrameListIsFull(PRAW_FRAME_CTRL ctrl)
{
    if ((ctrl->used_count + ctrl->threshold_count) > ctrl->count)
    {
        /*printf("raw frame list is full count=%d used_count=%d threshold_count=%d\n", 
            ctrl->count, ctrl->used_count, ctrl->threshold_count);*/
        taskDelay(100);
        return 1;
    }

    return 0;
}

/* 向链表写入一个节点 */
void WriteRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length, int port)
{
    PRAW_FRAME_NODE frame_node;
    
       frame_node = (PRAW_FRAME_NODE)ctrl->write_entry;
    frame_node->length = length;
    frame_node->port = port;
       memcpy(frame_node->data, buf, length);
    ctrl->used_count++;
    /*printf("ctrl->used_count=%d write raw data to %p\n", ctrl->used_count, ctrl->write_entry);*/
       ctrl->write_entry = ctrl->write_entry->f_link;
}

/* 根据key值从链表中读取一个节点 */
/* 2018-3-19: huilin, 这个函数以后准备删除，用ReadFirstRawFrameList代替*/
int ReadRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length, int *real_length, int *port)
{
    int ret, k0, k1, k2, k3, tk0, tk1, tk2, tk3, bfind;
    int *b;
    PLIST_ENTRY entry, cur_entry;
    PRAW_FRAME_NODE frame_node;

    b = (int *)buf;
    k0 = *b;
    b++;
    k1 = *b;
    b++;
    k2 = *b;
    b++;
    k3 = *b;
    
    /* lock */
    semTake(ctrl->lock, WAIT_FOREVER);
    /* debug */
    /*
    {
        int t_count;
        PLIST_ENTRY t_entry;
        t_entry = ctrl->read_entry;
        t_count = 0;
        while (t_entry != ctrl->write_entry)
        {
            t_count++;
            t_entry = t_entry->f_link;
        }
        printf("t_count=%d count=%d ", t_count, ctrl->count);
    }
    */
    if (ctrl->used_count > 0)
    {
        /*printf("[ReadRawFrameList]ctrl->used_count=%d\n", ctrl->used_count);*/
        bfind = 0;
         cur_entry = ctrl->read_entry;
         do {

            if(cur_entry == NULL)
            {
                bfind = 0;
                break;
            }

            
            entry = cur_entry;
            cur_entry = cur_entry->f_link;
            frame_node = (PRAW_FRAME_NODE)entry;
            /* 检查key */
            b = (int *)(frame_node->data + SOF_SIZE + FC_HEADER_SIZE);
            tk0 = *b;
            b++;
            tk1 = *b;
            b++;
            tk2 = *b;
            b++;
            tk3 = *b;
            if ((k0 == tk0) && (k1 == tk1) && (k2 == tk2) && (k3 == tk3))
            {
                /* 按照key找到了帧*/
                bfind = 1;
                break;
            }
        } while (cur_entry != ctrl->write_entry);
        
        if (bfind == 1)
        {
            /* 找到 */
            if (entry == ctrl->read_entry)
            {
                ctrl->read_entry = ctrl->read_entry->f_link;
            }
            *real_length = frame_node->length;
            *port = frame_node->port;
            memcpy(buf, frame_node->data, *real_length);
            frame_node->length = 0;

            /* 把节点从链表上摘下来 */
            entry->b_link->f_link = entry->f_link;
            entry->f_link->b_link = entry->b_link;
            /* 插入到write_entry的前面 */
            ctrl->write_entry->f_link->b_link = entry;
            entry->f_link = ctrl->write_entry->f_link;
            ctrl->write_entry->f_link = entry;
            entry->b_link = ctrl->write_entry;
            /*
                 ctrl->write_entry->b_link->f_link = entry;
                 entry->b_link = ctrl->write_entry->b_link;
                 ctrl->write_entry->b_link = entry;
                 entry->f_link = ctrl->write_entry;*/
            ctrl->used_count--;
            ret = 0;
        }
        else
        {
            /* 没有找到 */
            ret = 2;
        }
    }
    else 
    {
        ret = 1;
    }
    /* unlock */
    semGive(ctrl->lock);

    return ret;
}


/* 从链表中读取一个节点 */
int ReadFirstRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length, int *real_length, int *port)
{
    int ret;
    PLIST_ENTRY entry;
    PRAW_FRAME_NODE frame_node;

    /* lock */
    semTake(ctrl->lock, WAIT_FOREVER);

    if (ctrl->used_count > 0)
    {
        /*printf("[ReadRawFrameList]ctrl->used_count=%d\n", ctrl->used_count);*/
        if (ctrl->read_entry != NULL)
        {
            /* 从队列头取出第一个节点 */
            entry = ctrl->read_entry;            
            ctrl->read_entry = ctrl->read_entry->f_link;

            frame_node = (PRAW_FRAME_NODE)entry;
            *real_length = frame_node->length;
            *port = frame_node->port;
            memcpy(buf, frame_node->data, *real_length);
            frame_node->length = 0;

            /* 把节点从链表上摘下来 */
            entry->b_link->f_link = entry->f_link;
            entry->f_link->b_link = entry->b_link;
            /* 插入到write_entry的前面 */
            ctrl->write_entry->f_link->b_link = entry;
            entry->f_link = ctrl->write_entry->f_link;
            ctrl->write_entry->f_link = entry;
            entry->b_link = ctrl->write_entry;

            ctrl->used_count--;        

            semGive(ctrl->lock);
            return OK;
        }
    }

    semGive(ctrl->lock);
    return ERROR;
}    



/* 把连续保存的帧展开到单个帧链表 */
void ExpandToRawFrameList(PRAW_FRAME_CTRL ctrl, char *buf, int length)
{
#if 0
    int t_port, idx,length_arr[RAW_FRAME_NUMBER_MAX], port_arr[RAW_FRAME_NUMBER_MAX];
    char *t_buf;
    ELS_IO_DESC *desc;
    unsigned int count, t_len;

    /* 取得所有帧的长度 */
    count = 0;
    t_buf = buf + length;
    
    while (length)
    {
        desc = (ELS_IO_DESC *)(t_buf - 4);
        desc->value = (UINT32)HbaUlongByteSwap((ULONG)desc->value);

        t_len = desc->u.length;
        t_len *= 4;/*4字节为单位*/
        t_port = desc->u.port0;
        length_arr[count] = t_len;
        port_arr[count] = t_port;
        count++;
        t_buf -= ELS_LENGTH_DESC;
        length -= ELS_LENGTH_DESC; /* 长度占8字节 */
        /* FPGA放数据对齐到8字节，如果不是8字节整数倍，
        偏移要再移动4字节对齐 */
        if (t_len & 0x7)
        {
            t_buf -= 4;        
            length -= 4;
        }
        t_buf -= t_len;
        length -= t_len;
    }
    t_buf = buf;
    
    /*
    if (count > 1)
    {
        printf("@notice count=%d ctrl->used_count=%d\n", count, ctrl->used_count);
    }
    */
    
    /*printf("count=%d length=%d\n", count, length_arr[0]);*/
    for (idx = count - 1; idx >= 0; --idx)
    {
        t_len = length_arr[idx];
        t_port = port_arr[idx];
        WriteRawFrameList(ctrl, t_buf, t_len, t_port);
        /*printf("idx=%d ctrl->used_count=%d\n", idx, ctrl->used_count);*/
        if (t_len & 0x7)
        {
            t_len += 4;
        }
        t_len += ELS_LENGTH_DESC;
        t_buf += t_len;
    }    
#endif
}

