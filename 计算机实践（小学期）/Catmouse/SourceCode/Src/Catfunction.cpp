
#include "Catfunction.h"






/*
Getanimalrange:��ȡ����ķ�Χ
������
animal:��Ӧ����ĵ�ַ
����ֵ��
recangle����������������ĸ��߽�ֵ
*/
Recangle Getanimalrange(Animal *animal)
{
	Recangle recangle;
	recangle.left = animal->GetSpritePositionX() - animal->GetSpriteWidth() / 2;
	recangle.right = animal->GetSpritePositionX() + animal->GetSpriteWidth() / 2;
	recangle.top = animal->GetSpritePositionY() - animal->GetSpriteHeight() / 2;
	recangle.botton = animal->GetSpritePositionY() + animal->GetSpriteHeight() / 2;
	return recangle;
}

Recangle Getanimalrange(CSprite *animal)
{
	Recangle recangle;
	recangle.left = animal->GetSpritePositionX() - animal->GetSpriteWidth() / 2;
	recangle.right = animal->GetSpritePositionX() + animal->GetSpriteWidth() / 2;
	recangle.top = animal->GetSpritePositionY() - animal->GetSpriteHeight() / 2;
	recangle.botton = animal->GetSpritePositionY() + animal->GetSpriteHeight() / 2;
	return recangle;
}

Recangle Getanimalrange(CStaticSprite *animal)
{
	Recangle recangle;
	recangle.left = animal->GetSpritePositionX() - animal->GetSpriteWidth() / 2;
	recangle.right = animal->GetSpritePositionX() + animal->GetSpriteWidth() / 2;
	recangle.top = animal->GetSpritePositionY() - animal->GetSpriteHeight() / 2;
	recangle.botton = animal->GetSpritePositionY() + animal->GetSpriteHeight() / 2;
	return recangle;
}
Recangle Getanimalrange(CEffect *animal)
{
	Recangle recangle;
	recangle.left = animal->GetSpritePositionX() - animal->GetSpriteWidth() / 2;
	recangle.right = animal->GetSpritePositionX() + animal->GetSpriteWidth() / 2;
	recangle.top = animal->GetSpritePositionY() - animal->GetSpriteHeight() / 2;
	recangle.botton = animal->GetSpritePositionY() + animal->GetSpriteHeight() / 2;
	return recangle;
}

