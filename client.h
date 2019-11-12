#define BUF_SIZE 100
#define SKILL_COUNT 29
#define STRING_LEN 20
#define MAX_LEVEL 5
typedef enum {
    T_FIRE,
    T_GRASS,
    T_WATER,
    T_NORMAL,
    T_HEAL
} Type;
typedef enum {
    S_EMBER,
    S_VINEWHIP,
    S_WATERGUN,
    S_HEADBUTT,
    S_SLASH,
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
    S_NORMALATTACK
} Skill;
typedef struct UserInformation {
    char username[STRING_LEN];
    char password[STRING_LEN];
    int level;
    int curExp;
    int curHP;
    int curMP;
    int stage;
} UserInfo;
typedef struct UserInfoNode {
  UserInfo user;
  struct UserInfoNode *next;
} UserNode;
typedef struct SkillInformation {
    Skill skilltype;
    char name[STRING_LEN];
    int dmg;
    int mpcost;
    Type type;
} SkillInfo;
typedef struct LevelInformation {
    int level;
    int hp;
    int mp;
    int atk;
    int def;
    int maxexp;
    int count;
    SkillInfo skills[20];
} LevelInfo;
typedef struct MonsterInformation {
    char name[STRING_LEN];
    int hp;
    int mp;
    int atk;
    int def;
    int exp;
    Type type;
    SkillInfo skills[4];
} MonsterInfo;
typedef struct StageInformation {
    int number;
    MonsterInfo monsters[10];
} StageInfo;
//UTILITY FUNCTIONS
UserNode *makeNewNode(UserInfo data);                          //Create a new node for the account linked list

UserNode *insertNode(UserNode *root, UserNode *new);            //Append the new node to the account linked list

void freeList(UserNode *root);