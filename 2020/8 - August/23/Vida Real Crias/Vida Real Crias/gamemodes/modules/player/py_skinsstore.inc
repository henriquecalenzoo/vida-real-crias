#include YSI\y_hooks

new skinidlist[MAX_PLAYERS];
new CostSkin[MAX_PLAYERS];

enum e_sls
{
    sls_sex[10],
    sls_skinid,
    sls_price
};

new SkinsListStore[215][e_sls] =
{
    {"Masculino", 0, 120},
    {"Masculino", 1, 145},
    {"Masculino", 2, 160},
    {"Masculino", 3, 150},
    {"Masculino", 4, 145},
    {"Masculino", 5, 150},
    {"Masculino", 6, 155},
    {"Masculino", 7, 150},
    {"Feminino", 9, 170},
    {"Feminino", 10, 165},
    {"Feminino", 12, 175},
    {"Feminino", 13, 180},
    {"Masculino", 14, 150},
    {"Masculino", 15, 145},
    {"Masculino", 17, 185},
    {"Masculino", 18, 130},
    {"Masculino", 19, 125},
    {"Masculino", 20, 135},
    {"Masculino", 21, 170},
    {"Masculino", 22, 160},
    {"Masculino", 23, 500},
    {"Masculino", 24, 145},
    {"Masculino", 25, 150},
    {"Masculino", 26, 180},
    {"Masculino", 27, 155},
    {"Masculino", 28, 135},
    {"Masculino", 29, 195},
    {"Masculino", 30, 165},
    {"Feminino", 31, 195},
    {"Masculino", 32, 170},
    {"Masculino", 33, 185},
    {"Masculino", 34, 175},
    {"Masculino", 35, 185},
    {"Masculino", 36, 150},
    {"Masculino", 37, 155},
    {"Feminino", 38, 160},
    {"Feminino", 39, 165},
    {"Feminino", 40, 175},
    {"Feminino", 41, 160},
    {"Masculino", 43, 165},
    {"Masculino", 44, 175},
    {"Masculino", 45, 125},
    {"Masculino", 47, 170},
    {"Masculino", 48, 165},
    {"Masculino", 49, 160},
    {"Masculino", 51, 150},
    {"Masculino", 52, 150},
    {"Feminino", 53, 160},
    {"Feminino", 54, 170},
    {"Feminino", 55, 185},
    {"Feminino", 56, 190},
    {"Masculino", 58, 155},
    {"Masculino", 60, 130},
    {"Masculino", 62, 140},
    {"Feminino", 63, 170},
    {"Feminino", 64, 175},
    {"Feminino", 65, 170},
    {"Masculino", 66, 150},
    {"Masculino", 67, 140},
    {"Feminino", 69, 160},
    {"Masculino", 72, 155},
    {"Masculino", 73, 160},
    {"Feminino", 75, 145},
    {"Feminino", 77, 140},
    {"Masculino", 78, 150},
    {"Masculino", 79, 145},
    {"Feminino", 85, 170},
    {"Masculino", 86, 160},
    {"Feminino", 87, 145},
    {"Feminino", 88, 155},
    {"Feminino", 89, 155},
    {"Feminino", 90, 170},
    {"Feminino", 91, 190},
    {"Feminino", 93, 150},
    {"Masculino", 94, 160},
    {"Masculino", 95, 165},
    {"Masculino", 96, 150},
    {"Masculino", 97, 140},
    {"Masculino", 98, 160},
    {"Masculino", 100, 150},
    {"Masculino", 101, 160},
    {"Masculino", 102, 165},
    {"Masculino", 103, 180},
    {"Masculino", 104, 170},
    {"Masculino", 105, 175},
    {"Masculino", 106, 160},
    {"Masculino", 107, 155},
    {"Masculino", 108, 150},
    {"Masculino", 109, 155},
    {"Masculino", 110, 160},
    {"Masculino", 111, 160},
    {"Masculino", 112, 170},
    {"Masculino", 114, 160},
    {"Masculino", 115, 175},
    {"Masculino", 116, 170},
    {"Masculino", 119, 170},
    {"Masculino", 122, 160},
    {"Masculino", 123, 170},
    {"Masculino", 126, 155},
    {"Masculino", 127, 165},
    {"Masculino", 128, 140},
    {"Feminino", 129, 160},
    {"Feminino", 130, 165},
    {"Feminino", 131, 160},
    {"Masculino", 132, 135},
    {"Masculino", 133, 140},
    {"Masculino", 134, 150},
    {"Masculino", 135, 130},
    {"Masculino", 136, 125},
    {"Masculino", 137, 130},
    {"Feminino", 138, 170},
    {"Feminino", 139, 170},
    {"Feminino", 140, 170},
    {"Feminino", 141, 195},
    {"Masculino", 142, 130},
    {"Masculino", 143, 135},
    {"Masculino", 149, 160},
    {"Feminino", 151, 160},
    {"Feminino", 152, 155},
    {"Masculino", 153, 180},
    {"Masculino", 154, 150},
    {"Masculino", 156, 140},
    {"Feminino", 157, 160},
    {"Masculino", 158, 165},
    {"Masculino", 159, 140},
    {"Masculino", 160, 160},
    {"Masculino", 161, 165},
    {"Masculino", 162, 130},
    {"Feminino", 169, 170},
    {"Masculino", 170, 165},
    {"Masculino", 173, 160},
    {"Masculino", 174, 165},
    {"Masculino", 175, 150},
    {"Masculino", 176, 155},
    {"Masculino", 177, 155},
    {"Feminino", 178, 185},
    {"Masculino", 179, 160},
    {"Masculino", 180, 190},
    {"Masculino", 181, 150},
    {"Masculino", 182, 140},
    {"Masculino", 183, 145},
    {"Masculino", 184, 160},
    {"Masculino", 188, 210},
    {"Feminino", 190, 165},
    {"Feminino", 192, 160},
    {"Feminino", 193, 180},
    {"Feminino", 195, 150},
    {"Feminino", 196, 140},
    {"Feminino", 197, 145},
    {"Feminino", 198, 150},
    {"Feminino", 199, 165},
    {"Masculino", 200, 130},
    {"Feminino", 201, 165},
    {"Masculino", 202, 170},
    {"Masculino", 206, 165},
    {"Feminino", 207, 155},
    {"Masculino", 208, 170},
    {"Masculino", 210, 145},
    {"Masculino", 212, 135},
    {"Masculino", 213, 130},
    {"Feminino", 214, 215},
    {"Feminino", 215, 185},
    {"Feminino", 216, 220},
    {"Feminino", 218, 160},
    {"Feminino", 219, 200},
    {"Masculino", 220, 140},
    {"Masculino", 221, 170},
    {"Masculino", 222, 130},
    {"Feminino", 224, 180},
    {"Feminino", 225, 170},
    {"Feminino", 226, 160},
    {"Masculino", 229, 155},
    {"Masculino", 230, 165},
    {"Feminino", 231, 155},
    {"Feminino", 232, 150},
    {"Feminino", 233, 140},
    {"Masculino", 234, 155},
    {"Masculino", 235, 160},
    {"Masculino", 236, 140},
    {"Feminino", 237, 175},
    {"Feminino", 238, 175},
    {"Masculino", 239, 130},
    {"Masculino", 241, 125},
    {"Masculino", 242, 130},
    {"Feminino", 243, 150},
    {"Feminino", 244, 155},
    {"Feminino", 245, 160},
    {"Feminino", 246, 170},
    {"Masculino", 247, 150},
    {"Masculino", 248, 155},
    {"Masculino", 249, 165},
    {"Masculino", 250, 170},
    {"Feminino", 251, 165},
    {"Masculino", 254, 150},
    {"Feminino", 256, 160},
    {"Feminino", 257, 165},
    {"Masculino", 258, 170},
    {"Masculino", 259, 165},
    {"Masculino", 261, 170},
    {"Masculino", 262, 150},
    {"Feminino", 263, 195},
    {"Masculino", 269, 170},
    {"Masculino", 270, 175},
    {"Masculino", 271, 170},
    {"Masculino", 272, 185},
    {"Masculino", 273, 170},
    {"Masculino", 289, 200},
    {"Masculino", 290, 170},
    {"Masculino", 291, 160},
    {"Masculino", 292, 165},
    {"Masculino", 293, 170},
    {"Masculino", 294, 175},
    {"Masculino", 297, 160},
    {"Feminino", 298, 170},
    {"Feminino", 299, 180}
};

