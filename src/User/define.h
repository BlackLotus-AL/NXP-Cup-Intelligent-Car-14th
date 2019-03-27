#ifndef _DEFINE_H_
#define _DEFINE_H_
#include "include.h"

#define SERVO_PWM_FREQUENCY (100)       //100HZ��10ms��������50000
#define SPEED_PWM_FREQUENCY (10000)     //10000HZ��0.1ms��������500
#define PWM_CYCLE(x) (5000000 / x)
//Ƶ�ʣ�40M/(2^3)/500=10,000HZ,ÿ������Ϊ0.2us,����Ϊ100us

#define SPEED_PIT_CYCLE         (10.0)          //�ٶȿ��Ƶ�PIT���ڣ�ms
#define SPEED_CONTROL_CYCLE     (10 * 1000)     //�ٶȿ�������
#define SERVO_CONTROL_CYCLE     ( 5 * 1000)     //�����������
#define EMS_COLLECT_CYCLE       ( 1 * 1000)     //��Ųɼ�����
#define UART_SEND_CYCLE         (100 * 1000)    //������������

#define FORWARD (1)                     //ǰ��
#define STOP (0)                        //ֹͣ
#define RETREAT (-1)                    //����

#define EMS_CORRECT_MODE_IINT   (0)     //��ʼ������ź�У׼
#define EMS_CORRECT_MODE_H      (1)     //��������ź��м�У׼ģʽ
#define EMS_CORRECT_MODE_V      (2)     //��������ź�����У׼ģʽ
#define EMS_CORRECT_MODE_OFF    (3)     //�رյ���ź�У׼ģʽ

#define CLB (-2)                        //����ǳ�����
#define CLS (-1)                        //����ƫ��
#define CMZ (0)                         //��������
#define CRS (1)                         //����ƫ��
#define CRB (2)                         //����ǳ�����

#define TLB (-2)                        //������
#define TLS (-1)                        //����С��
#define TMZ (0)                         //ֱ��
#define TRS (1)                         //����С��
#define TRB (2)                         //���Ҽ���

#define CAR_LENGTH (200.0)                                                              //������mm
#define CAR_WIDTH (155.0)                                                               //�����mm
#define ENCODER_WHEEL_DIAMETER (18.1)                                                   //��������ֱ����mm
#define LINE_NUMBER (512.0)                                                             //512�߱�����
#define LENGTH_PER_PULSE (PI * ENCODER_WHEEL_DIAMETER / LINE_NUMBER)                    //ÿ�������Ӧ�ĳ��ȣ�mm
#define A2R(x) (PI * (x) / 180.0)                                                       //�Ƕ�ת������
#define R2A(x) (180.0 * (x) / PI)                                                       //����ת���Ƕ�
#define SPEED_PIT_CYCLE_PER_SECOND (1000.0 / SPEED_PIT_CYCLE)                           //ÿ������ٶȿ��ƵĴ���
#define ENCODER_2_TRUE(x) ((x) * (SPEED_PIT_CYCLE_PER_SECOND * LENGTH_PER_PULSE))       //����������ת����ʵ�ٶȣ�mm/s,setPulse=1��1.1cm/s
#define TRUE_2_ENCODER(x) ((x) / (SPEED_PIT_CYCLE_PER_SECOND * LENGTH_PER_PULSE))       //��ʵ�ٶ�ת������������
#define ADC_2_DISTANCE(x) (-0.00007 * pow((x), 3) + 0.0126 * pow((x), 2) - 1.0024 * pow((x), 1) + 41.316 * pow((x), 0)) //ADC����ת������ʵ�����߾��룬mm

#define SERVO_MIDDLE_DUTY (7050)        //�������ռ�ձ�
#define SERVO_MAX_TURN_DUTY (700)       //������ת��ռ�ձ�
#define SERVO_TURN_MOST_RIGHT (7750)    //���������ת
#define SERVO_TURN_MOST_LEFT (6350)     //���������ת

#define L2 (0)
#define L1 (1)
#define M0 (2)
#define R1 (3)
#define R2 (4)

#endif