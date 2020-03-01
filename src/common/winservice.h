/*
 * Copyright (C) 2002-2020  Auriga
 *
 * This file is part of Auriga.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef _WINSERVICE_H_
#define _WINSERVICE_H_

#ifdef WINDOWS

#include "utils.h"

bool winservice_change_current_dir(void);
bool winservice_init(int argc, char **argv);
bool winservice_notify_start(void);
bool winservice_notify_ready(void);
bool winservice_notify_stop(void);
bool winservice_notify_finish(void);

#else

#define winservice_change_current_dir() (1 == 1)
#define winservice_init(c,v)            (1 == 0)
#define winservice_notify_start()       (1 == 1)
#define winservice_notify_ready()       (1 == 1)
#define winservice_notify_stop()        (1 == 1)
#define winservice_notify_finish()      (1 == 1)

#endif

#endif /* _WINSERVICE_H_ */
