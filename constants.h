/**
 * ssu: Seamless Software Update
 * Copyright (c) 2012, 2013, 2014 Jolla Ltd.
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
 * @file constants.h
 * @copyright 2012 Jolla Ltd.
 * @author Bernd Wachter <bernd.wachter@jollamobile.com>
 * @date 2012
 */

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

/// The group ID ssu expects to run as. This is usually the GID of the main phone user
#define SSU_GROUP_ID 1000
/// Path to the main ssu configuration file
#define SSU_REPO_CONFIGURATION "/usr/share/ssu/repos.ini"
/// Path to board / device family mappings file
#define SSU_BOARD_MAPPING_CONFIGURATION "/var/cache/ssu/board-mappings.ini"
/// Path to config.d for board mappings
#define SSU_BOARD_MAPPING_CONFIGURATION_DIR "/usr/share/ssu/board-mappings.d"
/// Directory where all the non-user modifiable data sits
#define SSU_DATA_DIR "/usr/share/ssu/"
/// The ssu protocol version used by the ssu client libraries
#define SSU_PROTOCOL_VERSION "1"
/// Maximum recursion level for resolving variables
#define SSU_MAX_RECURSION 1024
/// Path to zypper repo configuration
#define ZYPP_REPO_PATH "/etc/zypp/repos.d"
#endif
