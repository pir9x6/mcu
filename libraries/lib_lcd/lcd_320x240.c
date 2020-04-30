//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   titre           :   afficheur lcd                                   &&&
//&&&   fichier         :   lcd_320x240.h                                   &&&
//&&&   description     :   prototypes des fonctions lcd                    &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   auteur          :   pierre blaché                                   &&&
//&&&   date            :   avril 2011                                      &&&
//&&&   version         :   1.0                                             &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&                                                                       &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//&&&   history         :   v1.0  01/04/2011  Original creation             &&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

#include "p33fxxxx.h"
#include "delays.h"
#include "caracteres.h"
#include "constantes.h"
#include "lcd_320x240.h"

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- initialisation de l'afficheur ------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_init(void)
{

    lcd_rst = 1;
    delay_ms(5);
    lcd_rst = 0;
    delay_ms(10);
    lcd_rst = 1;
    delay_ms(20);
    lcd_rd = 0;

    //  vendor
    lcd_write(0x0046,0x00a4);
    lcd_write(0x0047,0x0053);
    lcd_write(0x0048,0x0000);
    lcd_write(0x0049,0x0044);
    lcd_write(0x004a,0x0004);
    lcd_write(0x004b,0x0067);
    lcd_write(0x004c,0x0033);
    lcd_write(0x004d,0x0077);
    lcd_write(0x004e,0x0012);
    lcd_write(0x004f,0x004c);
    lcd_write(0x0050,0x0046);
    lcd_write(0x0051,0x0044);

    //240x320 window setting
    lcd_write(0x0002,0x0000); // column address start2
    lcd_write(0x0003,0x0000); // column address start1
    lcd_write(0x0004,0x0000); // column address end2
    lcd_write(0x0005,0x00ef); // column address end1
    lcd_write(0x0006,0x0000); // row address start2
    lcd_write(0x0007,0x0000); // row address start1
    lcd_write(0x0008,0x0001); // row address end2
    lcd_write(0x0009,0x003f); // row address end1

    // display setting
    lcd_write(0x0001,0x0006); // idmon=0, invon=1, noron=1, ptlon=0
    lcd_write(0x0016,0x00c8); // my=0, mx=0, mv=0, ml=1, bgr=0, teon=0   0048
    lcd_write(0x0023,0x0095); // n_dc=1001 0101
    lcd_write(0x0024,0x0095); // pi_dc=1001 0101
    lcd_write(0x0025,0x00ff); // i_dc=1111 1111

    lcd_write(0x0027,0x0002); // n_bp=0000 0010
    lcd_write(0x0028,0x0002); // n_fp=0000 0010
    lcd_write(0x0029,0x0002); // pi_bp=0000 0010
    lcd_write(0x002a,0x0002); // pi_fp=0000 0010
    lcd_write(0x002c,0x0002); // i_bp=0000 0010
    lcd_write(0x002d,0x0002); // i_fp=0000 0010

    lcd_write(0x003a,0x0001); // n_rtn=0000, n_nw=001    0001
    lcd_write(0x003b,0x0000); // p_rtn=0000, p_nw=001
    lcd_write(0x003c,0x00f0); // i_rtn=1111, i_nw=000
    lcd_write(0x003d,0x0000); // div=00
    delay_ms(1);
    lcd_write(0x0035,0x0038); // eqs=38h
    lcd_write(0x0036,0x0078); // eqp=78h
    lcd_write(0x003e,0x0038); // son=38h
    lcd_write(0x0040,0x000f); // gdon=0fh
    lcd_write(0x0041,0x00f0); // gdoff

    // power supply setting
    lcd_write(0x0019,0x0049); // cadj=0100, cuadj=100, osd_en=1 ,60hz
    lcd_write(0x0093,0x000f); // radj=1111, 100%
    delay_ms(1);
    lcd_write(0x0020,0x0040); // bt=0100
    lcd_write(0x001d,0x0007); // vc1=111   0007
    lcd_write(0x001e,0x0000); // vc3=000
    lcd_write(0x001f,0x0004); // vrh=0011

    //vcom setting
    lcd_write(0x0044,0x004d); // vcm=101 0000  4d
    lcd_write(0x0045,0x000e); // vdv=1 0001   0011
    delay_ms(1);
    lcd_write(0x001c,0x0004); // ap=100
    delay_ms(2);

    lcd_write(0x001b,0x0018); // gasenb=0, pon=0, dk=1, xdk=0, vlcd_tri=0, stb=0
    delay_ms(1);
    lcd_write(0x001b,0x0010); // gasenb=0, pon=1, dk=0, xdk=0, vlcd_tri=0, stb=0
    delay_ms(1);
    lcd_write(0x0043,0x0080); //set vcomg=1
    delay_ms(2);

    // display on setting
    lcd_write(0x0090,0x007f); // sap=0111 1111
    lcd_write(0x0026,0x0004); //gon=0, dte=0, d=01
    delay_ms(1);
    lcd_write(0x0026,0x0024); //gon=1, dte=0, d=01
    lcd_write(0x0026,0x002c); //gon=1, dte=0, d=11
    delay_ms(1);
    lcd_write(0x0026,0x003c); //gon=1, dte=1, d=11

    // internal register setting
    lcd_write(0x0057,0x0002); // test_mode=1: into test mode
    lcd_write(0x0095,0x0001); // set display clock and pumping clock to synchronize
    lcd_write(0x0057,0x0000); // test_mode=0: exit test mode

    //lcd_write(0x0021,0x0000);
    lcd_write_cmd(0x0022);

}

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------- envoi d'une adresse à l'afficheur ----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_adresse(u16 x1, u16 y1, u16 x2, u16 y2)
{
    lcd_write(0x0002, x1>>8);    // column address start2
    lcd_write(0x0003, x1);           // column address start1
    lcd_write(0x0004, x2>>8);    // column address end2
    lcd_write(0x0005, x2);           // column address end1
    lcd_write(0x0006, y1>>8);    // row address start2
    lcd_write(0x0007, y1);           // row address start1
    lcd_write(0x0008, y2>>8);    // row address end2
    lcd_write(0x0009, y2);           // row address end1
    lcd_write_cmd(0x0022);

}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------ envoi d'une commande + une donnée à l'afficheur ----------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_write(u16 cmd, u16 data)
{
   lcd_write_cmd(cmd);
   lcd_write_data(data);
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//-------------------- envoi d'une commande à l'afficheur ---------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_write_cmd(u16 cmd)
{
    lcd_rs = 0;
    lcd_cs = 0;
    lcd_data = cmd;
    lcd_wr = 0;
    lcd_wr = 1;
    lcd_cs = 1;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------------- envoi d'une couleur ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_write_color(u8 h, u8 l)
{
    lcd_rs = 1;
    lcd_cs = 0;
    lcd_data = ((h << 8) & 0xff00) | (l & 0x00ff);
    lcd_wr = 0;
    lcd_wr = 1;
    lcd_cs = 1;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//----------------------------- envoi d'une donnée ----------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_write_data(u16 data)
{
    lcd_rs = 1;
    lcd_cs = 0;
    lcd_data = data;
    lcd_wr = 0;
    lcd_wr = 1;
    lcd_cs = 1;
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//---------------------- affichage d'un rectangle plein -----------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void lcd_draw_fillrectangle(u16 color)
{
    u16 i,j;
    lcd_adresse(0, 0, 239, 319);

    for(i=0; i<320; i++)
    {
          for (j=0; j<240; j++)
           {
             lcd_write_data(color);
        }
    }
}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------ afficher chaine caractere --------------------------
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void showzifustr(u16 x, u16 y, u8 *str, u16 dcolor, u16 bgcolor)
{
    u16 x1, y1;
    x1 = x;
    y1 = y;
    while(*str!='\0')
    {
        showzifu(x1, y1, *str, dcolor, bgcolor);
        x1 += 7;
        str++;
    }
}

void showzifu(u16 x, u16 y, u8 value, u16 dcolor, u16 bgcolor)
{
    u8 i, j;
    u8 *temp = font;
    lcd_adresse(x,y,x+7,y+11);
    temp += (value-32)*12;

    for(j=0;j<12;j++)
    {
        for(i=0;i<8;i++)
        {
             if((*temp&(1<<(7-i)))!=0)
            {
                lcd_write_data(dcolor);
            }
            else
            {
                lcd_write_data(bgcolor);
            }
        }
        temp++;
     }
}
