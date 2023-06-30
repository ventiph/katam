#include "code_08128D48.h"
#include "task.h"
#include "pause_fade.h"
#include "palette.h"
#include "random.h"
#include "functions.h"
#include "constants/languages.h"

void sub_08128DB0(void);
void sub_08128E8C(void);

// apply a set of tilesets during animation (?)
struct Task *sub_08128D48(const struct Unk_08128D48_0 *a1) {
    struct Task *t = TaskCreate(sub_08128DB0, sizeof(struct Unk_08128D48), 0x100, TASK_USE_IWRAM, NULL);
    struct Unk_08128D48 *var = TaskGetStructPtr(t);

    var->frames = a1->frames;
    var->dstVram = VRAM + a1->dstVramOffset;
    var->numFrames = a1->numFrames;
    var->sizeTiles = 0x20 * a1->numTiles;
    var->currentTilesetIndex = 0;
    var->delayCounter = 0xFF;
    return t;
}

void sub_08128DB0(void) {
    struct Unk_08128D48 *var = TaskGetStructPtr(gCurTask);
    const struct Unk_08128D48_0_4 *p = &var->frames[var->currentTilesetIndex];

    if (var->delayCounter < p->delay)
        ++var->delayCounter;
    else {
        ++var->currentTilesetIndex;
        var->delayCounter = 0;
        if (var->currentTilesetIndex >= var->numFrames)
            var->currentTilesetIndex = 0;
        ++var; --var;
        p = &var->frames[var->currentTilesetIndex];
        CpuCopy32((void *)VRAM + p->srcVramOffset, (void *)var->dstVram, var->sizeTiles);
    }
}

// apply a set of palettes during animation (?)
struct Task *sub_08128E28(const struct Unk_08128E28_0 *a1) {
    struct Task *t = TaskCreate(sub_08128E8C, sizeof(struct Unk_08128E28), 0x100, TASK_USE_IWRAM, NULL);
    struct Unk_08128E28 *var = TaskGetStructPtr(t);

    var->data = a1->data;
    var->currentDataOffset = 0;
    var->paletteOffset = a1->paletteOffset;
    var->paletteSize = a1->paletteSize;
    var->numPalettes = a1->numPalettes;
    var->currentPaletteIndex = 0;
    var->delayCounter = 0xFF;
    return t;
}

void sub_08128E8C(void) {
    struct Unk_08128E28 *var = TaskGetStructPtr(gCurTask);
    const u16 *p = &var->data[var->currentDataOffset];

    if (var->delayCounter < p[0])
        ++var->delayCounter;
    else {
        ++var->currentPaletteIndex;
        var->delayCounter = 0;
        var->currentDataOffset += var->paletteSize + 1;
        if (var->currentPaletteIndex >= var->numPalettes) {
            var->currentPaletteIndex = 0;
            var->currentDataOffset = 0;
        }
        ++var; --var;
        p = &var->data[var->currentDataOffset];
        if (gUnk_03002440 & 0x10000)
            sub_08158334(p+1, var->paletteOffset, var->paletteSize);
        else {
            DmaCopy16(3, p+1, gBgPalette + var->paletteOffset, var->paletteSize * sizeof(u16));
            gUnk_03002440 |= 1;
        }
    }
}

void sub_081295A0(void);
void sub_081297F8(struct Unk_08128F44 *);
void sub_081298B4(void);
void sub_08129A6C(void);
void sub_08129C34(void);
void sub_08129F28(void);
void sub_0812A344(s32 *, struct Unk_08128F44_4 *);
s32 *sub_0812A388(struct Unk_08128F44_4 *);
void sub_0812A39C(void);
void sub_0812A8F0(void);
void sub_0812AAE0(struct Unk_0812A77C *);
void sub_0812B204(void);
void sub_0812B2F8(void);
void sub_0812B418(void);
void sub_0812B63C(void);
void sub_0812BEE0(void);
void sub_0812C168(struct Unk_0812A77C *);
void sub_0812C29C(void);
void sub_0812C490(struct Unk_0812A77C *);
void sub_0812C528(struct Unk_0812A77C_40 *, u8);
void sub_0812C63C(void);
void sub_0812C814(void);
void sub_0812CA84(void);
void sub_0812CBDC(void);
void sub_0812CDD4(struct Unk_0812A77C *);
void sub_0812CED8(struct Unk_0812A77C_40 *, u8);
void sub_0812CF80(struct Unk_0812A77C_40 *, struct Unk_0812A77C *);
void sub_0812D060(void);
void sub_0812D124(s16, s16, struct Unk_0812A77C_40 *);
struct Task *sub_0812D1EC(struct Unk_0812A77C_40 *, u8);
void sub_0812D3AC(void);
struct Task *sub_0812D4F4(void);
void sub_0812D988(void);
void sub_0812DB2C(void);
struct Task *sub_0812DBB4(s16, s16, s16, s16, bool8);
void sub_0812DC90(void);
void sub_0812DF14(void);
void sub_0812DFD4(void);
void sub_0812E0C8(u16, u16, u8);
void sub_0812E194(u16, u16, s16);
void sub_0812E468(struct Unk_0812A77C *);
void sub_0812E51C(void);
void sub_0812E588(struct Task *);
void sub_0812E604(struct Unk_0812A77C_40 *);
void sub_0812E640(void);
void nullsub_31(struct Task *);
bool32 sub_0812E6A8(struct Unk_0812D4F4 *);
bool32 sub_0812E6C8(struct Unk_0812DBB4 *);
void nullsub_32(struct Task *);
void sub_0812E6E4(u8);
void sub_0812E764(struct Sprite *, u8);
void sub_0812E7A0(void);
void sub_0812E818(struct Unk_0812A77C_40 *);
void sub_0812E9CC(void);
void sub_0812EC54(void);
void sub_0812ED78(s32);
void sub_0812EF3C(void);
struct Task *sub_0812EFB4(void);
struct Task *sub_0812EFFC(u32, u8);

extern const u8 gUnk_08363AA0[];
extern const struct Unk_02021590 gUnk_08364ACC[][6];
extern const s8 gUnk_08364B5C[][60];
extern const s8 gUnk_08364C4C[];
extern const s8 gUnk_08364C88[];
extern const s16 gUnk_08364C9A[][6];
extern const s8 gUnk_08364CCA[];
extern const u8 gUnk_08364CD2[][4];
extern const struct Unk_02021590 gUnk_08364CE4[][7];
extern const struct Unk_02021590 gUnk_08364D8C[][6];
extern const struct Unk_02021590 gUnk_08364E1C[][12];
extern const struct Unk_02021590 gUnk_08364F3C[][4];
extern const struct Unk_02021590 gUnk_08364F9C[][2];
extern const struct Unk_02021590 gUnk_08364FCC[];
extern const s32 gUnk_08364FE4[];
extern const struct Unk_02021590 gUnk_08364FF4[][4];
extern const struct Unk_02021590 gUnk_08365054[][4];
extern const struct Unk_02021590 gUnk_083650B4[][4];
extern const u8 gUnk_08365114[][16];
extern const u16 gUnk_08365144[][4];
extern const u16 gUnk_0836515C[];
extern const u16 gUnk_0836535C[];
extern const u32 gUnk_08365380[];
extern const u32 gUnk_0836C654[];
extern const u32 gUnk_0836CCDC[];
extern const u32 gUnk_0836D33C[];
extern const u32 gUnk_0836D9F0[];
extern const u32 gUnk_0836E034[];
extern const u32 gUnk_0836E66C[];
extern const u16 gUnk_0836ECC8[]; // works as extern const u16 gUnk_0836ECC8[][0x20][2];
extern const u32 gUnk_0836EEC8[0x200];
extern const u32 gUnk_0836F6C8[0x200];
extern const u32 gUnk_0836FEC8[0x200];
extern const u32 gUnk_083706C8[0x200];
extern const u32 gUnk_08370EC8[0x200];
extern const u32 gUnk_083716C8[0x200];
extern const struct Unk_08128D48_0 gUnk_083723C8;
extern const struct Unk_08128D48_0 gUnk_083723D4;
extern const struct Unk_08128D48_0 gUnk_083723E0;
extern const struct Unk_08128D48_0 gUnk_083723EC;
extern const struct Unk_08128D48_0 gUnk_083723F8;
extern const struct Unk_08128D48_0 gUnk_08372404;
extern const struct Unk_08128D48_0 gUnk_08372410;
extern const struct Unk_08128D48_0 gUnk_0837241C;
extern const struct Unk_08128D48_0 gUnk_08372428;
extern const struct Unk_08128D48_0 gUnk_08372434;
extern const struct Unk_02021590 gUnk_08372440[][16];
extern const struct Unk_02021590 gUnk_083725C0[][4];
extern const s8 gUnk_08372620[];

extern const u32 *const gUnk_08D61B3C[];

struct Task *sub_08128F44(const struct Unk_02021590 *a1, u8 a2, u8 a3, s16 a4, s16 a5, u8 a6) {
    struct Task *t = TaskCreate(sub_0812A39C, sizeof(struct Unk_08128F44), 0x100, TASK_USE_IWRAM, NULL);
    struct Unk_08128F44 *tmp = TaskGetStructPtr(t), *var = tmp;
#ifndef NONMATCHING
    register struct Unk_08128F44_4 *var1 asm("r6"), *var2 asm("r4");
#else
    struct Unk_08128F44_4 *var1, *var2;
#endif

    var->unk0 = a1;
    var->unk2AC = 0x10;
    var->unk2AD = 0;
    var->unk2AE = 0;
    var->unk2B0 = a2;
    var->unk2B1 = a3;
    var->unk2B2 = 1;
    var->unk2B3 = 0;
    var->unk2B4 = a4;
    var->unk2B6 = a5;
    if (a6) var->unk2AC |= 0x80;
    if (gUnk_03002440 & 0x20000)
        sub_0815828C(&gUnk_082DE69C[0x10 * var->unk2B2], 0x10 * var->unk2B0, 0x10);
    else {
        DmaCopy16(3, &gUnk_082DE69C[0x10 * var->unk2B2], &gObjPalette[0x10 * var->unk2B0], 0x10 * sizeof(u16));
        gUnk_03002440 |= 2;
    }
    if (gUnk_03002440 & 0x20000)
        sub_0815828C(gUnk_082DE69C, 0x10 * var->unk2B1, 0x10);
    else {
        DmaCopy16(3, gUnk_082DE69C, &gObjPalette[0x10 * var->unk2B1], 0x10 * sizeof(u16));
        gUnk_03002440 |= 2;
    }
    CpuFill32(0, &var->unk4[0][0], sizeof(struct Unk_08128F44_4));
    var->unk4[0][0].unk0.tilesVram = 0x6010000;
    var->unk4[0][0].unk0.unk14 = 0x280;
    var->unk4[0][0].unk0.animId = var->unk0[0].animId;
    var->unk4[0][0].unk0.variant = var->unk0[0].variant;
    var->unk4[0][0].unk0.unk16 = 0;
    var->unk4[0][0].unk0.unk1B = 0xFF;
    var->unk4[0][0].unk0.unk1C = 0x10;
    var->unk4[0][0].unk0.palId = var->unk2B0;
    var->unk4[0][0].unk0.x = ({var->unk2B4 + 0;});
    var->unk4[0][0].unk0.y = ({var->unk2B6 + 0;});
    var->unk4[0][0].unk0.unk8 = 0xC0000;
    var->unk4[0][0].unk28 = 4 * var->unk2B4;
    var->unk4[0][0].unk2C = 4 * var->unk2B6;
    var->unk4[0][0].unk30 = 0;
    var->unk4[0][0].unk32 = 0;
    var->unk4[0][0].unk34 = 0x10;
    var->unk4[0][0].unk36 = 0;
    var->unk4[0][0].unk38 = NULL;
    var->unk4[0][0].unk3C = NULL;
    var->unk4[0][0].unk40 = NULL;
    CpuFill32(0, &var->unk4[1][0], sizeof(struct Unk_08128F44_4));
    var->unk4[1][0].unk0.tilesVram = 0x6010000;
    var->unk4[1][0].unk0.unk14 = 0x280;
    var->unk4[1][0].unk0.animId = var->unk0[1].animId;
    var->unk4[1][0].unk0.variant = var->unk0[1].variant;
    var->unk4[1][0].unk0.unk16 = 0;
    var->unk4[1][0].unk0.unk1B = 0xFF;
    var->unk4[1][0].unk0.unk1C = 0x10;
    var->unk4[1][0].unk0.palId = var->unk2B0;
    var->unk4[1][0].unk0.x = 0;
    var->unk4[1][0].unk0.y = 0;
    var->unk4[1][0].unk0.unk8 = 0xC0000;
    var->unk4[1][0].unk28 = 0;
    var->unk4[1][0].unk2C = 0;
    var->unk4[1][0].unk30 = 0;
    var->unk4[1][0].unk32 = 0;
    var->unk4[1][0].unk34 = 0x10;
    var->unk4[1][0].unk36 = 0;
    var->unk4[1][0].unk38 = NULL;
    var->unk4[1][0].unk3C = NULL;
    var->unk4[1][0].unk40 = NULL;
    var->unk4[0][0].unk40 = &var->unk4[1][0];
    var->unk4[1][0].unk3C = &var->unk4[0][0];
    var->unk4[1][0].unk34 &= ~0x10;
    CpuFill32(0, var1 = &var->unk4[2][0], sizeof(struct Unk_08128F44_4));
    var1->unk0.tilesVram = 0x6010000;
    var1->unk0.unk14 = 0x2C0;
    var1->unk0.animId = var->unk0[0].animId;
    var1->unk0.variant = var->unk0[0].variant;
    var1->unk0.unk16 = 0;
    var1->unk0.unk1B = 0xFF;
    var1->unk0.unk1C = 0x10;
    var1->unk0.palId = var->unk2B1;
    var1->unk0.x = ({var->unk2B4 + 0x14;});
    var1->unk0.y = ({var->unk2B6 + 0xA;});
    var1->unk0.unk8 = 0xC0000;
    var1->unk28 = 4 * (var->unk2B4 + 0x14);
    var1->unk2C = 4 * (var->unk2B6 + 0xA);
    var1->unk30 = 0;
    var1->unk32 = 0;
    var1->unk34 = 0x10;
    var1->unk36 = 0;
    var1->unk38 = NULL;
    var1->unk3C = NULL;
    var1->unk40 = NULL;
    CpuFill32(0, var2 = &var->unk4[3][0], sizeof(struct Unk_08128F44_4));
    var2->unk0.tilesVram = 0x6010000;
    var2->unk0.unk14 = 0x2C0;
    var2->unk0.animId = var->unk0[2].animId;
    var2->unk0.variant = var->unk0[2].variant;
    var2->unk0.unk16 = 0;
    var2->unk0.unk1B = 0xFF;
    var2->unk0.unk1C = 0x10;
    var2->unk0.palId = var->unk2B1;
    var2->unk0.x = 0;
    var2->unk0.y = 0;
    var2->unk0.unk8 = 0xC0000;
    var2->unk28 = 0;
    var2->unk2C = 0;
    var2->unk30 = 0;
    var2->unk32 = 0;
    var2->unk34 = 0x10;
    var2->unk36 = 0;
    var2->unk38 = NULL;
    var2->unk3C = NULL;
    var2->unk40 = NULL;
    var1->unk40 = var2;
    var2->unk3C = var1;
    var2->unk34 &= ~0x10;
    CpuFill32(0, var1 = &var->unk4[4][0], sizeof(struct Unk_08128F44_4));
    var1->unk0.tilesVram = 0x6010000;
    var1->unk0.unk14 = 0x280;
    var1->unk0.animId = var->unk0[0].animId;
    var1->unk0.variant = var->unk0[0].variant;
    var1->unk0.unk16 = 0;
    var1->unk0.unk1B = 0xFF;
    var1->unk0.unk1C = 0x10;
    var1->unk0.palId = var->unk2B0;
    var1->unk0.x = ({var->unk2B4 - 0x14;});
    var1->unk0.y = ({var->unk2B6 - 5;});
    var1->unk0.unk8 = 0xC0000;
    var1->unk28 = 4 * (var->unk2B4 - 0x14);
    var1->unk2C = 4 * (var->unk2B6 - 5);
    var1->unk30 = 0;
    var1->unk32 = 0;
    var1->unk34 = 0x10;
    var1->unk36 = 0;
    var1->unk38 = NULL;
    var1->unk3C = NULL;
    var1->unk40 = NULL;
    CpuFill32(0, var2 = &var->unk4[7][0], sizeof(struct Unk_08128F44_4));
    var2->unk0.tilesVram = 0x6010000;
    var2->unk0.unk14 = 0x280;
    var2->unk0.animId = var->unk0[3].animId;
    var2->unk0.variant = var->unk0[3].variant;
    var2->unk0.unk16 = 0;
    var2->unk0.unk1B = 0xFF;
    var2->unk0.unk1C = 0x10;
    var2->unk0.palId = var->unk2B0;
    var2->unk0.x = 0;
    var2->unk0.y = 0;
    var2->unk0.unk8 = 0xC0000;
    var2->unk28 = 0;
    var2->unk2C = 0;
    var2->unk30 = 0;
    var2->unk32 = 0;
    var2->unk34 = 0x10;
    var2->unk36 = 0;
    var2->unk38 = NULL;
    var2->unk3C = NULL;
    var2->unk40 = NULL;
    var1->unk40 = var2;
    var2->unk3C = var1;
    var2->unk34 &= ~0x10;
    CpuFill32(0, var1 = &var->unk4[5][0], sizeof(struct Unk_08128F44_4));
    var1->unk0.tilesVram = 0x6010000;
    var1->unk0.unk14 = 0x2C0;
    var1->unk0.animId = var->unk0[0].animId;
    var1->unk0.variant = var->unk0[0].variant;
    var1->unk0.unk16 = 0;
    var1->unk0.unk1B = 0xFF;
    var1->unk0.unk1C = 0x10;
    var1->unk0.palId = var->unk2B1;
    var1->unk0.x = ({var->unk2B4 + 0;});
    var1->unk0.y = ({var->unk2B6 + 5;});
    var1->unk0.unk8 = 0xC0000;
    var1->unk28 = 4 * var->unk2B4;
    var1->unk2C = 4 * (var->unk2B6 + 5);
    var1->unk30 = 0;
    var1->unk32 = 0;
    var1->unk34 = 0x10;
    var1->unk36 = 0;
    var1->unk38 = NULL;
    var1->unk3C = NULL;
    var1->unk40 = NULL;
    CpuFill32(0, var2 = &var->unk4[8][0], sizeof(struct Unk_08128F44_4));
    var2->unk0.tilesVram = 0x6010000;
    var2->unk0.unk14 = 0x2C0;
    var2->unk0.animId = var->unk0[4].animId;
    var2->unk0.variant = var->unk0[4].variant;
    var2->unk0.unk16 = 0;
    var2->unk0.unk1B = 0xFF;
    var2->unk0.unk1C = 0x10;
    var2->unk0.palId = var->unk2B1;
    var2->unk0.x = 0;
    var2->unk0.y = 0;
    var2->unk0.unk8 = 0xC0000;
    var2->unk28 = 0;
    var2->unk2C = 0;
    var2->unk30 = 0;
    var2->unk32 = 0;
    var2->unk34 = 0x10;
    var2->unk36 = 0;
    var2->unk38 = NULL;
    var2->unk3C = NULL;
    var2->unk40 = NULL;
    var1->unk40 = var2;
    var2->unk3C = var1;
    var2->unk34 &= ~0x10;
    CpuFill32(0, var1 = &var->unk4[6][0], sizeof(struct Unk_08128F44_4));
    var1->unk0.tilesVram = 0x6010000;
    var1->unk0.unk14 = 0x300;
    var1->unk0.animId = var->unk0[0].animId;
    var1->unk0.variant = var->unk0[0].variant;
    var1->unk0.unk16 = 0;
    var1->unk0.unk1B = 0xFF;
    var1->unk0.unk1C = 0x10;
    var1->unk0.palId = var->unk2B1;
    var1->unk0.x = ({var->unk2B4 + 0x14;});
    var1->unk0.y = ({var->unk2B6 + 0xF;});
    var1->unk0.unk8 = 0xC0000;
    var1->unk28 = 4 * (var->unk2B4 + 0x14);
    var1->unk2C = 4 * (var->unk2B6 + 0xF);
    var1->unk30 = 0;
    var1->unk32 = 0;
    var1->unk34 = 0x10;
    var1->unk36 = 0;
    var1->unk38 = NULL;
    var1->unk3C = NULL;
    var1->unk40 = NULL;
    CpuFill32(0, var2 = &var->unk4[9][0], sizeof(struct Unk_08128F44_4));
    var2->unk0.tilesVram = 0x6010000;
    var2->unk0.unk14 = 0x300;
    var2->unk0.animId = var->unk0[5].animId;
    var2->unk0.variant = var->unk0[5].variant;
    var2->unk0.unk16 = 0;
    var2->unk0.unk1B = 0xFF;
    var2->unk0.unk1C = 0x10;
    var2->unk0.palId = var->unk2B1;
    var2->unk0.x = 0;
    var2->unk0.y = 0;
    var2->unk0.unk8 = 0xC0000;
    var2->unk28 = 0;
    var2->unk2C = 0;
    var2->unk30 = 0;
    var2->unk32 = 0;
    var2->unk34 = 0x10;
    var2->unk36 = 0;
    var2->unk38 = NULL;
    var2->unk3C = NULL;
    var2->unk40 = NULL;
    var1->unk40 = var2;
    var2->unk3C = var1;
    var2->unk34 &= ~0x10;
    return t;
}

