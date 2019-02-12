/*
@Author: Apoorv verma
@Apoorve8055
YT : https://www.youtube.com/watch?v=rDqFclKCCvY
*/

#include<bios.h>
#include<ctype.h>
#include<stdlib.h>
#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<string.h>

union  REGS i, o;
struct SREGS s;
int fon=0;
char c;
FILE *p;
char filename[20];
int  buttonm,xm,ym,gd=9,gm=1,set=1,midx,midy;

void clrwin();
void getmousepos(int *buttonm,int *xm, int *ym);
void restrictmouse(int x1,int y1,int x2,int y2);
void showmouse();
int  initmouse();
void setmousepos(int &xpos,int &ypos);
void hidemouse();
void changecursor(int *shape);
int  menu(int);
int  dropmenu(char menu[7][20],int x1,int y1,int x2,int y2,int opt);
int  File();
int  Edit();
void drawwindow(char head[30],int x1, int y1, int x2, int y2, int c);
void press(char name[15],int x1,int y1,int x2,int y2,int c);
int  about();
int  Help();
void newf(char namearray[20]);
void bkcolor();
int  Open();
void inputbox(int x,int y,int limit,int bkc);
int  Newbox();
int  input();
int  output();
void openf(char namearray[20]);
int deletebox();
int deleted();
int deletef();
int fontbox();
int fontf();
int cfont();


main()
 {   int gd = DETECT, gm, status, button, x, y,menu1=-1;

     char array[50];
      _setcursortype(0);
      initgraph(&gd,&gm,"../BGI");
      clrscr();

      {
      setfillstyle(1,BLUE);
       bar(0,0,getmaxx(),getmaxy());
      }//backgroungcolor

      {setcolor(WHITE);
       settextstyle(0,0,2);
       settextjustify(CENTER_TEXT, TOP_TEXT);
       outtextxy(getmaxx()/2,0,"NOTEPAD");
      }// tital name

      {
      setfillstyle(SOLID_FILL,RED);
      bar(getmaxx()-30,0,getmaxx(),20);
      setcolor(15);
      settextstyle(0,0,2);
      outtextxy(getmaxx()-15,0," x ");
       }//close button name

      {
      settextjustify(LEFT_TEXT, TOP_TEXT);
      settextstyle(0,0,0);
      }// for justify text

 //     clrwin();//main text screen

      restrictmouse(0,0,getmaxx()-10,getmaxy()-10); //mouse restriction
      setmousepos(getmaxx()/2,getmaxy()/2);
      showmouse();
      getmousepos(&buttonm,&xm,&ym);
//      about();
//      press("Apoorv",170,148,getmaxx()*3/4,getmaxy()*3/4,7);

      while(1)
     {
      showmouse();
      getmousepos(&buttonm,&xm,&ym);

      if(buttonm==1)
     {
      if((0<=ym)&&(20>=ym)&&(getmaxx()>=xm)&&((getmaxx()-30)<=xm))
      {exit(0);}
      else if((20<=ym)&&(40>=ym)&&(8<=xm)&&(90>=xm))   //File
      { menu1=0; }
      else if((20<=ym)&&(40>=ym)&&(90<=xm)&&(170>=xm))    //edit
      { menu1=1; }
      else if((20<=ym)&&(40>=ym)&&(170<=xm)&&(280>=xm))       //help
      { menu1=2; }
      else if((20<=ym)&&(40>=ym)&&(280<=xm)&&(390>=xm))       //about
      { menu1=3; }
      else {menu1=-1;    bkcolor() ;}
      menu(menu1);
     switch(menu1)
     {
     case 0:File();break;
     case 1:Edit();break;
     case 2:Help();break;
     case 3:about();break;
     }


     /*
    switch(menu1)
    {
    case 0:File();break;
    case 1:Edit();break;
    case 2:Help();break;
    case 3:About();break;
    }
      */

}
}

      getch();
      closegraph();

}

      //start clrwin (text screen + scroll bar)
     void clrwin()
     {
     setfillstyle(SOLID_FILL,15);
     bar(0,40,getmaxx(),getmaxy());//text screem

     setfillstyle(3,BLUE);
     bar(getmaxx()-20,40,getmaxx(),getmaxy());//scroll bar

     }
