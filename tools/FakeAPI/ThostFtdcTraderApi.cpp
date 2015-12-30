#include "stdafx.h"

#define ISLIB
#define LIB_TRADER_API_EXPORT

#include <stdio.h>
#include "../../include/CTP/ThostFtdcTraderApi.h"

class MyClassCTP :public CThostFtdcTraderApi
{
public:
	///����TraderApi
	///@param pszFlowPath ����������Ϣ�ļ���Ŀ¼��Ĭ��Ϊ��ǰĿ¼
	///@return ��������UserApi
	static CThostFtdcTraderApi *CreateFtdcTraderApi(const char *pszFlowPath = "");

	///��ȡAPI�İ汾��Ϣ
	///@retrun ��ȡ���İ汾��
	static const char *GetApiVersion();

	///ɾ���ӿڶ�����
	///@remark ����ʹ�ñ��ӿڶ���ʱ,���øú���ɾ���ӿڶ���
	virtual void Release(){}

	///��ʼ��
	///@remark ��ʼ�����л���,ֻ�е��ú�,�ӿڲſ�ʼ����
	virtual void Init()
	{
		m_pSpi->OnFrontConnected();
	}

	///�ȴ��ӿ��߳̽�������
	///@return �߳��˳�����
	virtual int Join(){ return 0; }

	///��ȡ��ǰ������
	///@retrun ��ȡ���Ľ�����
	///@remark ֻ�е�¼�ɹ���,���ܵõ���ȷ�Ľ�����
	virtual const char *GetTradingDay(){ return 0; }

	///ע��ǰ�û������ַ
	///@param pszFrontAddress��ǰ�û������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:17001���� 
	///@remark ��tcp����������Э�飬��127.0.0.1��������������ַ����17001�������������˿ںš�
	virtual void RegisterFront(char *pszFrontAddress){}

	///ע�����ַ����������ַ
	///@param pszNsAddress�����ַ����������ַ��
	///@remark �����ַ�ĸ�ʽΪ����protocol://ipaddress:port�����磺��tcp://127.0.0.1:12001���� 
	///@remark ��tcp����������Э�飬��127.0.0.1��������������ַ����12001�������������˿ںš�
	///@remark RegisterNameServer������RegisterFront
	virtual void RegisterNameServer(char *pszNsAddress){}

	///ע�����ַ������û���Ϣ
	///@param pFensUserInfo���û���Ϣ��
	virtual void RegisterFensUserInfo(CThostFtdcFensUserInfoField * pFensUserInfo){}

	///ע��ص��ӿ�
	///@param pSpi �����Իص��ӿ����ʵ��
	virtual void RegisterSpi(CThostFtdcTraderSpi *pSpi)
	{
		m_pSpi = pSpi;
	}

