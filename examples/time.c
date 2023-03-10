#include <stdio.h>  /* printf, stderr, fprintf */
#include <stdlib.h> /* EXIT_FAILURE, EXIT_SUCCESS */

#define CFS_IMPLEMENTATION
#include "../cfs.h"

int main(int argc, char **argv) {
	const char *path = "./README";

	uint64_t access, modif;
	if (fs_time(path, &modif, &access) != 0) {
		fprintf(stderr, "Failed to get modified and access time of file '%s'\n", path);
		return EXIT_FAILURE;
	}

	printf("Last modified time of '%s': %lu\n", path, (unsigned long)modif);
	printf("Last access time of '%s':   %lu\n", path, (unsigned long)access);

	return EXIT_SUCCESS;
}
