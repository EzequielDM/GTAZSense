#include "views/view.hpp"

namespace big
{
	void view::heading()
	{
		ImGui::SetNextWindowSize({ 300.f, 80.f });
		ImGui::SetNextWindowPos({ 10.f, 10.f });
		if (ImGui::Begin("menu_heading", nullptr, window_flags | ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::BeginGroup();
			ImGui::Text("Welcome");
			std::string player_name = g_local_player == nullptr || g_local_player->m_player_info == nullptr ? "unknown" : g_local_player->m_player_info->m_net_player_data.m_name;
			ImGui::PushStyleColor(ImGuiCol_Text, (player_name == "NinjaOficial_") ? ImVec4(1.0f, 0.271f, 0.271f, 1.f) : ImVec4(0.172f, 0.380f, 0.909f, 1.f));
			std::string display = player_name == "NinjaOficial_" ? player_name + " [DEV]" : player_name;
			ImGui::Text(display.c_str());
			ImGui::PopStyleColor();
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::SetCursorPos({ 300.f - ImGui::CalcTextSize("Unload").x - ImGui::GetStyle().ItemSpacing.x, ImGui::GetStyle().WindowPadding.y / 2 + ImGui::GetStyle().ItemSpacing.y + (ImGui::CalcTextSize("W").y / 2) });
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.69f, 0.29f, 0.29f, 1.00f));
			if (components::nav_button("Unload"))
			{
				g_running = false;
			}
			ImGui::PopStyleColor();
		}
	}
}
