

/* Standard includes. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/* FreeRTOS+CLI includes. */
#include "partest.h"
#include "FreeRTOS_CLI.h"

#ifndef  configINCLUDE_TRACE_RELATED_CLI_COMMANDS
    #define configINCLUDE_TRACE_RELATED_CLI_COMMANDS 0
#endif


/*
 * Implements the run-time-stats command.
 */
static portBASE_TYPE prvTaskStatsCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );

/*
 * Implements the task-stats command.
 */
static portBASE_TYPE prvRunTimeStatsCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );

/*
 * Implements the echo-three-parameters command.
 */
static portBASE_TYPE prvThreeParameterEchoCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );

/*
 * Implements the echo-parameters command.
 */
static portBASE_TYPE prvParameterEchoCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );

/*
 * Implements the "trace start" and "trace stop" commands;
 */
#if configINCLUDE_TRACE_RELATED_CLI_COMMANDS == 1
    static portBASE_TYPE prvStartStopTraceCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
#endif


    
static portBASE_TYPE prvVersCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
    
 /* Structure that defines the "board-info" command line command*/
static const CLI_Command_Definition_t xBoardInfo =
{
    "version", /* The command string to type. */
    "\r\nversion:\r\n Displays software build date\r\n",
    (pdCOMMAND_LINE_CALLBACK) prvVersCommand, /* The function to run. */
    0 /* No parameters are expected. */
};   
    
static portBASE_TYPE prvSetLEDStateCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
    
 /* Structure that defines the "board-info" command line command*/
static const CLI_Command_Definition_t xLedState =
{
    "led-state", /* The command string to type. */
    "\r\nled-state:\r\n Set LED state <LED_CELL1> <LED_CONN> <LED_DATA> <LED_ERR> \r\n",
    (pdCOMMAND_LINE_CALLBACK) prvSetLEDStateCommand, /* The function to run. */
    4 /* No parameters are expected. */
};   
    
    
/* Structure that defines the "run-time-stats" command line command.   This
generates a table that shows how much run time each task has */
static const CLI_Command_Definition_t xRunTimeStats =
{
    "run-time-stats", /* The command string to type. */
    "\r\nrun-time-stats:\r\n Displays a table showing how much processing time each FreeRTOS task has used\r\n",
    (pdCOMMAND_LINE_CALLBACK) prvRunTimeStatsCommand, /* The function to run. */
    0 /* No parameters are expected. */
};

/* Structure that defines the "task-stats" command line command.  This generates
a table that gives information on each task in the system. */
static const CLI_Command_Definition_t xTaskStats =
{
    "task-stats", /* The command string to type. */
    "\r\ntask-stats:\r\n Displays a table showing the state of each FreeRTOS task\r\n",
    (pdCOMMAND_LINE_CALLBACK) prvTaskStatsCommand, /* The function to run. */
    0 /* No parameters are expected. */
};

/* Structure that defines the "echo_3_parameters" command line command.  This
takes exactly three parameters that the command simply echos back one at a
time. */
static const CLI_Command_Definition_t xThreeParameterEcho =
{
    "echo-3-parameters",
    "\r\necho-3-parameters <param1> <param2> <param3>:\r\n Expects three parameters, echos each in turn\r\n",
    (pdCOMMAND_LINE_CALLBACK) prvThreeParameterEchoCommand, /* The function to run. */
    3 /* Three parameters are expected, which can take any value. */
};

/* Structure that defines the "echo_parameters" command line command.  This
takes a variable number of parameters that the command simply echos back one at
a time. */
static const CLI_Command_Definition_t xParameterEcho =
{
    "echo-parameters",
    "\r\necho-parameters <...>:\r\n Take variable number of parameters, echos each in turn\r\n",
    (pdCOMMAND_LINE_CALLBACK) prvParameterEchoCommand, /* The function to run. */
    -1 /* The user can enter any number of commands. */
};

#if configINCLUDE_TRACE_RELATED_CLI_COMMANDS == 1
    /* Structure that defines the "trace" command line command.  This takes a single
    parameter, which can be either "start" or "stop". */
    static const CLI_Command_Definition_t xStartStopTrace =
    {
        "trace",
        "\r\ntrace [start | stop]:\r\n Starts or stops a trace recording for viewing in FreeRTOS+Trace\r\n",
        prvStartStopTraceCommand, /* The function to run. */
        1 /* One parameter is expected.  Valid values are "start" and "stop". */
    };