void sub_081295A0(void) {
    struct Unk_08128F44 *tmp = TaskGetStructPtr(gCurTask), *var = tmp;
    u16 r2;

    if (var->unk2AC & 1)
        r2 = 0;
    else if (gUnk_0203AD10 & 2)
        r2 = gUnk_020382D0.unk8[1][0];
    else
        r2 = gPressedKeys;
    if (var->unk2AC & 4) {
        if (r2 & 1) {
            if (!(var->unk2AC & 0x80))
                m4aSongNumStart(0x21E);
            var->unk2AC |= 1;
        }
        else if (r2 & 2) {
            if (!(var->unk2AC & 0x80))
                m4aSongNumStart(0x21F);
            var->unk2AC &= ~4;
            var->unk2AC &= ~0x40;
        }
        else if (r2 & 0x40) {
            if (!(var->unk2AC & 0x80))
                m4aSongNumStart(0x21D);
            var->unk2AE = 0;
            gCurTask->main = sub_08129F28;
        }
        else if (r2 & 0x80) {
            if (!(var->unk2AC & 0x80))
                m4aSongNumStart(0x21D);
            var->unk2AE = 0;
            gCurTask->main = sub_08129C34;
        }
    }
    else {
        if (r2 & 1) {
            if (!(var->unk2AC & 0x80)) {
                m4aSongNumStart(0x21E);
                if (var->unk2AD == 0)
                    var->unk2B2 = 1;
                else if (var->unk2AD == 1)
                    var->unk2B2 = 3;
                else
                    var->unk2B2 = 5;
            }
            if (var->unk2AC & 0x10) {
                var->unk2AC |= 4;
                var->unk2AC |= 0x40;
            }
            else {
                var->unk2AC |= 1;
            }
        }
        else if (r2 & 0x40) {
            if (!(var->unk2AC & 0x80))
                m4aSongNumStart(0x21D);
            var->unk2AE = 0;
            gCurTask->main = sub_081298B4;
        }
        else if (r2 & 0x80) {
            if (!(var->unk2AC & 0x80))
                m4aSongNumStart(0x21D);
            var->unk2AE = 0;
            gCurTask->main = sub_08129A6C;
        }
    }
    sub_081297F8(var);
    if (!(var->unk2AC & 0x80)) {
        if (var->unk2AC & 4) {
            sub_081288DC(&var->unk4[4][0]);
            sub_081288DC(&var->unk4[5][0]);
            sub_081288DC(&var->unk4[6][0]);
        }
        else {
            sub_081288DC(&var->unk4[0][0]);
            sub_081288DC(&var->unk4[2][0]);
        }
    }
}

void sub_081297F8(struct Unk_08128F44 *a1) {
    const u16 *p;

    if (a1->unk2B3++ > 5) {
        a1->unk2B3 = 0;
        p = gUnk_082DE69C + 0x10 * (a1->unk2AC & 2 ? a1->unk2B2 : a1->unk2B2 + 1);
        a1->unk2AC ^= 2;
        if (gUnk_03002440 & 0x20000)
            sub_0815828C(p, 0x10 * a1->unk2B0, 0x10);
        else {
            DmaCopy16(3, p, gObjPalette + 0x10 * a1->unk2B0, 0x10 * sizeof(u16));
            gUnk_03002440 |= 2;
        }
    }
}

void sub_081298B4(void) {
    struct Unk_08128F44 *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    if (var->unk2AC & 0x10) {
        var->unk4[0][0].unk28 += 8;
        var->unk4[0][0].unk2C += 4;
        var->unk4[0][0].unk0.unk14 &= ~0x7C0;
        var->unk4[0][0].unk0.unk14 |= 0x2C0;
        var->unk4[0][0].unk0.palId = var->unk2B1;
        var->unk4[1][0].unk0.unk14 &= ~0x7C0;
        var->unk4[1][0].unk0.unk14 |= 0x2C0;
        var->unk4[1][0].unk0.palId = var->unk2B1;
        var->unk4[2][0].unk28 -= 8;
        var->unk4[2][0].unk2C -= 4;
        var->unk4[2][0].unk0.unk14 &= ~0x7C0;
        var->unk4[2][0].unk0.unk14 |= 0x280;
        var->unk4[2][0].unk0.palId = var->unk2B0;
        var->unk4[3][0].unk0.unk14 &= ~0x7C0;
        var->unk4[3][0].unk0.unk14 |= 0x280;
        var->unk4[3][0].unk0.palId = var->unk2B0;
    }
    else {
        var->unk4[0][0].unk28 -= 8;
        var->unk4[0][0].unk2C -= 4;
        var->unk4[0][0].unk0.unk14 &= ~0x7C0;
        var->unk4[0][0].unk0.unk14 |= 0x280;
        var->unk4[0][0].unk0.palId = var->unk2B0;
        var->unk4[1][0].unk0.unk14 &= ~0x7C0;
        var->unk4[1][0].unk0.unk14 |= 0x280;
        var->unk4[1][0].unk0.palId = var->unk2B0;
        var->unk4[2][0].unk28 += 8;
        var->unk4[2][0].unk2C += 4;
        var->unk4[2][0].unk0.unk14 &= ~0x7C0;
        var->unk4[2][0].unk0.unk14 |= 0x2C0;
        var->unk4[2][0].unk0.palId = var->unk2B1;
        var->unk4[3][0].unk0.unk14 &= ~0x7C0;
        var->unk4[3][0].unk0.unk14 |= 0x2C0;
        var->unk4[3][0].unk0.palId = var->unk2B1;
    }
    if (var->unk2AC & 0x10)
        var->unk2B2 = 1;
    else
        var->unk2B2 = 3;
    sub_081297F8(var);
    if (!(var->unk2AC & 0x80)) {
        sub_081288DC(&var->unk4[0][0]);
        sub_081288DC(&var->unk4[2][0]);
    }
    if (++var->unk2AE > 9) {
        gCurTask->main = sub_081295A0;
        var->unk2AC ^= 0x10;
        var->unk2AC ^= 0x20;
    }
}

void sub_08129A6C(void) {
    struct Unk_08128F44 *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    if (var->unk2AC & 0x10) {
        var->unk4[0][0].unk28 += 8;
        var->unk4[0][0].unk2C += 4;
        var->unk4[0][0].unk0.palId = var->unk2B1;
        var->unk4[1][0].unk0.palId = var->unk2B1;
        var->unk4[2][0].unk28 -= 8;
        var->unk4[2][0].unk2C -= 4;
        var->unk4[2][0].unk0.palId = var->unk2B0;
        var->unk4[3][0].unk0.palId = var->unk2B0;
    }
    else {
        var->unk4[0][0].unk28 -= 8;
        var->unk4[0][0].unk2C -= 4;
        var->unk4[0][0].unk0.palId = var->unk2B0;
        var->unk4[1][0].unk0.palId = var->unk2B0;
        var->unk4[2][0].unk28 += 8;
        var->unk4[2][0].unk2C += 4;
        var->unk4[2][0].unk0.palId = var->unk2B1;
        var->unk4[3][0].unk0.palId = var->unk2B1;
    }
    if (var->unk2AC & 0x10)
        var->unk2B2 = 1;
    else
        var->unk2B2 = 3;
    sub_081297F8(var);
    if (!(var->unk2AC & 0x80)) {
        sub_081288DC(&var->unk4[0][0]);
        sub_081288DC(&var->unk4[2][0]);
    }
    if (++var->unk2AE > 9) {
        if (var->unk2AC & 0x10) {
            var->unk4[0][0].unk0.unk14 &= ~0x7C0;
            var->unk4[0][0].unk0.unk14 |= 0x2C0;
            var->unk4[1][0].unk0.unk14 &= ~0x7C0;
            var->unk4[1][0].unk0.unk14 |= 0x2C0;
            var->unk4[2][0].unk0.unk14 &= ~0x7C0;
            var->unk4[2][0].unk0.unk14 |= 0x280;
            var->unk4[3][0].unk0.unk14 &= ~0x7C0;
            var->unk4[3][0].unk0.unk14 |= 0x280;
        }
        else {
            var->unk4[0][0].unk0.unk14 &= ~0x7C0;
            var->unk4[0][0].unk0.unk14 |= 0x280;
            var->unk4[1][0].unk0.unk14 &= ~0x7C0;
            var->unk4[1][0].unk0.unk14 |= 0x280;
            var->unk4[2][0].unk0.unk14 &= ~0x7C0;
            var->unk4[2][0].unk0.unk14 |= 0x2C0;
            var->unk4[3][0].unk0.unk14 &= ~0x7C0;
            var->unk4[3][0].unk0.unk14 |= 0x2C0;
        }
        gCurTask->main = sub_081295A0;
        var->unk2AC ^= 0x10;
        var->unk2AC ^= 0x20;
    }
}

void sub_08129C34(void) {
    struct Unk_08128F44 *tmp = TaskGetStructPtr(gCurTask), *var = tmp;
    const u8 *p = gUnk_08363AA0 + 3 * var->unk2AD;

    var->unk4[p[0]][4].unk28 += 0x10;
    var->unk4[p[0]][4].unk2C += 8;
    var->unk4[p[0]][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[0]][4].unk0.unk14 |= 0x300;
    var->unk4[p[0]][4].unk0.palId = var->unk2B1;
    var->unk4[p[0] + 3][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[0] + 3][4].unk0.unk14 |= 0x300;
    var->unk4[p[0] + 3][4].unk0.palId = var->unk2B1;
    var->unk4[p[1]][4].unk28 -= 8;
    var->unk4[p[1]][4].unk2C -= 4;
    var->unk4[p[1]][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[1]][4].unk0.unk14 |= 0x280;
    var->unk4[p[1]][4].unk0.palId = var->unk2B0;
    var->unk4[p[1] + 3][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[1] + 3][4].unk0.unk14 |= 0x280;
    var->unk4[p[1] + 3][4].unk0.palId = var->unk2B0;
    var->unk4[p[2]][4].unk28 -= 8;
    var->unk4[p[2]][4].unk2C -= 4;
    var->unk4[p[2]][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[2]][4].unk0.unk14 |= 0x2C0;
    var->unk4[p[2]][4].unk0.palId = var->unk2B1;
    var->unk4[p[2] + 3][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[2] + 3][4].unk0.unk14 |= 0x2C0;
    var->unk4[p[2] + 3][4].unk0.palId = var->unk2B1;
    if (p[1] == 0)
        var->unk2B2 = 1;
    else if (p[1] == 1)
        var->unk2B2 = 3;
    else
        var->unk2B2 = 5;
    sub_081297F8(var);
    if (!(var->unk2AC & 0x80)) {
        sub_081288DC(&var->unk4[4][0]);
        sub_081288DC(&var->unk4[5][0]);
        sub_081288DC(&var->unk4[6][0]);
    }
    if (++var->unk2AE > 9) {
        gCurTask->main = sub_081295A0;
        var->unk2AD = p[1];
    }
}

void sub_08129F28(void) {
    struct Unk_08128F44 *tmp = TaskGetStructPtr(gCurTask), *var = tmp;
    const u8 *p = gUnk_08363AA0 + 3 * var->unk2AD;

    var->unk4[p[0]][4].unk28 += 8;
    var->unk4[p[0]][4].unk2C += 4;
    var->unk4[p[0]][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[0]][4].unk0.unk14 |= 0x2C0;
    var->unk4[p[0]][4].unk0.palId = var->unk2B1;
    var->unk4[p[0] + 3][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[0] + 3][4].unk0.unk14 |= 0x2C0;
    var->unk4[p[0] + 3][4].unk0.palId = var->unk2B1;
    var->unk4[p[1]][4].unk28 += 8;
    var->unk4[p[1]][4].unk2C += 4;
    var->unk4[p[1]][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[1]][4].unk0.unk14 |= 0x300;
    var->unk4[p[1]][4].unk0.palId = var->unk2B1;
    var->unk4[p[1] + 3][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[1] + 3][4].unk0.unk14 |= 0x300;
    var->unk4[p[1] + 3][4].unk0.palId = var->unk2B1;
    var->unk4[p[2]][4].unk28 -= 0x10;
    var->unk4[p[2]][4].unk2C -= 8;
    var->unk4[p[2]][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[2]][4].unk0.unk14 |= 0x280;
    var->unk4[p[2]][4].unk0.palId = var->unk2B0;
    var->unk4[p[2] + 3][4].unk0.unk14 &= ~0x7C0;
    var->unk4[p[2] + 3][4].unk0.unk14 |= 0x280;
    var->unk4[p[2] + 3][4].unk0.palId = var->unk2B0;
    if (p[2] == 0)
        var->unk2B2 = 1;
    else if (p[2] == 1)
        var->unk2B2 = 3;
    else
        var->unk2B2 = 5;
    sub_081297F8(var);
    if (!(var->unk2AC & 0x80)) {
        sub_081288DC(&var->unk4[4][0]);
        sub_081288DC(&var->unk4[5][0]);
        sub_081288DC(&var->unk4[6][0]);
    }
    if (++var->unk2AE > 9) {
        gCurTask->main = sub_081295A0;
        var->unk2AD = p[2];
    }
}

void sub_0812A218(struct Unk_08128F44_4 *a1) {
    struct Unk_08128F44_4 *unk3C = a1->unk3C;

    a1->unk28 += unk3C->unk28;
    a1->unk2C += unk3C->unk2C;
    a1->unk30 = unk3C->unk30;
    a1->unk32 = unk3C->unk32;
    a1->unk34 |= 0x10;
    a1->unk38 = sub_0812A388(a1);
    unk3C->unk40 = NULL;
    a1->unk3C = NULL;
}

void sub_0812A254(struct Unk_08128F44_4 *a1) {
    s32 a[2];

    a[0] = 0;
    a[1] = 0;
    if (!(a1->unk34 & 0x2000)) {
        a1->unk28 += a1->unk30;
        a1->unk2C += a1->unk32;
        sub_0812A344(a, a1);
        a1->unk0.x = a[0] >> 2;
        a1->unk0.y = a[1] >> 2;
    }
}

// not referenced
void sub_0812A29C(struct Unk_08128F44_4 *a1) {
    a1->unk34 &= ~0x100;
    if (a1->unk34 & 0x200)
        a1->unk0.unk1B = 0xFF;
}

void sub_0812A2C0(struct Unk_0812D1EC_0 *a1) {
    a1->unk48 += a1->unk4.unk30;
    a1->unk4C += a1->unk4.unk32;
    a1->unk4.unk28 = a1->unk48;
    a1->unk4.unk2C = a1->unk4C;
    if (a1->unk52 & 2) {
        a1->unk4.unk28 += a1->unk0->unk0[0].unk28;
        a1->unk4.unk2C += a1->unk0->unk0[0].unk2C;
    }
    sub_081288DC(&a1->unk4);
}

