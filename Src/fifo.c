//
// Created by marcs on 11.05.2024.
//

#include "fifo.h"
#include <string.h>

#define BIT_SIZE_INT32    32

static bool fifoIsEmpty(libFifoBuffer_t *fifo)
{
    return(fifo->head == fifo->tail);
}

static bool fifoIsSizePowerOfTwo(uint32_t size)
{
    uint8_t numOfSetBits = 0;
    
    while(size)
    {
        numOfSetBits += size & 1;
        size = size >> 1;
    }
    
    if(numOfSetBits != 1)
    {
        return false;
    };
    return true;
}

bool fifoInit(libFifoBuffer_t *fifo, uint8_t *fifoDataBuffer, uint32_t size)
{
    if(!(fifoIsSizePowerOfTwo(size)) || (size < 2))
    {
        return false;
    }
    
    fifo->buffer = fifoDataBuffer;
    fifo->head = 0;
    fifo->tail = 0;
    fifo->mask = size - 1;
    
    return true;
}

bool fifoErase(libFifoBuffer_t *fifo)
{
    memset(&fifo->buffer, 0x00, fifo->mask + 1);
    fifo->head = 0;
    fifo->tail = 0;
    return true;
}

bool fifoWrite(libFifoBuffer_t *fifo, uint8_t data)
{
    uint32_t nextHeadPosition = (fifo->head + 1) & fifo->mask;
    
    if(nextHeadPosition == fifo->tail)
    {
        return false;
    }
    
    fifo->buffer[fifo->head] = data;
    fifo->head = nextHeadPosition;
    
    return true;
}

bool fifoReadToBuffer(libFifoBuffer_t *fifo, uint8_t *target)
{
    if(fifoIsEmpty(fifo))
    {
        return false;
    }
    
    *target = fifo->buffer[fifo->head];
    fifo->head = (fifo->head + 1) & fifo->mask;
    
    return true;
}

uint8_t fifoReadDirect(libFifoBuffer_t *fifo)
{
    uint8_t byte;
    
    if(fifoIsEmpty(fifo))
    {
        return false;
    }
    
    byte = fifo->buffer[fifo->head];
    fifo->head = (fifo->head + 1) & fifo->mask;
    
    return byte;
}

uint8_t fifoPeak(libFifoBuffer_t *fifo)
{
    if(fifoIsEmpty(fifo))
    {
        return 0x00;
    }
    
    return(fifo->buffer[fifo->head]);
}

