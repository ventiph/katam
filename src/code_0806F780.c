#include "code_0806F780.h"
#include "task.h"
#include "kirby.h"
#include "main.h"
#include "random.h"
#include "functions.h"
#include "constants/kirby.h"

void sub_08070404(void);
void sub_08070808(void);
void sub_08070B50(struct Task *);
void sub_080714A0(void);
void sub_080717AC(void);
void sub_08071B0C(void);
void sub_08071E34(void);
void sub_080720F8(void);
void sub_080724C4(void);
void sub_080728B0(void);
void sub_08072E40(void);
void sub_08084AC4(struct Task *);
void sub_08084B1C(void);
void sub_08088AC8(struct Kirby *);
void sub_0808C464(struct ObjectBase *);
void sub_0808C6F4(struct Kirby *);

extern void (*const gUnk_08350C38[])(struct ObjectBase *);

bool16 sub_0806F780(struct ObjectBase *a1) {
    if (a1->flags & 0x1000) {
        TaskDestroy(gCurTask);
        return TRUE;
    }
    if (sub_0803D80C(a1)) {
        a1->flags |= 0x1000;
        return TRUE;
    }
    if (gKirbys[a1->unk56].base.base.base.roomId != a1->roomId
        && sub_0803E324(a1)) {
        a1->flags |= 0x1000;
        return TRUE;
    }
    if (gUnk_02026D50[gCurLevelInfo[a1->unk56].unk65E] & 8) {
        a1->flags |= 0x1000;
        return TRUE;
    }
    if (Macro_0810B1F4(a1) && !(a1->flags & 0x2000) && !(gMainFlags & 0x400)) {
        // TODO: semantically the same as SetPointerSomething
        if (!(a1->flags & 0x1000) && !(a1->flags & 0x200)) {
            u32 temp = gCurLevelInfo[a1->unk56].unk65E;

            if (a1->unk56 == 0xFF)
                temp = 0xFF;
            if (temp != 0xFF) {
                u8 idx;
                u32 temp2 = temp * 0x40 + (a1->unk0 - 1) * 0x20;

                ++a1; --a1;
                idx = gUnk_02022EB0[temp][a1->unk0 - 1]++ + temp2;
                gUnk_02022F50[idx] = a1;
                gUnk_02022F50[idx + 1] = NULL;
            }
        } 
        sub_0803D9A8(a1);
        return TRUE;
    }
    return FALSE;
}

bool32 sub_0806F8BC(struct ObjectBase *a1) {
    SetPointerSomething(a1);
    Macro_080FC150(a1, &a1->sprite);
    if (!(a1->flags & 0x400) && gKirbys[gUnk_0203AD3C].base.base.base.roomId == a1->roomId) {
        a1->sprite.x += gUnk_0203AD18[0];
        a1->sprite.y += gUnk_0203AD18[1];
        Macro_0803DBC8(a1, &a1->sprite);
    }
    return FALSE;
}

bool32 sub_0806FAC8(struct Object4 *a1) {
    if (!(a1->flags & 0x400)) {
        Macro_080FC150(a1, &a1->sprite);
        if (!(a1->flags & 0x400) && gKirbys[gUnk_0203AD3C].base.base.base.roomId == a1->roomId) {
            a1->sprite.x += gUnk_0203AD18[0];
            a1->sprite.y += gUnk_0203AD18[1];
            Macro_0803DBC8(a1, &a1->sprite);
        }
    }
    return FALSE;
}

void sub_0806FC70(struct ObjectBase *a1) {
    a1->unk62 = 0;
    if (!(a1->flags & 0x100)) {
        u8 r4, r7 = a1->unk57;

        a1->unk57 = sub_080023E4(a1->unk56, a1->x >> 0xC, a1->y >> 0xC);
        a1->unk58 = gUnk_082D88B8[a1->unk57];
        if (gUnk_082D88B8[a1->unk57] & 0x200
            || (gUnk_082D88B8[a1->unk57] & 0xC && !(gUnk_082D88B8[a1->unk57] & 0xF0000000))) {
            if ((r4 = gUnk_082D88B8[r7] >> 0x1C)) {
                if (gUnk_082D88B8[a1->unk57] & 0xC) {
                    if (a1->yspeed > 0 && r4 < 7) return;
                    if (a1->xspeed < 0) {
                        if (r4 < 4 || r4 > 9)
                            return;
                    } else if (a1->xspeed > 0) {
                        if (!(r4 < 4 || r4 > 9))
                            return;
                    }
                }
                a1->unk57 = r7;
                if (a1->unk48 >> 0xC != a1->x >> 0xC) {
                    if (a1->xspeed & 0x8000) {
                        a1->x &= 0xFFFFF000;
                        a1->unk48 = a1->x += 0x1000;
                    } else {
                        a1->x &= 0xFFFFF000;
                        a1->unk48 = a1->x -= 1;
                    }
                }
                if (a1->unk4C >> 0xC != a1->y >> 0xC) {
                    if (a1->yspeed & 0x8000) {
                        a1->y &= 0xFFFFF000;
                        a1->unk4C = a1->y -= 1;
                    } else {
                        a1->y &= 0xFFFFF000;
                        a1->unk4C = a1->y += 0x1000;
                    }
                }
                gUnk_08350C38[r4](a1);
            } else if (!(gUnk_082D88B8[a1->unk57] & 0x200)) {
                return;
            }
            a1->unk62 = 0xFF;
        } else if ((r4 = gUnk_082D88B8[a1->unk57] >> 0x1C)) {
            gUnk_08350C38[r4](a1);
        }
    }
}

void sub_0806FDF4(void) {
    struct Unk_0806FDF4 *ptr;

    gUnk_03000518 = TaskCreate(sub_08070404, sizeof(struct Unk_0806FDF4), 0xFFEF, TASK_USE_IWRAM, sub_08070B50);
    ptr = TaskGetStructPtr(gUnk_03000518);
    CpuFill16(0, ptr, sizeof(struct Unk_0806FDF4));
    ptr->unk0[0].roomId = 0xFFFE;
    ptr->unk0[1].roomId = 0xFFFE;
    ptr->unk0[2].roomId = 0xFFFE;
    ptr->unk0[3].roomId = 0xFFFE;
}

#define Macro_0806FE64(ptr, idx) ({ \
    u8 _i; \
    bool32 _ret = FALSE; \
 \
    for (_i = 0; _i < gUnk_0203AD44; ++_i) { \
        if ((ptr)->unk0[idx].roomId == gCurLevelInfo[_i].currentRoom) { \
            _ret = TRUE; \
            /* break; */ \
        } \
    } \
    _ret; \
})

void sub_0806FE64(u16 a1, struct ObjectBase *a2) {
    struct Unk_0806FDF4 *tmp, *v3;
    s8 v4;
    s8 v10;
    struct Unk_0806FDF4_0 *v6;

    if (gUnk_03000518) {
        tmp = TaskGetStructPtr(gUnk_03000518);
        v3 = tmp;
        v4 = -1;
        if (v3->unk0[0].roomId == a2->roomId)
            v4 = 0;
        else if (v3->unk0[1].roomId == a2->roomId)
            v4 = 1;
        else if (v3->unk0[2].roomId == a2->roomId)
            v4 = 2;
        else if (v3->unk0[3].roomId == a2->roomId)
            v4 = 3;
        if (v4 >= 0) {
            v6 = &v3->unk0[v4];
            if (!(v6->flags & 0x400))
                v6->unk4 = 0;
            v6->flags |= 0x100;
            if (a1 & 0x200)
                v6->flags |= 0x200;
            if (v6->unk6 <= (a1 & 0xFF))
                v6->unk6 = a1;
            if ((a1 & 0xFF) > 3)
                v6->flags |= 0x400;
        } else {
            v10 = -1;
            if (!(v3->unk0[0].flags & 0x100))
                v10 = 0;
            else if (!(v3->unk0[1].flags & 0x100))
                v10 = 1;
            else if (!(v3->unk0[2].flags & 0x100))
                v10 = 2;
            else if (!(v3->unk0[3].flags & 0x100))
                v10 = 3;
            if (v10 == -1) {
                if (!Macro_0806FE64(v3, 0))
                    v10 = 0;
                else if (!Macro_0806FE64(v3, 1))
                    v10 = 1;
                else if (!Macro_0806FE64(v3, 2))
                    v10 = 2;
                else if (!Macro_0806FE64(v3, 3))
                    v10 = 3;
            }
            v6 = &v3->unk0[v10];
            v6->unk6 = a1;
            v6->flags = 0x100;
            v6->roomId = a2->roomId;
            v6->unk4 = 0;
            if (a1 & 0x200)
                v6->flags |= 0x200;
            if ((a1 & 0xFF) > 3)
                v6->flags |= 0x400;
        }
    }
}

