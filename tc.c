

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////
#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define PATH_MAX 2500
#define MYOS 2
#elif defined(_WIN64)
#define PATH_MAX 2500
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif



////////////////////////////
///  TC rocks
///  Turbo Commander
////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>



//////////////////////////
// ncurses
//#include <ncurses.h>
//////////////////////////
#if defined(__linux__)
#define MYOS 1
#include <ncurses.h>
#elif defined(_WIN32)
#define MYOS 2
#include <curses.h>
#elif defined(_WIN64)
#define MYOS 3
#include <curses.h>
#elif defined(__unix__)
#define MYOS 4
#include <ncurses.h>
#else
#define MYOS 0
#include <ncurses.h>
#endif




////////////////////////////////
void ncurses_runcmd( char *thecmd   )
{
       char rncmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( rncmdi , "  " , PATH_MAX );
       strncat( rncmdi , thecmd , PATH_MAX - strlen( rncmdi ) -1 );
       strncat( rncmdi , " " , PATH_MAX - strlen( rncmdi ) -1 );
       system( rncmdi );
       reset_prog_mode();
}



////////////////////////////////
void ncurses_runwith( char *thecmd , char *thestrfile  ) //thecmd first
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       printf( "<NDESK CMD: Command...>\n" );
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thestrfile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\" " , PATH_MAX - strlen( cmdi ) -1 );
       printf( "<NDESk CMD: %s>\n", cmdi );
       system( cmdi );
       reset_prog_mode();
}



///////////////// new
char *fextension(char *str)
{ 
    char ptr[strlen(str)+1];
    int i,j=0;
    //char ptrout[strlen(ptr)+1];  
    char ptrout[25];

    if ( strstr( str, "." ) != 0 )
    {
      for(i=strlen(str)-1 ; str[i] !='.' ; i--)
      {
        if ( str[i] != '.' ) 
            ptr[j++]=str[i];
      } 
      ptr[j]='\0';

      j = 0; 
      for( i=strlen(ptr)-1 ;  i >= 0 ; i--)
            ptrout[j++]=ptr[i];
      ptrout[j]='\0';
    }
    else
     ptrout[0]='\0';

    size_t siz = sizeof ptrout ; 
    char *r = malloc( sizeof ptrout );
    return r ? memcpy(r, ptrout, siz ) : NULL;
}




char *fbasename(char *name)
{
  char *base = name;
  while (*name)
    {
      if (*name++ == '/')
	{
	  base = name;
	}
    }
  return (base);
}






char searchitem[PATH_MAX];
int  tc_show_hidden     = 0; 
int  tc_refresh_reloaddir = 1; 
int rows, cols;  


void gfxhline( int y1 )
{
    int trows, tcols;
    getmaxyx( stdscr, trows , tcols);
    int foo;
    for( foo = 0 ; foo <= tcols-1 ; foo++) 
         mvaddch( y1 , foo , ' ' );
}




void gfxframe( int y1, int x1, int y2, int x2 )
{
    int foo, fooy , foox ;
    foo = x1;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
        mvaddch( fooy , foo , ACS_VLINE );
    foo = x2;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
         mvaddch( fooy , foo , ACS_VLINE );
    foo = y1;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    foo = y2;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    mvaddch( y1 , x1 , ACS_ULCORNER );
    mvaddch( y1 , x2 , ACS_URCORNER );
    mvaddch( y2 , x1 , ACS_LLCORNER );
    mvaddch( y2 , x2 , ACS_LRCORNER );
}


void colornorm()
{
    attroff( A_REVERSE );
    attroff( A_BOLD );
    color_set( 0, NULL );
}






//////////////////////////
//////////////////////////
//////////////////////////
//////////////////////////
void win_keypress()
{
  int win_key_gameover = 0;
  int ch = 0;
  while( win_key_gameover == 0)
  {
       erase();
       mvprintw( 0, 0, "Key Win Content" );
       mvprintw( 5,5, "%d", ch );
       ch = getch();
       if ( ch == 'i' ) 
           win_key_gameover = 1 ;
       else if ( ch == 'q' ) 
           win_key_gameover = 1 ;
  }
}




