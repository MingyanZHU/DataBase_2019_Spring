//
// Created by zmy on 19-5-3.
//
#include "random_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "extmem.h"

const unsigned int end_blk_next_addr = 0;
const unsigned int s_start_addr = 10000;
const unsigned int r_start_addr = 20000;
const unsigned int linear_search_answer_addr = 30000;
const size_t bufSize = 520;
const size_t blkSize = 64;
const unsigned int tuples_per_block = 7;
const unsigned int tuples_size = 8;
const unsigned int int_size = 4;

// load Relation R to Disk without any index.
int loadRelationRToDisk(Buffer *buffer, unsigned char *blk);

// load Relation S to Disk without any index.
int loadRelationSToDisk(Buffer *buffer, unsigned char *blk);

// linear Search on Relation
int linearSearch(Buffer *buffer, unsigned int relation_addr);

// output data
int outputDataFromDisk(Buffer *buffer, unsigned int addr);

int main() {
    Buffer buffer;
    unsigned char *blk;

    if (!initBuffer(bufSize, blkSize, &buffer)) {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }

    blk = getNewBlockInBuffer(&buffer);
    // load Relation S to Disk
    if (loadRelationSToDisk(&buffer, blk) != 0) {
        perror("Writing Relation S to Disk Failed!\n");
        return -1;
    }

    // load Relation R to Disk
    if (loadRelationRToDisk(&buffer, blk) != 0) {
        perror("Writing Relation R to Disk Failed!\n");
        return -1;
    }

//    freeBlockInBuffer(blk, &buffer);
// TODO 此处不能去掉注释 可能是对于申请的用于读的block是不能free的

    if (linearSearch(&buffer, r_start_addr) != 0) {
        perror("Linear Search Failed\n");
        return -1;
    }

    if (outputDataFromDisk(&buffer, linear_search_answer_addr) != 0) {
        perror("Output Data From Disk Filed\n");
        return -1;
    }
    return 0;
}

int loadRelationSToDisk(Buffer *buffer, unsigned char *blk) {
    S *s = randomGenerateRelationS();
    unsigned int s_using = 0;   // record relation S has used space size
    for (int i = 0; i < NUMBER_OF_S; i += tuples_per_block) {
        unsigned char *temp = blk;
        for (int j = 0; j < tuples_per_block; j++) {
            memcpy(temp, (unsigned char *) &(s[i + j].c), int_size);
            memcpy(temp + int_size, (unsigned char *) &(s[i + j].d), int_size);
            temp += tuples_size;
        }
        // record next blk size
        unsigned int next_blk_addr;
        if (i + tuples_per_block >= NUMBER_OF_S)
            next_blk_addr = 0;
        else
            next_blk_addr = s_start_addr + s_using + blkSize;
        memcpy(temp, (unsigned char *) &next_blk_addr, int_size);

        if (writeBlockToDisk(blk, s_start_addr + s_using, buffer) != 0) {
            perror("Writing Block Failed!\n");
            return -1;
        }
        s_using += blkSize;
    }
    return 0;
}

int loadRelationRToDisk(Buffer *buffer, unsigned char *blk) {
    R *r = randomGenerateRelationR();
    unsigned int r_using = 0;   // record relation R has used space size
    for (int i = 0; i < NUMBER_OF_R; i += tuples_per_block) {
        unsigned char *temp = blk;
        for (int j = 0; j < tuples_per_block; j++) {
            memcpy(temp, (unsigned char *) &(r[i + j].a), int_size);
            memcpy(temp + int_size, (unsigned char *) &(r[i + j].b), int_size);
            temp += tuples_size;
        }
        // record next blk size
        unsigned int next_blk_addr;
        if (i + tuples_per_block >= NUMBER_OF_R)
            next_blk_addr = 0;
        else
            next_blk_addr = r_start_addr + r_using + blkSize;
        memcpy(temp, (unsigned char *) &next_blk_addr, int_size);
        if (writeBlockToDisk(blk, r_start_addr + r_using, buffer) != 0) {
            perror("Writing Block Failed!\n");
            return -1;
        }
        r_using += blkSize;
    }
    return 0;
}

int linearSearch(Buffer *buffer, unsigned int relation_addr) {
    unsigned char *readBuffer;
    if ((readBuffer = readBlockFromDisk(relation_addr, buffer)) == NULL) {
        perror("Reading Block Failed!\n");
        return -1;
    }
    int searchValue = relation_addr == r_start_addr ? 40 : 60;
    unsigned char *writeBuffer = getNewBlockInBuffer(buffer);
    unsigned int writeBuffer_using = 0;
    unsigned int next_write_blk_addr = linear_search_answer_addr;
    while (1) {
        unsigned char *tempRead = readBuffer;
        for (int i = 0; i < tuples_per_block; i++) {
            int x, y;
            memcpy(&x, (int *) tempRead, int_size);
            memcpy(&y, (int *) (tempRead + int_size), int_size);
            if (x == searchValue) {
                memcpy(writeBuffer, (unsigned char *) &x, int_size);
                memcpy(writeBuffer + int_size, (unsigned char *) &y, int_size);
                writeBuffer_using += tuples_size;
                if (writeBuffer_using + tuples_size >= blkSize) {
                    int temp_next_blk_addr = next_write_blk_addr + blkSize;
                    memcpy(writeBuffer, (unsigned char *) &temp_next_blk_addr, int_size);
                    if (writeBlockToDisk(writeBuffer, next_write_blk_addr, buffer) != 0) {
                        freeBlockInBuffer(writeBuffer, buffer);
                        return -1;
                    }
                    next_write_blk_addr = temp_next_blk_addr;
                }
            }
            tempRead += tuples_size;
        }

        unsigned int next_read_blk_addr;
        memcpy(&next_read_blk_addr, (unsigned int *) tempRead, int_size);

        if (next_read_blk_addr == 0)
            break;

        freeBlockInBuffer(readBuffer, buffer);

        if ((readBuffer = readBlockFromDisk(next_read_blk_addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            freeBlockInBuffer(writeBuffer, buffer);
            return -1;
        }
    }
    memcpy(writeBuffer + blkSize - tuples_size, (unsigned char *) &end_blk_next_addr, int_size);
    if (writeBlockToDisk(writeBuffer, next_write_blk_addr, buffer) != 0) {
        freeBlockInBuffer(writeBuffer, buffer);
        return -1;
    }
    freeBlockInBuffer(writeBuffer, buffer);
    return 0;
}

int outputDataFromDisk(Buffer *buffer, unsigned int addr) {
    unsigned char *blk;
    if ((blk = readBlockFromDisk(addr, buffer)) == NULL) {
        perror("Reading Block Failed!\n");
        return -1;
    }

    while (1) {
        unsigned char *temp = blk;
        for (int i = 0; i < tuples_per_block; i++) {
            int c, d;
            memcpy(&c, (int *) temp, int_size);
            memcpy(&d, (int *) (temp + int_size), int_size);
            printf("%d %d\n", c, d);
            temp += tuples_size;
        }
        unsigned int next_blk_addr;
        memcpy(&next_blk_addr, (unsigned int *) temp, int_size);
        printf("%d\n", next_blk_addr);

        // next blk addr is 0 which means there is no next blk.
        if (next_blk_addr == 0)
            break;

        freeBlockInBuffer(blk, buffer);

        if ((blk = readBlockFromDisk(next_blk_addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
    }
    return 0;
}