void sub_080700D8(struct ObjectBase *a1) {
    struct Unk_0806FDF4 *tmp, *v3;
    s8 v4;
    struct Unk_0806FDF4_0 *v6;

    if (gUnk_03000518) {
        tmp = TaskGetStructPtr(gUnk_03000518);
        v3 = tmp;
        v4 = -1;
        if (v3->unk0[0].roomId == a1->roomId)
            v4 = 0;
        else if (v3->unk0[1].roomId == a1->roomId)
            v4 = 1;
        else if (v3->unk0[2].roomId == a1->roomId)
            v4 = 2;
        else if (v3->unk0[3].roomId == a1->roomId)
            v4 = 3;
        if (v4 >= 0) {
            v6 = &v3->unk0[v4];
            v6->flags = 0;
            v6->unk6 = 0;
            v6->roomId = 0xFFFE;
            gUnk_0203AD18[0] = 0;
            gUnk_0203AD18[1] = 0;
        }
    }
}

void sub_08070164(struct Unk_0806FDF4_0 *a1) {
    u16 v2 = 0, v3 = 0;
    bool32 v4 = FALSE;
    bool32 flag = TRUE;
    u8 i = gUnk_0203AD44;

    if (gUnk_0203AD44) {
        while (1) {
            if (gCurLevelInfo[i - 1].currentRoom == a1->roomId) {
                if (gUnk_03000510.unk4 & ((1 << (i - 1)) | 0x10))
                    v4 = TRUE;
                if (!(gUnk_02026D50[gCurLevelInfo[i - 1].unk65E] & 8)) {
                    flag = FALSE;
                    break;
                }
            }
            if (!--i)
                break;
        }
    }
    if (flag) {
        a1->flags = 0;
        a1->unk6 = 0;
        a1->roomId = 0xFFFE;
        gUnk_0203AD18[0] = 0;
        gUnk_0203AD18[1] = 0;
        return;
    }
    if (a1->flags & 0x100) {
        switch (a1->unk6) {
        case 1:
            v2 = gUnk_08350BB0[a1->unk4][0];
            v3 = gUnk_08350BB0[a1->unk4][1];
            if (a1->unk4 > 0xD) {
                a1->flags = 0;
                a1->unk6 = 0;
                a1->roomId = 0xFFFE;
            }
            break;
        case 2:
            v2 = gUnk_08350BCC[a1->unk4][0];
            v3 = gUnk_08350BCC[a1->unk4][1];
            if (a1->unk4 > 0x11) {
                a1->flags = 0;
                a1->unk6 = 0;
                a1->roomId = 0xFFFE;
            }
            break;
        case 3:
            v2 = gUnk_08350BF0[a1->unk4][0];
            v3 = gUnk_08350BF0[a1->unk4][1];
            if (a1->unk4 > 0x17) {
                a1->flags = 0;
                a1->unk6 = 0;
                a1->roomId = 0xFFFE;
            }
            break;
        case 4:
            if (a1->unk4 > 0x11)
                a1->unk4 = 0;
            v2 = gUnk_08350BCC[a1->unk4][0];
            v3 = gUnk_08350BCC[a1->unk4][1];
            break;
        case 5:
            if (a1->unk4 > 0xB)
                a1->unk4 = 0;
            v2 = gUnk_08350C20[a1->unk4][0];
            v3 = gUnk_08350C20[a1->unk4][1];
            break;
        case 6:
            if (a1->unk4 > 0x17)
                a1->unk4 = 0;
            v2 = gUnk_08350BF0[a1->unk4][0];
            v3 = gUnk_08350BF0[a1->unk4][1];
            break;
        }
        if (a1->roomId == gCurLevelInfo[gUnk_0203AD3C].currentRoom) {
            gUnk_0203AD18[0] = v2;
            gUnk_0203AD18[1] = v3;
            if (gUnk_0203AD20 & 8) {
                gCurLevelInfo[sub_08002374()].unk44 = gUnk_0203AD18[0];
                gCurLevelInfo[sub_08002374()].unk46 = gUnk_0203AD18[1];
            } else {
                gCurLevelInfo[sub_08002374()].unk44 = -gUnk_0203AD18[0];
                gCurLevelInfo[sub_08002374()].unk46 = -gUnk_0203AD18[1];
            }
        }
        if (!v4)
            ++a1->unk4;
    }
}

void sub_08070404(void) {
    struct Unk_0806FDF4 *var = TaskGetStructPtr(gCurTask);

    gUnk_0203AD18[0] = 0;
    gUnk_0203AD18[1] = 0;
    if (var->unk0[0].flags & 0x100)
        sub_08070164(&var->unk0[0]);
    if (var->unk0[1].flags & 0x100)
        sub_08070164(&var->unk0[1]);
    if (var->unk0[2].flags & 0x100)
        sub_08070164(&var->unk0[2]);
    if (var->unk0[3].flags & 0x100)
        sub_08070164(&var->unk0[3]);
}

bool8 sub_08070488(struct ObjectBase *a1) {
    bool8 ret = FALSE;
    struct Unk_0806FDF4 *tmp, *var;
    struct Unk_0806FDF4_0 *v6;
    u8 i;

    if (!gUnk_03000518)
        return FALSE;
    tmp = TaskGetStructPtr(gUnk_03000518);
    var = tmp;
    for (i = 0; i < gUnk_0203AD44; ++i) {
        v6 = &var->unk0[i];
        if (v6->roomId == a1->roomId && v6->flags & 0x100)
            ret = TRUE;
            // break;
    }
    return ret;
}

bool8 sub_08070504(struct ObjectBase *a1) {
    bool8 ret = FALSE;
    struct Unk_0806FDF4 *tmp, *var;
    struct Unk_0806FDF4_0 *v6;
    u8 i;

    if (!gUnk_03000518)
        return FALSE;
    tmp = TaskGetStructPtr(gUnk_03000518);
    var = tmp;
    for (i = 0; i < gUnk_0203AD44; ++i) {
        v6 = &var->unk0[i];
        if (v6->roomId == a1->roomId && v6->flags & 0x200) {
            ret = TRUE;
            // break;
        }
    }
    return ret;
}

void sub_08070580(void) {
    struct Unk_080C4EDC *tmp = TaskGetStructPtr(gCurTask), *var = tmp;

    if (var->unk84)
        var->unk84(var);
    if (!sub_0806F780(&var->base)
        && (!var->unk78 || !var->unk78(var))
        && ((!(var->base.flags & 0x40000) && !(var->base.flags & 0x80000)) || !var->unk7C || !var->unk7C(var))) {
        if (!(var->base.flags & 0x800)) {
            var->base.unk48 = var->base.x;
            var->base.unk4C = var->base.y;
            var->base.x += var->base.xspeed;
            var->base.y -= var->base.yspeed;
        }
        if (!(var->base.flags & 0x100)) {
            if (var->base.x <= gCurLevelInfo[var->base.unk56].unk50
                && var->base.x >= gCurLevelInfo[var->base.unk56].unk48
                && var->base.y <= gCurLevelInfo[var->base.unk56].unk54
                && var->base.y >= gCurLevelInfo[var->base.unk56].unk4C)
                sub_0806FC70(&var->base);
        }
        if (!var->unk80 || !var->base.unk62 || !var->unk80(var))
            sub_0806F8BC(&var->base);
    }
}

