/*
Open95Keygen PSX v1.0 - May 11th 2021

Copyright (c) 2021, Alex Free 
All rights reserved. 
Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met: 
 * Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer. 
 * Redistributions in binary form must reproduce the above copyright 
   notice, this list of conditions and the following disclaimer in the 
   documentation and/or other materials provided with the distribution. 
 * Neither the name of Alex Free nor the names of its contributors may be 
   used to endorse or promote products derived from this software without 
   specific prior written permission. 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE. 

Huge thanks to Lameguy64's tutorials (http://lameguy64.net/tutorials/pstutorials) and his PSX SDK (https://github.com/Lameguy64/PSn00bSDK)! This will probably not build with PhyQSDK!
 */

#include <stdio.h>
#include <sys/types.h>
#include <psxetc.h>
#include <psxgte.h>
#include <psxgpu.h>
#include <stdlib.h>
#include <psxpad.h>
#include <limits.h>
#include <ioctl.h>
#include <sys/fcntl.h>
#include <psxapi.h>
#include <psxsio.h>

#define DIGIT_RANGE 10
#define OEM_DAY_RANGE 367

typedef enum { FALSE, TRUE } bool;

bool gen;
bool display_keys;

int oem_key_year[2];
int oem_key_5[5];
int oem_key_5_random[5];
int retail_key_1[3];
int retail_key_2[7];

int oem_key_day;
int digit;
int sum7;

int sw_clock;

// Defines display/draw environments for double buffering
DISPENV disp[2];
DRAWENV draw[2];
int db;

void init(void)
{
	// This not only resets the GPU but it also installs the library's ISR subsystem to the kernel
	ResetGraph(0);
	
	// Define display environments, first on top and second on bottom
	SetDefDispEnv(&disp[0], 0, 0, 320, 240);
	SetDefDispEnv(&disp[1], 0, 240, 320, 240);
	
	// Define drawing environments, first on bottom and second on top
	SetDefDrawEnv(&draw[0], 0, 240, 320, 240);
	SetDefDrawEnv(&draw[1], 0, 0, 320, 240);
	
	// Set and enable black color
	setRGB0(&draw[0], 0, 0, 0);
	setRGB0(&draw[1], 0, 0, 0);
    draw[0].isbg = 1;
	draw[1].isbg = 1;
	
	// Clear double buffer counter
	db = 0;
	
	// Apply the GPU environments
	PutDispEnv(&disp[db]);
	PutDrawEnv(&draw[db]);
	
	// Load test font
	FntLoad(960, 0);
	
	// Open up a test font text stream of 200 characters
	FntOpen(0, 8, 320, 224, 0, 200);
}

void display(void)
{
	// Flip buffer index
	db = !db;
	
	// Wait for all drawing to complete
	DrawSync(0);
	
	// Wait for vertical sync to cap the logic to 60fps (or 50 in PAL mode)
	// and prevent screen tearing
	VSync(0);

	// Switch pages	
	PutDispEnv(&disp[db]);
	PutDrawEnv(&draw[db]);
	
	// Enable display output, ResetGraph() disables it by default
	SetDispMask(1);
}

void gen_oem_day() 
{
    gen = TRUE;
    while(gen) 
    {
        oem_key_day = rand() % OEM_DAY_RANGE;

        if(oem_key_day == 0)
        {
            gen = TRUE;
        }
        else
        {
            gen = FALSE;
        }
    }
}

void gen_oem_year() 
{
    gen = TRUE;
    while(gen) 
    {
        for(digit=0; digit<2; ++digit)
        oem_key_year[digit] = rand() % DIGIT_RANGE;

        if((oem_key_year[0] == 9 && oem_key_year[1] >= 5) || (oem_key_year[0] == 0 && oem_key_year[1] < 3))
        {
            gen = FALSE;
        }
        else
        {
            gen = TRUE;
        }
    }
}

void gen_5digits_oem()
{
    gen = TRUE;
    while(gen)
    {
        for(digit=0; digit<5; ++digit)
        oem_key_5[digit] = rand() % DIGIT_RANGE;

        sum7 = oem_key_5[0] + oem_key_5[1] + oem_key_5[2] + oem_key_5[3] + oem_key_5[4];

        if(sum7 % 7 == 0)
        {
            gen = FALSE;
        }
        else
        {
            gen = TRUE;
        }
    }
}

