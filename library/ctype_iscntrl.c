/*
 * $Id: ctype_iscntrl.c,v 1.3 2005-02-27 21:58:21 obarthel Exp $
 *
 * :ts=4
 *
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2005 by Olaf Barthel <olsen@sourcery.han.de>
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

#ifndef _CTYPE_HEADERS_H
#include "ctype_headers.h"
#endif /* _CTYPE_HEADERS_H */

/****************************************************************************/

#undef iscntrl

/****************************************************************************/

int
iscntrl(int c)
{
	DECLARE_LOCALEBASE();
	int result;

	__locale_lock();

	if(__locale_table[LC_CTYPE] != NULL)
	{
		assert( LocaleBase != NULL );

		result = IsCntrl(__locale_table[LC_CTYPE],(ULONG)c);
	}
	else
	{
		result = (('\0' <= c && c < ' ') || (c == 127));
	}

	__locale_unlock();

	return(result);
}
