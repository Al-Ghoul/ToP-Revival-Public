#include "Util.h"
#include "GameAppNet.h"
#include "Player.h"

#define defCHA_TABLE_VER		110
#define defCHA_TABLE_NEW_VER	111

enum ESaveType
{
	enumSAVE_TYPE_OFFLINE,	// 下线
	enumSAVE_TYPE_SWITCH,	// 地图切换
	enumSAVE_TYPE_TIMER,	// 定时保存
	enumSAVE_TYPE_TRADE,	// 交易
};

class CPlayer;
class CTableCha : public cfl_rs
{
public:

    CTableCha(cfl_db *pDB)
        :cfl_rs(pDB, "character", 100)
    {T_B
    
	T_E}

	bool Init(void);
    bool ReadAllData(CPlayer *pPlayer, DWORD cha_id);	// 角色进入游戏读盘
    bool SaveAllData(CPlayer *pPlayer, char chSaveType);// 角色存盘
	bool SavePos(CPlayer *pPlayer);						// 保存角色位置
	bool SaveMoney(CPlayer *pPlayer);
	bool SaveKBagDBID(CPlayer *pPlayer);
    bool SaveKBagTmpDBID(CPlayer *pPlayer);             // 保存临时背包ID
    bool SaveKBState(CPlayer *pPlayer);                 // 保存密码锁定状态
	bool SaveMMaskDBID(CPlayer *pPlayer);
	bool SaveBankDBID(CPlayer *pPlayer);
	bool SaveTableVer(DWORD cha_id);					// 保存表的版本
	BOOL SaveMissionData(CPlayer *pPlayer, DWORD cha_id); // 角色任务信息存盘
    BOOL VerifyName(const char *pszName);               // 角色名是否存在

	BOOL AddCreditByDBID(DWORD cha_id, long lCredit);
	BOOL IsChaOnline(DWORD cha_id, BOOL &bOnline);
	BOOL SaveStoreItemID(DWORD cha_id, long lStoreItemID);
	BOOL AddMoney(DWORD cha_id, long money);
};

class CTableMaster : public cfl_rs
{
public:

	CTableMaster(cfl_db *pDB)
		:cfl_rs(pDB, "master", 6)
	{T_B

	T_E}

	bool Init(void);
	unsigned long GetMasterDBID(CPlayer *pPlayer);
	bool IsMasterRelation(int masterID, int prenticeID);
};

// 此值和数据库对应，不可改动
enum ResDBTypeID
{
	enumRESDB_TYPE_LOOK,	// 外观
	enumRESDB_TYPE_KITBAG,	// 道具栏
	enumRESDB_TYPE_BANK,	// 银行
	enumRESDB_TYPE_KITBAGTMP, //临时背包
};

// Add by lark.li 20080521 begin
enum IssueState
{
	enumCURRENT = 0,	// 当前期
	enumPASTDUE = 1,	// 过期
	enumDISUSE = 2,		// 废弃
};

// 彩票设定
class CTableLotterySetting : public cfl_rs
{
public:
    CTableLotterySetting(cfl_db *pDB)
        :cfl_rs(pDB, "LotterySetting", 10)
    {T_B
    
	T_E}

	bool Init(void);
	bool GetCurrentIssue(int& issue);
	bool AddIssue(int issue);
	bool DisuseIssue(int issue, int state);
	bool SetWinItemNo(int issue, const char* itemno);
	bool GetWinItemNo(int issue, string& itemno);
};

// 彩票保存
class CTableTicket : public cfl_rs
{
public:
    CTableTicket(cfl_db *pDB)
        :cfl_rs(pDB, "Ticket", 10)
    {T_B
    
	T_E}

	bool Init(void);
	bool AddTicket(int cha_id, int issue, char itemno[6][2]);
	bool IsExist(int issue, char* itemno);
	bool CalWinTicket(int issue, int max, string& itemno);
private:
	bool AddTicket(int cha_id, int issue, char itemno1, char itemno2, char itemno3, char itemno4, char itemno5, char itemno6, int real = 1);
};

// 中奖号码保存
class CTableWinTicket : public cfl_rs
{
public:
    CTableWinTicket(cfl_db *pDB)
        :cfl_rs(pDB, "WinTicket", 10)
    {T_B
    
	T_E}

	bool Init(void);
	bool GetTicket(int issue);
	bool AddTicket(int issue, char* itemno, int grade);
	bool Exchange(int issue, char* itemno);
};