void crossgraphvga_colors(void)
{
  color_set( 7 , NULL ); attroff( A_REVERSE ); mvprintw( 2,2, "Darker  ;  Brighter (bold)" );
  
  getmaxyx( stdscr, rows, cols );

  int x = 5; int i = 1;
  for( i = 0; i <= rows-1 ; i++)  //ncurses as by default 8 colors
  { 
    mvprintw( x, 2 , "%d ", i );

    attron( A_REVERSE );
    attroff( A_BOLD );
    color_set( i , NULL );
    printw( "%d", i );
    colornorm(); printw( " " );

    attroff( A_REVERSE );
    attron(  A_BOLD );
    color_set( i , NULL );
    printw( " ; %d", i );
    colornorm(); printw( " " );

    // reverse and bold
    color_set( i , NULL );
    attron( A_REVERSE );
    attroff( A_BOLD ); //for the console
    attron(  A_BLINK ); //for the console
    printw( " R%d", i );
    colornorm(); printw( " " );


    color_set( i , NULL );
    attron(  A_REVERSE );
    attron(  A_BOLD ); //for the console
    attroff( A_BLINK ); //for the console
    printw( " Rev,Bold%d", i );
    colornorm(); printw( " " );

    color_set( i , NULL );
    attron(  A_REVERSE );
    attron(  A_BOLD ); //for the console
    attron(  A_BLINK ); //for the console
    printw( " Rev,Bold,Blink%d", i );
    colornorm(); printw( " " );

    x += 1; 
    colornorm(); printw( " " );
    color_set( 7 , NULL ); printw( " (#.%d)", i );

    mvprintw( rows-1, cols-8, "|%d,%d|" , rows, cols );
  } 

  refresh();
  x += 2; 
  attroff( A_REVERSE );
  color_set( 7, NULL ); mvprintw(  x, 5 , "<Press Key>" );

  // clean up
  attroff( A_REVERSE ); 
  attroff( A_BOLD ); 
  attroff( A_BLINK ); 
  color_set( 0, NULL ); 
}





void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) 
    {
        if (entry->d_type == DT_DIR) 
	{
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;


            snprintf( path, sizeof(path), "%s/%s", name, entry->d_name);
            //printf("%*s[%s]\n", indent, "", entry->d_name);

            listdir( path, indent + 2);
        } 
	else 
	{
	    if ( strstr( entry->d_name , searchitem ) != 0 ) 
	    {
              printf("DIR %s\n", name );
              //printf("%*s- %s (Found)\n", indent, "", entry->d_name);
              printf("%*s- %s\n", indent, "", entry->d_name);
	    }
        }
    }
    closedir(dir);
}










/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}












int gameselection = 1;
int gamescrolly = 0;
int gamedirfcheck = 1;
char gamefilter[PATH_MAX];
char gamefilter_previous[PATH_MAX];
char fileselection[PATH_MAX];



void selectioninit()
{
    strncpy( fileselection, "" , PATH_MAX );
}







/////////////////// MAIN LIST FILES (MVPRINTW)
void mvlistprint(const char *name, int indent, char *searchitem )
{
    int posy = 1; 
    getmaxyx( stdscr, rows, cols);

    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    int entryselnb = 0;  int dircondition ; 
    unsigned int entrycounter = 0;
    while ((entry = readdir(dir)) != NULL) 
    {
        attroff( A_REVERSE );

        entrycounter++;
        if ( entrycounter <= gamescrolly )
              continue;

        dircondition = 0; 
        if ( entry->d_type == DT_DIR ) 
           dircondition = 1; 
        else if ( entry->d_type == 0 ) 
         if ( gamedirfcheck == 1 )
          if ( posy <= rows-3 )
           if ( fexist( entry->d_name ) == 2 )
               dircondition = 1;

        if ( dircondition == 1 )
	{
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            if ( tc_show_hidden == 0 )
             if ( entry->d_name[0] ==  '.' ) 
                continue;

            snprintf( path, sizeof(path), "%s/%s", name, entry->d_name);

            //listdir( path, indent + 2);
	    if ( strstr( entry->d_name , searchitem ) != 0 ) 
            if ( posy <= rows-3 )
            {
              entryselnb++;
              if ( gameselection == entryselnb ) attron( A_REVERSE );
              color_set( 6, NULL );
              mvprintw( posy++, 0 +1, "[%d] [%s]", entry->d_type, entry->d_name );
              if ( gameselection == entryselnb ) 
                  if ( strcmp( entry->d_name , "" ) != 0 )
                   strncpy( fileselection, entry->d_name , PATH_MAX );
             }

        } 
	else 
	{

            if ( tc_show_hidden == 0 )
              if ( entry->d_name[0] ==  '.' ) 
                continue;

	    if ( strstr( entry->d_name , searchitem ) != 0 ) 
	    {


              //printf("DIR %s\n", name );
              //printf("%*s- %s\n", indent, "", entry->d_name);
              if ( posy <= rows-3 )
              {
                 entryselnb++;
                 if ( gameselection == entryselnb ) attron( A_REVERSE );
                 color_set( 4, NULL );
                 //mvprintw( posy++, 0 +1, "%s", entry->d_name );
                 mvprintw( posy++, 0 +1, "[%d] %s", entry->d_type, entry->d_name );
                 if ( gameselection == entryselnb ) 
                  if ( strcmp( entry->d_name , "" ) != 0 )
                   strncpy( fileselection, entry->d_name , PATH_MAX );
              }
	    }
        }

    }
    closedir(dir);
}








