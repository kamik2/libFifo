//
// Created by marcs on 11.05.2024.
//

#ifndef LIBFIFO_FIFO_H
#define LIBFIFO_FIFO_H

#include <stdint.h>
#include <stdbool.h>


#define VERSION 0x0100          // 0x0100 == V1.00

typedef struct
{
    uint32_t head;
    uint32_t tail;
    uint32_t mask;
    uint8_t *buffer;
}libFifoBuffer_t;

/**
 * initialise a fifo instance
 * @param fifo user created instance of libFifoBuffer_t
 * @param fifoDataBuffer uint8_t, user created data buffer,
 * @param size uint32_t, buffer size. must be power of 2 and > 1
 * @return false: size check failed, true, size check succeeded and fifo is initialized
 */
bool fifoInit(libFifoBuffer_t *fifo, uint8_t *fifoDataBuffer, uint32_t size);

/**
 * erase the fifo. resets head + tail, overwrites buffer with "0x00"
 * @param fifo fifo instance
 * @return always true, designed to return a "finished" flag
 */
bool fifoErase(libFifoBuffer_t *fifo);

/**
 * write a byte to the fifo
 * @param fifo fifo instance
 * @param data uint8_t, byte to be written
 * @return true: writing succeeded, false: fifo is full
 */
bool fifoWrite(libFifoBuffer_t *fifo, uint8_t data);

/**
 * read a byte from buffer
 * @param fifo fifo instace
 * @param target pointer to buffer target
 * @return true: reading succeeded, false: fio is empty
 */
bool fifoReadToBuffer(libFifoBuffer_t *fifo, uint8_t *target);

/**
 * read a byte and return it
 * @param fifo fifo instance
 * @return uint8_t, read byte
 */
uint8_t fifoReadDirect(libFifoBuffer_t *fifo);

/**
 * read the next byte without "flushing" it
 * @param fifo
 * @return uint8_t, read byte
 */
uint8_t fifoPeak(libFifoBuffer_t *fifo);




#endif //LIBFIFO_FIFO_H