struct AmphitheaterSetting
{
	enum AmphitheaterSateSetting
	{
		enumCURRENT = 0,
	};
};
//Add by sunny.sun 20080725
struct AmphitheaterTeam
{
	enum AmphitheaterSateTeam
	{
		enumNotUse = 0,				//没注册
		enumUse = 1,				// 正常
		enumPromotion = 2,			// 晋级
		enumRelive = 3,				// 复活
		enumOut = 4,				// 淘汰
	};
};

// 竞技场设定信息保存
// 保存 当前是第几赛季 第几轮次 等信息
class CTableAmphitheaterSetting : public cfl_rs
{
public:
    CTableAmphitheaterSetting(cfl_db *pDB)
        :cfl_rs(pDB, "AmphitheaterSetting", 10)
    {T_B
    
	T_E}

	bool Init(void);
	bool GetCurrentSeason(int& season, int& round);
	bool AddSeason(int season);
	bool DisuseSeason(int season, int state,const char* winner);
	bool UpdateRound(int season, int round);
};

// 竞技场参赛队伍信息保存
class CTableAmphitheaterTeam : public cfl_rs
{
public:
    CTableAmphitheaterTeam(cfl_db *pDB)
        :cfl_rs(pDB, "AmphitheaterTeam", 10)
    {T_B
    
	T_E}

	bool Init(void);
	bool GetTeamCount(int& count);
	bool GetNoUseTeamID(int &teamID);
	bool TeamSignUP(int &teamID, int captain, int member1, int member2);
	bool TeamCancel(int teamID);
	
	bool TeamUpdate(int teamID, int matchNo, int state, int winnum, int losenum, int relivenum);
	bool IsValidAmphitheaterTeam(int teamID, int captainID, int member1, int member2);
	bool IsLogin(int pActorID);//Add by sunny.sun20080714
	bool IsMapFull(int MapID,int & PActorIDNum);
	bool UpdateMapNum(int Teamid,int Mapid,int MapFlag);
	bool SetMaxBallotTeamRelive(void);
	bool SetMatchResult(int Teamid1,int Teamid2,int Id1state,int Id2state);
	bool GetMapFlag(int Teamid,int & Mapflag);
	bool GetCaptainByMapId(int Mapid,string &Captainid1,string &Captainid2);
	bool UpdateMap(int Mapid);

	bool GetPromotionAndReliveTeam(vector< vector< string > > &dataPromotion, vector< vector< string > > &dataRelive);
	bool UpdatReliveNum(int ReID);
	bool UpdateAbsentTeamRelive(void);
	bool UpdateMapAfterEnter(int CaptainID,int MapID);
	bool UpdateWinnum( int teamid );//Add by sunnysun20080818
	bool GetUniqueMaxWinnum(int &teamid);
	bool SetMatchnoState( int teamid );
	bool UpdateState(void);
	bool CloseReliveByState( int & statenum );
	bool CleanMapFlag(int teamid1,int teamid2);
	bool GetStateByTeamid( int teamid, int & state );
};

// End

//Add by sunny.sun 20080822
//Begin
class CTablePersoninfo : public cfl_rs
{
public:
    CTablePersoninfo(cfl_db *pDB)
        :cfl_rs(pDB, "personinfo", 10)
	{T_B
	
	T_E}
	bool Init(void);
	bool GetPersonBirthday(int chaid , int &birthday);
};

//End

class CTableResource : public cfl_rs
{
public:
    CTableResource(cfl_db *pDB)
        :cfl_rs(pDB, "resource", 10)
    {T_B
    
	T_E}

	bool Init(void);
	bool Create(long &lDBID, long lChaId, long lTypeId);
    bool ReadKitbagData(CCharacter *pCCha);
    bool SaveKitbagData(CCharacter *pCCha);
    bool ReadKitbagTmpData(CCharacter *pCCha);
    bool SaveKitbagTmpData(CCharacter *pCCha);
	bool ReadKitbagTmpData(long lRecDBID, string& strData);
	bool SaveKitbagTmpData(long lRecDBID, const string& strData);
	bool ReadBankData(CPlayer *pCPly, char chBankNO = -1);
	bool SaveBankData(CPlayer *pCPly, char chBankNO = -1);
};

class CTableMapMask : public cfl_rs
{
public:
    CTableMapMask(cfl_db *pDB)
        :cfl_rs(pDB, "map_mask", 10)
    {T_B
    
	T_E}

	bool Init(void);
	bool Create(long &lDBID, long lChaId);
    bool ReadData(CPlayer *pCPly);
    bool SaveData(CPlayer *pCPly, BOOL bDirect = FALSE);
	bool GetColNameByMapName(const char *szMapName, char *szColName, long lColNameLen);

