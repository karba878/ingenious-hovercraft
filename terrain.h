//
// terrain.h
//

#ifndef TERRAIN_H
#define TERRAIN_H

//
// Defines
//
#define T_BUFFER_LENGTH       200 // Circular buffer length
#define T_TERRAIN_DOT_N         9 // Amount of vertices on each segment (odd! at least 3)
#define T_TERRAIN_SEG_DIST     10 // Distance between segments

#define T_TERRAIN_START_WIDTH  20 // Width of first element

//
// Terrain segment struct
//
struct terrain_seg
{
   vec2 dots[T_TERRAIN_DOT_N];
};

//
// Global variables
//
extern terrain_seg  t_terrain[];
extern int          t_terrain_sta;
extern int          t_terrain_end;

//
// Function declarations
//
void t_init();
bool t_new_segment();

#endif // end terrain.h
