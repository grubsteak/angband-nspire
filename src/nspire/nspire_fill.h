#ifndef _NSPIRE_FILL_H
#define _NSPIRE_FILL_H
#include <sys/stat.h>
#include <pwd.h>

static char *pw_name = "nspire";
static char *pw_dir = "/";

unsigned int getuid(void) {
    return 0;
}

extern struct passwd* getpwuid(uid_t uid);

extern struct passwd* getpwnam(const char* str);

//extern  unsigned int umask(unsigned int mask);

extern void usleep(useconds_t t);
#endif