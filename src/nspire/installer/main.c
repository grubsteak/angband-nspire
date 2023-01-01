/*
This is a self-extracting installer for the game on the TI-Nspire.
Very hacky.
*/

#include <libndls.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "zip.h"

struct buffer_t {
    char *data;
    size_t size;
};

static size_t on_extract(void *arg, unsigned long long offset, const void *data, size_t size) {
    struct buffer_t *buf = (struct buffer_t *)arg;
    buf->data = realloc(buf->data, buf->size + size + 1);
    if (buf->data == NULL) {
        fprintf(stderr, "ERROR: could not allocate enough memory: %d\n", size);
        abort();
    }
    memcpy(&(buf->data[buf->size]), data, size);
    buf->size += size;
    buf->data[buf->size] = 0;

    return size;
}

char *add_prefix(const char *str) {
    char *ret = calloc(strlen(str) + 1, 1);
    strcat(ret, str);
    return ret;
}

char *add_tns(const char *filename) {
    if (strstr(filename, ".tns") == NULL) {
        const char *dot_tns = ".tns";
        char *ret = calloc(strlen(filename) + strlen(dot_tns) + 1, 1);
        strcat(ret, filename);
        strcat(ret, dot_tns);
        return ret;
    } else {
        char *ret = calloc(strlen(filename) + 1, 1);
        strcat(ret, filename);
        return ret;
    }
}

/** Hacky piece of code right here:
Given filename, it scans it for our magic number 'FUPA' and then overwrite the file with whatever comes after that
*/
typedef unsigned char uint8;
typedef unsigned int uint32;
int self_extract(const char *filename) {
    uint8 needle[4] = {'F', 'U', 'P', 'A'};
    uint8 search[4] = {0x00, 0x00, 0x00, 0x00};
    FILE *f = fopen(filename, "rb");

    if (!f)
        return 0;

    uint32 zip_start = 0;

    while (1) {
        search[0] = search[1];
        search[1] = search[2];
        search[2] = search[3];

        if (fread(&search[3], 1, 1, f) != 1) {
            return 0;
        } else if (search[0] == needle[0] && search[1] == needle[1] && search[2] == needle[2] && search[3] == needle[3]) {
			zip_start++;
            printf("Found start of zip: %ud", zip_start);
            break;
        }
        zip_start++;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f) - zip_start;
    fseek(f, zip_start, SEEK_SET); /* same as rewind(f); */

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

	f = fopen(filename, "wb");
	if(!f) {
		return 0;
	}
	fwrite(string, fsize, 1, f);
	fclose(f);
	string[20] = '\0';
	free(string);

	return 1;
}

//const char *zipfile = "angband.zip.tns";

int main(int argc, char **argv) {
    if (show_msgbox_2b("Angband Installer", "Would you like to install Angband?", "Yes", "No") == 2) {
        exit(-1);
    }
    printf("Extracting angband...\n");
	if(!self_extract(argv[0])) {
		show_msgbox("Error", "Can't open embedded archive");
        return -1;
	}
    struct zip_t *zip = zip_open(argv[0], 0, 'r');
    if (zip == NULL) {
        show_msgbox("Error", "Extraction failed");
        return -1;
    }
    int i, n = zip_total_entries(zip);
    for (i = 0; i < n; ++i) {
        zip_entry_openbyindex(zip, i);
        {
            const char *name = zip_entry_name(zip);
            int isdir = zip_entry_isdir(zip);
            unsigned long long size = zip_entry_size(zip);
            unsigned int crc32 = zip_entry_crc32(zip);
            printf("name=%s\nis-dir=%d\nsize=%lu\ncrc=%x\n---------\n", name, isdir, size, crc32);
            if (isdir) {
                char *dirname = add_prefix(name);
                mkdir(dirname, 0666);
                free(dirname);
            } else if (strstr(name, "/.") == NULL) {
                printf("extracting %s\n", name);
                struct buffer_t buf = {0};
                char *filename_prefixed = add_prefix(name);
                char *filename = add_tns(filename_prefixed);
                FILE *f = fopen(filename, "wb");
                if (f == NULL) {
                    fprintf(stderr, "ERROR: cannot open %s\n", filename);
                    show_msgbox("Error: cannot open", filename);
                    abort();
                }
                zip_entry_extract(zip, on_extract, &buf);
                fwrite(buf.data, buf.size, 1, f);
                fclose(f);
                free(buf.data);
                free(filename_prefixed);
                free(filename);
                printf("Done.\n");
            } else {
                printf("ignoring dotfile %s\n", name);
            }
        }
        zip_entry_close(zip);
    }
    zip_close(zip);
	remove(argv[0]);
    printf("Done.\n");
    show_msgbox("Angband Installer", "Angband installed!");
}
