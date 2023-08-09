/*
	Agent K-9
	A single player 2D Shooting game.

	Original Authors:

	Dipta Biswas
	Muhammad Riaz
	Bidyarthi Paul
*/

#define _CRT_SECURE_NO_WARNINGS

#include "iGraphics.h"
#include "Variables.h"
#include "LoadImage.h"
#include "Menu.h"
#include "Player.h"
#include "GameOver.h"
#include "GameSave.h"
#include "ScoreSave.h"
#include "Sound.h"
#include "IntroLevels.h"
#include "Enemy.h"
#include "Character.h"
#include "Collision.h"
#include <iostream>
using namespace std;

void iDraw()
{
	iClear();

	/*_____________________________________________________Showing menu pages._________________________________________________________*/

	if (menu_option >= 0 && menu_option <= 5)
	{
		showMenu(); //This function runs all the codes for menu.
	}

	/*_____________________________________________Intro level one codes run from here.________________________________________________*/

	else if (intro_level == 1)
	{
		introLevelOne(); //This function runs all the codes for intro level one.
	}

	/*______________________________________________________Showing map one.__________________________________________________________*/

	else if (show_map == 1)
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HIGHT, map_screen[0]);
	}

	/*________________________________________________Level one codes run from here.___________________________________________________*/


	/*____________________________________________________Showing gift screen.________________________________________________________*/

	else if (show_gift == 1)
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HIGHT, gift_screen);

		if (!gift_taken)
		{
			iShowImage(1240, 34, 240, 100, gift_plane[0]);
			showIntroPlayer();
		}
		else
		{
			iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HIGHT, invite);
			iShowImage(1200, 15, 200, 178, gift_plane[1]);
		}
	}

	/*_____________________________________________Intro level two codes run from here._______________________________________________*/


	/*______________________________________________________Showing map two.__________________________________________________________*/

	/*________________________________________________Level two codes run from here.__________________________________________________*/


	/*________________________________________________Game over codes start from here.________________________________________________*/

	gameOver(); //This function runs all the codes regarding game over.

	/*____________________________________________________Showing pause screen.______________________________________________________*/

	if (pause)
	{
		iShowImage(0, 0, SCREEN_WIDTH, SCREEN_HIGHT, pause_screen);
	}
}

/*_________________________________________________________Mouse Controls._____________________________________________________________*/

void iMouseMove(int mx, int my)
{

}

void iPassiveMouse(int mx, int my)
{
	if (!pause)
	{
		//cout << mx << ", " << my << endl;
		if (menu_option >= 0 && menu_option <= 5)
		{
			if (mx >= 552 && mx <= 968 && my >= 490 && my <= 547)
			{
				highlight_index = 0;
			}
			else if (mx >= 552 && mx <= 968 && my >= 429 && my <= 486)
			{
				highlight_index = 1;
			}
			else if (mx >= 552 && mx <= 968 && my >= 368 && my <= 426)
			{
				highlight_index = 2;
			}
			else if (mx >= 552 && mx <= 968 && my >= 305 && my <= 364)
			{
				highlight_index = 3;
			}
			else if (mx >= 552 && mx <= 968 && my >= 244 && my <= 302)
			{
				highlight_index = 4;
			}
			else if (mx >= 552 && mx <= 968 && my >= 181 && my <= 240)
			{
				highlight_index = 5;
			}
			else
			{
				highlight_index = 6;
			}

			//For highlighting new game and continue button.
			if (menu_option == 1)
			{
				if (mx >= 552 && mx <= 968 && my >= 490 && my <= 547)
				{
					start_highlight_index = 0;
				}
				else if (mx >= 552 && mx <= 968 && my >= 429 && my <= 486)
				{
					start_highlight_index = 1;
				}
				else
				{
					start_highlight_index = 2;
				}
			}

			//For highlighting back button.
			if (mx >= 552 && mx <= 968 && my >= 60 && my <= 116)
			{
				back_highlight_index = menu_option - 1;
			}
			else
			{
				back_highlight_index = 5;
			}

			game_over_highlight_index = 3;
		}

		//For highlighting home button in game over screen.
		else if (game_over)
		{
			if (mx >= 552 && mx <= 968 && my >= 60 && my <= 116)
			{
				game_over_highlight_index = game_over_index;
			}
			else
			{
				game_over_highlight_index = 3;
			}
		}

		//For apple collector ring.
	}
}