bool32 sub_0812A304(void) {
    if ((!gBldRegs.bldY || gBldRegs.bldY == 0x1F) && !gBldRegs.bldAlpha)
        return FALSE;
    else
        return TRUE;
}

bool32 sub_0812A328(struct Unk_08128F44 *a1) {
    if (a1->unk2AC & 1)
        return TRUE;
    else
        return FALSE;
}

void sub_0812A344(s32 *a1, struct Unk_08128F44_4 *a2) {
    if (a2->unk3C)
        sub_0812A344(a1, a2->unk3C);
    if (a2->unk38) {
        a1[0] += a2->unk28 + a2->unk38[0];
        a1[1] += a2->unk2C + a2->unk38[1];
    }
    else {
        a1[0] += a2->unk28;
        a1[1] += a2->unk2C;
    }
}

s32 *sub_0812A388(struct Unk_08128F44_4 *a1) {
    while (1) {
        if (!a1->unk3C)
            return a1->unk38;
        a1 = a1->unk3C;
    }
}

void sub_0812A39C(void) {
    struct Unk_08128F44 *var = TaskGetStructPtr(gCurTask);

    gCurTask->main = sub_081295A0;
    if (!(var->unk2AC & 0x80))
        m4aSongNumStart(542);
}

void sub_0812A3F4(struct Unk_0812A77C_40 *a1, s32 *a2, u8 a3, u8 a4) {
    if (a4 < gUnk_0203AD30)
        a1->unk90 = 0;
    else
        a1->unk90 = 1;
    a1->unk88 = NULL;
    a1->unk8C = NULL;
    a1->unk92 = 0;
    a1->unk96 = 0;
    a1->unk94 = 0;
    a1->unk98 = 0;
    a1->unk9A = 0;
    a1->unk9C = 0x5A;
    a1->unk9E = 1;
    a1->unkA0 = 1;
    a1->unkAC = 3;
    a1->unkA6 = 0;
    a1->unkA8 = 0;
    a1->unkAA = 0;
    a1->unkAD = 0;
    a1->unkAE = 0;
    CpuFill32(0, &a1->unk0[0], sizeof(struct Unk_08128F44_4));
    a1->unk0[0].unk0.tilesVram = 0x6010000;
    a1->unk0[0].unk0.unk14 = 0x480;
    a1->unk0[0].unk0.animId = gUnk_08364CE4[gLanguage][6].animId;
    a1->unk0[0].unk0.variant = gUnk_08364CE4[gLanguage][6].variant;
    a1->unk0[0].unk0.unk16 = 0;
    a1->unk0[0].unk0.unk1B = 0xFF;
    a1->unk0[0].unk0.unk1C = 0x10;
    a1->unk0[0].unk0.palId = a3;
    a1->unk0[0].unk0.x = gUnk_08364C9A[a3][0] >> 2;
    a1->unk0[0].unk0.y = gUnk_08364C9A[a3][1] >> 2;
    a1->unk0[0].unk0.unk8 = 0xC0000;
    a1->unk0[0].unk28 = gUnk_08364C9A[a3][0];
    a1->unk0[0].unk2C = gUnk_08364C9A[a3][1];
    a1->unk0[0].unk30 = 0;
    a1->unk0[0].unk32 = 0;
    a1->unk0[0].unk34 = 0x810;
    a1->unk0[0].unk36 = 0;
    a1->unk0[0].unk3C = NULL;
    a1->unk0[0].unk40 = NULL;
    a1->unk0[0].unk38 = a2;
    CpuFill32(0, &a1->unk0[1], sizeof(struct Unk_08128F44_4));
    a1->unk0[1].unk0.tilesVram = 0x6010000;
    a1->unk0[1].unk0.unk14 = 0x440;
    a1->unk0[1].unk0.animId = gUnk_08364F9C[gLanguage][0].animId;
    a1->unk0[1].unk0.variant = gUnk_08364F9C[gLanguage][0].variant;
    a1->unk0[1].unk0.unk16 = 0;
    a1->unk0[1].unk0.unk1B = 0xFF;
    a1->unk0[1].unk0.unk1C = 0x10;
    a1->unk0[1].unk0.palId = 4;
    a1->unk0[1].unk0.x = gUnk_08364C9A[a3][4] >> 2;
    a1->unk0[1].unk0.y = gUnk_08364C9A[a3][5] >> 2;
    a1->unk0[1].unk0.unk8 = 0xC0000;
    a1->unk0[1].unk28 = gUnk_08364C9A[a3][4];
    a1->unk0[1].unk2C = gUnk_08364C9A[a3][5];
    a1->unk0[1].unk30 = 0;
    a1->unk0[1].unk32 = 0;
    a1->unk0[1].unk34 = 0x10;
    a1->unk0[1].unk36 = 0;
    a1->unk0[1].unk3C = NULL;
    a1->unk0[1].unk40 = NULL;
    a1->unk0[1].unk38 = a2;
    if (a3 == 2 || a3 == 3) {
        a1->unk0[0].unk34 |= 1;
        a1->unk0[1].unk34 |= 1;
    }
}

void sub_0812A5FC(struct Unk_0812A77C_40 *a1, u8 a2) {
    if (a1->unk90 & 1) {
        u32 r6;

        r6 = Rand16();
        r6 &= 0xF;
        a1->unkAD = gUnk_08365114[a2][r6];
        r6 = Rand16();
        r6 &= 3;
        a1->unkAE = gUnk_08365144[a2][r6];
    }
}

void sub_0812A670(void) {
    CpuFill32(0, (void *)VRAM, VRAM_SIZE);
    if (gUnk_03002440 & 0x10000)
        sub_08158334(gUnk_0836515C, 0, BG_PLTT_SIZE / sizeof(u16));
    else {
        DmaCopy16(3, gUnk_0836515C, gBgPalette, BG_PLTT_SIZE);
        gUnk_03002440 |= 1;
    }
    LZ77UnCompVram(gUnk_08365380, (void *)0x6000000);
    switch (gLanguage) {
    case LANGUAGE_JAPANESE:
        LZ77UnCompVram(gUnk_0836C654, (void *)0x6002000);
        break;
    case LANGUAGE_ENGLISH:
        LZ77UnCompVram(gUnk_0836E034, (void *)0x6002000);
        break;
    case LANGUAGE_GERMAN:
        LZ77UnCompVram(gUnk_0836E66C, (void *)0x6002000);
        break;
    case LANGUAGE_FRENCH:
        LZ77UnCompVram(gUnk_0836D33C, (void *)0x6002000);
        break;
    case LANGUAGE_SPANISH:
        LZ77UnCompVram(gUnk_0836D9F0, (void *)0x6002000);
        break;
    case LANGUAGE_ITALIAN:
        LZ77UnCompVram(gUnk_0836CCDC, (void *)0x6002000);
        break;
    }
    LZ77UnCompVram(gUnk_08D61B3C[gLanguage], (void *)0x6010000);
}

void sub_0812A77C(void) {
    struct Task *t;
    struct Unk_0812A77C *var;

    gRngVal = 0;
    gDispCnt = DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_OBJ_ON;
    gBgCntRegs[0] = BGCNT_PRIORITY(2) | BGCNT_TXT256x256 | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(28);
    gBgCntRegs[1] = BGCNT_PRIORITY(2) | BGCNT_TXT256x256 | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(29);
    gBgCntRegs[2] = BGCNT_PRIORITY(1) | BGCNT_TXT256x256 | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(30);
    gBldRegs.bldCnt = BLDCNT_TGT1_ALL | BLDCNT_EFFECT_LIGHTEN;
    gBldRegs.bldY = 0x10;
    gBgScrollRegs[0][0] = 8;
    gBgScrollRegs[0][1] = 0x58;
    gBgScrollRegs[1][0] = 8;
    gBgScrollRegs[1][1] = 0x58;
    gBgScrollRegs[2][0] = 0;
    gBgScrollRegs[2][1] = 0;
    t = TaskCreate(sub_0812A8F0, sizeof(struct Unk_0812A77C), 0x100, TASK_USE_IWRAM, sub_0812E588);
    var = TaskGetStructPtr(t);
    CpuFill16(0, var, sizeof(struct Unk_0812A77C));
    var->unk14[0] = sub_08128D48(&gUnk_083723C8);
    var->unk14[1] = sub_08128D48(&gUnk_083723D4);
    var->unk14[2] = sub_08128D48(&gUnk_083723E0);
    var->unk14[3] = sub_08128D48(&gUnk_083723EC);
    var->unk14[4] = sub_08128D48(&gUnk_083723F8);
    var->unk14[5] = sub_08128D48(&gUnk_08372404);
    var->unk14[6] = sub_08128D48(&gUnk_08372410);
    var->unk14[7] = sub_08128D48(&gUnk_0837241C);
    var->unk14[8] = sub_08128D48(&gUnk_08372428);
    var->unk14[9] = sub_08128D48(&gUnk_08372434);
    var->unk5F4 = gUnk_0203AD14;
    var->unk10[0] = gUnk_08364CD2[gUnk_0203AD3C][0];
    var->unk10[1] = gUnk_08364CD2[gUnk_0203AD3C][1];
    var->unk10[2] = gUnk_08364CD2[gUnk_0203AD3C][2];
    var->unk10[3] = gUnk_08364CD2[gUnk_0203AD3C][3];
}

void sub_0812A8F0(void) {
    struct Unk_0812A77C *var;
#ifndef NONMATCHING
    register struct Unk_08128F44_4 *r4 asm("r4");
#else
    struct Unk_08128F44_4 *r4;
#endif

    CreatePauseFade(-0x10, 1);
    var = TaskGetStructPtr(gCurTask);
    gCurTask->main = sub_0812B204;
    var->unk0 = NULL;
    var->unk4 = NULL;
    var->unk8[0] = 0;
    var->unk8[1] = 0;
    var->unk5EC = 0;
    var->unk5F6 = 0;
    sub_0812AAE0(var);
    sub_0812A3F4(&var->unk40[0], var->unk8, 0, var->unk10[0]);
    sub_0812A3F4(&var->unk40[1], var->unk8, 1, var->unk10[1]);
    sub_0812A3F4(&var->unk40[2], var->unk8, 2, var->unk10[2]);
    sub_0812A3F4(&var->unk40[3], var->unk8, 3, var->unk10[3]);
    sub_0812A5FC(&var->unk40[0], var->unk5F4);
    sub_0812A5FC(&var->unk40[1], var->unk5F4);
    sub_0812A5FC(&var->unk40[2], var->unk5F4);
    sub_0812A5FC(&var->unk40[3], var->unk5F4);
    CpuFill32(0, r4 = &var->unk564[0], sizeof(struct Unk_08128F44_4));
    r4->unk0.tilesVram = 0x6010000;
    r4->unk0.unk14 = 0x3C0;
    r4->unk0.animId = gUnk_08365054[gLanguage][0].animId;
    r4->unk0.variant = gUnk_08365054[gLanguage][0].variant;
    r4->unk0.unk16 = 0;
    r4->unk0.unk1B = 0xFF;
    r4->unk0.unk1C = 0x10;
    r4->unk0.palId = 0xB;
    r4->unk0.x = 0;
    r4->unk0.y = 0x10;
    r4->unk0.unk8 = 0xC0000;
    r4->unk28 = 0;
    r4->unk2C = 0x40;
    r4->unk30 = 0;
    r4->unk32 = 0;
    r4->unk34 = 0x810;
    r4->unk36 = 0;
    r4->unk38 = NULL;
    r4->unk3C = NULL;
    r4->unk40 = NULL;
    CpuFill32(0, r4 = &var->unk564[1], sizeof(struct Unk_08128F44_4));
    r4->unk0.tilesVram = 0x6010000;
    r4->unk0.unk14 = 0x400;
    r4->unk0.animId = gUnk_08365054[gLanguage][0].animId;
    r4->unk0.variant = gUnk_08365054[gLanguage][0].variant;
    r4->unk0.unk16 = 0;
    r4->unk0.unk1B = 0xFF;
    r4->unk0.unk1C = 0x10;
    r4->unk0.palId = 0xB;
    r4->unk0.x = 0;
    r4->unk0.y = -0x28;
    r4->unk0.unk8 = 0xC0000;
    r4->unk28 = 0;
    r4->unk2C = -0xA0;
    r4->unk30 = 0;
    r4->unk32 = 0;
    r4->unk34 = 0x810;
    r4->unk36 = 0;
    r4->unk38 = NULL;
    r4->unk3C = NULL;
    r4->unk40 = NULL;
    sub_0812E7A0();
    sub_0812E818(var->unk40);
    m4aSongNumStart(28);
    m4aSongNumStart(556);
}

void sub_0812AAE0(struct Unk_0812A77C *a1) {
    u8 i;
    struct Sprite sprite[36];

    for (i = 0; i < 4; ++i) {
        u8 idx = a1->unk10[i];

        SpriteInit(&sprite[0], 0x6010000, 0x480,
            gUnk_083650B4[gLanguage][idx].animId,
            gUnk_083650B4[gLanguage][idx].variant,
            0, 0xFF, 0x10, i, 0, 0, 0x80000);
    }
    // This is completely pointless as every case is doing the same thing except for using different buffers
    switch (gLanguage) {
    case LANGUAGE_JAPANESE:
        SpriteInitNoPointer(&sprite[0], 0x6010000, 0x480, 0x345, 0,
            0, 0xFF, 0x10, 4, 0, 0, 0x80000);
        SpriteInit(&sprite[1], 0x6010000, 0x480, 0x344, 7,
            0, 0xFF, 0x10, 5, 0, 0, 0x80000);
        SpriteInit(&sprite[2], 0x6010000, 0x480, 0x345, 0x12,
            0, 0xFF, 0x10, 6, 0, 0, 0x80000);
        SpriteInit(&sprite[3], 0x6010000, 0x480, 0x343, 0x11,
            0, 0xFF, 0x10, 7, 0, 0, 0x80000);
        SpriteInit(&sprite[4], 0x6010000, 0x480, 0x343, 0,
            0, 0xFF, 0x10, 0xB, 0, 0, 0x80000);
        SpriteInit(&sprite[5], 0x6010000, 0x480, 0x346, 0,
            0, 0xFF, 0x10, 0xC, 0, 0, 0x80000);
        break;
    case LANGUAGE_ENGLISH:
        SpriteInit(&sprite[6], 0x6010000, 0x480, 0x345, 0,
            0, 0xFF, 0x10, 4, 0, 0, 0x80000);
        SpriteInit(&sprite[7], 0x6010000, 0x480, 0x344, 7,
            0, 0xFF, 0x10, 5, 0, 0, 0x80000);
        SpriteInit(&sprite[8], 0x6010000, 0x480, 0x345, 0x12,
            0, 0xFF, 0x10, 6, 0, 0, 0x80000);
        SpriteInit(&sprite[9], 0x6010000, 0x480, 0x343, 0x11,
            0, 0xFF, 0x10, 7, 0, 0, 0x80000);
        SpriteInit(&sprite[10], 0x6010000, 0x480, 0x343, 0,
            0, 0xFF, 0x10, 0xB, 0, 0, 0x80000);
        SpriteInit(&sprite[11], 0x6010000, 0x480, 0x346, 0,
            0, 0xFF, 0x10, 0xC, 0, 0, 0x80000);
        break;
    case LANGUAGE_GERMAN:
        SpriteInit(&sprite[12], 0x6010000, 0x480, 0x345, 0,
            0, 0xFF, 0x10, 4, 0, 0, 0x80000);
        SpriteInit(&sprite[13], 0x6010000, 0x480, 0x344, 7,
            0, 0xFF, 0x10, 5, 0, 0, 0x80000);
        SpriteInit(&sprite[14], 0x6010000, 0x480, 0x345, 0x12,
            0, 0xFF, 0x10, 6, 0, 0, 0x80000);
        SpriteInit(&sprite[15], 0x6010000, 0x480, 0x343, 0x11,
            0, 0xFF, 0x10, 7, 0, 0, 0x80000);
        SpriteInit(&sprite[16], 0x6010000, 0x480, 0x343, 0,
            0, 0xFF, 0x10, 0xB, 0, 0, 0x80000);
        SpriteInit(&sprite[17], 0x6010000, 0x480, 0x346, 0,
            0, 0xFF, 0x10, 0xC, 0, 0, 0x80000);
        break;
    case LANGUAGE_FRENCH:
        SpriteInit(&sprite[18], 0x6010000, 0x480, 0x345, 0,
            0, 0xFF, 0x10, 4, 0, 0, 0x80000);
        SpriteInit(&sprite[19], 0x6010000, 0x480, 0x344, 7,
            0, 0xFF, 0x10, 5, 0, 0, 0x80000);
        SpriteInit(&sprite[20], 0x6010000, 0x480, 0x345, 0x12,
            0, 0xFF, 0x10, 6, 0, 0, 0x80000);
        SpriteInit(&sprite[21], 0x6010000, 0x480, 0x343, 0x11,
            0, 0xFF, 0x10, 7, 0, 0, 0x80000);
        SpriteInit(&sprite[22], 0x6010000, 0x480, 0x343, 0,
            0, 0xFF, 0x10, 0xB, 0, 0, 0x80000);
        SpriteInit(&sprite[23], 0x6010000, 0x480, 0x346, 0,
            0, 0xFF, 0x10, 0xC, 0, 0, 0x80000);
        break;
    case LANGUAGE_SPANISH:
        SpriteInit(&sprite[24], 0x6010000, 0x480, 0x345, 0,
            0, 0xFF, 0x10, 4, 0, 0, 0x80000);
        SpriteInit(&sprite[25], 0x6010000, 0x480, 0x344, 7,
            0, 0xFF, 0x10, 5, 0, 0, 0x80000);
        SpriteInit(&sprite[26], 0x6010000, 0x480, 0x345, 0x12,
            0, 0xFF, 0x10, 6, 0, 0, 0x80000);
        SpriteInit(&sprite[27], 0x6010000, 0x480, 0x343, 0x11,
            0, 0xFF, 0x10, 7, 0, 0, 0x80000);
        SpriteInit(&sprite[28], 0x6010000, 0x480, 0x343, 0,
            0, 0xFF, 0x10, 0xB, 0, 0, 0x80000);
        SpriteInit(&sprite[29], 0x6010000, 0x480, 0x346, 0,
            0, 0xFF, 0x10, 0xC, 0, 0, 0x80000);
        break;
    case LANGUAGE_ITALIAN:
        SpriteInit(&sprite[30], 0x6010000, 0x480, 0x345, 0,
            0, 0xFF, 0x10, 4, 0, 0, 0x80000);
        SpriteInit(&sprite[31], 0x6010000, 0x480, 0x344, 7,
            0, 0xFF, 0x10, 5, 0, 0, 0x80000);
        SpriteInit(&sprite[32], 0x6010000, 0x480, 0x345, 0x12,
            0, 0xFF, 0x10, 6, 0, 0, 0x80000);
        SpriteInit(&sprite[33], 0x6010000, 0x480, 0x343, 0x11,
            0, 0xFF, 0x10, 7, 0, 0, 0x80000);
        SpriteInit(&sprite[34], 0x6010000, 0x480, 0x343, 0,
            0, 0xFF, 0x10, 0xB, 0, 0, 0x80000);
        SpriteInit(&sprite[35], 0x6010000, 0x480, 0x346, 0,
            0, 0xFF, 0x10, 0xC, 0, 0, 0x80000);
        break;
    }
    CpuCopy32(gUnk_0836EEC8, (void *)0x600E000, sizeof(gUnk_0836EEC8));
    CpuCopy32(gUnk_0836F6C8, (void *)0x600E800, sizeof(gUnk_0836F6C8));
}

