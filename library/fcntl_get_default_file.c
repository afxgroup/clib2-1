/*
 * $Id: fcntl_get_default_file.c,v 1.6 2006-09-12 14:16:44 obarthel Exp $
 *
 * :ts=4
 *
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2006 by Olaf Barthel <olsen (at) sourcery.han.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   - Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   - Neither the name of Olaf Barthel nor the names of contributors
 *     may be used to endorse or promote products derived from this
 *     software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _FCNTL_HEADERS_H
#include "fcntl_headers.h"
#endif /* _FCNTL_HEADERS_H */

/****************************************************************************/

/* The following is not part of the ISO 'C' (1994) standard. */

/****************************************************************************/

int
__get_default_file(int file_descriptor,long * file_ptr)
{
	int result = ERROR;
	struct fd * fd;
	BPTR file;

	assert( file_descriptor >= 0 && file_descriptor < __num_fd );
	assert( __fd[file_descriptor] != NULL );
	assert( FLAG_IS_SET(__fd[file_descriptor]->fd_Flags,FDF_IN_USE) );
	assert( file_ptr != NULL );

	fd = __get_file_descriptor(file_descriptor);
	if(fd == NULL)
	{
		__set_errno(EBADF);
		goto out;
	}

	__fd_unlock(fd);

	#if defined(__THREAD_SAFE)
	{
		/* Check if this file should be dynamically bound to one of the
		   three standard I/O streams. */
		if(FLAG_IS_SET(fd->fd_Flags,FDF_STDIO))
		{
			switch(fd->fd_DefaultFile)
			{
				case STDIN_FILENO:

					file = Input();
					break;

				case STDOUT_FILENO:

					file = Output();
					break;

				case STDERR_FILENO:

					#if defined(__amigaos4__)
					{
						file = ErrorOutput();
					}
					#else
					{
						struct Process * this_process = (struct Process *)FindTask(NULL);

						file = this_process->pr_CES;
					}
					#endif /* __amigaos4__ */

					/* The following is rather controversial; if the standard error stream
					   is unavailable, we default to reuse the standard output stream. This
					   is problematic if the standard output stream was redirected and should
					   not be the same as the standard error output stream. */
					if(file == ZERO)
						file = Output();

					break;

				default:

					file = ZERO;
					break;
			}
		}
		else
		{
			file = fd->fd_DefaultFile;
		}
	}
	#else
	{
		file = fd->fd_DefaultFile;
	}
	#endif /* __THREAD_SAFE */

	(*file_ptr) = (long)file;

	result = 0;

 out:

	__fd_unlock(fd);

	return(result);
}
