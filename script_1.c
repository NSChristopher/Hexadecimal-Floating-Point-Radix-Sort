#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printIntArray(unsigned int *arr, int count) {
    for (int i = 0; i < count; i++) {
        float value = *((float *)(arr + i));
        printf("%.2f\n", value);
    }

}

// sorts an array of ints using a version of radix sort that analysis the 32 bits in 4 bit hex segments. 
void floatRadixSort(unsigned int *arr, int count, int negCount) {
    
    unsigned int *buffer, **buckets, *bucketCounts;

    buffer = (unsigned int*) calloc(count, sizeof(unsigned int));
    buckets = (unsigned int**) calloc(16, sizeof(unsigned int *));
    for (int i = 0; i < 16; i++)
    {
        *(buckets + i) = (unsigned int*) calloc(count, sizeof(unsigned int));
    }
    
    bucketCounts = (unsigned int*) calloc(16, sizeof(unsigned int));

    // iterates over all 8 segments of each integer.
    for (int i = 0; i < 8; i++) {

        // resets the bucketCounts array to all 0's.
        for (int j = 0; j < 16; j++) {
            *(bucketCounts + j) = 0;
        }

        // iterates over each integer in the array sorting the ith segments by their respective buckets and putting the full integer value in the bucket.
        for (int j = 0; j < count; j++) {

            unsigned int value = *(arr + j);
            int hexSeg = (value >> 4 * i) & 0xF;

            *(*(buckets + hexSeg) + *(bucketCounts + hexSeg)) = value;
            *(bucketCounts + hexSeg) += 1;
        }

        // combines all buckets into the buffer array
        int negStartIndex = -1;
        int bufferIndex = 0;
        for (int j = 0; j < 16; j++) {
            for (int k = 0; k < *(bucketCounts + j); k++) {
                unsigned int bucketVal = *(*(buckets + j) + k);
                *(buffer + bufferIndex) = bucketVal;
                bufferIndex++;
                if(i > 7 && negStartIndex < 0 && bucketVal < 0) negStartIndex = bufferIndex;
            }
        }

        // loads all elements of the buffer array. Except on the last loop so negative number order can be corrected.
        if(i > 7) continue;

        for (int j = 0; j < count; j++) {
            *(arr + j) = *(buffer + j);
        }

    }

    // Correct negative number order
    int negStart = count - negCount;
    int k = 0;
    for (int j = count - 1; j >= negStart; j--) {
        *(arr + k) = *(buffer + j);
        k++;
    }
    k = negCount;
    for (int j = 0; j < negStart; j++) {
        *(arr + k) = *(buffer + j);
        k++;
    }


    free(buckets);
    free(buffer);
    free(bucketCounts);

}

int main() {

    int count = 0;
    int negCount = 0;
    
    // // Read input from users
    // printf("Enter the count: ");
    // scanf("%d", &count);

    // unsigned int *iarr = calloc(count, sizeof(*iarr));

    // printf("Enter a float: ");
    // for (int i = 0; i < count; i++)
    // {
    //     float f;
    //     scanf("%f", &f);
    //     if(f < 0) negCount++;
    //     *(iarr + i) = *(unsigned int*)&f;
    // }

    // Read input piped from bash test script
    if (scanf("%d", &count) != 1) {
        fprintf(stderr, "Could not read count.\n");
        return 1;
    }

    unsigned int *uiarr = calloc(count, sizeof(*uiarr));

    for (int i = 0; i < count; ++i) {
        float f;
        if (scanf("%f", &f) != 1) {
            fprintf(stderr, "Could not read number %u.\n", i + 1);
            return 1;
        }
        if(f < 0) negCount++;
        *(uiarr + i) = *(unsigned int*)&f;
    }
    
    floatRadixSort(uiarr, count, negCount);

    // Print Array
    printIntArray(uiarr, count);

    free(uiarr);

    return 1;
}