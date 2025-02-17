CMD:avisar(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id, reason[24];

    if(sscanf(params, "us[24]", id, reason))
        return SendClientMessage(playerid, Erro, "Digite: /Avisar [id/nome] [motivo]");

    if(id == INVALID_PLAYER_ID || !PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    if(PrisonEnum[id][pTempo] != 0)
        return SendClientMessage(playerid, Erro, "O(A) jogador(a) est� preso");

    new warning = GetIntQuery(id, "Identidade", "avisos");

    warning++;
    SetIntQuery(id, "Identidade", "avisos", warning);
    format(String, MAX_STRING, "VRC-Admin ~ O(A) %s %s avisou o(a) jogador(a) %s ( %d/3 )( Motivo: %s )", CargoAdmin(playerid), PlayerInfo[playerid][Nome], PlayerInfo[id][Nome], warning, reason);
    SendClientMessageToAll(Red, String);

    if(warning == 3)
    {
        SetIntQuery(id, "Identidade", "avisos", 0);

        format(String, MAX_STRING, "VRC-Admin ~ Por receber 3 avisos o(a) jogador(a) %s foi preso por 30 minutos", PlayerInfo[id][Nome]);
        SendClientMessageToAll(Red, String);

        SetPlayerPrision(id, PlayerInfo[playerid][Nome], "Federal", reason, 30);
    }
    return 1;
}

CMD:espiar(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id;

    if(sscanf(params, "u", id))
        return SendClientMessage(playerid, Erro, "Digite: /Espiar [id/nome]");

    if(id == INVALID_PLAYER_ID || !PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    if(PlayerInfo[id][tutorial])
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a) est� no tutorial");

    GetPlayerFacingAngle(playerid, stopspying[3]);
    GetPlayerPos(playerid, stopspying[0], stopspying[1], stopspying[2]);

    TogglePlayerSpectating(playerid, true);
    PlayerSpectatePlayer(playerid, id);
    SetPlayerInterior(playerid, GetPlayerInterior(id));
    SendClientMessage(playerid, adm, "VRC-Admin ~ Comando efetuado com sucesso");
    return 1;
}
CMD:pararespiar(playerid)
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    SetPlayerInterior(playerid, 0);
    TogglePlayerSpectating(playerid, false);
    SetPlayerFacingAngle(playerid, stopspying[3]);
    SetPlayerPos(playerid, stopspying[0], stopspying[1], stopspying[2]);
    SendClientMessage(playerid, adm, "VRC-Admin ~ Comando efetuado com sucesso");
    return 1;
}
CMD:tapa(playerid, params[])
{
    if(!IsPlayerIntern(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id, Float:x, Float:y, Float:z;

    if(sscanf(params, "u", id))
        return SendClientMessage(playerid, Erro, "Digite: /Tapa [id/nome]");

    if(id == INVALID_PLAYER_ID || !PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    GetPlayerPos(id, x, y, z);
    SetPlayerPos(id, x, y, z+50);
    format(String, MAX_STRING, "VRC-Admin ~ O(A) %s %s te deu um tapa", CargoAdmin(playerid), PlayerInfo[playerid][Nome]);
    SendClientMessage(id, adm, String);
    format(String, MAX_STRING, "VRC-Admin ~ Voc� deu um tapa no jogador(a) %s[%d]", PlayerInfo[id][Nome], id);
    SendClientMessage(playerid, adm, String);
    return 1;
}
CMD:kick(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id, tmp[128];

    if(sscanf(params, "us[128]", id, tmp))
        return SendClientMessage(playerid, Erro, "Digite: /Kick [id/nome] [motivo]");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    GameTextForPlayer(id,"~r~kickado~w~!", 2500, 3);
    format(String, MAX_STRING, "VRC-Admin ~ O(A) %s %s kickou o(a) jogador(a) %s ( Motivo: %s )", CargoAdmin(playerid), PlayerInfo[playerid][Nome], PlayerInfo[id][Nome], tmp);
    SendClientMessageToAll(Red, String);
    format(String, MAX_STRING, "VRC-Admin ~ Voc� kickou o(a) Jogador(a) %s[%d]", PlayerInfo[id][Nome], id);
    SendClientMessage(playerid, adm, String);
    Kick(id);
    return 1;
}
CMD:ir(playerid, params[])
{
    if(!IsPlayerIntern(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id, Float:x, Float:y, Float:z;

    if(sscanf(params, "u", id))
        return SendClientMessage(playerid, Erro, "Digite: /Ir [id/nome]");

    if(id == INVALID_PLAYER_ID || !PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    if(GetPlayerInterior(id) != 0 || GetPlayerInterior(playerid) != 0)
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a)/Voc� est� em um interior");

    if(PlayerInfo[id][tutorial])
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a) est� no tutorial");

    GetPlayerPos(id, x, y, z);
    SetPlayerPos(playerid, x, y, z);
    SetPlayerInterior(playerid, GetPlayerInterior(id));

    format(String, MAX_STRING, "VRC-Admin ~ O(A) %s %s[%d] veio at� sua posi��o", CargoAdmin(playerid), PlayerInfo[playerid][Nome], playerid);
    SendClientMessage(id, adm, String);
    format(String, MAX_STRING, "VRC-Admin ~ Voc� foi at� a posi��o do jogador(a) %s[%d]", PlayerInfo[id][Nome], id);
    SendClientMessage(playerid, adm, String);
    return 1;
}

CMD:trazer(playerid, params[])
{
    if(!IsPlayerIntern(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id, Float:x, Float:y, Float:z;

    if(sscanf(params, "u", id))
        return SendClientMessage(playerid, Erro, "Digite: /Trazer [id/nome]");

    if(id == INVALID_PLAYER_ID || !PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    if(GetPlayerInterior(id) != 0 || GetPlayerInterior(playerid) != 0)
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a)/Voc� est� em um interior");

    if(PlayerInfo[id][tutorial])
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a) est� no tutorial");

    GetPlayerPos(playerid, x, y, z);
    SetPlayerPos(id, x, y, z);
    SetPlayerInterior(id, GetPlayerInterior(playerid));

    format(String, MAX_STRING, "VRC-Admin ~ O(A) %s %s[%d] puxou voc�", CargoAdmin(playerid), PlayerInfo[playerid][Nome], playerid);
    SendClientMessage(id, adm, String);
    format(String, MAX_STRING, "VRC-Admin ~ Voc� puxou jogador(a) %s[%d]", PlayerInfo[id][Nome], id);
    SendClientMessage(playerid, adm, String);
    return 1;
}
CMD:punicao(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id, tempo, tmp[128];

    if(sscanf(params, "uds[128]", id, tempo, tmp))
        return SendClientMessage(playerid, Erro, "Digite: /Punicao [id/nome] [tempo] [motivo]");

    if(id == INVALID_PLAYER_ID || !PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    if(tempo <= 0 || tempo > 1000)
            return SendClientMessage(playerid, Erro, "Tempo s� permitido entre 1 e 1000");

    if(PrisonEnum[id][pTempo] != 0)
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a) j� est� preso(a)");

    format(String, MAX_STRING, "VRC-Admin ~ O(A) %s %s prendeu o(a) jogador(a) %s por %d minutos ( Motivo: %s )", CargoAdmin(playerid), PlayerInfo[playerid][Nome], PlayerInfo[id][Nome], tempo, PrisonEnum[id][pMotivo]);
    SendClientMessageToAll(adm, String);

    SetPlayerPrision(id, PlayerInfo[playerid][Nome], "Federal", tmp, tempo);
    return 1;
}
CMD:despunicao(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id;

    if(sscanf(params, "u", id))
        return SendClientMessage(playerid, Erro, "Digite: /Despunicao [id/nome]");

    if(id == INVALID_PLAYER_ID || !PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    if(PrisonEnum[id][pTempo] == 0)
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a) n�o esta preso(a)");

    KillTimer(TempoPreso[id]);

    SetPlayerInterior(id, 0);
    SetPlayerHealth(id, 100);
    SetPlayerPos(id, 1554.8657,-1675.6693,16.1953);

    PrisonEnum[id][pCadeia] = 0;
    PrisonEnum[id][pTempo] = 0;
    format(PrisonEnum[id][pMotivo], 1, "");

    new query[200];
    mysql_format(IDConexao, query, 200, "DELETE FROM `Prison` WHERE `id_contas`='%d'", PlayerInfo[id][ID]);
    mysql_query(IDConexao, query);

    PlayerTextDrawHide(id, TempoPresidio[id][2]);
    PlayerTextDrawHide(id, TempoPresidio[id][1]);
    PlayerTextDrawHide(id, TempoPresidio[id][0]);

    GameTextForPlayer(id, "~w~Solto!", 3000, 0);
    format(String, MAX_STRING, "VRC-Admin ~ Voc� soltou o(a) jogador(a) %s[%d] da pris�o", PlayerInfo[id][Nome], id);
    SendClientMessage(playerid, adm, String);
    format(String, MAX_STRING, "VRC-Admin ~ O(A) %s %s[%d] soltou voc� da pris�o", CargoAdmin(playerid), PlayerInfo[playerid][Nome], playerid);
    SendClientMessage(id, adm, String);
    return 1;
}
CMD:criarveiculo(playerid, params[])
{
    if(!IsPlayerIntern(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    if(IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, Erro, "Voc� est� em um veiculo");

    new id, color1, color2, Float:x, Float:y, Float:z, Float:a;

    if(sscanf(params, "ddd", id, color1, color2))
        return SendClientMessage(playerid, Erro, "Digite: /CriarVeiculo [id-carro] [id-cor] [id-cor]");

    if(id < 400 || id > 611)
        return SendClientMessage(playerid, Erro, "ID do Veiculo Inv�lido, Digite entre: 400 a 611");

    switch(id)
    {
        case 435, 441, 449, 450, 464, 465, 501, 537, 538, 564, 569, 570, 584, 590, 591, 594, 606..608, 610, 611:
            return SendClientMessage(playerid, Erro, "N�o � poss�vel criar este ve�culo, tente outro");
    }

    if(color1 < 0 || color1 > 255)
        return SendClientMessage(playerid, Erro, "ID da Cor Inv�lida, Digite entre: 0 a 255");

    if(color2 < 0 || color2 > 255)
        return SendClientMessage(playerid, Erro, "ID da Cor Inv�lida, Digite entre: 0 a 255");

    GetPlayerFacingAngle(playerid, a);
    GetPlayerPos(playerid, x, y, z);

    VehicleAdmin[playerid] = CreateVehicleEx(id, x-2, y, z, a, color1, color2, true);

    PutPlayerInVehicle(playerid, VehicleAdmin[playerid], 0);
    LinkVehicleToInterior(VehicleAdmin[playerid], GetPlayerInterior(playerid));

    format(String, MAX_STRING, "VRC-Admin ~ Voc� criou o ve�culo %s ID %d", getVehicleName(GetVehicleModel(id)), id);
    SendClientMessage(playerid, adm, String);
    return 1;
}
CMD:ac(playerid, params[])
{
    if(!IsPlayerIntern(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new tmp[128];

    if(sscanf(params, "s[128]", tmp))
        return SendClientMessage(playerid,Erro, "Digite: /Ac [mensagem]");

    format(String, MAX_STRING, "Chat-Admin ~ %s %s [%d] diz: %s", CargoAdmin(playerid), PlayerInfo[playerid][Nome], playerid, tmp);

    for(new i = 0; i < MAX_PLAYERS; i++)
    {
        if(IsPlayerIntern(i))
        {
            SendClientMessage(i, adm, String);
        }
    }

    #if !SERVER_OFFLINE
        TextConverterDiscord(tmp);

        format(String, 256, "%s %s [%d] diz: ```%s```", CargoAdmin(playerid), PlayerInfo[playerid][Nome], playerid, tmp);
        DCC_SendChannelMessage(Channels[dsc_admin], String);
    #endif

    return 1;
}
CMD:a(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new tmp[128];

    if(sscanf(params, "s[128]", tmp))
        return SendClientMessage(playerid,Erro, "Digite: /A [mensagem]");

    format(String, MAX_STRING, "* %s %s: %s", CargoAdmin(playerid), PlayerInfo[playerid][Nome], tmp);
    SendClientMessageToAll(0x0099CCAA, String);
    return 1;
}
CMD:cnn(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new tmp[128];

    if(sscanf(params, "s[128]", tmp))
        return SendClientMessage(playerid, Erro, "Digite: /Cnn [mensagem]");

    TextConverter(tmp);

    format(String, MAX_STRING, "~r~# ~p~%s~w~: %s ~r~#", PlayerInfo[playerid][Nome], tmp);
    TextDrawSetString(RespawnVeiculos, String);
    TextDrawShowForAll(RespawnVeiculos);
    SetTimer("HideTextRespawn", 1500, false);
    return 1;
}
CMD:ann(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new tmp[128];

    if(sscanf(params, "s[128]", tmp))
        return SendClientMessage(playerid, Erro, "Digite: /Ann [mensagem]");

    TextConverter(tmp);

    format(String, 50, "~r~#~w~%s ~r~#", tmp);
    TextDrawSetString(RespawnVeiculos, String);
	TextDrawShowForAll(RespawnVeiculos);
	SetTimer("HideTextRespawn", 1500, false);
    return 1;
}
CMD:godmodon(playerid)
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    SetPlayerHealth(playerid, 99999);
    SetPlayerArmour(playerid, 99999);
    SendClientMessage(playerid, adm, "VRC-Admin ~ Comando efetuado com sucesso");
    return 1;
}
CMD:godmodoff(playerid)
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    SetPlayerHealth(playerid, 100);
    SetPlayerArmour(playerid, 0);
    SendClientMessage(playerid, adm, "VRC-Admin ~ Comando efetuado com sucesso");
    return 1;
}
CMD:verip(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id, IP[32];

    if(sscanf(params, "u", id))
        return SendClientMessage(playerid, Erro, "Digite: /VerIP [id/nome]");

    if(id == INVALID_PLAYER_ID || !PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    GetPlayerIp(id, IP, 32);

    format(String, MAX_STRING, "VRC-Admin ~ IP do(a) jogador(a) %s[%d] : %s",  PlayerInfo[id][Nome], id, IP);
    SendClientMessage(playerid, adm, String);
    return 1;
}
CMD:congelar(playerid, params[])
{
    if(!IsPlayerHelper(playerid))
        return SendClientMessage(playerid, Erro, "Comando Inv�lido");

    new id;

    if(sscanf(params, "u", id))
        return SendClientMessage(playerid, Erro, "Digite: /Congelar [id/nome]");

    if(id == INVALID_PLAYER_ID || !PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    if(PlayerInfo[id][frozen]){
        TogglePlayerControllable(id, true);
        PlayerInfo[id][frozen] = false;
    } else {
        TogglePlayerControllable(id, false);
        PlayerInfo[id][frozen]= true;
    }

    format(String, MAX_STRING, "VRC-Admin ~ Jogador(a) %s[%d] %s(a)",  PlayerInfo[id][Nome], id, (PlayerInfo[id][frozen] ? ("congelado") : ("descongelado")));
    SendClientMessage(playerid, adm, String);
    format(String, MAX_STRING, "VRC-Admin ~ %s %s l� %s", CargoAdmin(playerid), PlayerInfo[playerid][Nome], (PlayerInfo[id][frozen] ? ("congelou") : ("descongelou")));
    SendClientMessage(id, adm, String);
    return 1;
}
