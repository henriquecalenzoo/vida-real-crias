#include YSI\y_hooks

hook OnGameModeInit()
{
    new db_identidade[1000];
    strins(db_identidade, "CREATE TABLE IF NOT EXISTS `Identidade` (", strlen(db_identidade));
    strins(db_identidade, "`id` int AUTO_INCREMENT, ", strlen(db_identidade));
    strins(db_identidade, "`profissao` int(3) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`minup` int(3) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`segup` int(3) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`level` int(11) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`experiencia` int(1) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`reais` int(11) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`avisos` int(1) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`estrelas` int(11) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`dinheiro` int(20) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`saldobancario` int(20) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`matou` int(10) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`morreu` int(10) NOT NULL,", strlen(db_identidade));
    strins(db_identidade, "`sexo` varchar(10) NOT NULL, ", strlen(db_identidade));
    strins(db_identidade, "`skin` int(3) NOT NULL, ", strlen(db_identidade));
    strins(db_identidade, "`disease` int(1) NOT NULL, ", strlen(db_identidade));
    strins(db_identidade, "`health` float NOT NULL DEFAULT 100, ", strlen(db_identidade));
    strins(db_identidade, "`lastlogin` int NOT NULL, ", strlen(db_identidade));
    strins(db_identidade, "`id_contas` int NOT NULL, ", strlen(db_identidade));
    strins(db_identidade, "PRIMARY KEY (`id`), ", strlen(db_identidade));
    strins(db_identidade, "FOREIGN KEY (`id_contas`) REFERENCES `Contas`(`id`) ON DELETE CASCADE )", strlen(db_identidade));
    mysql_query(IDConexao, db_identidade, false);
    return 1;
}