void sub_0812B204(void) {
    struct Unk_0812A77C *var = TaskGetStructPtr(gCurTask);

    if (var->unk5F2++ > 120) {
        var->unk5F2 = 0;
        gCurTask->main = sub_0812B2F8;
        var->unk40[0].unk0[0].unk2C += 0x18;
        var->unk40[1].unk0[0].unk2C += 0x18;
        var->unk40[2].unk0[0].unk2C += 0x18;
        var->unk40[3].unk0[0].unk2C += 0x18;
        sub_0812E764(&var->unk40[0].unk0[0].unk0, 0);
        sub_0812E764(&var->unk40[1].unk0[0].unk0, 0);
        sub_0812E764(&var->unk40[2].unk0[0].unk0, 0);
        sub_0812E764(&var->unk40[3].unk0[0].unk0, 0);
    }
    sub_081288DC(&var->unk40[0].unk0[0]);
    sub_081288DC(&var->unk40[1].unk0[0]);
    sub_081288DC(&var->unk40[2].unk0[0]);
    sub_081288DC(&var->unk40[3].unk0[0]);
    sub_081288DC(&var->unk40[0].unk0[1]);
    sub_081288DC(&var->unk40[1].unk0[1]);
    sub_081288DC(&var->unk40[2].unk0[1]);
    sub_081288DC(&var->unk40[3].unk0[1]);
}

void sub_0812B2F8(void) {
    struct Unk_0812A77C *var = TaskGetStructPtr(gCurTask);

    if (var->unk5F2++ > 60) {
        var->unk5F2 = 0;
        gCurTask->main = sub_0812B418;
        var->unk0 = sub_0812D4F4();
        var->unk40[0].unk88 = sub_0812D1EC(&var->unk40[0], 0);
        var->unk40[1].unk88 = sub_0812D1EC(&var->unk40[1], 1);
        var->unk40[2].unk88 = sub_0812D1EC(&var->unk40[2], 2);
        var->unk40[3].unk88 = sub_0812D1EC(&var->unk40[3], 3);
        var->unk40[0].unk90 |= 0x10;
        var->unk40[1].unk90 |= 0x10;
        var->unk40[2].unk90 |= 0x10;
        var->unk40[3].unk90 |= 0x10;
        sub_0812D060();
    }
    sub_081288DC(&var->unk40[0].unk0[0]);
    sub_081288DC(&var->unk40[1].unk0[0]);
    sub_081288DC(&var->unk40[2].unk0[0]);
    sub_081288DC(&var->unk40[3].unk0[0]);
    sub_081288DC(&var->unk40[0].unk0[1]);
    sub_081288DC(&var->unk40[1].unk0[1]);
    sub_081288DC(&var->unk40[2].unk0[1]);
    sub_081288DC(&var->unk40[3].unk0[1]);
}

void sub_0812B418(void) {
    struct Unk_0812A77C *tmp = TaskGetStructPtr(gCurTask), *var = tmp;
    struct Unk_08128F44_4 *ptr, *ptr2, *ptr3;

    sub_0812CDD4(var);
    if (sub_0812E6A8(TaskGetStructPtr(var->unk0)) && var->unk0) {
        TaskDestroy(var->unk0);
        var->unk0 = NULL;
        var->unk40[0].unk0[0].unk40 = ptr = &var->unk564[0];
        ptr->unk3C = &var->unk40[0].unk0[0];
        ptr->unk34 &= ~0x10;
        ptr2 = &var->unk40[0].unk0[1];
        ptr2->unk40 = ptr3 = &var->unk564[1];
        ptr3->unk3C = ptr2;
        ptr3->unk34 &= ~0x10;
        sub_0812E764(&var->unk40[0].unk0[0].unk0, 1);
        sub_0812E764(&var->unk40[1].unk0[0].unk0, 1);
        sub_0812E764(&var->unk40[2].unk0[0].unk0, 1);
        sub_0812E764(&var->unk40[3].unk0[0].unk0, 1);
        gCurTask->main = sub_0812B63C;
        TaskDestroy(var->unk40[0].unk88);
        TaskDestroy(var->unk40[1].unk88);
        TaskDestroy(var->unk40[2].unk88);
        TaskDestroy(var->unk40[3].unk88);
        var->unk40[0].unk88 = NULL;
        var->unk40[1].unk88 = NULL;
        var->unk40[2].unk88 = NULL;
        var->unk40[3].unk88 = NULL;
        var->unk40[0].unk90 &= ~0x10;
        var->unk40[1].unk90 &= ~0x10;
        var->unk40[2].unk90 &= ~0x10;
        var->unk40[3].unk90 &= ~0x10;
        var->unk40[0].unk90 |= 0x20;
        var->unk40[1].unk90 |= 0x20;
        var->unk40[2].unk90 |= 0x20;
        var->unk40[3].unk90 |= 0x20;
        var->unk5F0 = 0x10;
        var->unk3C = 0;
        sub_0812E640();
    }
    sub_0812CED8(&var->unk40[0], 0);
    sub_0812CED8(&var->unk40[1], 1);
    sub_0812CED8(&var->unk40[2], 2);
    sub_0812CED8(&var->unk40[3], 3);
    sub_0812D124(var->unk40[0].unk9C, var->unk40[0].unk9E, &var->unk40[0]);
    sub_081288DC(&var->unk40[0].unk0[0]);
    sub_081288DC(&var->unk40[1].unk0[0]);
    sub_081288DC(&var->unk40[2].unk0[0]);
    sub_081288DC(&var->unk40[3].unk0[0]);
    sub_081288DC(&var->unk40[0].unk0[1]);
    sub_081288DC(&var->unk40[1].unk0[1]);
    sub_081288DC(&var->unk40[2].unk0[1]);
    sub_081288DC(&var->unk40[3].unk0[1]);
}

void sub_0812B63C(void) {
    struct Unk_0812A77C *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    sub_0812CDD4(var);
    if (var->unk40[0].unkA6 & 4 && var->unk564[0].unk34 & 0x200) {
        struct Unk_08128F44_4 *ptr = &var->unk564[0];

        ptr->unk0.animId = gUnk_08365054[gLanguage][1].animId;
        ptr->unk0.variant = gUnk_08365054[gLanguage][1].variant;
        ptr->unk0.unk1B = 0xFF;
        var->unk564[0].unk34 |= 0x800;
    }
    if (var->unk5F0 & 0x20) {
        sub_0812CF80(&var->unk40[0], var);
        sub_0812E604(&var->unk40[1]);
        sub_0812E604(&var->unk40[2]);
        sub_0812E604(&var->unk40[3]);
    }
    if (var->unk5F0 & 0x10) {
        var->unk40[0].unk0[0].unk2C -= 4 * gUnk_08364B5C[0][var->unk3C];
        var->unk40[1].unk0[0].unk2C -= 4 * gUnk_08364B5C[1][var->unk3C];
        var->unk40[2].unk0[0].unk2C -= 4 * gUnk_08364B5C[2][var->unk3C];
        var->unk40[3].unk0[0].unk2C -= 4 * gUnk_08364B5C[3][var->unk3C];
        var->unk8[1] += 4 * gUnk_08364C4C[var->unk3C];
        ++var->unk3C;
        if (var->unk3C > 60) {
            var->unk5F0 &= ~0x10;
            var->unk5F0 |= 0x20;
            sub_0812E764(&var->unk40[0].unk0[0].unk0, 5);
            sub_0812E764(&var->unk40[1].unk0[0].unk0, 5);
            sub_0812E764(&var->unk40[2].unk0[0].unk0, 5);
            sub_0812E764(&var->unk40[3].unk0[0].unk0, 5);
            var->unk3C = 0;
            sub_0812A218(&var->unk564[0]);
            // TODO: typo?
            var->unk564[1].unk30 = 0;
            var->unk564[1].unk32 = 0;
            sub_0812A218(&var->unk564[1]);
            var->unk564[1].unk30 = 0;
            var->unk564[1].unk32 = 0;
            var->unk40[0].unkA8 = var->unk564[0].unk2C;
            var->unk40[1].unkA8 = var->unk564[0].unk2C;
            var->unk40[2].unkA8 = var->unk564[0].unk2C;
            var->unk40[3].unkA8 = var->unk564[0].unk2C;
            var->unk40[0].unkAA = var->unk564[1].unk2C;
            var->unk40[1].unkAA = var->unk564[1].unk2C;
            var->unk40[2].unkAA = var->unk564[1].unk2C;
            var->unk40[3].unkAA = var->unk564[1].unk2C;
            var->unk40[0].unkA6 |= 2;
            var->unk40[1].unkA6 |= 2;
            var->unk40[2].unkA6 |= 2;
            var->unk40[3].unkA6 |= 2;
        }
    }
    else if (var->unk5F0 & 0x20) {
        if (var->unk5EC > 0x29) {
            var->unk564[0].unk32 = 0;
            var->unk40[0].unkA6 &= ~2;
            var->unk40[0].unk0[0].unk2C += 4 * gUnk_08364C88[var->unk3C];
            var->unk40[1].unk0[0].unk2C += 4 * gUnk_08364C88[var->unk3C];
            var->unk40[2].unk0[0].unk2C += 4 * gUnk_08364C88[var->unk3C];
            var->unk40[3].unk0[0].unk2C += 4 * gUnk_08364C88[var->unk3C];
            ++var->unk3C;
        }
        else {
            if (var->unk5EC < 0xF)
                var->unk8[1] -= 0x20;
            ++var->unk5EC;
        }
        if (var->unk40[0].unkA6 & 2)
            var->unk40[0].unkA8 += 0x10;
        if (var->unk40[1].unkA6 & 2)
            var->unk40[1].unkA8 += 0x10;
        if (var->unk40[2].unkA6 & 2)
            var->unk40[2].unkA8 += 0x10;
        if (var->unk40[3].unkA6 & 2)
            var->unk40[3].unkA8 += 0x10;
        var->unk564[0].unk2C = var->unk40[0].unkA8;
        var->unk564[1].unk2C = var->unk40[0].unkAA;
        if (var->unk3C > 8) {
            sub_0812E764(&var->unk40[0].unk0[0].unk0, 2);
            sub_0812E764(&var->unk40[1].unk0[0].unk0, 2);
            sub_0812E764(&var->unk40[2].unk0[0].unk0, 2);
            sub_0812E764(&var->unk40[3].unk0[0].unk0, 2);
        }
        if (var->unk3C > 0x11) {
            u8 i;

            var->unk5F0 &= ~0x20;
            var->unk5F0 |= 0x40;
            for (i = 0; i < 4; ++i) {
                struct Unk_08128F44_4 *ptr = &var->unk40[i].unk0[1];

                ptr->unk0.animId = gUnk_08364F9C[gLanguage][1].animId;
                ptr->unk0.variant = gUnk_08364F9C[gLanguage][1].variant;
                ptr->unk0.unk1B = 0xFF;
            }
            m4aSongNumStart(554);
            var->unk0 = sub_0812EFB4();
            CreatePauseFade(4, 1);
        }
    }
    else if (var->unk5F0 & 0x40) {
        if (!sub_0812A304()) {
            s16 sp04[4];
            bool32 sp10;

            var->unk40[0].unkA4 = var->unk40[0].unk9C;
            var->unk40[1].unkA4 = var->unk40[1].unk9C;
            var->unk40[2].unkA4 = var->unk40[2].unk9C;
            var->unk40[3].unkA4 = var->unk40[3].unk9C;
            if (var->unk40[0].unk90 & 1)
                var->unk40[0].unkA0 = var->unk40[0].unkAE;
            if (var->unk40[1].unk90 & 1)
                var->unk40[1].unkA0 = var->unk40[1].unkAE;
            if (var->unk40[2].unk90 & 1)
                var->unk40[2].unkA0 = var->unk40[2].unkAE;
            if (var->unk40[3].unk90 & 1)
                var->unk40[3].unkA0 = var->unk40[3].unkAE;
            var->unk40[0].unk9C = 8 * (var->unk40[0].unkA4 * var->unk40[0].unkA0 / 0xA + var->unk40[0].unkA4 / 8);
            var->unk40[1].unk9C = 8 * (var->unk40[1].unkA4 * var->unk40[1].unkA0 / 0xA + var->unk40[1].unkA4 / 8);
            var->unk40[2].unk9C = 8 * (var->unk40[2].unkA4 * var->unk40[2].unkA0 / 0xA + var->unk40[2].unkA4 / 8);
            var->unk40[3].unk9C = 8 * (var->unk40[3].unkA4 * var->unk40[3].unkA0 / 0xA + var->unk40[3].unkA4 / 8);
            sp10 = FALSE;
            if (var->unk40[0].unk9C >= 8000)
                sp10 = TRUE;
            sub_0812E468(var);
            CpuCopy32(gUnk_0836FEC8, (void *)0x600E000, sizeof(gUnk_0836FEC8));
            CpuCopy32(gUnk_083706C8, (void *)0x600E800, sizeof(gUnk_083706C8));
            gDispCnt |= DISPCNT_BG2_ON;
            CpuFill32(0, (void *)0x600F000, 0x400);
            gDispCnt &= ~DISPCNT_WIN0_ON;
            gBgScrollRegs[2][1] = 0;
            gCurTask->main = sub_0812BEE0;
            TaskDestroy(var->unk0);
            var->unk0 = NULL;
            CreatePauseFade(-0x10, 1);
            sp04[0] = var->unk40[0].unk9C;
            sp04[1] = var->unk40[1].unk9C;
            sp04[2] = var->unk40[2].unk9C;
            sp04[3] = var->unk40[3].unk9C;
            if (var->unk40[0].unkAC)
                sp04[0] -= 120;
            if (var->unk40[1].unkAC)
                sp04[1] -= 120;
            if (var->unk40[2].unkAC)
                sp04[2] -= 120;
            if (var->unk40[3].unkAC)
                sp04[3] -= 120;
            var->unk0 = sub_0812DBB4(sp04[0], sp04[1], sp04[2], sp04[3], sp10);
            gBgScrollRegs[0][0] = 8;
            gBgScrollRegs[0][1] = 0x58;
            gBgScrollRegs[1][0] = 8;
            gBgScrollRegs[1][1] = 0x58;
            gBgScrollRegs[2][0] = 0;
            gBgScrollRegs[2][1] = 0;
            var->unk8[0] = 0;
            var->unk8[1] = 0;
        }
    }
    gBgScrollRegs[0][0] = 8 - (var->unk8[0] >> 3);
    gBgScrollRegs[0][1] = 0x58 - (var->unk8[1] >> 3);
    gBgScrollRegs[1][0] = 8 - (var->unk8[0] >> 3) - (var->unk8[0] >> 6);
    gBgScrollRegs[1][1] = 0x58 - (var->unk8[1] >> 3) - (var->unk8[1] >> 6);
    if (var->unk5F0 & 0x40) {
        u16 a = Rand16() & 7, b = Rand16() & 7;

        gBgScrollRegs[0][0] += gUnk_08364CCA[a];
        gBgScrollRegs[0][1] += gUnk_08364CCA[b];
        gBgScrollRegs[1][0] += gUnk_08364CCA[a];
        gBgScrollRegs[1][1] += gUnk_08364CCA[b];
    }
    sub_081288DC(&var->unk40[0].unk0[0]);
    sub_081288DC(&var->unk40[1].unk0[0]);
    sub_081288DC(&var->unk40[2].unk0[0]);
    sub_081288DC(&var->unk40[3].unk0[0]);
    sub_081288DC(&var->unk40[0].unk0[1]);
    sub_081288DC(&var->unk40[1].unk0[1]);
    sub_081288DC(&var->unk40[2].unk0[1]);
    sub_081288DC(&var->unk40[3].unk0[1]);
    if (var->unk564[1].unk34 & 0x10) {
        sub_081288DC(&var->unk564[1]);
        sub_081288DC(&var->unk564[0]);
    }
}

void sub_0812BE74(struct Unk_0812A77C_40 *a1) {
    s32 r2 = abs(a1->unkA8 - a1->unkAA);

    a1->unkA0 = 1;
    if (a1->unkA8 > a1->unkAA) {
        if (r2 > 0x30) return;
        if (r2 > 0x20)
            a1->unkA0 = 2;
        else
            a1->unkA0 = 3;
    }
    else {
        if (r2 == 0)
            a1->unkA0 = 5;
        else if (r2 <= 0x10)
            a1->unkA0 = 4;
        else if (r2 <= 0x20)
            a1->unkA0 = 3;
        else if (r2 <= 0x30)
            a1->unkA0 = 2;
        else
            a1->unkA0 = 1;
    }
}

