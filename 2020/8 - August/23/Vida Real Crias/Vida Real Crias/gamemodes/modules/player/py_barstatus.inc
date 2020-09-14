#include YSI\y_hooks

hook OnPlayerDisconnect(playerid, reason)
{
    UpdateProgressBar(playerid);

    Progress[playerid][Fome] = 0.0;
    Progress[playerid][Sede] = 0.0;
    Progress[playerid][Sono] = 0.0;
    Progress[playerid][Vida] = 0.0;
    KillTimer(TimerBarStatus[playerid]);
    return 1;
}

forward ProgrecoBar(playerid);
public ProgrecoBar(playerid)
{
    if(PrisonEnum[playerid][pTempo] || IsArena[playerid] || PlayerInfo[playerid][tutorial]) return 0;

    if(Progress[playerid][Fome] < 100.0)
    {
        if(Progress[playerid][Fome] == 95.0 || Progress[playerid][Fome] == 90.0)
        {
            SendClientMessage(playerid, 0xFF8000AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            SendClientMessage(playerid, 0xFFFFFFAA, "Voc� est� com muita fome!");
            SendClientMessage(playerid, 0xFFFFFFAA, "V� at� o restaurante mais pr�ximo!");
            SendClientMessage(playerid, 0xFF8000AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        }

        Progress[playerid][Fome] += 1.5;
    }
    else
    {
        PlayerInfo[playerid][Health] -= 10.0;

        if(PlayerInfo[playerid][Health] <= 0.0)
        {
            PlayerInfo[playerid][Health] = 0.0;
            SetPlayerHealth(playerid, PlayerInfo[playerid][Health]);

            Progress[playerid][Fome] = 95.0;

            SendClientMessage(playerid, 0xFF8000AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            SendClientMessage(playerid, 0xFFFFFFAA, "Voc� perdeu a conci�ncia e foi levado pro hospital mais pr�ximo!");
            SendClientMessage(playerid, 0xFFFFFFAA, "V� at� o restaurante mais pr�ximo!");
            SendClientMessage(playerid, 0xFF8000AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        }
        else
        {
            SetPlayerHealth(playerid, PlayerInfo[playerid][Health]);
        }
    }

    if(Progress[playerid][Sede] < 100.0)
    {
        if(Progress[playerid][Sede] == 95.0 || Progress[playerid][Sede] == 90.0)
        {
            SendClientMessage(playerid, 0x008000AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            SendClientMessage(playerid, 0xFFFFFFAA, "Voc� est� com muita sede!");
            SendClientMessage(playerid, 0xFFFFFFAA, "V� at� o restaurante mais pr�ximo!");
            SendClientMessage(playerid, 0x008000AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        }

        Progress[playerid][Sede] += 1.0;
    }
    else
    {
        PlayerInfo[playerid][Health] -= 10.0;

        if(PlayerInfo[playerid][Health] <= 0.0)
        {
            PlayerInfo[playerid][Health] = 0.0;
            SetPlayerHealth(playerid, PlayerInfo[playerid][Health]);

            Progress[playerid][Sede] = 95.0;

            SendClientMessage(playerid, 0x008000AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            SendClientMessage(playerid, 0xFFFFFFAA, "Voc� perdeu a conci�ncia e foi levado pro hospital mais pr�ximo!");
            SendClientMessage(playerid, 0xFFFFFFAA, "V� at� o restaurante mais pr�ximo!");
            SendClientMessage(playerid, 0x008000AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        }
        else
        {
            SetPlayerHealth(playerid, PlayerInfo[playerid][Health]);
        }
    }

    if(Progress[playerid][Sono] < 100.0)
    {
        if(Progress[playerid][Sono] == 90.0 || Progress[playerid][Sono] == 95.0)
        {
            SendClientMessage(playerid, 0x0080C0AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            SendClientMessage(playerid, 0xFFFFFFAA, "Voc� est� com muito sono!");
            SendClientMessage(playerid, 0xFFFFFFAA, "V� at� a sua casa/hotel e digite: /dormir!");
            SendClientMessage(playerid, 0x0080C0AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        }
        else if(Progress[playerid][Sono] == 98.0)
        {
            TimerEffectSleep[playerid] = SetTimerEx("SleepEffect", 3000, true, "d", playerid);
            SendClientMessage(playerid, 0x0080C0AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            SendClientMessage(playerid, 0xFFFFFFAA, "Voc� est� com muito sono!");
            SendClientMessage(playerid, 0xFFFFFFAA, "V� at� a sua casa/hotel e digite: /dormir!");
            SendClientMessage(playerid, 0x0080C0AA, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        }

        Progress[playerid][Sono] += 0.5;
    }
    else
    {
        if(Sleeping[playerid] == false)
        {
            TimerSleeping[playerid] = SetTimerEx("Sleep", 1000, true, "d", playerid);
            SendClientMessage(playerid, 0xFFFFFFAA, "Voc� est� com muito sono e acabou perdendo a conci�ncia! {0080C0}zzZZzZZZ");
        }
    }

    UpdateProgressBar(playerid);
    return 1;
}

stock UpdateProgressBar(playerid)
{
    PlayerTextDrawTextSize(playerid, PlayerBarStatus[playerid][2], ((IsPlayerMobile(playerid) ? (513.0) : (593.0)) - ((49.0 * Progress[playerid][Fome]) / 100)), 0.0);
    PlayerTextDrawShow(playerid, PlayerBarStatus[playerid][2]);
    PlayerTextDrawTextSize(playerid, PlayerBarStatus[playerid][3], ((IsPlayerMobile(playerid) ? (513.0) : (593.0)) - ((49.0 * Progress[playerid][Sede]) / 100)), 0.0);
    PlayerTextDrawShow(playerid, PlayerBarStatus[playerid][3]);
    PlayerTextDrawTextSize(playerid, PlayerBarStatus[playerid][4], ((IsPlayerMobile(playerid) ? (513.0) : (593.0)) - ((49.0 * Progress[playerid][Sono]) / 100)), 0.0);
    PlayerTextDrawShow(playerid, PlayerBarStatus[playerid][4]);
    PlayerTextDrawTextSize(playerid, PlayerBarStatus[playerid][5], ((IsPlayerMobile(playerid) ? (513.0) : (593.0)) - ((49.0 * Progress[playerid][Vida]) / 100)), 0.0);
    PlayerTextDrawShow(playerid, PlayerBarStatus[playerid][5]);


    mysql_format(IDConexao, String, sizeof(String), "UPDATE `Status` SET `fome`='%f', `sede`='%f', `sono`='%f', `vida`='%f' WHERE `id_contas`='%d'", Progress[playerid][Fome], Progress[playerid][Sede], Progress[playerid][Sono], Progress[playerid][Vida], PlayerInfo[playerid][ID]);
    mysql_query(IDConexao, String);
    return 1;
}