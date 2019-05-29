#include "include.h"

extern PID_value PID_servo;
extern int servoDuty, servoTurnDuty;
extern int posStatus;
extern float posError;

extern int goFlag;

/**
* @������: Servo_Set
* @��  ��: �������
* @��  ��: ��
* @��  ��: ��
* @��  ��: ��
* @ע  �⣺��
*/
void Servo_Set()
{ 
    //PID����
    PID_servo.set = 0.0;
    PID_servo.fdb = 0.0001 * pow(posError, 3) + 0.25 * posError;	
    PosPID_Operation(&PID_servo);
    //���ö��ռ�ձ�
    servoTurnDuty = (int)PID_servo.output;
    servoDuty = SERVO_MIDDLE_DUTY - servoTurnDuty;
    
    //�������ƫ�����߽�Զ��ʹ�����ת��Ƕ�
    if(posStatus == CAR_VERY_LEFT)
    {
        servoDuty = SERVO_TURN_MOST_RIGHT;
    }
    else if(posStatus == CAR_VERY_RIGHT)
    {
        servoDuty = SERVO_TURN_MOST_LEFT;
    }
    
    //δ����ʱ�������
    if(!goFlag)
    {
        servoDuty = SERVO_MIDDLE_DUTY;
    }
    FTM_PWM_Duty(FTM3, FTM_CH6, servoDuty);
}

/**
* @������: Servo_Test_Key
* @��  ��: �����������
* @��  ��: ��
* @��  ��: ��
* @��  ��: ��
* @ע  �⣺��
*/
void Servo_Test_Key()
{
    //���У׼����
    if(!KEY_Read(KEY1))           //���KEY1���£���ת
    {
        if(servoDuty < 10000) servoDuty += 2;       
    }
    else if(!KEY_Read(KEY2))     //���KEY2���£���ת
    {
        if(servoDuty > 4000)  servoDuty -= 2;       
    }
    else if(!KEY_Read(KEY0))     //���KEY0���£�����
    {
        servoDuty = SERVO_MIDDLE_DUTY;       
    }
    FTM_PWM_Duty(FTM3, FTM_CH6, servoDuty);
}

/**
* @������: Servo_Test_Key
* @��  ��: �����������
* @��  ��: ��
* @��  ��: ��
* @��  ��: ��
* @ע  �⣺��
*/
void Servo_Test_UART()
{
    servoDuty = Constrain_int(servoDuty, SERVO_TURN_MOST_LEFT, SERVO_TURN_MOST_RIGHT);
    FTM_PWM_Duty(FTM3, FTM_CH6, servoDuty);
}
