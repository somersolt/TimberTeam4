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
	NONE = -1, SCENE_TITLE, SCENE_MOD_SELECT, SCENE_GAME, COUNT,
}; 
//  SCENE_DEV1 => SCENE_TITLE , SCENE_DEV2 => SCENE_MOD_SELECT

enum class CharacterID
{
	Character1, Character2, Character3, Character4,
};

enum class GameMod
{
	SoloMod, BattleMod,
};