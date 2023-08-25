/* Generated by Together */

#include <iostream>
#include "IniFile.h"
#include "GroupServerApp.h"
#include "GameCommon.h"
#include "Team.h"
#include "Script.h"
#include "Parser.h"

_DBC_USING

void InitDBSvrConnect(GroupServerApp &gpapp);
void InitACTSvrConnect(GroupServerApp &gpapp);	//AccountServer连接

void GroupServerApp::Initialize()
{

	//Sleep(20000);

	m_dwCheatCount = 0;
	LogLine l_line(g_LogConnect);
	//l_line<<newln<<"开始数据库连接"<<endln;
	l_line<<newln<<"begin connect database"<<endln;
	InitDBSvrConnect(*this);
	m_tblguilds->InitAllGuilds(7);
	dstring		l_acct	=m_cfg["AccountServer"]["AcctEnable"];
	if(l_acct	!="0")
	{
		//l_line<<newln<<"开始初始化AccountServer连接"<<endln;
		l_line<<newln<<"begin init AccountServer connect"<<endln;
		InitACTSvrConnect(*this);
	}

	//LG("init", "初始化Lua Script...\n");
	LG("init", "init Lua Script...\n");
	if( !InitLuaScript() )
	{
		//THROW_EXCP(excp, "初始化LUA脚本失败！");
		THROW_EXCP(excp, "init LUA script failed!");
	}

	//最后打开自己的端口侦听来自GateServer/GameServer的连接：
	//l_line<<newln<<"开始开始读取GroupServer.cfg配置文件"<<endln;
	l_line<<newln<<"begin read GroupServer.cfg"<<endln;
	IniSection	&l_is	=m_cfg["Main"];
	cChar		*l_ip	=l_is["Listen_IP"];
	uShort		l_port	=atoi(l_is["Listen_Port"]);
/*
	const_cha.MaxChaNum			=atoi(m_cfg["角色"]["每帐号最大角色数"]);
	const_cha.MaxChaNum			=min(const_cha.MaxChaNum,Player::emMaxCharacters);
	const_cha.MaxIconVal		=atoi(m_cfg["角色"]["个性化图标的最大值"]);
	const_cha.MaxLoginUsr		=atoi(m_cfg["角色"]["最大登录人数"]);
*/
	const_cha.MaxChaNum			=atoi(m_cfg["character"]["MaxCharacterNum"]);
	const_cha.MaxChaNum			=min(const_cha.MaxChaNum,Player::emMaxCharacters);
	const_cha.MaxIconVal		=atoi(m_cfg["character"]["MaxValue"]);
	const_cha.MaxLoginUsr		=atoi(m_cfg["character"]["MaxPerson"]);


	/*
	const_frnd.InvitedMax		=atoi(m_cfg["好友"]["最多被邀请数"]);
	const_frnd.PendTimeOut		=atoi(m_cfg["好友"]["未决邀请超时"])*1000;
	const_frnd.FriendMax		=atoi(m_cfg["好友"]["每角色最多好友数"]);
	const_frnd.FriendGroupMax	=atoi(m_cfg["好友"]["每角色的自制好友分组数"]);
	*/
	const_frnd.InvitedMax		=atoi(m_cfg["friend"]["MaxInvitedNum"]);
	const_frnd.PendTimeOut		=atoi(m_cfg["friend"]["InvitedTime"])*1000;
	const_frnd.FriendMax		=atoi(m_cfg["friend"]["MaxFriendNum"]);
	const_frnd.FriendGroupMax	=atoi(m_cfg["friend"]["FriendGroupNum"]);


	/*
	const_team.InvitedMax		=atoi(m_cfg["组队"]["最多被邀请数"]);
	const_team.PendTimeOut		=atoi(m_cfg["组队"]["未决邀请超时"])*1000;
	const_team.MemberMax		=atoi(m_cfg["组队"]["每组队最多成员数"]);
	*/
	const_team.InvitedMax		=atoi(m_cfg["team"]["MaxInvitedNum"]);
	const_team.PendTimeOut		=atoi(m_cfg["team"]["InvitedTime"])*1000;
	const_team.MemberMax		=atoi(m_cfg["team"]["MaxPersonNum"]);


	const_master.InvitedMax		= 5;
	const_master.PendTimeOut	= 30000;
	const_master.MasterMax		= 1;
	const_master.PrenticeMax	= 4;

	/*
	const_chat.MaxSession		=atoi(m_cfg["聊天"]["每玩家最多会话数"]);
	const_chat.MaxSession		=min(const_chat.MaxSession,Player::emMaxSessChat);
	const_chat.MaxPlayer		=atoi(m_cfg["聊天"]["每会话最多玩家数"]);
	const_chat.MaxPlayer		=min(const_chat.MaxPlayer,Player::emMaxSessPlayer);
	*/
	const_chat.MaxSession		=atoi(m_cfg["chat"]["MaxChatNumPerPlayer"]);
	const_chat.MaxSession		=min(const_chat.MaxSession,Player::emMaxSessChat);
	const_chat.MaxPlayer		=atoi(m_cfg["chat"]["maxPlayerPerChat"]);
	const_chat.MaxPlayer		=min(const_chat.MaxPlayer,Player::emMaxSessPlayer);


	/*
	const_interval.World		=atoi(m_cfg["聊天"]["世界频道说话间隔"])*1000;
	const_interval.Trade		=atoi(m_cfg["聊天"]["交易频道说话间隔"])*1000;
	const_interval.ToYou		=atoi(m_cfg["聊天"]["私聊频道说话间隔"])*1000;
	*/
	const_interval.World		=atoi(m_cfg["chat"]["WorldInterval"])*1000;
	const_interval.Trade		=atoi(m_cfg["chat"]["TradeInterval"])*1000;
	const_interval.ToYou		=atoi(m_cfg["chat"]["ToYouInterval"])*1000;


	if(!InitMasterRelation())
	{
		//THROW_EXCP(excp, "初始化师徒关系表失败！");
		THROW_EXCP(excp, RES_STRING(GP_GROUPSERVERAPPINIT_CPP_00001));
	}
	
	//l_line<<newln<<"开始装载ChaNameFilter.txt过虑文件"<<endln;
	l_line<<newln<<"begin load ChaNameFilter.txt"<<endln;
	CTextFilter::LoadFile("ChaNameFilter.txt");
	//l_line<<newln<<"开始打开侦听端口:"<<l_port<<endln;
	l_line<<newln<<"begin listen port:"<<l_port<<endln;
	if(OpenListenSocket(l_port,l_ip))
	{
		//THROW_EXCP(excpSock,l_ip<<","<<l_port<<" 打开失败！请检查端口"<<l_port<<"是否被占用或者GroupServer.cfg的Listen_IP参数配置是否正确。");
		char l_content[500];
		sprintf(l_content,RES_STRING(GP_GROUPSERVERAPPINIT_CPP_00002),l_ip, l_port, l_port);
		THROW_EXCP(excpSock,l_content);
	}
	//l_line<<newln<<"开始打开侦听端口:"<<l_port<<"成功完成，初始化过程结束"<<endln;
	l_line<<newln<<"open listen port:"<<l_port<<"success, init is ok"<<endln;
}

