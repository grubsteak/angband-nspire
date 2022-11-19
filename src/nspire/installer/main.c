#include <stdio.h>

#include "zip.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

struct buffer_t {
    char *data;
    size_t size;
};

static size_t on_extract(void *arg, unsigned long long offset, const void *data, size_t size) {
    struct buffer_t *buf = (struct buffer_t *)arg;
    buf->data = realloc(buf->data, buf->size + size + 1);
	if(buf->data == NULL) {
		fprintf(stderr, "ERROR: could not allocate enough memory: %d\n", size);
		abort();
	}
    memcpy(&(buf->data[buf->size]), data, size);
    buf->size += size;
    buf->data[buf->size] = 0;

    return size;
}

char* add_prefix(const char *str)
{
	char *ret = calloc(strlen(str)+1,1);
	strcat(ret,str);
	return ret;
}

char* add_tns(const char *filename)
{
	if(strstr(filename,".tns")==NULL) {
		const char *dot_tns=".tns";
		char *ret = calloc(strlen(filename)+strlen(dot_tns)+1,1);
		strcat(ret,filename);
		strcat(ret,dot_tns);
		return ret;
	} else {
		char *ret = calloc(strlen(filename)+1,1);
		strcat(ret,filename);
		return ret;
	}
}

int main(int argc, char **argv)
{
	printf("Extracting angband...\n");
	struct zip_t *zip = zip_open(argv[0], 0, 'r');
	int i, n = zip_total_entries(zip);
	for (i = 0; i < n; ++i) {
	    zip_entry_openbyindex(zip, i);
	    {
	        const char *name = zip_entry_name(zip);
	        int isdir = zip_entry_isdir(zip);
	        unsigned long long size = zip_entry_size(zip);
	        unsigned int crc32 = zip_entry_crc32(zip);
			printf("name=%s\nis-dir=%d\nsize=%lu\ncrc=%x\n---------\n",name, isdir, size, crc32);
			if(isdir) {
				char *dirname = add_prefix(name);
				mkdir(dirname,0666);
				free(dirname);
			} else if(strstr(name,"/.") == NULL) {
				printf("extracting %s\n",name);
				struct buffer_t buf = {0};
				char *filename_prefixed = add_prefix(name);
				char *filename = add_tns(filename_prefixed);
				FILE * f = fopen(filename,"wb");
				if(f==NULL) {
					fprintf(stderr, "ERROR: cannot open %s\n", filename);
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
	printf("Done.\n");
}