#endif /* configINCLUDE_TRACE_RELATED_CLI_COMMANDS */

/*-----------------------------------------------------------*/

void vRegisterSampleCLICommands( void )
{

    /* Register all the command line commands defined immediately above. */
    FreeRTOS_CLIRegisterCommand( &xTaskStats );
    FreeRTOS_CLIRegisterCommand( &xRunTimeStats );
    FreeRTOS_CLIRegisterCommand( &xThreeParameterEcho );
    FreeRTOS_CLIRegisterCommand( &xParameterEcho );
    FreeRTOS_CLIRegisterCommand( &xBoardInfo );
 //   FreeRTOS_CLIRegisterCommand( &xLedState);


    #if( configINCLUDE_TRACE_RELATED_CLI_COMMANDS == 1 )
    {
        FreeRTOS_CLIRegisterCommand( & xStartStopTrace );
    }
    #endif
}
/*-----------------------------------------------------------*/

static portBASE_TYPE prvVersCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
const char *const pcHeader = "Build date: ";

    /* Remove compile time warnings about unused parameters, and check the
    write buffer is not NULL.  NOTE - for simplicity, this example assumes the
    write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    /* Generate a table of task stats. */
    strcpy( pcWriteBuffer, pcHeader );
    strncat( pcWriteBuffer, __DATE__, strlen( __DATE__ ) );
    strncat( pcWriteBuffer, "\r\n", strlen( "\r\n" ) );

    /* There is no more data to return after this single string, so return
    pdFALSE. */
    return pdFALSE;
}

static portBASE_TYPE prvTaskStatsCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
const char *const pcHeader = "Task          State  Priority  Stack  #\r\n************************************************\r\n";

    /* Remove compile time warnings about unused parameters, and check the
    write buffer is not NULL.  NOTE - for simplicity, this example assumes the
    write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    /* Generate a table of task stats. */
    strcpy( pcWriteBuffer, pcHeader );
    vTaskList( pcWriteBuffer + strlen( pcHeader ) );

    /* There is no more data to return after this single string, so return
    pdFALSE. */
    return pdFALSE;
}
/*-----------------------------------------------------------*/

static portBASE_TYPE prvRunTimeStatsCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
const char * const pcHeader = "Task            Abs Time      % Time\r\n****************************************\r\n";

    /* Remove compile time warnings about unused parameters, and check the
    write buffer is not NULL.  NOTE - for simplicity, this example assumes the
    write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    /* Generate a table of task stats. */
    strcpy( pcWriteBuffer, pcHeader );
    vTaskGetRunTimeStats( pcWriteBuffer + strlen( pcHeader ) );

    /* There is no more data to return after this single string, so return
    pdFALSE. */
    return pdFALSE;
}
/*-----------------------------------------------------------*/

static portBASE_TYPE prvThreeParameterEchoCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
const char *pcParameter;
portBASE_TYPE xParameterStringLength, xReturn;
static portBASE_TYPE lParameterNumber = 0;

    /* Remove compile time warnings about unused parameters, and check the
    write buffer is not NULL.  NOTE - for simplicity, this example assumes the
    write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    if( lParameterNumber == 0 )
    {
        /* The first time the function is called after the command has been
        entered just a header string is returned. */
        sprintf( pcWriteBuffer, "The three parameters were:\r\n" );

        /* Next time the function is called the first parameter will be echoed
        back. */
        lParameterNumber = 1L;

        /* There is more data to be returned as no parameters have been echoed
        back yet. */
        xReturn = pdPASS;
    }
    else
    {
        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                            (
                                pcCommandString,        /* The command string itself. */
                                lParameterNumber,       /* Return the next parameter. */
                                (BaseType_t *) &xParameterStringLength  /* Store the parameter string length. */
                            );

        /* Sanity check something was returned. */
        configASSERT( pcParameter );

        /* Return the parameter string. */
        memset( pcWriteBuffer, 0x00, xWriteBufferLen );
        sprintf( pcWriteBuffer, "%d: ", ( int ) lParameterNumber );
        strncat( pcWriteBuffer, pcParameter, xParameterStringLength );
        strncat( pcWriteBuffer, "\r\n", strlen( "\r\n" ) );

        /* If this is the last of the three parameters then there are no more
        strings to return after this one. */
        if( lParameterNumber == 3L )
        {
            /* If this is the last of the three parameters then there are no more
            strings to return after this one. */
            xReturn = pdFALSE;
            lParameterNumber = 0L;
        }
        else
        {
            /* There are more parameters to return after this one. */
            xReturn = pdTRUE;
            lParameterNumber++;
        }
    }

    return xReturn;
}
/*-----------------------------------------------------------*/

