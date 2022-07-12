/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>
#include <string>
#include <iostream>
#include<vector>


using namespace std;

class Animal :public  CAnimateSprite
{
public:

	int hp;	//Ѫ��
	int mp;	//����
	int att;//������
	int defend;//������
	float jumptime;//��Ծ����ʱ��
	bool up;//����״̬
	bool down;//����״̬

	string nowchaoxiang;//���鵱ǰ����
	string changechaoxiang;//����Ҫ�ı�ĳ���
	const char *animation;//���鵱ǰ������ʾ�����ŵĶ���

	int mode;//1,run 2,att 3,sta
	Animal(const char*name);//���캯��


};

class	CGameMain
{
private:
	int				m_iGameState;				// ��Ϸ״̬��0���������ߵȴ���ʼ��1����ʼ����2����Ϸ������

	int Now;//��ǰ�ؿ�
	CStaticSprite *map;//���屳����ͼ��ָ��
	CTextSprite *debug;//�������ı���ʾ
	double *score;

	vector<Animal*> human;
	int nowhuman;
	const char*nowhumansta;
	const char*nowhumanrun;
	CEffect *nowhumanatt;
	Animal *cat;//��������-è��ָ��
	Animal *mouse;//����ָ��
	CEffect *cat_att_eff;//è�Ĺ���Ч��
	CEffect *mouse_att_eff;//���Ĺ���Ч��
	CEffect *jn1;
	CEffect *jn2;


	Animal *sdog;//С��1-С��ָ��
	Animal *boss;//boss-bossָ��
	vector<Animal*> smalldog;//С������
	float leftovertime;//С���Զ�����ʣ��ʱ��
	float lefttime;
	float totaltime;
	float tmptime;
	int produce;//С����������


	CSprite *mainmap;//�������ͼ
	CStaticSprite *first;//��һ�ذ�ť
	CStaticSprite *second;//�ڶ��ذ�ť
	CStaticSprite *third;//�����ذ�ť
	CStaticSprite *xzrw;
	CStaticSprite *xzrwjm;
	CStaticSprite *help;
	CStaticSprite *helpbb;
	CStaticSprite *helpx;
	CStaticSprite *phb;
	CStaticSprite *phbbb;
	CStaticSprite *phbx;
	CSprite *mainmenu;//���˵�
	CStaticSprite *menu;//�˵�����
	CStaticSprite *menu1;//�ص���Ϸ
	CStaticSprite *menu2;//�˳���Ϸ
	CStaticSprite *menu3;//�ص�������


	CStaticSprite *button_cj;//�ɾͰ�ť
	CStaticSprite *cj1;//�ɾͽ���ָ��
	CStaticSprite *cjx;//�رճɾͽ���~
	CStaticSprite *cjd1;//�ɾ͵�1
	CStaticSprite *cjd2;//�ɾ͵�2
	CStaticSprite *cjd3;//�ɾ͵�3
	CStaticSprite *cjd4;//�ɾ͵�4
	CStaticSprite *cjd5;//�ɾ͵�5
	CStaticSprite *cjd6;//�ɾ͵�6
	CStaticSprite *cjd7;//�ɾ͵�7
	CStaticSprite *cj;
	CStaticSprite *button_bb;//������ť
	CStaticSprite *bb;//��������
	CStaticSprite *bb1;//�󱳰�
	CStaticSprite *bb2;//�ұ���
	CStaticSprite *bbx;//�رձ�������
	bool bagopen;

	CStaticSprite *grey;//��ɫ����
	CStaticSprite *gameover;//��Ϸ��������
	CStaticSprite *gamenext;//������һ��
	CStaticSprite *gameback;//����������
	CStaticSprite *tongguan;//ͨ������
	CStaticSprite *guanqia;
	CStaticSprite *humant;
	CStaticSprite *sshp;
	CStaticSprite *ssmp;


	const char*bossname;//boss�����ƣ���Ӧfuncode�Ľӿڣ�
	const char*smallbossname;//С�ֵ�����
	CStaticSprite *bossx;
	CStaticSprite *bosst;
	int bosstj;


	CTextSprite *thp;
	CTextSprite *tmp;
	CTextSprite *tatt;
	CTextSprite *tdef;
	CTextSprite *sshpt;
	CTextSprite *ssmpt;

	CTextSprite *totalt;
	CTextSprite *time1;
	CTextSprite *time2;
	CTextSprite *time3;
	CTextSprite *time4;
	CTextSprite *time5;



	bool config1;
	bool config2;
	bool config3;
	bool config4;
	bool config5;
	bool config6;
	bool config7;

public:
	
	
	CGameMain();    //���캯��
	~CGameMain();   //��������     
	int				GetGameState()											{ return m_iGameState; }
	void			SetGameState( const int iState )				{ m_iGameState	=	iState; }
	void			GameMainLoop( float	fDeltaTime );	
	void			GameInit();
	void			GameRun( float fDeltaTime );
	void			GameEnd();
	void 			OnMouseMove( const float fMouseX, const float fMouseY );
	void 			OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );
	void 			OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
	void 			OnKeyUp( const int iKey );
	void 			OnSpriteColSprite( const char *szSrcName, const char *szTarName );
	void 			OnSpriteColWorldLimit( const char *szName, const int iColSide );
	void ViewScore(double *score);
/*
	ProduceDog:����С��	

	������
	i     :���
	sprite:�����õĹ�������
	x,y   :����λ��
*/
	
	void ProduceDog(int i,const char*sprite,float x,float y);
/*
ProduceBoss:����boss
������
i     :���
sprite:�����õĹ�������
x,y   :����λ��
����ֵ:
tmpDog:���ɵ�boss��Ӧ�ĵ�ַ
*/
	Animal* ProduceBoss(int i, const char*sprite, float x, float y);
	/*
	Init:��ʼ���ؿ�
	������
	now  :��ǰ�ؿ�
	mname:��ͼ����
	bname:boss����
	sname:С������
	*/
	void Init(int now, const char*mname, const char*bname, const char*sname);

	void SetAnimalbase(int hp, int mp, int att, int def);
};

/////////////////////////////////////////////////////////////////////////////////
// 
extern CGameMain	g_GameMain;

#endif // _LESSON_X_H_