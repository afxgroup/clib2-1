/*
 * $Id: stdlib_locale_utility.h,v 1.1.1.1 2004-07-26 16:31:57 obarthel Exp $
 *
 * :ts=4
 *
 * Portable ISO 'C' (1994) runtime library for the Amiga computer
 * Copyright (c) 2002-2004 by Olaf Barthel <olsen@sourcery.han.de>
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

#ifndef _STDLIB_LOCALE_UTILITY_H
#define _STDLIB_LOCALE_UTILITY_H

/****************************************************************************/

#ifndef __NOLIBBASE__
#define __NOLIBBASE__
#endif /* __NOLIBBASE__ */

#ifndef __NOGLOBALIFACE__
#define __NOGLOBALIFACE__
#endif /* __NOGLOBALIFACE__ */

#include <proto/utility.h>
#include <proto/locale.h>

/****************************************************************************/

extern struct Library * __UtilityBase;
extern struct Library * __LocaleBase;

/****************************************************************************/

#if defined(__amigaos4__)

/****************************************************************************/

extern struct UtilityIFace *	__IUtility;
extern struct LocaleIFace *		__ILocale;

/****************************************************************************/

#define DECLARE_UTILITYBASE() \
	struct Library *		UNUSED	UtilityBase	= __UtilityBase; \
	struct UtilityIFace *			IUtility	= __IUtility

#define DECLARE_LOCALEBASE() \
	struct Library *		UNUSED	LocaleBase	= __LocaleBase; \
	struct LocaleIFace *			ILocale		= __ILocale

/****************************************************************************/

#else

/****************************************************************************/

#define DECLARE_UTILITYBASE() \
	struct Library * UtilityBase = __UtilityBase

#define DECLARE_LOCALEBASE() \
	struct Library * LocaleBase = __LocaleBase

/****************************************************************************/

#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* _STDLIB_LOCALE_UTILITY_H */