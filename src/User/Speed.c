#include "include.h"

extern PID_value PID_left, PID_right;
extern int servoTurnDuty;
extern int setPulse, turnPulse, defaultPulse;
extern int getLeftPulse,  setLeftPulse,  leftDuty;
extern int getRightPulse, setRightPulse, rightDuty;
extern float getSpeed, turnAngle, turnRadius, turnSpeed;

extern float ADC_value[5];
extern int posStatus;
extern int goFlag;
extern KEY_value K1;

void Speed_Get()        //��ȡ���������ٶ�
{
    getLeftPulse  = FTM_AB_Get(FTM1);
    getLeftPulse  = Constrain_int_output(getLeftPulse , 0, -50000, 50000);
    
    getRightPulse = FTM_AB_Get(FTM2) * -1;
    getRightPulse = Constrain_int_output(getRightPulse, 0, -50000, 50000);
}

void Speed_Set()
{
    PID_left.set = (float)setLeftPulse;
    PID_left.fdb = (float)getLeftPulse;
    PID_left.output_1 = (float)leftDuty;
    IncPID_Operation(&PID_left);        
    leftDuty = (int)PID_left.output;      
            
    if(leftDuty > 0)
    {
        FTM_PWM_Duty(FTM0, FTM_CH0, 0);
        FTM_PWM_Duty(FTM0, FTM_CH1, leftDuty);
    }
    else
    {
        FTM_PWM_Duty(FTM0, FTM_CH0, -leftDuty);
        FTM_PWM_Duty(FTM0, FTM_CH1, 0);
    }        

   
    PID_right.set = (float)setRightPulse;     
    PID_right.fdb = (float)getRightPulse;
    PID_right.output_1 = (float)rightDuty;
    IncPID_Operation(&PID_right);
    rightDuty = (int)PID_right.output;
            
    if(rightDuty > 0)
    {
        FTM_PWM_Duty(FTM0, FTM_CH2, rightDuty);
        FTM_PWM_Duty(FTM0, FTM_CH3, 0);
    }
    else
    {
        FTM_PWM_Duty(FTM0, FTM_CH2, 0);
        FTM_PWM_Duty(FTM0, FTM_CH3, -rightDuty);
    }        
}

void Speed_Turn()
{
    getSpeed = ENCODER_2_TRUE(getLeftPulse + getRightPulse) / 2.0;
    
    turnAngle = 0.0542 * fabs((float)servoTurnDuty) + 0.1667;                   //���ݶ��ת��ռ�ձȼ���ת��Ƕ�
    turnRadius = (CAR_LENGTH / sin(A2R(turnAngle))) - (CAR_WIDTH / 2.0);        //����ת��Ƕȼ���ת��뾶
    turnSpeed = (getSpeed * CAR_WIDTH) / (2.0 * turnRadius);                    //���ݵ�ǰ�ٶȼ���ת�����
    turnSpeed = turnSpeed * 0.8;
    turnPulse = (int)TRUE_2_ENCODER(turnSpeed);                                 //����ת����ټ���ת�������
    
    if(servoTurnDuty > 0)
    {
        turnPulse = -turnPulse;
    }
    setLeftPulse = setPulse + turnPulse;
    setRightPulse = setPulse - turnPulse;

}

void Speed_Test()
{
    if(!KEY_Read(KEY1))           //���KEY1����
    {
        if(leftDuty < 400 && rightDuty < 400 )
        {
            leftDuty += 10;
            rightDuty += 10;                               
        }
    }
    else if(!KEY_Read(KEY2))     //���KEY2����
    {
        if(leftDuty > 0 && rightDuty > 0)
        {
            leftDuty -= 10;
            rightDuty -= 10;
        }
    }
    else if(!KEY_Read(KEY0))     //���KEY0����
    {
        leftDuty = 250;
        rightDuty = 250;                       
    }  
}

void Speed_Stop()
{
    if(ADC_value[M0] < -150)
        
    {   
        goFlag = 0;
    }
    
    if(goFlag)
    {    
        setPulse = defaultPulse;
    }
    else
    {
        setPulse = 0;
        setLeftPulse = 0;
        setRightPulse = 0;
    }
}
