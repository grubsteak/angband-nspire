/**
 * \file z-profiler.c
 * \brief Profiling functions
 *
 * Copyright (c) 2022 Joel Herzog
 *
 * This work is free software; you can redistribute it and/or modify it
 * under the terms of either:
 *
 * a) the GNU General Public License as published by the Free Software
 *    Foundation, version 2, or
 *
 * b) the "Angband licence":
 *    This software may be copied and distributed for educational, research,
 *    and not for profit purposes provided that this copyright and statement
 *    are included in all such copies.  Other copyrights may also apply.
 */

#if 0

#include "z-profiler.h"
#include <stdio.h>
#include <SDL/SDL.h>
#include <nspireio/nspireio.h>

profiler_data profiler_states[PROFILER_STACK_SIZE];
int profiler_stack_pointer = 0;
int counter = 0;

nio_console c1;
int console_init = 0;

void init_console() {
    
    console_init = 1;
	// 53 columns, 15 rows. 0px offset for x/y. Background color 15 (white), foreground color 0 (black)
	nio_init(&c1,NIO_MAX_COLS,NIO_MAX_ROWS,0,0,WHITE,BLACK,true);
    // Ruh roh, no way to close it.
}

void push_profile(const char* name) {
    if(!console_init) init_console();
    profiler_stack_pointer++;
    profiler_data *profile = &profiler_states[profiler_stack_pointer];
    profile->name = name;
    profile->id = counter++;
    profile->start_time = SDL_GetTicks();
    profile->child_time = 0;
    // printf("[%d]start %s at %ld ms\n", profile->id, profile->name, profile->start_time);
    //fflush(stdout);
}
void pop_profile(const char* name) {
    profiler_data *profile = &profiler_states[profiler_stack_pointer];
    profiler_stack_pointer--;

    // printf("[%d]     end %s\n", profile->id, profile->name);
    long int child_time = (long int)profile->child_time;
    if(profile->name == NULL) {
        nio_fprintf(&c1,"error: profile name is null : %s\n", name); // break z-profiler.c:41
    } else {
        long int duration = (((long int)SDL_GetTicks()-(long int)profile->start_time));
        if(duration>10) {
            for(int i=0; i<profiler_stack_pointer; i++) {
                nio_fprintf(&c1," ");
            }

            // this should let us see whats actually taking soo long
            if(profiler_stack_pointer > 0) {
                (&profiler_states[profiler_stack_pointer])->child_time += duration;
            }
            nio_fprintf(&c1,"%s took %ld/%ld ms\n", profile->name, duration-child_time, duration);
            
        }
    }
    fflush(stdout);
}


#endif