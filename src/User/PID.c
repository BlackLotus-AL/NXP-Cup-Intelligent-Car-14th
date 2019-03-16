#include "include.h"

void IncPID_Operation(PID_value *pid)
{
    //���㵱ǰ���
    pid->error = pid->set - pid->fdb;
    
    //�����м����AP,AI,AD;
    pid->AP = pid->error - pid->error_1;
    pid->AI = pid->error * pid->T;
    pid->AD = (pid->error - 2 * pid->error_1 + pid->error_2) / pid->T;
    
    //�������
    pid->output = pid->output_1 + pid->KP * pid->AP + pid->KI * pid->AI + pid->KD * pid->AD;
    
    //����޷�
    pid->output = Constrain_float(pid->output, pid->output_min, pid->output_max);
      
    //Ϊ�´μ������ 
    pid->output_1 = pid->output;
    pid->error_2 = pid->error_1;
    pid->error_1 = pid->error;
}

void PosPID_Operation(PID_value *pid)
{
    //���㵱ǰ���
    pid->error = pid->set - pid->fdb;
    
    //�����������ĺ�
    //pid->error_sum = pid->error_sum + pid->error;
    
    //�����м����AP,AI,AD;
    pid->AP = pid->error;
    pid->AI = pid->error_sum * pid->T;
    pid->AD = (pid->error - pid->error_1) / pid->T;
    
    //�������
    pid->output = pid->KP * pid->AP + pid->KI * pid->AI + pid->KD * pid->AD;
    
    //����޷�
    pid->output = Constrain_float(pid->output, pid->output_min, pid->output_max);
}

void PID_Init(PID_value *pid, float KP, float KI, float KD, float T, float min, float max)
{
    memset(pid, 0, sizeof(PID_value));
    pid->KP = KP;
    pid->KI = KI;
    pid->KD = KD;
    pid->T = T;
    pid->output_min = min;
    pid->output_max = max;
}