//end clrwin

//start mouse function
     int initmouse()
{
     i.x.ax=0;//for  initialising mouse.
     int86(0x33,&i,&o);
     return (o.x.ax);
}

void showmouse(){
 i.x.ax=1; // for displaying mouse pointer.
 int86(0x33,&i,&o);
}
void hidemouse(){
 i.x.ax=2;
 int86(0x33,&i,&o);
}

void setmousepos(int &xpos,int &ypos)
{

 i.x.ax=4;
 i.x.cx=xpos;
 i.x.dx=ypos;
 int86(0x33,&i,&o);
}

void restrictmouse(int x1,int y1,int x2,int y2){
 i.x.ax=7;     //to define the upper left boundry of mouse.
 i.x.cx=x1;
 i.x.dx=x2;
 int86(0x33,&i,&o);
 i.x.ax=8;   //to define the bottom right boundry of mouse.
 i.x.cx=y1;
 i.x.dx=y2;
 int86(0x33,&i,&o);
}
void getmousepos(int *buttonm,int *x, int *y){
 i.x.ax=3; //to move mouse.
 int86(0x33,&i,&o);
 *buttonm=o.x.bx;
 *x=o.x.cx;
 *y=o.x.dx;
}

void changecursor(int *shape)
{
  i.x.ax=9;
  i.x.bx=0;
  i.x.cx=0;
  i.x.dx=(unsigned)shape;
  segread(&s);
  s.es=s.ds;
  int86x(0x33,&i,&o,&s);
}
//end mouse function

 int menu(int select)
{
  char ch, menu[4][10]={"FILE","EDIT","HELP","ABOUT"};
  char date[11];
  struct date da;
  hidemouse();
  setfillstyle(1,8);
  setcolor(15);
  line(0,19,getmaxx(),19);
  line(0,20,2,40);
  setcolor(0);
  bar(0,20,getmaxx(),40);
  getdate(&da);
  setcolor(0);
  setcolor(WHITE);
  settextstyle(0,0,2);
  outtextxy(10,23,menu[0]);
  outtextxy(100,23,menu[1]);
  outtextxy(200,23,menu[2]);
  outtextxy(300,23,menu[3]);

    showmouse();
    switch(select)
    {
    case 0:
    hidemouse();
    setfillstyle(9,9);
    setcolor(15);
    bar(8,20,90,40);
    outtextxy(20,21,menu[0]);
    break;
   case 1:
    hidemouse();
    setfillstyle(9,9);
    setcolor(15);
    bar(90,20,170,40);
    outtextxy(100,23,menu[1]);
    break;
    case 2:
    hidemouse();
    setfillstyle(9,9);
    setcolor(15);
    bar(170,20,280,40);
    outtextxy(200,23,menu[2]);
    break;
    case 3:
    hidemouse();
    setfillstyle(9,9);
    setcolor(15);
    bar(280,20,390,40);
    outtextxy(300,23,menu[3]);
    break;
 }
  sprintf(date,"%02d/%02d/%d",da.da_day,da.da_mon,da.da_year);
  setcolor(7);
  outtextxy(getmaxx()-170,21,date);
  showmouse();
 return select;
}

