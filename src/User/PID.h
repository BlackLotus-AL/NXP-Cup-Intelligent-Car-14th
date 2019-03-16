#ifndef _PID_H_
#define _PID_H_
#include "include.h"

typedef struct
{
    float set;          //ϵͳ�����������趨ֵ 
    float fdb;          //ϵͳ���������ķ���ֵ�����Ǵ�����ʵ�ʲ�����ֵ
    
    float KP;           //����ϵ��
    float KI;           //����ϵ��
    float KD;           //΢��ϵ��   
    float T;            //��ɢ��ϵͳ�Ĳ�������
      
    float AP;           //�������������������
    float AI;
    float AD;
      
    float error;        //��ǰƫ��e(k)
    float error_1;      //ǰһ����ƫ��
    float error_2;      //ǰǰһ����ƫ��
    float error_sum;    //����ƫ��ĺ�
       
    float output;       //pid�����������
    float output_1;     //pid��ǰһ�����
    float output_2;     //pid��ǰǰһ�����
    float output_max;   //�������
    float output_min;   //�������   
}PID_value;

void IncPID_Operation(PID_value *pid);
void PosPID_Operation(PID_value *pid);
void PID_Init(PID_value *pid, float KP, float KI, float KD, float T, float min, float max);

#endif