
#ifndef ZERG_SERVER_AUTO_CONNECT_H_
#define ZERG_SERVER_AUTO_CONNECT_H_



class Zerg_Server_Config;


/****************************************************************************************************
strcut SERVICES_ROUTE_INFO
****************************************************************************************************/
struct SERVICES_ROUTE_INFO
{
public:

    SERVICES_ROUTE_INFO();
    ~SERVICES_ROUTE_INFO();

public:
    //��·��SVCID
    SERVICES_ID                 main_route_info_;
    //��·��IP��ַ��Ϣ
    ZCE_Sockaddr_In             main_route_ip_;

    //����·���Ƿ���Ч
    bool                        back_route_valid_;
    //����·����Ϣ
    SERVICES_ID                 back_route_info_;
    //����·��IP��ַ��Ϣ
    ZCE_Sockaddr_In             back_route_ip_;

};

//
typedef std::vector< SERVICES_ROUTE_INFO > ArrayOfSvcInfoIPAddr;

/****************************************************************************************************
��services type�������������������Ϣ

��������ά���鱣��������������ӵ�services id��һ�������Ӧ��·��id�б���һ�������Ӧ����·��id�б�
����ĵ�һ�������Ա��Ӧservices type(��Ӧ��ϵ������map����)���ڶ��������ԱΪservices id
****************************************************************************************************/
//����services type������������Ӧ��ϵ��map
typedef std::map<unsigned short, unsigned int>  RouteType2Index;

//��·��id�б�
typedef std::vector<std::vector<unsigned int> > ListOfMainRouteId;

//����·��id�б�
typedef std::vector<std::vector<unsigned int> > ListOfBackRouteId;

/****************************************************************************************************
class Zerg_Auto_Connector
****************************************************************************************************/
class Zerg_Auto_Connector
{

protected:

    //
    ArrayOfSvcInfoIPAddr      ary_want_connect_;
    //
    size_t                    size_of_wantconnect_;

    //������
    ZCE_Socket_Connector      zerg_connector_;

private:
    //��·��id�б�
    ListOfMainRouteId           list_of_want_connect_main_id_;

    //����·��id�б�
    ListOfMainRouteId           list_of_want_connect_back_id_;

    //��������type��index��map
    RouteType2Index             want_connect_type_2_index_;

public:

    //���캯��
    Zerg_Auto_Connector();
    ~Zerg_Auto_Connector();

    //
    int get_config(const Zerg_Server_Config *config);

    // ���¼���������������
    int reload_cfg(const Zerg_Server_Config *config);

    //�������еķ�����
    void reconnect_allserver(size_t &szvalid, size_t &sz_succ, size_t &szfail);


    //���ӵ�����
    size_t numsvr_connect();

    //���������������õ����ݷ���������Ϣ
    int get_backupsvcinfo(const SERVICES_ID &main_svrinfo,
        bool &backroute_valid,
        SERVICES_ID &backroute_svrinfo);

    //����SVRINFO,����Ƿ����������ӵķ���.,
    int reconnect_server(const SERVICES_ID &reconnect_svrinfo);

    //����svr type��ȡserviceid���ж��idʱ�����ȡһ�� 
    int get_server(unsigned short svr_type, SERVICES_ID *svrinfo);
protected:

    //����SVRINFO+IP,����Ƿ����������ӵķ���.����������
    int connect_server_bysvcid(const SERVICES_ID &svrinfo, const ZCE_Sockaddr_In &inet_addr);

    //����svrinfo ����Ƿ��Ѿ�����
    bool is_connected(const SERVICES_ID &svrinfo);

private:
    //�����������ӷ�����Ϣ
    void add_auto_connect_info(const SERVICES_ID &main_svrinfo, const SERVICES_ID &back_svrinfo);

    // �ж��Ƿ�ǰ��������
    bool is_current_auto_connect(const SERVICES_ID &service, bool is_main_service);

};


#endif //_ZERG_SERVER_AUTO_CONNECT_H_

