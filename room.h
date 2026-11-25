
#ifndef ROOM_H
#define ROOM_H

#include "common.h"
#include "schedule.h"

/* Struktur data ruangan */
typedef struct {
    char code[STR_LEN_SHORT];
    char building[STR_LEN_MID];
    int floor;
    int capacity;
    char facilities[STR_LEN_LONG];
    ScheduleNode* schedule_head;
} Room;

/* Struktur data Array ruangan */
typedef struct {
    Room rooms[MAX_ROOMS];
    int count;
} RoomArray;

/* Fungsi pengelolaan Array ruangan */
void init_room_array(RoomArray* ra);

bool add_room(RoomArray* ra, const char* code,
              const char* building, int floor,
              int capacity, const char* facilities);

bool update_room(RoomArray* ra, const char* code,
                 const char* building, int floor,
                 int capacity, const char* facilities);

bool delete_room(RoomArray* ra, const char* code);

void display_all_rooms(const RoomArray* ra);

void display_room_detail(const Room* room);

/* Filter ruangan berdasarkan fasilitas */
int filter_rooms_by_facility(const RoomArray* ra,
                             const char* facility);

#endif
