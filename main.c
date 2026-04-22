#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>

static u32 *xfb;
static GXRModeObj *rmode;


void Initialise() {
  
	VIDEO_Init();
	WPAD_Init();
 
	rmode = VIDEO_GetPreferredMode(NULL);

	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
 
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
}


int main() {
 
	Initialise();
 
	printf("Button Break for Wii v0.5 - Nunchuck\n");
	printf("------------------------------------\n");
	printf("Hold the Power Button for 3-5 seconds to power off.\n");
	printf("---------------------------------------------------\n");
	while (1) {
		expansion_t exp;
		WPAD_ScanPads();
		WPAD_Expansion(0, &exp);
		if (exp.type == WPAD_EXP_NUNCHUK) {
			u16 buttonsDown = WPAD_ButtonsDown(0);
			u32 nunchuk_btns = exp.nunchuk.btns;
			if (buttonsDown & WPAD_BUTTON_A) {
				printf("Button A pressed.\n");
				printf("-----------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_B) {
				printf("Button B pressed.\n");
				printf("-----------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_1) {
				printf("Button 1 pressed.\n");
				printf("-----------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_2) {
				printf("Button 2 pressed.\n");
				printf("-----------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_PLUS) {
				printf("Button Start pressed.\n");
				printf("--------------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_MINUS) {
				printf("Button Select pressed.\n");
				printf("---------------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_UP) {
				printf("Button D-pad Up pressed.\n");
				printf("-----------------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_LEFT) {
				printf("Button D-pad Left pressed.\n");
				printf("-------------------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_RIGHT) {
				printf("Button D-Pad Right pressed.\n");
				printf("--------------------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_DOWN) {
				printf("Button D-Pad Down pressed.\n");
				printf("-------------------------\n");
			}
			if (buttonsDown & WPAD_BUTTON_HOME) {
				printf("Button Home pressed.\n");
				printf("--------------------\n");
			}
			if (nunchuk_btns & NUNCHUK_BUTTON_Z) {
				printf("Button Z pressed.\n");
				printf("-----------------\n");
			}
			if (nunchuk_btns & NUNCHUK_BUTTON_C) {
				printf("Button C pressed.\n");
				printf("-----------------\n");
			}

		}
		}
	
		return 0;
	}