/*
Ismouseinrange:�ж�ĳ�����Ƿ���ĳ����Χ��
������
MouseX:������
MouseY:������
range :ĳ��Χ
����ֵ��
true ���ڴ˷�Χ
false�����ڴ˷�Χ
*/
bool Ismouseinrange(float MouseX, float MouseY, Recangle range)
{
	if ((MouseX > range.left && MouseX < range.right) && (MouseY > range.top && MouseY < range.botton))
		return true;
	else
		return false;
}
/*
BottonView:�������ھ��鷶Χ�ڣ��Զ�������һ��ͼƬ���Ž�OnMouseMove�����ڼ���ʵ�ְ�ťЧ����
����:
sprite:����ĵ�ַ
mousex:������
mousey:������
zctp  :���겻�ڷ�Χ����ʾ��ͼƬ����
drtp  :�����ڷ�Χ����ʾ��ͼƬ����
*/
bool BottonView(CStaticSprite *sprite, float mousex, float mousey, const char* zctp, const char* drtp,bool config)
{
	if (Ismouseinrange(mousex, mousey, Getanimalrange(sprite)))//��������ڷ�Χ��
	{
		sprite->SetStaticSpriteImage(drtp, 0);//�����������Ϊ��drtp�������ͼƬ���ƣ�����ͼƬ
		return true;
	}
	else
	{
		if (config == false)
		{
			sprite->SetStaticSpriteImage(zctp, 0);//�����������Ϊ��zctp�������ͼƬ���ƣ�����ͼƬ
			return false;
		}
		else { sprite->SetStaticSpriteImage(drtp, 0); return true; }
	}
}
/*
CalculY:������ٶȶ�·�̸ı���
����:
v0:���ٶ�
t :˥��ʱ��
a :���ٶȴ�С
*/
float CalculY(float v0, float t,float a)
{
	return (v0 * t) - (a * t*t / 2);
}
/*
Calculhp:���㵱ǰѪ������
����:
totalhp:������Ѫ��
nowhp  :���鵱ǰѪ��
length :Ѫ�����ȣ���Ѫ����
*/
float Calculhp(float totalhp, float nowhp, float length)
{
	return (nowhp / totalhp)*length;
}
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
void AnimalJump(Animal *animal, float fDeltaTime,float heigh,float bottom,float v0,float a)
{
	if (animal->up == true && animal->down == false)//���鵱ǰΪ����״̬����������״̬
	{
		animal->jumptime += fDeltaTime;//������Ծ����ʱ��
		animal->SetSpritePositionY(animal->GetSpritePositionY() - CalculY(v0, animal->jumptime, a));//��̬���þ���λ��
		if (animal->GetSpritePositionY() < heigh)//������ﶥ��
		{
			animal->up = false;
			animal->down = true;
			animal->jumptime = 0;//������Ծ����ʱ���������״̬
		}
	}
	else if (animal->up == false && animal->down == true)//���鵱ǰΪ����״̬����������״̬
	{
		animal->jumptime += fDeltaTime;
		animal->SetSpritePositionY(animal->GetSpritePositionY() + CalculY(v0, animal->jumptime, a));
		if (animal->GetSpritePositionY() > bottom)
		{
			animal->SetSpritePositionY(bottom);
			animal->jumptime = 0;
			animal->down = false;//���鲻�ڿ���
		}
	}

}
/*
AnimalModeChange:���鲻ͬģʽִ�в�ͬ������1���ƶ�ģʽ��2������ģʽ��3����ֹģʽ��
������
animal:����ĵ�ַ
sta   :���龲ֹʱ���ŵ�ͼƬ����
run   :�����ƶ�ʱ���ŵ�ͼƬ����
att   :����Ĺ���Ч���ĵ�ַ
god   :�������Ĺ���ĵ�ַ
*/
void AnimalModeChange(Animal *animal, const char*sta, const char*run, CEffect *att,Animal *god,CEffect *jn1, CEffect *jn2, vector<Animal*>gg)
{
	if (animal->mode == 1)//�ƶ�ģʽ
	{
		if (strcmp(animal->animation, run) == 0)//������鵱ǰ����Ϊ�ƶ�����
		{
			if (animal->IsAnimateSpriteAnimationFinished())//������鵱ǰ�����������
			{
				animal->AnimateSpritePlayAnimation(run, true);//�����ƶ�����
			}
		}
		else//������鵱ǰ������Ϊ�ƶ�����
		{
			animal->AnimateSpritePlayAnimation(run, true);//�����ƶ�����
		}

	}
	else if (animal->mode == 2)//����ģʽ
	{
		char *tmpchar;//��ʱ�ַ���
		tmpchar = CSystem::MakeSpriteName("eff", 1);//��ʱ�ַ�������
		Animal *tmp = new Animal(tmpchar);//��ʱ�����ж���ָ��
		att->PlayEffect(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1), 0);//���Ź�����Ч
		tmp->CloneSprite("mouse_att_eff");//��¡������Ч����ʱ�����ж���ָ��
		tmp->SetSpritePosition(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1));//����ʱ�����ж���ָ���빥����Ч����ͬһ��λ��
		Recangle attrange;//��ʱ������Χ
		attrange.left = tmp->GetSpriteLinkPointPosX(3) - 6;
		attrange.right = tmp->GetSpriteLinkPointPosX(3) + 6;
		attrange.top = tmp->GetSpriteLinkPointPosY(3) - 6;
		attrange.botton = tmp->GetSpriteLinkPointPosY(3) + 6;
		if (Ismouseinrange(god->GetSpriteLinkPointPosX(3), god->GetSpriteLinkPointPosY(3), attrange))//�������ı������㣨���������ӵ㣩�ڹ�����Χ��
		{
			god->hp -= animal->att;//�����Ѫ
		}
		tmp->DeleteSprite();//ɾ����ʱ�����ж���ָ��
		delete tmp;

	}
	else if (animal->mode == 3)//��ֹģʽ
	{
		if (strcmp(animal->animation, sta) == 0)
		{

			if (animal->IsAnimateSpriteAnimationFinished())
			{
				animal->AnimateSpritePlayAnimation(sta, true);

			}
		}
		else
		{

			animal->AnimateSpritePlayAnimation(sta, true);
		}


	}
	else if (animal->mode == 4)//����1
	{
		if ((animal->mp - 100) > 0)
		{
			animal->mp -= 100;
			PlaySound("shasha.wav", NULL, SND_FILENAME | SND_ASYNC);
			char *tmpchar;//��ʱ�ַ���
			tmpchar = CSystem::MakeSpriteName("eff", 1);//��ʱ�ַ�������
			Animal *tmp = new Animal(tmpchar);//��ʱ�����ж���ָ��
			jn1->PlayEffect(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1), 0);//���Ź�����Ч
			tmp->CloneSprite("steam");//��¡������Ч����ʱ�����ж���ָ��
			tmp->SetSpritePosition(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1));//����ʱ�����ж���ָ���빥����Ч����ͬһ��λ��
			Recangle attrange;//��ʱ������Χ
			attrange.left = tmp->GetSpriteLinkPointPosX(3) - 30;
			attrange.right = tmp->GetSpriteLinkPointPosX(3) + 30;
			attrange.top = tmp->GetSpriteLinkPointPosY(3) - 30;
			attrange.botton = tmp->GetSpriteLinkPointPosY(3) + 30;
			for (int i = 0; i < gg.size(); i++)
			{
				if (Ismouseinrange(gg[i]->GetSpriteLinkPointPosX(3), gg[i]->GetSpriteLinkPointPosY(3), attrange))//�������ı������㣨���������ӵ㣩�ڹ�����Χ��
				{
					gg[i]->hp -= 400;//�����Ѫ
				}
			}
			tmp->DeleteSprite();//ɾ����ʱ�����ж���ָ��
			delete tmp;
			animal->mode = 3;
		}

	}
	else if (animal->mode == 5)//����2
	{
		if ((animal->mp - 300) > 0)
		{
			animal->mp -= 300;
			PlaySound("boom.wav", NULL, SND_FILENAME | SND_ASYNC);
			char *tmpchar;//��ʱ�ַ���
			tmpchar = CSystem::MakeSpriteName("eff", 1);//��ʱ�ַ�������
			Animal *tmp = new Animal(tmpchar);//��ʱ�����ж���ָ��
			jn2->PlayEffect(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1), 0);//���Ź�����Ч
			tmp->CloneSprite("miaosha");//��¡������Ч����ʱ�����ж���ָ��
			tmp->SetSpritePosition(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1));//����ʱ�����ж���ָ���빥����Ч����ͬһ��λ��
			Recangle attrange;//��ʱ������Χ
			attrange.left = tmp->GetSpriteLinkPointPosX(3) - 10;
			attrange.right = tmp->GetSpriteLinkPointPosX(3) + 10;
			attrange.top = tmp->GetSpriteLinkPointPosY(3) - 10;
			attrange.botton = tmp->GetSpriteLinkPointPosY(3) + 10;
			for (int i = 0; i < gg.size(); i++)
			{
				if (Ismouseinrange(gg[i]->GetSpriteLinkPointPosX(3), gg[i]->GetSpriteLinkPointPosY(3), attrange))//�������ı������㣨���������ӵ㣩�ڹ�����Χ��
				{
					gg[i]->hp -= 3000;//�����Ѫ
				}
			}
			tmp->DeleteSprite();//ɾ����ʱ�����ж���ָ��
			delete tmp;
			animal->mode = 3;
		}

	}
}

