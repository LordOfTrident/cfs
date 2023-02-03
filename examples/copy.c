#include <stdio.h>  /* printf */
#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE */

#define CFS_IMPLEMENTATION
#include "../cfs.h"

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "Copy a file\nUsage: %s PATH NEW_PATH\n", argv[0]);
		return EXIT_FAILURE;
	}

	const char *path = argv[1], *new  = argv[2];
	if (!fs_exists(path)) {
		fprintf(stderr, "Error: file '%s' does not exist\n", path);
		return EXIT_FAILURE;
	}

	if (fs_copy(path, new) != 0) {
		fprintf(stderr, "Error: could not copy file '%s' to '%s'\n", path, new);
		return EXIT_FAILURE;
	}
	printf("Succesfully copied '%s' to '%s'\n", path, new);
	return EXIT_SUCCESS;
}
