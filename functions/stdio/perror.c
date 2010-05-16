/* $Id$ */

/* perror( const char * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

#include <errno.h>

/* TODO: Doing this via a static array is not the way to do it. */
void perror( const char * s )
{
    if ( ( s != NULL ) && ( s[0] != '\n' ) )
    {
        fprintf( stderr, "%s: ", s );
    }
    fprintf( stderr, "%s\n", _PDCLIB_errno_texts[ errno ] );
    return;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

int main( void )
{
    TESTCASE( NO_TESTDRIVER );
    return TEST_RESULTS;
}

#endif
