#include "backend/looped/looped.hpp"
#include "util/globals.hpp"
#include "util/scripts.hpp"
#include "script_local.hpp"
#include "gta_util.hpp"

namespace big {

	static bool state = false;
	static bool busy = false;
	static int old[196];

	void looped::recovery_casino_loop() {
		if (busy) return;
		busy = true;

		constexpr int hash = RAGE_JOAAT("casino_slots");
		if (!g->recovery.rig_casino) {
			if (state) {
				if (auto casino_thread = gta_util::find_script_thread(hash); casino_thread) {
					for (int i = 1; i <= 195; i++) {
						auto local1354 = script_local(casino_thread, 1354).at(1);
						int break_value = *local1354.at(i).as<int*>();
						if (break_value != 64) {
							*local1354.at(i).as<int*>() = old[i];
						}
					}

					state = false;
				}
			}
			busy = false;
			return;
		}
		
		if (!scripts::is_loaded(hash)) {
			busy = false;
			return;
		}

		if (scripts::is_running(hash) && !state) {
			if (auto casino_thread = gta_util::find_script_thread(hash); casino_thread) {
				for (int i = 1; i <= 195; i++) {
					auto local1354 = script_local(casino_thread, 1354).at(1);
					int break_value = *local1354.at(i).as<int*>();
					if (break_value != 64) {
						old[i] = break_value;
						*local1354.at(i).as<int*>() = 6;
					}
				}

				state = true;
			}
		}

		busy = false;
	}
}