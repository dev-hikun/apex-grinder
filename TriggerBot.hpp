#pragma once

#include "./Utils/Modules.hpp"

struct TriggerBot {
    ConfigLoader* cl;
    XDisplay* display;
    Level* level;
    LocalPlayer* localPlayer;
    std::vector<Player*>* players;
    const float TB_MAX_RANGE_ZOOMED = util::metersToGameUnits(150);
    const float TB_MAX_RANGE_HIPFRE = util::metersToGameUnits(10);

    TriggerBot(ConfigLoader* cl, XDisplay* display, Level* level, LocalPlayer* localPlayer, std::vector<Player*>* players) {
        this->cl = cl;
        this->display = display;
        this->level = level;
        this->localPlayer = localPlayer;
        this->players = players;
    }

    void shootAtEnemy(int counter) {
        if (!localPlayer->inZoom) return;
        if (!cl->FEATURE_TRIGGERBOT_ON) return;
        if (!localPlayer->isCombatReady()) return;

        //only these weapons will work with trigger bot
        int weaponId = localPlayer->weaponIndex;
        // printf("Last weapon held: %s id: %d \n", WeaponName(weaponId).c_str(), weaponId);
        if (
            // shotgun
            weaponId != WEAPON_MOZAMBIQUE &&
            weaponId != WEAPON_EVA8 &&
            weaponId != WEAPON_PEACEKEEPER &&
            weaponId != WEAPON_MASTIFF &&
            // light
            weaponId != WEAPON_P2020 &&
            weaponId != WEAPON_RE45 &&
            weaponId != WEAPON_ALTERNATOR &&
            weaponId != WEAPON_R99 &&
            weaponId != WEAPON_R301 &&
            weaponId != WEAPON_SPITFIRE &&
            weaponId != WEAPON_G7 &&
            // heavy
            weaponId != WEAPON_CAR &&
            weaponId != WEAPON_RAMPAGE &&
            weaponId != WEAPON_3030 &&
            weaponId != WEAPON_HEMLOCK &&
            weaponId != WEAPON_FLATLINE &&
            // energy
            weaponId != WEAPON_NEMESIS &&
            weaponId != WEAPON_VOLT &&
            weaponId != WEAPON_TRIPLE_TAKE &&
            weaponId != WEAPON_LSTAR &&
            weaponId != WEAPON_DEVOTION &&
            // weaponId != WEAPON_HAVOC &&
            //weaponId != WEAPON_THROWING_KNIFE &&
            weaponId != WEAPON_WINGMAN &&
            weaponId != WEAPON_LONGBOW &&
            weaponId != WEAPON_PROWLER &&
            weaponId != WEAPON_SENTINEL 
            //weaponId != WEAPON_KRABER &&
            // weaponId != WEAPON_BOCEK
            )return;

        //max range changes based on if we are zoomed in or not
        const float RANGE_MAX = (localPlayer->inZoom) ? TB_MAX_RANGE_ZOOMED : TB_MAX_RANGE_HIPFRE;

        for (int i = 0; i < players->size(); i++) {
            Player* player = players->at(i);
            if (!player->isCombatReady()) continue;
            if (!player->enemy) continue;
            if (!player->aimedAt) continue;
            if (player->distanceToLocalPlayer < RANGE_MAX) {
                display->mouseClickLeft();
                break;
            }
        }
    }
};
