#include "backend/looped/looped.hpp"
#include "util/globals.hpp"
#include "util/scripts.hpp"
#include "script_local.hpp"
#include "gta_util.hpp"

namespace big {
	static bool busy = false;
	static bool state = false;

	void looped::recovery_reduce_bunker_supply_cost() {
		if (busy) return;
		busy = true;

		// Enable
		if (g->recovery.reduce_bunker_supply_cost && !state) {
			*script_global(283744).as<int*>() = 1000;
			*script_global(283745).as<int*>() = 1000;

			state = true;
		}

		//Disable
		if (!g->recovery.reduce_bunker_supply_cost && state) {
			*script_global(283744).as<int*>() = 15000;
			*script_global(283745).as<int*>() = 15000;

			state = false;
		}

		busy = false;
	}
}