#ifndef CFS_HEADER_GUARD
#define CFS_HEADER_GUARD

#include <stdbool.h> /* bool, true, false */
#include <string.h>  /* strcpy, strcat, memset */

#ifndef WIN32
#	if defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#		define WIN32
#	endif
#endif

#ifdef WIN32
#	include <windows.h>

#	ifndef PATH_MAX
#		ifndef MAX_PATH
#			define PATH_MAX 1024
#		else
#			define PATH_MAX MAX_PATH
#		endif
#	endif
#else
#	include <unistd.h>
#	include <dirent.h>
#	include <sys/stat.h>
#	include <sys/types.h>

#	ifndef PATH_MAX
#		define PATH_MAX 1024
#	endif
#endif

typedef enum {
	FS_REGULAR = 0,
	FS_HIDDEN  = 1 << 0,
	FS_DIR     = 1 << 1,
	FS_LINK    = 1 << 2,

	FS_INVALID_ATTR = 1 << 3,
} fs_attr_t;

typedef struct {
#ifdef WIN32
	WIN32_FIND_DATA data;
	HANDLE          handle;

	bool first;
#else
	DIR *d;
#endif

	const char *path;
} fs_dir_t;

typedef struct {
#ifdef WIN32
	WIN32_FIND_DATA data;
#else
	struct dirent *e;
#endif

	const char *name;
	fs_attr_t   attr;
} fs_ent_t;

fs_attr_t   fs_attr(const     char *path);
const char *fs_basename(const char *path);
bool        fs_exists(const   char *path);

int fs_dir_open(fs_dir_t *d, const char *path);
int fs_dir_close(fs_dir_t *d);
int fs_dir_next(fs_dir_t *d, fs_ent_t *e);

#endif

#ifdef CFS_IMPLEMENTATION

bool fs_exists(const char *path) {
#ifdef WIN32
	DWORD attr = GetFileAttributesA(path);
	return attr != INVALID_FILE_ATTRIBUTES;
#else
	return access(path, F_OK) == 0;
#endif
}

const char *fs_basename(const char *path) {
	for (size_t i = strlen(path) - 1; i > 0; -- i) {
		if (path[i] == '\\' || path[i] == '/')
			return path + i + 1;
	}
	return path;
}

fs_attr_t fs_attr(const char *path) {
	fs_attr_t   attr = FS_REGULAR;
	const char *base = fs_basename(path);

#ifdef WIN32
	WORD attrs = GetFileAttributesA(path);

	if (attrs & FILE_ATTRIBUTE_HIDDEN || strcmp(base, ".") == 0 || strcmp(base, "..") == 0)
		attr |= FS_HIDDEN;
	if (attrs & FILE_ATTRIBUTE_DIRECTORY)
		attr |= FS_DIR;
	if (attrs & FILE_ATTRIBUTE_REPARSE_POINT)
		attr |= FS_LINK;
#else
	struct stat s;
	if (stat(path, &s) != 0)
		return FS_INVALID_ATTR;

	if (base[0] == '.')
		attr |= FS_HIDDEN;
	if (S_ISDIR(s.st_mode))
		attr |= FS_DIR;
	if (S_ISLNK(s.st_mode))
		attr |= FS_LINK;
#endif

	return attr;
}

int fs_dir_open(fs_dir_t *d, const char *path) {
#ifdef WIN32
	char pattern[MAX_PATH] = {0};
	strcpy(pattern, path);
	strcat(pattern, "\\*");

	d->handle = FindFirstFile(pattern, &d->data);
	if (d->handle == INVALID_HANDLE_VALUE)
		return -1;

	d->first = true;
#else
	d->d = opendir(path);
	if (d->d == NULL)
		return -1;
#endif

	d->path = path;
	return 0;
}

int fs_dir_close(fs_dir_t *d) {
#ifdef WIN32
	if (!FindClose(d->handle))
		return -1;
#else
	if (closedir(d->d) != 0)
		return -1;
#endif

	memset(d, 0, sizeof(*d));
	return 0;
}

int fs_dir_next(fs_dir_t *d, fs_ent_t *e) {
#ifdef WIN32
	if (d->first)
		d->first = false;
	else {
		if (FindNextFile(d->handle, &d->data) == 0)
			return -1;
	}

	e->data = d->data;
	e->name = e->data.cFileName;
#else
	e->e = readdir(d->d);
	if (e->e == NULL)
		return -1;

	e->name = e->e->d_name;
#endif

	char path[PATH_MAX] = {0};
	strcpy(path, d->path);
	strcat(path, "/");
	strcat(path, e->name);

	e->attr = fs_attr(path);
	if (e->attr == FS_INVALID_ATTR)
		return -1;

	return 0;
}

#endif
