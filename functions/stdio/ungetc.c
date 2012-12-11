/* $Id$ */

/* ungetc( int, FILE * )

   This file is part of the Public Domain C Library (PDCLib).
   Permission is granted to use, modify, and / or redistribute at will.
*/

#include <stdio.h>

#ifndef REGTEST

int ungetc_unlocked( int c, struct _PDCLIB_file_t * stream )
{
    if ( c == EOF || stream->ungetidx == _PDCLIB_UNGETCBUFSIZE )
    {
        return -1;
    }
    return stream->ungetbuf[stream->ungetidx++] = (unsigned char) c;
}

int ungetc( int c, struct _PDCLIB_file_t * stream )
{
    flockfile( stream );
    int r = ungetc_unlocked( c, stream );
    funlockfile( stream);
    return r;
}

#endif

#ifdef TEST
#include <_PDCLIB_test.h>

const char* hellostr = "Hello, world!";

int main( void )
{
    // Also see ftell() for some testing

    // PDCLIB-18: fread ignores ungetc
    size_t bufsz = strlen( hellostr ) + 1;
    char * buf = malloc( bufsz );
    FILE * fh;

    // Also fgets
    TESTCASE( ( fh = tmpfile() ) != NULL );
    TESTCASE( fputs(hellostr, fh) == 0 );
    rewind(fh);
    TESTCASE( fgetc( fh ) == 'H' );
    TESTCASE( ungetc( 'H', fh ) == 'H' );
    TESTCASE( fgets( buf, bufsz, fh ) != NULL );
    TESTCASE( strcmp( buf, hellostr ) == 0 );

    // fread
    rewind(fh);
    TESTCASE( fgetc( fh ) == 'H' );
    TESTCASE( ungetc( 'H', fh ) == 'H' );
    TESTCASE( fread( buf, bufsz - 1, 1, fh ) == 1 );
    TESTCASE( strncmp( buf, hellostr, bufsz - 1 ) == 0 );



    return TEST_RESULTS;
}

#endif
