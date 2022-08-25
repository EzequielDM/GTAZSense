#include "backend/looped/looped.hpp"
#include "util/globals.hpp"
#include "util/scripts.hpp"
#include "script_local.hpp"
#include "gta_util.hpp"

namespace big {
	static bool state = false;
	static bool busy = false;
	static bool first_tick = false;

	void looped::recovery_remove_vehicle_cooldown() {		
		if (busy) return;
		busy = true;

		// Enable
		if (g->recovery.remove_vehicle_cooldown) {
			// Check if not enabled already
			if (!state) {
				for (int i = 281872; i <= 281875; i++) {
					if (!first_tick) {
						*script_global(i).as<int*>() = 0;
					}
					else {
						*script_global(i).as<int*>() = 1;
					}
				}
				first_tick = !first_tick;
				if (!first_tick) {
					*script_global(281504).as<int*>() = 1;
					state = true;
				}
			}
		}
		// Disable
		else if (state) {
			*script_global(281504).as<int*>() = 1;
			int values[5] = { 180000 , 1200000 , 1680000 , 2340000 , 2880000 };
			for (int i = 0; i < 4; i++) {
				*script_global(281872 + i).as<int*>() = values[i];
			}
			state = false;
		}

		busy = false;
	}
}