	void HandleSaveList();
	void AddSaveQuest(const char *pszSQL);
	void SaveAll();

protected:

	BOOL			_ExecSQL(const char *pszSQL);
	list<string>	_SaveMapMaskList;  // 保存大地图的队列
};

void inline CTableMapMask::AddSaveQuest(const char *pszSQL)
{
	_SaveMapMaskList.push_back(pszSQL);
}


class CTableAct : public cfl_rs
{
public:

    CTableAct(cfl_db *pDB)
        :cfl_rs(pDB, "account", 10)
    {T_B
    
	T_E}

	bool Init(void);
	bool ReadAllData(CPlayer *pPlayer, DWORD act_id);
};

class CTableBoat : public cfl_rs
{
public:
	CTableBoat( cfl_db* pDB )
		:cfl_rs( pDB, "boat", 100 )
	{T_B

	T_E}

	bool Init(void);
	BOOL Create( DWORD& dwBoatID, const BOAT_DATA& Data );
	BOOL GetBoat( CCharacter& Boat );
	BOOL SaveBoat( CCharacter& Boat, char chSaveType );
	BOOL SaveBoatTempData( CCharacter& Boat, BYTE byIsDeleted = 0 );
	BOOL SaveBoatTempData( DWORD dwBoatID, DWORD dwOwnerID, BYTE byIsDeleted = 0 );
	BOOL SaveBoatDelTag( DWORD dwBoatID, BYTE byIsDeleted = 0 );	

    bool SaveAllData(CPlayer *pPlayer, char chSaveType);
	bool ReadCabin(CCharacter& Boat);	// 读取船舱
	bool SaveCabin(CCharacter& Boat, char chSaveType);	// 保存船舱
	bool SaveAllCabin(CPlayer *pPlayer, char chSaveType);
};

class CTableGuild : public cfl_rs
{
public:
	CTableGuild(cfl_db *pDB)
        :cfl_rs(pDB, "guild", 100)
	{T_B

	T_E}

	bool Init(void);
	long Create(CCharacter* pCha, char guildtype, char *guildname, cChar *passwd);
	bool ListAll(CCharacter* pCha, char guildtype, char disband_days);
	void TryFor(CCharacter* pCha, uLong guildid);
	void TryForConfirm(CCharacter* pCha, uLong guildid);	
	char GetTypeByID(uLong guildid);
	bool GetGuildInfo(CCharacter* pCha, uLong guildid );
	bool ListTryPlayer(CCharacter* pCha, char disband_days);
	bool Approve(CCharacter* pCha, uLong chaid);
	bool Reject(CCharacter* pCha, uLong chaid);
	bool Kick(CCharacter* pCha, uLong chaid);
	bool Leave(CCharacter* pCha);
	bool Disband(CCharacter* pCha,cChar *passwd);
	bool Motto(CCharacter* pCha,cChar *motto);
	bool GetGuildName(long lGuildID, std::string& strGuildName);

	// 公会挑战
	bool Challenge( CCharacter* pCha, BYTE byLevel, DWORD dwMoney );
	bool Leizhu( CCharacter* pCha, BYTE byLevel, DWORD dwMoney );
	void ListChallenge( CCharacter* pCha );
	bool GetChallInfo( BYTE byLevel, DWORD& dwGuildID1, DWORD& dwGuildID2, DWORD& dwMoney );
	bool StartChall( BYTE byLevel );
	bool HasCall( BYTE byLevel );
	void EndChall( DWORD dwGuild1, DWORD dwGuild2, BOOL bChall );
	void ChallMoney( BYTE byLevel, BOOL bChall, DWORD dwGuildID, DWORD dwChallID, DWORD dwMoney );
	bool ChallWin( BOOL bUpdate, BYTE byLevel, DWORD dwWinGuildID, DWORD dwFailerGuildID );
	bool HasGuildLevel( CCharacter* pChar, BYTE byLevel );
};

// Log专用表
class CTableLog : public cfl_rs
{
public:
    CTableLog(cfl_db *pDB)
        :cfl_rs(pDB, "gamelog", 10)
    {T_B
    
	T_E}

};

//	2008-7-28	yyy	add	begin!
//	增加道具的唯一ID表，用于道具锁定。
class	CTableItem	:	public	cfl_rs
{
public:
	CTableItem(	cfl_db*	pDB)
		:	cfl_rs(pDB, "property",	10	)
	{T_B
	T_E}

	//	锁定道具。
	bool	LockItem(	SItemGrid*	sig,	int	iChaId	);

};
//	2008-7-28	yyy	add	end!

class CGameDB
{
public:

    CGameDB::CGameDB()
    : _connect(), _tab_cha(NULL), _tab_master(NULL), _tab_act(NULL), _tab_gld(NULL), _tab_boat(NULL), _tab_log(NULL),_tab_item(NULL),m_bInitOK(FALSE)
    {T_B

    T_E}

    CGameDB::~CGameDB()
    {T_B
       if (_tab_cha != NULL) {delete _tab_cha; _tab_cha = NULL;}
       if (_tab_act != NULL) {delete _tab_act; _tab_act = NULL;}
	   if (_tab_gld != NULL) {delete _tab_gld; _tab_gld = NULL;}
	   if (_tab_master != NULL) {delete _tab_master; _tab_master = NULL;}
	   SAFE_DELETE(_tab_boat);
       SAFE_DELETE(_tab_log);
	   SAFE_DELETE(_tab_item);
	   _connect.disconn();
    T_E}
    
    BOOL    Init();

	bool	BeginTran()
	{
		return _connect.begin_tran();
	}

	bool	RollBack()
	{
		return _connect.rollback();
	}

	bool	CommitTran()
	{
		return _connect.commit_tran();
	}

	bool	ReadPlayer(CPlayer *pPlayer, DWORD cha_id);
	bool	SavePlayer(CPlayer *pPlayer, char chSaveType);
	bool	SavePlayerKitbag(CPlayer *pPlayer, char chSaveType = enumSAVE_TYPE_TRADE)
	{
		return false;
		// 因为此操作可能包含数据库回滚操作，所以期间不能throw异常
		try
		{
			if (!_tab_res->SaveKitbagData(pPlayer->GetMainCha()))
				return false;
			if (!_tab_boat->SaveAllCabin(pPlayer, chSaveType))
				return false;
		}
		catch (...)
		{
			//LG("enter_map", "保存玩家道具和金钱时，发生异常!\n");
			LG("enter_map", "When save character item and money occured abnormity\n");
			return false;
		}

		return true;
	}
	bool	SaveChaAssets(CCharacter *pCCha)
	{
		// 因为此操作可能包含数据库回滚操作，所以期间不能throw异常
		try
		{
			//LG("enter_map", "开始保存角色资产.\n");
			LG("enter_map", "Start save character assets.\n");
			if (!pCCha || !pCCha->GetPlayer())
				return false;

			DWORD	dwStartTick = GetTickCount();
			if (!_tab_cha->SaveMoney(pCCha->GetPlayer()))
				return false;

			if (!pCCha->IsBoat())
			{
				if (!_tab_res->SaveKitbagData(pCCha))
					return false;
			}
			else
			{
				if (!_tab_boat->SaveCabin(*pCCha, enumSAVE_TYPE_TRADE))
					return false;
			}

			//LG("enter_map", "保存角色 %s(%s) 资产成功.\n", pCCha->GetLogName(), pCCha->GetPlyMainCha()->GetLogName());
			LG("enter_map", "Save character %s(%s)assets succeed.\n", pCCha->GetLogName(), pCCha->GetPlyMainCha()->GetLogName());
			//LG("保存数据耗时", "总计%-8d.[%d %s]\n", GetTickCount() - dwStartTick, pCCha->GetPlayer()->GetDBChaId(), pCCha->GetLogName());
			LG("Save data waste time", "totalled %-8d.[%d %s]\n", GetTickCount() - dwStartTick, pCCha->GetPlayer()->GetDBChaId(), pCCha->GetLogName());
		}
		catch (...)
		{
			//LG("enter_map", "保存角色资产时，发生异常!\n");
			LG("enter_map", "When save character assets occured abnormity\n");
			return false;
		}

		return true;
	}

	// Add by lark.li 20080527 begin
	bool	GetWinItemno(int issue, string& itemno)
	{
		try
		{
			return this->_tab_setting->GetWinItemNo(issue, itemno);
		}
		catch (...)
		{
			return false;
		}
	}