stock ClickTextDrawSkinsStore(playerid, PlayerText:playertextid)
{
    if(playertextid == TDPlayerSkinsStore[playerid][2]) //exit
    {
        HideTDPlayerSkinsStore(playerid);

        SetSpawnInfo(playerid, 0, PlayerInfo[playerid][skin], 217.3514, -98.5038, 1005.2578, 200.0, 0, 0, 0, 0, 0, 0);

        SpawnPlayer(playerid);
        return 1;
    }
    if(playertextid == TDPlayerSkinsStore[playerid][3]) //buy
    {
        if(strcmp(SkinsListStore[skinidlist[playerid]][sls_sex], PlayerInfo[playerid][sexo]))
            return SendClientMessage(playerid, Erro, "Seu sexo n�o � o mesmo que a skin selecionada");

        if(PlayerInfo[playerid][Dinheiro] < SkinsListStore[skinidlist[playerid]][sls_price])
            return SendClientMessage(playerid, Erro, "Voc� n�o tem dinheiro suficiente");

        PlayerInfo[playerid][Dinheiro] -= SkinsListStore[skinidlist[playerid]][sls_price];
        UpdatePlayerMoney(playerid);

        if(strcmp(BusinessInfo[idbusiness[playerid]][cName], "N/A"))
            { BusinessInfo[idbusiness[playerid]][cSafe] += SkinsListStore[skinidlist[playerid]][sls_price]; }

        HideTDPlayerSkinsStore(playerid);
        PlayerInfo[playerid][skin] = SkinsListStore[skinidlist[playerid]][sls_skinid];
        SetSpawnInfo(playerid, 0, PlayerInfo[playerid][skin], 217.3514, -98.5038, 1005.2578, 200.0, 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);

        format(String, sizeof(String), "Voc� comprou a skin {FF4000}%s{FFFFFF} por {1b6302}$%d", SkinListName(SkinsListStore[skinidlist[playerid]][sls_skinid]), SkinsListStore[skinidlist[playerid]][sls_price]);
        SendClientMessage(playerid, White, String);
        return 1;
    }
    if(playertextid == TDPlayerSkinsStore[playerid][4]) //left
    {
        if(skinidlist[playerid] == 0)
            return SendClientMessage(playerid, Erro, "N�o tem mais skins");

        skinidlist[playerid]--;

        SetPlayerSkin(playerid, SkinsListStore[skinidlist[playerid]][sls_skinid]);
        format(String, sizeof(String), "~r~%s", SkinsListStore[skinidlist[playerid]][sls_sex]);
        PlayerTextDrawSetString(playerid, TDPlayerSkinsStore[playerid][0], String);
        PlayerTextDrawShow(playerid, TDPlayerSkinsStore[playerid][0]);
        format(String, sizeof(String), "~g~$%d", SkinsListStore[skinidlist[playerid]][sls_price]);
        PlayerTextDrawSetString(playerid, TDPlayerSkinsStore[playerid][1], String);
        PlayerTextDrawShow(playerid, TDPlayerSkinsStore[playerid][1]);
        return 1;
    }
    if(playertextid == TDPlayerSkinsStore[playerid][5]) //right
    {
        if(skinidlist[playerid] == 217)
            return SendClientMessage(playerid, Erro, "N�o tem mais skins");

        skinidlist[playerid]++;

        SetPlayerSkin(playerid, SkinsListStore[skinidlist[playerid]][sls_skinid]);
        format(String, sizeof(String), "~r~%s", SkinsListStore[skinidlist[playerid]][sls_sex]);
        PlayerTextDrawSetString(playerid, TDPlayerSkinsStore[playerid][0], String);
        PlayerTextDrawShow(playerid, TDPlayerSkinsStore[playerid][0]);
        format(String, sizeof(String), "~g~$%d", SkinsListStore[skinidlist[playerid]][sls_price]);
        PlayerTextDrawSetString(playerid, TDPlayerSkinsStore[playerid][1], String);
        PlayerTextDrawShow(playerid, TDPlayerSkinsStore[playerid][1]);
        return 1;
    }
    return 1;
}

