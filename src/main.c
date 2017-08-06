#include <genesis.h>
#include "../res/gfx.h"

int main(void)
{
    u16 palette[64];

    SYS_disableInts();

    VDP_setPaletteColors(0, (u16*) palette_black, 64);

    VDP_drawImageEx(PLAN_B, &bgb_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX), 0, 0, FALSE, TRUE);
    VDP_drawImageEx(PLAN_A, &bga_image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, TILE_USERINDEX + bgb_image.tileset->numTile), 0, 0, FALSE, TRUE);
    VDP_drawText("Hello World", 15, 12);

    SYS_enableInts();

    memcpy(&palette[0], bgb_image.palette->data, 16 * 2);
    memcpy(&palette[16], bga_image.palette->data, 16 * 2);

    VDP_fadeIn(0, (4 * 16) - 1, palette, 20, FALSE);

    while (1) {
        VDP_waitVSync();
    }

    return 0;
}