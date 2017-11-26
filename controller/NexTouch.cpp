/*
Library is Patched by yangweixian@cybergal.com
Date : 2017.10
*/

#include "NexTouch.h"


NexTouch::NexTouch(uint8_t pid, uint8_t cid, const char *name)
    :NexObject(pid, cid, name)
{
    this->__cb_push = NULL;
    this->__cb_pop = NULL;
    this->__cbpop_ptr = NULL;
    this->__cbpush_ptr = NULL;
}

void NexTouch::attachPush(NexTouchEventCb push, void *ptr)
{
    this->__cb_push = push;
    this->__cbpush_ptr = ptr;
}

void NexTouch::detachPush(void)
{
    this->__cb_push = NULL;
    this->__cbpush_ptr = NULL;
}

void NexTouch::attachPop(NexTouchEventCb pop, void *ptr)
{
    this->__cb_pop = pop;
    this->__cbpop_ptr = ptr;
}

void NexTouch::detachPop(void)
{
    this->__cb_pop = NULL;    
    this->__cbpop_ptr = NULL;
}

void NexTouch::push(void)
{
    if (__cb_push)
    {
        __cb_push(__cbpush_ptr);
    }
}

void NexTouch::pop(void)
{
    if (__cb_pop)
    {
        __cb_pop(__cbpop_ptr);
    }
}

void NexTouch::iterate(NexTouch **list, uint8_t pid, uint8_t cid, int32_t event)
{
    NexTouch *e = NULL;
    uint16_t i = 0;

    if (NULL == list)
    {
        return;
    }
    
    for(i = 0; (e = list[i]) != NULL; i++)
    {
        if (e->getObjPid() == pid && e->getObjCid() == cid)
        {
            e->printObjInfo();
            if (NEX_EVENT_PUSH == event)
            {
				e->push();
            }
            else if (NEX_EVENT_POP == event)
            {
				e->pop();
            }
            
            break;
        }
    }
}

