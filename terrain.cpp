//
// terrain.cpp
//

#include "common.h"
#include "terrain.h"

//
// Local variables
//
terrain_seg previous_seg;
double      terrain_left;
double      terrain_right;

//
// Global variables
//
terrain_seg  t_terrain[T_BUFFER_LENGTH];
int          t_terrain_sta = 0;
int          t_terrain_end = T_BUFFER_LENGTH-1;

//
// Initialize terrain
//
void t_init()
{
    // Initialize terrain parameters
    terrain_left  = -T_TERRAIN_START_WIDTH*0.5;
    terrain_right =  T_TERRAIN_START_WIDTH*0.5;

    // Initialize first previous segment (not in buffer)
    for(int i=0; i<T_TERRAIN_DOT_N; i++)
    {
        previous_seg.dots[i].x = terrain_left + i*(terrain_right-terrain_left)/(T_TERRAIN_DOT_N-1);
	previous_seg.dots[i].y = 0;
    }

    // Init terrain
    while(t_new_segment());

}

//
// Create and append new terrain segment
//
bool t_new_segment()
{
    // Increment end index
    t_terrain_end++;
    if(t_terrain_end >= T_BUFFER_LENGTH)
        t_terrain_end = 0;

    // Don't push the limit
    if(t_terrain_end == t_terrain_sta)
        return false;

    // Get segment address
    terrain_seg* seg = &(t_terrain[t_terrain_end]);

    // Change dot coordinates
    // TEMP: Just copy the last segment
    for(int i=0; i<T_TERRAIN_DOT_N; i++)
    {
        seg->dots[i].x = previous_seg.dots[i].x;
	seg->dots[i].y = previous_seg.dots[i].y;
    }

    return true;

}
