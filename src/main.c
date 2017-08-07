#include <genesis.h>
#include "../res/gfx.h"

fix32 groundSpeed = 0;
fix32 backgroundSpeed = 0;

int main(void)
{
    SYS_disableInts();

    VDP_setScreenWidth320();

    VDP_setPaletteColors(0, (u16*) palette_black, 64);

    VDP_drawImageEx(PLAN_A, &ground_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX), 0, 26, FALSE, TRUE);
    VDP_drawImageEx(PLAN_B, &clouds_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX + ground_image.tileset->numTile), 0, 10, FALSE, TRUE);

    SYS_enableInts();

    VDP_setPalette(PAL0, ground_image.palette->data);

    while (1) {
        VDP_setHorizontalScroll(PLAN_A, fix32ToInt(groundSpeed));
        VDP_setHorizontalScroll(PLAN_B, fix32ToInt(backgroundSpeed));

        groundSpeed -= FIX32(3.5);
        backgroundSpeed -= FIX32(0.5);
        VDP_waitVSync();
    }

    return 0;
}