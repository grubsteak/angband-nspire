#include <sys/stat.h>
#include <pwd.h>
#include <libndls.h>

uid_t getuid(void) {
    return 0;
}

struct passwd* getpwuid(uid_t uid) {
    static struct passwd fakepasswd = {
        .pw_name = "nspire",
        .pw_dir = "/"
    };
    return &fakepasswd;
}

struct passwd* getpwnam(const char* str) {
    return getpwuid(0);
}

mode_t umask(mode_t mask) {
    return mask;
}

int usleep(useconds_t t) {
    return msleep(t /  1000);
}