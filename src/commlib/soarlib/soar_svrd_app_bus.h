
#ifndef SOARING_LIB_SVRD_APP_NONCTRL_H_
#define SOARING_LIB_SVRD_APP_NONCTRL_H_

#include "soar_svrd_app_base.h"

class Zerg_App_Frame;
//������������APP FRAME
class Comm_SvrdApp_BUS : public Comm_Svrd_Appliction
{
protected:

    //���ܵ�������
    Zerg_App_Frame          *nonctrl_recv_buffer_;

protected:
    //
    Comm_SvrdApp_BUS();
    virtual ~Comm_SvrdApp_BUS();

public:

    //���д���,
    virtual int on_run();

protected:

    //�������յ���Frame,
    virtual int popfront_recvpipe(size_t max_prc, size_t &proc_frame);

    //�����յ���APPFRAME����ʹ��const��ԭ������ΪΪ�˼ӿ��ٶȣ��ܶ�ط���ֱ�ӽ�recv_frame�޸�
    virtual int process_recv_appframe(Zerg_App_Frame *recv_frame) = 0;


};

#endif //#ifndef SOARING_LIB_SVRD_APP_NONCTRL_H_
