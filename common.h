#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROOMS 200
#define STR_LEN_SHORT 32
#define STR_LEN_MID 64
#define STR_LEN_LONG 128

// Helper umum & konversi waktu (Kesepakatan Tim)
int time_to_minutes(int hour, int minute);
void minutes_to_time_str(int minutes, char* buffer);
bool is_time_overlap(int start1, int end1, int start2, int end2);

#endif // COMMON_H
