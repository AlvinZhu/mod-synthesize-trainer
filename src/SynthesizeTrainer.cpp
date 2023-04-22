#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptedGossip.h"
#include "Chat.h"

class CreatureScript_SynthesizeTrainer : public CreatureScript
{
public:
    CreatureScript_SynthesizeTrainer() : CreatureScript("synthesize_trainer") {}

    bool OnGossipHello(Player *player, Creature *creature) override
    {
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "职业技能训练", 1, 1);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "商业技能训练", 1, 2);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "骑术技能训练", 1, 3);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "武器技能训练", 1, 4);
        if (player->GetSpecsCount() == 1 && player->getLevel() >= sWorld->getIntConfig(CONFIG_MIN_DUALSPEC_LEVEL))
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "开双天赋专精", 1, 5);
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature);
        return true;
    }

    bool OnGossipSelect(Player *player, Creature *creature, uint32 Sender, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();

        if (Sender == 1)
        {
            if (action == 1) {
                uint32 npcspellid = 0;
                switch (player->getClass())
                {
                    case CLASS_WARRIOR: npcspellid = 3042; break;
                    case CLASS_PALADIN:   player->GetTeamId() == TEAM_HORDE ? npcspellid = 16679 : npcspellid = 16761; break;
                    case CLASS_HUNTER:    npcspellid = 3352; break;
                    case CLASS_ROGUE:    npcspellid = 3328; break;
                    case CLASS_PRIEST:    npcspellid = 6014; break;
                    case CLASS_DEATH_KNIGHT:    npcspellid = 28472; break;
                    case CLASS_SHAMAN:    npcspellid = 3344; break;
                    case CLASS_MAGE:    npcspellid = 16652; break;
                    case CLASS_WARLOCK:    npcspellid = 988; break;
                    case CLASS_DRUID:    npcspellid = 3036; break;
                }
                player->GetSession()->SendTrainerList(creature->GetGUID(), npcspellid);
                CloseGossipMenuFor(player);
            }
            else if (action == 2) {
                learnPSkill(player, creature); 
            }
            else if (action == 3) {
                player->GetSession()->SendTrainerList(creature->GetGUID(), 31238);
                CloseGossipMenuFor(player);
            }
            else if (action == 4) {
                player->GetSession()->SendTrainerList(creature->GetGUID(), 190017);
                CloseGossipMenuFor(player);
            }
            else if (action == 5) {
                // Cast spells that teach dual spec
                // Both are also ImplicitTarget self and must be cast by player
                player->CastSpell(player, 63680, true, NULL, NULL, player->GetGUID());
                player->CastSpell(player, 63624, true, NULL, NULL, player->GetGUID());

                ChatHandler(player->GetSession()).PSendSysMessage("开双天赋专精成功!");
                player->PlayerTalkClass->SendCloseGossip();
            }
        }
        else if (Sender == 2) {
            uint32 npcskillid = 0; //技能训练师ID
            switch (action)
            {
                case 1:     npcskillid = 28698; break; //采矿
                case 2:     npcskillid = 28704; break; //草药
                case 3:     npcskillid = 28703; break; //炼金
                case 4:     npcskillid = 28693; break; //附魔
                case 5:     npcskillid = 28694; break; //锻造
                case 6:     npcskillid = 28699; break; //裁缝
                case 7:     npcskillid = 28697; break; //工程
                case 8:     npcskillid = 28701; break; //珠宝
                case 9:     npcskillid = 28700; break; //制皮
                case 10:    npcskillid = 28696; break; //剥皮
                case 11:    npcskillid = 28702; break; //铭文
                case 12:    npcskillid = 28705; break; //烹饪
                case 13:    npcskillid = 28742; break; //钓鱼
                case 14:    npcskillid = 28706; break; //急救
            }
            player->GetSession()->SendTrainerList(creature->GetGUID(), npcskillid);
            CloseGossipMenuFor(player);
        }
        return true;
    }
   //专业训练菜单
    static void learnPSkill(Player* player, Creature* creature)
    {
        player->PlayerTalkClass->ClearMenus();
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "采矿训练", 2, 1);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "草药训练", 2, 2);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "炼金训练", 2, 3);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "附魔训练", 2, 4);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "锻造训练", 2, 5);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "裁缝训练", 2, 6);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "工程训练", 2, 7);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "珠宝训练", 2, 8);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "制皮训练", 2, 9);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "剥皮训练", 2, 10);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "铭文训练", 2, 11);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "烹饪训练", 2, 12);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "钓鱼训练", 2, 13);
        AddGossipItemFor(player, GOSSIP_ICON_TRAINER, "急救训练", 2, 14);
        SendGossipMenuFor(player, DEFAULT_GOSSIP_MESSAGE, creature);
    }
};

void AddSC_SynthesizeTrainer()
{
    new CreatureScript_SynthesizeTrainer();
}
