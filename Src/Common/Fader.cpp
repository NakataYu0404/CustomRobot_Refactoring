#include <DxLib.h>
#include <time.h>
#include <random>
#include "../Application.h"
#include "Fader.h"

Fader::STATE Fader::GetState(void) const
{
	return state_;
}

bool Fader::IsEnd(void) const
{
	return isEnd_;
}

void Fader::SetFade(STATE state)
{
	state_ = state;
	if (state_ != STATE::NONE)
	{
		isPreEnd_ = false;
		isEnd_ = false;
	}
}

void Fader::Init(void)
{
	state_ = STATE::NONE;
	alpha_ = 0;
	isPreEnd_ = true;
	isEnd_ = true;

	imgSousakiH_ = LoadGraph("./Data/Image/sousakihon.png");
	imgSousakoH_ = LoadGraph("./Data/Image/sousakougeki.png");

	rand_ = 0;
	random_ = false;
}

void Fader::Update(void)
{

	if (isEnd_)
	{
		return;
	}

	switch (state_)
	{
	case STATE::NONE:
		return;
	case STATE::FADE_OUT:
		if (random_ == false)
		{
			srand((unsigned int)time(NULL));
			rand_ = rand() % 2;
			random_ = true;
		}
		alpha_ += SPEED_ALPHA;
		if (alpha_ > 510)
		{
			//  フェード終了
			alpha_ = 510;
			if (isPreEnd_)
			{
				//  1フレーム後(Draw後)に終了とする
				isEnd_ = true;
				random_ = false;
			}
			isPreEnd_ = true;
		}

		break;

	case STATE::FADE_IN:
		alpha_ -= SPEED_ALPHA;
		if (alpha_ < 0)
		{
			//  フェード終了
			alpha_ = 0;
			if (isPreEnd_)
			{
				//  1フレーム後(Draw後)に終了とする
				isEnd_ = true;
			}
			isPreEnd_ = true;
		}
		break;

	default:
		return;
	}

}

void Fader::Draw(void)
{

	switch (state_)
	{
	case STATE::NONE:
		return;
	case STATE::FADE_OUT:
	case STATE::FADE_IN:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha_/2);
		if (rand_ == 0)
		{
			DrawGraph(0, 0, imgSousakiH_, false);

		}
		else
		{
			DrawGraph(0, 0, imgSousakoH_, false);

		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		break;
	}

}

