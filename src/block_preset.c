#include "definition.h"
Block block_preset(int type) {
	Preset presets[] = {
		{2, 2, {{1, 1}, {1, 1}}},
		{1, 3, {{1}, {1}, {1}}}};
	return (Block){presets[type], (Vector2){0,0}, GREEN};
}