#ifndef __SKILL_H__
#define __SKILL_H__

<<<<<<< HEAD
#define STRING_LEN 20
#define SKILL_COUNT 54 /**< Maximum number of skill */
=======
#define STRING_LEN 20 /**< Maximum number of character */
#define SKILL_COUNT 29 /**< Maximum number of skill */
>>>>>>> add documentation and fix fetch highscore

/**
 * @brief Skill enum
 * 
 * List of skill 
 * */
typedef enum
{
    S_EMBER,
    S_VINEWHIP,
    S_WATERGUN,
    S_HEADBUTT,
    S_SLASH,
    S_RECOVER,
    S_FLAMEWHEEL,
    S_MAGICALLEAF,
    S_WATERPULSE,
    S_FLAMETHROWER,
    S_LEAFBLADE,
    S_SURF,
    S_MEGAPUNCH,
    S_FIREBLAST,
    S_SOLARBEAM,
    S_HYDROPUMP,
    S_MEGAKICK,
    S_BLASTBURN,
    S_FRENZYPLANT,
    S_HYDROCANNON,
    S_HYPERBEAM,
    ES_TACKLE,
    ES_ACID,
    ES_SLUDGEBOMB,
    ES_GUNKSHOT,
    ES_SCRATCH,
    ES_THRUST,
    ES_POTION,
    ES_GOBLINPUNCH,
    ES_BITE,
    ES_FLAMEBURST,
    ES_FIREFANG,
    ES_SCORCH,
    ES_BUBBLE,
    ES_BUBBLEBEAM,
    ES_NATUREGRASP,
    ES_LEECHSEED,
    ES_INGRAIN,
    ES_OVERGROWTH,
    ES_CRUNCH,
    ES_MOWDOWN,
    ES_MAELSTROM,
    ES_METEOR,
    ES_BULLETSEED,
    ES_SEEDBOMB,
    ES_ENERGYBALL,
    ES_NATUREWRATH,
    ES_TENTACLEPOUND,
    ES_WRAP,
    ES_TSUNAMI,
    ES_TRIATTACK,
    ES_HELLFLAME,
    ES_SUPERNOVA,
    S_NORMALATTACK
} Skill;
/**
 * @brief Type enum
 * 
 * List of Type
 * */
typedef enum
{
    T_FIRE,
    T_GRASS,
    T_WATER,
    T_NORMAL,
    T_HEAL
} Type;

/**
 * @brief SkillInformation Structure
 * 
 * Structure to store Skill's Information
 * */
typedef struct SkillInformation
{
    Skill skilltype; /**< Skill name type */
    char name[STRING_LEN]; /**< Skill name */
    int dmg; /**< Skill damage */
    int mpcost; /**< Skill MP cost */
    Type type; /**< Skill action type */
} SkillInfo;
#endif