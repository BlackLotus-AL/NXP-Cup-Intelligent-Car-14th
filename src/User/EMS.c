#include "include.h"

extern float ADC_value[5], ADC_min[5], ADC_max[5];
extern float posError, posError_H, posError_V;
extern int posStatus;
extern KEY_value K1;

/**
* @������: EMS_Get
* @��  ��: ��ȡ�������
* @��  ��: ��
* @��  ��: ��
* @��  ��: ��
* @ע  �⣺ADCͨ�����б�ŵĶ�Ӧ������Լ���������
*/
void EMS_Get()
{
    //����źŲɼ�
    ADC_value[L2] = (float)ADC_Ave(ADC_1, ADC1_SE11, ADC_12bit, 10);    
    ADC_value[M0] = (float)ADC_Ave(ADC_1, ADC1_SE12, ADC_12bit, 10);  
    ADC_value[R2] = (float)ADC_Ave(ADC_1, ADC1_SE14, ADC_12bit, 10);   
    //ADC_value[L1] = (float)ADC_Ave(ADC_1, ADC1_SE13, ADC_12bit, 10);  
    //ADC_value[R1] = (float)ADC_Ave(ADC_1, ADC1_SE10, ADC_12bit, 10);
    

    if(K1.flag == EMS_CORRECT_MODE_OFF)    //������У׼ģʽ�ر�
    {
        //��һ������
        ADC_value[L2] = 1000.0 * (ADC_value[L2] - ADC_min[L2]) / (ADC_max[L2] - ADC_min[L2]);
        ADC_value[M0] = 1000.0 * (ADC_value[M0] - ADC_min[M0]) / (ADC_max[M0] - ADC_min[M0]);
        ADC_value[R2] = 1000.0 * (ADC_value[R2] - ADC_min[R2]) / (ADC_max[R2] - ADC_min[R2]);
        //ADC_value[L1] = 1000.0 * (ADC_value[L1] - ADC_min[L1]) / (ADC_max[L1] - ADC_min[L1]);
        //ADC_value[R1] = 1000.0 * (ADC_value[R1] - ADC_min[R1]) / (ADC_max[R1] - ADC_min[R1]);
        
        //�޷�
        Constrain_float(ADC_value[L2], 1.0, 1000.0);
        Constrain_float(ADC_value[M0], 1.0, 1000.0);
        Constrain_float(ADC_value[L2], 1.0, 1000.0);
        //Constrain_float(ADC_value[L1], 1.0, 1000.0); 
        //Constrain_float(ADC_value[R1], 1.0, 1000.0);        
    }
}

/**
* @������: EMS_Correct
* @��  ��: ��ȡ��������Сֵ����֮��Ĺ�һ������
* @��  ��: ��
* @��  ��: ��
* @��  ��: ��
* @ע  �⣺�ȳ�ʼ���ٶ�ȡ�����Сֵ
*/
void EMS_Correct()
{
    switch(K1.flag)
    {
        //��ʼ����������Сֵ
        case (EMS_CORRECT_MODE_IINT):
            ADC_max[L2] = 0,    ADC_max[L1] = 0,    ADC_max[M0] = 0,    ADC_max[R1] = 0,    ADC_max[R2] = 0;   
            ADC_min[L2] = 4095, ADC_min[L1] = 4095, ADC_min[M0] = 4095, ADC_min[R1] = 4095, ADC_min[R2] = 4095; 
            break;
         
        //��ȡˮƽ��е������Сֵ
        case (EMS_CORRECT_MODE_H):
            if(ADC_value[M0] > ADC_max[M0])     ADC_max[M0] = ADC_value[M0];
            if(ADC_value[M0] < ADC_min[M0])     ADC_min[M0] = ADC_value[M0];
            
            if(ADC_value[L2] > ADC_max[L2])     ADC_max[L2] = ADC_value[L2];
            if(ADC_value[L2] < ADC_min[L2])     ADC_min[L2] = ADC_value[L2];
            
            if(ADC_value[R2] > ADC_max[R2])     ADC_max[R2] = ADC_value[R2];
            if(ADC_value[R2] < ADC_min[R2])     ADC_min[R2] = ADC_value[R2];
            break;   
            
        /*
        case (EMS_CORRECT_MODE_V):
            if(ADC_value[L1] > ADC_max[L1])     ADC_max[L1] = ADC_value[L1];
            if(ADC_value[L1] < ADC_min[L1])     ADC_min[L1] = ADC_value[L1];
            
            if(ADC_value[R1] > ADC_max[R1])     ADC_max[R1] = ADC_value[R1];
            if(ADC_value[R1] < ADC_min[R1])     ADC_min[R1] = ADC_value[R1];
            break;
        */
    }
}  


/**
* @������: Pos_Get
* @��  ��: ���ݵ�������ж�λ��״̬
* @��  ��: ��
* @��  ��: ��
* @��  ��: ��
* @ע  �⣺��
*/
void Pos_Get()
{
    //�м���ֵ���
    if(ADC_value[M0] > ADC_value[L2] && ADC_value[M0] > ADC_value[R2])
    {
        posStatus = CAR_MIDDLE;
    }
    //�������ֵ���
    else if(ADC_value[L2] > ADC_value[M0] && ADC_value[L2] > ADC_value[R2])
    {
        posStatus = CAR_RIGHT;
        if(ADC_value[M0] < 400.0)
        {
             posStatus = CAR_VERY_RIGHT;
        }       
    }
    //���Ҳ���ֵ���
    else if(ADC_value[R2] > ADC_value[M0] && ADC_value[R2] > ADC_value[L2])
    {
        posStatus = CAR_LEFT;
        if(ADC_value[M0] < 400.0)
        {
             posStatus = CAR_VERY_LEFT;
        }  
    }
    
    //��Ⱥ͵ó�ˮƽ���λ��ƫ��
    posError_H = ((ADC_value[M0] - ADC_value[L2]) /(ADC_value[M0] + ADC_value[L2])) - ((ADC_value[M0] - ADC_value[R2]) / (ADC_value[M0] + ADC_value[R2]));  
    posError_H = posError_H * 100.0;
    
    //��Ⱥ͵ó���ֱ���λ��ƫ��
    //posError_V = ((ADC_value[M0] - ADC_value[L1]) /(ADC_value[M0] + ADC_value[L1])) - ((ADC_value[M0] - ADC_value[R1]) / (ADC_value[M0] + ADC_value[R1]));     
    //posError_V = posError_V * 100.0;
    
    //����λ��ƫ��
    posError = posError_H;
}