stock ShowTDPlayerSkinsStore(playerid)
{
    CostSkin[playerid] = true;

    SetPlayerVirtualWorld(playerid, (playerid + 1));

    skinidlist[playerid] = 0;
    SetPlayerSkin(playerid, SkinsListStore[skinidlist[playerid]][sls_skinid]);

    TogglePlayerControllable(playerid, false);
    SelectTextDraw(playerid, Green);

    for(new i = 0; i < 7; i++)
    {
        TextDrawShowForPlayer(playerid, TDSkinsStore[i]);
    }
    for(new i = 0; i < 6; i++)
    {
        PlayerTextDrawShow(playerid, TDPlayerSkinsStore[playerid][i]);
    }
    return 1;
}

stock HideTDPlayerSkinsStore(playerid)
{
    CostSkin[playerid] = false;

    SetPlayerVirtualWorld(playerid, 0);

    TogglePlayerControllable(playerid, true);
    CancelSelectTextDraw(playerid);

    for(new i = 0; i < 7; i++)
    {
        TextDrawHideForPlayer(playerid, TDSkinsStore[i]);
    }
    for(new i = 0; i < 6; i++)
    {
        PlayerTextDrawHide(playerid, TDPlayerSkinsStore[playerid][i]);
    }

    SetSpawnInfo(playerid, 0, PlayerInfo[playerid][skin], 217.3514, -98.5038, 1005.2578, 200.0, 0, 0, 0, 0, 0, 0);

    SpawnPlayer(playerid);
    return 1;
}