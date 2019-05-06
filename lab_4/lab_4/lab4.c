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

const unsigned int sort_addr_bias = 30000;

const unsigned int ext_sort_s_answer_addr = 40000;
const unsigned int ext_sort_r_answer_addr = 50000;
const unsigned int projection_addr = 60000;
const unsigned int join_answer_addr = 70000;
const unsigned int b_plus_tree_root_addr = 80000;
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
int linearSearch(Buffer *buffer, unsigned int relation_addr, int paramIndex, int searchValue);

// output normal relation
int outputNormalRelationFromDisk(Buffer *buffer, unsigned int addr);

// Fresh block in buffer, make them to 0.
void freshBlockInBuffer(Buffer *buffer, unsigned char *blk);

// Relation External sorting, make sure all blocks in buffer is free.
int externalSorting(Buffer *buffer, unsigned int start_addr, int paramIndex);

// project the first value of relation
int projection(Buffer *buffer, unsigned int start_addr);

// output projection answer
int outputProjection(Buffer *buffer);

// binary search
int binarySearch(Buffer *buffer, unsigned int relation_addr, int paramIndex, int searchValue);

// nest loop join
int nestLoopJoin(Buffer *buffer);

// sort merge join
int sortMergeJoin(Buffer *buffer);

int addBPlusTree(Buffer *buffer, unsigned int relation_addr, int paramIndex);

int main() {
    Buffer buffer;
    unsigned char *blk;

    if (!initBuffer(bufSize, blkSize, &buffer)) {
        perror("Buffer Initialization Failed!\n");
        return -1;
    }
    printf("After Init Buffer:\n");
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);

    blk = getNewBlockInBuffer(&buffer);
    // load Relation S to Disk
    if (loadRelationSToDisk(&buffer, blk) != 0) {
        perror("Writing Relation S to Disk Failed!\n");
        return -1;
    }
    printf("After load relation S to Disk:\n");
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);

    blk = getNewBlockInBuffer(&buffer);
    // load Relation R to Disk
    if (loadRelationRToDisk(&buffer, blk) != 0) {
        perror("Writing Relation R to Disk Failed!\n");
        return -1;
    }
    printf("After load relation R to Disk:\n");
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);


//    externalSorting(&buffer, r_start_addr, 1);
//    printf("After external sorting:\n");
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//    outputNormalRelationFromDisk(&buffer, r_start_addr);
//    printf("======================================\n");
//    printf("After output data from disk:\n");
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//
//    int search_ans = binarySearch(&buffer, r_start_addr, 1, 40);
//    printf("After binary search in relation:\n");
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//    if (search_ans != 0) {
//        if (search_ans < 0) {
//            perror("Linear Search Failed\n");
//            return -1;
//        } else {
//            printf("Not found!\n");
//        }
//    } else {
//        if (outputNormalRelationFromDisk(&buffer, linear_search_answer_addr) != 0) {
//            perror("Output Data From Disk Filed\n");
//            return -1;
//        }
//        printf("After output linear search result to disk:\n");
//        printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//    }
//
//    printf("======================================\n");
//    externalSorting(&buffer, s_start_addr, 1);
//    outputNormalRelationFromDisk(&buffer, s_start_addr);
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
    printf("======================================\n");
    sortMergeJoin(&buffer);
    printf("After nest loop join:\n");
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);

    addBPlusTree(&buffer, r_start_addr, 1);
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//    printf("After output relation from disk:\n");
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//
//    externalSorting(&buffer, s_start_addr, 1);
//    printf("After external sorting:\n");
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//
//    outputNormalRelationFromDisk(&buffer, s_start_addr);
//    printf("After output relation from disk:\n");
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//
//    printf("======================================\n");
//    outputNormalRelationFromDisk(&buffer, r_start_addr + sort_addr_bias);
//    printf("After output relation from disk:\n");
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//
//    projection(&buffer, r_start_addr);
//    printf("======================================\n");
//    printf("After projection:");
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);
//
//    outputProjection(&buffer);
//    printf("======================================\n");
//    printf("After output projection answer:");
//    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer.numFreeBlk, buffer.numAllBlk, buffer.numIO);


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