int dropmenu(char menu[7][20],int x1,int y1,int x2,int y2,int opt){
 int i;
 char ch;
 setfillstyle(1,7);
 setcolor(15);
 hidemouse();
 line(x1,y1,x2,y1);
 line(x1,y1,x1,y2);
 setcolor(0);
 line(x2,y1,x2,y2);
 line(x1,y2,x2,y2);
 bar(x1+1,y1+1,x2-1,y2-1);
 rectangle(x1+5,y1+5,x2-5,y2-5);
 settextstyle(0,0,1);
 for(i=0;i<(y2-y1-15)/14;i++){
  if(i==opt){
  setcolor(15);
  setfillstyle(1,3);
  bar(x1+10,y1+8+(i*14),x2-10,y1+20+(i*14));
  outtextxy(x1+15,y1+10+(i*14),menu[i]);
  }else{
   setcolor(0);
   outtextxy(x1+15,y1+10+(i*14),menu[i]);
  }
 }
 showmouse();
 delay(100);
 return opt;
}

int File()
{
bkcolor();
 setbkcolor(0);

 int opt=-1,j,close;
 char menu[4][20]={"New","Open","Save","Quit"};
 close=1;
 dropmenu(menu,10,40,131,120,opt);

 do{
  showmouse();
  getmousepos(&buttonm,&xm,&ym);

  if(xm>=10+10&&xm<=131-10&&ym>=40+8&&ym<=120-8&&buttonm==1)
  {
   for(j=0;j<(120-40-8)/14;j++)
   if((ym-40-8)/14==j){
   opt=j;
   break;
  }
   dropmenu(menu,10,40,131,120,opt);
   switch(opt)
   {
    case 0: Newbox(); break;
    case 1: Open(); break;
    case 2: fclose(p);  bkcolor(); break;
    case 3: delay(100); cleardevice(); closegraph(); exit(0);
   }
  }else if(xm>=10&&xm<=34&&ym>=18&&ym<=32&&buttonm==1){
   dropmenu(menu,10,40,131,120,opt);
   continue;
  }else if(buttonm==1){
   break;
  }
 }while(close);
// clrwin();
 return 0;
}

int Edit()
{
  bkcolor();
  char menu[3][20]={"Delete","Font color","Exit"};
 int opt=-1,j,close;
 close=1;

 dropmenu(menu,90,40,200,100,opt);
 do{
  showmouse();
  getmousepos(&buttonm,&xm,&ym);
  if(xm>=90+10&&xm<=211-10&&ym>=40+8&&ym<=130-8&&buttonm==1){
   for(j=0;j<(130-40-8)/14;j++)
    if((ym-40-8)/14==j)
    {
     opt=j;
     break;
    }
       //dropmenu(menu,90,40,131,120,opt);

   dropmenu(menu,90,40,200,100,opt);
   switch(opt){
   case 0:deletebox();break;
   case 1:fontbox();break;
   case 2:exit(0);break;
   }
  }
  else if(xm>=40&&xm<=94&&ym>=18&&ym<=32&&buttonm==1){
  //   dropmenu(menu,90,40,131,120,opt);

  dropmenu(menu,90,40,200,100,opt);
  continue;
  }
  else if(buttonm==1){
   break;
  }
 }while(close);

 return 1;
}
void drawwindow(char head[30],int x1, int y1, int x2, int y2, int c){
 hidemouse();
 setfillstyle(1,7);
 bar(x1,y1-14,x2,y1-2);
 setfillstyle(1,c);
 bar(x1,y1,x2,y2);
 setcolor(15);
 line(x1-1,y1-15,x2+1,y1-15);
 line(x1-1,y1-15,x1-1,y2+1);
 setcolor(0);
 line(x2+1,y1-14,x2+1,y2+1);
 line(x1-1,y2+1,x2+1,y2+1);
 line(x1,y1-1,x2,y1-1);
 setcolor(15);
 rectangle(x1+5,y1+5,x2-5,y2-5);
 setcolor(0);
 settextstyle(0,0,1);
 outtextxy((x2+x1-textwidth(head))/2,y1-12,head);
 showmouse();

}

