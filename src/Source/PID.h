#ifndef __PID_H__
#define __PID_H__

//PID������Ҫ�Ĳ���
typedef struct PID
{
    u16 set;          //ϵͳ�����������趨ֵ 
    u16 fdb;          //ϵͳ���������ķ���ֵ�����Ǵ�����ʵ�ʲ�����ֵ
    
    float KP;           //����ϵ��
    float KI;           //����ϵ��
    float KD;           //΢��ϵ��   
    float T;            //��ɢ��ϵͳ�Ĳ������� 
      
    float AP;           //�������������������
    float AI;
    float AD;
      
    u16 error;        //��ǰƫ��e(k)
    u16 error_1;      //ǰһ����ƫ��
    u16 error_2;      //ǰǰһ����ƫ��
      
    u16 output;       //pid�����������
    u16 output_1;     //pid��ǰһ�����
    u16 output_max;   //�������
    u16 output_min;   //�������   
}PID_value;

void PID_Operation(PID_value *pid);
u16 Constrain_u16(u16 input, u16 low, u16 high);

#endif