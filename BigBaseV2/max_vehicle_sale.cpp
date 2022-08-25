#include "backend/looped/looped.hpp"
#include "util/globals.hpp"
#include "util/scripts.hpp"
#include "script_local.hpp"
#include "gta_util.hpp"

namespace big {

	static bool state = false;
	static bool busy = false;

	void looped::recovery_max_vehicle_sale() {
		if (busy) return;
		busy = true;

		if (g->recovery.max_vehicle_sale) {
			if (!state) {
				for (int i = 0; i < 3; i++) {
					*script_global(281602 + i).as<int*>() = 155000;
				}
				*script_global(281606).as<float*>() = 0.f;
				*script_global(281607).as<float*>() = 0.f;

				state = true;
			}
		} else if (state) {
			*script_global(281602).as<int*>() = 40000;
			*script_global(281603).as<int*>() = 25000;
			*script_global(281604).as<int*>() = 15000;
			*script_global(281606).as<float*>() = 0.25f;
			*script_global(281607).as<float*>() = 0.5f;

			state = false;
		}

		busy = false;
	}
}