////////////////////////////////////////////////////////////////////
char *strrlf(char *str) 
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}
////////////////////////////////////////////////////////////////////
char *strcut( char *str , int myposstart, int myposend )
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}





////////////////////////////////
void nvim( char *thecmd   )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , " vi   " , PATH_MAX );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
}


////////////////////////////////
void nrunwith( char *theprg , char *thefile )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , "   " , PATH_MAX );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , theprg , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "  " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thefile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
}


////////////////////////////////
void nruncmd( char *thecmd   )
{
       char cmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
       reset_prog_mode();
}









////////////////////////
////////////////////////
////////////////////////
////////////////////////
char *strninput( char *myinitstring )
{

   int strninput_gameover = 0; 
   char strmsg[PATH_MAX];
   char charo[PATH_MAX];
   strncpy( strmsg, myinitstring , PATH_MAX );

   int ch ;  int foo ; 
   int fooj; 
   while ( strninput_gameover == 0 )
   {
                  getmaxyx( stdscr, rows, cols);
                  attroff( A_REVERSE );
                  for ( fooj = 0 ; fooj <= cols-1;  fooj++)
                  {
                    //mvaddch( rows-2, fooj , ' ' );
                    mvaddch( rows-1, fooj , ' ' );
                  }
                  mvprintw( rows-1, 0, ":> %s" , strrlf( strmsg ) );
                  attron( A_REVERSE );
                  printw( " " );
                  attroff( A_REVERSE );
                  attroff( A_REVERSE );
                  attroff( A_BOLD );
                  refresh() ; 

                  ch = getch();
                  /*
		  if ( ch == KEY_BACKSPACE )  // not working on FreeBSD
		  {
		      strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );
	          }
   
		  //if ( ch == 8 )  // for linux
		  if ( ch == 263 )    // for FreeBSD
		  {
		      strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );
	 	  } 
                  */

#if defined(__linux__)
  //if ( ch == 8 )    // for Linux
  if ( ch == 263 )    // for Linux under the console tty1, without screen
    strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );
#elif defined(_WIN32)
// what?
#elif defined(_WIN64)
// what?
#elif defined(__unix__)
  if ( ch == 263 )    // for FreeBSD but not working
    strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );

  else if ( ch == 8 )    // for FreeBSD but maybe better working
    strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );

