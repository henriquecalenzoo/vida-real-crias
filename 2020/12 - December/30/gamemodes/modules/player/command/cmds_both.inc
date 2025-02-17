CMD:cp(playerid, params[])
{
    if(PlayerInfo[playerid][Profissao] == unemployed)
        return PC_EmulateCommand(playerid, "/profissao");

    new tmp[128];

    if(sscanf(params, "s[128]", tmp))
        return SendClientMessage(playerid, Erro, "Digite: /Cp [mensagem]");

    for(new i; i < MAX_PLAYERS; i++)
    {
        if(PlayerInfo[i][Profissao] == PlayerInfo[playerid][Profissao])
        {
            format(String, MAX_STRING, "Chat-Profiss�o ~ %s [%d] diz: %s", PlayerInfo[playerid][Nome], playerid, tmp);
            SendClientMessage(i, GetPlayerColor(playerid), String);
        }
    }
    return 1;
}
CMD:lt(playerid)
{
    new profession = PlayerInfo[playerid][Profissao];

    if(profession == unemployed)
        return PC_EmulateCommand(playerid, "/profissao");

    if(profession == motoboy)
        return SendClientMessage(playerid, Erro, "Essa profiss�o n�o tem um LT");

    CreateCPGPS(playerid, Profission[profession][pfs_x], Profission[profession][pfs_y], Profission[profession][pfs_z]);
    return 1;
}