void sub_0812BEE0(void) {
    struct Unk_0812A77C *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    if (sub_0812E6C8(TaskGetStructPtr(var->unk0))) {
        if (!(var->unk5F0 & 2)) {
            if (var->unk40[0].unk9C >= 8000)
                CreatePauseFade(0x10, 1);
            else if (var->unk40[1].unk9C >= 8000 || var->unk40[2].unk9C >= 8000 || var->unk40[3].unk9C >= 8000)
                CreatePauseFadeSetBldCnt(0x10, 1);
            else
                CreatePauseFade(0x10, 1);
            var->unk5F0 |= 2;
        }
        if (!sub_0812A304()) {
            u32 r2;

            TaskDestroy(var->unk0);
            var->unk0 = NULL;
            var->unk5F0 &= ~2;
            r2 = 0;
            if (var->unk40[0].unk9C >= 8000)
                r2 = 1;
            if (var->unk40[1].unk9C >= 8000)
                ++r2;
            if (var->unk40[2].unk9C >= 8000)
                ++r2;
            if (var->unk40[3].unk9C >= 8000)
                ++r2;
            gDispCnt |= DISPCNT_BG0_ON | DISPCNT_BG1_ON;
            if (r2) {
                var->unk5F2 = 0;
                if (var->unk40[0].unk9C >= 8000) {
                    gDispCnt &= ~DISPCNT_BG2_ON;
                    sub_0812C168(var);
                    if (gUnk_0203AD10 & 2) {
                        gCurTask->main = sub_0812C29C;
                        sub_0812E194(10, 0x10, var->unk40[0].unk9C - 120);
                        sub_0812E194(70, 0x10, var->unk40[1].unk9C - 120);
                        sub_0812E194(130, 0x10, var->unk40[2].unk9C - 120);
                        sub_0812E194(190, 0x10, var->unk40[3].unk9C - 120);
                    }
                    else {
                        gCurTask->main = sub_0812C29C;
                    }
                }
                else {
                    gCurTask->main = sub_0812C29C;
                    sub_0812E194(10, 0x10, var->unk40[0].unk9C - 120);
                    sub_0812E194(70, 0x10, var->unk40[1].unk9C - 120);
                    sub_0812E194(130, 0x10, var->unk40[2].unk9C - 120);
                    sub_0812E194(190, 0x10, var->unk40[3].unk9C - 120);
                }
            }
            else {
                sub_0812C490(var);
                gCurTask->main = sub_0812C63C;
            }
        }
    }
    if (var->unk40[0].unk9C < 8000)
        sub_0812E6E4(0);
}

static inline struct Unk_08128F44_4 *BeYourself(struct Unk_08128F44_4 *a1) { // for matching
    return a1;
}

void sub_0812C168(struct Unk_0812A77C *a1) {
    u8 i;
    struct Unk_08128F44_4 *var;

    CpuCopy32(gUnk_08370EC8, (void *)0x600E000, sizeof(gUnk_08370EC8));
    CpuCopy32(gUnk_083716C8, (void *)0x600E800, sizeof(gUnk_083716C8));
    gDispCnt &= ~DISPCNT_BG2_ON;
    gBgCntRegs[0] = BGCNT_PRIORITY(2) | BGCNT_TXT256x256 | BGCNT_CHARBASE(1) | BGCNT_SCREENBASE(0x1C);
    gBgCntRegs[1] = BGCNT_PRIORITY(2) | BGCNT_TXT256x256 | BGCNT_CHARBASE(1) | BGCNT_SCREENBASE(0x1D);
    gBgScrollRegs[0][0] = 8;
    gBgScrollRegs[0][1] = 0;
    gBgScrollRegs[1][0] = 8;
    gBgScrollRegs[1][1] = 0;
    gBgScrollRegs[2][0] = 0;
    gBgScrollRegs[2][1] = 0;
    a1->unk5F2 = 0;
    for (i = 0; i < 4; ++i) {
        CpuFill32(0, &a1->unk410[i], sizeof(a1->unk410[i]));
        var = BeYourself(&a1->unk410[i]);
        var->unk0.tilesVram = 0x6010000;
        var->unk0.unk14 = 0x480;
        var->unk0.animId = gUnk_08364FCC[gLanguage].animId;
        var->unk0.variant = gUnk_08364FCC[gLanguage].variant;
        var->unk0.unk16 = 0;
        var->unk0.unk1B = 0xFF;
        var->unk0.unk1C = 0x10;
        var->unk0.palId = 4;
        var->unk0.x = gUnk_08364FE4[i] >> 2;
        var->unk0.y = 0;
        var->unk0.unk8 = 0xC0000;
        var->unk28 = gUnk_08364FE4[i];
        var->unk2C = 0;
        var->unk30 = 0;
        var->unk32 = 0;
        var->unk34 = 0x10;
        var->unk36 = 0;
        var->unk38 = NULL;
        var->unk3C = NULL;
        var->unk40 = NULL;
    }
}

void sub_0812C29C(void) {
    struct Unk_0812A77C *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    sub_0812E194(10, 0x10, var->unk40[0].unk9C - 120);
    sub_0812E194(70, 0x10, var->unk40[1].unk9C - 120);
    sub_0812E194(130, 0x10, var->unk40[2].unk9C - 120);
    sub_0812E194(190, 0x10, var->unk40[3].unk9C - 120);
    if (!(var->unk5F0 & 2) && !sub_0812A304()) {
        if (var->unk40[0].unk9C >= 8000) {
            CreatePauseFade(-0x10, 1);
            m4aSongNumStart(561);
        }
        else {
            CreatePauseFadeSetBldCnt(-0x10, 1);
        }
        var->unk5F0 |= 2;
    }
    if (var->unk5F2 > 120) {
        if (!sub_0812A304()) {
            var->unk5F0 &= ~2;
            gDispCnt &= ~DISPCNT_BG2_ON;
            gBgCntRegs[0] = BGCNT_PRIORITY(2) | BGCNT_TXT256x256 | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(0x1C);
            gBgCntRegs[1] = BGCNT_PRIORITY(2) | BGCNT_TXT256x256 | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(0x1D);
            sub_0812C490(var);
            gCurTask->main = sub_0812C63C;
        }
    }
    else {
        if (var->unk5F2 == 120) {
            CreatePauseFade(0x10, 1);
            ++var->unk5F2;
        }
        else {
            ++var->unk5F2;
        }
    }
    if (var->unk5F2 == 30)
        m4aSongNumStart(561);
    if (var->unk5F2 > 30) {
        if (var->unk40[0].unk9C >= 8000) {
            sub_081288DC(var->unk410);
            if (var->unk40[1].unk9C >= 8000)
                sub_081288DC(&var->unk410[1]);
            if (var->unk40[2].unk9C >= 8000)
                sub_081288DC(&var->unk410[2]);
            if (var->unk40[3].unk9C >= 8000)
                sub_081288DC(&var->unk410[3]);
        }
    }
    if (var->unk40[0].unk9C < 8000)
        sub_0812E6E4(0);
}

void sub_0812C490(struct Unk_0812A77C *a1) {
    CpuCopy32(gUnk_0836EEC8, (void *)0x600E000, sizeof(gUnk_0836EEC8));
    CpuCopy32(gUnk_0836F6C8, (void *)0x600E800, sizeof(gUnk_0836F6C8));
    gDispCnt &= ~DISPCNT_BG2_ON;
    sub_0812C528(&a1->unk40[0], 0);
    sub_0812C528(&a1->unk40[1], 1);
    sub_0812C528(&a1->unk40[2], 2);
    sub_0812C528(&a1->unk40[3], 3);
    gBgScrollRegs[0][0] = 8;
    gBgScrollRegs[0][1] = 0x58;
    gBgScrollRegs[1][0] = 8;
    gBgScrollRegs[1][1] = 0x58;
    gBgScrollRegs[2][0] = 0;
    gBgScrollRegs[2][1] = 0;
    a1->unk5F2 = 30;
}

void sub_0812C528(struct Unk_0812A77C_40 *a1, u8 a2) {
    if (a1->unkAC) {
        sub_0812E764(&a1->unk0[0].unk0, 4);
        switch (a2) {
        case 0:
            a1->unk0[0].unk28 = 120;
            a1->unk0[0].unk2C = 0x228;
            break;
        case 1:
            a1->unk0[0].unk28 = 360;
            a1->unk0[0].unk2C = 0x228;
            break;
        case 2:
            a1->unk0[0].unk28 = 600;
            a1->unk0[0].unk2C = 0x228;
            break;
        case 3:
            a1->unk0[0].unk28 = 840;
            a1->unk0[0].unk2C = 0x228;
            break;
        }
    }
    else {
        sub_0812E764(&a1->unk0[0].unk0, 3);
        switch (a2) {
        case 0:
            a1->unk0[0].unk28 = 120;
            a1->unk0[0].unk2C = 0x1A8;
            break;
        case 1:
            a1->unk0[0].unk28 = 360;
            a1->unk0[0].unk2C = 0x1A8;
            break;
        case 2:
            a1->unk0[0].unk28 = 600;
            a1->unk0[0].unk2C = 0x1A8;
            break;
        case 3:
            a1->unk0[0].unk28 = 840;
            a1->unk0[0].unk2C = 0x1A8;
            break;
        }
    }
    a1->unk0[1].unk0.palId = 6;
    switch (gLanguage) { // all the same
    case LANGUAGE_JAPANESE:
        a1->unk0[1].unk0.animId = 0x345;
        a1->unk0[1].unk0.variant = 0x12;
        a1->unk0[1].unk0.unk1B = 0xFF;
        break;
    case LANGUAGE_ENGLISH:
        a1->unk0[1].unk0.animId = 0x345;
        a1->unk0[1].unk0.variant = 0x12;
        a1->unk0[1].unk0.unk1B = 0xFF;
        break;
    case LANGUAGE_GERMAN:
        a1->unk0[1].unk0.animId = 0x345;
        a1->unk0[1].unk0.variant = 0x12;
        a1->unk0[1].unk0.unk1B = 0xFF;
        break;
    case LANGUAGE_FRENCH:
        a1->unk0[1].unk0.animId = 0x345;
        a1->unk0[1].unk0.variant = 0x12;
        a1->unk0[1].unk0.unk1B = 0xFF;
        break;
    case LANGUAGE_SPANISH:
        a1->unk0[1].unk0.animId = 0x345;
        a1->unk0[1].unk0.variant = 0x12;
        a1->unk0[1].unk0.unk1B = 0xFF;
        break;
    case LANGUAGE_ITALIAN:
        a1->unk0[1].unk0.animId = 0x345;
        a1->unk0[1].unk0.variant = 0x12;
        a1->unk0[1].unk0.unk1B = 0xFF;
        break;
    }
    switch (a2) { // all the same
    case 0:
        a1->unk0[1].unk2C = 0x248;
        break;
    case 1:
        a1->unk0[1].unk2C = 0x248;
        break;
    case 2:
        a1->unk0[1].unk2C = 0x248;
        break;
    case 3:
        a1->unk0[1].unk2C = 0x248;
        break;
    }
}

void sub_0812C63C(void) {
    struct Unk_0812A77C *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    if (!sub_0812A304()) {
        CreatePauseFade(-8, 1);
        gCurTask->main = sub_0812C814;
        var->unk5F0 |= 2;
        var->unk40[0].unk8C = sub_0812EFFC(120, 4);
        var->unk40[1].unk8C = sub_0812EFFC(360, 4);
        var->unk40[2].unk8C = sub_0812EFFC(600, 4);
        var->unk40[3].unk8C = sub_0812EFFC(840, 4);
    }
    if (!var->unk40[0].unkAC) {
        if (var->unk40[0].unk9C >= 8000)
            m4aSongNumStart(34);
        else
            m4aSongNumStart(19);
    }
    else {
        m4aSongNumStart(32);
    }
    sub_0812E194(10, 0x10, var->unk40[0].unk9C - 120);
    sub_0812E194(70, 0x10, var->unk40[1].unk9C - 120);
    sub_0812E194(130, 0x10, var->unk40[2].unk9C - 120);
    sub_0812E194(190, 0x10, var->unk40[3].unk9C - 120);
    sub_0812E0C8(30, 0x30, var->unk40[0].unkAC);
    sub_0812E0C8(90, 0x30, var->unk40[1].unkAC);
    sub_0812E0C8(150, 0x30, var->unk40[2].unkAC);
    sub_0812E0C8(210, 0x30, var->unk40[3].unkAC);
    sub_081288DC(&var->unk40[0].unk0[0]);
    sub_081288DC(&var->unk40[1].unk0[0]);
    sub_081288DC(&var->unk40[2].unk0[0]);
    sub_081288DC(&var->unk40[3].unk0[0]);
    if (!var->unk40[0].unkAC)
        sub_081288DC(&var->unk40[0].unk0[1]);
    if (!var->unk40[1].unkAC)
        sub_081288DC(&var->unk40[1].unk0[1]);
    if (!var->unk40[2].unkAC)
        sub_081288DC(&var->unk40[2].unk0[1]);
    if (!var->unk40[3].unkAC)
        sub_081288DC(&var->unk40[3].unk0[1]);
}

void sub_0812C814(void) {
    struct Unk_0812A77C *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    if (!sub_0812A304()) {
        if (!var->unk4) {
            u16 unk = gUnk_0203AD10 & 2 ? gUnk_020382D0.unk8[1][0] : gPressedKeys;

            if (unk & 1) {
                if (gUnk_0203AD3C)
                    var->unk4 = sub_08128F44(gUnk_08364ACC[gLanguage], 0xD, 0xE, 0x50, 0x32, 1);
                else
                    var->unk4 = sub_08128F44(gUnk_08364ACC[gLanguage], 0xD, 0xE, 0x50, 0x32, 0);
            }
        }
        else {
            struct Unk_08128F44 *var2 = TaskGetStructPtr(var->unk4);

            if (sub_0812A328(var2)) {
                TaskDestroy(var->unk40[0].unk8C);
                TaskDestroy(var->unk40[1].unk8C);
                TaskDestroy(var->unk40[2].unk8C);
                TaskDestroy(var->unk40[3].unk8C);
                CreatePauseFade(4, 1);
                var->unk5F4 = var2->unk2AD;
                if (var2->unk2AC & 0x10)
                    gCurTask->main = sub_0812CA84;
                else
                    gCurTask->main = sub_0812CBDC;
            }
        }
    }
    sub_0812E194(10, 0x10, var->unk40[0].unk9C - 120);
    sub_0812E194(70, 0x10, var->unk40[1].unk9C - 120);
    sub_0812E194(130, 0x10, var->unk40[2].unk9C - 120);
    sub_0812E194(190, 0x10, var->unk40[3].unk9C - 120);
    sub_0812E0C8(30, 0x30, var->unk40[0].unkAC);
    sub_0812E0C8(90, 0x30, var->unk40[1].unkAC);
    sub_0812E0C8(150, 0x30, var->unk40[2].unkAC);
    sub_0812E0C8(210, 0x30, var->unk40[3].unkAC);
    sub_081288DC(&var->unk40[0].unk0[0]);
    sub_081288DC(&var->unk40[1].unk0[0]);
    sub_081288DC(&var->unk40[2].unk0[0]);
    sub_081288DC(&var->unk40[3].unk0[0]);
    if (!var->unk40[0].unkAC)
        sub_081288DC(&var->unk40[0].unk0[1]);
    if (!var->unk40[1].unkAC)
        sub_081288DC(&var->unk40[1].unk0[1]);
    if (!var->unk40[2].unkAC)
        sub_081288DC(&var->unk40[2].unk0[1]);
    if (!var->unk40[3].unkAC)
        sub_081288DC(&var->unk40[3].unk0[1]);
}

void sub_0812CA84(void) {
    struct Unk_0812A77C *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    if (!sub_0812A304()) {
        m4aMPlayAllStop();
        gCurTask->main = sub_0812A8F0;
        TaskDestroy(var->unk4);
        var->unk4 = NULL;
    }
    sub_0812E194(10, 0x10, var->unk40[0].unk9C - 120);
    sub_0812E194(70, 0x10, var->unk40[1].unk9C - 120);
    sub_0812E194(130, 0x10, var->unk40[2].unk9C - 120);
    sub_0812E194(190, 0x10, var->unk40[3].unk9C - 120);
    sub_0812E0C8(30, 0x30, var->unk40[0].unkAC);
    sub_0812E0C8(90, 0x30, var->unk40[1].unkAC);
    sub_0812E0C8(150, 0x30, var->unk40[2].unkAC);
    sub_0812E0C8(210, 0x30, var->unk40[3].unkAC);
    sub_081288DC(&var->unk40[0].unk0[0]);
    sub_081288DC(&var->unk40[1].unk0[0]);
    sub_081288DC(&var->unk40[2].unk0[0]);
    sub_081288DC(&var->unk40[3].unk0[0]);
    if (!var->unk40[0].unkAC)
        sub_081288DC(&var->unk40[0].unk0[1]);
    if (!var->unk40[1].unkAC)
        sub_081288DC(&var->unk40[1].unk0[1]);
    if (!var->unk40[2].unkAC)
        sub_081288DC(&var->unk40[2].unk0[1]);
    if (!var->unk40[3].unkAC)
        sub_081288DC(&var->unk40[3].unk0[1]);
}