static portBASE_TYPE prvParameterEchoCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
const char *pcParameter;
portBASE_TYPE xParameterStringLength, xReturn;
static portBASE_TYPE lParameterNumber = 0;

    /* Remove compile time warnings about unused parameters, and check the
    write buffer is not NULL.  NOTE - for simplicity, this example assumes the
    write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    if( lParameterNumber == 0 )
    {
        /* The first time the function is called after the command has been
        entered just a header string is returned. */
        sprintf( pcWriteBuffer, "The parameters were:\r\n" );

        /* Next time the function is called the first parameter will be echoed
        back. */
        lParameterNumber = 1L;

        /* There is more data to be returned as no parameters have been echoed
        back yet. */
        xReturn = pdPASS;
    }
    else
    {
        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                            (
                                pcCommandString,        /* The command string itself. */
                                lParameterNumber,       /* Return the next parameter. */
                                (BaseType_t *) &xParameterStringLength  /* Store the parameter string length. */
                            );

        if( pcParameter != NULL )
        {
            /* Return the parameter string. */
            memset( pcWriteBuffer, 0x00, xWriteBufferLen );
            sprintf( pcWriteBuffer, "%d: ", ( int ) lParameterNumber );
            strncat( pcWriteBuffer, pcParameter, xParameterStringLength );
            strncat( pcWriteBuffer, "\r\n", strlen( "\r\n" ) );

            /* There might be more parameters to return after this one. */
            xReturn = pdTRUE;
            lParameterNumber++;
        }
        else
        {
            /* No more parameters were found.  Make sure the write buffer does
            not contain a valid string. */
            pcWriteBuffer[ 0 ] = 0x00;

            /* No more data to return. */
            xReturn = pdFALSE;

            /* Start over the next time this command is executed. */
            lParameterNumber = 0;
        }
    }

    return xReturn;
}
/*-----------------------------------------------------------*/

#if configINCLUDE_TRACE_RELATED_CLI_COMMANDS == 1

    static portBASE_TYPE prvStartStopTraceCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
    {
    const char *pcParameter;
    portBASE_TYPE lParameterStringLength;

        /* Remove compile time warnings about unused parameters, and check the
        write buffer is not NULL.  NOTE - for simplicity, this example assumes the
        write buffer length is adequate, so does not check for buffer overflows. */
        ( void ) pcCommandString;
        ( void ) xWriteBufferLen;
        configASSERT( pcWriteBuffer );

        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                            (
                                pcCommandString,        /* The command string itself. */
                                1,                      /* Return the first parameter. */
                                (BaseType_t *) &lParameterStringLength  /* Store the parameter string length. */
                            );

        /* Sanity check something was returned. */
        configASSERT( pcParameter );

        /* There are only two valid parameter values. */
        if( strncmp( pcParameter, "start", strlen( "start" ) ) == 0 )
        {
            /* Start or restart the trace. */
            vTraceStop();
            vTraceClear();
            vTraceStart();

            sprintf( pcWriteBuffer, "Trace recording (re)started.\r\n" );
        }
        else if( strncmp( pcParameter, "stop", strlen( "stop" ) ) == 0 )
        {
            /* End the trace, if one is running. */
            vTraceStop();
            sprintf( pcWriteBuffer, "Stopping trace recording.\r\n" );
        }
        else
        {
            sprintf( pcWriteBuffer, "Valid parameters are 'start' and 'stop'.\r\n" );
        }

        /* There is no more data to return after this single string, so return
        pdFALSE. */
        return pdFALSE;
    }

