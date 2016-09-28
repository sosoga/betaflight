/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <platform.h>
#include "build/build_config.h"

#include "drivers/system.h"
#include "drivers/gyro_sync.h"

volatile bool gyroDataReady = false;

uint32_t gyroIntSignalledAt = 0;
int32_t gyroIntSignalDelta = 0;

void gyroSyncIntHandler(void)
{
    gyroDataReady = true;

    uint32_t now = micros();
    gyroIntSignalDelta = now - gyroIntSignalledAt;

    gyroIntSignalledAt = now;
}

bool gyroSyncIsDataReady(void)
{
    if (gyroDataReady) {
        gyroDataReady = false;
        return true;
    }

    return false;
}
