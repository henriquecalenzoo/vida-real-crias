public OnPlayerText(playerid, text[])
{
    if(!PlayerInfo[playerid][Logado]){
        SendClientMessage(playerid, Erro, "Voc� n�o est� logado");
        return 0;
    }
    if(AntiAfk[playerid][aa_afk]){
        SendClientMessage(playerid, Erro, "Antes de falar, digite: /Sairafk");
        return 0;
    }
    if(PrisonEnum[playerid][pTempo]){
        SendClientMessage(playerid, Erro, "Voc� est� preso e n�o pode usar o chat");
        return 0;
    }
    if(PlayerInfo[playerid][tutorial]){
        SendClientMessage(playerid, Erro, "Voc� est� no tutorial e n�o pode usar o chat");
        return 0;
    }
    if(PlayerInfo[playerid][load]){
        SendClientMessage(playerid, Erro, "Seus dados est�o sendo carregado, aguarde alguns segundos...");
        return 0;
    }

    for(new i = 0; i < MAX_STRING; i++)
    {
        if(!strfind(text[i], ".com") || !strfind(text[i], ".br") || !strfind(text[i], ":7777") || !strfind(text[i], ":7778"))
        {
            new warning = GetIntQuery(playerid, "Identidade", "avisos");

            warning++;
            SetIntQuery(playerid, "Identidade", "avisos", warning);
            format(String, MAX_STRING, "VRC-Admin ~ O Bot avisou o(a) jogador(a) %s ( %d/3 )( Motivo: Divulga��o )", PlayerInfo[playerid][Nome], warning);
            SendClientMessageToAll(Red, String);

            if(warning == 3)
            {
                SetIntQuery(playerid, "Identidade", "avisos", 0);

                format(String, MAX_STRING, "VRC-Admin ~ Por receber 3 avisos o(a) jogador(a) %s foi preso por 30 minutos", PlayerInfo[playerid][Nome]);
                SendClientMessageToAll(Red, String);

                SetPlayerPrision(playerid, "Bot", "Federal", "Divulgacao", 30);
            }
            return 0;
        }
    }

    //Staffs login
    new query[100];
    mysql_format(IDConexao, query, 100, "SELECT * FROM `Staffs` WHERE `code`='%e'", text);
    mysql_query(IDConexao, query);

    if(cache_num_rows() > 0)
    {
        if(IsPlayerHelper(playerid))
        {
            SendClientMessage(playerid, Erro, "Voc� j� est� exercendo seu cargo");
            return 0;
        }

        cache_get_value_int(0, "nivel", PlayerInfo[playerid][Admin]);

        format(String, MAX_STRING, "VRC-Admin ~ Ol� %s %s[%d], agora voc� pode exerce seu cargo", CargoAdmin(playerid), PlayerInfo[playerid][Nome], playerid);
        SendClientMessage(playerid, adm, String);
        return 0;
    }


    if(IsPlayerMemberBaseEx(playerid))
    {
        for(new baseid = 0; baseid < MAX_BASES; baseid++)
        {
            if(IsPlayerMemberBaseEx(playerid, baseid))
            {
                if(IsPlayerYoutuber(playerid))
                    format(String, MAX_STRING, "[%s][{800000}Youtuber{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", BaseInfo[baseid][bi_tag], (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
                else if(IsPlayerVip(playerid))
                    format(String, MAX_STRING, "[%s][{%s}VIP{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", BaseInfo[baseid][bi_tag], VipInfo[playerid][tagcolor], (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
                else if(PlayerInfo[playerid][Admin] == 1)
                    format(String, MAX_STRING, "[%s][{804000}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", BaseInfo[baseid][bi_tag], CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
                else if(PlayerInfo[playerid][Admin] == 2)
                    format(String, MAX_STRING, "[%s][{FFFF00}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", BaseInfo[baseid][bi_tag], CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
                else if(PlayerInfo[playerid][Admin] == 3)
                    format(String, MAX_STRING, "[%s][{FF8C00}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", BaseInfo[baseid][bi_tag], CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
                else if(PlayerInfo[playerid][Admin] == 4)
                    format(String, MAX_STRING, "[%s][{008bce}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", BaseInfo[baseid][bi_tag], CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
                else if(PlayerInfo[playerid][Admin] == 5)
                    format(String, MAX_STRING, "[%s][{FF0000}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", BaseInfo[baseid][bi_tag], CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
                else if(PlayerInfo[playerid][Admin] == 6)
                    format(String, MAX_STRING, "[%s][{328E0A}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", BaseInfo[baseid][bi_tag], CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
                else
                    format(String, MAX_STRING, "[%s]{%06x}%s{FFFFFF}[%d]: %s", BaseInfo[baseid][bi_tag], (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);

                LocalMessage(30.0, playerid, String, -1);
                break;
            }
        }
    }
    else
    {
        if(IsPlayerYoutuber(playerid))
            format(String, MAX_STRING, "[{800000}Youtuber{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
        else if(IsPlayerVip(playerid))
            format(String, MAX_STRING, "[{%s}VIP{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", VipInfo[playerid][tagcolor], (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
        else if(PlayerInfo[playerid][Admin] == 1)
            format(String, MAX_STRING, "[{804000}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
        else if(PlayerInfo[playerid][Admin] == 2)
            format(String, MAX_STRING, "[{FFFF00}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
        else if(PlayerInfo[playerid][Admin] == 3)
            format(String, MAX_STRING, "[{FF8C00}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
        else if(PlayerInfo[playerid][Admin] == 4)
            format(String, MAX_STRING, "[{008bce}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
        else if(PlayerInfo[playerid][Admin] == 5)
            format(String, MAX_STRING, "[{FF0000}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
        else if(PlayerInfo[playerid][Admin] == 6)
            format(String, MAX_STRING, "[{328E0A}%s{FFFFFF}]{%06x}%s{FFFFFF}[%d]: %s", CargoAdmin(playerid), (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);
        else
            format(String, MAX_STRING, "{%06x}%s{FFFFFF}[%d]: %s", (GetPlayerColor(playerid) >>> 8), PlayerInfo[playerid][Nome], playerid, text);

        LocalMessage(30.0, playerid, String, -1);
    }
    return 0;
}

forward LocalMessage(Float:radi, playerid, string[], color);
public LocalMessage(Float:radi, playerid, string[], color)
{
    if(PlayerInfo[playerid][Logado])
    {
        new Float:posx, Float:posy, Float:posz;
        new Float:oldposx, Float:oldposy, Float:oldposz;
        new Float:tempposx, Float:tempposy, Float:tempposz;
        GetPlayerPos(playerid, oldposx, oldposy, oldposz);

        for(new i; i < MAX_PLAYERS; i++)
        {
            if(PlayerInfo[i][Logado] && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
            {
                GetPlayerPos(i, posx, posy, posz);
                tempposx = (oldposx -posx);
                tempposy = (oldposy -posy);
                tempposz = (oldposz -posz);
                if (((tempposx < radi/16) && (tempposx > -radi/16)) && ((tempposy < radi/16) && (tempposy > -radi/16)) && ((tempposz < radi/16) && (tempposz > -radi/16))) {
                    SendClientMessage(i, color, string);
                } else if (((tempposx < radi/8) && (tempposx > -radi/8)) && ((tempposy < radi/8) && (tempposy > -radi/8)) && ((tempposz < radi/8) && (tempposz > -radi/8))) {
                    SendClientMessage(i, color, string);
                } else if (((tempposx < radi/4) && (tempposx > -radi/4)) && ((tempposy < radi/4) && (tempposy > -radi/4)) && ((tempposz < radi/4) && (tempposz > -radi/4))) {
                    SendClientMessage(i, color, string);
                } else if (((tempposx < radi/2) && (tempposx > -radi/2)) && ((tempposy < radi/2) && (tempposy > -radi/2)) && ((tempposz < radi/2) && (tempposz > -radi/2))) {
                    SendClientMessage(i, color, string);
                } else if (((tempposx < radi) && (tempposx > -radi)) && ((tempposy < radi) && (tempposy > -radi)) && ((tempposz < radi) && (tempposz > -radi))) {
                    SendClientMessage(i, color, string);
                }
            }
        }
    }
    return 1;
}
