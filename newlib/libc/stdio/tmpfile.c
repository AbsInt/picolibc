/*
FUNCTION
<<tmpfile>>---create a temporary file

INDEX
	tmpfile
INDEX
	_tmpfile_r

SYNOPSIS
	#include <stdio.h>
	FILE *tmpfile(void);

	FILE *_tmpfile_r(struct _reent *<[reent]>);

DESCRIPTION
Create a temporary file (a file which will be deleted automatically),
using a name generated by <<tmpnam>>.  The temporary file is opened with
the mode <<"wb+">>, permitting you to read and write anywhere in it
as a binary file (without any data transformations the host system may
perform for text files).

The alternate function <<_tmpfile_r>> is a reentrant version.  The
argument <[reent]> is a pointer to a reentrancy structure.

RETURNS
<<tmpfile>> normally returns a pointer to the temporary file.  If no
temporary file could be created, the result is NULL, and <<errno>>
records the reason for failure.

PORTABILITY
Both ANSI C and the System V Interface Definition (Issue 2) require
<<tmpfile>>.

Supporting OS subroutines required: <<close>>, <<fstat>>, <<getpid>>,
<<isatty>>, <<lseek>>, <<open>>, <<read>>, <<sbrk>>, <<write>>.

<<tmpfile>> also requires the global pointer <<environ>>.
*/

#include <_ansi.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#ifndef O_BINARY
# define O_BINARY 0
#endif

FILE *
_tmpfile_r (struct _reent *ptr)
{
  FILE *fp;
  int e;
  char *f;
  char buf[L_tmpnam];
  int fd;

  do
    {
      if ((f = _tmpnam_r (ptr, buf)) == NULL)
	return NULL;
      fd = open (f, O_RDWR | O_CREAT | O_EXCL | O_BINARY,
		    S_IRUSR | S_IWUSR);
    }
  while (fd < 0 && __errno_r(ptr) == EEXIST);
  if (fd < 0)
    return NULL;
  fp = _fdopen_r (ptr, fd, "wb+");
  e = __errno_r(ptr);
  if (!fp)
    close (fd);
  (void) remove (f);
  __errno_r(ptr) = e;
  return fp;
}

#ifndef _REENT_ONLY

FILE *
tmpfile (void)
{
  return _tmpfile_r (_REENT);
}

#endif