void gen_5digits_random_oem()
{
    for(digit=0; digit<5; ++digit)
    oem_key_5_random[digit] = rand() % DIGIT_RANGE;   
}



void gen_3digits_retail() 
{
    gen = TRUE;
    while(gen) 
    {
        for(digit=0; digit<3; ++digit)
        retail_key_1[digit] = rand() % DIGIT_RANGE;

        if((retail_key_1[0] == 3 && retail_key_1[1] == 3 && retail_key_1[2] == 3) || (retail_key_1[0] == 4 && retail_key_1[1] == 4 && retail_key_1[2] == 4) || (retail_key_1[0] == 5 && retail_key_1[1] == 5 && retail_key_1[2] == 5) || (retail_key_1[0] == 6 && retail_key_1[1] == 6 && retail_key_1[2] == 6) || (retail_key_1[0] == 7 && retail_key_1[1] == 7 && retail_key_1[2] == 7) || (retail_key_1[0] == 8 && retail_key_1[1] == 8 && retail_key_1[2] == 8) || (retail_key_1[0] == 9 && retail_key_1[1] == 9 && retail_key_1[2] == 9))
        {
            gen = TRUE;
        }
        else
        {
            gen = FALSE;
        }
    }
}

void gen_7digits_retail()
{
    gen = TRUE;
    while(gen)
    {
        for(digit=0; digit<7; ++digit)
        retail_key_2[digit] = rand() % DIGIT_RANGE;

        sum7 = retail_key_2[0] + retail_key_2[1] + retail_key_2[2] + retail_key_2[3] + retail_key_2[4] + retail_key_2[5] + retail_key_2[6];

        if(sum7 % 7 == 0)
        {
            gen = FALSE;
        }
        else
        {
            gen = TRUE;
        }
    }
}

int main(int argc, const char *argv[])
{
	init();

    // Controller
    u_char padbuff[2][34];
    InitPAD( padbuff[0], 34, padbuff[1], 34 );
    padbuff[0][0] = padbuff[0][1] = 0xff;
    padbuff[1][0] = padbuff[1][1] = 0xff;
    u_short button;
    button = *((u_short*)(padbuff[0]+2));	
    StartPAD();
    ChangeClearPAD(1);
    PADTYPE *pad;
    pad = (PADTYPE*)padbuff[0];

// Replacement for time based randomness, goes up to INT_MAX and then resets...
	sw_clock = 1;
    srand(sw_clock);

    display_keys = false;

	while(1)
	{
		FntPrint(-1, "Open95Keygen by Alex Free (C)2021\n=================================\n\n");

        if(display_keys)
        {
        FntPrint(-1, "Retail Product Key: %d%d%d-%d%d%d%d%d%d%d\nOEM Product Key: %03d%d%d-OEM-00%d%d%d%d%d-%d%d%d%d%d\n\nPress the cross button for more keys...\n", retail_key_1[0], retail_key_1[1], retail_key_1[2], retail_key_2[0], retail_key_2[1], retail_key_2[2], retail_key_2[3], retail_key_2[4], retail_key_2[5], retail_key_2[6], oem_key_day, oem_key_year[0], oem_key_year[1], oem_key_5[0], oem_key_5[1], oem_key_5[2], oem_key_5[3], oem_key_5[4], oem_key_5_random[0], oem_key_5_random[1], oem_key_5_random[2], oem_key_5_random[3], oem_key_5_random[4]);
	    FntFlush(-1);
        } 
        else
        {
		FntPrint(-1, "Press the cross button to generate\nrandom Microsoft Windows 95/NT 4.0 OEM\nand retail keys!\n");
		FntFlush(-1);
        }
  
		// Update display
		display();
		
        if(sw_clock < INT_MAX)
        {
            sw_clock++;
        }
        else
        {
            sw_clock = 1;
        }

        // Only parse inputs when a compatible controller is connected
        if( pad->stat == 0 )
        {
            if( ( pad->type == 0x4 ) || ( pad->type == 0x5 ) || ( pad->type == 0x7 ) )
            {
                if( !(pad->btn&PAD_CROSS) )
                {
                    if(!display_keys)
                    display_keys = true;
                    gen_3digits_retail();
                    gen_7digits_retail();
                    gen_oem_day();
                    gen_oem_year();
                    gen_5digits_oem();
                    gen_5digits_random_oem();
                }
            }
        }

    }
	return 0;
}