void sub_0812CBDC(void) {
    struct Unk_0812A77C *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    if (!sub_0812A304()) {
        TaskDestroy(var->unk4);
        var->unk4 = NULL;
        if (gUnk_0203AD10 & 2)
            gUnk_020382D0.unk4 &= ~2;
        var->unk5F6 = 0;
        gCurTask->main = sub_0812E51C;
    }
    sub_0812E194(10, 0x10, var->unk40[0].unk9C - 120);
    sub_0812E194(70, 0x10, var->unk40[1].unk9C - 120);
    sub_0812E194(130, 0x10, var->unk40[2].unk9C - 120);
    sub_0812E194(190, 0x10, var->unk40[3].unk9C - 120);
    sub_0812E0C8(30, 0x30, var->unk40[0].unkAC);
    sub_0812E0C8(90, 0x30, var->unk40[1].unkAC);
    sub_0812E0C8(150, 0x30, var->unk40[2].unkAC);
    sub_0812E0C8(210, 0x30, var->unk40[3].unkAC);
    sub_081288DC(&var->unk40[0].unk0[0]);
    sub_081288DC(&var->unk40[1].unk0[0]);
    sub_081288DC(&var->unk40[2].unk0[0]);
    sub_081288DC(&var->unk40[3].unk0[0]);
    if (!var->unk40[0].unkAC)
        sub_081288DC(&var->unk40[0].unk0[1]);
    if (!var->unk40[1].unkAC)
        sub_081288DC(&var->unk40[1].unk0[1]);
    if (!var->unk40[2].unkAC)
        sub_081288DC(&var->unk40[2].unk0[1]);
    if (!var->unk40[3].unkAC)
        sub_081288DC(&var->unk40[3].unk0[1]);
}

bool32 sub_0812CD5C(struct Unk_0812A77C_40 *a1, u8 a2) {
    bool32 ret = FALSE;
    u16 r = Rand16() & 0xF;

    if (a1->unk90 & 0x10) {
        if (a1->unk9E == a1->unkAD) {
            a1->unkAD = gUnk_08365114[a2][r];
            ret = TRUE;
        }
    }
    else if (a1->unk90 & 0x20) {
        a1->unk90 &= ~0x20;
    }
    return ret;
}

void sub_0812CDD4(struct Unk_0812A77C *a1) {
    u8 i;

    for (i = 0; i < 4; ++i) {
        u8 unk = a1->unk10[i];

        if (a1->unk40[i].unk90 & 1) {
            a1->unk40[i].unk98 = a1->unk40[i].unk96;
            a1->unk40[i].unk96 = sub_0812CD5C(&a1->unk40[i], a1->unk5F4);
            a1->unk40[i].unk98 = a1->unk40[i].unk98; // required for matching
            a1->unk40[i].unk94 = (a1->unk40[i].unk98 ^ a1->unk40[i].unk96) & a1->unk40[i].unk96;
            a1->unk40[i].unk9A = 0;
        }
        else if (gUnk_0203AD10 & 2) {
            a1->unk40[i].unk98 = a1->unk40[i].unk96;
            a1->unk40[i].unk96 = gUnk_020382D0.unk8[0][unk];
            a1->unk40[i].unk94 = gUnk_020382D0.unk8[1][unk];
            a1->unk40[i].unk9A = gUnk_020382D0.unk8[2][unk];
        }
        else {
            a1->unk40[i].unk98 = gPrevInput;
            a1->unk40[i].unk96 = gInput;
            a1->unk40[i].unk94 = gPressedKeys;
            a1->unk40[i].unk9A = gReleasedKeys;
        }
    }
}

void sub_0812CED8(struct Unk_0812A77C_40 *a1, u8 a2 __attribute__((unused))) {
    if (a1->unk92) {
        if (--a1->unk92 < 2)
            a1->unk9E = 0;
    }
    else {
        if (a1->unk94 & 1) {
            a1->unk9C += 0xA * a1->unk9E;
            if (a1->unk9C > 0x640)
                a1->unk9C = 0x640;
            a1->unk92 = 0x2D;
            a1->unkA6 |= 0x10;
        }
        if (a1->unkA6 & 1) {
            if (--a1->unk9E < 1)
                a1->unkA6 ^= 1;
        }
        else {
            if (++a1->unk9E > 0x28)
                a1->unkA6 ^= 1;
        }
    }
}

void sub_0812CF80(struct Unk_0812A77C_40 *a1, struct Unk_0812A77C *a2) {
    if (a1->unkA6 & 2 && a1->unk94 & 1) {
        sub_0812BE74(a1);
        if (a1->unkA0 == 5)
            m4aSongNumStart(553);
        else
            m4aSongNumStart(552);
        a2->unk564[0].unk34 &= ~0x800;
        a1->unkA6 |= 4;
        a1->unkA6 &= ~2;
        if (a2->unk564[0].unk2C != a2->unk564[1].unk2C) {
            struct Sprite *sprite = &a2->unk564[0].unk0;

            sprite->animId = gUnk_08365054[gLanguage][2].animId;
            sprite->variant = gUnk_08365054[gLanguage][2].variant;
            sprite->unk1B = 0xFF;
        }
        else {
            struct Sprite *sprite = &a2->unk564[0].unk0;

            sprite->animId = gUnk_08365054[gLanguage][3].animId;
            sprite->variant = gUnk_08365054[gLanguage][3].variant;
            sprite->unk1B = 0xFF;
        }
    }
}

void sub_0812D060(void) {
    gBgCntRegs[2] = BGCNT_PRIORITY(1) | BGCNT_TXT256x256 | BGCNT_CHARBASE(3) | BGCNT_SCREENBASE(30);
    gBgScrollRegs[2][0] = 0;
    gBgScrollRegs[2][1] = -0x46;
    gDispCnt |= DISPCNT_WIN0_ON | DISPCNT_BG2_ON;
    gWinRegs[0] = WIN_RANGE(0x10, 0x18);
    gWinRegs[2] = WIN_RANGE(0x10, 0x38);
    gWinRegs[4] = WIN_RANGE(0, 4);
    gWinRegs[5] = WIN_RANGE(0, 0x3B);
    CpuFill32(0x22222222, (void *)0x600C000, 0x20);
    CpuFill32(0x11111111, (void *)0x600C020, 0x20);
    DmaFill32(3, 0xF001F001, (void *)0x600F000, 0x400);
    DmaFill32(3, 0xF000F000, (void *)0x600F400, 0x400);
}

void sub_0812D124(s16 a1, s16 a2, struct Unk_0812A77C_40 *a3) {
    u8 r4 = a1 / 100;

    if (r4 > 0x10) r4 = 0x10;
    gBgScrollRegs[2][1] = a2 - 0x38;
    if (a2 > 0x27) r4 = 0x11;
    if (a3->unk94 & 1 && a3->unkA6 & 0x10) {
        a3->unkA6 &= ~0x10;
        if (a2 > 0x27)
            m4aSongNumStart(553);
        else
            m4aSongNumStart(552);
    }
    if (gUnk_03002440 & 0x10000)
        sub_08158334(gUnk_0836535C + r4, 0xF1, 1);
    else {
        DmaCopy16(3, gUnk_0836535C + r4, gUnk_030038A0 + 0x71, 1 * sizeof(u16));
        gUnk_03002440 |= 1;
    }
}

struct Task *sub_0812D1EC(struct Unk_0812A77C_40 *a1, u8 a2) {
    struct Task *t = TaskCreate(sub_0812D3AC, sizeof(struct Unk_0812D1EC), 0x100, TASK_USE_IWRAM, NULL);
    struct Unk_0812D1EC *tmp = TaskGetStructPtr(t), *var = tmp;

    var->unk0.unk0 = a1;
    var->unk0.unk50 = 0;
    var->unk0.unk52 = 2;
    var->unk0.unk48 = 0;
    var->unk0.unk4C = 0;
    if (var->unk0.unk52 & 2) {
        ({ CpuFill32(0, &var->unk0.unk4, sizeof(struct Unk_08128F44_4)); }); // for sharing the filler with another CpuSet call
        var->unk0.unk4.unk0.tilesVram = 0x6010000;
        var->unk0.unk4.unk0.unk14 = 0x4C0;
        var->unk0.unk4.unk0.animId = gUnk_08364D8C[gLanguage][0].animId;
        var->unk0.unk4.unk0.variant = gUnk_08364D8C[gLanguage][0].variant;
        var->unk0.unk4.unk0.unk16 = 0;
        var->unk0.unk4.unk0.unk1B = 0xFF;
        var->unk0.unk4.unk0.unk1C = 0x10;
        var->unk0.unk4.unk0.palId = 5;
        var->unk0.unk4.unk0.x = (var->unk0.unk48 + var->unk0.unk0->unk0[0].unk28) >> 2;
        var->unk0.unk4.unk0.y = (var->unk0.unk4C + var->unk0.unk0->unk0[0].unk2C) >> 2;
        var->unk0.unk4.unk0.unk8 = 0xC0000;
        var->unk0.unk4.unk28 = var->unk0.unk48 + var->unk0.unk0->unk0[0].unk28;
        var->unk0.unk4.unk2C = var->unk0.unk4C + var->unk0.unk0->unk0[0].unk2C;
        var->unk0.unk4.unk30 = 0;
        var->unk0.unk4.unk32 = 0;
        var->unk0.unk4.unk34 = 0x810;
        var->unk0.unk4.unk36 = 0;
        var->unk0.unk4.unk38 = NULL;
        var->unk0.unk4.unk3C = NULL;
        var->unk0.unk4.unk40 = NULL;
    }
    else {
        CpuFill32(0, &var->unk0.unk4, sizeof(struct Unk_08128F44_4));
        var->unk0.unk4.unk0.tilesVram = 0x6010000;
        var->unk0.unk4.unk0.unk14 = 0x4C0;
        var->unk0.unk4.unk0.animId = gUnk_08364D8C[gLanguage][0].animId;
        var->unk0.unk4.unk0.variant = gUnk_08364D8C[gLanguage][0].variant;
        var->unk0.unk4.unk0.unk16 = 0;
        var->unk0.unk4.unk0.unk1B = 0xFF;
        var->unk0.unk4.unk0.unk1C = 0x10;
        var->unk0.unk4.unk0.palId = 5;
        var->unk0.unk4.unk0.x = var->unk0.unk48 >> 2;
        var->unk0.unk4.unk0.y = var->unk0.unk4C >> 2;
        var->unk0.unk4.unk0.unk8 = 0xC0000;
        var->unk0.unk4.unk28 = var->unk0.unk48;
        var->unk0.unk4.unk2C = var->unk0.unk4C;
        var->unk0.unk4.unk30 = 0;
        var->unk0.unk4.unk32 = 0;
        var->unk0.unk4.unk34 = 0x810;
        var->unk0.unk4.unk36 = 0;
        var->unk0.unk4.unk38 = NULL;
        var->unk0.unk4.unk3C = NULL;
        var->unk0.unk4.unk40 = NULL;
    }
    var->unk0.unk4.unk38 = a1->unk0[0].unk38;
    if (a2 == 2 || a2 == 3) {
        var->unk0.unk4.unk34 |= 1;
    }
    var->unk54 = a1;
    var->unk58 = 0;
    var->unk59 = 0;
    return t;
}

void sub_0812D3AC(void) {
    struct Unk_0812D1EC *tmp = TaskGetStructPtr(gCurTask), *var = tmp;
    u8 r3;

    if (var->unk54->unk9C >= 1500) {
        var->unk59 |= 2;
        r3 = 2;
    }
    else if (var->unk54->unk9C >= 1000)
        r3 = 2;
    else if (var->unk54->unk9C >= 500)
        r3 = 1;
    else
        r3 = 0;
    if (var->unk59 & 1) {
        if (var->unk0.unk4.unk34 & 0x200) {
            var->unk0.unk4.unk34 |= 0x800;
            var->unk59 &= ~1;
            var->unk0.unk4.unk0.animId = gUnk_08364D8C[gLanguage][2 * var->unk58 + 1].animId;
            var->unk0.unk4.unk0.variant = gUnk_08364D8C[gLanguage][2 * var->unk58 + 1].variant;
            var->unk0.unk4.unk0.unk1B = 0xFF;
        }
    }
    else {
        if (var->unk58 < r3) {
            var->unk59 |= 1;
            var->unk58 = r3;
            var->unk0.unk4.unk0.animId = gUnk_08364D8C[gLanguage][2 * var->unk58].animId;
            var->unk0.unk4.unk0.variant = gUnk_08364D8C[gLanguage][2 * var->unk58].variant;
            var->unk0.unk4.unk0.unk1B = 0xFF;
            var->unk0.unk4.unk34 &= ~0x800;
        }
    }
    sub_0812A2C0(&var->unk0);
}

struct Task *sub_0812D4F4(void) {
    struct Task *t = TaskCreate(sub_0812D988, sizeof(struct Unk_0812D4F4), 0x100, TASK_USE_IWRAM, nullsub_31);
    struct Unk_0812D4F4 *var = TaskGetStructPtr(t);
#ifndef NONMATCHING
    register struct Unk_08128F44_4 *r4 asm("r4"), *r6; // probably the same issue as sub_08128F44
#else
    struct Unk_08128F44_4 *r4, *r6;
#endif

    var->unk110 = 1;
    var->unk111 = 0;
    var->unk112 = 0;
    var->unk113 = 0;
    var->unk114 = 0;
    CpuFill32(0, &var->unk0[0], sizeof(struct Unk_08128F44_4));
    var->unk0[0].unk0.tilesVram = 0x6010000;
    var->unk0[0].unk0.unk14 = 0x340;
    var->unk0[0].unk0.animId = gUnk_08364E1C[gLanguage][var->unk110].animId;
    var->unk0[0].unk0.variant = gUnk_08364E1C[gLanguage][var->unk110].variant;
    var->unk0[0].unk0.unk16 = 0;
    var->unk0[0].unk0.unk1B = 0xFF;
    var->unk0[0].unk0.unk1C = 0x10;
    var->unk0[0].unk0.palId = 0xC;
    var->unk0[0].unk0.x = 0x68;
    var->unk0[0].unk0.y = 0x10;
    var->unk0[0].unk0.unk8 = 0xC0000;
    var->unk0[0].unk28 = 0x1A0;
    var->unk0[0].unk2C = 0x40;
    var->unk0[0].unk30 = 0;
    var->unk0[0].unk32 = 0;
    var->unk0[0].unk34 = 0x10;
    var->unk0[0].unk36 = 0;
    var->unk0[0].unk38 = NULL;
    var->unk0[0].unk3C = NULL;
    var->unk0[0].unk40 = NULL;
    CpuFill32(0, &var->unk0[1], sizeof(struct Unk_08128F44_4));
    var->unk0[1].unk0.tilesVram = 0x6010000;
    var->unk0[1].unk0.unk14 = 0x340;
    var->unk0[1].unk0.animId = gUnk_08364E1C[gLanguage][var->unk111].animId;
    var->unk0[1].unk0.variant = gUnk_08364E1C[gLanguage][var->unk111].variant;
    var->unk0[1].unk0.unk16 = 0;
    var->unk0[1].unk0.unk1B = 0xFF;
    var->unk0[1].unk0.unk1C = 0x10;
    var->unk0[1].unk0.palId = 0xC;
    var->unk0[1].unk0.x = 0x74;
    var->unk0[1].unk0.y = 0x10;
    var->unk0[1].unk0.unk8 = 0xC0000;
    var->unk0[1].unk28 = 0x1D0;
    var->unk0[1].unk2C = 0x40;
    var->unk0[1].unk30 = 0;
    var->unk0[1].unk32 = 0;
    var->unk0[1].unk34 = 0x10;
    var->unk0[1].unk36 = 0;
    var->unk0[1].unk38 = NULL;
    var->unk0[1].unk3C = NULL;
    var->unk0[1].unk40 = NULL;
    CpuFill32(0, r4 = &var->unk0[2], sizeof(struct Unk_08128F44_4));
    r4->unk0.tilesVram = 0x6010000;
    r4->unk0.unk14 = 0x340;
    r4->unk0.animId = gUnk_08364E1C[gLanguage][0xA].animId;
    r4->unk0.variant = gUnk_08364E1C[gLanguage][0xA].variant;
    r4->unk0.unk16 = 0;
    r4->unk0.unk1B = 0xFF;
    r4->unk0.unk1C = 0x10;
    r4->unk0.palId = 0xC;
    r4->unk0.x = 0x7E;
    r4->unk0.y = 0x10;
    r4->unk0.unk8 = 0xC0000;
    r4->unk28 = 0x1F8;
    r4->unk2C = 0x40;
    r4->unk30 = 0;
    r4->unk32 = 0;
    r4->unk34 = 0x10;
    r4->unk36 = 0;
    r4->unk38 = NULL;
    r4->unk3C = NULL;
    r4->unk40 = NULL;
    CpuFill32(0, r4 = &var->unk0[3], sizeof(struct Unk_08128F44_4));
    r4->unk0.tilesVram = 0x6010000;
    r4->unk0.unk14 = 0x340;
    r4->unk0.animId = gUnk_08364E1C[gLanguage][var->unk112].animId;
    r4->unk0.variant = gUnk_08364E1C[gLanguage][var->unk112].variant;
    r4->unk0.unk16 = 0;
    r4->unk0.unk1B = 0xFF;
    r4->unk0.unk1C = 0x10;
    r4->unk0.palId = 0xC;
    r4->unk0.x = 0x8C;
    r4->unk0.y = 0x10;
    r4->unk0.unk8 = 0xC0000;
    r4->unk28 = 0x230;
    r4->unk2C = 0x40;
    r4->unk30 = 0;
    r4->unk32 = 0;
    r4->unk34 = 0x10;
    r4->unk36 = 0;
    r4->unk38 = NULL;
    r4->unk3C = NULL;
    r4->unk40 = NULL;
    CpuFill32(0, r4 = &var->unk118[0], sizeof(struct Unk_08128F44_4));
    r4->unk0.tilesVram = 0x6010000;
    r4->unk0.unk14 = 0x480;
    r4->unk0.animId = gUnk_08364F3C[gLanguage][3].animId;
    r4->unk0.variant = gUnk_08364F3C[gLanguage][3].variant;
    r4->unk0.unk16 = 0;
    r4->unk0.unk1B = 0xFF;
    r4->unk0.unk1C = 0x10;
    r4->unk0.palId = 0xB;
    r4->unk0.x = 0x7A;
    r4->unk0.y = 0x10;
    r4->unk0.unk8 = 0xC0000;
    r4->unk28 = 0x1E8;
    r4->unk2C = 0x40;
    r4->unk30 = 0;
    r4->unk32 = 0;
    r4->unk34 = 0x10;
    r4->unk36 = 0;
    r4->unk38 = NULL;
    r4->unk3C = NULL;
    r4->unk40 = NULL;
    CpuFill32(0, r4 = &var->unk118[3], sizeof(struct Unk_08128F44_4));
    r4->unk0.tilesVram = 0x6010000;
    r4->unk0.unk14 = 0x480;
    r4->unk0.animId = gUnk_08364F3C[gLanguage][2].animId;
    r4->unk0.variant = gUnk_08364F3C[gLanguage][2].variant;
    r4->unk0.unk16 = 0;
    r4->unk0.unk1B = 0xFF;
    r4->unk0.unk1C = 0x10;
    r4->unk0.palId = 0xB;
    r4->unk0.x = 0x10;
    r4->unk0.y = 0x10;
    r4->unk0.unk8 = 0xC0000;
    r4->unk28 = 0x40;
    r4->unk2C = 0x40;
    r4->unk30 = 0;
    r4->unk32 = 0;
    r4->unk34 = 0x10;
    r4->unk36 = 0;
    r4->unk38 = NULL;
    r4->unk3C = NULL;
    r4->unk40 = NULL;
    CpuFill32(0, r4 = &var->unk118[1], sizeof(struct Unk_08128F44_4));
    r4->unk0.tilesVram = 0x6010000;
    r4->unk0.unk14 = 0x480;
    r4->unk0.animId = gUnk_08364F3C[gLanguage][0].animId;
    r4->unk0.variant = gUnk_08364F3C[gLanguage][0].variant;
    r4->unk0.unk16 = 0;
    r4->unk0.unk1B = 0xFF;
    r4->unk0.unk1C = 0x10;
    r4->unk0.palId = 0xB;
    r4->unk0.x = 0x30;
    r4->unk0.y = 0x12;
    r4->unk0.unk8 = 0xC0000;
    r4->unk28 = 0xC0;
    r4->unk2C = 0x48;
    r4->unk30 = 0;
    r4->unk32 = 0;
    r4->unk34 = 0x810;
    r4->unk36 = 0;
    r4->unk38 = NULL;
    r4->unk3C = NULL;
    r4->unk40 = NULL;
    CpuFill32(0, r6 = &var->unk118[2], sizeof(struct Unk_08128F44_4));
    r6->unk0.tilesVram = 0x6010000;
    r6->unk0.unk14 = 0x480;
    r6->unk0.animId = gUnk_08364F3C[gLanguage][1].animId;
    r6->unk0.variant = gUnk_08364F3C[gLanguage][1].variant;
    r6->unk0.unk16 = 0;
    r6->unk0.unk1B = 0xFF;
    r6->unk0.unk1C = 0x10;
    r6->unk0.palId = 0xB;
    r6->unk0.x = 0x20;
    r6->unk0.y = 0x12;
    r6->unk0.unk8 = 0xC0000;
    r6->unk28 = 0x80;
    r6->unk2C = 0x48;
    r6->unk30 = 0;
    r6->unk32 = 0;
    r6->unk34 = 0x10;
    r6->unk36 = 0;
    r6->unk38 = NULL;
    r6->unk3C = NULL;
    r6->unk40 = NULL;
    return t;
}