forward DB_LoadIdentidade(playerid);
public DB_LoadIdentidade(playerid)
{
    if(cache_num_rows() == 0)
    {
        new query[150];
        mysql_format(IDConexao, query, sizeof(query), "INSERT INTO `Identidade` (`sexo`, `skin`, `id_contas`) VALUES ('%s', '%d', '%d')", PlayerInfo[playerid][sexo], PlayerInfo[playerid][skin], PlayerInfo[playerid][ID]);
        mysql_query(IDConexao, query);
    }
    else
    {
        new tmp[25];
        cache_get_value_int(0, "profissao", PlayerInfo[playerid][Profissao]);
        cache_get_value_int(0, "minup", PlayerInfo[playerid][minUP]);
        cache_get_value_int(0, "segup", PlayerInfo[playerid][segUP]);
        cache_get_value_int(0, "level", PlayerInfo[playerid][Level]);
        cache_get_value_int(0, "experiencia", PlayerInfo[playerid][Exp]);
        cache_get_value_int(0, "reais", PlayerInfo[playerid][Reais]);
        cache_get_value_int(0, "avisos", PlayerInfo[playerid][Avisos]);
        cache_get_value_int(0, "estrelas", PlayerInfo[playerid][Estrelas]);
        cache_get_value_int(0, "dinheiro", PlayerInfo[playerid][Dinheiro]);
        cache_get_value_int(0, "saldobancario", PlayerInfo[playerid][SaldoBancario]);
        cache_get_value_int(0, "matou", PlayerInfo[playerid][Matou]);
        cache_get_value_int(0, "morreu", PlayerInfo[playerid][Morreu]);
        cache_get_value_name(0, "sexo", tmp); format(PlayerInfo[playerid][sexo], 10, tmp);
        cache_get_value_int(0, "skin", PlayerInfo[playerid][skin]);
        cache_get_value_float(0, "health", PlayerInfo[playerid][Health]);
        cache_get_value_int(0, "disease", PlayerInfo[playerid][disease]);
        cache_get_value_int(0, "lastlogin", PlayerInfo[playerid][lastlogin]);

        SendClientMessage(playerid, Green, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
        format(String, sizeof(String), "� Seja bem-vindo(a) mais uma vez {008040}%s{FFFFFF}!", PlayerInfo[playerid][Nome]);
        SendClientMessage(playerid, White, String);
        format(String, sizeof(String), "� Sua �ltima entrada foi {FFFF00}%s {FFFFFF}atr�s", OnPlayerLastLogin( ( gettime() - PlayerInfo[playerid][lastlogin] )) );
        SendClientMessage(playerid, White, String);
        SendClientMessage(playerid, Green, "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

        TogglePlayerSpectating(playerid, false);
        PlayerInfo[playerid][Logado] = true;
        SetColorProfession(playerid);

        SetPlayerName(playerid, PlayerInfo[playerid][Nome]);
        SetPlayerScore(playerid, PlayerInfo[playerid][Level]);
        GivePlayerMoney(playerid, PlayerInfo[playerid][Dinheiro]);
        SetPlayerHealth(playerid, PlayerInfo[playerid][Health]);

        HideTextDrawLogin(playerid);
        CancelSelectTextDraw(playerid);
        StopAudioStreamForPlayer(playerid);
        ApplyAnimation(playerid, "BIKES", "BIKEs_Back", 0, 0, 0, 0, 0, 0);
    }

    mysql_format(IDConexao, String, sizeof(String), "SELECT `Tutorial` FROM `Contas` WHERE `Tutorial`='1' AND `id`='%d'", PlayerInfo[playerid][ID]);
    mysql_tquery(IDConexao, String, "LoadTutorial", "d", playerid);

    UPRelogio[playerid] = SetTimerEx("ClockUP", 1000, true, "d", playerid);
    return 1;
}

stock SaveIdentidade(playerid)
{
    new query[500];

    PlayerInfo[playerid][lastlogin] = gettime();

    GetPlayerHealth(playerid, PlayerInfo[playerid][Health]);

    mysql_format(IDConexao, query, sizeof(query), "UPDATE `Identidade` SET `profissao`='%d', `minup`='%d', `segup`='%d', `level`='%d', `experiencia`='%d', `reais`='%d', `avisos`='%d', `estrelas`='%d', `dinheiro`='%d', `health`='%f', `saldobancario`='%d', `matou`='%d', `morreu`='%d', `sexo`='%e', `skin`='%d', `lastlogin`='%d' WHERE `id_contas`='%d'",
    PlayerInfo[playerid][Profissao],
    PlayerInfo[playerid][minUP],
    PlayerInfo[playerid][segUP],
    PlayerInfo[playerid][Level],
    PlayerInfo[playerid][Exp],
    PlayerInfo[playerid][Reais],
    PlayerInfo[playerid][Avisos],
    PlayerInfo[playerid][Estrelas],
    PlayerInfo[playerid][Dinheiro],
    PlayerInfo[playerid][Health],
    PlayerInfo[playerid][SaldoBancario],
    PlayerInfo[playerid][Matou],
    PlayerInfo[playerid][Morreu],
    PlayerInfo[playerid][sexo],
    PlayerInfo[playerid][skin],
    PlayerInfo[playerid][lastlogin],
    PlayerInfo[playerid][ID]);
    mysql_query(IDConexao, query);
    return 1;
}

stock OnPlayerLastLogin(value)
{
    new str[30], days, hours, minutes, seconds;

    TimeConvertEx(value, days, hours, minutes, seconds);

    if(days >= 1)
    {
        format(str, 30, "%d dia%s", days, (days > 1 ? ("s"):(#)));
    }
    else if(hours >= 1)
    {
        format(str, 30, "%d hora%s", hours, (hours > 1 ? ("s"):(#)));
    }
    else if(minutes >= 1)
    {
        format(str, 30, "%d minuto%s", minutes, (minutes > 1 ? ("s"):(#)));
    }
    else
    {
        format(str, 30, "%d segundos", seconds);
    }
    return str;
}