int about()
{
 bkcolor();
 char str[3][35]={"","              Notepad "};
 int midx=getmaxx()/2,close;
 int midy=getmaxy()/2;
 close=1;
 drawwindow("About", 170, 148, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 settextstyle(0,0,1);
 setcolor(15);
 for(int i=0;i<2;i++)
 outtextxy(170+15,148+20+(i*20),str[i]);
 outtextxy(170+15,148+20+40,"           Version : 1.0 ");
 outtextxy(170+15,148+20+60,"        All Right Reserved");
 outtextxy(170+15,148+20+ 80,"      Coded by Apoorv Verma");
 outtextxy(170+15,148+20+ 100,"Who is Apoorv Verma ? :Web Developer");
 outtextxy(170+15,148+20+ 120,"Open Source Contributor , YouTuber");
  outtextxy(170+15,148+20+ 140,"Programmer , Progeek , Dreamer !");
  press("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,7);

   do{
  getmousepos(&buttonm,&xm,&ym);
  if(buttonm==1)
  {
   if(xm>=midx-30&&ym>=midy*3/2-22&&xm<=midx+30&&ym<=midy*3/2-8)
   {
    press("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,3);   //ok coding
    delay(100);
     clrwin();
    close=0;
    }
  }
}while(close);
bkcolor();
 return 4;
}

void press(char name[15],int x1,int y1,int x2 ,int y2,int c)
{
 setfillstyle(1,c);
 setcolor(15);
 hidemouse();
 line(x1,y1,x2,y1);
 line(x1,y1,x1,y2);
 setcolor(0);
 line(x2,y1,x2,y2);
 line(x1,y2,x2,y2);
 bar(x1+1,y1+1,x2-1,y2-1);
 outtextxy((x2+x1-textwidth(name))/2,(y2+y1-textheight(name))/2,name);
 showmouse();
}

int Help()
{
 bkcolor();
 int midx=getmaxx()/2,close;
 int midy=getmaxy()/2;
 close=1;
 drawwindow("Contact", 170, 148, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 settextstyle(0,0,1);
 setcolor(15);
 for(int i=0;i<2;i++);
 outtextxy(170+15,148+20+20,"email : vapoorve@gmail.com");
 outtextxy(170+15,148+20+40,"Facebook Id: Apoorv verma");
 outtextxy(170+15,148+20+60,"Page: www.facebook.com/progeeks8055");
 outtextxy(170+15,148+20+80,"Instagram : Apoorv786");
 outtextxy(170+15,148+20+100,"YouTube : Progeeks (channel Name)");
 press("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,7);

do{
  getmousepos(&buttonm,&xm,&ym);
  if(buttonm==1)
  {
   if(xm>=midx-30&&ym>=midy*3/2-22&&xm<=midx+30&&ym<=midy*3/2-8)
    {
    press("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,3);   //ok coding
    delay(100);
    clrwin();
    close=0;
    }
  }
 }while(close);
 bkcolor();
 return 4;
}
void newf(char namearray[20])
{
 clrwin();
 //int font_size,text_style,text_color
     int j=0,menu1=-1;
     int change=0;
      char ch,text[2]="";
      int key,line=70;

      setbkcolor(fon);
      p=fopen(strcat(namearray,".txt"),"w");

       setcolor(fon);
     //  settextstyle(text_style,0,font_size);
       moveto(10,line);

   do{


    //{moveto(10,ym+textheight(text));}

    key = bioskey(0);
    ch = key & 0xFF;

     if(key==7181)
    {
     line=line+20;
     moveto(10,line);

      }

    if(change==73)
    {
     line=line+20;
     moveto(10,line);
    change=0;
    }


    if(!iscntrl(ch))
   {
    text[0] = ch;
    text[1] = '\0';
    outtext(text);
    change++;
    }

  putc(ch,p);


    //delay(100);
    getmousepos(&buttonm,&xm,&ym);

    if(buttonm==1)
   do
    {
     getmousepos(&buttonm,&xm,&ym);
     if(buttonm==1)
     {
      if((0<=ym)&&(20>=ym)&&(getmaxx()>=xm)&&((getmaxx()-30)<=xm))
      {exit(0);}
      else if((20<=ym)&&(40>=ym)&&(8<=xm)&&(90>=xm))   //File
      { menu1=0; }
      else if((20<=ym)&&(40>=ym)&&(90<=xm)&&(170>=xm))    //edit
      { menu1=1; }
      else if((20<=ym)&&(40>=ym)&&(170<=xm)&&(280>=xm))       //help
      { menu1=2; }
      else if((20<=ym)&&(40>=ym)&&(280<=xm)&&(390>=xm))       //about
      { menu1=3; }
      else
      {menu1=-1;}
      menu(menu1);
     switch(menu1)
     {
     case 0:File();break;
     case 1:Edit();break;
     case 2:Help();break;
     case 3:about();break;
     }
    }
 }while(1);

}while(1);

}

void bkcolor()
  {
      setfillstyle(1,BLUE);
      bar(0,40,getmaxx(),getmaxy());
  }//backgroungcolor
int Open()
{
 char namearray[20];
 bkcolor();
 int midx=getmaxx()/2,close;
 int midy=getmaxy()/2,count=0,test=0;
 close=1;
 drawwindow("Open", 170, 148, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 settextstyle(0,0,1);
// for(int i=0;i<2;i++)
 setcolor(15);
 outtextxy(170+15,148+20+40,"File Name :");
 inputbox(170+110,148+20+40,20,15);

 setcolor(15);
 outtextxy(170+15,148+20+60,"Notic:- we can enter File name");
 outtextxy(170+15,148+20+80,"and also File location........");
 outtextxy(170+15,148+20+100,"press => Esc <= to cancel.  ");
 outtextxy(170+15,148+20+120,"press => Enter <= to Open.  ");

press("Exit",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
 press("Cancel",midx+40,midy*3/2-22,midx+100,midy*3/2-8,7);

   do{

   getmousepos(&buttonm,&xm,&ym);
   if(buttonm==1)
   {
    if(xm>=170+110&&ym>=148+20+40&&xm<=442&&ym<=148+20+40+2)
    {
     delay(100);

    output();
    close=0;

    }

    if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8)
    {
     press("Exit",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);

     delay(100);
      close=0;
     bkcolor();

    }
    if(xm>=midx+40&&ym>=midy*3/2-22&&xm<=midx+100&&ym<=midy*3/2-8)
    {
     press("Cancel",midx+40,midy*3/2-22,midx+100,midy*3/2-8,3);

     delay(100);

    close=0;

   }

 }
}while(close);
 return 4;

}

void inputbox(int x,int y,int limit,int bkc)
{
 hidemouse();
 setfillstyle(1,bkc);
 bar(x-2,y-2,x+limit*8+2,y+8);
 setcolor(0);
 line(x-3,y-3,x-3,y+9);
 line(x-3,y-3,x+limit*8+2,y-3);
 showmouse();
}

int Newbox()
{
 char namearray[20];
 bkcolor();
 int midx=getmaxx()/2,close;
 int midy=getmaxy()/2,count=0,test=0;
 close=1;
 drawwindow("NEW", 170, 148, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 settextstyle(0,0,1);
// for(int i=0;i<2;i++)
 setcolor(15);
 outtextxy(170+15,148+20+40,"File Name :");
 inputbox(170+110,148+20+40,20,15);

 setcolor(15);
 outtextxy(170+15,148+20+60,"Notic:- we can enter File name");
 outtextxy(170+15,148+20+80,"and also File location........");
 outtextxy(170+15,148+20+100,"press => Esc <= to cancel.  ");
 outtextxy(170+15,148+20+120,"press => Enter <= to Creat.  ");

press("Exit",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
 press("Cancel",midx+40,midy*3/2-22,midx+100,midy*3/2-8,7);

   do{

   getmousepos(&buttonm,&xm,&ym);
   if(buttonm==1)
   {
    if(xm>=170+110&&ym>=148+20+40&&xm<=442&&ym<=148+20+40+2)
    {
     delay(100);
     input();
     close=0;

    }

    if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8)
    {
     press("Exit",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);

     delay(100);
      close=0;
     bkcolor();

    }
    if(xm>=midx+40&&ym>=midy*3/2-22&&xm<=midx+100&&ym<=midy*3/2-8)
    {
     press("Cancel",midx+40,midy*3/2-22,midx+100,midy*3/2-8,3);

     delay(100);

    close=0;

   }

 }
}while(close);
 return 4;
}

int input()
{
      char ch,text[2]="";
      int key,close=0,i=0,count=0;
      char namearray[20]="";


moveto(170+110,148+20+40);

do{
    key = bioskey(0);
    if(key==7181)
    {
    newf(namearray);}

    if(key==283)
    {
    bkcolor();

    break;
    }

    if(key==14624)
    {
    count++;
    }

     ch = key & 0xFF;


    if(count<=20)
    {


      if(!iscntrl(ch))
   {
	if(count<=10)
	{
	text[0] = ch;
	text[1] = '\0';
	outtext(text);
	namearray[i]=text[0];
	i++;
	count++;
	}
    }
    }


}while(1);

return i;
}
void openf(char namearray[20])
{
 clrwin();
 //int font_size,text_style,text_color
     int j=0,menu1=-1;
     char ch,text[2]="";
     int key;

      setbkcolor(fon);
      p=fopen(strcat(namearray,".txt"),"a+");

       setcolor(fon);
     //  settextstyle(text_style,0,font_size);
       moveto(10,70);
       while((ch=getc(p))!=EOF)
       {
       text[0] = ch;
       text[1] = '\0';
       outtext(text);

       }


do{


    //{moveto(10,ym+textheight(text));}

    key = bioskey(0);
    ch = key & 0xFF;

    if(!iscntrl(ch))
   {
    text[0] = ch;
    text[1] = '\0';
    outtext(text);
    }

  putc(ch,p);


    //delay(100);
    getmousepos(&buttonm,&xm,&ym);

    if(buttonm==1)
   do
    {
     getmousepos(&buttonm,&xm,&ym);
     if(buttonm==1)
     {
      if((0<=ym)&&(20>=ym)&&(getmaxx()>=xm)&&((getmaxx()-30)<=xm))
      {exit(0);}
      else if((20<=ym)&&(40>=ym)&&(8<=xm)&&(90>=xm))   //File
      { menu1=0; }
      else if((20<=ym)&&(40>=ym)&&(90<=xm)&&(170>=xm))    //edit
      { menu1=1; }
      else if((20<=ym)&&(40>=ym)&&(170<=xm)&&(280>=xm))       //help
      { menu1=2; }
      else if((20<=ym)&&(40>=ym)&&(280<=xm)&&(390>=xm))       //about
      { menu1=3; }
      else
      {menu1=-1;}
      menu(menu1);
     switch(menu1)
     {
     case 0:File();break;
     case 1:Edit();break;
     case 2:Help();break;
     case 3:about();break;
     }
    }
 }while(1);

}while(1);

}


int output()
{
      char ch,text[2]="";
      int key,close=0,i=0,count=0;
      char namearray[20]="";


moveto(170+110,148+20+40);

do{
    key = bioskey(0);
    if(key==7181)
    {
    openf(namearray);
    }

    if(key==283)
    {
    bkcolor();

    break;
    }

    if(key==14624)
    {
    count++;
    }

     ch = key & 0xFF;


    if(count<=20)
    {


      if(!iscntrl(ch))
   {
	if(count<=10)
	{
	text[0] = ch;
	text[1] = '\0';
	outtext(text);
	namearray[i]=text[0];
	i++;
	count++;
	}
    }
    }








}while(1);

return i;
}


//:::::::::::::::::::::::Delete functions::::::::::::::::::::::::::::::

int deletebox()
{
 char namearray[20];
 bkcolor();
 int midx=getmaxx()/2,close;
 int midy=getmaxy()/2,count=0,test=0;
 close=1;
 drawwindow("Delete", 170, 148, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 settextstyle(0,0,1);
// for(int i=0;i<2;i++)
 setcolor(15);
 outtextxy(170+15,148+20+40,"File Name :");
 inputbox(170+110,148+20+40,20,15);

 setcolor(15);
 outtextxy(170+15,148+20+60,"Notic:- we can enter File name");
 outtextxy(170+15,148+20+80,"and also File location........");
 outtextxy(170+15,148+20+100,"press => Esc <= to cancel.  ");
 outtextxy(170+15,148+20+120,"press => Enter <= to Delete.");

press("Exit",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
 press("Cancel",midx+40,midy*3/2-22,midx+100,midy*3/2-8,7);

   do{

   getmousepos(&buttonm,&xm,&ym);
   if(buttonm==1)
   {
    if(xm>=170+110&&ym>=148+20+40&&xm<=442&&ym<=148+20+40+2)
    {
     delay(100);
     deletef();
     close=0;

    }

    if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8)
    {
     press("Exit",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);

     delay(100);
      close=0;
     bkcolor();

    }
    if(xm>=midx+40&&ym>=midy*3/2-22&&xm<=midx+100&&ym<=midy*3/2-8)
    {
     press("Cancel",midx+40,midy*3/2-22,midx+100,midy*3/2-8,3);

     delay(100);

    close=0;

   }

 }
}while(close);
 return 4;
}
int deletef()
{
      char ch,text[2]="";
      int key,close=0,i=0,count=0;
      char namearray[20]="";


moveto(170+110,148+20+40);

do{
    key = bioskey(0);
    if(key==7181)
    {
      remove(strcat(namearray,".txt"));
      remove(namearray);
      close=0;
      deleted();
      bkcolor();

      break;
    }

    if(key==283)
    {
    bkcolor();

    break;
    }

    if(key==14624)
    {
    count++;
    }

     ch = key & 0xFF;


    if(count<=20)
    {


      if(!iscntrl(ch))
   {
	if(count<=10)
	{
	text[0] = ch;
	text[1] = '\0';
	outtext(text);
	namearray[i]=text[0];
	i++;
	count++;
	}
    }
    }


}while(1);

return i;
}

int deleted()
{
 char namearray[20];
 int key;
 bkcolor();
 int midx=getmaxx()/2,close;
 int midy=getmaxy()/2,count=0,test=0;
 //close=1;



  drawwindow(" ", 170, 148, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 settextstyle(0,0,1);
// for(int i=0;i<2;i++)
 setcolor(15);
 setcolor(15);
 outtextxy(170+15,148+20+60," ::YOUR FILE HAS BEEN DELETED::");
 outtextxy(170+15,148+20+100,"press => Esc <= to exit program.");
 outtextxy(170+15,148+20+120,"press => Enter <= to cancel.");

 press("Exit",midx-90,midy*3/2-22,midx-30,midy*3/2-8,7);
 press("Cancel",midx+40,midy*3/2-22,midx+100,midy*3/2-8,7);

 do{

   getmousepos(&buttonm,&xm,&ym);
   if(buttonm==1)
   {

    if(xm>=midx-90&&ym>=midy*3/2-22&&xm<=midx-30&&ym<=midy*3/2-8)
    {
     press("Exit",midx-90,midy*3/2-22,midx-30,midy*3/2-8,3);

     delay(100);
      bkcolor();
       close=0;
      exit(0);
    }
    if(xm>=midx+40&&ym>=midy*3/2-22&&xm<=midx+100&&ym<=midy*3/2-8)
    {
     press("Cancel",midx+40,midy*3/2-22,midx+100,midy*3/2-8,3);

     delay(100);
     close=0;

   }

 }

   if(key==7181)
    {

      delay(100);
      close=0;
     }
}while(close);

    return 4;
}

//::::::::::::::::::::::: End Delete functions :::::::::::::::::::::::::::

int fontbox()
{
 char namearray[20];
 bkcolor();
 int midx=getmaxx()/2,close;
 int midy=getmaxy()/2,count=0,test=0;
 close=1;
 drawwindow("Font Color", 170, 148, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 settextstyle(0,0,1);
// for(int i=0;i<2;i++)
 setcolor(15);
 outtextxy(170+15,148+20+40,"File Name :");
 inputbox(170+110,148+20+40,20,15);

 setcolor(15);
 outtextxy(170+15,148+20+60,"0=>black 1=>blue 2=>green 3=>aqua");
 outtextxy(170+15,148+20+80,"4=>red 5=>purple");
 outtextxy(170+15,148+20+100,"press => Esc <= to cancel.  ");
 outtextxy(170+15,148+20+120,"press => Enter <= to Delete.");

  press("Cancel",midx-30,midy*3/2-22,midx+30,midy*3/2-8,7);


   do{

   getmousepos(&buttonm,&xm,&ym);
   if(buttonm==1)
   {
    if(xm>=170+110&&ym>=148+20+40&&xm<=442&&ym<=148+20+40+2)
    {
     delay(100);
     fontf();
     close=0;

    }
       if(xm>=midx-30&&ym>=midy*3/2-22&&xm<=midx+30&&ym<=midy*3/2-8)
   {

    press("Cancel",midx-30,midy*3/2-22,midx+30,midy*3/2-8,3);   //cancel coding
    delay(100);
    clrwin();
    close=0;

    }


 }
}while(close);
 return 4;
}
int fontf()
{
      char ch,text[2]="";
      int key,close=0,i=0,count=0;
      char namearray[20]="";


moveto(170+110,148+20+40);

do{
    key = bioskey(0);
    if(key==7181)
    {
      fon = atoi(namearray);
      cfont();
      close=0;
      deleted();
      bkcolor();

      break;
    }

    if(key==283)
    {
    bkcolor();

    break;
    }

    if(key==14624)
    {
    count++;
    }

     ch = key & 0xFF;


    if(count<=20)
    {


      if(!iscntrl(ch))
   {
	if(count<=10)
	{
	text[0] = ch;
	text[1] = '\0';
	outtext(text);
	namearray[i]=text[0];
	i++;
	count++;
	}
    }
    }


}while(1);

return i;
}

int cfont()
{
 char namearray[20];
 int key;
 bkcolor();
 int midx=getmaxx()/2,close;
 int midy=getmaxy()/2,count=0,test=0;
 //close=1;



  drawwindow("ALL SET", 170, 148, (getmaxx()*3)/4, (getmaxy()*3)/4,1 );
 settextstyle(0,0,1);
// for(int i=0;i<2;i++)
 setcolor(15);
 setcolor(15);
 outtextxy(170+15,148+20+60,"   ::YOUR FONT COLOR HAS BEEN SET::");
 outtextxy(170+15,148+20+100,"   Click => OK <= to CLOSE THIS TAB");

  press("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,7);

 do{

   getmousepos(&buttonm,&xm,&ym);
   if(buttonm==1)
   {

   if(xm>=midx-30&&ym>=midy*3/2-22&&xm<=midx+30&&ym<=midy*3/2-8)
   {
    press("OK",midx-30,midy*3/2-22,midx+30,midy*3/2-8,3);   //ok coding
    delay(100);
    close=0;
    }
    bkcolor();

     }

   if(key==7181)
    {
      delay(100);
      close=0;
     }
}while(close);
   bkcolor();
    return 4;
}

/*
@Author: Apoorv verma 
@Apoorve8055
YT : https://www.youtube.com/watch?v=rDqFclKCCvY
Aug 2018
*/