CMD:cancelar(playerid)
{
    switch(PlayerInfo[playerid][Profissao])
    {
        case newspaperdelivery:
        {
            if(!Newspaper[playerid])
                return SendClientMessage(playerid, Erro, "Voc� n�o tem nenhuma entrega pendente");

            if(IsValidDynamicRaceCP(CPSEJ[playerid])) DestroyDynamicRaceCP(CPSEJ[playerid]);

            CPSEJ[playerid] = 0;
            Newspaper[playerid] = 0;
            BlockNewspaper[playerid] = false;
            return 1;
        }
        case pizzaboy:
        {
            if(!pb_pizzas[playerid])
                return SendClientMessage(playerid, Erro, "Voc� n�o tem nenhuma entrega pendente");

            pb_pizzas[playerid] = 0;
            DestroyDynamicPickup(pb_pickup[playerid]);
            DestroyDynamicMapIcon(pb_mapicon[playerid]);
            DestroyDynamic3DTextLabel(pb_label[playerid]);
        }
        case tanker:
        {
            if(!Petroleum[playerid][ptl_value])
                return SendClientMessage(playerid, Erro, "Voc� n�o tem nenhuma entrega pendente");

            if(_gpson[playerid]){
                DestroyDynamicMapIcon(_gpsmap[playerid]);
                _gpson[playerid] = false;
            }
            Petroleum[playerid][ptl_value] = 0;
        }
        case strongcardriver:
        {
            new vehicleid = getPlayerVehicleID(playerid);

            if(GetVehicleModel(PublicVehicle[vehicleid][pv_vehicle]) != 428)
                return SendClientMessage(playerid, Erro, "Seu �ltimo ve�culo n�o � um Carro Forte");

            PublicVehicle[vehicleid][pv_loaded] = false;
        }
        case light:
        {
            if(light_route[playerid] == -1)
                return SendClientMessage(playerid, Erro, "Voc� n�o tem consertos pendente");

            light_route[playerid] = -1;
            DestroyDynamicRaceCP(light_cp[playerid]);
            Light_Place_Repair[playerid][lpr_x] = 0;
            Light_Place_Repair[playerid][lpr_y] = 0;
            Light_Place_Repair[playerid][lpr_z] = 0;
        }
        case loader:
        {
            if(!IsPlayerInAnyVehicle(playerid))
                return SendClientMessage(playerid, Erro, "Voc� n�o est� em um ve�culo");

            new vehicleid = getPlayerVehicleID(playerid);

            if(!PublicVehicle[vehicleid][pv_loaded])
                return SendClientMessage(playerid, Erro, "Seu ve�culo n�o est� carregado");

            loader_count[playerid] = 0;
            DestroyDynamicRaceCP(loader_cp[playerid]);
            PublicVehicle[vehicleid][pv_loaded] = false;
        }
        case minerals:
        {
            if(!IsPlayerInAnyVehicle(playerid))
                return SendClientMessage(playerid, Erro, "Voc� n�o est� em um Cement Truck");

            if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 524)
                return SendClientMessage(playerid, Erro, "Voc� n�o est� em um Cement Truck");

            new vehicleid = getPlayerVehicleID(playerid);

            if(vehicleid == INVALID_VEHICLE_ID)
                return 0;

            if(!PublicVehicle[vehicleid][pv_loaded])
                return SendClientMessage(playerid, Erro, "Seu ve�culo n�o est� carregado");

            LoadOrDownload(playerid, vehicleid, false);
            LeftPfsMinerals(playerid);
        }
        case motoboy:
        {
            if(!MotoBoy[playerid][mb_accept])
                return SendClientMessage(playerid, Erro, "Voc� n�o tem pedido pendente");

            MotoBoy[playerid][mb_accept] = false;
            MotoBoy[playerid][mb_business] = false;
            DestroyDynamicRaceCP(MotoBoy[playerid][mb_cp]);
        }
        case woods:
        {
            if(!IsPlayerInAnyVehicle(playerid))
                return SendClientMessage(playerid, Erro, "Voc� n�o est� em um DFT-30");

            if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 578)
                return SendClientMessage(playerid, Erro, "Voc� n�o est� em um DFT-30");

            new vehicleid = getPlayerVehicleID(playerid);

            if(vehicleid == INVALID_VEHICLE_ID)
                return 0;

            if(!PublicVehicle[vehicleid][pv_loaded])
                return SendClientMessage(playerid, Erro, "Seu ve�culo n�o est� carregado");

            LoadOrDownload(playerid, vehicleid, false);
            LeftPfsWoods(playerid);
        }
        case pilot:
        {
            if(!IsPlayerInAnyVehicle(playerid))
                return SendClientMessage(playerid, Erro, "Voc� n�o est� em um Dodo");

            if(GetVehicleModel(GetPlayerVehicleID(playerid)) != 593)
                return SendClientMessage(playerid, Erro, "Voc� n�o est� em um Dodo");

            new vehicleid = getPlayerVehicleID(playerid);

            if(vehicleid == INVALID_VEHICLE_ID)
                return 0;

            if(!PublicVehicle[vehicleid][pv_loaded])
                return SendClientMessage(playerid, Erro, "Seu ve�culo n�o est� carregado");

            LoadOrDownload(playerid, vehicleid, false);
            LeftPfsPilot(playerid);
        }
        default:
            return SendClientMessage(playerid, Erro, "Voc� n�o tem permiss�o");
    }

    PlayerInfo[playerid][Dinheiro] -= 1000;
    UpdatePlayerMoney(playerid);

    SendClientMessage(playerid, Yellow, "Voc� cancelou sua(as) entrega(as) e perdeu $1.000");
    return 1;
}
CMD:localizar(playerid, params[])
{
    if(!IsPlayerPolice(playerid) && !IsPlayerIntern(playerid) && PlayerInfo[playerid][Profissao] != taxi && PlayerInfo[playerid][Profissao] != taxiair && PlayerInfo[playerid][Profissao] != paramedic)
        return SendClientMessage(playerid, Erro, "Voc� n�o tem permiss�o");

    new id;

    if((IsPlayerPolice(playerid) && !IsPlayerUniformPM(playerid)) || (PlayerInfo[playerid][Profissao] == paramedic && !IsPlayerUniformParamedic(playerid)))
        return SendClientMessage(playerid, Erro, "Voc� n�o est� com o uniforme");

    if(PlayerInfo[playerid][Profissao] == taxi && !IsPlayerInAnyVehicle(playerid))
        return SendClientMessage(playerid, Erro, "Seu �ltimo ve�culo n�o � um t�xi");

    if((PlayerInfo[playerid][Profissao] == taxi && GetVehicleModel(LastVehicle[playerid]) != 420) && (PlayerInfo[playerid][Profissao] == taxi && GetVehicleModel(LastVehicle[playerid]) != 487))
        return SendClientMessage(playerid, Erro, "Seu �ltimo ve�culo n�o � um t�xi");

    if(sscanf(params, "d", id))
        return SendClientMessage(playerid, Erro, "Digite: /Localizar [id]");

    if(!PlayerInfo[id][Logado])
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a) n�o conectado(a)");

    if(playerid == id)
        return SendClientMessage(playerid, Erro, "Voc� n�o pode efetuar comando em s� mesmo");

    if(IsPlayerPolice(playerid) && !PlayerInfo[id][Estrelas])
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a) n�o est� procurado(a)");

    if(PlayerInfo[playerid][Profissao] == taxi && !RequestTaxi[id])
        return SendClientMessage(playerid, Erro, "O(A) Jogador(a) n�o est� precisando, indique ~~> /taxi");

    if(locate[playerid]){
        KillTimer(TimerProcurando[playerid]);
    }

    locate[playerid] = true;
    TimerProcurando[playerid] = SetTimerEx("OnPlayerLocate", 2000, true, "dd", playerid, id);
    SendClientMessage(playerid, Green, "Jogador(a) localizado(a)");
    return 1;
}
CMD:deslocalizar(playerid)
{
    if(!IsPlayerPolice(playerid) && !IsPlayerIntern(playerid) && PlayerInfo[playerid][Profissao] != taxi && PlayerInfo[playerid][Profissao] != taxiair && PlayerInfo[playerid][Profissao] != paramedic)
        return SendClientMessage(playerid, Erro, "Voc� n�o tem permiss�o");

    if(!locate[playerid])
        return SendClientMessage(playerid, Erro, "Voc� n�o localizou algum jogador(a)");

    locate[playerid] = false;
    KillTimer(TimerProcurando[playerid]);
    if(IsValidDynamicMapIcon(maplocate[playerid])) DestroyDynamicMapIcon(maplocate[playerid]);

    SendClientMessage(playerid, Green, "Jogador(a) deslocalizado(a)");
    return 1;
}
CMD:profissao(playerid)
{
    new txt[1500];

    strcat(txt, (!IsPlayerMobile(playerid) ? ("{FF0000}Comandos \t\t {FFFFFF}Informa��es \n") : (#)));

    switch(PlayerInfo[playerid][Profissao])
    {
        case unemployed:
        {
            new string[1000];
            strcat(string, "{FFFFFF}Voc� est� desempregado, para conseguir um v� at� a Agencia de Empregos em uma das 3 cidades de san andreas \n\n");
            strcat(string, "{FFFFFF}Los Santos - Est� localizado perto da praia de Santa Maria \n\n");
            strcat(string, "{FFFFFF}Las Venturas - Est� localizado perto do Aero Porto \n\n");
            strcat(string, "{FFFFFF}San Fierro - Est� localizado perto da Esta��o Ferrovi�ria \n\n");
            strcat(string, "{FFFFFF}Todas as Ag�ncias de Empregos tem um simbolo de uma {1e90ff}Caveira Azul {FFFFFF}no Radar \n\n");
            ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "{FF0000}Desempregado", string, "Fechar", #);
            return 1;
        }
        case newspaperdelivery:
        {
            strcat(txt, "{80FF80}/Pegarjornais {FFFFFF}\t\t Para pegar 20 jornais \n");
            strcat(txt, "{80FF80}/Cancelar {FFFFFF}\t\t Para cancelar as entregas \n\n");
        }
        case pizzaboy:
        {
            strcat(txt, "{FFFF80}Precione \"Y\"{FFFFFF}\t\t Para criar ve�culo profiss�o \n");
            strcat(txt, "{FFFF80}Precione \"N\" {FFFFFF}\t\t Para pegar/entregar pizza \n");
            strcat(txt, "{FFFF80}/Cancelar {FFFFFF}\t\t Para cancelar as entregas \n\n");
        }
        case motoboy:
        {
            strcat(txt, "{FF00FF}Pedidos {FFFFFF}\t\t Os pedidos s�o gerados � cada 1 minuto \n\n");
            strcat(txt, "{FF00FF}/Radar {FFFFFF}\t\t Para ativar/desativar os pedidos \n");
            strcat(txt, "{FF00FF}/AceitarPedido {FFFFFF}\t\t Para aceitar um servi�o \n");
            strcat(txt, "{FF00FF}/Cancelar {FFFFFF}\t\t Para cancelar o servi�o \n\n");
        }
        case gari:
        {
            strcat(txt, "{D56A00}Precione \"Y\"{FFFFFF}\t\t Para criar ve�culo profiss�o \n");
            strcat(txt, "{D56A00}Precione \"N\" {FFFFFF}\t\t Para pegar/remover um lixo \n");
        }
        case mechanical:
        {
            strcat(txt, "{004000}/OfertarReparo {FFFFFF}\t\t Para oferecer reparo � um determinado jogador(a) \n");
            strcat(txt, "{004000}/Reparar{FFFFFF}\t\t Para reparar um ve�culo \n");
            strcat(txt, "{004000}/Tunar {FFFFFF}\t\t Tune um ve�culo \n");
        }
        case paramedic:
        {
            strcat(txt, "{00FF80}/VenderCura {FFFFFF}\t\t Para oferecer cura � um determinado jogador(a) \n");
            strcat(txt, "{00FF80}/VenderVacina {FFFFFF}\t\t Para oferecer vacina � um determinado jogador(a) \n");
            strcat(txt, "{00FF80}/Reanimar {FFFFFF}\t\t Para reanimar um(a) jogador(a) \n");
            strcat(txt, "{00FF80}Precione \"N\" {FFFFFF}\t\t Para uniformizar-se (Dentro do HOSPITAL no uniforme girando)\n");
        }
        case light:
        {
            strcat(txt, "{008040}/Iniciar {FFFFFF}\t\t Para in�ciar as rotas de consertos \n");
            strcat(txt, "{008040}/Cancelar {FFFFFF}\t\t Para cancelar as entregas \n\n");
            strcat(txt, "{008040}Precione \"N\" {FFFFFF}\t\t Para uniformizar-se \n");
        }
        case lawyer:
        {
            strcat(txt, "{8000FF}/Presos {FFFFFF}\t\t Para ver s jogador(a) que est� preso(a) \n");
            strcat(txt, "{8000FF}/Soltar {FFFFFF}\t\t Para soltar um determinado jogador(a) \n\n");
        }
        case taxi, taxiair:
        {
            strcat(txt, "{FFFF00}/Localizar {FFFFFF}\t\t Para localizar o cliente \n");
            strcat(txt, "{FFFF00}/Deslocalizar {FFFFFF}\t\t Para deslocalizar o cliente \n");
            strcat(txt, "{FFFF00}/Taximetro {FFFFFF}\t\t Para iniciar seus servi�os a um cliente \n\n");
        }
        case tanker:
        {
            strcat(txt, "{808080}/Carregar {FFFFFF}\t\t Inicie o carregamento \n");
            strcat(txt, "{808080}/Descarregar {FFFFFF}\t\t Inicie o descarregamento \n");
            strcat(txt, "{808080}/Cancelar {FFFFFF}\t\t Para cancelar as entregas \n\n");
        }
        case loader:
        {
            strcat(txt, "{408080}/Carregar {FFFFFF}\t\t Inicie o carregamento \n");
            strcat(txt, "{408080}/Cancelar {FFFFFF}\t\t Para cancelar as entregas \n\n");
        }
        case minerals:
        {
            strcat(txt, "{808040}/Carregar {FFFFFF}\t\t Inicie o carregamento \n");
            strcat(txt, "{808040}/Cancelar {FFFFFF}\t\t Para cancelar as entregas \n\n");
        }
        case woods:
        {
            strcat(txt, "{804000}Carregamento {FFFFFF}\t\t Para iniciar v� na marca��o vermelha no LT\n");
            strcat(txt, "{804000}Observa��o: {FFFFFF}\t\t Quantia recebida � por efici�ncia no servi�o \n");
            strcat(txt, "{804000}/Cancelar {FFFFFF}\t\t Para cancelar as entregas \n\n");
        }
        case strongcardriver:
        {
            strcat(txt, "{8080FF}Precione \"N\" {FFFFFF}\t\t Para carregar/descarregar o Carro Forte \n");
            strcat(txt, "{8080FF}/Cancelar {FFFFFF}\t\t Para cancelar as entregas \n\n");
        }
        case strongcarsecurity:
        {
            strcat(txt, "{B7B7FF}Entre no Carro Forte{FFFFFF}\t\t Para realizar seguran�a \n");
            strcat(txt, "{B7B7FF}Saia do Carro Forte{FFFFFF}\t\t Para cancelar seguran�a \n\n");
        }
        case pilot:
        {
            strcat(txt, "{808040}/Carregar {FFFFFF}\t\t Inicie o carregamento \n");
            strcat(txt, "{808040}/Cancelar {FFFFFF}\t\t Para cancelar as entregas \n\n");
        }
        case municipalguard:
        {
            strcat(txt, "{4AA5FF}/Procurados {FFFFFF}\t\t Ver todos procurados \n");
            strcat(txt, "{4AA5FF}/Localizar  {FFFFFF}\t\t Para localizar o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Abordar {FFFFFF}\t\t Para abordar o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Perseguicao {FFFFFF}\t\t Para iniciar uma persegui��o o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Algemar {FFFFFF}\t\t Para algemar o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Prender {FFFFFF}\t\t Para prender o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Equipar {FFFFFF}\t\t Para equipar armas e colete \n");
            strcat(txt, "{4AA5FF}/ArrombarCasa {FFFFFF}\t\t Para arrombar uma casa \n");
            strcat(txt, "{4AA5FF}/RemoverUniforme {FFFFFF}\t\t Para remover o uniforme \n\n");
            strcat(txt, "{4AA5FF}Precione \"N\" {FFFFFF}\t\t Para uniformizar-se \n");
        }
        case military..interpol:
        {
            strcat(txt, "{4AA5FF}/Procurados {FFFFFF}\t\t Ver todos procurados \n");
            strcat(txt, "{4AA5FF}/Prenderarmas {FFFFFF}\t\t Para apreender as armas de um(a) jogador(a) \n");
            strcat(txt, "{4AA5FF}/Localizar  {FFFFFF}\t\t Para localizar o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Abordar {FFFFFF}\t\t Para abordar o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Perseguicao {FFFFFF}\t\t Para iniciar uma persegui��o o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Algemar {FFFFFF}\t\t Para algemar o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Prender {FFFFFF}\t\t Para prender o(a) procurado(a) \n");
            strcat(txt, "{4AA5FF}/Tapete {FFFFFF}\t\t Para criar/remover um tapete de pregos \n");
            strcat(txt, "{4AA5FF}/Barreira {FFFFFF}\t\t Para criar/remover uma barreira \n");
            strcat(txt, "{4AA5FF}/Procurar {FFFFFF}\t\t Para colocar como procurado(a) um determinado jogador(a)\n");
            strcat(txt, "{4AA5FF}/Equipar {FFFFFF}\t\t Para equipar armas e colete \n");
            strcat(txt, "{4AA5FF}/ArrombarCasa {FFFFFF}\t\t Para arrombar uma casa \n");
            strcat(txt, "{4AA5FF}/RemoverUniforme {FFFFFF}\t\t Para remover o uniforme \n\n");
            strcat(txt, "{4AA5FF}Precione \"N\" {FFFFFF}\t\t Para uniformizar-se \n");
        }
        case internalaffairs:
        {
            strcat(txt, "{8080C0}/PrenderPolicial [id] [motivo] {FFFFFF}\t\t Para prender o(a) policial \n\n");
        }
        case potplanter:
        {
            strcat(txt, "{550000}/Plantar {FFFFFF}\t\t Para plantar Cannabis\n");
            strcat(txt, "{550000}/Colher {FFFFFF}\t\t Para colher Cannabis\n");
            strcat(txt, "{550000}/Fornecedor {FFFFFF}\t\t Para localizar o fornecedor de Cannabis \n\n");
        }
        case weaponproducer:
        {
            strcat(txt, "{800000}Precione \"N\" {FFFFFF}\t\t Para montar uma arma\n");
            strcat(txt, "{800000}/Armas {FFFFFF}\t\t Para ver/pegar para s�\n");
            strcat(txt, "{800000}/VenderArma {FFFFFF}\t\t Para vender � algum jogador(a)\n");
            strcat(txt, "{800000}/Fornecedor {FFFFFF}\t\t Para localizar o fornecedor de pe�as de armas\n\n");
        }
        case thief:
        {
            strcat(txt, "{D50000}/Assaltar {FFFFFF}\t\t Para assaltar um determinado(a) jogador(a)\n");
            strcat(txt, "{D50000}/AssaltarCaixa {FFFFFF}\t\t Para assaltar um caixa eletr�nico\n");
            strcat(txt, "{D50000}/AssaltarCarroForte {FFFFFF}\t\t Para assaltar um Carro Forte\n");
            strcat(txt, "{D50000}/Hackear {FFFFFF}\t\t Para hackear um banco\n");
            strcat(txt, "{D50000}/AssaltarCofre {FFFFFF}\t\t Para assaltar um banco\n\n");
            strcat(txt, "{D50000}Precione \"N\" {FFFFFF}\t\t Para pegar/remover g�s \n");
            strcat(txt, "{D50000}Precione \"H\" {FFFFFF}\t\t Para colorcar g�s no ve�culo \n\n");
            strcat(txt, "{D50000}Obs: Os g�s est�o localizados pertos de trailers \n\n");
        }
    }

    strcat(txt, "{0080FF}/Cp [mensagem] {FFFFFF}\t\t Para usar o chat profiss�o \n");
    strcat(txt, "{0080FF}/Lt {FFFFFF}\t\t Para localizar o local de trabalho \n\n");

    ShowPlayerDialog(playerid, 0, (IsPlayerMobile(playerid) ? (DIALOG_STYLE_LIST) : (DIALOG_STYLE_TABLIST_HEADERS)), "{FF0000}Comandos Profiss�o", txt, "Fechar", #);
    return 1;
}
CMD:trabalhar(playerid)
{
    if(!AgenciaEncaminhado[playerid])
        return SendClientMessage(playerid, Erro, "Voc� n�o foi encaminhado por nenhuma Agencia de Empregos");

    new profession = PlayerInfo[playerid][Semprofissao];

    if(!IsPlayerInRangeOfPoint(playerid, 2.0, Profission[profession][pfs_x], Profission[profession][pfs_y], Profission[profession][pfs_z]))
        return SendClientMessage(playerid, Erro, "Voc� n�o est� no local de trabalho");

    GetForwardedAgency(playerid, PlayerInfo[playerid][Semprofissao]);
    return 1;
}
CMD:carregar(playerid)
{
    switch(PlayerInfo[playerid][Profissao])
    {
        case loader: CMD_LoaderCarregar(playerid);
        case tanker: CMD_TankerCarregar(playerid);
        case minerals: CMD_MineralsCarregar(playerid);
        case pilot: CMD_PilotCarregar(playerid);
    }
    return 1;
}

CMD:descarregar(playerid)
{
    switch(PlayerInfo[playerid][Profissao])
    {
        case tanker: CMD_TankerDescarregar(playerid);
    }
    return 1;
}

