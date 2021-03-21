#define _CRT_SECURE_NO_WARNINGS
#include<bangtal.h>
#include<stdio.h>

SceneID scene1;
ObjectID knight_p[15], blank16, start, end, restart;
TimerID timer1;
Second timer_second;
bool started = false;
int X[4] = { 342, 482, 622, 762 };
int Y[4] = { 482, 332, 182, 32 };
int blank[2] = { X[3], Y[3] };
int knight_X[15] = { X[3], X[2], X[3], X[3], X[1], X[0], X[0], X[1], X[1], X[2], X[2], X[1], X[0], X[2], X[0] };
int knight_Y[15] = { Y[2], Y[3], Y[1], Y[0], Y[3], Y[3], Y[1], Y[1], Y[0], Y[0], Y[1], Y[2], Y[2], Y[2], Y[0] };


ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown)
{
	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);
	if (shown)
		showObject(object);
	return object;
}

void timerCallback(TimerID timer)
{
	if (timer == timer1)
	{
		showMessage("실패");
		started = false;
	}
}

void startGame()
{
	startTimer(timer1);
	hideObject(start);
	started = true;
}

void resetGame()
{
	locateObject(knight_p[0], scene1, X[3], Y[2]);
	locateObject(knight_p[1], scene1, X[2], Y[3]);
	locateObject(knight_p[2], scene1, X[3], Y[1]);
	locateObject(knight_p[3], scene1, X[3], Y[0]);
	locateObject(knight_p[4], scene1, X[1], Y[3]);
	locateObject(knight_p[5], scene1, X[0], Y[3]);
	locateObject(knight_p[6], scene1, X[0], Y[1]);
	locateObject(knight_p[7], scene1, X[1], Y[1]);
	locateObject(knight_p[8], scene1, X[1], Y[0]);
	locateObject(knight_p[9], scene1, X[2], Y[0]);
	locateObject(knight_p[10], scene1, X[2], Y[1]);
	locateObject(knight_p[11], scene1, X[1], Y[2]);
	locateObject(knight_p[12], scene1, X[0], Y[2]);
	locateObject(knight_p[13], scene1, X[2], Y[2]);
	locateObject(knight_p[14], scene1, X[0], Y[0]);
	locateObject(blank16, scene1, X[3], Y[3]);
	blank[0] = X[3], blank[1] = Y[3];
	stopTimer(timer1);
	setTimer(timer1, 300.0f);
	showObject(start);

}

