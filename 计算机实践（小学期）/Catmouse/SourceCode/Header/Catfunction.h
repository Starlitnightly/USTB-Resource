#ifndef _CATFUNCTION_H_
#define _CATFUNCTION_H_

#include "CommonClass.h"
#include "LessonX.h"

struct Recangle//��Χ����
{
	float left;
	float right;
	float top;
	float botton;

};





/*
Ismouseinrange���ж�����Ƿ���ĳ��Χ��
���� MouseX����������
���� MouseY�����������
���� range��Ҫ�жϵķ�Χ
*/
bool Ismouseinrange(float MouseX, float MouseY, Recangle range);
/*
CalculY:������ٶȶ�·�̸ı���
����:
v0:���ٶ�
t :˥��ʱ��
a :���ٶȴ�С
*/
float CalculY(float v0, float t,float a);
/*
Calculhp:���㵱ǰѪ������
����:
totalhp:������Ѫ��
nowhp  :���鵱ǰѪ��
length :Ѫ�����ȣ���Ѫ����
*/
float Calculhp(float totalhp, float nowhp, float length);
/*
AnimalJump:������Ծ���Ž�gamerun�����ڣ�
����:
animal    :������Ծ�����ľ���ĵ�ַ
fDeltaTime:����ˢ����Ļ��ʱ���
heigh     :��Ծ�����λ��
bottom    :�����λ��
v0        :���ٶ�
a         :���ٶ�
*/
void AnimalJump(Animal *animal, float fDeltaTime, float heigh, float bottom, float v0, float a);
/*
BottonView:�������ھ��鷶Χ�ڣ��Զ�������һ��ͼƬ���Ž�OnMouseMove�����ڼ���ʵ�ְ�ťЧ����
����:
sprite:����ĵ�ַ
mousex:������
mousey:������
zctp  :���겻�ڷ�Χ����ʾ��ͼƬ����
drtp  :�����ڷ�Χ����ʾ��ͼƬ����
*/
bool BottonView(CStaticSprite *sprite, float mousex, float mousey, const char* zctp, const char* drtp, bool config=false);
/*
AnimalModeChange:���鲻ͬģʽִ�в�ͬ������1���ƶ�ģʽ��2������ģʽ��3����ֹģʽ�����й�״̬��
������
animal:����ĵ�ַ
sta   :���龲ֹʱ���ŵ�ͼƬ����
run   :�����ƶ�ʱ���ŵ�ͼƬ����
att   :����Ĺ���Ч���ĵ�ַ
god   :�������Ĺ���ĵ�ַ
*/
void AnimalModeChange(Animal *animal, const char*sta, const char*run, CEffect *att, Animal *god, CEffect *jn1, CEffect *jn2, vector<Animal*>gg);
/*
AnimalModeChange:���鲻ͬģʽִ�в�ͬ������1���ƶ�ģʽ��2������ģʽ��3����ֹģʽ�����޹�״̬��
������
animal:����ĵ�ַ
sta   :���龲ֹʱ���ŵ�ͼƬ����
run   :�����ƶ�ʱ���ŵ�ͼƬ����
att   :����Ĺ���Ч���ĵ�ַ
*/
void AnimalModeChange(Animal *animal, const char*sta, const char*run, CEffect *att);
/*
AnimalChangdirect:����ı䳯��
����:
animal:����ĵ�ַ
*/
void AnimalChangdirect(Animal *animal);
/*
AnimalColWorld:������ײ��ͼ���������
������
animal    :����ĵ�ַ
map       :�����ĵ�ַ
iColSide  :��ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
name      :���������
szName    :��ײ���߽�ľ�������
maprange  :��ͼ��С
animalmove:������ײ��ͼ��߽��Զ����˵�ֵ
*/
void AnimalColWorld(Animal *animal, CStaticSprite *map, const int iColSide, const char*name, const char*szName, float maprange, float animalmove);
/*
AutoColWorld:������ײ��ͼ���Զ��������Թ��
����:
animal    :����ĵ�ַ
map       :�����ĵ�ַ
iColSide  :��ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
name      :���������
szName    :��ײ���߽�ľ�������
*/
void AutoColWorld(Animal *animal, CStaticSprite *map, const int iColSide, const char*name, const char*szName);

Recangle Getanimalrange(Animal *animal);
Recangle Getanimalrange(CSprite *animal);
Recangle Getanimalrange(CStaticSprite *animal);
Recangle Getanimalrange(CEffect *animal);
/*
AnimalDrawline
������
animal :�����ָ��
totalhp:�������Ѫ��
length :Ѫ�����ܳ���
*/
void AnimalDrawline(Animal *animal, float totalhp, float length);

#endif // _FUNCTION_H_