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
			ImGui::SetTooltip("Removes cooldowns from both buying and selling. Don't do more than 30 in an hour, you'll get banned\nINFO! Enable before making a delivery");

		ImGui::Checkbox("Remove repair cost", &g->recovery.remove_repair_cost);

		ImGui::Separator();

		components::sub_title("Bunker");

		ImGui::Text("Current value: %f", *script_global(283698).as<float*>());

		static char bunker_sell_value[20];
		components::input_text_with_hint("Sell value", 
			"Max 2.5M otherwise you'll get transaction error.\nWARNING! Doing this repeatedly will result in a ban",
			bunker_sell_value, sizeof(bunker_sell_value),
			ImGuiInputTextFlags_AutoSelectAll,
			[] {
				std::string base = std::string(value);
				int amount;
				try
				{
					amount = std::stoi(base);
				}
				catch (const std::invalid_argument&)
				{
					LOG(WARNING) << "Invalid value provided. Value is not a number. BUNKER VAL. VAL: " << base;
				}

				*script_global(283698).as<float*>() = (float)amount;
				*script_global(283699).as<float*>() = (float)amount;
			});

		ImGui::Checkbox("Extend bunker delivery times", &g->recovery.extend_bunker_timers);

		ImGui::Checkbox("Reduce bunker supply cost", &g->recovery.reduce_bunker_supply_cost);

		ImGui::Separator();

		components::sub_title("Nightclub");

		components::button("Max popularity", [] {
			std::string mpPlayer = local_player::get_mp_prefix();
			STATS::STAT_SET_INT(rage::joaat(mpPlayer + "CLUB_POPULARITY"), 1000, true);
		});

		if(ImGui::TreeNode("Nightclub values")) {
			ImGui::Text("Current value: %d", *script_global(286554).as<int*>());
			static char nightclub_sporting_goods_value[20];
			components::input_text_with_hint("Sporting Goods value",
				"WARNING! Keep it low, this feature wasn't thoroughly tested.",
				nightclub_sporting_goods_value, sizeof(nightclub_sporting_goods_value),
				ImGuiInputTextFlags_AutoSelectAll,
				[] {
					std::string base = std::string(value);
					int amount;
					try
					{
						amount = std::stoi(base);
					}
					catch (const std::invalid_argument&)
					{
						LOG(WARNING) << "Invalid value provided. Value is not a number. NC SG VALUE. VAL: " << base;
					}

					*script_global(286554).as<int*>() = amount;
				});

			ImGui::Text("Current value: %d", *script_global(286555).as<int*>());
			static char nightclub_sa_imports_value[20];
			components::input_text_with_hint("S.A. Imports value",
				"WARNING! Keep it low, this feature wasn't thoroughly tested.",
				nightclub_sa_imports_value, sizeof(nightclub_sa_imports_value),
				ImGuiInputTextFlags_AutoSelectAll,
				[] {
					std::string base = std::string(value);
					int amount;
					try
					{
						amount = std::stoi(base);
					}
					catch (const std::invalid_argument&)
					{
						LOG(WARNING) << "Invalid value provided. Value is not a number. NC SAI VALUE. VAL: " << base;
					}

					*script_global(286555).as<int*>() = amount;
				});

			ImGui::Text("Current value: %d", *script_global(286556).as<int*>());
			static char nightclub_pharmaceutics_value[20];
			components::input_text_with_hint("Pharmaceutics value",
				"WARNING! Keep it low, this feature wasn't thoroughly tested.",
				nightclub_pharmaceutics_value, sizeof(nightclub_pharmaceutics_value),
				ImGuiInputTextFlags_AutoSelectAll,
				[] {
					std::string base = std::string(value);
					int amount;
					try
					{
						amount = std::stoi(base);
					}
					catch (const std::invalid_argument&)
					{
						LOG(WARNING) << "Invalid value provided. Value is not a number. NC PHARMA VALUE. VAL: " << base;
					}

					*script_global(286556).as<int*>() = amount;
				});

			ImGui::Text("Current value: %d", *script_global(286557).as<int*>());
			static char nightclub_organic_product_value[20];
			components::input_text_with_hint("Organic Products value",
				"WARNING! Keep it low, this feature wasn't thoroughly tested. weed :woozy:",
				nightclub_organic_product_value, sizeof(nightclub_organic_product_value),
				ImGuiInputTextFlags_AutoSelectAll,
				[] {
					std::string base = std::string(value);
					int amount;
					try
					{
						amount = std::stoi(base);
					}
					catch (const std::invalid_argument&)
					{
						LOG(WARNING) << "Invalid value provided. Value is not a number. NC OP VALUE. VAL: " << base;
					}

					*script_global(286557).as<int*>() = amount;
				});

			ImGui::Text("Current value: %d", *script_global(286558).as<int*>());
			static char nightclub_print_n_copy_value[20];
			components::input_text_with_hint("Print and Copy value",
				"WARNING! Keep it low, this feature wasn't thoroughly tested.",
				nightclub_print_n_copy_value, sizeof(nightclub_print_n_copy_value),
				ImGuiInputTextFlags_AutoSelectAll,
				[] {
					std::string base = std::string(value);
					int amount;
					try
					{
						amount = std::stoi(base);
					}
					catch (const std::invalid_argument&)
					{
						LOG(WARNING) << "Invalid value provided. Value is not a number. NC P&C VALUE. VAL: " << base;
					}

					*script_global(286558).as<int*>() = amount;
				});

			ImGui::Text("Current value: %d", *script_global(286559).as<int*>());
			static char nightclub_cash_creation_value[20];
			components::input_text_with_hint("Cash Creation value",
				"WARNING! Keep it low, this feature wasn't thoroughly tested.",
				nightclub_cash_creation_value, sizeof(nightclub_cash_creation_value),
				ImGuiInputTextFlags_AutoSelectAll,
				[] {
					std::string base = std::string(value);
					int amount;
					try
					{
						amount = std::stoi(base);
					}
					catch (const std::invalid_argument&)
					{
						LOG(WARNING) << "Invalid value provided. Value is not a number. NC CC VALUE. VAL: " << base;
					}

					*script_global(286559).as<int*>() = amount;
				});

			ImGui::Text("Current value: %d", *script_global(286560).as<int*>());
			static char nightclub_cargo_shipments_value[20];
			components::input_text_with_hint("Cargo and Shipments value",
				"WARNING! Keep it low, this feature wasn't thoroughly tested.",
				nightclub_cargo_shipments_value, sizeof(nightclub_cargo_shipments_value),
				ImGuiInputTextFlags_AutoSelectAll,
				[] {
					std::string base = std::string(value);
					int amount;
					try
					{
						amount = std::stoi(base);
					}
					catch (const std::invalid_argument&)
					{
						LOG(WARNING) << "Invalid value provided. Value is not a number. NC CS VALUE. VAL: " << base;
					}

					*script_global(286560).as<int*>() = amount;
				});

			ImGui::TreePop();
		}

		ImGui::Separator();

		components::sub_title("Casino");

		ImGui::Checkbox("Rig slot machines", &g->recovery.rig_casino);

		ImGui::Checkbox("Rig blackjack", &g->recovery.rig_blackjack);
	}
}