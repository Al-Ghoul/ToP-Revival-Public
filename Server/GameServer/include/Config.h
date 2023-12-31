#pragma once

#include <string>

#define MAX_GATE 5
#define MAX_MAP  100
#define MAX_MAPNAME_LENGTH	32

class CGameConfig
{

public:	
	
    CGameConfig();
	
	bool	Load(char *pszFileName);
	void	SetDefault();
	
public:

	// 请注意此处不要放置任何非固定内存尺寸的变量, 比如模板, string之类的,
	// 此类将被直接写盘和读盘
	char    m_szGateIP[MAX_GATE][64];  // GateIP地址列表
    int     m_nGatePort[MAX_GATE];     // Gate Port列表
    int     m_nGateCnt;                // Gate数量
    char    m_szInfoIP[64];            // InfoServer IP
    int     m_nInfoPort;               // InfoServer Port
	char	m_szInfoPwd[33];		   // InfoServer验证码
	int		m_nSection;				   // 小区号
    char    m_szMapList[MAX_MAP][MAX_MAPNAME_LENGTH];
	BYTE	m_btMapOK[MAX_MAP];		   // 地图是否初始化成功
	int     m_nMapCnt;				   // 地图数量
	char	m_szEqument[MAX_MAPNAME_LENGTH];   // 世界守护神
    char    m_szName[64];			   // 服务器名字
	char	m_szDBIP[64];			   // DB IP
	char	m_szDBUsr[32];			   // DB 用户名
	char	m_szDBPass[32];			   // DB 密码
	std::string driverVersion_;
	char	databaseName_[64];

	// Add by lark.li 20080321 begin
	char	m_szTradeLogDBIP[64];			   // DB IP
	char	m_szTradeLogDBName[32];			   // DB IP
	char	m_szTradeLogDBUsr[32];			   // DB 用户名
	char	m_szTradeLogDBPass[32];			   // DB 密码

	BOOL	m_bTradeLogIsConfig;
	// End

	long	m_lSocketAlive;            // Socket保持活动
	int		m_nMaxPly;                 // 最大玩家数
	int		m_nMaxCha;                 // 最大角色数
	int		m_nMaxItem;                // 最大道具数
	int		m_nMaxTNpc;                // 最大对话NPC
	unsigned long	m_ulBaseID;        // 服务器的ID基数
	long	m_lItemShowTime;           // 道具存在时间
	long	m_lItemProtTime;           // 道具保护时间
	long	m_lSayInterval;            // 喊话间隔
	char	m_szResDir[255];		   // 运行资源所在的目录
	char	m_szLogDir[255];		   // Log所在的目录
	char	m_chMapMask;               // 是否存取大地图
	long	m_lDBSave;                 // 数据库定时存盘时间间隔

	BOOL	m_bLogAI;				   // 是否打开AI的log
	BOOL	m_bLogCha;				   // 是否打开角色的log
	BOOL	m_bLogCal;				   // 是否打开数值计算的log
	BOOL	m_bLogMission;			   // 是否打开Mission的log

	BOOL	m_bSuperCmd;
	
	// Add by lark.li 20080731 begin
	vector<int>	m_vGMCmd;
	// End
	
	BOOL	m_bLogDB;				   // 是否把玩家行为记录到数据库
};

#define	defCONFIG_FILE_NAME_LEN	512
extern char	szConfigFileN[defCONFIG_FILE_NAME_LEN];
extern CGameConfig g_Config;

