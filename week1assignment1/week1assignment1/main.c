//
//  main.c
//  week1assignment1
//
//  Created by Anh Luong on 7/23/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

/*
 * Problem: Inversion
 * Input: array A containing the numbers 1,2,3,...,n in some arbitrary order
 * Output: number of inversions = number of pairs (i,j) of array indices with i < j, and A[i] > A[j]
 * Algorithm: divide and conquer
 * Pseudocode:
 *      Sort-and-Count(array A, length n)
 *      if n = 1, return 0
 *      else
 *          (B, x) = Sort-and-Count(1st half of A, n/2)
 *          (C, y) = Sort-and-Count(2nd half of B, n/2)
 *          (D, z) = CountSplitInv(A, n)
 *          return x + y + z
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXARRAY        100000

void merge(int *a, int asize, int *b, int bsize, int *c, int csize);
void mymergesort(int *a, int asize);
unsigned countSplitInv(int *a, int asize, int *b, int bsize, int *c, int csize);
unsigned sortAndCount(int *a, int asize);

int main(int argc, const char * argv[]) {
    int i, num;
    FILE *fp;
    int inarray[MAXARRAY], copyarray[MAXARRAY];
    
    if ((fp = fopen(*++argv, "r")) == NULL) {
        printf("read failed\n");
        return 1;
    }
    
    for (i = 0; fscanf(fp, "%d", &inarray[i]) != EOF; i++) {
        //printf("Number read: %d\n", inarray[i]);
        copyarray[i] = inarray[i];
    }

    num = i;
    printf("Total number of elements is %d\n", num);
    /*
    mymergesort(copyarray, num);
    
    for (i = 0; i < num; i++)
        printf("After sorted %d\n", copyarray[i]);
    
    for (i = 0; i < num; i++)
        if (inarray[i] == copyarray[i])
            printf("Line %d with element %d is inversion\n", i + 1, inarray[i]);
     */
    
    printf("Total number of inversions is %u\n", sortAndCount(inarray, num));
    fclose(fp);
    return 0;
}

void merge(int *a, int asize, int *b, int bsize, int *c, int csize)
{
    int i, j, k;
    
    for (i = j = k = 0; k < csize; k++)
    {
        if (i >= asize)
            c[k] = b[j++];
        else if (j >= bsize)
            c[k] = a[i++];
        else if (a[i] < b[j]) {
            c[k] = a[i++];
        } else {    // a[i] >= b[j]
            c[k] = b[j++];
        }
    }
}

void mymergesort(int *a, int asize)
{
    int firsthalf, secondhalf;
    int *c;
    int i;
    
    if (asize == 1)
        return;
    firsthalf = asize / 2;
    secondhalf = asize - firsthalf;
    //printf("firsthalf %d, secondhalf %d\n", firsthalf, secondhalf);
    mymergesort(a, asize / 2);
    mymergesort((a + firsthalf), secondhalf);
    c = (int *) malloc(asize * sizeof(int));
    
    for (i = 0; i < asize; i++) // duplicate the string
        c[i] = a[i];
    merge(c, firsthalf, (c + firsthalf), secondhalf, a, asize);
    free(c);
}

unsigned countSplitInv(int *a, int asize, int *b, int bsize, int *c, int csize)
{
    int i, j, k;
    unsigned inversion = 0;
    int l;
    
    for (i = j = k = 0; k < csize; k++)
    {
        if (i >= asize)
            c[k] = b[j++];
        else if (j >= bsize) {  // don't need to increment inversion counter here because the else statement already taken care of it. If we increment here, it will be counted double in some case, such as 456 and 123 (6_2IntegerArray.txt)
            // ALDBG printf("j >= bsize start\n");
            c[k] = a[i++];
            // ALDBG printf("j >= bsize end\n");
        } else if (a[i] < b[j]) {
            c[k] = a[i++];
        } else {    // a[i] >= b[j]
            // ALDBG printf("else start\n");
            assert(a[i] >= b[j]);
            /* ALDBG
            for (l = i; l < asize; l++)
                printf("Inversion pair (%d, %d)\n", a[l], b[j]);
             */
            c[k] = b[j++];
            inversion += (asize - i);
            // ALDBG printf("else end\n");
        }
    }
    return inversion;
}

unsigned sortAndCount(int *a, int asize)
{
    int firsthalf, secondhalf;
    int *c;
    int i;
    unsigned inversion = 0;
    
    if (asize == 1)
        return 0;
    firsthalf = asize / 2;
    secondhalf = asize - firsthalf;
    //printf("firsthalf %d, secondhalf %d\n", firsthalf, secondhalf);
    inversion += sortAndCount(a, asize / 2);
    inversion += sortAndCount((a + firsthalf), secondhalf);
    c = (int *) malloc(asize * sizeof(int));
    
    for (i = 0; i < asize; i++) // duplicate the string
        c[i] = a[i];
    inversion += countSplitInv(c, firsthalf, (c + firsthalf), secondhalf, a, asize);
    free(c);
    return inversion;
}