struct Object14 *sub_080706A0(struct ObjectBase *a1, u32 a2, u16 a3, u8 a4,
    bool8 (*a5)(struct Object14 *), void (*a6)(struct Object14 *)) {
    struct Task *t = TaskCreate(sub_08070808, sizeof(struct Object14), 0x3500, TASK_USE_EWRAM, sub_0803DCCC);
    struct Object14 *tmp = TaskGetStructPtr(t), *obj14 = tmp;

    sub_0803E3B0(&obj14->obj4);
    obj14->obj4.unk0 = 3;
    obj14->obj4.x = a1->x;
    obj14->obj4.y = a1->y;
    obj14->obj4.parent = a1;
    obj14->obj4.roomId = a1->roomId;
    obj14->obj4.flags |= 0x300;
    if (Macro_0810B1F4(a1))
        obj14->obj4.flags |= 0x2000;
    if (a1->flags & 1)
        obj14->obj4.flags |= 1;
    obj14->func48 = a5;
    obj14->func4C = a6;
    obj14->obj4.flags |= 2;
    a5(obj14);
    if (a2) {
        if (a2 > 0x200) {
            if (a2 != a1->unk56 * 0x800 + 0x6010600)
                obj14->obj4.flags |= 0x4000;
            sub_080709F8(&obj14->obj4, &obj14->obj4.sprite, a2, a3, a4, 0xA);
        } else {
            sub_080709F8(&obj14->obj4, &obj14->obj4.sprite, a2, a3, a4, 0xA);
        }
    } else {
        obj14->obj4.flags |= 0x4000;
        sub_080709F8(&obj14->obj4, &obj14->obj4.sprite, 0x6012000, a3, a4, 0xA);
    }
    return obj14;
}

void sub_08070808(void) {
    struct Object14 *tmp = TaskGetStructPtr(gCurTask), *obj14 = tmp;
    struct ObjectBase *parent = obj14->obj4.parent;

    if (obj14->obj4.flags & 0x1000)
        TaskDestroy(gCurTask);
    else {
        if (obj14->func4C)
            obj14->func4C(obj14);
        if (Macro_0810B1F4(parent) && !(obj14->obj4.flags & 0x2000))
            sub_0803DBC8(&obj14->obj4);
        else if (obj14->func48(obj14))
            obj14->obj4.flags |= 0x1000;
        else {
            obj14->obj4.unk3C += obj14->obj4.unk4;
            obj14->obj4.unk3E += obj14->obj4.unk8;
            if (!(obj14->obj4.flags & 0x800)) {
                obj14->obj4.x += obj14->obj4.unk3C;
                obj14->obj4.y -= obj14->obj4.unk3E;
            }
            sub_0806FAC8(&obj14->obj4);
        }
    }
}

void sub_080708DC(struct ObjectBase *a1, struct Sprite *a2, u32 a3, u16 animId, u8 variant, u16 a6) {
    u32 vram = 0;
    u32 flags = 0xC0000;

    if (a3 > 0x400) {
        vram = a3;
        if (vram != 0x6012000)
            flags &= ~0x80000;
    } else {
        if (gKirbys[gUnk_0203AD3C].base.base.base.roomId == a1->roomId) {
            if (a1->flags & 0x4000)
                vram = sub_0803DE54(a3, animId, variant);
            else {
                vram = VramMalloc(a3);
                flags &= ~0x80000;
            }
        }
    }
    if (a1->flags & 1)
        flags |= 0x400;
    else
        flags &= ~0x400;
    a2->tilesVram = vram;
    a2->unk14 = a6 * 0x40;
    a2->animId = animId;
    a2->variant = variant;
    a2->unk16 = 0;
    a2->unk1B = 0xFF;
    a2->unk1C = 0;
    a2->palId = 0xF;
    a2->x = a1->x >> 8;
    a2->y = a1->y >> 8;
    a2->unk8 = flags | 0x2000;
    a2->unk20[0].unk0 = -1;
    sub_08155128(a2);
    a2->unk1C = 0x10;
    // dead code
    if (a1->flags & 0x4000) {
        u32 vram2 = 0x6012000;

        if (vram == vram2)
            { ++vram2; --vram2; }
        else
            { ++vram2; --vram2; }
    }
}

void sub_080709F8(struct Object4 *a1, struct Sprite *a2, u32 a3, u16 animId, u8 variant, u16 a6) {
    u32 vram = 0;
    u32 flags = 0xC0000;

    if (a3 > 0x400) {
        vram = a3;
        if (vram != 0x6012000)
            flags &= ~0x80000;
    } else {
        if (gKirbys[gUnk_0203AD3C].base.base.base.roomId == a1->roomId) {
            if (a1->flags & 0x4000)
                vram = sub_0803DE54(a3, animId, variant);
            else {
                vram = VramMalloc(a3);
                flags &= ~0x80000;
            }
        }
    }
    if (a1->flags & 1)
        flags |= 0x400;
    else
        flags &= ~0x400;
    a2->tilesVram = vram;
    a2->unk14 = a6 * 0x40;
    a2->animId = animId;
    a2->variant = variant;
    a2->unk16 = 0;
    a2->unk1B = 0xFF;
    a2->unk1C = 0;
    a2->palId = 0xF;
    a2->x = a1->x >> 8;
    a2->y = a1->y >> 8;
    a2->unk8 = flags | 0x2000;
    a2->unk20[0].unk0 = -1;
    sub_08155128(a2);
    a2->unk1C = 0x10;
    // dead code
    if (a1->flags & 0x4000) {
        u32 vram2 = 0x6012000;

        if (vram == vram2)
            { ++vram2; --vram2; }
        else
            { ++vram2; --vram2; }
    }
}

void sub_08070B14(struct ObjectBase *a1) {
    if (!(a1->flags & 0x800)) {
        a1->unk48 = a1->x;
        a1->unk4C = a1->y;
        a1->x = a1->x + a1->xspeed;
        a1->y = a1->y - a1->yspeed;
    }
    sub_0806F8BC(a1);
}

void sub_08070B50(struct Task *t __attribute__((unused))) {
    gUnk_0203AD18[0] = 0;
    gUnk_0203AD18[1] = 0;
    gUnk_03000518 = NULL;
}

void sub_08070B68(void) {
    struct ObjectBase *objBase = TaskGetStructPtr(gCurTask);

    sub_0806F780(objBase);
    sub_0806F8BC(objBase);
}

void nullsub_122(struct ObjectBase *a1 __attribute__((unused))) {}

