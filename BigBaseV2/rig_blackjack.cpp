#include "backend/looped/looped.hpp"
#include "util/globals.hpp"
#include "util/scripts.hpp"
#include "script_local.hpp"
#include "gta_util.hpp"

namespace big {
	static bool busy = false;

	void looped::recovery_rig_blackjack() {
		if (busy) return;
		busy = true;

		// Enable
		if (&g->recovery.rig_blackjack) {
			auto hash = RAGE_JOAAT("BLACKJACK");
			auto thread = gta_util::find_script_thread(hash);
			if (!thread) {
				busy = false; return;
			}
			auto cur_table = script_local(thread, 1782).at(PLAYER::PLAYER_ID(), 8).at(4).as<int*>();
			auto cur_card = script_local(thread, 122).at(1).at(*cur_table, 211);

			if (*cur_table != -1) {
				*cur_card.at(1).as<int*>() = 1;
				*script_local(thread, 2042).as<int*>() = 1;
				*cur_card.at(2).as<int*>() = 0;
				*script_local(thread, 2043).as<int*>() = 0;
				*cur_card.at(4).as<int*>() = 23;
				*script_local(thread, 2044).as<int*>() = 0;
				*cur_card.at(5).as<int*>() = 0;
				*script_local(thread, 2045).as<int*>() = 0;
				*script_local(thread, 2039).at(244).as<int*>() = 0;
				*script_local(thread, 2039).at(246).as<int*>() = 0;
				*script_local(thread, 3626).at(14).as<int*>() = 2500000;
				*script_local(thread, 122).at(1580).at(1).as<int*>() = 0;
			}
		}

		busy = false;
	}
}