void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
	for (int i = 0; i < 15; i++)
	{
		if (started)
		{
			if (object == knight_p[i])
			{
				if (action == MouseAction::MOUSE_DRAG_RIGHT)
				{
					if (knight_X[i] == blank[0] - 140 && knight_Y[i] == blank[1])
					{
						locateObject(knight_p[i], scene1, blank[0], blank[1]);
						locateObject(blank16, scene1, blank[0] - 140, blank[1]);
						blank[0] = blank[0] - 140;
						knight_X[i] = knight_X[i] + 140;

					}
				}
				else if (action == MouseAction::MOUSE_DRAG_LEFT)
				{
					if (knight_X[i] == blank[0] + 140 && knight_Y[i] == blank[1])
					{
						locateObject(knight_p[i], scene1, blank[0], blank[1]);
						locateObject(blank16, scene1, blank[0] + 140, blank[1]);
						blank[0] = blank[0] + 140;
						knight_X[i] = knight_X[i] - 140;
					}
				}
				else if (action == MouseAction::MOUSE_DRAG_UP)
				{
					if (knight_Y[i] == blank[1] - 150 && knight_X[i] == blank[0])
					{
						locateObject(knight_p[i], scene1, blank[0], blank[1]);
						locateObject(blank16, scene1, blank[0], blank[1] - 150);
						blank[1] = blank[1] - 150;
						knight_Y[i] = knight_Y[i] + 150;
					}
				}
				else if (action == MouseAction::MOUSE_DRAG_DOWN)
				{
					if (knight_Y[i] == blank[1] + 150 && knight_X[i] == blank[0])
					{
						locateObject(knight_p[i], scene1, blank[0], blank[1]);
						locateObject(blank16, scene1, blank[0], blank[1] + 150);
						blank[1] = blank[1] + 150;
						knight_Y[i] = knight_Y[i] - 150;
					}
				}
			}
		}
	}
	if (started)
	{
		if (knight_X[0] == 342 && knight_X[1] == 482 && knight_X[2] == 622 && knight_X[3] == 762 && knight_X[4] == 342 && knight_X[5] == 482 && knight_X[6] == 622 && knight_X[7] == 762 &&
			knight_X[8] == 342 && knight_X[9] == 482 && knight_X[10] == 622 && knight_X[11] == 762 && knight_X[12] == 342 && knight_X[13] == 482 && knight_X[14] == 622 &&
			knight_Y[0] == 482 && knight_Y[1] == 482 && knight_Y[2] == 482 && knight_Y[3] == 482 && knight_Y[4] == 332 && knight_Y[5] == 332 && knight_Y[6] == 332 && knight_Y[7] == 332 &&
			knight_Y[8] == 182 && knight_Y[9] == 182 && knight_Y[10] == 182 && knight_Y[11] == 182 && knight_Y[12] == 32 && knight_Y[13] == 32 && knight_Y[14] == 32)
		{
			timer_second = getTimer(timer1);
			int tem;
			int timer_value = 300 - timer_second;
			char buf[256];
			sprintf(buf, "성공, 걸린 시간은 %d초 입니다.", timer_value);
			stopTimer(timer1);
			showMessage(buf);
			started = false;
		}
	}

	if (object == start)
	{
		startGame();
	}
	else if (object == end)
	{
		endGame();
	}
	else if (object == restart)
	{
		resetGame();
	}
}


int main()
{
	setTimerCallback(timerCallback);
	setMouseCallback(mouseCallback);
	scene1 = createScene("hollow_knight", "hollow_knight1.1200.png");
	knight_p[0] = createObject("knightp_1.png", scene1, X[3], Y[2], true);
	knight_p[1] = createObject("knightp_2.png", scene1, X[2], Y[3], true);
	knight_p[2] = createObject("knightp_3.png", scene1, X[3], Y[1], true);
	knight_p[3] = createObject("knightp_4.png", scene1, X[3], Y[0], true);
	knight_p[4] = createObject("knightp_5.png", scene1, X[1], Y[3], true);
	knight_p[5] = createObject("knightp_6.png", scene1, X[0], Y[3], true);
	knight_p[6] = createObject("knightp_7.png", scene1, X[0], Y[1], true);
	knight_p[7] = createObject("knightp_8.png", scene1, X[1], Y[1], true);
	knight_p[8] = createObject("knightp_9.png", scene1, X[1], Y[0], true);
	knight_p[9] = createObject("knightp_10.png", scene1, X[2], Y[0], true);
	knight_p[10] = createObject("knightp_11.png", scene1, X[2], Y[1], true);
	knight_p[11] = createObject("knightp_12.png", scene1, X[1], Y[2], true);
	knight_p[12] = createObject("knightp_13.png", scene1, X[0], Y[2], true);
	knight_p[13] = createObject("knightp_14.png", scene1, X[2], Y[2], true);
	knight_p[14] = createObject("knightp_15.png", scene1, X[0], Y[0], true);
	blank16 = createObject("blank16.png", scene1, X[3], Y[3], true);
	start = createObject("start.png", scene1, 1000, 500, true);
	end = createObject("end.png", scene1, 1000, 450, true);
	restart = createObject("restart.png", scene1, 1000, 400, true);
	timer1 = createTimer(300.0f);
	showTimer(timer1);
	startGame(scene1);
}