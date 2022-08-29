#include "backend/looped/looped.hpp"
#include "util/globals.hpp"
#include "util/scripts.hpp"
#include "script_local.hpp"
#include "gta_util.hpp"

namespace big {

	static bool busy = false;
	static bool state = false;
	constexpr int values[3] = { 34000 , 21250 , 12750 };

	void looped::recovery_remove_repair_cost() {
		if (busy) return;
		busy = true;

		// Enable
		if (g->recovery.remove_repair_cost && !state) {
			for (int i = 281851; i <= 281853; i++) {
				*script_global(i).as<int*>() = 0;
			}

			state = true;
		}

		//Disable
		if (!g->recovery.remove_repair_cost && state) {
			for (int i = 281851; i <= 281853; i++) {
				*script_global(i).as<int*>() = values[i - 281851];
			}

			state = false;
		}

		busy = false;
	}
}