#endif

		  else if ( ch == 4 ) 
		  {
			   strncpy( strmsg, ""  ,  PATH_MAX );
		  }
		  else if ( ch == 27 ) 
		  {
			   strncpy( strmsg, ""  ,  PATH_MAX );
		  }
	          else if (
			(( ch >= 'a' ) && ( ch <= 'z' ) ) 
		        || (( ch >= 'A' ) && ( ch <= 'Z' ) ) 
		        || (( ch >= '1' ) && ( ch <= '9' ) ) 
		        || (( ch == '0' ) ) 
		        || (( ch == '~' ) ) 
		        || (( ch == '!' ) ) 
		        || (( ch == '&' ) ) 
		        || (( ch == '=' ) ) 
		        || (( ch == ':' ) ) 
		        || (( ch == ';' ) ) 
		        || (( ch == '<' ) ) 
		        || (( ch == '>' ) ) 
		        || (( ch == ' ' ) ) 
		        || (( ch == '|' ) ) 
		        || (( ch == '#' ) ) 
		        || (( ch == '?' ) ) 
		        || (( ch == '+' ) ) 
		        || (( ch == '/' ) ) 
		        || (( ch == '\\' ) ) 
		        || (( ch == '.' ) ) 
		        || (( ch == '$' ) ) 
		        || (( ch == '%' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == ',' ) ) 
		        || (( ch == '{' ) ) 
		        || (( ch == '}' ) ) 
		        || (( ch == '(' ) ) 
		        || (( ch == ')' ) ) 
		        || (( ch == ']' ) ) 
		        || (( ch == '[' ) ) 
		        || (( ch == '*' ) ) 
		        || (( ch == '"' ) ) 
		        || (( ch == '@' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '_' ) ) 
		        || (( ch == '^' ) ) 
		        || (( ch == '\'' ) ) 
	             ) 
		  {
                           foo = snprintf( charo, PATH_MAX , "%s%c",  strmsg, ch );
			   strncpy( strmsg,  charo ,  PATH_MAX );
		  }
		  else if ( ch == 10 ) 
		  {
                        strninput_gameover = 1;
		  }
     }
     char ptr[PATH_MAX];
     strncpy( ptr, strmsg, PATH_MAX );
     size_t siz = sizeof ptr ; 
     char *r = malloc( sizeof ptr );
     return r ? memcpy(r, ptr, siz ) : NULL;
}



///////////////////////////////
///////////////////////////////
void nappendclip( char *thefile )
{
     char fileinputsrc[PATH_MAX];
     strncpy( fileinputsrc, "", PATH_MAX );
     strncat( fileinputsrc , getenv( "HOME" ) , PATH_MAX - strlen( fileinputsrc ) -1 );
     strncat( fileinputsrc , "/.clipboard" , PATH_MAX - strlen( fileinputsrc ) -1 );

     FILE *fp;  
     fp = fopen( fileinputsrc , "ab+" );
       fputs( "!fig{", fp );
       fputs( thefile , fp );
       fputs( "}" , fp );
       fputs( "\n" , fp );
     fclose( fp );


}





///////////////////////////////
///////////////////////////////
void naddclip( char *thefile )
{
     char fileinputsrc[PATH_MAX];
     strncpy( fileinputsrc, "", PATH_MAX );
     strncat( fileinputsrc , getenv( "HOME" ) , PATH_MAX - strlen( fileinputsrc ) -1 );
     strncat( fileinputsrc , "/.clipboard" , PATH_MAX - strlen( fileinputsrc ) -1 );

     FILE *fp;  
     fp = fopen( fileinputsrc , "wb+" );
       fputs( "!fig{", fp );
       fputs( thefile , fp );
       fputs( "}" , fp );
       fputs( "\n" , fp );
     fclose( fp );
}





     void tc_file_mkdir( char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|Mkdir|");
                    char fooline[PATH_MAX];
                    strncpy( fooline , myfile , PATH_MAX );
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       strncpy( cmdi, " mkdir -p  " , PATH_MAX );
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );
                     }
       }




     void tc_run_sys_command( char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|System Command|");
                    char fooline[PATH_MAX];
                    strncpy( fooline , myfile , PATH_MAX );
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       /*strncpy( cmdi, " mkfile  " , PATH_MAX );
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );*/
                       printf( "Ext. Sys Command: %s\n", fooline );
                       nruncmd( fooline );
                     }
       }










     void tc_file_mkfile( char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|Mkfile|");
                    char fooline[PATH_MAX];
                    strncpy( fooline , myfile , PATH_MAX );
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       strncpy( cmdi, " mkfile  " , PATH_MAX );
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );
                     }
       }




     void tc_file_rename( char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|Rename: %s|", myfile );
                    char fooline[PATH_MAX];
                    strncpy( fooline , strninput( myfile ), PATH_MAX );

                    if ( ( fexist( myfile ) == 2 ) || ( fexist( myfile ) == 1 ) )
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       strncpy( cmdi, " mv  -v " , PATH_MAX );
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi ,  myfile  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );
                     }
       }




     void tc_file_copy( char *dirtarget , char *myfile )
     {
                    char cmdi[PATH_MAX];
                    mvprintw( 0,0, "|Copy: %s|", myfile );
                    char fooline[PATH_MAX];
                    strncpy( fooline , strninput( myfile ), PATH_MAX );

                    if ( ( fexist( myfile ) == 2 ) || ( fexist( myfile ) == 1 ) )
                    if ( strcmp(  fooline  , "" ) != 0 )
                    {
                       strncpy( cmdi, " cp -r   -v " , PATH_MAX );
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi ,  myfile  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "  " , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , " \"" , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , fooline  , PATH_MAX - strlen(cmdi) - 1);
                       strncat( cmdi , "\"  " , PATH_MAX - strlen(cmdi) - 1);
                       nruncmd( cmdi );
                     }
       }








