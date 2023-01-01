/**
 * \file z-profiler.h
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

#ifndef INCLUDED_Z_PROFILER_H
#define INCLUDED_Z_PROFILER_H

#define PROFILER_STACK_SIZE 256


typedef struct profiler_data {
    const char* name;
    int id;
    unsigned int start_time;
    unsigned int child_time;
} profiler_data;
extern profiler_data profiler_states[PROFILER_STACK_SIZE];
extern int profiler_stack_pointer;

#undef PROFILE_ENABLE

#ifdef PROFILE_ENABLE
extern void push_profile(const char* id);
extern void pop_profile();


#define PROFILE(id, ...) {push_profile(id); __VA_OPT__(__VA_ARGS__) pop_profile();}
#define PROFILE_RETURN(N) do{for(int __kounter=0; __kounter<N; __kounter++){ pop_profile(); } return;}while(0)
#else
#define pop_profile() (void)0
#define push_profile(id) (void)0 
#define PROFILE(id,...) { __VA_ARGS__ }
#define PROFILE_RETURN(N) return
#endif

#endif