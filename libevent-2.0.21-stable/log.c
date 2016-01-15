/*	$OpenBSD: err.c,v 1.2 2002/06/25 15:50:15 mickey Exp $	*/

/*
 * log.c
 *
 * Based on err.c, which was adapted from OpenBSD libc *err* *warn* code.
 *
 * Copyright (c) 2005-2012 Niels Provos and Nick Mathewson
 *
 * Copyright (c) 2000 Dug Song <dugsong@monkey.org>
 *
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "event2/event-config.h"

#ifdef WIN32
#include <winsock2.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "event2/event.h"
#include "event2/util.h"

#include "log-internal.h"

static void _warn_helper(int severity, const char *errstr, const char *fmt,
    va_list ap);
static void event_log(int severity, const char *msg);
static void event_exit(int errcode) EV_NORETURN;

static event_fatal_cb fatal_fn = NULL;

void
event_set_fatal_callback(event_fatal_cb cb)
{
	fatal_fn = cb;
}

static void
event_exit(int errcode)
{
}

void
event_err(int eval, const char *fmt, ...)
{
}

void
event_warn(const char *fmt, ...)
{
}

void
event_sock_err(int eval, evutil_socket_t sock, const char *fmt, ...)
{
}

void
event_sock_warn(evutil_socket_t sock, const char *fmt, ...)
{
}

void
event_errx(int eval, const char *fmt, ...)
{
}

void
event_warnx(const char *fmt, ...)
{
}

void
event_msgx(const char *fmt, ...)
{
}

void
_event_debugx(const char *fmt, ...)
{
}

static void
_warn_helper(int severity, const char *errstr, const char *fmt, va_list ap)
{
}

static event_log_cb log_fn = NULL;

void
event_set_log_callback(event_log_cb cb)
{
	log_fn = cb;
}

static void
event_log(int severity, const char *msg)
{

}
