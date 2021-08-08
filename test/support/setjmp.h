#ifndef _SETJMP_H
#define _SETJMP_H

#include "/opt/microchip/xc8/v2.10/pic/include/xc.h"

/******************************************************************************/
/*                                                                            */
/* FILENAME   : setjmp.c                                                      */
/* PROJECT    : Implementation of setjmp and longjmp                          */
/* CPU TYPE   : Microchip PIC16 family                                        */
/* COMPILER   : microC compiler for PIC v. 6.2.0.0 (241106) or up             */
/*                                                                            */
/*                                                                            */
/**************************** CHANGE AND RELEASE LOG **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.01 | changed function longjmp to be macro             | 241106 | IR   */
/*    0.00 | Created file                                     | 231106 | ST   */
/*                                                                            */
/******************************************************************************/



/******************************************************************************/
/*                                                                            */
/*  type: jmp_buf                                                             */
/*  Purpose:  array of type (jmp_buf) suitible for holding the                */
/*                   information needed for restoring calling environment     */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created type jmp_buf                             | 231106 | IR   */
/*         |                                                  |        |      */
/******************************************************************************/
typedef volatile char jmp_buf[3];


/******************************************************************************/
/*                                                                            */
/*  Macro: setjmp                                                             */
/*  Purpose:  saves calling position in jmp_buf for later use by longjmp      */
/*  CallParams: env: array of type (jmp_buf) suitible for holding the         */
/*                   information needed for restoring calling environment     */
/*  ReturnValues:  if the return is from direct invocation it returns 0       */
/*                 if the return is from  a call to the longjmp               */
/*                 it reurns nonzero value                                    */
/*  Notes:   setjmp macro is based on knowledge about the size of generated   */
/*           asm code and may need chages to work with version under v6.0     */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.00 | Created macro setjmp                             | 231106 | IR   */
/*         |                                                  |        |      */
/******************************************************************************/
#define _PCL_OFFSET  2
#define setjmp(env)  env[0] = PCLATHbits.PCLATH, env[1] = PCLbits.PCL+PCLATHbits.PCLATH, env[2] = 0

/******************************************************************************/
/*                                                                            */
/*  Macro: longjmp (divergence from ANSI C to fascilate to PIC16 family)      */
/*  Purpose:  restores calling position saved in jmp_buf by most recent       */
/*            invocation of setjmp macro. If there has been no such           */
/*            invocation, or function conatinig the invocation of setjmp has  */
/*            terminated in the interim, the behaviour is undefined           */
/*  CallParams: env: array of type (jmp_buf) holding the information          */
/*                   saved by corresponding setjmp invocation                 */
/*              val: char value, that will return corresponding setjmp        */
/*  ReturnValues:  longjmp causes setjmp to return val,if val is 0 it will    */
/*                 return 1                                                   */
/*                                                                            */
/****************************       CHANGE LOG       **************************/
/* Version | ACTION                                           |  DATE  | SIG  */
/* --------|--------------------------------------------------|--------|----- */
/*         |                                                  |        |      */
/*    0.01 | Change function to macro                         | 241106 | SH   */
/*    0.00 | Created function                                 | 231106 | IR   */
/*         |                                                  |        |      */
/******************************************************************************/
#define longjmp(env, val) env[2] = val ? val : 1, \
                          PCLATHbits.PCLATH = env[0], PCLbits.PCL = env[1]

#endif