void iMouse(int button, int state, int mx, int my)
{
	if (!pause)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		{
			//cout << mx << ", " << my << endl;

			if (menu_option >= 0 && menu_option <= 5) //If the game is on the menu page.
			{
				selectMenuOption(mx, my);
			}

			if (game_over_index == 0 || game_over_index == 1 || game_over_index == 2) //If high score is achieved.
			{
				if (game_over_index == 1 || game_over_index == 2) //If high score is achieved.
				{
					activateTextBox(mx, my); //This will activate the text box to enter high scorer's name.
				}

				//Clicking home button in game over screen.
				if (mx >= 552 && mx <= 968 && my >= 60 && my <= 116)
				{
					menu_option = 0; //To go to home.
					controlSound(true); //For playing sound.
					sound_playing = false;

					level = 0;
					intro_level = 0;
					show_map = 0;
					show_gift = 0;

					ground_player.score = 0;
					ground_player.health = 100;
					player_distance = 0;
					gift_taken = false;

					intro_player.x = 160;
					intro_player.y = 30;

					ground_player.x = 160;

					flying_player.x = 160;
					flying_player.y = 520;

					jump = false;
					jumping = false;
					jumping_height = 0;

					intro_player.condition = 0;
					ground_player.condition = 0;

					game_over = false;
					player_rank = 0;
					game_over_index = 3;
					memset(high_score.name, NULL, sizeof(high_score.name)); //Clearing the name.
					name_index = 0;
				}
			}
		}

		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{

		}
	}
}

/*_______________________________________________________Keyboard controls.____________________________________________________________*/

void iKeyboard(unsigned char key)
{
	if (!pause)
	{
		if (field_active) //If high score is achieved and texbox is active for entering name.
		{
			inputName(key);
		}

		if (key == '\r')
		{
			if (field_active && game_over && player_rank != 0) //This block will execute after entering the high scorer's name and pressing Enter.
			{
				field_active = false; //To deactivate the name input text box.
				saveScore();
				memset(high_score.name, NULL, sizeof(high_score.name)); //Clearing the name after saving the high score.
				name_index = 0;
				ground_player.health = 100;
				ground_player.score = 0;
				game_over = false;
				menu_option = 0;
			}
		}

		if (key == ' ')
		{
			fire = true;
		}

		if (key == 'e' || key == 'E')
		{
			if (intro_level == 1)
			{
				if (intro_player.x + intro_player.extended_x + 35 >= stair_top.x && intro_player.x + intro_player.extended_x + intro_player.dimension_x - 35 <= stair_top.x + stair_top.dimension_x && intro_player.y + intro_player.extended_y + jumping_height >= stair_top.y + stair_top.dimension_y)
				{
					show_map = 1; //For showing map after intro level one.
					intro_level = 0; //To stop running intro level one codes.

					saveGame(); //To save the game progress.
				}
			}
			else if (show_gift == 1)
			{
				if (intro_player.x + intro_player.extended_x + 35 >= 1320 && intro_player.x + intro_player.extended_x + intro_player.dimension_x - 35 <= 1480)
				{
					gift_taken = true;
				}
			}
		}

		if (key == 'm' || key == 'M')
		{
			if (!field_active)
			{
				if (!mute)
				{
					controlSound(false);
					mute = true;
				}
				else
				{
					mute = false;
					controlSound(true);
				}
			}
		}

		if (key == '$')
		{
			cheatcode_active = true;
			//cout << "Cheatcode activated!" << endl;
		}
	}

	if (key == 'p' || key == 'P')
	{
		if (intro_level != 0 || level != 0 || show_gift != 0)
		{
			if (!pause)
			{
				pause = true;

				iPauseTimer(timer_ten_mili);
				iPauseTimer(timer_twenty_mili);
				iPauseTimer(timer_forty_mili);
				iPauseTimer(timer_hundred_mili);
				iPauseTimer(timer_one_sec);
				iPauseTimer(timer_four_sec);
			}
			else
			{
				pause = false;

				iResumeTimer(timer_ten_mili);
				iResumeTimer(timer_twenty_mili);
				iResumeTimer(timer_forty_mili);
				iResumeTimer(timer_hundred_mili);
				iResumeTimer(timer_one_sec);
				iResumeTimer(timer_four_sec);
			}
		}
	}
}

