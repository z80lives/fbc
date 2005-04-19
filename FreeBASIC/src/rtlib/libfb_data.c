/*
 *  libfb - FreeBASIC's runtime library
 *	Copyright (C) 2004-2005 Andre Victor T. Vicentini (av1ctor@yahoo.com.br)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * data.c -- restore and read stmts
 *
 * chng: oct/2004 written [v1ctor]
 *
 */

#include <stdlib.h>
#include "fb.h"


static char *fb_dataptr = NULL;

#define FB_DATATYPE_LINK -1
#define FB_DATATYPE_OFS  -2


/*:::::*/
FBCALL void fb_DataRestore( char *labeladdr )
{
	FB_LOCK();

	fb_dataptr = labeladdr;

	FB_UNLOCK();
}

static short fb_hDataRead( void )
{
	short len;

	if( fb_dataptr == NULL )
		return 0;

	len = *((short *)fb_dataptr);
	fb_dataptr += sizeof(short);

	/* link? */
	while ( len == FB_DATATYPE_LINK )
	{
		fb_dataptr = (char *)(*(int *)fb_dataptr);
		if( fb_dataptr == NULL )
			return 0;

		len = *((short *)fb_dataptr);
		fb_dataptr += sizeof(short);
	}

	return len;
}

/*:::::*/
FBCALL void fb_DataReadStr( void *dst, int dst_size, int fillrem )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == FB_DATATYPE_OFS )
	{
		/* !!!WRITEME!!! */
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
		fb_StrAssign( dst, dst_size, (void *)fb_dataptr, 0, fillrem );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadByte( char *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
        *dst = (char)fb_hStr2Int( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadUByte( unsigned char *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
        *dst = (unsigned char)fb_hStr2Int( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadShort( short *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
        *dst = (short)fb_hStr2Int( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadUShort( unsigned short *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
        *dst = (unsigned short)fb_hStr2Int( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadInt( int *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
        *dst = (int)fb_hStr2Int( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadUInt( unsigned int *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
        *dst = (unsigned int)fb_hStr2Int( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadLongint( long long *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
		*dst = (long long)fb_hStr2Longint( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadULongint( unsigned long long *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
		*dst = (unsigned long long)fb_hStr2Longint( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadSingle( float *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0.0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
        *dst = (float)fb_hStr2Double( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

/*:::::*/
FBCALL void fb_DataReadDouble( double *dst )
{
	short len;

	FB_LOCK();

	len = fb_hDataRead();

	if( len == 0 )
	{
		*dst = 0.0;
	}
	else if( len == FB_DATATYPE_OFS )
	{
		*dst = *(unsigned int *)fb_dataptr;
		fb_dataptr += sizeof( unsigned int );
	}
	else
	{
        *dst = fb_hStr2Double( (char *)fb_dataptr, len );

		fb_dataptr += len + 1;
	}

	FB_UNLOCK();
}

