<h1 align="center">cfs</h1>
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
	<img width="80%" src="res/thumbnail.png"/>
	<br><br><br>
</p>

A simple single-header [STB-style](https://github.com/nothings/stb) cross-platform C filesystem library.

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
Output

<img width="25%" src="res/img.png"/>

## Quickstart
Just copy [`cfs.h`](./cfs.h) into your project or submodule this repository and include the header.
[See the examples](./examples) to see how to use the library.

To compile and run the examples, run
```sh
$ cc ./examples/ls.c -o ls
$ cc ./examples/copy.c -o copy
$ cc ./examples/link.c -o link
$ cc ./examples/join.c -o join
$ cc ./examples/foreach.c -o foreach
$ ./ls
$ ./copy
$ ./link
$ ./join
$ ./foreach
```

## Bugs
If you find any bugs, please create an issue and report them.
