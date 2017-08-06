#include <genesis.h>
#include "../res/gfx.h"

int main(void)
{
    SYS_disableInts();

    VDP_setPaletteColors(0, (u16*) palette_green, 64);

    VDP_drawImageEx(PLAN_A, &horizon_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX), 0, 26, FALSE, TRUE);
    VDP_drawText("Hello World", 15, 12);

    SYS_enableInts();

    VDP_setPalette(PAL0, horizon_image.palette->data);

    fix32 i = 0;
    while (1) {
        VDP_setHorizontalScroll(PLAN_A, fix32ToInt(i));
        i -= FIX32(1.5);
        VDP_waitVSync();
    }

    return 0;
}