#endif /* configINCLUDE_TRACE_RELATED_CLI_COMMANDS */
    
    
static portBASE_TYPE prvSetLEDStateCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
const char *pcParameter;
portBASE_TYPE xParameterStringLength, xReturn;
static portBASE_TYPE lParameterNumber = 0;

    /* Remove compile time warnings about unused parameters, and check the
    write buffer is not NULL.  NOTE - for simplicity, this example assumes the
    write buffer length is adequate, so does not check for buffer overflows. */
    ( void ) pcCommandString;
    ( void ) xWriteBufferLen;
    configASSERT( pcWriteBuffer );

    if( lParameterNumber == 0 )
    {
        /* The first time the function is called after the command has been
        entered just a header string is returned. */
        sprintf( pcWriteBuffer, "LED Status :" );

        /* Next time the function is called the first parameter will be echoed
        back. */
        lParameterNumber = 1L;

        /* There is more data to be returned as no parameters have been echoed
        back yet. */
        xReturn = pdPASS;
    }
    else
    {
        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                            (
                                pcCommandString,        /* The command string itself. */
                                lParameterNumber,       /* Return the next parameter. */
                                (BaseType_t *) &xParameterStringLength  /* Store the parameter string length. */
                            );

        /* Sanity check something was returned. */
        configASSERT( pcParameter );

        if (pcParameter[0] == '0') 
        {
            vParTestSetLED((lParameterNumber-1), 1);       
            sprintf( pcWriteBuffer, " OFF " );
        }
        else if (pcParameter[0] == '1') 
        {
            vParTestSetLED((lParameterNumber-1), 0);    
            sprintf( pcWriteBuffer, " ON " );
        }
        else 
        {
            sprintf( pcWriteBuffer, " ??? " );
         }

        /* If this is the last of the three parameters then there are no more
        strings to return after this one. */
        if( lParameterNumber == 4L )
        {
            strncat( pcWriteBuffer, "\r\n", strlen( "\r\n" ) );
            /* If this is the last of the three parameters then there are no more
            strings to return after this one. */
            xReturn = pdFALSE;
            lParameterNumber = 0L;
        }
        else
        {
            /* There are more parameters to return after this one. */
            xReturn = pdTRUE;
            lParameterNumber++;
        }
    }

    return xReturn;
}
/*-----------------------------------------------------------*/



#if configINCLUDE_TRACE_RELATED_CLI_COMMANDS == 1

    static portBASE_TYPE prvStartStopTraceCommand( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
    {
    const char *pcParameter;
    portBASE_TYPE lParameterStringLength;

        /* Remove compile time warnings about unused parameters, and check the
        write buffer is not NULL.  NOTE - for simplicity, this example assumes the
        write buffer length is adequate, so does not check for buffer overflows. */
        ( void ) pcCommandString;
        ( void ) xWriteBufferLen;
        configASSERT( pcWriteBuffer );

        /* Obtain the parameter string. */
        pcParameter = FreeRTOS_CLIGetParameter
                            (
                                pcCommandString,        /* The command string itself. */
                                1,                      /* Return the first parameter. */
                                &lParameterStringLength /* Store the parameter string length. */
                            );

        /* Sanity check something was returned. */
        configASSERT( pcParameter );

        /* There are only two valid parameter values. */
        if( strncmp( pcParameter, "start", strlen( "start" ) ) == 0 )
        {
            /* Start or restart the trace. */
            vTraceStop();
            vTraceClear();
            vTraceStart();

            sprintf( pcWriteBuffer, "Trace recording (re)started.\r\n" );
        }
        else if( strncmp( pcParameter, "stop", strlen( "stop" ) ) == 0 )
        {
            /* End the trace, if one is running. */
            vTraceStop();
            sprintf( pcWriteBuffer, "Stopping trace recording.\r\n" );
        }
        else
        {
            sprintf( pcWriteBuffer, "Valid parameters are 'start' and 'stop'.\r\n" );
        }

        /* There is no more data to return after this single string, so return
        pdFALSE. */
        return pdFALSE;
    }

#endif /* configINCLUDE_TRACE_RELATED_CLI_COMMANDS */
