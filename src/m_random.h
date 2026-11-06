//
//  Copyright (C) 1999 by
//  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
// DESCRIPTION:
//
//
//-----------------------------------------------------------------------------


#ifndef __M_RANDOM__
#define __M_RANDOM__

#include "doomtype.h"
#include "m_fixed.h"

// killough 1/19/98: rewritten to use to use a better random number generator
// in the new engine, although the old one is available for compatibility.

// killough 2/16/98:
//
// Make every random number generator local to each control-equivalent block.
// Critical for demo sync. Changing the order of this list breaks all previous
// versions' demos. The random number generators are made local to reduce the
// chances of sync problems. In Doom, if a single random number generator call
// was off, it would mess up all random number generators. This reduces the
// chances of it happening by making each RNG local to a control flow block.
//
// Notes to developers: if you want to reduce your demo sync hassles, follow
// this rule: for each call to P_Random you add, add a new class to the enum
// type below for each block of code which calls P_Random. If two calls to
// P_Random are not in "control-equivalent blocks", i.e. there are any cases
// where one is executed, and the other is not, put them in separate classes.
//
// Keep all current entries in this list the same, and in the order
// indicated by the #'s, because they're critical for preserving demo
// sync. Do not remove entries simply because they become unused later.

typedef enum {
  pr_skullfly,                // #1
  pr_damage,                  // #2
  pr_crush,                   // #3
  pr_genlift,                 // #4
  pr_killtics,                // #5
  pr_damagemobj,              // #6
  pr_painchance,              // #7
  pr_lights,                  // #8
  pr_explode,                 // #9
  pr_respawn,                 // #10
  pr_lastlook,                // #11
  pr_spawnthing,              // #12
  pr_spawnpuff,               // #13
  pr_spawnblood,              // #14
  pr_missile,                 // #15
  pr_shadow,                  // #16
  pr_plats,                   // #17
  pr_punch,                   // #18
  pr_punchangle,              // #19
  pr_saw,                     // #20
  pr_plasma,                  // #21
  pr_gunshot,                 // #22
  pr_misfire,                 // #23
  pr_shotgun,                 // #24
  pr_bfg,                     // #25
  pr_slimehurt,               // #26
  pr_dmspawn,                 // #27
  pr_missrange,               // #28
  pr_trywalk,                 // #29
  pr_newchase,                // #30
  pr_newchasedir,             // #31
  pr_see,                     // #32
  pr_facetarget,              // #33
  pr_posattack,               // #34
  pr_sposattack,              // #35
  pr_cposattack,              // #36
  pr_spidrefire,              // #37
  pr_troopattack,             // #38
  pr_sargattack,              // #39
  pr_headattack,              // #40
  pr_bruisattack,             // #41
  pr_tracer,                  // #42
  pr_skelfist,                // #43
  pr_scream,                  // #44
  pr_brainscream,             // #45
  pr_cposrefire,              // #46
  pr_brainexp,                // #47
  pr_spawnfly,                // #48
  pr_misc,                    // #49
  pr_all_in_one,              // #50
  // Start new entries -- add new entries below
  pr_opendoor,                // #51
  pr_targetsearch,            // #52
  pr_friends,                 // #53
  pr_threshold,               // #54
  pr_skiptarget,              // #55
  pr_enemystrafe,             // #56
  pr_avoidcrush,              // #57
  pr_stayonlift,              // #58
  pr_helpfriend,              // #59
  pr_dropoff,                 // #60
  pr_randomjump,              // #61
  pr_defect,                  // #62

  // End of new entries
  NUMPRCLASS,               // MUST be last item in list

  pr_mbf21,                   // #63
} pr_class_t;

// The random number generator's state.
typedef struct {
  unsigned long seed[NUMPRCLASS];      // Each block's random seed
  int rndindex, prndindex;             // For compatibility support
} rng_t;

extern rng_t rng;                      // The rng's state

extern unsigned long rngseed;          // The starting seed (not part of state)

// Returns a number from 0 to 255,
#define M_Random() P_Random(pr_misc)

// As M_Random, but used by the play simulation.
int P_Random(pr_class_t);

// [crispy] our own private random function
int Woof_Random(void);

// Fix randoms for demos.
void M_ClearRandom(void);

//
// RNG settings (Options -> RNG)
//
// Every setting is Default (stock vanilla rolls), Best (the roll always goes
// the player's way) or Worst (the roll always goes against the player).
// The helpers below still draw from the RNG exactly like the vanilla call
// they replace, so the random number stream, and everything that is not
// rigged, behaves exactly as without this feature. The settings are ignored
// (CRITICAL) while recording/playing demos and in netgames.
//

typedef enum
{
  RNG_DEFAULT,
  RNG_BEST,
  RNG_WORST,
  RNG_PRESET_CUSTOM // preset display only: the settings differ
} rng_mode_t;

