#if !defined(__VCI_INTERFACE_CLuaInterp_H_INCLUDED__)
#define __VCI_INTERFACE_CLuaInterp_H_INCLUDED__


#include "vcicomm.h"
#include "IInterp.h"

#define INF_IInterp \
{\
	"IInterp",\
	"1.0.0.0",\
	THIS_REVISION_TYPE,\
	"{6D800C48-E676-45C6-A633-B168D04D45A7}",\
	"Lua Interpreter",\
	"blueant",\
	__DATE__\
}
const TInterfaceInfo INTERFACE_INFO_IInterp = INF_IInterp;

class CLuaInterp : public CVisualComponent
{
public:
	CLuaInterp();
	~CLuaInterp();

//////////////////////////////////////////////////////////////////////////
// �ṩ���ӿڵĹ��ܺ���
//////////////////////////////////////////////////////////////////////////
public:
	//{{VCI_IMPLEMENT_DEFINE_BEGIN
	virtual int __stdcall SetIPlatUI(LPVOID lpIPlatUI);// ����ƽ̨UI�ӿ�ָ��
	virtual int __stdcall SetLibPath(LPCTSTR lpszPath);
	virtual int __stdcall IsInterpRunning();
	virtual int __stdcall SetScriptFile(LPCTSTR lpszPathName);
	virtual CString __stdcall GetScriptFile();
	virtual int __stdcall RunScriptFile(LPCTSTR lpszPathName);
	virtual int __stdcall RunScriptCommand(LPCTSTR lpszTclCmd);
	virtual int __stdcall StopScript();
	virtual LPVOID __stdcall GetInterp();
	virtual int __stdcall GetInterpID();
	virtual void __stdcall SetInterpName(LPCTSTR lpszInterptName);
	virtual CString __stdcall GetInterpName();
	virtual int __stdcall GetErrorLine();
	virtual CString __stdcall GetResult();
	virtual int __stdcall SetVar(LPCTSTR lpszVarName, LPCTSTR lpszVarValue);
	virtual CString __stdcall GetVar(LPCTSTR lpszVarName);
	virtual int __stdcall RegisterCommand(LPVOID pInterp, LPCTSTR lpszCmd, LPVOID lpFunc);
	virtual int __stdcall SetInterpParam(LPCTSTR lpszParamName, LPCTSTR lpszParamValue);
	virtual CString __stdcall GetInterpParam(LPCTSTR lpszParamName);
	virtual int __stdcall SetRunMode(int nRunMode);
	virtual int __stdcall GetRunMode();
	virtual int __stdcall SetRunState(int nRunState);
	virtual int __stdcall GetRunState();
	virtual int __stdcall GetCurStackLevel();
	virtual int __stdcall GetKeyWordList(LPCTSTR lpszType, CStringArray& asKeyWord);
	virtual int __stdcall SetDebugEvent(int nEvent, int nParam, LPCTSTR lpszParam);
	virtual int __stdcall SetBreakList(LPCTSTR lpszFile, CUIntArray& auBreaks);
	virtual int __stdcall GetBreakList(LPCTSTR lpszFile, CUIntArray& auBreaks);
	virtual int __stdcall GetEnableProfileAnalyse();
	virtual int __stdcall GetAvailableLineCount();
	virtual LPVOID __stdcall GetProfileMap();
	virtual int __stdcall MethodIsSupport(LPCTSTR lpszMethod);
	virtual int __stdcall InitialDebugMode(CString& strResult);
	virtual int __stdcall RefreshDebugWindow(LPCTSTR lpszWindow, BOOL bActive, CString& strResult);
	virtual int __stdcall CallMethod(LPCTSTR lpszMethod, CStringArray& asParam);
	virtual int __stdcall Compile(LPCTSTR lpszSrcFile, CString& strDestFile, LPCTSTR lpszParams);
	virtual int __stdcall Build(LPCTSTR lpszSrcFile, CString& strDestFile, LPCTSTR lpszParams);
	//}}VCI_IMPLEMENT_DEFINE_END

	virtual int __stdcall InstallHandler(DWORD nEventID, LPVOID lpHandler, DWORD dwRefData);
	virtual int __stdcall UninstallHandler(DWORD nEventID, LPVOID lpHandler);