	bool	CalWinTicket(int issue, int max, string& itemno)
	{
		try
		{
			if(!this->_tab_ticket->CalWinTicket(issue, max, itemno))
				return false;
			
			this->_tab_setting->SetWinItemNo(issue, itemno.c_str());

			//this->DisuseIssue(issue, 1);

			//this->AddIssue(issue + 1);

			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	bool	GetLotteryIssue(int& issue)
	{
		try
		{
			return this->_tab_setting->GetCurrentIssue(issue);	
		}
		catch (...)
		{
			return false;
		}
	}

	bool	LotteryIsExsit(int issue, char* itemno)
	{
		try
		{
			return this->_tab_ticket->IsExist(issue, itemno);
		}
		catch (...)
		{
			return false;
		}
	}

	bool	AddLotteryTicket(CCharacter *pCCha, int issue, char itemno[6][2])
	{
		try
		{
			this->_tab_ticket->AddTicket(pCCha->m_ID, issue, itemno);
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	bool AddIssue(int issue)
	{
		try
		{
			this->_tab_setting->AddIssue(issue);
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	bool DisuseIssue(int issue, int state)
	{
		try
		{
			this->_tab_setting->DisuseIssue(issue, state);
		}
		catch (...)
		{
			return false;
		}

		return true;
	}

	bool IsValidAmphitheaterTeam(int teamID, int captainID, int member1, int member2)
	{
		bool ret = false;

		try
		{
			ret = this->_tab_amp_team->IsValidAmphitheaterTeam(teamID, captainID, member1, member2);
		}
		catch (...)
		{
			ret = false;
		}

		return ret;
	}

	// 师徒关系判断
	bool IsMasterRelation(int masterID, int prenticeID)
	{
		bool ret = false;

		try
		{
			ret = this->_tab_master->IsMasterRelation(masterID, prenticeID);
		}
		catch (...)
		{
			ret = false;
		}

		return ret;
	}

	// 取得当前赛季 和 轮次s
	bool GetAmphitheaterSeasonAndRound(int& season, int& round)
	{
		try
		{
			return this->_tab_amp_setting->GetCurrentSeason(season, round);	
		}
		catch (...)
		{
			return false;
		}
	}

	// 追加赛季
	bool AddAmphitheaterSeason(int season)
	{
		try
		{
			return this->_tab_amp_setting->AddSeason(season);	
		}
		catch (...)
		{
			return false;
		}
	}

	// 更新赛季状态
	bool DisuseAmphitheaterSeason(int season, int state,const char* winner)
	{
		try
		{
			return this->_tab_amp_setting->DisuseSeason(season, state, winner);	
		}
		catch (...)
		{
			return false;
		}
	}

	// 更新轮次 
	bool UpdateAmphitheaterRound(int season, int round)
	{
		try
		{
			return this->_tab_amp_setting->UpdateRound(season, round);	
		}
		catch (...)
		{
			return false;
		}
	}

	// 获取队伍个数
	bool GetAmphitheaterTeamCount(int& count)
	{
		try
		{
			return this->_tab_amp_team->GetTeamCount(count);	
		}
		catch (...)
		{
			return false;
		}
	}

	// 获取队伍ID
	bool GetAmphitheaterNoUseTeamID(int &teamID)
	{
		try
		{
			return this->_tab_amp_team->GetNoUseTeamID(teamID);	
		}
		catch (...)
		{
			return false;
		}
	}

	// 注册
	bool AmphitheaterTeamSignUP(int &teamID, int captain, int member1, int member2)
	{
		try
		{
			return this->_tab_amp_team->TeamSignUP(teamID, captain, member1, member2);	
		}
		catch (...)
		{
			return false;
		}
	}

	// 注销
	bool AmphitheaterTeamCancel(int teamID)
	{
		try
		{
			return this->_tab_amp_team->TeamCancel(teamID);	
		}
		catch (...)
		{
			return false;
		}
	}
	//Add by sunny.sun20080714
	//查询该角色ID是否已经注册
	bool IsAmphitheaterLogin(int pActorID)
	{
		try
		{
			return this->_tab_amp_team->IsLogin(pActorID);
		}
		catch(...)
		{
			return false;
		}
	
	}
	//判断是否地图队伍已满
	bool IsMapFull(int MapID,int &PActorIDNum)
	{
		try 
		{
			return this->_tab_amp_team->IsMapFull(MapID,PActorIDNum);
		}
		catch(...)
		{
			return false;
		}
	}
		//更新地图队伍mapflag
	bool UpdateMapNum(int Teamid,int Mapid,int MapFlag)
	{
		try
		{
			return this->_tab_amp_team->UpdateMapNum(Teamid,Mapid,MapFlag);
		}
		catch(...)
		{
			return false;
		}
	}

	bool GetMapFlag(int Teamid,int & Mapflag)
	{
		try
		{
			return this->_tab_amp_team->GetMapFlag(Teamid,Mapflag);
		}
		catch(...)
		{
			return false;
		}
		
	}
	bool SetMaxBallotTeamRelive(void)
	{
		try
		{
			return this->_tab_amp_team->SetMaxBallotTeamRelive();
		}
		catch(...)
		{
			return false;
		}
	}

	bool SetMatchResult(int Teamid1,int Teamid2,int Id1state,int Id2state)
	{
		try
		{
			return this->_tab_amp_team->SetMatchResult(Teamid1,Teamid2,Id1state,Id2state);
		}
		catch(...)
		{
			return false;
		}
	}

	bool GetCaptainByMapId(int Mapid,string &Captainid,string & Captainid2)
	{
		try
		{
			return this->_tab_amp_team->GetCaptainByMapId(Mapid,Captainid,Captainid2);
		}
		catch(...)
		{
			return false;
		}
	}

	bool UpdateMap(int Mapid)
	{
		try
		{
			return this->_tab_amp_team->UpdateMap(Mapid);
		}
		catch(...)
		{
			return false;
		}
	
	}

	bool UpdateMapAfterEnter(int CaptainID,int MapID)
	{
		try
		{
			return this->_tab_amp_team->UpdateMapAfterEnter(CaptainID,MapID);
		}
		catch(...)
		{
			return false;
		}
	}

	bool GetPromotionAndReliveTeam(vector< vector< string > > &dataPromotion, vector< vector< string > > &dataRelive)
	{
		try
		{
			return this->_tab_amp_team->GetPromotionAndReliveTeam(dataPromotion, dataRelive);
		}
		catch(...)
		{
			return false;
		}
	}
	
	bool UpdatReliveNum( int ReID )
	{
		try
		{
			return this->_tab_amp_team->UpdatReliveNum(ReID);
		}
		catch(...)
		{
			return false;
		}
	}

	bool UpdateAbsentTeamRelive()
	{
		try
		{
			return this->_tab_amp_team->UpdateAbsentTeamRelive();
		}
		catch(...)
		{
			return false;
		}		
	}

	bool UpdateWinnum(int teamid )
	{
		try
		{
			return this->_tab_amp_team->UpdateWinnum( teamid );
		}
		catch(...)
		{
			return false;
		}
	}
	
	bool GetUniqueMaxWinnum(int &teamid)
	{	
		try
		{
			return this->_tab_amp_team->GetUniqueMaxWinnum( teamid );
		}
		catch(...)
		{
			return false;
		}
	}

	bool SetMatchnoState( int teamid )
	{
		try
		{
			return this->_tab_amp_team->SetMatchnoState( teamid );
		}
		catch(...)
		{
			return false;
		}
	}
	bool UpdateState()
	{
		try
		{
			return this->_tab_amp_team->UpdateState();
		}
		catch(...)
		{
			return false;
		}
	}

	bool CloseReliveByState( int & statenum )
	{	try
		{
			return this->_tab_amp_team->CloseReliveByState( statenum );
		}
		catch(...)
		{
			return false;
		}
	}

	bool CleanMapFlag(int teamid1,int teamid2)
	{
		try
		{
			return this->_tab_amp_team->CleanMapFlag( teamid1,teamid2 );
		}
		catch(...)
		{
			return false;
		}
	
	}
	bool GetStateByTeamid( int teamid, int &state )
	{
		try
		{
			return this->_tab_amp_team->GetStateByTeamid( teamid,state );
		}
		catch(...)
		{
			return false;
		}	
	}

	bool GetPersonBirthday( int chaid, int &birthday)
	{
	
		try
		{
			return this->_tab_per_info->GetPersonBirthday( chaid, birthday );
		}
		catch(...)
		{
			return false;
		}	
	}
	// End

	bool	SavePlayerPos(CPlayer *pPlayer)
	{
		return _tab_cha->SavePos(pPlayer);
	}
	bool	SavePlayerKBagDBID(CPlayer *pPlayer)
	{
		return _tab_cha->SaveKBagDBID(pPlayer);
	}
    bool	SavePlayerKBagTmpDBID(CPlayer *pPlayer)
	{
		return _tab_cha->SaveKBagTmpDBID(pPlayer);
	}
	bool	SavePlayerMMaskDBID(CPlayer *pPlayer)
	{
		return _tab_cha->SaveMMaskDBID(pPlayer);
	}
	bool	CreatePlyBank(CPlayer *pCPly)
	{
		if (pCPly->GetCurBankNum() >= MAX_BANK_NUM)
			return false;
		long lBankDBID;
		if (!_tab_res->Create(lBankDBID, pCPly->GetDBChaId(), enumRESDB_TYPE_BANK))
			return false;
		pCPly->AddBankDBID(lBankDBID);
		if (!_tab_cha->SaveBankDBID(pCPly))
			return false;

		return true;
	}
	bool	SavePlyBank(CPlayer *pCPly, char chBankNO = -1)
	{
		return _tab_res->SaveBankData(pCPly, chBankNO);
	}

	unsigned long GetPlayerMasterDBID(CPlayer *pPlayer)
	{
		return _tab_master->GetMasterDBID(pPlayer);
	}

	BOOL	AddCreditByDBID(DWORD cha_id, long lCredit)
	{
		return _tab_cha->AddCreditByDBID(cha_id, lCredit);
	}

	BOOL	SaveStoreItemID(DWORD cha_id, long lStoreItemID)
	{
		return _tab_cha->SaveStoreItemID(cha_id, lStoreItemID);
	}

	BOOL	AddMoney(DWORD cha_id, long money)
	{
		return _tab_cha->AddMoney(cha_id, money);
	}

	BOOL	ReadKitbagTmpData(DWORD res_id, string& strData)
	{
		return _tab_res->ReadKitbagTmpData(res_id, strData);
	}

	BOOL	SaveKitbagTmpData(DWORD res_id, const string& strData)
	{
		return _tab_res->SaveKitbagTmpData(res_id, strData);
	}

	BOOL	IsChaOnline(DWORD cha_id, BOOL &bOnline)
	{
		return _tab_cha->IsChaOnline(cha_id, bOnline);
	}

	BOOL	SaveMissionData( CPlayer *pPlayer, DWORD cha_id ) // 角色任务信息存盘
	{T_B
		return _tab_cha->SaveMissionData( pPlayer, cha_id );
	T_E}

	// 船只存储
	BOOL Create( DWORD& dwBoatID, const BOAT_DATA& Data )
	{T_B
		return _tab_boat->Create( dwBoatID, Data );
	T_E}
	BOOL GetBoat( CCharacter& Boat )
	{T_B
		return _tab_boat->GetBoat( Boat );
	T_E}
	BOOL SaveBoat( CCharacter& Boat, char chSaveType )
	{T_B
		return _tab_boat->SaveBoat( Boat, chSaveType );
	T_E}
	BOOL SaveBoatDelTag( DWORD dwBoatID, BYTE byIsDeleted = 0 )
	{
		return _tab_boat->SaveBoatDelTag( dwBoatID, byIsDeleted );
	}
	BOOL SaveBoatTempData( CCharacter& Boat, BYTE byIsDeleted = 0 )
	{
		return _tab_boat->SaveBoatTempData( Boat, byIsDeleted );
	}
	BOOL SaveBoatTempData( DWORD dwBoatID, DWORD dwOwnerID, BYTE byIsDeleted = 0 )
	{
		return _tab_boat->SaveBoatTempData( dwBoatID, dwOwnerID, byIsDeleted );
	}
	long CreateGuild(CCharacter* pCha, char guildtype, char *guildname, cChar *passwd)
	{
		return _tab_gld->Create(pCha, guildtype, guildname,passwd);
	}
	bool ListAllGuild(CCharacter* pCha, char guildtype, char disband_days =1)
	{
		return _tab_gld->ListAll(pCha,guildtype,disband_days);
	}
	void GuildTryFor(CCharacter* pCha, uLong guildid)
	{
		_tab_gld->TryFor(pCha,guildid);
	}
	void GuildTryForConfirm(CCharacter* pCha, uLong guildid)
	{
		_tab_gld->TryForConfirm(pCha,guildid);
	}
	char GetGuildTypeByID(CCharacter* pCha, uLong guildid)
	{
		return _tab_gld->GetTypeByID(guildid);
	}
	bool GuildListTryPlayer(CCharacter* pCha, char disband_days)
	{
		return _tab_gld->ListTryPlayer(pCha,disband_days);
	}
	bool GuildApprove(CCharacter* pCha, uLong chaid)
	{
		return _tab_gld->Approve(pCha,chaid);
	}
	bool GuildReject(CCharacter* pCha, uLong chaid)
	{
		return _tab_gld->Reject(pCha,chaid);
	}
	bool GuildKick(CCharacter* pCha, uLong chaid)
	{
		return _tab_gld->Kick(pCha,chaid);
	}
	bool GuildLeave(CCharacter* pCha)
	{
		return _tab_gld->Leave(pCha);
	}
	bool GuildDisband(CCharacter* pCha,cChar *passwd)
	{
		return _tab_gld->Disband(pCha,passwd);
	}
	bool GuildMotto(CCharacter* pCha,cChar *motto)
	{
		return _tab_gld->Motto(pCha,motto);
	}
	CTableMapMask* GetMapMaskTable()
	{
		return _tab_mmask;	
	}
	bool GetGuildName(long lGuildID, std::string& strGuildName)
	{
		return _tab_gld->GetGuildName(lGuildID, strGuildName);
	}
	
	bool Challenge( CCharacter* pCha, BYTE byLevel, DWORD dwMoney )
	{
		return _tab_gld->Challenge( pCha, byLevel, dwMoney );
	}

	bool Leizhu( CCharacter* pCha, BYTE byLevel, DWORD dwMoney )
	{
		return _tab_gld->Leizhu( pCha, byLevel, dwMoney );
	}

	void ListChallenge( CCharacter* pCha )
	{
		return _tab_gld->ListChallenge( pCha );
	}

	bool StartChall( BYTE byLevel )
	{
		for( int i = 0; i < 100; i++ )
		{
			if( _tab_gld->StartChall( byLevel ) )
			{
				return true;
			}
		}

		return false;
	}

	bool GetChall( BYTE byLevel, DWORD& dwGuildID1, DWORD& dwGuildID2, DWORD& dwMoney )
	{
		for( int i = 0; i < 100; i++ )
		{
			if( _tab_gld->GetChallInfo( byLevel, dwGuildID1, dwGuildID2, dwMoney ) )
			{
				return true;
			}
		}

		return false;
	}

	void EndChall( DWORD dwGuild1, DWORD dwGuild2, BOOL bChall )
	{
		return _tab_gld->EndChall( dwGuild1, dwGuild2, bChall );
	}

	bool HasChall( BYTE byLevel )
	{
		return _tab_gld->HasCall( byLevel );
	}

	bool HasGuildLevel( CCharacter* pChar, BYTE byLevel )
	{
		return _tab_gld->HasGuildLevel( pChar, byLevel );
	}

	// 执行sql语句到gamelog表
	void ExecLogSQL(const char *pszSQL)
	{
		SQLRETURN l_sqlret  =  _tab_log->exec_sql_direct(pszSQL);
		if(!DBOK(l_sqlret))
		{
			//LG("gamelog", "添加log记录失败, sql = [%s]!\n", pszSQL);
			LG("gamelog", "add log note failed, sql = [%s]!\n", pszSQL);
		}
	}
	
	// 可以Log 5个字符串字段, 最后一个长度为8000字符以内
	//void Log(const char *type, const char *c1, const char *c2, const char *c3, const char *c4, const char *p, BOOL bAddToList = TRUE);
	//void Log1(int nType, const char *cha1, const char *cha2, const char *pszContent);
	//void Log2(int nType, CCharacter *pCha1, CCharacter *pCha2, const char *pszContent);
	
	// Add by lark.li 20080324 begin
	void ExecTradeLogSQL(const char* gameServerName, const char* action, const char *pszChaFrom, const char *pszChaTo, const char *pszTrade)
	{
		time_t ltime;
		time(&ltime);

		tm* ttm  = localtime(&ltime);
		char time[20];
		time[19] = 0;
        sprintf(time, "%04i/%02i/%02i %02i:%02i:%02i", ttm->tm_year + 1900, ttm->tm_mon + 1, ttm->tm_mday, ttm->tm_hour, ttm->tm_min, ttm->tm_sec);
		
		char format[] = "insert into Trade_Log(ExecuteTime,GameServer,[Action],[From],[To],Memo) values ('%s','%s','%s','%s','%s','%s')";
		
		char sql[1024];
		memset(sql, 0, sizeof(sql));
		sprintf(sql, format, time, gameServerName, action, pszChaFrom, pszChaTo, pszTrade);
		
		ExecLogSQL(sql);
	}
	// End

	BOOL	m_bInitOK;

//	2008-7-28	yyy	add	function	begin!

	//	记录道具到道具表。
	bool	LockItem(	SItemGrid*	sig,	int	iChaId	)
	{
		return	_tab_item->LockItem(	sig,	iChaId	);
	};

//	2008-7-28	yyy	add	function	end!

protected:

    cfl_db			_connect;
    CTableCha*		_tab_cha;
	CTableMaster*	_tab_master;
	CTableResource*	_tab_res;
	
	// Add by lark.li 20080521 begin
	// 彩票
	CTableLotterySetting*	_tab_setting;
	CTableTicket*			_tab_ticket;
	CTableWinTicket*			_tab_winticket;

	// 竞技场
	CTableAmphitheaterSetting*	_tab_amp_setting;
	CTableAmphitheaterTeam*	_tab_amp_team;
	// End
	
	CTablePersoninfo *	_tab_per_info;//Add by sunny.sun20080822
	
	CTableMapMask*	_tab_mmask;
	CTableAct*		_tab_act;
	CTableGuild*	_tab_gld;
	CTableBoat*		_tab_boat;
	CTableLog*		_tab_log;
	CTableItem*		_tab_item;

};



extern CGameDB game_db;

