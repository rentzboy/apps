/****************************************************************************
 * apps/examples/bmi160/sixaxis_main.c
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <inttypes.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <nuttx/sensors/lsm303dlhc.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define ACC_DEVPATH      "/dev/acc"

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * sixaxis_main
 ****************************************************************************/

int main(int argc, char *argv[])
{
  int fd;
  struct lsm303dlhc_acc_data_s data;

  fd = open(ACC_DEVPATH, O_RDONLY);
  if (fd < 0)
    {
      printf("Device %s open failure. %d\n", ACC_DEVPATH, fd);
      return -1;
    }

  for (; ; )
    {
      int ret;

      ret = read(fd, &data, sizeof(struct lsm303dlhc_acc_data_s));
      if (ret != sizeof(struct lsm303dlhc_acc_data_s))
        {
          fprintf(stderr, "Read failed.\n");
          break;
        }

      printf("accel_X: %u, accel_Y: %u, accel_Z: %u \n",
              data.x_axis_acc, data.y_axis_acc, data.z_axis_acc);
      fflush(stdout);

      sleep(3);
    }

  close(fd);

  return 0;
}