void AnimalModeChange(Animal *animal, const char*sta, const char*run, CEffect *att)
{
	if (animal->mode == 1)
	{
		if (strcmp(animal->animation, run) == 0)
		{
			if (animal->IsAnimateSpriteAnimationFinished())
			{
				animal->AnimateSpritePlayAnimation(run, true);
			}
		}
		else
		{
			animal->AnimateSpritePlayAnimation(run, true);
		}

	}
	else if (animal->mode == 2)
	{

		att->PlayEffect(animal->GetSpriteLinkPointPosX(1), animal->GetSpriteLinkPointPosY(1), 0);

	}
	else if (animal->mode == 3)
	{
		if (strcmp(animal->animation, sta) == 0)
		{

			if (animal->IsAnimateSpriteAnimationFinished())
			{
				animal->AnimateSpritePlayAnimation(sta, true);

			}
		}
		else
		{

			animal->AnimateSpritePlayAnimation(sta, true);
		}


	}
}

/*
AnimalChangdirect:����ı䳯��
����:
animal:����ĵ�ַ
*/
void AnimalChangdirect(Animal *animal)
{
	if (animal->changechaoxiang == "right")//������鳯��Ϊ��
	{
		animal->SetSpriteFlipX(true);//���ĳ���Ϊ��
		animal->nowchaoxiang = animal->changechaoxiang;//�����鵱ǰ��������Ϊ��
	}
	else
	{
		animal->SetSpriteFlipX(false);
	}
}
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
void AnimalColWorld(Animal *animal,CStaticSprite *map,const int iColSide,const char*name,const char*szName,float maprange,float animalmove)
{
	if (strcmp(szName, name) == 0)
	{
		if (animal->GetSpriteLinearVelocityX() != 0)
		{
			switch (iColSide)
			{
			case 0:
			{
				if (map->GetSpritePositionX() >= -maprange && map->GetSpritePositionX() <= maprange)
				{
					if (map->GetSpritePositionX() == maprange)
						map->SetSpritePositionX(map->GetSpritePositionX());
					else
						map->SetSpritePositionX(map->GetSpritePositionX() + 1);
					animal->SetSpritePositionX(CSystem::GetScreenLeft() + animalmove);
				}
				break;
			}
			case 1:
			{
				if (map->GetSpritePositionX() >= -maprange && map->GetSpritePositionX() <= maprange)
				{
					if (map->GetSpritePositionX() == -maprange)
						map->SetSpritePositionX(map->GetSpritePositionX());
					else
						map->SetSpritePositionX(map->GetSpritePositionX() - 1);
					animal->SetSpritePositionX(CSystem::GetScreenRight() - animalmove);
				}
				break;
			}
			case 2:
			{
				
				break;
			}
			}
		}
	}
}
/*
AutoColWorld:������ײ��ͼ���Զ��������Թ��
����:
animal    :����ĵ�ַ
map       :�����ĵ�ַ
iColSide  :��ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
name      :���������
szName    :��ײ���߽�ľ�������
*/
void AutoColWorld(Animal *animal, CStaticSprite *map, const int iColSide, const char*name, const char*szName)
{
	if (strcmp(szName, name) == 0)//���Ŀ�꾫��Ϊ��ײ����
	{
		if (animal->GetSpriteLinearVelocityX() != 0)//��������ٶȲ�Ϊ0
		{
			switch (iColSide)//�жϱ߽�
			{
			case 0://���
			{
				animal->changechaoxiang = "right";//�����Ϊ��
				AnimalChangdirect(animal);
				animal->SetSpriteLinearVelocity(10.f, 0);
				break;
			}
			case 1://�ұ�
			{
				animal->changechaoxiang = "left";//�����Ϊ��
				AnimalChangdirect(animal);
				animal->SetSpriteLinearVelocity(-10.f, 0);
				break;
			}
			case 2:
			{

				break;
			}
			}
		}
	}
}
/*
AnimalDrawline
������
animal :�����ָ��
totalhp:�������Ѫ��
length :Ѫ�����ܳ���
*/
void AnimalDrawline(Animal *animal, float totalhp,float length)
{
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2), animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, animal->hp, length), animal->GetSpriteLinkPointPosY(2), 4, 0, 191, 0, 0, 255);//��Ѫ��		
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2)+0.25, animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length), animal->GetSpriteLinkPointPosY(2)+0.25, 1, 0,0,0,10, 255);
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2) -0.25 ,animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length), animal->GetSpriteLinkPointPosY(2) -0.25 ,1, 0, 0,0,10, 255);
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2) -0.25 ,animal->GetSpriteLinkPointPosX(2), animal->GetSpriteLinkPointPosY(2) +0.25, 1, 0, 0,0,10, 255);
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length), animal->GetSpriteLinkPointPosY(2) -0.25 ,animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length), animal->GetSpriteLinkPointPosY(2) +0.25, 1, 0, 0,0,10, 255);
	CSystem::DrawLine(animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length)/2, animal->GetSpriteLinkPointPosY(2) - 0.25, animal->GetSpriteLinkPointPosX(2) + Calculhp(totalhp, totalhp, length)/2, animal->GetSpriteLinkPointPosY(2) + 0.25, 1, 0, 0,0,10, 255);
}



