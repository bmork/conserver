/*
 *  $Id: client.h,v 5.33 2003-10-10 03:28:49-07 bryan Exp $
 *
 *  Copyright conserver.com, 2000
 *
 *  Maintainer/Enhancer: Bryan Stansell (bryan@conserver.com)
 *
 *  Copyright GNAC, Inc., 1998
 */

/*
 * Copyright 1992 Purdue Research Foundation, West Lafayette, Indiana
 * 47907.  All rights reserved.
 *
 * Written by Kevin S Braunsdorf, ksb@cc.purdue.edu, purdue!ksb
 *
 * This software is not subject to any license of the American Telephone
 * and Telegraph Company or the Regents of the University of California.
 *
 * Permission is granted to anyone to use this software for any purpose on
 * any computer system, and to alter it and redistribute it freely, subject
 * to the following restrictions:
 *
 * 1. Neither the authors nor Purdue University are responsible for any
 *    consequences of the use of this software.
 *
 * 2. The origin of this software must not be misrepresented, either by
 *    explicit claim or by omission.  Credit to the authors and Purdue
 *    University must appear in documentation and sources.
 *
 * 3. Altered versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 4. This notice may not be removed or altered.
 */
/* states for a server fsm
 */
typedef enum clientState {
    S_NORMAL,			/* just pass character                     */
    S_ESC1,			/* first escape character received         */
    S_CMD,			/* second interrupt character received     */
    S_CATTN,			/* change 1 escape char to next input char */
    S_CESC,			/* change 2 escape char to next input char */
    S_HALT1,			/* we have a halt sequence in progress     */
    S_SUSP,			/* we are suspened, first char wakes us up */
    S_IDENT,			/* probational connection (who is this)    */
    S_PASSWD,			/* still needs a passwd to connect         */
    S_QUOTE,			/* send any character we can spell         */
    S_BCAST			/* send a broadcast message to all clients */
} CLIENTSTATE;

typedef struct client {		/* Connection Information:              */
    CONSFILE *fd;		/* file descriptor                      */
    short fcon;			/* currently connect or not             */
    short fwr;			/* (client) write enable flag           */
    short fwantwr;		/* (client) wants to write              */
    short fro;			/* read-only permission                 */
    short fecho;		/* echo commands (not set by machines)  */
    STRING *acid;		/* login and location of client         */
    STRING *peername;		/* location of client                   */
    STRING *username;		/* login of client                      */
    time_t tym;			/* time of connect                      */
    time_t typetym;		/* time of last keystroke               */
    char actym[32];		/* pre-formatted time                   */
    struct consent
     *pCEto;			/* host a client gets output from       */
    struct client
    **ppCLbscan,		/* back link for scan ptr               */
     *pCLscan,			/* next client fd to scan after select  */
	/* scan lists link ALL clients together */
    **ppCLbnext,		/* back link for next ptr               */
     *pCLnext;			/* next person on this list             */
    /* next lists link clients on a console */
    char ic[2];			/* two character escape sequence        */
    CLIENTSTATE iState;		/* state for fsm in server              */
    char caccess;		/* did we trust the remote machine      */
    IOSTATE ioState;		/* state of the socket                  */
    time_t stateTimer;		/* timer for various ioState states */
    STRING *accmd;		/* the command the user issued          */
    STRING *msg;		/* the broadcast message                */
    struct sockaddr_in
      cnct_port;		/* where from                           */
} CONSCLIENT;

extern void Replay PARAMS((CONSFILE *, CONSFILE *, int));
extern void HelpUser PARAMS((CONSCLIENT *));
extern void FindWrite PARAMS((CONSENT *));
extern int ClientAccessOk PARAMS((CONSCLIENT *));