void InitDBSvrConnect(GroupServerApp &gpapp)
{
	//LG("group_sql", "开始初始化数据库连接\n");
	LG("group_sql", RES_STRING(GP_GROUPSERVERAPPINIT_CPP_00030));
	string	l_errinfo;
	std::string driverVersion = gpapp.m_cfg["Database"]["SQL_driverVersion"];
	cChar	*l_ip		=gpapp.m_cfg["Database"]["IP"];
	cChar	*l_db		=gpapp.m_cfg["Database"]["DB"];
	cChar	*l_login	=gpapp.m_cfg["Database"]["Login"];
	cChar	*l_passwd	=gpapp.m_cfg["Database"]["Password"];
	std::string l_str;
	dbpswd_out(l_passwd,int(strlen(l_passwd)),l_str);
	gpapp.m_cfg_db.enable_errinfo();

	//LG("group_sql", "开始初始化数据库连接, ip = [%s], db = [%s]\n", l_ip, l_db);
	LG("group_sql", "begin connect database, ip = [%s], db = [%s]\n", l_ip, l_db);
	if (!gpapp.m_cfg_db.connect(driverVersion, l_ip, l_db, l_login, l_str.c_str(), l_errinfo))
	{
		//LG("group_sql", "数据库连接失败, 错误原因[%s]\n", l_errinfo.c_str());
		LG("group_sql", "connect database failed, error[%s]\n", l_errinfo.c_str());
		THROW_EXCP(excpDB,l_errinfo.c_str());
	} 
	/*gpapp.m_tblsystem		=new TBLSystem(&(gpapp.m_cfg_db));
	if(gpapp.m_tblsystem->Increment() !=1)
	{
		gpapp.m_tblsystem->Decrement();
		delete gpapp.m_tblsystem;
		gpapp.m_tblsystem	=0;
		THROW_EXCP(excpDB,"GroupServer重复！，程序马上退出...");
	}*/

	//LG("group_sql", "数据库连接成功, 开始初始化数据表\n");
	LG("group_sql", "connect database ok, begin init datatable\n");

	gpapp.m_tblaccounts		=new TBLAccounts(&(gpapp.m_cfg_db));
	gpapp.m_tblcharaters	=new TBLCharacters(&(gpapp.m_cfg_db));

	// Add by lark.li 20080806 begin
	gpapp.m_tblpersoninfo	=new TBLPersonInfo(&(gpapp.m_cfg_db));

	//stQueryPersonInfo query;
	//query.nCurPage = 1;
	//query.nPageItemNum = 10;

	//strncpy(query.sChaName, "名字", sizeof(query.sChaName));

	//stQueryResoultPersonInfo result[10];
	//int num;
	//gpapp.m_tblpersoninfo->Query(&query, result,num);

	gpapp.m_tblpersonavatar	=new TBLPersonAvatar(&(gpapp.m_cfg_db));
	// End

	gpapp.m_tblfriends		=new TBLFriends(&(gpapp.m_cfg_db));
	gpapp.m_tblmaster		=new TBLMaster(&(gpapp.m_cfg_db));
	gpapp.m_tblguilds		=new TBLGuilds(&(gpapp.m_cfg_db));
	gpapp.m_tblX1			=new friend_tbl(&(gpapp.m_cfg_db));
	gpapp.m_tbLparam		=new TBLParam(&(gpapp.m_cfg_db));
	
	//LG("group_sql", "开始检查 account表 完整性\n");
	LG("group_sql", "begin check table [account] \n");
	if(!gpapp.m_tblaccounts->IsReady())
	{
		//LG("group_sql", " account表 完整性检查失败\n");
		LG("group_sql", " check table [account] failed\n");
		//THROW_EXCP(excpDB,"触发器初始化失败");
		THROW_EXCP(excpDB,RES_STRING(GP_GROUPSERVERAPPINIT_CPP_00003));
	}
	
	//LG("group_sql", "开始检查 公会表 完整性\n");
	LG("group_sql", "begin check table [guild]\n");
	if(!gpapp.m_tblguilds->IsReady())
	{
		//LG("group_sql", " 公会表 完整性检查失败\n");
		LG("group_sql", " check table [guild] failed \n");
		//THROW_EXCP(excpDB,"公会表尚未执行初始化SQL语句");
		THROW_EXCP(excpDB,RES_STRING(GP_GROUPSERVERAPPINIT_CPP_00004));
	}
	gpapp.m_tblcharaters->ZeroAddr();

	//LG("group_sql", "开始检查 param表 完整性\n");
	LG("group_sql", "begin check table [param]\n");

	//if(!gpapp.m_tbLparam->IsReady())
	//{
	//	LG("group_sql", " 参数表 完整性检查失败\n");
	//	THROW_EXCP(excpDB,"参数表尚未执行初始化SQL语句");

	//}

	if(gpapp.m_tbLparam->InitParam())
	//LG("group_sql", "数据库初始化成功\n");
	LG("group_sql", "init database success\n");
}

