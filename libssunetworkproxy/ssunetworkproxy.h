/**
 * ssu: Seamless Software Update
 * Copyright (c) 2014 Jolla Ltd.
 * Contact: Bernd Wachter <bernd.wachter@jolla.com>
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **/

/**
 * @file ssunetworkproxy.h
 * @copyright 2014 Jolla Ltd.
 * @author Juha Kallioinen <juha.kallioinen@jolla.com>
 * @date 2014
 */

#ifndef _LibSsuNetworkProxy_H
#define _LibSsuNetworkProxy_H
#include <dlfcn.h>

/**
 * Set application proxy if the required library is found, otherwise
 * do nothing.
 */
inline void set_application_proxy_factory()
{
    void *proxylib = dlopen("libssunetworkproxy.so", RTLD_LAZY);
    if (proxylib) {
        typedef void (*ssuproxyinit_t)();
        dlerror();
        ssuproxyinit_t proxy_init = (ssuproxyinit_t) dlsym(proxylib, "initialize");
        const char *dlsym_err = dlerror();
        if (!dlsym_err) {
            proxy_init();
        }
        dlclose(proxylib);
    }
}

#endif
