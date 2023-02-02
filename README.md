<h1 align="center">cfs</h1>
<p align="center">A cross-platform filesystem library for C</p>

<p align="center">
	<a href="./LICENSE">
		<img alt="License" src="https://img.shields.io/badge/license-GPL-blue?color=26d374"/>
	</a>
	<a href="https://github.com/LordOfTrident/cfs/issues">
		<img alt="Issues" src="https://img.shields.io/github/issues/LordOfTrident/cfs?color=4f79e4"/>
	</a>
	<a href="https://github.com/LordOfTrident/cfs/pulls">
		<img alt="GitHub pull requests" src="https://img.shields.io/github/issues-pr/LordOfTrident/cfs?color=4f79e4"/>
	</a>
	<br><br><br>
</p>

A simple single-header STB-style cross-platform C filesystem library.

## Table of contents
* [Simple example](#simple-example)
* [Quickstart](#quickstart)
* [Bugs](#bugs)

## Simple example
```c
#include <stdio.h> /* printf */

#define CFS_IMPLEMENTATION
#include "cfs.h"

int main(void) {
	fs_dir_t dir;
	fs_dir_open(&dir, "./");

	fs_ent_t ent;
	while (fs_dir_next(&dir, &ent) == 0)
		printf("%s\n", ent.name);

	fs_dir_close(&dir);
	return 0;
}
```

## Quickstart
Just copy [`cfs.h`](./cfs.h) into your project and include it.
[See the example](./examples/main.c) to see how to use the library.

To compile and run the example, run
```sh
$ cc ./examples/main.c -o main
$ ./main
```

## Bugs
If you find any bugs, please create an issue and report them.