void InitACTSvrConnect(GroupServerApp &gpapp)
{
	gpapp.m_name		=gpapp.m_cfg["Main"]["Name"];
	IniSection	&l_is	=gpapp.m_cfg["AccountServer"];
	dstring	l_passwd	=l_is["Password"];
	cChar	*l_ip		=l_is["IP"];
	uShort	l_port		=atoi(l_is["Port"]);

	char buffer[512];

	while(!g_exit && !g_gpsvr->m_acctsock)
	{
		gpapp.m_acctsock	=gpapp.Connect(l_ip,l_port);
		if(!gpapp.m_acctsock)
		{
			//std::cout<<"连接AccountServer:("<<l_ip<<","<<l_port<<")失败,5秒后再次重连..."<<std::endl;
			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, RES_STRING(GP_GROUPSERVERAPPINIT_CPP_00005), l_ip, l_port);
			std::cout<<buffer<<std::endl;
			Sleep(5000);
			continue;
		}
		WPacket	l_wpk	=gpapp.GetWPacket();
		l_wpk.WriteCmd(CMD_PA_LOGIN);
		l_wpk.WriteString(gpapp.m_name);
		l_wpk.WriteString(l_passwd);
		RPacket l_rpk	=gpapp.SyncCall(gpapp.m_acctsock,l_wpk);
		if(!l_rpk.HasData())
		{
			//std::cout<<"在AccountServer:("<<l_ip<<","<<l_port<<")上登录超时,5秒钟后重新连接和登录..."<<std::endl;
			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, RES_STRING(GP_GROUPSERVERAPPINIT_CPP_00006), l_ip, l_port);
			std::cout<<buffer<<std::endl;
			gpapp.Disconnect(gpapp.m_acctsock,0,100);
			break;
		}
		if(l_rpk.ReadShort())		//返回非0表示失败
		{
			//std::cout<<"在AccountServer:("<<l_ip<<","<<l_port<<")上登录失败,5秒钟后重新连接和登录..."<<std::endl;
			memset(buffer, 0, sizeof(buffer));
			sprintf(buffer, RES_STRING(GP_GROUPSERVERAPPINIT_CPP_00007), l_ip, l_port);
			std::cout<<buffer<<std::endl;
			gpapp.Disconnect(gpapp.m_acctsock,0,200);
			break;
		}
		gpapp.m_acctsock->SetPointer(0);
	}
}
