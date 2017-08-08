/*
 * TODO
 *
 * Read Joypad
 * Rex Jump
 * Add scores
 * Add Cactus
 * Add Pterodactyl
 * Handle colisions
 * Game States (Just loaded, running, game over, Pre load with credits)
 * Sega Logo
 * Increase difficult
 * Add sounds
 * Cleanup the code
 */

#include <genesis.h>

#include "gfx.h"
#include "palette.h"
#include "sprites.h"

/**
 * @brief Responsible to update all animations on screen
 */
static void Game_updateAnimations();

/**
 * @brief Responsible to update the horizontal game scrolling
 */
static void Game_updateHorizontalScrolling();

/**
 * @brief All the possible rex states
 */
enum RexState {
	REX_STATE_IDLE = 0,
	REX_STATE_JUMPING = 0,
	REX_STATE_RUNNING,
	REX_STATE_DEAD,
} RexState;

/**
 * @brief Hold structures related to player/rex
 */
struct Rex {
	enum RexState state;
	Sprite* sprite;
};

// Global variables
struct Rex rex;
fix32 groundSpeed = 0;
fix32 backgroundSpeed = 0;

int main(void)
{
	// Initialize Mega Drive

	// disable interruptions
	SYS_disableInts();

	// Screen Width
	VDP_setScreenWidth320();

	// Sprite engine
	SPR_init(16, 256, 256);

	// Load the palette
	VDP_setPalette(PAL0, game_palette.data);

	// Load Background
	VDP_drawImageEx(PLAN_A, &ground_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX), 0, 26, FALSE, TRUE);
	VDP_drawImageEx(PLAN_B, &clouds_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX + ground_image.tileset->numTile), 0, 10, FALSE, TRUE);

	// Re enable interruptions
	SYS_enableInts();

	// Load Rex Sprite
	rex.sprite = SPR_addSprite(&rex_sprite, fix32ToInt(FIX32(15)), fix32ToInt(FIX32(170)), TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
	rex.state = REX_STATE_RUNNING;
	SPR_setAnim(rex.sprite, rex.state);
	SPR_update();

	while (1) {
		// Parallax Effect
		VDP_setHorizontalScroll(PLAN_A, fix32ToInt(groundSpeed));
		VDP_setHorizontalScroll(PLAN_B, fix32ToInt(backgroundSpeed));

		Game_updateAnimations();
		Game_updateHorizontalScrolling();

		SPR_update();
		VDP_waitVSync();
	}

	return 0;
}

static void Game_updateAnimations()
{
	SPR_setAnim(rex.sprite, rex.state);
}

static void Game_updateHorizontalScrolling()
{
	groundSpeed -= FIX32(4.0);
	backgroundSpeed -= FIX32(0.5);
}