///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
char tc_current_path[PATH_MAX];
char tc_current_path_last[PATH_MAX];
void drawit()
{
        getmaxyx( stdscr, rows, cols);
  
        if ( gameselection <= 0 ) gameselection = 0;
        if ( gamescrolly <= 0 )   gamescrolly = 0;
        int fooj; 
        char foocwd[PATH_MAX];

        color_set( 2 , NULL );

        attroff( A_REVERSE );
        attroff( A_BOLD );
        erase();  


        mvprintw( 0, 0, "|CONSOLE|" );
        color_set( 2 , NULL );
        attroff( A_REVERSE );
        
           selectioninit();
             
           strncpy( tc_current_path, getcwd(foocwd, PATH_MAX) , PATH_MAX);

           if ( ( strcmp( tc_current_path_last, tc_current_path ) == 0 ) 
            && ( tc_refresh_reloaddir == 0 ) )
            {  } else mvlistprint( ".", 0 , gamefilter ) ;

           strncpy( tc_current_path_last, getcwd(foocwd, PATH_MAX) , PATH_MAX);
        


        // bottom bar
        color_set( 15 , NULL );
        attron( A_REVERSE );
        for ( fooj = 0 ; fooj <= cols-1;  fooj++)
        {
            mvaddch( rows-2, fooj , ' ' );
            mvaddch( 0, fooj , ' ' );
        }
        mvprintw( rows-2, 0 , "|%s|", fileselection );
        if ( strcmp( gamefilter, "" ) != 0 ) 
          printw( "Filter|" );
        else
          printw( "*|" );
        printw( "%d|", gameselection );
        printw( "%d|", gamescrolly );

        // top bar
        color_set( 15 , NULL );
        attron( A_REVERSE );
        mvprintw( 0, 0 , "|%s|", " TC " );

        move( rows-1, 0 );
        color_set( 0 , NULL );
        attroff( A_REVERSE );
        mvprintw( rows-1, 0, "%s", getcwd( foocwd, PATH_MAX ) );

        move( rows-1, 0 );
        color_set( 2 , NULL );
        attroff( A_REVERSE );

        attroff( A_REVERSE );
        attroff( A_BOLD );
}




char *fbasenoext(char* mystr)
{
    char *retstr;
    char *lastdot;
    if (mystr == NULL)
         return NULL;
    if ((retstr = malloc (strlen (mystr) + 1)) == NULL)
        return NULL;
    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, '.');
    if (lastdot != NULL)
        *lastdot = '\0';
    return retstr;
}





//////////////////////////////
//////////////////////////////
//////////////////////////////
//////////////////////////////
void nrun_openextension( char *theapp , char *thefile , char *theextension)
{
       def_prog_mode();
       endwin();
       ///////
         char targetfile[PATH_MAX];
         char cmdi[PATH_MAX];

         strncpy( targetfile, fbasenoext( thefile ) , PATH_MAX );
         //strncat( targetfile , ".pdf" , PATH_MAX - strlen( targetfile ) -1 );
         strncat( targetfile , "." , PATH_MAX - strlen( targetfile ) -1 );
         strncat( targetfile , theextension , PATH_MAX - strlen( targetfile ) -1 );

         strncpy( cmdi , theapp , PATH_MAX );
         //strncpy( cmdi , " screen -d -m mupdf  " , PATH_MAX );
         strncat( cmdi , "  \"" , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , targetfile , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , "\"  " , PATH_MAX - strlen( cmdi ) -1 );
         strncat( cmdi , " " , PATH_MAX - strlen( cmdi ) -1 );
         system( cmdi );
       ////////////////////////
       reset_prog_mode();

}