void sub_0812D988(void) {
    struct Unk_0812D4F4 *tmp = TaskGetStructPtr(gCurTask), *var = tmp;
    struct Unk_08128F44_4 *r4;

    if (var->unk113++ > 1) {
        var->unk113 = 0;
        if (var->unk112-- < 1) {
            var->unk112 = 9;
            if (var->unk111-- < 1) {
                var->unk111 = 9;
                if (var->unk110-- < 1) {
                    var->unk110 = 0;
                    var->unk111 = 0;
                    var->unk112 = 0;
                    var->unk113 = 0xA;
                    gCurTask->main = sub_0812DB2C;
                }
            }
        }
    }
    var->unk0[0].unk0.animId = gUnk_08364E1C[gLanguage][var->unk110].animId;
    var->unk0[0].unk0.variant = gUnk_08364E1C[gLanguage][var->unk110].variant;
    var->unk0[0].unk0.unk1B = 0xFF;
    var->unk0[1].unk0.animId = gUnk_08364E1C[gLanguage][var->unk111].animId;
    var->unk0[1].unk0.variant = gUnk_08364E1C[gLanguage][var->unk111].variant;
    var->unk0[1].unk0.unk1B = 0xFF;
    r4 = &var->unk0[3];
    r4->unk0.animId = gUnk_08364E1C[gLanguage][var->unk112].animId;
    r4->unk0.variant = gUnk_08364E1C[gLanguage][var->unk112].variant;
    r4->unk0.unk1B = 0xFF;
    sub_081288DC(&var->unk0[0]);
    sub_081288DC(&var->unk0[1]);
    sub_081288DC(&var->unk0[2]);
    sub_081288DC(&var->unk0[3]);
    sub_081288DC(&var->unk118[0]);
    sub_081288DC(&var->unk118[1]);
    sub_081288DC(&var->unk118[2]);
    sub_081288DC(&var->unk118[3]);
}

void sub_0812DB2C(void) {
    struct Unk_0812D4F4 *var = TaskGetStructPtr(gCurTask);

    if (!var->unk113--)
        var->unk114 |= 2;
    sub_081288DC(&var->unk0[0]);
    sub_081288DC(&var->unk0[1]);
    sub_081288DC(&var->unk0[2]);
    sub_081288DC(&var->unk0[3]);
    sub_081288DC(&var->unk118[0]);
    sub_081288DC(&var->unk118[3]);
}

struct Task *sub_0812DBB4(s16 a1, s16 a2, s16 a3, s16 a4, bool8 a5) {
    struct Task *t = TaskCreate(sub_0812DC90, sizeof(struct Unk_0812DBB4), 0x100, TASK_USE_IWRAM, nullsub_32);
    struct Unk_0812DBB4 *var = TaskGetStructPtr(t);
    s16 max = 0; // intialization for matching

    max = max(max(max(a4, a3), a2), a1);
    var->unk20 = max;
    var->unk20 -= 120;
    var->unk22 = 0;
    var->unk24 = 0;
    var->unk26 = 1;
    var->unk28 = 0;
    var->unk0[0].unk0 = a1;
    var->unk0[0].unk2 = 0;
    var->unk0[0].unk4 = 0;
    var->unk0[1].unk0 = a2;
    var->unk0[1].unk2 = 0;
    var->unk0[1].unk4 = 0;
    var->unk0[2].unk0 = a3;
    var->unk0[2].unk2 = 0;
    var->unk0[2].unk4 = 0;
    var->unk0[3].unk0 = a4;
    var->unk0[3].unk2 = 0;
    var->unk0[3].unk4 = 0;
    if (a5) var->unk24 |= 0x10;
    return t;
}

void sub_0812DC90(void) {
    struct Unk_0812DBB4 *tmp = TaskGetStructPtr(gCurTask), *var = tmp;
    s16 v;

    var->unk26 = (var->unk20 - var->unk22) >> 6;
    if (var->unk26 > 0x10) {
        var->unk26 = 0x10;
        gDispCnt &= ~DISPCNT_BG0_ON;
    }
    else {
        gDispCnt |= DISPCNT_BG0_ON;
    }
    if (!var->unk26) {
        if (var->unk20 != var->unk22)
            var->unk26 = 1;
        else
            var->unk24 |= 0x20;
    }
    gBgScrollRegs[0][1] += var->unk26;
    gBgScrollRegs[1][1] += var->unk26;
    var->unk22 += var->unk26;
    gBgScrollRegs[2][1] += var->unk26;
    if (gBgScrollRegs[2][1] > 0x17) {
        gBgScrollRegs[2][1] = 0;
        if (var->unk26) {
            if (gDispCnt & DISPCNT_BG0_ON)
                m4aSongNumStart(561);
            else
                m4aSongNumStart(560);
        }
        v = (var->unk0[0].unk0 - var->unk0[0].unk2) >> 3;
        if (v >= 0x14)
            var->unk0[0].unk4 = 0x14;
        else
            var->unk0[0].unk4 = v;
        v = (var->unk0[1].unk0 - var->unk0[1].unk2) >> 3;
        if (v >= 0x14)
            var->unk0[1].unk4 = 0x14;
        else
            var->unk0[1].unk4 = v;
        v = (var->unk0[2].unk0 - var->unk0[2].unk2) >> 3;
        if (v >= 0x14)
            var->unk0[2].unk4 = 0x14;
        else
            var->unk0[2].unk4 = v;
        v = (var->unk0[3].unk0 - var->unk0[3].unk2) >> 3;
        if (v >= 0x14)
            var->unk0[3].unk4 = 0x14;
        else
            var->unk0[3].unk4 = v;
    }
    sub_0812E6E4(var->unk26);
    if (var->unk0[0].unk0 <= var->unk0[0].unk2 + var->unk26) {
        var->unk0[0].unk4 = 0;
        var->unk0[0].unk2 = var->unk0[0].unk0;
    }
    else {
        var->unk0[0].unk2 += var->unk26;
    }
    if (var->unk0[1].unk0 < var->unk0[1].unk2 + var->unk26) {
        var->unk0[1].unk4 = 0;
        var->unk0[1].unk2 = var->unk0[1].unk0;
    }
    else {
        var->unk0[1].unk2 += var->unk26;
    }
    if (var->unk0[2].unk0 < var->unk0[2].unk2 + var->unk26) {
        var->unk0[2].unk4 = 0;
        var->unk0[2].unk2 = var->unk0[2].unk0;
    }
    else {
        var->unk0[2].unk2 += var->unk26;
    }
    if (var->unk0[3].unk0 <= var->unk0[3].unk2 + var->unk26) {
        var->unk0[3].unk4 = 0;
        var->unk0[3].unk2 = var->unk0[3].unk0;
    }
    else {
        var->unk0[3].unk2 += var->unk26;
    }
    gUnk_03000530 = var;
    gUnk_03002470[gUnk_03006070++] = sub_0812DFD4;
    gUnk_03002440 |= 0x10;
    sub_0812E194(10, 0x10, var->unk0[0].unk2);
    sub_0812E194(70, 0x10, var->unk0[1].unk2);
    sub_0812E194(130, 0x10, var->unk0[2].unk2);
    sub_0812E194(190, 0x10, var->unk0[3].unk2);
    if (var->unk24 & 1) return;
    if (var->unk24 & 0x20)
        gCurTask->main = sub_0812DF14;
}

void sub_0812DF14(void) {
    struct Unk_0812DBB4 *var = TaskGetStructPtr(gCurTask);

    var->unk24 |= 2;
    gBgScrollRegs[0][1] += var->unk26;
    gBgScrollRegs[1][1] += var->unk26;
    sub_0812E6E4(var->unk26);
    gUnk_03000530 = var;
    gUnk_03002470[gUnk_03006070++] = sub_0812DFD4;
    gUnk_03002440 |= 0x10;
    sub_0812E194(10, 0x10, var->unk0[0].unk2);
    sub_0812E194(70, 0x10, var->unk0[1].unk2);
    sub_0812E194(130, 0x10, var->unk0[2].unk2);
    sub_0812E194(190, 0x10, var->unk0[3].unk2);
}

// TODO: match this in a better way
void sub_0812DFD4(void) {
    struct Unk_0812DBB4 *var = gUnk_03000530;
    u32 i;
    s32 r6 = var->unk0[0].unk4;
    u16 *vram = (u16 *)0x600F004;

    for (i = 0; i < r6 + 5; ++i) {
        int var = -r6 + 0x17 + i;
        ++var; --var;
        do
            CpuCopy16(({ gUnk_0836ECC8 + 2 * var; }), vram, sizeof(u16) * 2);
        while (0);
        vram += 0x20;
    }
    r6 = var->unk0[1].unk4;
    vram = (u16 *)0x600F014;
    for (i = 0; i < r6 + 5; ++i) {
        CpuCopy16(({ gUnk_0836ECC8 + 2 * (-r6 + 0x17 + i); }) + 0x40, vram, sizeof(u16) * 2);
        vram += 0x20;
    }
    r6 = var->unk0[2].unk4;
    vram = (u16 *)0x600F024;
    for (i = 0; i < r6 + 5; ++i) {
        CpuCopy16(({ gUnk_0836ECC8 + 2 * (-r6 + 0x17 + i); }) + 0x80, vram, sizeof(u16) * 2);
        vram += 0x20;
    }
    r6 = var->unk0[3].unk4;
    vram = (u16 *)0x600F034;
    for (i = 0; i < r6 + 5; ++i) {
        CpuCopy16(({ gUnk_0836ECC8 + 2 * (-r6 + 0x17 + i); }) + 0xC0, vram, sizeof(u16) * 2);
        vram += 0x20;
    }
}

void sub_0812E0C8(u16 a1, u16 a2, u8 a3) {
    struct Unk_08128F44_4 var;
    u16 r9 = 0;

    if (a3)
        r9 = a3 * 0x20 + 0x38;
    CpuFill32(0, &var, sizeof(struct Unk_08128F44_4));
    var.unk0.tilesVram = 0x6010000;
    var.unk0.unk14 = 0x500;
    var.unk0.animId = gUnk_08364FF4[gLanguage][a3].animId;
    var.unk0.variant = gUnk_08364FF4[gLanguage][a3].variant;
    var.unk0.unk16 = 0;
    var.unk0.unk1B = 0xFF;
    var.unk0.unk1C = 0x10;
    var.unk0.palId = 12;
    var.unk0.x = (4 * a1) >> 2;
    var.unk0.y = (4 * a2 + r9) >> 2;
    var.unk0.unk8 = 0xC0000;
    var.unk28 = 4 * a1;
    var.unk2C = 4 * a2 + r9;
    var.unk30 = 0;
    var.unk32 = 0;
    var.unk34 = 0x10;
    var.unk36 = 0;
    var.unk38 = NULL;
    var.unk3C = NULL;
    var.unk40 = NULL;
    sub_081288DC(&var);
}

void sub_0812E194(u16 a1, u16 a2, s16 a3) {
    u16 hundreds, tens, ones;
    struct Unk_08128F44_4 vars[4];
    struct Unk_08128F44_4 *r4, *r6;

    a3 += 120;
    ones = a3 >> 3;
    if (ones > 999) ones = 999;
    ones -= 1000 * (ones / 1000); // do nothing
    hundreds = ones / 100;
    ones -= 100 * hundreds;
    tens = ones / 10;
    ones -= 10 * tens;
    CpuFill32(0, r6 = &vars[3], sizeof(struct Unk_08128F44_4));
    r6->unk0.tilesVram = 0x6010000;
    r6->unk0.unk14 = 0x340;
    r6->unk0.animId = gUnk_08364E1C[gLanguage][hundreds].animId;
    r6->unk0.variant = gUnk_08364E1C[gLanguage][hundreds].variant;
    r6->unk0.unk16 = 0;
    r6->unk0.unk1B = 0xFF;
    r6->unk0.unk1C = 0x10;
    r6->unk0.palId = 12;
    r6->unk0.x = (4 * a1) >> 2;
    r6->unk0.y = (4 * a2) >> 2;
    r6->unk0.unk8 = 0xC0000;
    r6->unk28 = 4 * a1;
    r6->unk2C = 4 * a2;
    r6->unk30 = 0;
    r6->unk32 = 0;
    r6->unk34 = 0x10;
    r6->unk36 = 0;
    r6->unk38 = NULL;
    r6->unk3C = NULL;
    r6->unk40 = NULL;
    CpuFill32(0, r4 = &vars[2], sizeof(struct Unk_08128F44_4));
    r4->unk0.tilesVram = 0x6010000;
    r4->unk0.unk14 = 0x340;
    r4->unk0.animId = gUnk_08364E1C[gLanguage][tens].animId;
    r4->unk0.variant = gUnk_08364E1C[gLanguage][tens].variant;
    r4->unk0.unk16 = 0;
    r4->unk0.unk1B = 0xFF;
    r4->unk0.unk1C = 0x10;
    r4->unk0.palId = 12;
    r4->unk0.x = (4 * (a1 + 10)) >> 2;
    r4->unk0.y = (4 * a2) >> 2;
    r4->unk0.unk8 = 0xC0000;
    r4->unk28 = 4 * (a1 + 10);
    r4->unk2C = 4 * a2;
    r4->unk30 = 0;
    r4->unk32 = 0;
    r4->unk34 = 0x10;
    r4->unk36 = 0;
    r4->unk38 = NULL;
    r4->unk3C = NULL;
    r4->unk40 = NULL;
    CpuFill32(0, &vars[1], sizeof(struct Unk_08128F44_4));
    vars[1].unk0.tilesVram = 0x6010000;
    vars[1].unk0.unk14 = 0x340;
    vars[1].unk0.animId = gUnk_08364E1C[gLanguage][ones].animId;
    vars[1].unk0.variant = gUnk_08364E1C[gLanguage][ones].variant;
    vars[1].unk0.unk16 = 0;
    vars[1].unk0.unk1B = 0xFF;
    vars[1].unk0.unk1C = 0x10;
    vars[1].unk0.palId = 12;
    vars[1].unk0.x = (4 * (a1 + 20)) >> 2;
    vars[1].unk0.y = (4 * a2) >> 2;
    vars[1].unk0.unk8 = 0xC0000;
    vars[1].unk28 = 4 * (a1 + 20);
    vars[1].unk2C = 4 * a2;
    vars[1].unk30 = 0;
    vars[1].unk32 = 0;
    vars[1].unk34 = 0x10;
    vars[1].unk36 = 0;
    vars[1].unk38 = NULL;
    vars[1].unk3C = NULL;
    vars[1].unk40 = NULL;
    CpuFill32(0, &vars[0], sizeof(struct Unk_08128F44_4));
    vars[0].unk0.tilesVram = 0x6010000;
    vars[0].unk0.unk14 = 0x340;
    vars[0].unk0.animId = gUnk_08364E1C[gLanguage][11].animId;
    vars[0].unk0.variant = gUnk_08364E1C[gLanguage][11].variant;
    vars[0].unk0.unk16 = 0;
    vars[0].unk0.unk1B = 0xFF;
    vars[0].unk0.unk1C = 0x10;
    vars[0].unk0.palId = 12;
    vars[0].unk0.x = (4 * (a1 + 34)) >> 2;
    vars[0].unk0.y = (4 * a2) >> 2;
    vars[0].unk0.unk8 = 0xC0000;
    vars[0].unk28 = 4 * (a1 + 34);
    vars[0].unk2C = 4 * a2;
    vars[0].unk30 = 0;
    vars[0].unk32 = 0;
    vars[0].unk34 = 0x10;
    vars[0].unk36 = 0;
    vars[0].unk38 = NULL;
    vars[0].unk3C = NULL;
    vars[0].unk40 = NULL;
    sub_081288DC(&vars[0]);
    sub_081288DC(&vars[1]);
    sub_081288DC(r4);
    sub_081288DC(r6);
}