int linearSearch(Buffer *buffer, unsigned int relation_addr, int paramIndex, int searchValue) {
    if (relation_addr != r_start_addr && relation_addr != s_start_addr) {
        perror("There are only two relations: R and S!\n");
        return -1;
    }

    if (paramIndex != 1 && paramIndex != 2) {
        perror("Param index of linear search is 1 or 2!\n");
        return -2;
    }

    if (relation_addr == r_start_addr) {
        if ((paramIndex == 1 && (searchValue > A_MAX || searchValue < A_MIN)) ||
            (paramIndex == 2 && (searchValue > B_MAX || searchValue < B_MIN))) {
            return 1;
        }
    } else {
        if ((paramIndex == 1 && (searchValue > C_MAX || searchValue < C_MIN)) ||
            (paramIndex == 2 && (searchValue > D_MAX || searchValue < D_MIN))) {
            return 1;
        }
    }

    unsigned char *readBuffer;
    if ((readBuffer = readBlockFromDisk(relation_addr, buffer)) == NULL) {
        perror("Reading Block Failed!\n");
        return -1;
    }
    int not_found = 1;
    unsigned char *writeBuffer = getNewBlockInBuffer(buffer);
    freshBlockInBuffer(buffer, writeBuffer);
    unsigned int writeBuffer_using = 0;
    unsigned int next_write_blk_addr = linear_search_answer_addr;
    while (1) {
        unsigned char *tempRead = readBuffer;
        for (int i = 0; i < tuples_per_block; i++) {
            int x, y;
            memcpy(&x, (int *) tempRead, int_size);
            memcpy(&y, (int *) (tempRead + int_size), int_size);
            if ((x == searchValue && paramIndex == 1) || (y == searchValue && paramIndex == 2)) {
                not_found = 0;
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
                    writeBuffer = getNewBlockInBuffer(buffer);
                    freshBlockInBuffer(buffer, writeBuffer);
                    writeBuffer_using = 0;
                }
            }
            tempRead += tuples_size;
        }

        unsigned int next_read_blk_addr;
        memcpy(&next_read_blk_addr, (unsigned int *) tempRead, int_size);

        if (next_read_blk_addr == 0) {
            freeBlockInBuffer(readBuffer, buffer);
            break;
        }

        freeBlockInBuffer(readBuffer, buffer);

        if ((readBuffer = readBlockFromDisk(next_read_blk_addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
    }

    if (writeBuffer_using == 0 && !not_found) {
        // 多申请一个块的输出缓冲 需要将多申请的块还回
        freeBlockInBuffer(writeBuffer, buffer);
        if ((writeBuffer = readBlockFromDisk(next_write_blk_addr - blkSize, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
        memcpy(writeBuffer + blkSize - tuples_size, (unsigned char *) &end_blk_next_addr, int_size);
        if (writeBlockToDisk(writeBuffer, next_write_blk_addr - blkSize, buffer) != 0)
            return -1;
    } else {
        memcpy(writeBuffer + blkSize - tuples_size, (unsigned char *) &end_blk_next_addr, int_size);
        if (writeBlockToDisk(writeBuffer, next_write_blk_addr, buffer) != 0)
            return -1;
    }
    return not_found;
}

int outputNormalRelationFromDisk(Buffer *buffer, unsigned int addr) {
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

int externalSorting(Buffer *buffer, unsigned int start_addr, int paramIndex) {
    if (paramIndex != 1 && paramIndex != 2) {
        perror("Param used to sorting must be 1 or 2.\n");
        return -1;
    }
    int blk_num = buffer->bufSize / buffer->blkSize;
    int countBlk;
    unsigned int addr = start_addr;
    unsigned char *blks[blk_num];
    int sort_times = 0;
    unsigned int ext_sort_addr[NUMBER_OF_R / (tuples_per_block * buffer->numAllBlk)];

    // 形成多个连续8块的有序段
    while (addr != 0) {
        countBlk = 0;
        ext_sort_addr[sort_times] = addr;
        while (countBlk < blk_num) {
            if ((blks[countBlk] = readBlockFromDisk(addr, buffer)) == NULL) {
                perror("Reading Block Failed!\n");
                return -1;
            }
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

        addr = ext_sort_addr[sort_times++];
        for (int i = 0; i < blk_num; i++) {
            unsigned int next_addr;
            memcpy(&next_addr, (unsigned int *) (blks[i] + buffer->blkSize - tuples_size), int_size);
            if (writeBlockToDisk(blks[i], addr, buffer) != 0) {
                perror("Writing Block Failed!\n");
                return -1;
            }
            addr = next_addr;
        }
    }

    unsigned char *writeBuffer = getNewBlockInBuffer(buffer);
    int write_buffer_using = 0;
    unsigned int write_blk_addr = start_addr + sort_addr_bias;
    int blk_tuple[sort_times];

    for (int i = 0; i < sort_times; i++) {
        if ((blks[i] = readBlockFromDisk(ext_sort_addr[i], buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
        blk_tuple[i] = 0;
    }

    while (1) {
        int x1, x2, y1, y2, min_index = -1;
        for (int i = 0; i < sort_times; i++) {
            if (blks[i] != NULL) {
                min_index = i;
                break;
            }
        }
        if (min_index == -1)
            break;  // 证明所有的有序段都已经识别完毕
        memcpy(&x1, (int *) (blks[min_index] + blk_tuple[min_index] * tuples_size), int_size);
        memcpy(&y1, (int *) (blks[min_index] + blk_tuple[min_index] * tuples_size + int_size), int_size);
        for (int i = min_index + 1; i < sort_times; i++) {
            if (blks[i] == NULL)
                continue;
            memcpy(&x2, (int *) (blks[i] + blk_tuple[i] * tuples_size), int_size);
            memcpy(&y2, (int *) (blks[i] + blk_tuple[i] * tuples_size + int_size), int_size);
            if (paramIndex == 1) {
                if (x1 > x2) {
                    x1 = x2;
                    y1 = y2;
                    min_index = i;
                }
            } else {
                if (y1 > y2) {
                    x1 = x2;
                    y1 = y2;
                    min_index = i;
                }
            }
        }
        // 1.将当前的最小元组写到输出缓冲区，并判断输出缓冲区是否已满
        memcpy(writeBuffer + write_buffer_using, (unsigned char *) &x1, int_size);
        memcpy(writeBuffer + write_buffer_using + int_size, (unsigned char *) &y1, int_size);
        write_buffer_using += tuples_size;
        if (write_buffer_using + tuples_size >= blkSize) {
            int temp_write_next_addr = write_blk_addr + blkSize;
            memcpy(writeBuffer + write_buffer_using, (unsigned char *) &temp_write_next_addr, int_size);
            if (writeBlockToDisk(writeBuffer, write_blk_addr, buffer) != 0) {
                return -1;
            }
            write_blk_addr = temp_write_next_addr;
            writeBuffer = getNewBlockInBuffer(buffer);
            freshBlockInBuffer(buffer, writeBuffer);
            write_buffer_using = 0;
        }
        // 2.最小元组对应的块的指针下移，并判断该指针是否到块末尾
        if (++blk_tuple[min_index] >= tuples_per_block) {
            unsigned int next_read_addr;
            memcpy(&next_read_addr, (unsigned int *) (blks[min_index] + blkSize - tuples_size), int_size);
            freeBlockInBuffer(blks[min_index], buffer);
            if (next_read_addr == 0 ||
                (min_index < sort_times - 1 && next_read_addr == ext_sort_addr[min_index + 1]))
                blks[min_index] = NULL; // 证明当前的块已经是对应的有序段里的最后一块，且此有序段中所有元素均已经输出
            else {
                if ((blks[min_index] = readBlockFromDisk(next_read_addr, buffer)) == NULL) {
                    perror("Reading Block Failed!\n");
                    return -1;
                }
                blk_tuple[min_index] = 0;
            }
        }
    }

    if (write_buffer_using == 0) {
        // 多申请一个块 需要将之前块的后续位置置为零
        freeBlockInBuffer(writeBuffer, buffer);
        if ((writeBuffer = readBlockFromDisk(write_blk_addr - blkSize, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
        memcpy(writeBuffer + blkSize - tuples_size, (unsigned char *) &end_blk_next_addr, int_size);
        if (writeBlockToDisk(writeBuffer, write_blk_addr - blkSize, buffer) != 0) {
            return -1;
        }
    } else {
        if (writeBlockToDisk(writeBuffer, write_blk_addr, buffer) != 0)
            return -1;
    }

    return 0;
}

int projection(Buffer *buffer, unsigned int start_addr) {
    unsigned char *readBuffer;
    if ((readBuffer = readBlockFromDisk(start_addr, buffer)) == NULL) {
        perror("Reading Block Failed!\n");
        return -1;
    }
    unsigned char *writeBuffer = getNewBlockInBuffer(buffer);
    unsigned int write_next_addr = projection_addr;
    int write_buffer_using = 0;
    while (1) {
        unsigned char *temp = readBuffer;
        for (int i = 0; i < tuples_per_block; i++) {
            memcpy(writeBuffer + write_buffer_using, (unsigned char *) temp, int_size);
            write_buffer_using += int_size;
            if (write_buffer_using + int_size >= blkSize) {
                unsigned int temp_write_next_addr = write_next_addr + blkSize;
                memcpy(writeBuffer + write_buffer_using, (unsigned char *) &temp_write_next_addr, int_size);
                if (writeBlockToDisk(writeBuffer, write_next_addr, buffer) != 0)
                    return -1;
                write_next_addr = temp_write_next_addr;
                writeBuffer = getNewBlockInBuffer(buffer);
                freshBlockInBuffer(buffer, writeBuffer);
                write_buffer_using = 0;
            }
            temp += tuples_size;
        }
        unsigned int next_read_addr;
        memcpy(&next_read_addr, (unsigned int *) temp, int_size);
        if (next_read_addr == 0) {
            freeBlockInBuffer(readBuffer, buffer);
            break;
        }

        freeBlockInBuffer(readBuffer, buffer);
        if ((readBuffer = readBlockFromDisk(next_read_addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
    }
    if (write_buffer_using == 0) {
        // 多申请一个块 需要将之前块的后续位置置为零
        freeBlockInBuffer(writeBuffer, buffer);
        if ((writeBuffer = readBlockFromDisk(write_next_addr - blkSize, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
        memcpy(writeBuffer + blkSize - int_size, (unsigned char *) &end_blk_next_addr, int_size);
        if (writeBlockToDisk(writeBuffer, write_next_addr - blkSize, buffer) != 0) {
            return -1;
        }
    } else {
        if (writeBlockToDisk(writeBuffer, write_next_addr, buffer) != 0)
            return -1;
    }
    return 0;
}

int outputProjection(Buffer *buffer) {
    unsigned char *readBuffer;
    unsigned int addr = projection_addr;
    if ((readBuffer = readBlockFromDisk(addr, buffer)) == NULL) {
        perror("Reading Block Failed!\n");
        return -1;
    }
    while (1) {
        unsigned char *temp = readBuffer;
        for (int i = 0; i < blkSize - int_size; i += int_size) {
            int x;
            memcpy(&x, (int *) temp, int_size);
            printf("%d\n", x);
            temp += int_size;
        }

        unsigned int next_read_addr;
        memcpy(&next_read_addr, (unsigned int *) temp, int_size);
        printf("%d\n", next_read_addr);

        if (next_read_addr == 0) {
            freeBlockInBuffer(readBuffer, buffer);
            break;
        }

        freeBlockInBuffer(readBuffer, buffer);
        if ((readBuffer = readBlockFromDisk(next_read_addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
    }
    return 0;
}

int binarySearch(Buffer *buffer, unsigned int relation_addr, int paramIndex, int searchValue) {
    if (relation_addr != r_start_addr && relation_addr != s_start_addr) {
        perror("There are only two relations: R and S!\n");
        return -1;
    }

    if (paramIndex != 1 && paramIndex != 2) {
        perror("Param index of binary search is 1 or 2!\n");
        return -1;
    }


    unsigned int left_addr, right_addr, mid_addr = 0, left_prev = -1, right_prev = -1;
    int found = 0;
    unsigned char *readBuffer;
    if (relation_addr == r_start_addr) {
        if ((paramIndex == 1 && (searchValue > A_MAX || searchValue < A_MIN)) ||
            (paramIndex == 2 && (searchValue > B_MAX || searchValue < B_MIN))) {
            return 1;
        }
        left_addr = r_start_addr + sort_addr_bias;
        right_addr = r_start_addr + sort_addr_bias + NUMBER_OF_R / tuples_per_block * blkSize;
    } else {
        if ((paramIndex == 1 && (searchValue > C_MAX || searchValue < C_MIN)) ||
            (paramIndex == 2 && (searchValue > D_MAX || searchValue < D_MIN))) {
            return 1;
        }
        left_addr = s_start_addr + sort_addr_bias;
        right_addr = s_start_addr + sort_addr_bias + NUMBER_OF_S / tuples_per_block * blkSize;
    }

    while (left_addr < right_addr) {
        if (left_addr == left_prev && right_addr == right_prev) {
            // 出现死循环 跳出
            found = 0;
            break;
        }
        mid_addr = (right_addr - left_addr) / (2 * blkSize) * blkSize + left_addr;
        if ((readBuffer = readBlockFromDisk(mid_addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
        int relation = 0;
        for (int i = 0; i < tuples_per_block; i++) {
            int x, y;
            memcpy(&x, (int *) (readBuffer + i * tuples_size), int_size);
            memcpy(&y, (int *) (readBuffer + i * tuples_size + int_size), int_size);
            if (paramIndex == 1)
                relation = x == searchValue ? 0 : x > searchValue ? 1 : -1;
            else
                relation = y == searchValue ? 0 : y > searchValue ? 1 : -1;
            if (relation >= 0)
                // 如果当前块的第一条元组的查询元素已经大于待搜索值 则后面的所有元组中均不会出现待查询值
                // 如果当前块出现了符合要求的查询值 可能存在两种情况
                // 1. 当前元组恰好是该块内的第一条元组 在其之前的块中仍然存在可能符合要求的元组
                // 2. 当前元组恰好是第一条满足要求的元组 从该块向后读输出即可
                break;
        }
        freeBlockInBuffer(readBuffer, buffer);
        if (relation > 0) {
            left_prev = left_addr;
            right_prev = right_addr;
            right_addr = mid_addr;
        } else if (relation < 0) {
            right_prev = right_addr;
            left_prev = left_addr;
            left_addr = mid_addr;
        } else {
            unsigned char *search_first_fit_tuple;
            found = 1;
            int i;
            for (i = 1; i <= (mid_addr - relation_addr - sort_addr_bias) / blkSize; i++) {
                if ((search_first_fit_tuple = readBlockFromDisk(mid_addr - i * blkSize, buffer)) == NULL) {
                    perror("Reading Block Failed!\n");
                    return -1;
                }
                int x, y;
                memcpy(&x, (int *) search_first_fit_tuple, int_size);
                memcpy(&y, (int *) (search_first_fit_tuple + int_size), int_size);
                freeBlockInBuffer(search_first_fit_tuple, buffer);
                if (paramIndex == 1) {
                    if (x < searchValue)
                        break;
                } else {
                    if (y < searchValue)
                        break;
                }
            }
            if (relation_addr + sort_addr_bias + i * blkSize > mid_addr)
                // 第一块的第一个元组也是待搜索的元组
                mid_addr = relation_addr + sort_addr_bias;
            else
                mid_addr = mid_addr - i * blkSize;
            break;
        }
    }
    if (!found) {
        // Not Found
        return 1;
    }
    unsigned char *writeBuffer;
    writeBuffer = getNewBlockInBuffer(buffer);
    freshBlockInBuffer(buffer, writeBuffer);
    unsigned int write_next_addr = linear_search_answer_addr;
    int write_buffer_using = 0, end = 0;
    unsigned int addr = mid_addr;
    while (1) {
        if ((readBuffer = readBlockFromDisk(addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
        for (int i = 0; i < tuples_per_block; i++) {
            int x, y;
            memcpy(&x, (int *) (readBuffer + i * tuples_size), int_size);
            memcpy(&y, (int *) (readBuffer + i * tuples_size + int_size), int_size);
            if ((paramIndex == 1 && x == searchValue) || (paramIndex == 2 && y == searchValue)) {
                memcpy(writeBuffer + write_buffer_using, (unsigned char *) &x, int_size);
                memcpy(writeBuffer + write_buffer_using + int_size, (unsigned char *) &y, int_size);
                write_buffer_using += tuples_size;
                if (write_buffer_using + tuples_size >= blkSize) {
                    int temp_next_addr = write_next_addr + blkSize;
                    memcpy(writeBuffer + write_buffer_using, (unsigned char *) &temp_next_addr, int_size);
                    if (writeBlockToDisk(writeBuffer, write_next_addr, buffer) != 0)
                        return -1;
                    write_next_addr = temp_next_addr;
                    writeBuffer = getNewBlockInBuffer(buffer);
                    freshBlockInBuffer(buffer, writeBuffer);
                    write_buffer_using = 0;
                }
            } else if ((paramIndex == 1 && x > searchValue) || (paramIndex == 2 && y > searchValue)) {
                end = 1;
                break;
            }
        }
        unsigned int next_read_blk_addr;
        memcpy(&next_read_blk_addr, (unsigned char *) (readBuffer + blkSize - tuples_size), int_size);
        freeBlockInBuffer(readBuffer, buffer);
        if (next_read_blk_addr == 0 || end == 1)
            break;
        addr = next_read_blk_addr;
    }
    if (write_buffer_using == 0) {
        freeBlockInBuffer(writeBuffer, buffer);
        if ((writeBuffer = readBlockFromDisk(write_next_addr - blkSize, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
        memcpy(writeBuffer + blkSize - tuples_size, (unsigned char *) &end_blk_next_addr, int_size);
        if (writeBlockToDisk(writeBuffer, write_next_addr - blkSize, buffer) != 0)
            return -1;
    } else {
        if (writeBlockToDisk(writeBuffer, write_next_addr, buffer) != 0)
            return -1;
    }
    return 0;
}

int nestLoopJoin(Buffer *buffer) {
    unsigned int out_addr, in_addr;
    if (NUMBER_OF_S > NUMBER_OF_R) {
        out_addr = r_start_addr;
        in_addr = s_start_addr;
    } else {
        out_addr = s_start_addr;
        in_addr = r_start_addr;
    }
    int found = 0;
    unsigned char *out_p, *in_p, *write_buffer;
    unsigned int write_next_addr = join_answer_addr;
    unsigned int origin_in_relation_start_addr = in_addr;
    int write_using = 0;
    write_buffer = getNewBlockInBuffer(buffer);
    freshBlockInBuffer(buffer, write_buffer);
    while (1) {
        if ((out_p = readBlockFromDisk(out_addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
        for (int i = 0; i < tuples_per_block; i++) {
            int x1, y1;
            memcpy(&x1, (int *) (out_p + i * tuples_size), int_size);
            memcpy(&y1, (int *) (out_p + i * tuples_size + int_size), int_size);
            in_addr = origin_in_relation_start_addr;
            while (1) {
                if ((in_p = readBlockFromDisk(in_addr, buffer)) == NULL) {
                    perror("Reading Block Failed!\n");
                    return -1;
                }
                for (int j = 0; j < tuples_per_block; j++) {
                    int x2, y2;
                    memcpy(&x2, (int *) (in_p + j * tuples_size), int_size);
                    memcpy(&y2, (int *) (in_p + j * tuples_size + int_size), int_size);

                    if (x1 == x2) {
                        found = 1;
                        memcpy(write_buffer + write_using, (unsigned char *) &x1, int_size);
                        memcpy(write_buffer + write_using + int_size, (unsigned char *) &y1, int_size);
                        memcpy(write_buffer + write_using + tuples_size, (unsigned char *) &y2, int_size);
                        write_using += (tuples_size + int_size);
                        if (write_using + tuples_size + int_size >= blkSize) {
                            int temp_write_next_addr = write_next_addr + blkSize;
                            memcpy(write_buffer + write_using, (unsigned char *) &temp_write_next_addr, int_size);
                            if (writeBlockToDisk(write_buffer, write_next_addr, buffer) != 0)
                                return -1;
                            write_buffer = getNewBlockInBuffer(buffer);
                            freshBlockInBuffer(buffer, write_buffer);
                            write_using = 0;
                            write_next_addr = temp_write_next_addr;
                        }
                    }
                }
                unsigned int temp_in_next_addr;
                memcpy(&temp_in_next_addr, (unsigned int *) (in_p + blkSize - tuples_size), int_size);
                freeBlockInBuffer(in_p, buffer);
                if (temp_in_next_addr == 0)
                    break;

                in_addr = temp_in_next_addr;
            }
        }
        unsigned int temp_out_next_addr;
        memcpy(&temp_out_next_addr, (unsigned int *) (out_p + blkSize - tuples_size), int_size);
        freeBlockInBuffer(out_p, buffer);
        if (temp_out_next_addr == 0)
            break;

        out_addr = temp_out_next_addr;
    }
    if (write_using == 0) {
        if (found == 0) {
            freeBlockInBuffer(write_buffer, buffer);
            return 1;   // not such tuples
        } else {
            freeBlockInBuffer(write_buffer, buffer);
            if ((write_buffer = readBlockFromDisk(write_next_addr - blkSize, buffer)) == NULL) {
                perror("Reading Block Failed!\n");
                return -1;
            }
            memcpy(write_buffer + blkSize - int_size, (unsigned char *) &end_blk_next_addr, int_size);
            if (writeBlockToDisk(write_buffer, write_next_addr - blkSize, buffer) != 0)
                return -1;
            return 0;
        }
    } else {
        if (writeBlockToDisk(write_buffer, write_next_addr, buffer) != 0)
            return -1;
        return 0;
    }
}

int sortMergeJoin(Buffer *buffer) {
    externalSorting(buffer, s_start_addr, 1);
    externalSorting(buffer, r_start_addr, 1);
    printf("Before sort-merge join, after sort relation r and s:\n");
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer->numFreeBlk, buffer->numAllBlk, buffer->numIO);

    unsigned char *r_read_buffer, *s_read_buffer, *write_buffer;
    int write_using = 0;
    unsigned int write_next_addr = join_answer_addr;
    write_buffer = getNewBlockInBuffer(buffer);
    freshBlockInBuffer(buffer, write_buffer);
    int ri, si, found;
    ri = si = found = 0;
    unsigned int s_next_addr, r_next_addr;
    s_next_addr = s_start_addr + sort_addr_bias;
    r_next_addr = r_start_addr + sort_addr_bias;

    if ((r_read_buffer = readBlockFromDisk(r_next_addr, buffer)) == NULL) {
        perror("Reading Block Failed!\n");
        return -1;
    }

    if ((s_read_buffer = readBlockFromDisk(s_next_addr, buffer)) == NULL) {
        perror("Reading Block Failed!\n");
        return -1;
    }
    S s[32];    // 除去3个已用的缓存块 最多可存储数据所用空间可以存储40个关系S的元组 超过32个重复元素的sort-merge join不正确
    int s_array_count = 0;
    while (1) {
        if (ri >= tuples_per_block) {
            unsigned int temp_r_read_next_addr;
            memcpy(&temp_r_read_next_addr, (unsigned int *) (r_read_buffer + ri * tuples_size), int_size);
            freeBlockInBuffer(r_read_buffer, buffer);
            if (temp_r_read_next_addr == 0) {
                freeBlockInBuffer(s_read_buffer, buffer);
                break;
            }
            r_next_addr = temp_r_read_next_addr;
            if ((r_read_buffer = readBlockFromDisk(r_next_addr, buffer)) == NULL) {
                perror("Reading Block Failed!\n");
                return -1;
            }
            ri = 0;
        }
        if (si >= tuples_per_block) {
            unsigned int temp_s_read_next_addr;
            memcpy(&temp_s_read_next_addr, (unsigned int *) (s_read_buffer + si * tuples_size), int_size);
            freeBlockInBuffer(s_read_buffer, buffer);
            if (temp_s_read_next_addr == 0) {
                freeBlockInBuffer(r_read_buffer, buffer);
                break;
            }
            s_next_addr = temp_s_read_next_addr;
            if ((s_read_buffer = readBlockFromDisk(s_next_addr, buffer)) == NULL) {
                perror("Reading Block Failed!\n");
                return -1;
            }
            si = 0;
        }
        int x1, y1, x2, y2;
        memcpy(&x1, (int *) (r_read_buffer + ri * tuples_size), int_size);
        memcpy(&y1, (int *) (r_read_buffer + ri * tuples_size + int_size), int_size);
        memcpy(&x2, (int *) (s_read_buffer + si * tuples_size), int_size);
        memcpy(&y2, (int *) (s_read_buffer + si * tuples_size + int_size), int_size);

        if (x1 == x2) {
            found = 1;
            if (s_array_count == 0) {
                s[s_array_count].c = x2;
                s[s_array_count++].d = y2;
                unsigned char *temp_s_read_buffer;
                // 尝试向下找所有与x2相等的元组
                if ((temp_s_read_buffer = readBlockFromDisk(s_next_addr, buffer)) == NULL) {
                    perror("Reading Block Failed!\n");
                    return -1;
                }
                int temp_si = si + 1;
                while (1) {
                    if (temp_si >= tuples_per_block) {
                        unsigned int temp_temp_s_read_next_addr;
                        memcpy(&temp_temp_s_read_next_addr,
                               (unsigned int *) (temp_s_read_buffer + temp_si * tuples_size), int_size);
                        freeBlockInBuffer(temp_s_read_buffer, buffer);
                        if (temp_temp_s_read_next_addr == 0)
                            break;
                        if ((temp_s_read_buffer = readBlockFromDisk(temp_temp_s_read_next_addr, buffer)) == NULL) {
                            perror("Reading Block Failed!\n");
                            return -1;
                        }
                        temp_si = 0;
                    }
                    int c, d;
                    memcpy(&c, (int *) (temp_s_read_buffer + temp_si * tuples_size), int_size);
                    memcpy(&d, (int *) (temp_s_read_buffer + temp_si * tuples_size + int_size), int_size);
                    if (c == x2) {
                        s[s_array_count].c = c;
                        s[s_array_count++].d = d;
                        temp_si++;
                    } else {
                        freeBlockInBuffer(temp_s_read_buffer, buffer);
                        break;
                    }
                }
            }
            for (int i = 0; i < s_array_count; i++) {
                memcpy(write_buffer + write_using, (unsigned char *) &x2, int_size);
                memcpy(write_buffer + write_using + int_size, (unsigned char *) &y1, int_size);
                memcpy(write_buffer + write_using + int_size * 2, (unsigned char *) &(s[i].d), int_size);
                write_using += (tuples_size + int_size);
                if (write_using + tuples_size + int_size >= blkSize) {
                    int temp_write_next_addr = write_next_addr + blkSize;
                    memcpy(write_buffer + write_using, (unsigned char *) &temp_write_next_addr, int_size);
                    if (writeBlockToDisk(write_buffer, write_next_addr, buffer) != 0)
                        return -1;
                    write_next_addr = temp_write_next_addr;
                    write_using = 0;
                    write_buffer = getNewBlockInBuffer(buffer);
                    freshBlockInBuffer(buffer, write_buffer);
                }
            }
            ri++;
        } else {
            s_array_count = 0;
            if (x1 < x2) {
                ri++;
            } else if (x1 > x2) {
                si++;
            }
        }
    }
    if (write_using == 0) {
        freeBlockInBuffer(write_buffer, buffer);
        if (found == 0) {
            // not found
            return 1;
        } else {
            if ((write_buffer = readBlockFromDisk(write_next_addr - blkSize, buffer)) == NULL) {
                perror("Reading Block Failed!\n");
                return -1;
            }
            // 此处式子不具有一般性 应改为 write_buffer + blkSize - blkSize / (int_size + tuple_size) * (int_size + tuple_size)
            // 为了方便写为下列形式
            memcpy(write_buffer + blkSize - int_size, (unsigned char *) &end_blk_next_addr, int_size);
            if (writeBlockToDisk(write_buffer, write_next_addr - blkSize, buffer) != 0)
                return -1;
            return 0;
        }
    } else {
        if (writeBlockToDisk(write_buffer, write_next_addr, buffer) != 0)
            return -1;
        return 0;
    }
}

int addBPlusTree(Buffer *buffer, unsigned int relation_addr, int paramIndex) {
    if (relation_addr != r_start_addr && relation_addr != s_start_addr) {
        perror("There are only two relations: R and S!\n");
        return -1;
    }

    if (paramIndex != 1 && paramIndex != 2) {
        perror("Param index of binary search is 1 or 2!\n");
        return -1;
    }

    externalSorting(buffer, relation_addr, paramIndex);
    printf("Free_blocks: %zu, All_blocks: %zu, IO times: %lu\n", buffer->numFreeBlk, buffer->numAllBlk, buffer->numIO);

    unsigned char *read_buffer, *write_leaf_buffer, *write_inner_buffer;
    int write_leaf_buffer_using = 0;
    unsigned int write_next_addr = b_plus_tree_root_addr + blkSize;
    write_leaf_buffer = getNewBlockInBuffer(buffer);
    freshBlockInBuffer(buffer, write_leaf_buffer);

    unsigned int read_next_addr = relation_addr + sort_addr_bias;
    int inner_index = 0;
    write_inner_buffer = getNewBlockInBuffer(buffer);

    unsigned char *root_buffer = NULL;
    int root_using = 0;

    freshBlockInBuffer(buffer, write_inner_buffer);

    int now_value = -1;
    while (1) {
        if ((read_buffer = readBlockFromDisk(read_next_addr, buffer)) == NULL) {
            perror("Reading Block Failed!\n");
            return -1;
        }
        for (int i = 0; i < tuples_per_block; i++) {
            int x, y;
            memcpy(&x, (int *) (read_buffer + i * tuples_size), int_size);
            memcpy(&y, (int *) (read_buffer + i * tuples_size + int_size), int_size);
            if (now_value == -1) {
                now_value = paramIndex == 1 ? x : y;
                memcpy(write_leaf_buffer + write_leaf_buffer_using, (unsigned char *) &read_next_addr, int_size);
                write_leaf_buffer_using += int_size;
                // 第一次进入
            } else {
                if ((paramIndex == 1 && x > now_value) || (paramIndex == 2 && y > now_value)) {
                    now_value = paramIndex == 1 ? x : y;
                    memcpy(write_leaf_buffer + write_leaf_buffer_using, (unsigned char *) &read_next_addr, int_size);
                    write_leaf_buffer_using += int_size;
                    if (write_leaf_buffer_using / int_size >= tuples_per_block) {
                        // m = 6
                        if (writeBlockToDisk(write_leaf_buffer, write_next_addr, buffer) != 0)
                            return -1;
                        memcpy(write_inner_buffer + 2 * inner_index * int_size, (unsigned char *) &write_next_addr,
                               int_size);
                        now_value++;
                        memcpy(write_inner_buffer + (2 * inner_index + 1) * int_size, (unsigned char *) &now_value,
                               int_size);

                        write_next_addr += blkSize;
                        write_leaf_buffer = getNewBlockInBuffer(buffer);
                        freshBlockInBuffer(buffer, write_leaf_buffer);
                        write_leaf_buffer_using = 0;

                        inner_index++;
                        if (inner_index >= tuples_per_block) {
                            // 内节点已满
                            if (root_buffer == NULL) {
                                root_buffer = getNewBlockInBuffer(buffer);
                                freshBlockInBuffer(buffer, root_buffer);
                                root_using = 0;
                            }
                            if (writeBlockToDisk(write_inner_buffer, write_next_addr, buffer) != 0)
                                return -1;
                            memcpy(root_buffer + 2 * root_using * int_size, (unsigned char *) &write_next_addr,
                                   int_size);
                            memcpy(root_buffer + (2 * root_using + 1) * int_size, (unsigned char *) &now_value,
                                   int_size);
                            root_using++;
                            write_next_addr += blkSize;
                            write_inner_buffer = getNewBlockInBuffer(buffer);
                            freshBlockInBuffer(buffer, write_inner_buffer);
                            inner_index = 0;
                        }
                        now_value--;
                    }
                }
            }
        }
        unsigned int temp_next_read_addr;
        memcpy(&temp_next_read_addr, (unsigned int *) (read_buffer + blkSize - tuples_size), int_size);
        freeBlockInBuffer(read_buffer, buffer);
        if (temp_next_read_addr == 0)
            break;
        read_next_addr = temp_next_read_addr;
    }
    if (root_buffer == NULL) {
        if (write_leaf_buffer_using != 0) {
            memcpy(write_inner_buffer + 2 * inner_index * int_size, (unsigned char *) &write_next_addr, int_size);
            if (writeBlockToDisk(write_leaf_buffer, write_next_addr, buffer) != 0)
                return -1;
//        write_next_addr += blkSize;
        } else {
            freeBlockInBuffer(write_leaf_buffer, buffer);
        }
        if (writeBlockToDisk(write_inner_buffer, b_plus_tree_root_addr, buffer) != 0)
            return -1;
    } else {
        if (write_leaf_buffer_using != 0) {
            unsigned int temp_write_next_addr = write_next_addr - blkSize;  // 此时write_next_addr代表的是当前内部块的地址
            // todo 此处应该区分write_next_addr的使用 可以重构为对于write_leaf_buffer和write_inner_buffer使用不同的变量区分地址
            memcpy(write_inner_buffer + 2 * inner_index * int_size, (unsigned char *) &temp_write_next_addr, int_size);
            if (writeBlockToDisk(write_leaf_buffer, write_next_addr, buffer) != 0)
                return -1;
        } else {
            freeBlockInBuffer(write_leaf_buffer, buffer);
        }
        if (inner_index != 0)
            memcpy(root_buffer + 2 * root_using * int_size, (unsigned char *) &write_next_addr, int_size);
        if (writeBlockToDisk(root_buffer, b_plus_tree_root_addr, buffer) != 0)
            return -1;
        if (writeBlockToDisk(write_inner_buffer, write_next_addr, buffer) != 0)
            return -1;
    }
    return 0;
}