	void SetHide(BOOL bHide) { m_bHide = bHide; }
	BOOL GetHide() { return m_bHide; }
	void SetRunLevel(int nLevel) { m_nRunLevel = nLevel; }
	int	 GetRunLevel() { return m_nRunLevel; }
	void SetStopSignal(BOOL bStop) { m_bStopSignal = bStop; }
	BOOL GetStopSignal() { return m_bStopSignal; }
	void SetBreakSignal(BOOL bBreak);
	BOOL GetBreakSignal() { return m_bBreakSignal; }
	void SetBreakMode(int nMode) { m_nBreakMode = nMode; }
	int  GetBreakMode() { return m_nBreakMode; }
	void SetBreakLineNo(int nLineNo) { m_nBreakLineNo = nLineNo; }
	int  GetBreakLineNo() { return m_nBreakLineNo; }
	void SetBreakName(LPCTSTR lpszName) { m_strBreakName = lpszName; }
	CString GetBreakName() { return m_strBreakName; }
	void SetBreakLevel(int nLevel) { m_nBreakLevel = nLevel; }
	int  GetBreakLevel() { return m_nBreakLevel; }
	void SetStackLevel(int nLevel) { m_nStackLevel = nLevel; }
	int	 GetStackLevel() { return m_nStackLevel; }

	BOOL RunProgramWithPipe(CString strExePath, CString strParam, int nOutputId = 1, BOOL bActiveOutput = FALSE);
	BOOL TerminatePipeProcess();
	BOOL ExecProcess(CString strExePath, CString strParam, BOOL bWaitEnd = FALSE);

	int  LuaSetPlatformVariable();

	// ���ļ�����
	CStringArray* GetDebugScriptList() { return &m_asDebugScript; }
	int  FindDebugFile(CString strFileName);
	int  AddDebugFile(CString strFileName);
	BOOL ClearDebugFile();

	// ����
	void DebugBreak(const char *szFile, int nStackLevel, int nLine);
	void LineHook(const char *szFile, int nLine);
	int	 LuaReport(int status);
	int	 LuaDocall(int narg, int clear);

	CString LuaMakeNumber(double dnum);
	CString LuaMakeBoolean(int num);
	CString LuaGetTableInfo(int nIndex);
	int  EnumerateTable(int nTableRef, int nIndex, CUIntArray& auReferences);

	CString GetValueString(int nIndex);
	CString Describe(int nIndex);

	int  RefreshVarWindow();
	int  RefreshFuncWindow();
	int  RefreshStackWindow();

// attribute
public:
	lua_State*	pLState;		// ����Lua������״̬��ָ��
	int			m_nInterpID;	// ������ID(������Ψһ��ʶ)
	IPlatUI*	pIPlatUI;		// ƽ̨����ӿ�
	DWORD		m_dwRunThreadId;// �ű����е��߳�ID
	HANDLE		m_hPipeProcess;	// �ܵ����̾��
	BOOL		m_bPipeProcessTerminated;	// �ܵ������Ƿ���ֹ��
	BOOL		m_bHide;		// �������Ƿ�����(�ڵ������в��ɼ�)
	CString		m_strInterpName;// ������(��������������)
	CString		m_strScriptFile;// �ű��ļ�
	int			m_nRunMode;		// �ű�����ģʽ
	int			m_nRunState;	// �ű�����״̬
	int			m_nRunLevel;	// �ű����м���(Ȩ��)
	BOOL		m_bStopSignal;	// �ű���ֹ�ź�
	BOOL		m_bBreakSignal;	// �ϵ㼤���ź�
	int			m_nEvalResult;	// �ű����н��
	int			m_nBreakMode;	// ��ǰ�ϵ�ģʽ
	int			m_nBreakLineNo;	// �ϵ��к�
	CString		m_strBreakName;	// �����ϵ���
	int			m_nBreakLevel;	// ��ǰ��ջ���
	CUIntArray	m_auBreakList;	// �ϵ��б�
	int			m_nStackLevel;	// ����Ķ�ջ����
	BOOL		m_bProfileEnable;	// �Ƿ��������и����ʷ���
	int			m_nTDLineCount;	// ��td��ǵ�����
	CMap<int,int,int,int> m_ProfileMap;	// �洢�����еĹ�ϣ��
	INTERP_EXIT_FUNC*	m_lpfnExit;	// �˳��ص�����
	INTERP_DEBUG_FUNC*	m_lpfnDebug;// ���Իص�����
	HMODULE		m_hLoaded[1024];	// ������ؿ�ľ���б�
	int			m_nLoaded;			// �Ѽ�����չ�������
	CString		m_strResult;		// �����Ϣ

	CStringArray m_asDebugScript;	// ���Թ����и��ٽ�ȥ���ļ�

	HANDLE		m_hDebugEvent;     //�����¼������ڶϵ㣬����ģʽ����Ż����
	int			m_nCurCommand;     //��ǰ�յ��ĵ���ָ�IDB_STEPINTO��IDB_NEXT��

	int			m_nOutputVar;      // ��������ID
	int			m_nOutputObject;   // ���󴰿�ID
	int			m_nOutputFunc;	   // ��������ID
	int			m_nOutputStack;    // ��ջ����ID

//////////////////////////////////////////////////////////////////////////
// Ҫ����Ĺ��ܽӿ�
//////////////////////////////////////////////////////////////////////////
protected:
	// �ӿڶ���
	BEGIN_INTERFACE_PART(VciControl, IVciControl)
		CONTROL_INTERFACE_DEFINE
	END_INTERFACE_PART(VciControl)
	EXPORT_CONTROL_INTERFACE_PART(VciControl)

	BEGIN_INTERFACE_PART(LuaInterp, IInterp)
		//{{ ע�⣺!!!�����Ǳ�������Ҫ����������ɾ��!!!
		// ��ȡ�ӿڵĶ�����Ϣ
		virtual LPVOID __stdcall GetExtraInfo(LPVOID lpRefData);
		//}} ע�⣺!!!�����Ǳ�������Ҫ����������ɾ��!!!

	//{{VCI_INTERFACE_PART_BEGIN
		virtual int __stdcall SetIPlatUI(LPVOID lpIPlatUI);// ����ƽ̨UI�ӿ�ָ��
		virtual int __stdcall SetLibPath(LPCTSTR lpszPath);
		virtual int __stdcall IsInterpRunning();
		virtual int __stdcall SetScriptFile(LPCTSTR lpszPathName);
		virtual CString __stdcall GetScriptFile();
		virtual int __stdcall RunScriptFile(LPCTSTR lpszPathName);
		virtual int __stdcall RunScriptCommand(LPCTSTR lpszTclCmd);
		virtual int __stdcall StopScript();
		virtual LPVOID __stdcall GetInterp();
		virtual int __stdcall GetInterpID();
		virtual void __stdcall SetInterpName(LPCTSTR lpszInterptName);
		virtual CString __stdcall GetInterpName();
		virtual int __stdcall GetErrorLine();
		virtual CString __stdcall GetResult();
		virtual int __stdcall SetVar(LPCTSTR lpszVarName, LPCTSTR lpszVarValue);
		virtual CString __stdcall GetVar(LPCTSTR lpszVarName);
		virtual int __stdcall RegisterCommand(LPVOID pInterp, LPCTSTR lpszCmd, LPVOID lpFunc);
		virtual int __stdcall SetInterpParam(LPCTSTR lpszParamName, LPCTSTR lpszParamValue);
		virtual CString __stdcall GetInterpParam(LPCTSTR lpszParamName);
		virtual int __stdcall SetRunMode(int nRunMode);
		virtual int __stdcall GetRunMode();
		virtual int __stdcall SetRunState(int nRunState);
		virtual int __stdcall GetRunState();
		virtual int __stdcall GetCurStackLevel();
		virtual int __stdcall GetKeyWordList(LPCTSTR lpszType, CStringArray& asKeyWord);
		virtual int __stdcall SetDebugEvent(int nEvent, int nParam, LPCTSTR lpszParam);
		virtual int __stdcall SetBreakList(LPCTSTR lpszFile, CUIntArray& auBreaks);
		virtual int __stdcall GetBreakList(LPCTSTR lpszFile, CUIntArray& auBreaks);
		virtual int __stdcall GetEnableProfileAnalyse();
		virtual int __stdcall GetAvailableLineCount();
		virtual LPVOID __stdcall GetProfileMap();
		virtual int __stdcall MethodIsSupport(LPCTSTR lpszMethod);
		virtual int __stdcall InitialDebugMode(CString& strResult);
		virtual int __stdcall RefreshDebugWindow(LPCTSTR lpszWindow, BOOL bActive, CString& strResult);
		virtual int __stdcall CallMethod(LPCTSTR lpszMethod, CStringArray& asParam);
		virtual int __stdcall Compile(LPCTSTR lpszSrcFile, CString& strDestFile, LPCTSTR lpszParams);
		virtual int __stdcall Build(LPCTSTR lpszSrcFile, CString& strDestFile, LPCTSTR lpszParams);
	//}}VCI_INTERFACE_PART_END
	END_INTERFACE_PART(LuaInterp)
	EXPORT_INTERFACE_PART(LuaInterp)
};

// ��������������
CPtrList* GetInterpList();
CLuaInterp* GetLuaInterp(LPVOID lpInterp);

// Lua��չ����ע�ắ��
int LuaExCmd_Register(lua_State *L);

#endif // !defined(__VCI_INTERFACE_CLuaInterp_H_INCLUDED__)