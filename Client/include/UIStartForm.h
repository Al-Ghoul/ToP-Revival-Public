#pragma once
#include "UIGlobalVar.h"
#include "ChaState.h"//add by alfred.shi 20080709
#include "uipage.h"	//add by alfred.shi 20080709

class	CCharacter2D;
struct	stNetChangeChaPart;
namespace GUI
{

class CTitle;
class CImage;
class CItemCommand;

// ��ʼ�˵�
class CStartMgr : public CUIInterface
{
public:
	void			MainChaDied();

    void            RefreshMainLifeNum( long num, long max );
	void			RefreshMainExperience(	LONG64 num , LONG64 curlev, LONG64 nextlev );
	void			RefreshMainSP(long num, long max );
	void			RefreshMainName(const char* szName );
	void			RefreshMainFace( stNetChangeChaPart& stPart );

	void			RefreshPet( CItemCommand* pItem );

	void			SetIsLeader( bool v );
	bool			GetIsLeader();

	void			RefreshLv( long l );
	void			PopMenu( CCharacter* pCha );

	void			CloseForm();
	void			CheckMouseDown(int x, int y);
	void			ShowBigText( const char* str );

	void			ShowQueryReliveForm( int nType, const char* str );				// ��ʾ�Ƿ�ԭ�ظ����

	void			ShowShipSailForm( bool isShow = true );
	void			UpdateShipSailForm();

	void			SetIsNewer( bool v )	{ _IsNewer = v;			}

	void			SysLabel( const char *pszFormat, ... );
	void			SysHide();

	void			AskTeamFight( const char* str );

	bool			IsCanTeam()				{ return _IsCanTeam;	}
	void			SetIsCanTeam( bool v )	{ _IsCanTeam = v;		}
	bool			IsCanTeamAndInfo();

	void			ShowHelpSystem(bool bShow = true, int nIndex = -1);
	void			ShowLevelUpHelpButton(bool bShow = true);
	void			ShowLevelUpaddButton(bool bShow = true);		//	Add by alfred.shi
	void			ShowInfoCenterButton(bool bShow = true);

	void			ShowBagButtonForm(bool bShow = true);
	void			ShowSociliatyButtonForm(bool bShow = true);

	static CTextButton*	GetShowQQButton();

	// NPCָ�� add by alfred.shi 20080709
	void			ShowNPCHelper(const char * mapName,bool isShow /*= true*/);
	const char*		GetCurrMapName() {return strMapName;}
	//Ů��ť���� add by alfred.shi 20080724;
	//CForm*			frmQueen;
	void			ShowQueenButtonForm(bool isShow = true);
	CList*			GetNpcList(){return lstNpcList;}
	CCheckBox*		chkID;
	//end
protected:
	virtual bool Init();
    virtual void End();
	virtual void FrameMove(DWORD dwTime);
	virtual void SwitchMap();

private:
	static void		_evtStartFormMouseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);
	static void		_evtReliveFormMouseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);

	static void		_evtTaskMouseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);

	// ���鵥���ĶԻ���ص�
	static void		_evtAskTeamFightMouseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);

	static void		_evtChaActionChange(CGuiData *pSender);       //�ı��ɫ�Ķ���
	static void		_evtChaHeartChange(CGuiData *pSender);         //�ı��ɫ������

	static void		_evtPopMenu(CGuiData *pSender, int x, int y, DWORD key);

	static void		_evtSelfMouseDown(CGuiData *pSender,int x,int y ,DWORD key);	// ���Լ���Ѫ�¼�

	static void		_evtOriginReliveFormMouseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);

	static void		_evtShowBoatAttr(CGuiData *pSender,int x,int y ,DWORD key);		// ��ʾ��ֻ����

	static void		_NewFrmMainMouseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);

	static void		_HelpFrmMainMouseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);

	static void		_CloseEvent(CCompent *pSender, int nMsgType, int x, int y, DWORD dwKey);

	//static const int HELP_PICTURE_COUNT = 68;	// ���ְ����������
	static const int HELP_PICTURE_COUNT = 84;	// ���ְ���������� Modify by sunny.sun 20080828
	static const int HELP_LV1_BEGIN     = 28;	// Level1��ͼƬ�±�

private:
	CForm*			frmMain800;

	CForm*			frmMainFun;
	//CTextButton*	btnStart;
	static CTextButton*	btnQQ;

	//����Լ���Ѫ����sp�� exp������
	CForm*			frmDetail;
	CProgressBar*	proMainHP;
	CProgressBar*	proMainSP;
	CProgressBar*	proMainExp;
	CLabel*			labMainName;
	CLabel*			labMainLevel;
	CImage*		    imgLeader;

 //   CProgressBar*	proMainHP1;		//��ɫ������ֵ
	//CProgressBar*	proMainHP2;		//��ɫ������ֵ
	//CProgressBar*	proMainHP3;		//��ɫ������ֵ
	//CProgressBar*	proMainSP;		//��ɫ������ֵ   	

	// ��Ҿ��飬�ȼ�
	//CLabel*			_pShowExp;
	//CLabel*			_pShowLevel;

	CForm*			frmMainChaRelive;			// ���Ǹ������

	// ����,����
	CGrid*			grdAction;
	CGrid*			grdHeart;

	// ��ʾ�����
	CTitle*			tlCity;
	CTitle*			tlField;

	// �����е��Ҽ��˵�
	static CMenu*	mainMouseRight;

	//��ֻ����ʱ�Ľ���
	CForm*			frmShipSail;
	CLabelEx*		labCanonShow;
	CLabelEx*		labSailorShow;
	CLabelEx*		labLevelShow;
	CLabelEx*		labExpShow;
	CProgressBar*	proSailor;				//�;ù�����
	CProgressBar*	proCanon;				//����������

	bool			_IsNewer;				// �Ƿ�Ϊ����

	// ��ʾ�Զ�������ʾ
	CForm*			frmFollow;
	CLabel*			labFollow;

	CMenu*			mnuSelf;

	bool			_IsCanTeam;				// �Ƿ��ܹ�ʹ�������ӵ��������صĲ���

	// �������
	CForm*			frmMainPet;
	CImage*			imgPetHead;
	CLabel*			labPetLv;
	CProgressBar*	proPetHP;
	CProgressBar*	proPetSP;

	// ���ְ�������
	CForm*			frmHelpSystem;			// ��������
	CTextButton*	btnLevelUpHelp;			// ����������ť
	CTextButton*	btnLevelUpadd;			// ��������
	CList*			lstHelpList;			// �����б�

	CImage*			imgHelpShow1[HELP_PICTURE_COUNT];		// ͼƬ
	CImage*			imgHelpShow2[HELP_PICTURE_COUNT];		// ͼƬ
	CImage*			imgHelpShow3[HELP_PICTURE_COUNT];		// ͼƬ
	CImage*			imgHelpShow4[HELP_PICTURE_COUNT];		// ͼƬ

	// ������ť����
	CForm*			frmBag;

	// �罻��ť����
	CForm*			frmSociliaty;
	//Ů��ť���� add by alfred.shi 20080724
	CForm*			frmQueen;
	

	// NPCָ������ add by alfred.shi 20080709
	CForm*			frmNpcShow;
	CPage*			listPage;
	CList*			lstNpcList;
	CList*			lstMonsterList;
	//CList*			lstBOSSList;
	CList*			lstCurrList;
	const char*		strMapName;
private:
	// ��Ӧ���������
	static CCharacter2D*	pMainCha;				
    static void				_MainChaRenderEvent(C3DCompent *pSender, int x, int y);
	static void				_OnSelfMenu(CGuiData *pSender, int x, int y, DWORD key);

	static void				_evtHelpListChange(CGuiData *pSender);
	static void				_evtNPCListChange(CGuiData *pSender); // add by alfred.shi 20080709
	static void				_evtPageIndexChange(CGuiData *pSender);// add by alfred.shi 20080709
};

}