extern int rng_preset;
extern int rng_player_melee_damage;
extern int rng_player_bullet_damage;
extern int rng_player_projectile_damage;
extern int rng_enemy_damage;
extern int rng_enemy_stagger;
extern int rng_player_accuracy;
extern int rng_enemy_accuracy;
extern int rng_enemy_crossfire;
extern int rng_melee_accuracy;
extern int rng_enemy_refire;
extern int rng_enemy_aggression;
extern int rng_enemy_pathing;
extern int rng_enemy_focus;
extern int rng_revenant_homing;
extern int rng_radiation_suit;
extern int rng_icon_of_sin;
extern int rng_monster_respawn;

// All rigged settings, in menu order (used by the preset).
#define RNG_NUM_SETTINGS 17
extern int *const rng_settings[RNG_NUM_SETTINGS];

void M_BindRNGVariables(void);

// Who is rolling the damage. Each player weapon type has its own setting.
typedef enum
{
  DMG_MONSTER,     // any monster attack
  DMG_MELEE,       // player fist, chainsaw
  DMG_BULLET,      // player pistol, shotguns, chaingun
  DMG_PROJECTILE   // player rockets, plasma, BFG
} rng_dmg_kind_t;

// Replaces "P_Random(c) % mod" in a damage formula. Returns 0..mod-1.
int P_DamageRoll(pr_class_t pr_class, int mod, rng_dmg_kind_t kind);

// Replace "P_Random(pr_cposrefire/pr_spidrefire) < threshold" in the
// chaingunner / Spider Mastermind refire code. A low roll means "keep firing
// without looking whether the target is still there".
int P_RefireRoll(pr_class_t pr_class);

// Replaces "P_Random(pr_missrange)" in the monster's "should I shoot?" check.
// A low roll means "don't shoot yet" (when the target is not point blank).
int P_AggressionRoll(void);

// Replaces "P_Random(pr_newchase)" in the monster's choice of direction. In
// vanilla, a roll above 200 makes it try the less direct axis first.
int P_PathingRoll(void);

// Replaces "P_Random(pr_trywalk) & 15", the number of steps a monster walks
// before it thinks again. (It may only start an attack when this reaches 0.)
int P_MoveCountRoll(void);

// Replaces "P_Random(pr_slimehurt)" for a player wearing a radiation suit on
// a damaging floor: the suit fails when the roll is below 5.
int P_SuitRoll(void);

// Replaces "P_Random(pr_spawnfly)", which picks what the Icon of Sin spawns.
int P_IconRoll(void);

// Replaces "P_Random(pr_respawn)": a corpse respawns when the roll is 4 or less.
int P_RespawnRoll(void);

// The random turn a monster gets when its target is invisible (fuzzy).
// roll is the vanilla (-255..255) value; only a player target is rigged.
int P_FuzzRoll(int roll, boolean target_is_player);

// Revenant missiles. A_Tracer runs every 2 tics but only acts (homing, smoke)
// on game tics that are a multiple of 4. A missile therefore either always
// acts or never does, depending on the parity of the tic it was fired on.
// Returns RNG_DEFAULT, RNG_BEST (never homes) or RNG_WORST (always homes).
int P_RevenantPhaseMode(void);

// The vanilla "P_Random(c) - P_Random(c)" spread roll (-255..255). Draws the
// same two numbers in the same order as the code it replaces.
int P_SpreadRoll(pr_class_t pr_class);

// Pieces of the mbf21 hitscan spread formulas (see P_RandomHitscanAngle).
int64_t P_HitscanSpreadBAM(fixed_t spread);
int P_HitscanSlopeFromAngle(int angle);

// Replaces the pain chance roll in P_DamageMobj. The result is compared with
// "roll < painchance", so a low value always staggers, a high one never does.
int P_PainRoll(boolean target_is_player);

// mbf21: [XA] Common random formulas used by codepointers
int P_RandomHitscanAngle(pr_class_t pr_class, fixed_t spread);
int P_RandomHitscanSlope(pr_class_t pr_class, fixed_t spread);

#endif

//----------------------------------------------------------------------------
//
// $Log: m_random.h,v $
// Revision 1.9  1998/05/01  14:20:31  killough
// beautification
//
// Revision 1.8  1998/03/31  10:43:07  killough
// Fix (supposed) RNG problems, add new demo_insurance
//
// Revision 1.7  1998/03/28  17:56:02  killough
// Improve RNG by adding external seed
//
// Revision 1.6  1998/03/09  07:16:39  killough
// Remove unused pr_class (don't do this after 1st release)
//
// Revision 1.5  1998/03/02  11:37:47  killough
// fix misspelling in comment
//
// Revision 1.4  1998/02/23  04:42:01  killough
// Add pr_atracer type
//
// Revision 1.3  1998/02/17  05:40:12  killough
// Make RNGs local to each calling block, for demo sync
//
// Revision 1.2  1998/01/26  19:27:14  phares
// First rev with no ^Ms
//
// Revision 1.1.1.1  1998/01/19  14:02:58  rand
// Lee's Jan 19 sources
//
//
//----------------------------------------------------------------------------
