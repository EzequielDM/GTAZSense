#include "backend/looped/looped.hpp"
#include "util/globals.hpp"
#include "util/scripts.hpp"
#include "script_local.hpp"
#include "gta_util.hpp"

namespace big {
	static bool busy = false;

	void looped::system_kick_nonfriends() {
		

		busy = false;
	}
}