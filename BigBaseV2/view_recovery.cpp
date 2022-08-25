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

		ImGui::BeginDisabled();

		components::button("Get crate", [] {
			std::string mpPrefix = local_player::get_mp_prefix();
			int mpSlot;
			local_player::get_active_character_slot(&mpSlot);
			for (int i = 12; i < 16; i++) {
				//STATS::STAT_SET_BOOL_MASKED(rage::joaat(mpPrefix + "FIXERPSTAT_BOOL1"), true, i, true);
			}
			});

		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("This is currently under research and development.");

		ImGui::EndDisabled();
		ImGui::SameLine();
		components::button("Remove cooldown", [] {
			globals::removeCargoCooldown();
		});

		ImGui::Text("Current value: %d", *script_global(277988).as<int*>());

		g_fiber_pool->queue_job([] {
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		});
		static char value[20];
		components::input_text_with_hint("New value", "10000 base/9M Max", value, sizeof(value), ImGuiInputTextFlags_AutoSelectAll, [] {
			std::string base = std::string(value);
			int amount;
			try
			{
				amount = std::stoi(base);
			}
			catch (const std::invalid_argument&)
			{
				LOG(WARNING) << "Invalid value provided. Value is not a number. CEO CRATE. VAL: " << base;
			}

			for (int i = 1; i <= 21; i++) {
				int floored = (int)std::floor(amount / i);
				*script_global(277987 + i).as<int*>() = floored;
			}
		});

		ImGui::Separator();

		components::sub_title("Vehicle Import/Export");

		ImGui::Checkbox("Max all ranges", &g->recovery.max_vehicle_sale);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Sets all ranges of vehicles (low/medium/top) to the maximum possible sale value.\nWARNING! Do not tamper with these values further, you'll get banned");

		ImGui::Checkbox("Remove cooldowns", &g->recovery.remove_vehicle_cooldown);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Removes cooldowns from both buying and selling. Don't do more than 30 in an hour, you'll get banned");

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