void sub_0812E468(struct Unk_0812A77C *a1) {
    u8 i, r6;
    u32 j;
    s16 array[4], max;

    array[0] = a1->unk40[0].unk9C;
    array[1] = a1->unk40[1].unk9C;
    array[2] = a1->unk40[2].unk9C;
    array[3] = a1->unk40[3].unk9C;
    for (i = 0; i < 4; i += r6) {
        r6 = 0;
        max = max(max(max(array[3], array[2]), array[1]), array[0]);
        for (j = 0; j < 4; ++j) {
            if (max == a1->unk40[j].unk9C) {
                a1->unk40[j].unkAC = i;
                array[j] = 0;
                ++r6;
            }
        }
    }
}

void sub_0812E51C(void) {
    struct Unk_0812A77C *var = TaskGetStructPtr(gCurTask);

    if (var->unk5F6++ > 50) {
        TaskDestroy(gCurTask);
        if (gUnk_0203AD10 & 2) {
            sub_08031CC8();
            sub_081589E8();
        }
        sub_08138D64(1);
    }
}

void sub_0812E588(struct Task *t) {
    struct Unk_0812A77C *var = TaskGetStructPtr(t);

    TaskDestroy(var->unk14[0]);
    var->unk14[0] = NULL;
    TaskDestroy(var->unk14[1]);
    var->unk14[1] = NULL;
    TaskDestroy(var->unk14[2]);
    var->unk14[2] = NULL;
    TaskDestroy(var->unk14[3]);
    var->unk14[3] = NULL;
    TaskDestroy(var->unk14[4]);
    var->unk14[4] = NULL;
    TaskDestroy(var->unk14[5]);
    var->unk14[5] = NULL;
    TaskDestroy(var->unk14[6]);
    var->unk14[6] = NULL;
    TaskDestroy(var->unk14[7]);
    var->unk14[7] = NULL;
    TaskDestroy(var->unk14[8]);
    var->unk14[8] = NULL;
    TaskDestroy(var->unk14[9]);
    var->unk14[9] = NULL;
}

void sub_0812E604(struct Unk_0812A77C_40 *a1) {
    if (a1->unkA6 & 2 && a1->unk94 & 1) {
        sub_0812BE74(a1);
        a1->unkA6 |= 4;
        a1->unkA6 &= ~2;
    }
}

void sub_0812E640(void) {
    gDispCnt &= ~DISPCNT_WIN0_ON & ~DISPCNT_BG2_ON;
    gBgCntRegs[2] = BGCNT_PRIORITY(1) | BGCNT_TXT256x256 | BGCNT_SCREENBASE(30);
    gBgScrollRegs[2][0] = 0;
    gBgScrollRegs[2][1] = 0;
    DmaFill32(3, 0, 0x600F000, 0x800);
    CpuFill32(0, gWinRegs, 4);
}

bool32 sub_0812E6A8(struct Unk_0812D4F4 *a1) {
    if (a1->unk114 & 2)
        return TRUE;
    else
        return FALSE;
}

void nullsub_31(struct Task *t __attribute__((unused))) {}

bool32 sub_0812E6C8(struct Unk_0812DBB4 *a1) {
    if (a1->unk24 & 2)
        return TRUE;
    else
        return FALSE;
}

void nullsub_32(struct Task *t __attribute__((unused))) {}

void sub_0812E6E4(u8 a1) {
    u32 a1Copy = a1 * 2;
    u32 size = 2 * (160 - a1);

    gUnk_03002440 |= 4;
    gUnk_030036C8 = 0x4000018;
    gUnk_030039A0 = 2;
    CpuCopy16(&gUnk_03002484[2 * a1], gUnk_03002EAC, size / 2 * 2);
    CpuCopy16(gUnk_03002484, gUnk_03002EAC + size, a1Copy / 2 * 2);
}

void sub_0812E764(struct Sprite *sprite, u8 a2) {
    sprite->animId = gUnk_08364CE4[gLanguage][a2].animId;
    sprite->variant = gUnk_08364CE4[gLanguage][a2].variant;
    sprite->unk1B = 0xFF;
}

void sub_0812E7A0(void) {
    u32 i = 0, j = 0;
    u16 *p1, *p2;

    gUnk_030036C8 = 0x4000018;
    gUnk_030039A0 = 2;
    p1 = (u16 *)gUnk_03002484;
    p2 = (u16 *)gUnk_03002EAC;
    for (; i < 160; ++i) {
        *p1++ = j / 4;
        *p2++ = j / 4;
        if (i < 10)
            j += 3;
        else if (i < 20)
            j -= 3;
        else if (i < 40)
            j += 2;
        else if (i < 60)
            j -= 2;
        else if (i < 90)
            j += 1;
        else if (i < 120)
            j -= 1;
        else if (i < 140)
            j += 3;
        else
            j -= 3;
    }
}

void sub_0812E818(struct Unk_0812A77C_40 *a1) {
    struct Unk_02021590 sp00;
    struct Task *t = TaskCreate(sub_0812E9CC, sizeof(struct Unk_0812E818), 0x100, TASK_USE_IWRAM, NULL);
    struct Unk_0812E818 *tmp = TaskGetStructPtr(t), *var = tmp;

    var->unk54 = 0;
    switch (gLanguage) { // same for every language
    case LANGUAGE_JAPANESE:
        sp00.animId = 0x343;
        sp00.variant = 8;
        break;
    case LANGUAGE_ENGLISH:
        sp00.animId = 0x343;
        sp00.variant = 8;
        break;
    case LANGUAGE_GERMAN:
        sp00.animId = 0x343;
        sp00.variant = 8;
        break;
    case LANGUAGE_FRENCH:
        sp00.animId = 0x343;
        sp00.variant = 8;
        break;
    case LANGUAGE_SPANISH:
        sp00.animId = 0x343;
        sp00.variant = 8;
        break;
    case LANGUAGE_ITALIAN:
        sp00.animId = 0x343;
        sp00.variant = 8;
        break;
    }
    var->unk0.unk0 = a1;
    var->unk0.unk50 = 0x5A;
    var->unk0.unk52 = 3;
    var->unk0.unk48 = 0;
    var->unk0.unk4C = -0x100;
    if (var->unk0.unk52 & 2) {
        ({ CpuFill32(0, &var->unk0.unk4, sizeof(struct Unk_08128F44_4)); }); // for sharing the filler with another CpuSet call
        var->unk0.unk4.unk0.tilesVram = 0x6010000;
        var->unk0.unk4.unk0.unk14 = 0x480;
        var->unk0.unk4.unk0.animId = sp00.animId;
        var->unk0.unk4.unk0.variant = sp00.variant;
        var->unk0.unk4.unk0.unk16 = 0;
        var->unk0.unk4.unk0.unk1B = 0xFF;
        var->unk0.unk4.unk0.unk1C = 0x10;
        var->unk0.unk4.unk0.palId = 11;
        var->unk0.unk4.unk0.x = (var->unk0.unk48 + var->unk0.unk0->unk0[0].unk28) >> 2;
        var->unk0.unk4.unk0.y = (var->unk0.unk4C + var->unk0.unk0->unk0[0].unk2C) >> 2;
        var->unk0.unk4.unk0.unk8 = 0xC0000;
        var->unk0.unk4.unk28 = var->unk0.unk48 + var->unk0.unk0->unk0[0].unk28;
        var->unk0.unk4.unk2C = var->unk0.unk4C + var->unk0.unk0->unk0[0].unk2C;
        var->unk0.unk4.unk30 = 0;
        var->unk0.unk4.unk32 = 0;
        var->unk0.unk4.unk34 = 0x810;
        var->unk0.unk4.unk36 = 0;
        var->unk0.unk4.unk38 = NULL;
        var->unk0.unk4.unk3C = NULL;
        var->unk0.unk4.unk40 = NULL;
    }
    else {
        CpuFill32(0, &var->unk0.unk4, sizeof(struct Unk_08128F44_4));
        var->unk0.unk4.unk0.tilesVram = 0x6010000;
        var->unk0.unk4.unk0.unk14 = 0x480;
        var->unk0.unk4.unk0.animId = sp00.animId;
        var->unk0.unk4.unk0.variant = sp00.variant;
        var->unk0.unk4.unk0.unk16 = 0;
        var->unk0.unk4.unk0.unk1B = 0xFF;
        var->unk0.unk4.unk0.unk1C = 0x10;
        var->unk0.unk4.unk0.palId = 11;
        var->unk0.unk4.unk0.x = var->unk0.unk48 >> 2;
        var->unk0.unk4.unk0.y = var->unk0.unk4C >> 2;
        var->unk0.unk4.unk0.unk8 = 0xC0000;
        var->unk0.unk4.unk28 = var->unk0.unk48;
        var->unk0.unk4.unk2C = var->unk0.unk4C;
        var->unk0.unk4.unk30 = 0;
        var->unk0.unk4.unk32 = 0;
        var->unk0.unk4.unk34 = 0x810;
        var->unk0.unk4.unk36 = 0;
        var->unk0.unk4.unk38 = NULL;
        var->unk0.unk4.unk3C = NULL;
        var->unk0.unk4.unk40 = NULL;
    }
    var->unk0.unk4.unk38 = a1->unk0[0].unk38;
    var->unk0.unk4.unk32 = 2;
}

void sub_0812E9CC(void) {
    struct Unk_0812E818 *var = TaskGetStructPtr(gCurTask);

    sub_0812A2C0(&var->unk0);
    if (var->unk54++ > 0x18) {
        var->unk54 = 0;
        var->unk0.unk4C = -0x100;
    }
    if (var->unk0.unk52 & 1) {
        if (var->unk0.unk50)
            --var->unk0.unk50;
        else
            TaskDestroy(gCurTask);
    }
}

void sub_0812EA4C(s32 a1, s32 a2) {
    struct Task *t = TaskCreate(sub_0812EC54, sizeof(struct Unk_0812D1EC_0), 0x100, TASK_USE_IWRAM, NULL);
    struct Unk_0812D1EC_0 *tmp = TaskGetStructPtr(t), *var = tmp;
    s32 r = Rand16() & 0xF;

    var->unk0 = NULL;
    var->unk50 = 0x14;
    var->unk52 = 1;
    var->unk48 = a1;
    var->unk4C = a2;
    if (var->unk52 & 2) {
        ({ CpuFill32(0, &var->unk4, sizeof(struct Unk_08128F44_4)); }); // for sharing the filler with another CpuSet call
        var->unk4.unk0.tilesVram = 0x6010000;
        var->unk4.unk0.unk14 = 0x380;
        var->unk4.unk0.animId = gUnk_08372440[gLanguage][r].animId;
        var->unk4.unk0.variant = gUnk_08372440[gLanguage][r].variant;
        var->unk4.unk0.unk16 = 0;
        var->unk4.unk0.unk1B = 0xFF;
        var->unk4.unk0.unk1C = 0x10;
        var->unk4.unk0.palId = 4;
        var->unk4.unk0.x = (var->unk48 + var->unk0->unk0[0].unk28) >> 2;
        var->unk4.unk0.y = (var->unk4C + var->unk0->unk0[0].unk2C) >> 2;
        var->unk4.unk0.unk8 = 0xC0000;
        var->unk4.unk28 = var->unk48 + var->unk0->unk0[0].unk28;
        var->unk4.unk2C = var->unk4C + var->unk0->unk0[0].unk2C;
        var->unk4.unk30 = 0;
        var->unk4.unk32 = 0;
        var->unk4.unk34 = 0x810;
        var->unk4.unk36 = 0;
        var->unk4.unk38 = NULL;
        var->unk4.unk3C = NULL;
        var->unk4.unk40 = NULL;
    }
    else {
        CpuFill32(0, &var->unk4, sizeof(struct Unk_08128F44_4));
        var->unk4.unk0.tilesVram = 0x6010000;
        var->unk4.unk0.unk14 = 0x380;
        var->unk4.unk0.animId = gUnk_08372440[gLanguage][r].animId;
        var->unk4.unk0.variant = gUnk_08372440[gLanguage][r].variant;
        var->unk4.unk0.unk16 = 0;
        var->unk4.unk0.unk1B = 0xFF;
        var->unk4.unk0.unk1C = 0x10;
        var->unk4.unk0.palId = 4;
        var->unk4.unk0.x = var->unk48 >> 2;
        var->unk4.unk0.y = var->unk4C >> 2;
        var->unk4.unk0.unk8 = 0xC0000;
        var->unk4.unk28 = var->unk48;
        var->unk4.unk2C = var->unk4C;
        var->unk4.unk30 = 0;
        var->unk4.unk32 = 0;
        var->unk4.unk34 = 0x810;
        var->unk4.unk36 = 0;
        var->unk4.unk38 = NULL;
        var->unk4.unk3C = NULL;
        var->unk4.unk40 = NULL;
    }
    r = Rand16() & 0xF;
    if (Rand32() & 0x10)
        var->unk4.unk30 = r;
    else
        var->unk4.unk30 = -r;
    var->unk4.unk32 = -(((Rand16() & 0xF) + 4) * 4);
}

void sub_0812EC54(void) {
    struct Unk_0812D1EC_0 *var = TaskGetStructPtr(gCurTask);
    struct Unk_0812D1EC_0 *var2 = var;

    sub_0812A2C0(var);
    if (var->unk52 & 1) {
        if (var->unk50)
            --var->unk50;
        else
            TaskDestroy(gCurTask);
    }
    else {
        if (var->unk4C > 680)
            TaskDestroy(gCurTask);
        else if (var2->unk48 < -40)
            TaskDestroy(gCurTask);
        else if (var2->unk48 > 1000)
            TaskDestroy(gCurTask);
    }
}

void sub_0812ECE0(void) {
    struct Unk_0812ECE0 *var = TaskGetStructPtr(gCurTask);
    s32 r3;

    if (var->unk0-- < 1) {
        var->unk0 = (Rand16() & 0xF) + gUnk_08372620[var->unk3];
        r3 = (Rand16() & 0x1F) * 4;
        if (Rand32() & 0x10)
            r3 = -r3;
        sub_0812ED78(var->unk4 + r3);
    }
}

void sub_0812ED78(s32 a1) {
    struct Task *t = TaskCreate(sub_0812EF3C, sizeof(struct Unk_0812D1EC_0), 0x100, TASK_USE_IWRAM, NULL);
    struct Unk_0812D1EC_0 *tmp = TaskGetStructPtr(t), *var = tmp;
    s32 r = Rand16() & 3;

    var->unk0 = NULL;
    var->unk50 = 0x96;
    var->unk52 = 1;
    var->unk48 = a1;
    var->unk4C = 0;
    if (var->unk52 & 2) {
        ({ CpuFill32(0, &var->unk4, sizeof(struct Unk_08128F44_4)); }); // for sharing the filler with another CpuSet call
        var->unk4.unk0.tilesVram = 0x6010000;
        var->unk4.unk0.unk14 = 0x380;
        var->unk4.unk0.animId = gUnk_083725C0[gLanguage][r].animId;
        var->unk4.unk0.variant = gUnk_083725C0[gLanguage][r].variant;
        var->unk4.unk0.unk16 = 0;
        var->unk4.unk0.unk1B = 0xFF;
        var->unk4.unk0.unk1C = 0x10;
        var->unk4.unk0.palId = 7;
        var->unk4.unk0.x = (var->unk48 + var->unk0->unk0[0].unk28) >> 2;
        var->unk4.unk0.y = (var->unk4C + var->unk0->unk0[0].unk2C) >> 2;
        var->unk4.unk0.unk8 = 0xC0000;
        var->unk4.unk28 = var->unk48 + var->unk0->unk0[0].unk28;
        var->unk4.unk2C = var->unk4C + var->unk0->unk0[0].unk2C;
        var->unk4.unk30 = 0;
        var->unk4.unk32 = 0;
        var->unk4.unk34 = 0x810;
        var->unk4.unk36 = 0;
        var->unk4.unk38 = NULL;
        var->unk4.unk3C = NULL;
        var->unk4.unk40 = NULL;
    }
    else {
        CpuFill32(0, &var->unk4, sizeof(struct Unk_08128F44_4));
        var->unk4.unk0.tilesVram = 0x6010000;
        var->unk4.unk0.unk14 = 0x380;
        var->unk4.unk0.animId = gUnk_083725C0[gLanguage][r].animId;
        var->unk4.unk0.variant = gUnk_083725C0[gLanguage][r].variant;
        var->unk4.unk0.unk16 = 0;
        var->unk4.unk0.unk1B = 0xFF;
        var->unk4.unk0.unk1C = 0x10;
        var->unk4.unk0.palId = 7;
        var->unk4.unk0.x = var->unk48 >> 2;
        var->unk4.unk0.y = var->unk4C >> 2;
        var->unk4.unk0.unk8 = 0xC0000;
        var->unk4.unk28 = var->unk48;
        var->unk4.unk2C = var->unk4C;
        var->unk4.unk30 = 0;
        var->unk4.unk32 = 0;
        var->unk4.unk34 = 0x810;
        var->unk4.unk36 = 0;
        var->unk4.unk38 = NULL;
        var->unk4.unk3C = NULL;
        var->unk4.unk40 = NULL;
    }
    r = (Rand16() & 3) + 1;
    var->unk4.unk32 = r;
}

void sub_0812EF3C(void) {
    struct Unk_0812D1EC_0 *var = TaskGetStructPtr(gCurTask);

    sub_0812A2C0(var);
    if (var->unk52 & 1) {
        if (var->unk50)
            --var->unk50;
        else
            TaskDestroy(gCurTask);
    }
    else if (var->unk4C > 680)
        TaskDestroy(gCurTask);
}