void iSpecialKeyboard(unsigned char key)
{
	if (!pause)
	{
		if (key == GLUT_KEY_LEFT)
		{
			if (intro_level == 1 || show_gift == 1) //Moving character for intro levels.
			{
				if (jumping_height == 0)
				{
					intro_player.condition = 3;
				}

				if (intro_player.x > -34)
				{
					intro_player.x -= 4;
				}

				changeRunningBackImage();
			}

		}

		if (key == GLUT_KEY_RIGHT)
		{
			if (intro_level == 1 || show_gift == 1) //Moving character for intro levels.
			{
				if (jumping_height == 0)
				{
					intro_player.condition = 2;
				}

				if (intro_player.x < 1395)
				{
					intro_player.x += 4;
				}

				changeRunningImage();
			}
		}

		if (key == GLUT_KEY_UP)
		{
			if (intro_level == 1 || show_gift == 1) //Moving character for intro levels.
			{
				if (intro_player.condition <= 3)
				{
					intro_player.condition += 4;
				}

				if (!jump)
				{
					jump = true;
					jumping = true;
				}
			}
		if (key == GLUT_KEY_HOME)
		{
			//Resetting conditions.
			menu_option = 0; //To go to home.
			controlSound(true); //For playing sound.
			sound_playing = false;

			level = 0;
			intro_level = 0;
			show_map = 0;
			show_gift = 0;

			ground_player.score = 0;
			ground_player.health = 100;
			player_distance = 0;
			shield_count = 0;
			active_shield = false;
			gift_taken = false;

			intro_player.x = 160;
			intro_player.y = 30;

			ground_player.x = 160;

			flying_player.x = 160;
			flying_player.y = 520;

			jump = false;
			jumping = false;
			jumping_height = 0;

			intro_player.condition = 0;
			ground_player.condition = 0;

			goblin.reset(1390, 662, true, 24, 0);

			game_over = false;
			player_rank = 0;
			game_over_index = 3;
			memset(high_score.name, NULL, sizeof(high_score.name)); //Clearing the name.
			name_index = 0;
		}
	}

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
}

/*________________________________________________________Timer functions._____________________________________________________________*/

void tenMiliSec()
{
	if (intro_level == 1)
	{
		moveStairs();
	}
}

void twentyMiliSec()
{
	if (intro_level == 1 || show_gift == 1)
	{
		Jump();
	}
}

void hundredMiliSec()
{
	if (intro_level == 1 && goblin.state)
	{
		changeGoblinImage();

		if (!cannon_fire)
		{
			cannonFire();
		}
	}
	if (intro_level == 1 || show_gift == 1)
	{
		changeIdleImage();
	}
}

/*_________________________________________________________Main function.______________________________________________________________*/
/***************************************************************************************************************************************/

int main()
{
	timer_ten_mili = iSetTimer(10, tenMiliSec);
	timer_twenty_mili = iSetTimer(20, twentyMiliSec);
	timer_hundred_mili = iSetTimer(100, hundredMiliSec);

	system("Color 0C"); //For only windows platform.
	cout << "Agent K-9 is suiting up! Get Ready!" << endl;

	iInitialize(SCREEN_WIDTH, SCREEN_HIGHT, "AGENT K-9");

	loadImage();

	controlSound(true); //For playing sound.

	iStart();

	return 0;
}
