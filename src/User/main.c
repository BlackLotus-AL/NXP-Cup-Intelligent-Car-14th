/****************************************************************************************************
��ƽ    ̨������K66FX���ܳ�VCĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@aliyun.com
������汾��V1.0
�������¡�2016��08��24��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.3
��Target  ��K66FX1M0VLQ18
��Crystal �� 50.000Mhz
��busclock�� 40.000MHz
��pllclock��200.000MHz
=============================================================
�ӿڶ��壺
-------------------------------------------------------------
LED����GPIO
LED1--PTA17
LED2--PTC0
LED3--PTD15
LED4--PTE26
-------------------------------------------------------------
OLED����GPIO
DC  --PTC13
RST --PTC14
MISO--PTC15
CLK --PTC16
-------------------------------------------------------------
����       K66��Ƭ���ӿ�     ��ע
GND        GND
TX         PTE24             ��������RX
RX         PTE25             ��������TX
-------------------------------------------------------------
��������ģ��ͨ��        �˿�  
FTM1_QDPHA              PTA12       
FTM1_QDPHB              PTA13  
FTM2_QDPHA              PTB18       
FTM2_QDPHB              PTB19
-------------------------------------------------------------
PWM�˿ڵĶ���           �˿� 
#define FTM3_CH6        PTC10       // PTE11��PTC10
#define FTM3_CH7        PTC11       // PTE12��PTC11

#define FTM0_CH0        PTC1        // PTC1��PTA3
#define FTM0_CH1        PTC2        // PTC2��PTA4
#define FTM0_CH2        PTC3        // PTC3��PTA5
#define FTM0_CH3        PTC4        // PTC4��PTA6
-------------------------------------------------------------
//ADCģ��ͨ��           �˿� 
ADC1_SE10 = 10          PTB4
ADC1_SE11 = 11          PTB5
ADC1_SE12 = 12          PTB6
ADC1_SE13 = 13          PTB7
ADC1_SE14 = 14          PTB10
=============================================================
������ʷ��
------------------------------------------------------------------------------------------------------
�޸���ʷ
******************************************************************************************************/

#include "include.h" 
PID_value PID_left, PID_right, PID_servo;                //����PID�����ṹ�壬����PID�����ṹ�壬�ŷ���PID�����ṹ��

float ADC_value[5], ADC_min[5], ADC_max[5];             //��ж������飬�����Сֵ���飬������ֵ����
float posError = 0, posError_H = 0, posError_V = 0;     //λ��ƫ�ˮƽ���λ��ƫ���ֱ���λ��ƫ�� 
int posStatus = 0;                                      //λ��״̬

int servoDuty = SERVO_MIDDLE_DUTY, servoTurnDuty = 0;   //���ռ�ձȣ����ת��ռ�ձ�
int setPulse = 0, turnPulse = 0, defaultPulse = 80;     //�ٶ��趨ֵ��������������Ŀ������������ת�������趨ֵ��Ĭ���ٶ�����
int getLeftPulse  = 0, setLeftPulse  = 0, leftDuty  = 0;//��ȡ�������壬�����������壬��������ռ�ձ�          
int getRightPulse = 0, setRightPulse = 0, rightDuty = 0;//��ȡ�ҵ�����壬�����ҵ�����壬�����ҵ��ռ�ձ�          

float getSpeed = 0, turnAngle = 0, turnRadius = 0, turnSpeed = 0;//��ȡ�ٶȣ�ת��Ƕȣ�ת��뾶��ת����ٶȣ�

char sendStr[250] = {0}, receiveStr[20] = {0};          //�����ַ����������ַ���
int sendArr[50] = {0};                                  //��������
int strI = 0;                                           //�ַ�����ǰλ��

KEY_value K1, K2;                                       //����K1,K2�ṹ��
int goFlag = 0;                                         //������־

//������
void main(void)
{
    DisableInterrupts;                  //�ر��ж�
    Init_All();                         //��ʼ������
    PID_Init(&PID_left , 3.0, 210.0, 0.0,  0.01, -200, 400);                                //��ʼ��PID����
    PID_Init(&PID_right, 3.0, 210.0, 0.0,  0.01, -200, 400);                                //��ʼ��PID����
    PID_Init(&PID_servo, 0.5,   0.0, 0.2, 0.005, -SERVO_MAX_TURN_DUTY, SERVO_MAX_TURN_DUTY);//��ʼ��PID����
    EnableInterrupts;                   //�����ж�
    
    while(1)
    {       
        EMS_Correct_KEY_Operation(&K1); //���У׼��������
        GO_KEY_Operation(&K2);          //������������

    }
}