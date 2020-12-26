#include "common.hpp"
#include "gui.hpp"
#include "imgui.h"
#include "tab_bar/tab_bar.hpp"

namespace big
{
	void gui::render_main_window()
	{
		if (ImGui::Begin("Yimura's Mod Menu"))
		{
			ImGui::BeginTabBar("tabbar");
			tabbar::render_self();
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
}