void sub_08070BA8(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed >= 0 && a1->yspeed <= 0))
        && (r3 = ((a1->x & 0xF00) >> 9) - ((~a1->y & 0xF00) >> 8)) >= 0) {
        if (a1->xspeed > -a1->yspeed)
            a1->x -= r3 * 0x100;
        else
            a1->y -= r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08070C24(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed >= 0 && a1->yspeed <= 0))
        && (r3 = ((a1->x & 0xF00) >> 9) - ({ ((~a1->y & 0xF00) >> 8) - 7; })) >= 0) {
        if (a1->xspeed > -a1->yspeed)
            a1->x -= r3 * 0x100;
        else
            a1->y -= r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08070CA0(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed <= 0 && a1->yspeed <= 0))
        && (r3 = ((~a1->x & 0xF00) >> 9) - ((~a1->y & 0xF00) >> 8)) >= 0) {
        if (-a1->xspeed > -a1->yspeed)
            a1->x += r3 * 0x100;
        else
            a1->y -= r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08070D20(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed <= 0 && a1->yspeed <= 0))
        && (r3 = ((~a1->x & 0xF00) >> 9) - ({ ((~a1->y & 0xF00) >> 8) - 7; })) >= 0) {
        if (-a1->xspeed > -a1->yspeed)
            a1->x += r3 * 0x100;
        else
            a1->y -= r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08070DA0(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed >= 0 && a1->yspeed >= 0))
        && (r3 = ((a1->x & 0xF00) >> 9) - ((a1->y & 0xF00) >> 8)) >= 0) {
        if (a1->xspeed > a1->yspeed)
            a1->x -= r3 * 0x100;
        else
            a1->y += r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08070E20(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed >= 0 && a1->yspeed >= 0))
        && (r3 = ((a1->x & 0xF00) >> 9) - ({ ((a1->y & 0xF00) >> 8) - 7; })) >= 0) {
        if (a1->xspeed > a1->yspeed)
            a1->x -= r3 * 0x100;
        else
            a1->y += r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08070EA0(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed <= 0 && a1->yspeed >= 0))
        && (r3 = ((~a1->x & 0xF00) >> 9) - ((a1->y & 0xF00) >> 8)) > 0) {
        ++r3;
        if (-a1->xspeed > a1->yspeed)
            a1->x += r3 * 0x100;
        else
            a1->y += r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08070F24(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed <= 0 && a1->yspeed >= 0))
        && (r3 = ((~a1->x & 0xF00) >> 9) - ({ ((a1->y & 0xF00) >> 8) - 7; })) >= 0) {
        ++r3;
        if (-a1->xspeed > a1->yspeed)
            a1->x += r3 * 0x100;
        else
            a1->y += r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08070FA8(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed >= 0 && a1->yspeed <= 0))
        && (r3 = ((a1->x & 0xF00) >> 8) - ((~a1->y & 0xF00) >> 8)) >= 0) {
        if (a1->xspeed > -a1->yspeed)
            a1->x -= r3 * 0x100;
        else
            a1->y -= r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08071024(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed <= 0 && a1->yspeed <= 0))
        && (r3 = ((~a1->x & 0xF00) >> 8) - ((~a1->y & 0xF00) >> 8)) >= 0) {
        if (-a1->xspeed > -a1->yspeed)
            a1->x += r3 * 0x100;
        else
            a1->y -= r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_080710A4(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed <= 0 && a1->yspeed >= 0))
        && (r3 = ((a1->x & 0xF00) >> 8) - ((~a1->y & 0xF00) >> 8)) < 2) {
        if (-a1->xspeed > a1->yspeed)
            a1->x -= r3 * 0x100;
        else
            a1->y -= r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_08071124(struct ObjectBase *a1) {
    s32 r3;

    if ((!(gUnk_082D88B8[a1->unk57] & 0xC) || (a1->xspeed >= 0 && a1->yspeed >= 0))
        && (r3 = ((~a1->x & 0xF00) >> 8) - ((~a1->y & 0xF00) >> 8)) < 0) {
        if (a1->xspeed > a1->yspeed)
            a1->x += r3 * 0x100;
        else
            a1->y -= r3 * 0x100;
        a1->unk62 = 0xFF;
    }
}

void sub_080711A0(struct ObjectBase *a1) {
    a1->unk62 = 0xFF;
}

void sub_080711A8(struct Kirby *kirby) {
    struct Task *t = TaskCreate(sub_080714A0, sizeof(struct ObjectBase), 0x2FFF, TASK_USE_IWRAM, NULL);
    struct ObjectBase *tmp = TaskGetStructPtr(t), *objBase = tmp;

    sub_0803E380(objBase);
    objBase->unk0 = 2;
    objBase->x = kirby->base.base.base.x;
    objBase->y = kirby->base.base.base.y;
    objBase->parent = kirby;
    objBase->counter = 0;
    objBase->roomId = kirby->base.base.base.roomId;
    objBase->unk56 = kirby->base.base.base.unk56;
    if (Macro_0810B1F4(objBase))
        objBase->flags |= 0x2000;
    objBase->unk64 = 0x1C0;
    objBase->unk66 = 0;
    objBase->unk63 = 2;
    objBase->flags |= 0x2000000;
    if (kirby->ability == KIRBY_ABILITY_MASTER) {
        objBase->unk64 = 0;
        objBase->unk66 = 0x120;
        objBase->unk63 = 2;
        objBase->unk68 |= 0x30007103;
        objBase->unk68 |= 0x2000000;
    }
    objBase->flags |= 0x80000000;
    objBase->flags |= 0x400;
    objBase->unk68 |= 0x10400042;
    if (kirby->ability == KIRBY_ABILITY_FIGHTER || kirby->ability == KIRBY_ABILITY_MASTER || kirby->ability == KIRBY_ABILITY_SWORD) {
        objBase->unk68 &= ~7;
        objBase->unk68 |= 3;
        if (kirby->ability == KIRBY_ABILITY_FIGHTER)
            objBase->unk63 = 3;
        if (kirby->ability == KIRBY_ABILITY_SWORD) {
            objBase->unk63 = 4;
            objBase->unk68 |= 0x2000;
        }
    }
    if (kirby->base.base.base.flags & 1)
        objBase->flags |= 1;
    if (kirby->ability == KIRBY_ABILITY_MASTER) {
        sub_0803E2B0(objBase, 1, -0xA, 0x2E, 0xE);
        sub_0803E308(objBase, -1, -4, 0x28, 0xE);
        objBase->unk68 |= 0x2000;
    }
    else if (kirby->ability == KIRBY_ABILITY_SWORD || kirby->base.base.base.unkC & 2) {
        sub_0803E2B0(objBase, 1, -8, 0x20, 0xE);
        sub_0803E308(objBase, -1, -4, 0x20, 0xE);
    } else {
        sub_0803E2B0(objBase, 1, -6, 0x10, 0xE);
        sub_0803E308(objBase, -1, -4, 0x10, 0xE);
    }
    SetPointerSomething(objBase);
    PlaySfx(&kirby->base.base.base, 115);
}

void sub_080714A0(void) {
    struct ObjectBase *tmp = TaskGetStructPtr(gCurTask), *objBase = tmp;
    struct Kirby *kirby;
    struct Object2 *unk6C;

    if (!sub_0806F780(objBase)) {
        kirby = objBase->parent;
        if (kirby->base.base.base.unk62 & 1)
            objBase->flags &= ~0x20000000;
        else
            objBase->flags |= 0x20000000;
        if (kirby->unkD4 != 13) {
            if (kirby->base.base.base.unk56 == gUnk_0203AD3C)
                m4aSongNumStop(115);
            objBase->flags |= 0x1000;
        } else {
            if (kirby->ability != KIRBY_ABILITY_MASTER && objBase->flags & 0x40000) {
                unk6C = objBase->unk6C;
                if (unk6C && unk6C->base.unk0 == 1 && unk6C->type == OBJ_GORDO)
                    objBase->flags &= ~0x40000;
                if (objBase->flags & 0x40000) {
                    if (kirby->base.base.base.unkC & 2) {
                        sub_08074240(&kirby->base.base.base, FALSE);
                        kirby->base.base.base.unkC &= ~2;
                        sub_0806EB74(kirby);
                    }
                    sub_0804323C(kirby);
                    return;
                }
            }
            if (objBase->flags & 0x80000 && kirby->base.base.base.unkC & 2) {
                sub_08074240(&kirby->base.base.base, FALSE);
                kirby->base.base.base.unkC &= ~2;
                sub_0806EB74(kirby);
            }
            if (kirby->ability == KIRBY_ABILITY_MASTER && objBase->flags & 0x40000) {
                if (!(kirby->base.base.base.flags & 0x800000) && ++objBase->counter > 1) {
                    objBase->flags &= ~0x40000;
                    objBase->counter = 0;
                    ++objBase->unk1;
                }
                if (objBase->unk1 > 4) {
                    sub_0804323C(kirby);
                    return;
                }
            }
            SetPointerSomething(objBase);
            objBase->x = kirby->base.base.base.x;
            objBase->y = kirby->base.base.base.y;
            if (kirby->base.base.base.flags & 1)
                objBase->flags |= 1;
            else
                objBase->flags &= ~1;
        }
    }
}

void sub_080716BC(struct Kirby *kirby) {
    struct Task *t = TaskCreate(sub_080717AC, sizeof(struct ObjectBase), 0x3500, TASK_USE_IWRAM, NULL);
    struct ObjectBase *objBase = TaskGetStructPtr(t);

    sub_0803E380(objBase);
    objBase->unk0 = 2;
    objBase->x = kirby->base.base.base.x;
    objBase->y = kirby->base.base.base.y;
    objBase->parent = kirby;
    objBase->counter = 0;
    objBase->roomId = kirby->base.base.base.roomId;
    objBase->unk56 = kirby->base.base.base.unk56;
    if (Macro_0810B1F4(objBase))
        objBase->flags |= 0x2000;
    objBase->unk64 = 0x1C0;
    objBase->unk66 = 0;
    objBase->unk63 = 2;
    objBase->flags |= 0xA0000000;
    objBase->flags |= 0x400;
    objBase->flags |= 0x2000000;
    objBase->unk68 |= 0x30400042;
    sub_0803E2B0(objBase, -0xA, 6, 0xC, 0xD);
    sub_0803E308(objBase, -0xA, 6, 0xC, 0xD);
}

void sub_080717AC(void) {
    struct ObjectBase *tmp = TaskGetStructPtr(gCurTask), *objBase = tmp;
    struct Kirby *kirby;
    struct Object2 *unk6C;

    if (!sub_0806F780(objBase)) {
        kirby = objBase->parent;
        if (kirby->unkD4 < 0x12 || kirby->unkD4 > 0x13) {
            objBase->flags |= 0x1000;
            return;
        }
        if (objBase->flags & 0x40000) {
            unk6C = objBase->unk6C;
            if (unk6C && unk6C->base.unk0 == 1 && unk6C->type == OBJ_GORDO)
                objBase->flags &= ~0x40000;
        }
        if (objBase->flags & 0xC0000) {
            unk6C = objBase->unk6C;
            if (unk6C && unk6C->base.unk0 == 1) {
                if (!(({ 0x3FFFF8 & ~(unk6C->base.unk5C & ~7) ;}) & objBase->unk68)
                    || (objBase->unk68 & 7) < (unk6C->base.unk5C & 7)
                    || objBase->flags & 0x8000)
                    PlaySfx(&kirby->base.base.base, 113);
            }
            sub_080459B8(kirby);
        } else {
            SetPointerSomething(objBase);
            objBase->x = kirby->base.base.base.x;
            objBase->y = kirby->base.base.base.y;
            if (kirby->base.base.base.flags & 1)
                objBase->flags |= 1;
            else
                objBase->flags &= ~1;
        }
    }
}

void sub_08071994(struct Kirby *kirby) {
    struct Task *t = TaskCreate(sub_08071B0C, sizeof(struct ObjectBase), 0x3500, TASK_USE_IWRAM, NULL);
    struct ObjectBase *tmp = TaskGetStructPtr(t), *objBase = tmp;

    sub_0803E380(objBase);
    objBase->unk0 = 2;
    objBase->x = kirby->base.base.base.x;
    objBase->y = kirby->base.base.base.y;
    objBase->parent = kirby;
    objBase->counter = 0;
    objBase->roomId = kirby->base.base.base.roomId;
    objBase->unk56 = kirby->base.base.base.unk56;
    if (Macro_0810B1F4(objBase))
        objBase->flags |= 0x2000;
    objBase->unk64 = 0x1C0;
    objBase->unk66 = 0;
    objBase->unk63 = 2;
    objBase->flags |= 0xA0000000;
    objBase->flags |= 0x400;
    objBase->flags |= 0x2000000;
    objBase->unk68 |= 0x10400042;
    if (kirby->base.base.base.flags & 1)
        objBase->flags |= 1;
    sub_0803E2B0(objBase, -0xA, -8, 0x10, 8);
    sub_0803E308(objBase, 1, -8, 0x10, 8);
    SetPointerSomething(objBase);
}

void sub_08071B0C(void) {
    struct ObjectBase *tmp = TaskGetStructPtr(gCurTask), *objBase = tmp;
    struct Kirby *kirby;
    struct Object2 *unk6C;

    if (!sub_0806F780(objBase)) {
        kirby = objBase->parent;
        if (kirby->unkD4 < 0x4A || kirby->unkD4 > 0x59) {
            objBase->flags |= 0x1000;
            return;
        }
        if (objBase->flags & 0x40000) {
            unk6C = objBase->unk6C;
            if (unk6C && unk6C->base.unk0 == 1 && unk6C->type == OBJ_GORDO)
                objBase->flags &= ~0x40000;
        }
        if (objBase->flags & 0x40000) {
            if (kirby->base.base.base.unkC & 2) {
                sub_08074240(&kirby->base.base.base, FALSE);
                kirby->base.base.base.unkC &= ~2;
                sub_0806EB74(kirby);
            }
            objBase->flags |= 0x200;
            objBase->flags |= 0x1000;
            sub_0804323C(kirby);
        } else {
            if (objBase->flags & 0x80000 && kirby->base.base.base.unkC & 2) {
                sub_08074240(&kirby->base.base.base, FALSE);
                kirby->base.base.base.unkC &= ~2;
                sub_0806EB74(kirby);
            }
            SetPointerSomething(objBase);
            objBase->x = kirby->base.base.base.x;
            objBase->y = kirby->base.base.base.y;
            if (kirby->base.base.base.flags & 1)
                objBase->flags |= 1;
            else
                objBase->flags &= ~1;
        }
    }
}

void sub_08071C9C(struct Kirby *kirby) {
    struct Task *t = TaskCreate(sub_08071E34, sizeof(struct ObjectBase), 0x3500, TASK_USE_IWRAM, NULL);
    struct ObjectBase *tmp = TaskGetStructPtr(t), *objBase = tmp;

    sub_0803E380(objBase);
    objBase->unk0 = 2;
    objBase->x = kirby->base.base.base.x;
    objBase->y = kirby->base.base.base.y;
    objBase->parent = kirby;
    objBase->counter = 0;
    objBase->roomId = kirby->base.base.base.roomId;
    objBase->unk56 = kirby->base.base.base.unk56;
    if (Macro_0810B1F4(objBase))
        objBase->flags |= 0x2000;
    objBase->unk64 = 0x1C0;
    objBase->unk66 = 0;
    objBase->unk63 = 2;
    objBase->flags |= 0xA0000000;
    objBase->flags |= 0x400;
    objBase->flags |= 0x2000000;
    objBase->unk68 |= 0x10000042;
    if (kirby->base.base.base.flags & 1)
        objBase->flags |= 1;
    sub_0803E2B0(objBase, -6, -8, 6, 4);
    sub_0803E308(objBase, 0xA, -6, 0xC, 4);
    SetPointerSomething(objBase);
    sub_0808AE30(&kirby->base.base.base, 0, 0x2B1, 0);
}

void sub_08071E34(void) {
    struct ObjectBase *tmp = TaskGetStructPtr(gCurTask), *objBase = tmp;
    struct Kirby *kirby;
    struct Object4 *obj4;

    if (!sub_0806F780(objBase)) {
        kirby = objBase->parent;
        if (kirby->unkD4 != 0xF) {
            objBase->flags |= 0x1000;
            return;
        }
        if (objBase->flags & 0x40000) {
            objBase->flags |= 0x200;
            objBase->flags |= 0x1000;
        } else {
            if ((++objBase->counter & 3) == 3) {
                obj4 = sub_0808AE30(&kirby->base.base.base, 0, 0x2B1, 1);
                obj4->x += (0x10 - (Rand16() & 0x1F)) * 0x100;
                obj4->y += ((Rand16() & 7) + 4) * 0x100;
                obj4->unk3E = -0x40;
                obj4->unk3C = 0x40 - (Rand16() & 0x7F);
            }
            SetPointerSomething(objBase);
            objBase->x = kirby->base.base.base.x;
            objBase->y = kirby->base.base.base.y;
            if (kirby->base.base.base.flags & 1)
                objBase->flags |= 1;
            else
                objBase->flags &= ~1;
        }
    }
}

void sub_08071FC0(struct Kirby *kirby) {
    struct Task *t = TaskCreate(sub_080720F8, sizeof(struct ObjectBase), 0x3500, TASK_USE_IWRAM, sub_08084AC4);
    struct ObjectBase *tmp = TaskGetStructPtr(t), *objBase = tmp;

    sub_0803E380(objBase);
    objBase->unk0 = 2;
    objBase->x = kirby->base.base.base.x;
    objBase->y = kirby->base.base.base.y;
    objBase->parent = kirby;
    objBase->counter = 0;
    objBase->roomId = kirby->base.base.base.roomId;
    objBase->unk56 = kirby->base.base.base.unk56;
    if (Macro_0810B1F4(objBase))
        objBase->flags |= 0x2000;
    objBase->flags |= 0xA0100000;
    objBase->flags |= 0x4000;
    objBase->unk68 |= 0x20000021;
    objBase->flags |= 0x2000000;
    objBase->unk5C |= 0x80000;
    if (kirby->base.base.base.flags & 1) {
        objBase->flags |= 1;
        objBase->x -= 0x400;
    } else {
        objBase->x += 0x400;
    }
    sub_0803E2B0(objBase, 0, -0x12, 0x2C, 0x10);
    sub_0803E308(objBase, 0, -0x12, 0x2C, 0x10);
    sub_080708DC(objBase, &objBase->sprite, (kirby->base.base.base.unk56 * 0x800) + 0x6010400, 0x13, 0, 0xA);
    objBase->sprite.palId = kirby->base.base.base.unk56;
}

void sub_080720F8(void) {
    struct ObjectBase *tmp = TaskGetStructPtr(gCurTask), *objBase = tmp;
    struct Kirby *kirby = objBase->parent;
    struct Object2 *unk6C;

    if (kirby->unkD4 != 0x1D) {
        if ((kirby->unkD4 != 0x1A && kirby->unkD4 != 0x1B)
            && kirby->unkD4 != 0x6A && kirby->unkD4 != 0x6B)
            objBase->roomId = 0xFFFF;
        if (!sub_0806F780(objBase)) {
            objBase->flags |= 4;
            if (objBase->flags & 1)
                objBase->x = kirby->base.base.base.x - 0x400;
            else
                objBase->x = kirby->base.base.base.x + 0x400;
            objBase->y = kirby->base.base.base.y;
            if (objBase->counter & 1) {
                objBase->flags |= 0x400;
                if (kirby->unkD4 < 0x6A || kirby->unkD4 > 0x6B)
                    objBase->flags |= 8;
            } else {
                objBase->flags &= ~0x400;
                objBase->flags &= ~8;
            }
            if (objBase->flags & 0xC0000) {
                unk6C = objBase->unk6C;
                objBase->flags |= 0x200;
                if (unk6C && unk6C->base.unk0 == 1 && ObjType5ETo6C(unk6C))
                    objBase->flags &= ~0x200;
                if (kirby->base.base.base.unk56 >= gUnk_0203AD30) {
                    if (unk6C->type == OBJ_ABILITY_STAR_2)
                        objBase->flags &= ~0x200;
                    if (unk6C->type == OBJ_ABILITY_STAR_1 && unk6C->base.unk56 < gUnk_0203AD30)
                        objBase->flags &= ~0x200;
                }
            }
            if (objBase->counter > 5) {
                if (objBase->counter == 6) {
                    sub_08088AC8(kirby);
                    sub_08088AC8(kirby);
                    sub_08088AC8(kirby);
                }
                PlaySfxAlt(&kirby->base.base.base, 101);
                sub_0806F8BC(objBase);
            }
            if (++objBase->counter == 0x30) {
                sub_0803E2B0(objBase, 0, -0x17, 0x37, 0x15);
                sub_0803E308(objBase, 0, -0x17, 0x37, 0x15);
                objBase->unk68 = 0x20000023;
            }
        }
    }
}

void sub_08072314(struct Kirby *kirby) {
    struct Task *t = TaskCreate(sub_080724C4, sizeof(struct ObjectBase), 0x3500, TASK_USE_IWRAM, sub_08084AC4);
    struct ObjectBase *tmp = TaskGetStructPtr(t), *objBase = tmp;

    sub_0803E380(objBase);
    objBase->unk0 = 2;
    objBase->x = kirby->base.base.base.x;
    objBase->y = kirby->base.base.base.y;
    objBase->parent = kirby;
    objBase->counter = 0;
    objBase->roomId = kirby->base.base.base.roomId;
    objBase->unk56 = kirby->base.base.base.unk56;
    if (Macro_0810B1F4(objBase))
        objBase->flags |= 0x2000;
    objBase->flags |= 0xA0100000;
    objBase->unk68 |= 0x20200023;
    objBase->unk5C |= 0x80000;
    objBase->flags |= 0x2000000;
    if (kirby->base.base.base.flags & 1) {
        objBase->x -= 0x400;
        objBase->flags |= 1;
    } else {
        objBase->x += 0x400;
        objBase->flags &= ~1;
    }
    sub_0803E2B0(objBase, 0, -0x12, 0x32, 0x10);
    sub_0803E308(objBase, 0, -0x12, 0x32, 0x10);
    sub_0808C6F4(kirby);
    sub_0808C6F4(kirby);
    sub_0808C6F4(kirby);
    PlaySfx(&kirby->base.base.base, 101);
}

void sub_080724C4(void) {
    struct ObjectBase *tmp = TaskGetStructPtr(gCurTask), *objBase = tmp;
    struct Kirby *kirby;
    struct Object2 *unk6C;

    if (!sub_0806F780(objBase)) {
        kirby = objBase->parent;
        if (kirby->unkD4 != 0x1A && kirby->unkD4 != 0x1B)
            objBase->flags |= 0x1000;
        else {
            if (objBase->flags & 1)
                objBase->x = kirby->base.base.base.x - 0x400;
            else
                objBase->x = kirby->base.base.base.x + 0x400;
            objBase->y = kirby->base.base.base.y;
            if (objBase->flags & 0xC0000) {
                unk6C = objBase->unk6C;
                if (unk6C->base.unk0 != 1
                    || (unk6C->type != OBJ_ABILITY_STAR_1 && unk6C->type != OBJ_ABILITY_STAR_2))
                    objBase->flags |= 0x200;
            }
            SetPointerSomething(objBase);
        }
    }
}

void sub_080725E0(struct Kirby *kirby) {
    struct Task *t = TaskCreate(sub_080728B0, sizeof(struct ObjectBase), 0x3500, TASK_USE_IWRAM, sub_0803DCCC);
    struct ObjectBase *tmp = TaskGetStructPtr(t), *objBase = tmp;

    sub_0803E380(objBase);
    objBase->unk0 = 2;
    objBase->x = kirby->base.base.base.x;
    objBase->y = kirby->base.base.base.y;
    objBase->parent = kirby;
    objBase->counter = 0;
    objBase->roomId = kirby->base.base.base.roomId;
    objBase->unk56 = kirby->base.base.base.unk56;
    if (Macro_0810B1F4(objBase))
        objBase->flags |= 0x2000;
    objBase->flags |= 0xA0000000;
    objBase->unk68 |= 0x20000043;
    objBase->unk64 = 0x280;
    objBase->unk66 = 0x280;
    if (objBase->flags & 0x2000)
        objBase->flags |= 0x200;
    if (kirby->unkDD & KIRBY_ABILITY_CHANGE_UNKNOWN) {
        objBase->unk63 = 0x19;
        objBase->unk68 = 0x20000043;
    } else {
        objBase->unk63 = 0xA;
    }
    objBase->xspeed = 0;
    objBase->yspeed = 0;
    sub_0803E2B0(objBase, -0xC, -0xC, 0xC, 0xC);
    sub_0803E308(objBase, -2, -2, 2, 2);
    if (kirby->unkDD & KIRBY_ABILITY_CHANGE_UNKNOWN) {
        objBase->flags |= 0x4000;
        sub_080708DC(objBase, &objBase->sprite, 0x6012000, 0x2A1, 0, 0xA);
        sub_080706A0(objBase, 0, 0x2A1, 1, sub_08072B98, sub_08084AA0);
        PlaySfx(&kirby->base.base.base, 104);
    } else {
        objBase->flags |= 0x4000;
        sub_080708DC(objBase, &objBase->sprite, 0x6012000, 0x295, 0, 0xA);
        sub_080706A0(objBase, 0, 0x295, 2, sub_08072B98, sub_08084AA0);
        PlaySfx(&kirby->base.base.base, 103);
    }
}

void sub_080728B0(void) {
    struct ObjectBase *tmp = TaskGetStructPtr(gCurTask), *objBase = tmp;
    struct Kirby *kirby;

    if (!sub_0806F780(objBase)) {
        kirby = objBase->parent;
        if (objBase->counter < 2) {
            if (kirby->hp <= 0)
                objBase->flags |= 0x1000;
            objBase->flags |= 0x400;
            objBase->flags |= 0x200;
            ++objBase->counter;
        } else if (objBase->counter == 2) {
            objBase->flags &= ~0x600;
            if (objBase->flags & 0x2000)
                objBase->flags |= 0x200;
            objBase->y = kirby->base.base.base.y;
            if (kirby->base.base.base.flags & 1) {
                objBase->flags |= 1;
                objBase->x = kirby->base.base.base.x - 0x800;
                objBase->xspeed = -0x400;
            } else {
                objBase->x = kirby->base.base.base.x + 0x800;
                objBase->xspeed = 0x400;
            }
            ++objBase->counter;
            SetPointerSomething(objBase);
        } else {
            objBase->flags |= 4;
            if (!(objBase->flags & 0x800)) {
                objBase->unk48 = objBase->x;
                objBase->unk4C = objBase->y;
                objBase->x = objBase->x + objBase->xspeed;
                objBase->y = objBase->y - objBase->yspeed;
            }
            if (objBase->unk63 != 0x19 && objBase->flags & 0xC0000) {
                sub_0808AE30(objBase, 0, 0x28E, 0);
                objBase->flags |= 0x1000;
            } else {
                if (objBase->x <= gCurLevelInfo[objBase->unk56].unk50 && objBase->x >= gCurLevelInfo[objBase->unk56].unk48
                    && objBase->y <= gCurLevelInfo[objBase->unk56].unk54 && objBase->y >= gCurLevelInfo[objBase->unk56].unk4C)
                    sub_0806FC70(objBase);
                if (objBase->unk62 && (!(gUnk_082D88B8[objBase->unk57] & 0x1000)
                    || (gUnk_082D88B8[objBase->unk57] & 0xF00000) > 0x100000)) {
                    objBase->flags |= 0x1000;
                    sub_0808AE30(objBase, 0, 0x28E, 0);
                    PlaySfx(&kirby->base.base.base, 126);
                } else {
                    sub_0806F8BC(objBase);
                }
            }
        }
    }
}

bool8 sub_08072B98(struct Object14 *obj14) {
    struct ObjectBase *objBase = obj14->obj4.parent;
#ifdef NONMATCHING
    s32 x, y;
#else
    register s32 x asm("r3"), y;
#endif

    if (objBase->flags & 0x1000)
        return TRUE;
    else {
        if (objBase->flags & 0x400)
            obj14->obj4.flags |= 0x400;
        else
            obj14->obj4.flags &= ~0x400;
        obj14->obj4.flags |= 4;
        if (obj14->obj4.flags & 2) {
            x = obj14->obj4.x = objBase->x;
            y = obj14->obj4.y = objBase->y;
            obj14->obj4.unk3C = -0x100;
            obj14->obj4.unk3E = 0;
            obj14->obj4.unk4 = 0;
            obj14->obj4.unk8 = 0;
            if (obj14->obj4.flags & 1)
                obj14->obj4.unk3C = -obj14->obj4.unk3C;
            else {
                obj14->obj4.x = x;
                obj14->obj4.y = y;
            }
        }
        return FALSE;
    }
}

bool8 sub_08072C0C(struct Object14 *obj14) {
    struct ObjectBase *objBase = obj14->obj4.parent;
#ifdef NONMATCHING
    s32 x, y;
#else
    register s32 x asm("r4"), y;
#endif

    if (objBase->flags & 0x1000)
        return TRUE;
    else {
        obj14->obj4.flags |= 4;
        if (obj14->obj4.flags & 2) {
            x = obj14->obj4.x = objBase->x;
            y = obj14->obj4.y = objBase->y;
            obj14->obj4.unk3C = 0;
            obj14->obj4.unk3E = -0x100;
            obj14->obj4.unk4 = 0;
            obj14->obj4.unk8 = 0;
            if (obj14->obj4.flags & 1) {
                obj14->obj4.unk3C = obj14->obj4.unk3C;
            } else {
                obj14->obj4.x = x;
                obj14->obj4.y = y;
            }
        }
        return FALSE;
    }
}

void sub_08072C5C(struct Kirby *kirby) {
    struct Task *t = TaskCreate(sub_08072E40, sizeof(struct ObjectBase), 0x3500, TASK_USE_IWRAM, sub_0803DCCC);
    struct ObjectBase *tmp = TaskGetStructPtr(t), *objBase = tmp;

    sub_0803E380(objBase);
    objBase->unk0 = 2;
    objBase->x = kirby->base.base.base.x;
    objBase->y = kirby->base.base.base.y;
    objBase->parent = kirby;
    objBase->counter = 0;
    objBase->roomId = kirby->base.base.base.roomId;
    objBase->unk56 = kirby->base.base.base.unk56;
    if (Macro_0810B1F4(objBase))
        objBase->flags |= 0x2000;
    objBase->flags |= 0xA0000000;
    objBase->unk68 |= 0x20000042;
    objBase->unk68 &= ~7;
    objBase->unk68 |= 2;
    if (objBase->flags & 0x2000)
        objBase->flags |= 0x200;
    objBase->unk64 = 0x1C0;
    objBase->unk66 = 0;
    objBase->unk63 = 2;
    objBase->y = kirby->base.base.base.y;
    objBase->yspeed = 0;
    if (kirby->base.base.base.flags & 1) {
        objBase->flags |= 1;
        objBase->x = kirby->base.base.base.x - 0x800;
        objBase->xspeed = -0x3C0;
    } else {
        objBase->x = kirby->base.base.base.x + 0x800;
        objBase->xspeed = 0x3C0;
    }
    sub_0803E2B0(objBase, -5, -5, 5, 5);
    sub_0803E308(objBase, -2, -2, 2, 2);
    objBase->flags |= 0x4000;
    sub_080708DC(objBase, &objBase->sprite, 0x6012000, 0x28C, 0, 0xA);
    SetPointerSomething(objBase);
}

void sub_08072E40(void) {
    struct ObjectBase *tmp = TaskGetStructPtr(gCurTask), *objBase = tmp;
    struct Kirby *kirby;

    if (!sub_0806F780(objBase)) {
        if (objBase->sprite.variant && objBase->flags & 2) {
            objBase->flags |= 0x1000;
            return;
        }
        if (objBase->counter > 0x10)
            objBase->sprite.variant = 1;
        if (objBase->sprite.variant == 0)
            objBase->flags |= 4;
        if (objBase->counter < 0x10
            && (objBase->counter & 7) == 7)
            sub_0808C464(objBase);
        if (objBase->xspeed < 0) {
            objBase->xspeed += 0x20;
            if (objBase->xspeed > 0)
                objBase->xspeed = 0;
        } else {
            objBase->xspeed -= 0x20;
            if (objBase->xspeed < 0)
                objBase->xspeed = 0;
        }
        if (!(objBase->flags & 0x800)) {
            objBase->unk48 = objBase->x;
            objBase->unk4C = objBase->y;
            objBase->x = objBase->x + objBase->xspeed;
            objBase->y = objBase->y - objBase->yspeed;
        }
        if (objBase->flags & 0xC0000) {
            objBase->flags |= 0x200;
            objBase->sprite.variant = 2;
            gCurTask->main = sub_08084B1C;
        }
        if (objBase->x <= gCurLevelInfo[objBase->unk56].unk50 && objBase->x >= gCurLevelInfo[objBase->unk56].unk48
            && objBase->y <= gCurLevelInfo[objBase->unk56].unk54 && objBase->y >= gCurLevelInfo[objBase->unk56].unk4C)
            sub_0806FC70(objBase);
        if (objBase->unk62
            && (!(gUnk_082D88B8[objBase->unk57] & 0x1000) || (gUnk_082D88B8[objBase->unk57] & 0xF00000) > 0x100000)) {
            objBase->flags |= 0x200;
            objBase->sprite.variant = 2;
            gCurTask->main = sub_08084B1C;
        }
        sub_0806F8BC(objBase);
        ++objBase->counter;
    }
}

void sub_08072FF0(struct Object14 *obj14) {
    struct Kirby *kirby = obj14->obj4.parent;
    bool32 var;

    if (kirby->unkD4 != 0x34
        && obj14->obj4.flags & 2)
        obj14->obj4.flags |= 0x1400;
    if (kirby->ability != KIRBY_ABILITY_FIRE)
        obj14->obj4.flags |= 0x1400;
    {
        struct Kirby *kirby;

        var = FALSE;
        kirby = obj14->obj4.parent;
        if (kirby->unkD4 == 0x5A || kirby->ability == KIRBY_ABILITY_NORMAL) {
            obj14->obj4.flags |= 0x1400;
            var = TRUE;
        }
    }
    if (var)
        obj14->obj4.flags |= 0x1400;
}

void sub_08073068(struct Object14 *obj14) {
    struct Kirby *kirby = obj14->obj4.parent;
    bool32 var;

    if (kirby->unkD4 != 0x34
        && obj14->obj4.flags & 2)
        obj14->obj4.flags |= 0x1400;
    if (kirby->ability != KIRBY_ABILITY_ICE)
        obj14->obj4.flags |= 0x1400;
    {
        struct Kirby *kirby;

        var = FALSE;
        kirby = obj14->obj4.parent;
        if (kirby->unkD4 == 0x5A || kirby->ability == KIRBY_ABILITY_NORMAL) {
            obj14->obj4.flags |= 0x1400;
            var = TRUE;
        }
    }
    if (var)
        obj14->obj4.flags |= 0x1400;
}

bool8 sub_080730E0(struct Object14 *obj14) {
    struct Kirby *kirby = obj14->obj4.parent;

    if (obj14->obj4.flags & 2) {
        obj14->obj4.sprite.variant = ~obj14->obj4.sprite.variant & 1;
        obj14->obj4.flags &= ~1;
        obj14->obj4.flags |= (kirby->base.base.base.flags & 1);
        obj14->obj4.x = kirby->base.base.base.x;
        obj14->obj4.y = kirby->base.base.base.y;
        obj14->obj4.unk3C = kirby->unkD6 + 0x80;
        obj14->obj4.unk3E = kirby->base.base.base.counter;
        obj14->obj4.unk4 = 0x30;
        obj14->obj4.unk8 = 0xB - (Rand16() & 0x1F);
        if (obj14->obj4.flags & 1) {
            obj14->obj4.x = obj14->obj4.x - ((Rand16() & 7) + 0x18) * 0x100;
            obj14->obj4.y = obj14->obj4.y - (Rand16() & 7) * 0x100;
            obj14->obj4.unk3C = -obj14->obj4.unk3C;
            obj14->obj4.unk4 = -obj14->obj4.unk4;
        } else {
            obj14->obj4.x = obj14->obj4.x + ((Rand16() & 7) + 0x18) * 0x100;
            obj14->obj4.y = obj14->obj4.y - (Rand16() & 7) * 0x100;
        }
    }
    return FALSE;
}

bool8 sub_080731EC(struct Object14 *obj14) {
    struct Kirby *kirby = obj14->obj4.parent;

    if (obj14->obj4.flags & 2) {
        obj14->obj4.flags |= 4;
        obj14->obj4.flags &= ~1;
        obj14->obj4.flags |= (kirby->base.base.base.flags & 1);
        obj14->obj4.x = kirby->base.base.base.x;
        obj14->obj4.y = kirby->base.base.base.y;
        obj14->obj4.unk3C = kirby->unkD6 + 0x120;
        obj14->obj4.unk3E = kirby->base.base.base.counter;
        obj14->obj4.unk4 = -8;
        obj14->obj4.unk8 = -2;
        if (obj14->obj4.flags & 1) {
            obj14->obj4.x = obj14->obj4.x - ((Rand16() & 0x1F) + 0x10) * 0x100;
            obj14->obj4.y = obj14->obj4.y - (Rand16() | ~7) * 0x100;
            obj14->obj4.unk3C = -obj14->obj4.unk3C;
            obj14->obj4.unk4 = -obj14->obj4.unk4;
        } else {
            obj14->obj4.x = obj14->obj4.x + ((Rand16() & 0x1F) + 0x10) * 0x100;
            obj14->obj4.y = obj14->obj4.y - (Rand16() | ~7) * 0x100;
        }
    }
    return FALSE;
}

bool8 sub_080732E4(struct Object14 *obj14) {
    struct Kirby *kirby = obj14->obj4.parent;

    if (obj14->obj4.flags & 2) {
        obj14->obj4.flags |= 4;
        obj14->obj4.flags &= ~1;
        obj14->obj4.flags |= (kirby->base.base.base.flags & 1);
        obj14->obj4.x = kirby->base.base.base.x;
        obj14->obj4.y = kirby->base.base.base.y;
        obj14->obj4.unk3C = kirby->unkD6 + 0x10;
        obj14->obj4.unk3E = kirby->base.base.base.counter;
        obj14->obj4.unk4 = 0x30;
        obj14->obj4.unk8 = 0xF;
        if (obj14->obj4.flags & 1) {
            obj14->obj4.x = obj14->obj4.x - ((Rand16() & 0x1F) + 0x10) * 0x100;
            obj14->obj4.y = obj14->obj4.y - (Rand16() | ~7) * 0x100;
            obj14->obj4.unk3C = -obj14->obj4.unk3C;
            obj14->obj4.unk4 = -obj14->obj4.unk4;
        } else {
            obj14->obj4.x = obj14->obj4.x + ((Rand16() & 0x1F) + 0x10) * 0x100;
            obj14->obj4.y = obj14->obj4.y - (Rand16() | ~7) * 0x100;
        }
    }
    return FALSE;
}

bool8 sub_080733D8(struct Object14 *obj14) {
    struct Kirby *kirby = obj14->obj4.parent;

    if (obj14->obj4.flags & 2) {
        obj14->obj4.flags |= 4;
        obj14->obj4.flags &= ~1;
        obj14->obj4.flags |= (kirby->base.base.base.flags & 1);
        obj14->obj4.x = kirby->base.base.base.x;
        obj14->obj4.y = kirby->base.base.base.y;
        obj14->obj4.unk3C = kirby->unkD6 + 0x80;
        obj14->obj4.unk3E = kirby->base.base.base.counter + 0x80;
        obj14->obj4.unk4 = 0x20;
        obj14->obj4.unk8 = 0xF - (Rand16() & 0x1F);
        if (obj14->obj4.flags & 1) {
            obj14->obj4.x = obj14->obj4.x - ((Rand16() & 7) + (Rand16() & 3) + 0x14) * 0x100;
            obj14->obj4.y = obj14->obj4.y - (Rand16() & 7) * 0x100;
            obj14->obj4.unk3C = -obj14->obj4.unk3C;
            obj14->obj4.unk4 = -obj14->obj4.unk4;
        } else {
            obj14->obj4.x = obj14->obj4.x + ((Rand16() & 7) + (Rand16() & 3) + 0x14) * 0x100;
            obj14->obj4.y = obj14->obj4.y - (Rand16() & 7) * 0x100;
        }
    }
    return FALSE;
}
