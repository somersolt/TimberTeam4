#pragma once

enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR, ML, MC, MR, BL, BC, BR, CUSTOM,
};

enum class Sides
{
	NONE = -1, LEFT, RIGHT, COUNT
};

enum class SceneIds
{
	NONE = -1, SCENE_TITLE, SCENE_MODE_SELECT, SCENE_CHARACTER_SELECT, SCENE_GAME, SCENE_BATTLE, COUNT,
};

enum class Modes
{
	NONE = -1, SINGLE, MULTI, COUNT
};

enum class Players
{
	NONE = -1, P1, P2, COUNT
};
