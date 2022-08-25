#include "fiber_pool.hpp"
#include "views/view.hpp"
#include "util/entity.hpp"
#include "util/local_player.hpp"
#include "util/globals.hpp"
#include "util/scripts.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"

namespace big {

	void view::recovery() {

		components::title("Recovery options");

		components::small_text("Zeki is the best cheat dev i know i know, keep the cuddos for after you get rich");

		ImGui::Separator();

		components::sub_title("Warehouse");

		components::button("Get crate", [] {
			std::string mpPrefix = local_player::get_mp_prefix();
			int mpSlot;
			local_player::get_active_character_slot(&mpSlot);
			for (int i = 12; i < 16; i++) {
				//STATS::STAT_SET_BOOL_MASKED(rage::joaat(mpPrefix + "FIXERPSTAT_BOOL1"), true, i, true);
			}
			});

		components::button("Remove cooldown", [] {
			globals::removeCargoCooldown();
		});

		ImGui::Text("Current value: %d", *script_global(277988).as<int*>());

		ImGui::Separator();

		components::sub_title("Nightclub");

		components::button("Max popularity", [] {
			std::string mpPlayer = local_player::get_mp_prefix();
			STATS::STAT_SET_INT(rage::joaat(mpPlayer + "CLUB_POPULARITY"), 1000, true);
		});

		ImGui::Separator();

		components::sub_title("Casino");

		ImGui::Checkbox("Rig slot machines", &g->recovery.rig_casino);
	}
}