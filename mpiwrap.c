#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#ifndef A2BOHR
#define A2BOHR 0.52917721092
#endif

#ifndef NM2BOHR
#define NM2BOHR 0.052917721092
#endif

#ifndef AUT2PS
#define AUT2PS 2.418884326505000E-05
#endif


#ifndef MAXLINE
#define MAXLINE 1000
#endif

#ifndef MAXCHARINLINE
#define MAXCHARINLINE 1500
#endif

#ifndef EV2HARTREE
#define EV2HARTREE 1.000/27.211
#endif

#ifndef CM2HARTREE
#define CM2HARTREE 1.000/219474.63
#endif

#ifndef DEBYE2AU
#define DEBYE2AU 0.393430307
#endif


#ifndef YES
#define YES 1
#endif

#ifndef NO
#define NO 0
#endif


int main( int argc , char * argv[ ] )
{

  char ** pcmd = argv ; 
  
  int icmd = 1 ;
  
  char buffer[ MAXCHARINLINE ] ;
  
  int lenBuff ;
  
  char cache[ MAXCHARINLINE ] ;

  
  int itmp , itmp2 ; double dtmp ; char ctmp , tmp_char ; 
  
  char stmp[ 300 ] , stmp2[ 300 ] , tmpString[ 300 ];
  
  double dtmpArray[ 150 ] ;
  
  int info , signal , blank_signal ;
  
  register FILE * debug ; 
  
  char * flag ;




  char * command , * set_env , * get_NID , * env_value ;
  
  int exe = NO ; int command_signal ;




  while( icmd < argc )
  {  
    pcmd ++ ; 

    flag = * pcmd ;

    //printf("\nNo.%d argument , Currently @ flag = %s ...\n\n" , icmd , flag );

    if( ( * flag == '-' ) && ( strlen( flag ) == 2 ) )
    {
      switch ( *( flag + 1 ) )
      {
	      
	      case 'e' : //strcpy( command , *( ++ pcmd ) ) ; 
                     
                     info = asprintf( &command , "%s" , *( ++ pcmd ) ) ;
                     
                     if( info == -1 )
                     {
                       fprintf( stderr , "\nOops ... Did not successfully 10-4 your command line ...\n\n" ) ;
                       
                       exit( 3 ) ;
                     }
                     else
                     {
                       exe = YES ;
                     }

	                 icmd = icmd + 2 ; 
	                 
	                 break ;
  
	    
	      case 'h' : printf("\nUsage:  %s [ -e 'command line to be executed' ] \n" , * argv ); 
	                 
	                 /*
                     printf("\n                Note : 1) when -m is specified as \"None\" or \"none\" or \"NONE\", no reference will be checked and orbital numbers provided in CI file will be directly used.\n\n");
                     printf("\n                Note : 2) Default group selection : [ -p \"Donor-Block\"] [ -q \"Acceptor-Block\"] [ -r \"Bridge-Block\"] [ -x \"Irrelevant-Block\"] [ -z \"Irrelevant-Block-2\"]\n\n\n") ; 
                     printf("\n                Note : 3) Default fragment names selection : [ -D \"Donor\"] [ -A \"Acceptor\"]\n\n\n") ; 
                     printf("\n                Note : 4) If one of the partition is not necessary, \"None/none/None\" has to be specified ...\n\n\n") ; 
	                 */

	                 icmd = icmd + 1 ; 
	                 
	                 exit( 1 ) ;
	                 
	      

	      default : printf("\n\nInvalid option ' %s ' ... Please refer to the usage by typing ' %s -h '\n\n" , flag , * argv ); 
	      
	                icmd = argc ; 
	                
	                exit( 1 );

      
      }
    
    }
    else
    {
        printf("\n\nInvalid option ' %s ' ... Please refer to the usage by typing ' %s -h '\n\n" , flag , * argv );

	    exit(1);
      
      
    }
    
 
  } 
  


  /* MPI Setup */
  
  
  int myid , numprocs , namelen ;
  
  char processor_name[ MPI_MAX_PROCESSOR_NAME ] ;
  
  
  MPI_Init( &argc , &argv ) ;
  
  MPI_Comm_rank( MPI_COMM_WORLD , &myid ) ;
  
  MPI_Comm_size( MPI_COMM_WORLD , &numprocs ) ;
  
  MPI_Get_processor_name( processor_name , &namelen ) ;
  
  
  info = asprintf( &set_env , "ZM_MPI_RANK=%d" , myid ) ;

  info = putenv( set_env ) ;
  
  env_value = getenv( "ZM_MPI_RANK" ) ;

  printf( "\nRank is [ %s ] \n" , env_value ) ;

  info = asprintf( &get_NID , "ZM_NID=%s" , processor_name );

  info = putenv( get_NID ) ; 

  env_value = getenv( "ZM_NID" ) ;

  printf( "Node ID is [ %s ] \n" , env_value ) ;
  



  command_signal = system( command ) ;


  
  
  //fprintf( stderr , "Hello, World! Process %d of %d on %s\n" , myid , numprocs , processor_name ) ;

  MPI_Finalize() ;

  
  
  /* MPI Done */


  return( 0 ) ;





}