	///����˽������
	///@param nResumeType ˽�����ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼��˽����������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ�˽���������ݡ�
	virtual void SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType){}

	///���Ĺ�������
	///@param nResumeType �������ش���ʽ  
	///        THOST_TERT_RESTART:�ӱ������տ�ʼ�ش�
	///        THOST_TERT_RESUME:���ϴ��յ�������
	///        THOST_TERT_QUICK:ֻ���͵�¼�󹫹���������
	///@remark �÷���Ҫ��Init����ǰ���á����������򲻻��յ������������ݡ�
	virtual void SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType){}

	///�ͻ�����֤����
	virtual int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID)
	{
		char buf[512] = { 0 };
		sprintf(buf, "UserProductInfo:%s\nAuthCode:%s\n�Ѿ����Ƶ�������",
			pReqAuthenticateField->UserProductInfo,
			pReqAuthenticateField->AuthCode);

		if (OpenClipboard(NULL))
		{
			int len = strlen(buf) + 1;

			HGLOBAL hmem = GlobalAlloc(GHND, len);
			char *pmem = (char*)GlobalLock(hmem);

			EmptyClipboard();
			strcpy(pmem, buf);
			SetClipboardData(CF_TEXT, hmem);
			CloseClipboard();
			GlobalFree(hmem);
		}

		MessageBoxA(nullptr, buf, "", MB_OK);

		return 0;
	}

	///�û���¼����
	virtual int ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLoginField, int nRequestID)
	{
		char buf[512] = { 0 };
		sprintf(buf, "UserID:%s\nPassword:%s\nUserProductInfo:%s\n�Ѿ����Ƶ�������",
			pReqUserLoginField->UserID,
			pReqUserLoginField->Password,
			pReqUserLoginField->UserProductInfo);

		if (OpenClipboard(NULL))
		{
			int len = strlen(buf) + 1;

			HGLOBAL hmem = GlobalAlloc(GHND, len);
			char *pmem = (char*)GlobalLock(hmem);

			EmptyClipboard();
			strcpy(pmem, buf);
			SetClipboardData(CF_TEXT, hmem);
			CloseClipboard();
			GlobalFree(hmem);
		}

		MessageBoxA(nullptr, buf, "", MB_OK);

		return 0;
	}


	///�ǳ�����
	virtual int ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID){ return 0; }

	///�û������������
	virtual int ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID){ return 0; }

	///�ʽ��˻������������
	virtual int ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID){ return 0; }

	///����¼������
	virtual int ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID){ return 0; }

	///Ԥ��¼������
	virtual int ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID){ return 0; }

	///Ԥ�񳷵�¼������
	virtual int ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID){ return 0; }

	///������������
	virtual int ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID){ return 0; }

	///��ѯ��󱨵���������
	virtual int ReqQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID){ return 0; }

	///Ͷ���߽�����ȷ��
	virtual int ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID){ return 0; }

	///����ɾ��Ԥ��
	virtual int ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID){ return 0; }

	///����ɾ��Ԥ�񳷵�
	virtual int ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID){ return 0; }

	///ִ������¼������
	virtual int ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, int nRequestID){ return 0; }

	///ִ�������������
	virtual int ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, int nRequestID){ return 0; }

	///ѯ��¼������
	virtual int ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID){ return 0; }

	///����¼������
	virtual int ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID){ return 0; }

	///���۲�������
	virtual int ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID){ return 0; }

	///��������
	virtual int ReqLockInsert(CThostFtdcInputLockField *pInputLock, int nRequestID){ return 0; }

	///�������¼������
	virtual int ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, int nRequestID){ return 0; }

	///�����ѯ����
	virtual int ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID){ return 0; }

	///�����ѯ�ɽ�
	virtual int ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID){ return 0; }

	///�����ѯͶ���ֲ߳�
	virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID){ return 0; }

	///�����ѯ�ʽ��˻�
	virtual int ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID){ return 0; }

	///�����ѯͶ����
	virtual int ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID){ return 0; }

	///�����ѯ���ױ���
	virtual int ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID){ return 0; }

	///�����ѯ��Լ��֤����
	virtual int ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID){ return 0; }

	///�����ѯ��Լ��������
	virtual int ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID){ return 0; }

	///�����ѯ������
	virtual int ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID){ return 0; }

	///�����ѯ��Ʒ
	virtual int ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID){ return 0; }

	///�����ѯ��Լ
	virtual int ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID){ return 0; }

	///�����ѯ����
	virtual int ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID){ return 0; }

	///�����ѯͶ���߽�����
	virtual int ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID){ return 0; }

	///�����ѯת������
	virtual int ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID){ return 0; }

	///�����ѯͶ���ֲ߳���ϸ
	virtual int ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID){ return 0; }

	///�����ѯ�ͻ�֪ͨ
	virtual int ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID){ return 0; }

	///�����ѯ������Ϣȷ��
	virtual int ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID){ return 0; }

	///�����ѯͶ���ֲ߳���ϸ
	virtual int ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID){ return 0; }

	///�����ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ
	virtual int ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID){ return 0; }

	///�����ѯ�ֵ��۵���Ϣ
	virtual int ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID){ return 0; }

	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤��
	virtual int ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin, int nRequestID){ return 0; }

	///�����ѯ��������֤����
	virtual int ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField *pQryExchangeMarginRate, int nRequestID){ return 0; }

	///�����ѯ������������֤����
	virtual int ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID){ return 0; }

	///�����ѯ����
	virtual int ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID){ return 0; }

	///�����ѯ������������Ա����Ȩ��
	virtual int ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID){ return 0; }

	///�����ѯ��Ʒ���ۻ���
	virtual int ReqQryProductExchRate(CThostFtdcQryProductExchRateField *pQryProductExchRate, int nRequestID){ return 0; }

	///�����ѯ��Ȩ���׳ɱ�
	virtual int ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost, int nRequestID){ return 0; }

	///�����ѯ��Ȩ��Լ������
	virtual int ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID){ return 0; }

	///�����ѯִ������
	virtual int ReqQryExecOrder(CThostFtdcQryExecOrderField *pQryExecOrder, int nRequestID){ return 0; }

	///�����ѯѯ��
	virtual int ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID){ return 0; }

	///�����ѯ����
	virtual int ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID){ return 0; }

	///�����ѯ����
	virtual int ReqQryLock(CThostFtdcQryLockField *pQryLock, int nRequestID){ return 0; }

	///�����ѯ����֤ȯ��λ
	virtual int ReqQryLockPosition(CThostFtdcQryLockPositionField *pQryLockPosition, int nRequestID){ return 0; }

	///�����ѯ��Ϻ�Լ��ȫϵ��
	virtual int ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard, int nRequestID){ return 0; }

	///�����ѯ�������
	virtual int ReqQryCombAction(CThostFtdcQryCombActionField *pQryCombAction, int nRequestID){ return 0; }

	///�����ѯת����ˮ
	virtual int ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID){ return 0; }

	///�����ѯ����ǩԼ��ϵ
	virtual int ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID){ return 0; }

	///�����ѯǩԼ����
	virtual int ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID){ return 0; }

	///�����ѯԤ��
	virtual int ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID){ return 0; }

	///�����ѯԤ�񳷵�
	virtual int ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID){ return 0; }

	///�����ѯ����֪ͨ
	virtual int ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID){ return 0; }

	///�����ѯ���͹�˾���ײ���
	virtual int ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID){ return 0; }

	///�����ѯ���͹�˾�����㷨
	virtual int ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID){ return 0; }

	///�����ѯ��������û�����
	virtual int ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, int nRequestID){ return 0; }

	///�ڻ����������ʽ�ת�ڻ�����
	virtual int ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID){ return 0; }

	///�ڻ������ڻ��ʽ�ת��������
	virtual int ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID){ return 0; }

	///�ڻ������ѯ�����������
	virtual int ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, int nRequestID){ return 0; }

private:
	CThostFtdcTraderSpi *m_pSpi;
};

CThostFtdcTraderApi *CThostFtdcTraderApi::CreateFtdcTraderApi(const char *pszFlowPath)
{
	return new MyClassCTP();
}