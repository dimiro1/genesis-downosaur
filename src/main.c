#include <genesis.h>
#include "../res/gfx.h"
#include "../res/palette.h"
#include "../res/sprites.h"

static void Game_updateHorizontalScrolling();

Sprite *rex;
fix32 groundSpeed = 0;
fix32 backgroundSpeed = 0;

int main(void)
{
    SYS_disableInts();

    VDP_setScreenWidth320();

    // Initialize Sprite engine
    SPR_init(16, 256, 256);

    VDP_setPalette(PAL0, game_palette.data);

    // Load Background
    VDP_drawImageEx(PLAN_A, &ground_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX), 0, 26, FALSE, TRUE);
    VDP_drawImageEx(PLAN_B, &clouds_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX + ground_image.tileset->numTile), 0, 10, FALSE, TRUE);

    SYS_enableInts();

    // Load Rex Sprite
    rex = SPR_addSprite(&rex_sprite, fix32ToInt(FIX32(15)), fix32ToInt(FIX32(170)), TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    SPR_setAnim(rex, 1);

    SPR_update();

    while (1) {
        VDP_setHorizontalScroll(PLAN_A, fix32ToInt(groundSpeed));
        VDP_setHorizontalScroll(PLAN_B, fix32ToInt(backgroundSpeed));

        Game_updateHorizontalScrolling();

        SPR_update();

        VDP_waitVSync();
    }

    return 0;
}

static void Game_updateHorizontalScrolling()
{
    groundSpeed -= FIX32(4.0);
    backgroundSpeed -= FIX32(0.5);
}