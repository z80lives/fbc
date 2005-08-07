/*
 *  libfb - FreeBASIC's runtime library
 *	Copyright (C) 2004-2005 Andre V. T. Vicentini (av1ctor@yahoo.com.br) and others.
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
 * time_datepart.c -- datepart function
 *
 * chng: aug/2005 written [mjs]
 *
 */

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "fb.h"
#include "fb_rterr.h"

FBCALL int fb_DatePart( FBSTRING *interval, double serial, int first_day_of_week, int first_day_of_year )
{
    int result = 0;
    int year, month, day, hour, minute, second;
    int interval_type = fb_hTimeGetIntervalType( interval );

    fb_ErrorSetNum( FB_RTERROR_OK );

    switch ( interval_type ) {
    case FB_TIME_INTERVAL_YEAR:
        fb_hDateDecodeSerial ( serial, &year, NULL, NULL );
        result = year;
        break;
    case FB_TIME_INTERVAL_QUARTER:
        fb_hDateDecodeSerial ( serial, NULL, &month, NULL );
        result = ((month - 1) / 3) + 1;
        break;
    case FB_TIME_INTERVAL_MONTH:
        fb_hDateDecodeSerial ( serial, NULL, &month, NULL );
        result = month;
        break;
    case FB_TIME_INTERVAL_DAY_OF_YEAR:
        fb_hDateDecodeSerial ( serial, &year, &month, &day );
        result = fb_hGetDayOfYearEx( year, month, day );
        break;
    case FB_TIME_INTERVAL_DAY:
        fb_hDateDecodeSerial ( serial, NULL, NULL, &day );
        result = day;
        break;
    case FB_TIME_INTERVAL_WEEKDAY:
        result = fb_Weekday( serial, first_day_of_week );
        break;
    case FB_TIME_INTERVAL_WEEK_OF_YEAR:
        fb_hDateDecodeSerial ( serial, &year, NULL, NULL );
        result = fb_hGetWeekOfYear( year, serial, first_day_of_year, first_day_of_week );
        if( result < 0 )
            result = fb_hGetWeekOfYear( year - 1, serial, first_day_of_year, first_day_of_week );
        break;
    case FB_TIME_INTERVAL_HOUR:
        fb_hTimeDecodeSerial ( serial, &hour, NULL, NULL, FALSE );
        result = hour;
        break;
    case FB_TIME_INTERVAL_MINUTE:
        fb_hTimeDecodeSerial ( serial, NULL, &minute, NULL, FALSE );
        result = minute;
        break;
    case FB_TIME_INTERVAL_SECOND:
        fb_hTimeDecodeSerial ( serial, NULL, NULL, &second, FALSE );
        result = second;
        break;
    case FB_TIME_INTERVAL_INVALID:
    default:
        fb_ErrorSetNum( FB_RTERROR_ILLEGALFUNCTIONCALL );
        break;
    }

    return result;
}