void tc_yline( int liy )
{
      int fooxy = 0;
      getmaxyx( stdscr, rows, cols);
      for( fooxy = 0 ; fooxy <= cols- 1 ; fooxy++) 
         mvprintw( liy , fooxy, " " );
}



///////////////////////////////////////////////////////////
int main( int argc, char *argv[])
{
    strncpy( gamefilter, "", PATH_MAX );
    strncpy( gamefilter_previous, "", PATH_MAX );
    char foostr[PATH_MAX];

    ////////////////////////////////////////////////////////
    if ( argc == 2)
      if ( strcmp( argv[1] , "" ) !=  0 )
       {
          chdir( argv[ 1 ] );
       }



    ////////////////////////////////////////////////////////
    if ( argc == 3)
     if ( strcmp( argv[1] , "--find" ) ==  0 ) 
     {
         strncpy( searchitem, argv[ 2 ], PATH_MAX );          
         listdir( ".", 0 ) ;
         return 0;
     }



   initscr();
   //raw();  //ctrl+c is with raw() disabled.
   keypad(stdscr, true);
   curs_set( 0 );
   noecho();
   start_color();
   init_pair(0, COLOR_WHITE, COLOR_BLACK);
   init_pair(1, COLOR_RED, COLOR_BLACK);
   init_pair(2, COLOR_GREEN, COLOR_BLACK);
   init_pair(3, COLOR_BLUE, COLOR_BLACK);
   init_pair(4, COLOR_CYAN, COLOR_BLACK);
   init_pair(6, COLOR_YELLOW, COLOR_BLACK);
   init_pair(15, COLOR_BLUE, COLOR_WHITE);
   color_set( 2, NULL );

   int ch ; 
   int rows, cols;  
   getmaxyx( stdscr, rows, cols);
   char userinp[PATH_MAX];
   int gameover_nsc = 0;
   strncpy( gamefilter, "", PATH_MAX );

   while ( gameover_nsc == 0)
   {
           
           //getmaxyx( stdscr, rows , cols);
           drawit();
	   refresh();			/* Print it on to the real screen */
           ch = getch();

           if ( ch == 'q' ) gameover_nsc =1 ;

    else if ( ch ==  KEY_UP )
        gameselection--;

    else if ( ch == KEY_DOWN )
        gameselection++;

    else if ( ch ==  KEY_LEFT )
        gameselection--;

    else if ( ch ==  KEY_RIGHT )
        gameselection++;

           else if ( ch == '~' ) { chdir( getenv( "HOME" ) ); gameselection = 1;  }

           else if ( ch == '2' ) tc_file_rename( fileselection );
           else if ( ch == '5' ) tc_file_copy( "."  , fileselection );

           else if ( ch == '$' ) 
           {
                    mvprintw( 0,0, "|Run Bash System Command|");
                    tc_run_sys_command( strninput( "" ) );
           }

           else if ( ch == '7' ) 
           {
                    mvprintw( 0,0, "|Mkfile|");
                    tc_file_mkfile( strninput( "" ) );
           }
           else if ( ch == '8' ) 
           {
                    mvprintw( 0,0, "|Mkdir|");
                    tc_file_mkdir( strninput( "" ) );
           }


           else if ( ch == 'o' ) { nrunwith( " mupdf " , fileselection  ); }
           else if ( ch == 'c' ) { mvprintw(0,0,"chdir"); chdir( strninput( "" ) ); }

           else if ( ch == 's' ) { nrunwith( " feh  " , fileselection  ); }

           else if ( ch == 'p' ) { nrunwith( " tcview " , fileselection  ); }
           else if ( ch == 'r' ) { nrunwith( " tcview " , fileselection  ); }
           else if ( ch == 'R' ) { nrunwith( " ncview " , fileselection  ); }
           else if ( ch == 'P' ) { nrunwith( " mupdf " , fileselection  ); }
           else if ( ch == 'v' ) { nrunwith( " vim  " , fileselection  ); }
           else if ( ch == 'x' ) { nrunwith( " xpaint " , fileselection  ); }

          //////////////////////////////
          //////////////////////////////
          //////////////////////////////
          else if ( ch ==  'm' ) 
          {
              mvprintw( 0,0, "[m]" );
              printw( " [d:chdir][o:mupdf (pdf)]" );
              ch = getch();
              if ( ch ==  '$' )      nruncmd( " bash " );
              else if ( ch ==  'c' ) nruncmd( " bash " );
              else if ( ch ==  'b' ) nruncmd( " bash " );
              else if ( ch ==  'v' ) { nrunwith( " vim  " , fileselection  ); }
              else if ( ch == 'o' )  { nrun_openextension( " screen -d -m mupdf ", fileselection , "pdf"  ); }

             else if ( ch == 'd' )
             { 
              tc_yline(0);
              mvprintw(0, 0, "CHDIR(?)" );
              chdir( strninput( "" ) ); 
              strncpy( gamefilter,  "" , PATH_MAX );
              gameselection=1;   gamescrolly = 0;   
             }


          }



          else if  ( ( ch == 'a' ) )
          {
           mvprintw( 0, 0, "|APPS: (f)eh; (l)ess; less (a); (n)ano; (b)ash; (v)im;|");
           mvprintw( 1, 0, "|APPS: m(p)layer; (m)pg123; (M)pg123 mp3s|");
           mvprintw( 2, 0, "|APPS: (o) open with mupdf; (o) pdftotext;|");
           mvprintw( 3, 0, "|APPS: (v)im; (t)im editor|");
           mvprintw( 4, 0, "|APPS: (l) less; |");
           mvprintw( 5, 0, "|APPS: (r) tcview (reader); |");
           mvprintw( 6, 0, "|APPS: (m) nmenu; |");
           mvprintw( 7, 0, "|APPS: (g) game file; |");
           mvprintw( 8, 0, "|APPS: (e) elinks; (n) links for net|");

           ch = getch(); 
           if ( ch == 'f' )      { nrunwith( " feh  " , fileselection  ); }


           else if ( ch == 'm' )  nruncmd( " nmenu   " );

           else if ( ch == 'l' ) { nrunwith( " less " , fileselection  ); }

           else if ( ch == 'e' )  nruncmd( "  elinks  google.com  " );
           else if ( ch == 'n' )  nruncmd( "  links  google.com  " );



           else if ( ch == 'r' ) { nruncmd( " tcview " ); }
           else if ( ch == 'e' ) { nruncmd( "  tcexp " ); }
           else if ( ch == 'o' ) { nrunwith( " screen -d -m mupdf " , fileselection  ); }






           else if ( ch == 'v' ) { nvim( fileselection ); }

           else if ( ch == 't' ) { nrunwith( " vim  " , fileselection  ); }


           else if ( ch == 'g' ) { nruncmd( " mintendo   "  ); }

           else if ( ch == '6' ) { nrunwith( " mupen64plus ", fileselection  ); }

           else if ( ch == 'p' ) { nrunwith( " mplayer -fs -zoom ", fileselection  ); }
           else if ( ch == 'P' ) { nrunwith( " mplayer -fs -zoom -ao null ", fileselection  ); }
           else if ( ch == '*' ) { nrunwith( " mplayer -fs -zoom * ", fileselection  ); }

           else if ( ch == 'm' ) { nrunwith( " mpg123 ", fileselection  ); }
           else if ( ch == 'M' ) { nrunwith( " mpg123 *.mp3 ", fileselection  ); }

           else if ( ch == 'T' ) { nruncmd( " setterm -powersave off -blank 0 " ); }

           else if ( ch == 'b' ) { nruncmd( " bash "  ); }
           else if ( ch == '$' ) { nruncmd( " bash "  ); }
           else if ( ch == 'e' ) { nruncmd( " rox "  ); }
          }

          else if ( ch == '!' ) { nrunwith( strninput( "" ) , fileselection  ); }

           else if ( ch == 'g' ) 
           {  mvprintw( rows-1, cols-1, "g" );
              ch = getch(); 
              if ( ch == 'o' ) { chdir( strninput( "" ) ); gameselection = 1;  }
              else if ( ch == 'g' ) { gameselection = 1; gamescrolly = 0 ; }
           }

           else if (( ch == 'h' ) || ( ch == '<' ))
           {
             chdir( ".." ); 
             strncpy( gamefilter,  "" , PATH_MAX );
             gameselection = 1;  gamescrolly = 0 ;  
           }

           else if (( ch == 'l' ) || ( ch == '>' ))
           { 
             strncpy( gamefilter_previous , gamefilter , PATH_MAX );
             chdir( fileselection ); 
             strncpy( gamefilter,  "" , PATH_MAX );
             strncpy( gamefilter,  "" , PATH_MAX );
             gameselection=1;   gamescrolly = 0;   
           }


           else if ( ch == 'F' ) 
           {
             strncpy( gamefilter , gamefilter_previous, PATH_MAX );
             gameselection=1; 
           }
           else if ( ch == 'f' ) 
           {
             strncpy( gamefilter_previous , gamefilter , PATH_MAX );
             strncpy( gamefilter, strninput( "" ) , PATH_MAX );
             gameselection=1; 
           }


           else if ( ch == 'K' ) 
           {
             win_keypress(); 
           }


           else if ( ch == ':' ) 
           {
             strncpy( foostr , strninput( "" ) , PATH_MAX );
           }


           else if ( ch == 'k' ) 
               gameselection--;
           else if ( ch == 'j' ) 
               gameselection++; 

         else if ( ch == '?' )
         {
             erase();
             mvprintw( 1, 0 , "|TC| " );
             getch();
         }




           else if ( ch == KEY_PPAGE )   gamescrolly-=4;  
           else if ( ch == KEY_NPAGE )   gamescrolly+=4; 
           else if ( ch == 'u' )   gamescrolly-=4;  
           else if ( ch == 'd' )   gamescrolly+=4; 
           else if ( ch == 'n' )   gamescrolly+=4; 


           else if ( ch ==  'y' ) naddclip( fileselection );

           else if ( ch ==  'Y' ) nappendclip( fileselection );

           else if ( ch ==  '%' ) 
           {
               if ( gamedirfcheck == 0 )
                   gamedirfcheck = 1; 
               else
                   gamedirfcheck = 0;
           }



           else if ( ch ==  '&' ) 
           {
               if ( tc_show_hidden == 0 )
                   tc_show_hidden = 1; 
               else
                   tc_show_hidden = 0;
           }

           else if ( ch ==  'C' ) 
           {
             erase();
             crossgraphvga_colors();
             getch();
           }


           else if ( ch ==  12 ) 
           {
             erase();
             getmaxyx( stdscr, rows , cols);
             mvprintw( 0, 0, "Reload Screen Rows/Cols" );
             getch();
           }


           else if ( ch ==  10 ) 
           {
             erase();
             getmaxyx( stdscr, rows , cols);
             mvprintw( 0, 0, "Pressed Enter" );
             //getch();
             if ( fexist( fileselection ) == 1 ) 
             {
                  if ( strcmp( fextension( fileselection ) , "png" ) == 0 )
                     ncurses_runwith( "  feh -FZ  "  , fileselection ); 
                  else if ( strcmp( fextension( fileselection ) , "jpg" ) == 0 )
                     ncurses_runwith( "  feh -FZ  "  , fileselection ); 
                  else if ( strcmp( fextension( fileselection ) , "pdf" ) == 0 )
                     ncurses_runwith( "  mupdf  "  , fileselection ); 
             }
           }


          /*
           else if ( ch ==  '#' ) 
           {
               if ( tc_refresh_reloaddir == 0 )
                   tc_refresh_reloaddir = 1; 
               else
                   tc_refresh_reloaddir = 0;

               attron( A_REVERSE );
               color_set( 4, NULL );
               gfxhline( 0 );
               gfxhline( 1 );
               mvprintw( 1, 0, "TC REFRESH LOADDIR: %d", tc_refresh_reloaddir );
               gfxhline( 2 );
               gfxhline( 3 );
               gfxframe( 0,0, 3, cols-1 );
               attroff( A_REVERSE );
               color_set( 0, NULL );
               getch();
           } */
 
    }

    curs_set( 1 );
    endwin();			/* End curses mode		  */
    return 0;
}



