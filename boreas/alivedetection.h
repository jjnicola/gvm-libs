/* Copyright (C) 2020 Greenbone Networks GmbH
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef ALIVE_DETECTION_H
#define ALIVE_DETECTION_H

#include "../base/hosts.h"
#include "../util/kb.h"

/* to how many hosts are packets send to at a time. value <= 0 for no rate limit
 */
#define BURST 100
/* how long (in msec) to wait until new BURST of packets is send */
#define BURST_TIMEOUT 100000
/* how tong (in sec) to wait for replies after last packet was sent */
#define WAIT_FOR_REPLIES_TIMEOUT 5

/* Redis related */

/* Queue (Redis list) for communicating with openvas main process. */
#define ALIVE_DETECTION_QUEUE "alive_detection"
/* Signal to put on ALIVE_DETECTION_QUEUE if alive detection finished. */
#define ALIVE_DETECTION_FINISHED "alive_detection_finished"

gvm_host_t *
get_host_from_queue (kb_t alive_hosts_kb, gboolean *alive_detection_finished);

void *
start_alive_detection (void *hosts);

/**
 * @brief Alive tests.
 *
 * These numbers are used in the database by gvmd, so if the number associated
 * with any symbol changes in gvmd we need to change them here too.
 */
typedef enum
{
  ALIVE_TEST_TCP_ACK_SERVICE = 1,
  ALIVE_TEST_ICMP = 2,
  ALIVE_TEST_ARP = 4,
  ALIVE_TEST_CONSIDER_ALIVE = 8,
  ALIVE_TEST_TCP_SYN_SERVICE = 16
} alive_test_t;

/**
 * @brief Alive detection error codes.
 */
typedef enum
{
  BOREAS_OPENING_SOCKET_FAILED = -100,
  BOREAS_SETTING_SOCKET_OPTION_FAILED,
  BOREAS_NO_VALID_ALIVE_TEST_SPECIFIED,
  BOREAS_CLEANUP_ERROR,
  BOREAS_NO_SRC_ADDR_FOUND,
  NO_ERROR = 0,
} boreas_error_t;

/**
 * @brief Type of socket.
 */
typedef enum
{
  TCPV4,
  TCPV6,
  ICMPV4,
  ICMPV6,
  ARPV4,
  ARPV6,
  UDPV4,
  UDPV6,
} socket_type_t;

#endif
