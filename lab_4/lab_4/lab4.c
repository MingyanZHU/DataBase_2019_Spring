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

// Fresh block in buffer, make them to 0.
void freshBlockInBuffer(Buffer *buffer, unsigned char *blk);

// Relation R External sorting, make sure all blocks in buffer is free.
int rExternalSorting(Buffer *buffer, int paramIndex);

int compareR_1(const void *a, const void *b) {
    return ((*(R *) a).a - (*(R *) b).a);
}


int main() {
    Buffer buffer;
    unsigned char *blk;

    if (!initBuffer(bufSize, blkSize, &buffer)) {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);

    blk = getNewBlockInBuffer(&buffer);
    // load Relation S to Disk
    if (loadRelationSToDisk(&buffer, blk) != 0) {
        perror("Writing Relation S to Disk Failed!\n");
        return -1;
    }
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);

    blk = getNewBlockInBuffer(&buffer);
    // load Relation R to Disk
    if (loadRelationRToDisk(&buffer, blk) != 0) {
        perror("Writing Relation R to Disk Failed!\n");
        return -1;
    }
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);

    outputDataFromDisk(&buffer, s_start_addr);
    printf("======================================\n");
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);

    if (linearSearch(&buffer, s_start_addr) != 0) {
        perror("Linear Search Failed\n");
        return -1;
    }
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);

    if (outputDataFromDisk(&buffer, linear_search_answer_addr) != 0) {
        perror("Output Data From Disk Filed\n");
        return -1;
    }
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);

    printf("======================================\n");
    outputDataFromDisk(&buffer, r_start_addr);
    rExternalSorting(&buffer, 1);
    printf("======================================\n");
    outputDataFromDisk(&buffer, r_start_addr);

//    freeBuffer(&buffer);
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
        blk = getNewBlockInBuffer(buffer);
        s_using += blkSize;
    }
    freeBlockInBuffer(blk, buffer);
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
        blk = getNewBlockInBuffer(buffer);
        r_using += blkSize;
    }
    freeBlockInBuffer(blk, buffer);
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
                memcpy(writeBuffer + writeBuffer_using, (unsigned char *) &x, int_size);
                memcpy(writeBuffer + writeBuffer_using + int_size, (unsigned char *) &y, int_size);
                writeBuffer_using += tuples_size;
                if (writeBuffer_using + tuples_size >= blkSize) {
                    int temp_next_blk_addr = next_write_blk_addr + blkSize;
                    memcpy(writeBuffer + writeBuffer_using, (unsigned char *) &temp_next_blk_addr, int_size);
                    if (writeBlockToDisk(writeBuffer, next_write_blk_addr, buffer) != 0) {
                        return -1;
                    }
                    next_write_blk_addr = temp_next_blk_addr;
                    freshBlockInBuffer(buffer, writeBuffer);
                    writeBuffer_using = 0;
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
            return -1;
        }
    }
    memcpy(writeBuffer + blkSize - tuples_size, (unsigned char *) &end_blk_next_addr, int_size);
    if (writeBlockToDisk(writeBuffer, next_write_blk_addr, buffer) != 0) {
        return -1;
    }
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
        if (next_blk_addr == 0) {
            freeBlockInBuffer(blk, buffer);
            break;
        }

        freeBlockInBuffer(blk, buffer);
        if ((blk = readBlockFromDisk(next_blk_addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
    }
    return 0;
}

void freshBlockInBuffer(Buffer *buffer, unsigned char *blk) {
    for (int i = 0; i < buffer->blkSize; i += int_size)
        memcpy(blk + i, (unsigned char *) &end_blk_next_addr, int_size);
}

int rExternalSorting(Buffer *buffer, int paramIndex) {
    if (paramIndex != 1 && paramIndex != 2) {
        perror("Param used to sorting must be 1 or 2.\n");
        return -1;
    }
    int blk_num = buffer->bufSize / buffer->blkSize;
    int countBlk = 0;
    unsigned int addr = r_start_addr;
    unsigned char *blks[blk_num];
    while (countBlk < blk_num) {
        blks[countBlk] = readBlockFromDisk(addr, buffer);
        memcpy(&addr, (int *) (blks[countBlk] + buffer->blkSize - tuples_size), int_size);
        countBlk++;
    }
    for (int i = 0; i < blk_num; i++) {
        for (int j = 0; j < tuples_per_block; j++) {
            unsigned char *ip_1 = blks[i] + j * tuples_size;
            unsigned char *ip_2 = blks[i] + j * tuples_size + int_size;
            // 以上loop 1
            int x;
            memcpy(&x, (int *) (ip_1 + (paramIndex - 1) * int_size), int_size);
            for (int ii = i; ii < blk_num; ii++) {
                int jj = ii == i ? j : 0;
                for (; jj < tuples_per_block; jj++) {
                    // loop 2
                    int y;
                    memcpy(&y, (int *) (blks[ii] + jj * tuples_size + (paramIndex - 1) * int_size), int_size);
                    if (x > y) {
                        ip_1 = blks[ii] + jj * tuples_size;
                        ip_2 = blks[ii] + jj * tuples_size + int_size;
                        x = y;
                    }
                }
            }
            if ((blks[i] + j * tuples_size) != ip_1) {
                int a, b;
                memcpy(&a, (int *) ip_1, int_size);
                memcpy(&b, (int *) ip_2, int_size);
                memcpy(ip_1, (unsigned char *) (blks[i] + j * tuples_size), int_size);
                memcpy(ip_2, (unsigned char *) (blks[i] + j * tuples_size + int_size), int_size);
                memcpy(blks[i] + j * tuples_size, (unsigned char *) &a, int_size);
                memcpy(blks[i] + j * tuples_size + int_size, (unsigned char *) &b, int_size);
            }
        }
    }

    addr = r_start_addr;
    for (int i = 0; i < blk_num; i++) {
        unsigned int next_addr;
        memcpy(&next_addr, (unsigned int *) (blks[i] + buffer->blkSize - tuples_size), int_size);
        if (writeBlockToDisk(blks[i], addr, buffer) != 0) {
            perror("Writing Block Failed!\n");
            return -1;
        }
        addr = next_addr;
    }
    return 0;
}
