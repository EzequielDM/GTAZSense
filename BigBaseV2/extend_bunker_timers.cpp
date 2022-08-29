#include "backend/looped/looped.hpp"
#include "util/globals.hpp"
#include "util/scripts.hpp"
#include "script_local.hpp"
#include "gta_util.hpp"

namespace big {
	static bool busy = false;
	static bool state = false;

    std::unordered_map<int, int> moddedValues = {
        {283810, 14400000},
        {283834, 15000000},
        {283836, 15600000},
        {283839, 16200000},
        {283843, 16800000},
        {283845, 17400000},
        {283847, 18000000},
        {283849, 18600000},
        {283855, 19200000},
        {283857, 19800000},
        {283860, 20400000},
        {283862, 21000000},
        {283864, 21600000},
        {283867, 22200000},
        {283878, 22800000},
        {283880, 23400000},
        {283884, 24000000},
        {283886, 24600000},
        {283888, 25200000},
        {283891, 25800000},
    };

    std::unordered_map<int, int> defaultValues = {
        {283810, 1800000},
        {283834, 1800000},
        {283836, 1800000},
        {283839, 1800000},
        {283843, 1800000},
        {283845, 1800000},
        {283847, 1800000},
        {283849, 1800000},
        {283855, 1800000},
        {283857, 1800000},
        {283860, 1800000},
        {283862, 1800000},
        {283864, 1800000},
        {283867, 1800000},
        {283878, 900000},
        {283880, 900000},
        {283884, 1800000},
        {283886, 900000},
        {283888, 900000},
        {283891, 900000},
    };

	void looped::recovery_extend_bunker_timers() {
		if (busy) return;
		busy = true;

		// Enable
		if (g->recovery.extend_bunker_timers && !state) {
            for (const auto& [key, value] : moddedValues) {
                *script_global(key).as<int*>() = value;
            }

            state = true;
		}

		// Disable
		if (!g->recovery.extend_bunker_timers && state) {
            for (const auto& [key, value] : defaultValues) {
                *script_global(key).as<int*>() = value;
            }

            state = false;
		}

		busy = false;
	}
}