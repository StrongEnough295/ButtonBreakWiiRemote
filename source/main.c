#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

static u32* xfb;
static GXRModeObj* rmode;


void Initialise() {

	VIDEO_Init();
	WPAD_Init();
	PAD_Init();

	rmode = VIDEO_GetPreferredMode(NULL);

	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb, 20, 20, rmode->fbWidth, rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);

	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if (rmode->viTVMode & VI_NON_INTERLACE) VIDEO_WaitVSync();
}

void UpdateBackgroundColor(int counter) {
	int colorTier = (counter / 100) % 4;

	if (colorTier == 0) {
		printf("\x1b[40m");
	}
	else if (colorTier == 1) {
		printf("\x1b[41m");
	}
	else if (colorTier == 2) {
		printf("\x1b[42m");
	}
	else {
		printf("\x1b[44m");
	}

	printf("\x1b[37m");
	printf("\x1b[2J");
	printf("\x1b[H");

	printf("Button Break for Wii v1.3\n");
	printf("Created by Strong Enough\n");
	printf("-------------------------\n");
	printf("Press the Home/Start Button to exit.\n");
	printf("------------------------------\n");
}


int main() {

	Initialise();

	int buttonCounter = 0;
	int lastColorTier = 0;
	u32 lastNunchukBtns = 0;
	u32 lastClassicBtns = 0;

	UpdateBackgroundColor(buttonCounter);

	while (1) {
		WPAD_ScanPads();
		PAD_ScanPads();

		u16 buttonsDown = WPAD_ButtonsDown(0);
		u16 gcButtonsDown = PAD_ButtonsDown(0);

		if (buttonsDown & WPAD_BUTTON_A) {
			buttonCounter++;
			printf("You pressed the A button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_B) {
			buttonCounter++;
			printf("You pressed the B button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_1) {
			buttonCounter++;
			printf("You pressed the 1 button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_2) {
			buttonCounter++;
			printf("You pressed the 2 button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_PLUS) {
			buttonCounter++;
			printf("You pressed the Plus button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_MINUS) {
			buttonCounter++;
			printf("You pressed the Select button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_UP) {
			buttonCounter++;
			printf("You pressed the D-pad Up button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_LEFT) {
			buttonCounter++;
			printf("You pressed the D-pad Left button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_RIGHT) {
			buttonCounter++;
			printf("You pressed the D-Pad Right button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_DOWN) {
			buttonCounter++;
			printf("You pressed the D-Pad Down button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (buttonsDown & WPAD_BUTTON_HOME) {
			printf("Exiting...\n");
			break;
		}

		if (gcButtonsDown & PAD_BUTTON_A) {
			buttonCounter++;
			printf("You pressed the A button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_BUTTON_B) {
			buttonCounter++;
			printf("You pressed the B button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_BUTTON_X) {
			buttonCounter++;
			printf("You pressed the X button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_BUTTON_Y) {
			buttonCounter++;
			printf("You pressed the Y button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_TRIGGER_L) {
			buttonCounter++;
			printf("You pressed the L button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_TRIGGER_R) {
			buttonCounter++;
			printf("You pressed the R button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_TRIGGER_Z) {
			buttonCounter++;
			printf("You pressed the Z button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_BUTTON_UP) {
			buttonCounter++;
			printf("You pressed the D-pad Up button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_BUTTON_DOWN) {
			buttonCounter++;
			printf("You pressed the D-pad Down button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_BUTTON_LEFT) {
			buttonCounter++;
			printf("You pressed the D-pad Left button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_BUTTON_RIGHT) {
			buttonCounter++;
			printf("You pressed the D-pad Right button!\n");
			printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
		}
		if (gcButtonsDown & PAD_BUTTON_START) {
			printf("Exiting...\n");
			break;
		}

		expansion_t exp;
		WPAD_Expansion(0, &exp);

		if (exp.type == WPAD_EXP_NUNCHUK) {
			u32 nunchuk_btns = exp.nunchuk.btns;
			u32 nunchuk_down = nunchuk_btns & ~lastNunchukBtns;
			lastNunchukBtns = nunchuk_btns;

			if (nunchuk_down & NUNCHUK_BUTTON_Z) {
				buttonCounter++;
				printf("You pressed the Z button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (nunchuk_down & NUNCHUK_BUTTON_C) {
				buttonCounter++;
				printf("You pressed the C button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
		}
		else if (exp.type == WPAD_EXP_CLASSIC) {
			u32 classic_btns = exp.classic.btns;
			u32 classic_down = classic_btns & ~lastClassicBtns;
			lastClassicBtns = classic_btns;

			if (classic_down & WPAD_CLASSIC_BUTTON_A) {
				buttonCounter++;
				printf("You pressed the A button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_B) {
				buttonCounter++;
				printf("You pressed the B button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_X) {
				buttonCounter++;
				printf("You pressed the X button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_Y) {
				buttonCounter++;
				printf("You pressed the Y button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_ZL) {
				buttonCounter++;
				printf("You pressed the ZL button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_ZR) {
				buttonCounter++;
				printf("You pressed the ZR button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_FULL_L) {
				buttonCounter++;
				printf("You pressed the L button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_FULL_R) {
				buttonCounter++;
				printf("You pressed the R button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_PLUS) {
				buttonCounter++;
				printf("You pressed the Plus button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_MINUS) {
				buttonCounter++;
				printf("You pressed the Minus button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_UP) {
				buttonCounter++;
				printf("You pressed the D-pad Up button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_DOWN) {
				buttonCounter++;
				printf("You pressed the D-pad Down button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_LEFT) {
				buttonCounter++;
				printf("You pressed the D-pad Left button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_RIGHT) {
				buttonCounter++;
				printf("You pressed the D-pad Right button!\n");
				printf("You Mashed %d Buttons!\n-----------------------\n", buttonCounter);
			}
			if (classic_down & WPAD_CLASSIC_BUTTON_HOME) {
				printf("Exiting...\n");
				break;
			}
		}
		else {
			lastNunchukBtns = 0;
			lastClassicBtns = 0;
		}

		int currentTier = buttonCounter / 100;
		if (currentTier != lastColorTier) {
			UpdateBackgroundColor(buttonCounter);
			lastColorTier = currentTier;
		}

		VIDEO_WaitVSync();
	}

	return 0;
}
