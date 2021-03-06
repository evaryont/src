/*
  This file is part of Musca.

  Musca is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as publishead by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Musca is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Musca.  If not, see <http://www.gnu.org/licenses/>.

  Sean Pringle
  sean dot pringle at gmail dot com
  https://launchpad.net/musca
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>
#include <setjmp.h>
#include <math.h>
#include <unistd.h>
#include <regex.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define CHUNKS(c,n) (((n)<1)?0:((((n)-1)/(c))+1)*(c))
#define BLOCK 1024
#define BLOCKS(n) CHUNKS(BLOCK,(n))
#define NOTE 256

typedef char byte;
typedef unsigned char ubyte;
typedef short int word;
typedef unsigned short int uword;
typedef int cell;
typedef unsigned int ucell;
typedef long long int lcell;
typedef unsigned long long int ulcell;
typedef double dcell;

typedef struct {
	jmp_buf jmp;
	void *prev;
	ubyte code;
} exception;
exception *safety;

#define try(name) exception (name); \
	(name).prev = safety; \
	safety = &(name); \
	(name).code = setjmp((name).jmp); \
	if (!(name).code)

#define catch(name) safety = (name).prev
#define throw(val) longjmp(safety->jmp, val)

typedef struct _autostr {
	char *pad;
	ucell len;
	ucell lim;
} autostr;

typedef cell (*str_cb_chr)(cell);

#define STACK 32
typedef struct {
	void **items;
	ucell depth;
	ucell limit;
} stack;

