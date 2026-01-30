#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval t1, t2;
    long min = 1000000;

    for (int i = 0; i < 100000; i++) {
        gettimeofday(&t1, NULL);
        for (volatile int j = 0; j < 100; j++);   // tiny delay
        gettimeofday(&t2, NULL);

        long diff =
            (t2.tv_sec - t1.tv_sec) * 1000000L +
            (t2.tv_usec - t1.tv_usec);

        if (diff > 0 && diff < min)
            min = diff;
    }

    printf("Smallest non-zero interval: %ld us\n", min);
}
