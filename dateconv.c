/* DateConv.C

   By Michael W. Maher

   Ver 1.0 9/28/92
       2.0 1/29/93 Added Julian / Gregorian date conversion routines.

   Description: dateconv.c is a set of C date conversion and manipulation
		routines.  Some of these routines where published in The
		C User's Journal, by David Burki (February 1993).

   Portability: Standard ANSI C

	 Notes: A.D. - "anno Domini" Latin for "in the year of the Lord"
		46 B.C. - the "B.C." follows the date
		A.D. 46 - the "A.C." precedes the date

		Be careful when using historical information since not all
		Countries adopted the Gregorian calendar in a uniform manner.
		Britian and all colonies adopted it in 1752.

*/


/****************************************************************************
   function: days_in_month()

 parameters:  year - year in the form of yy
	     month - month in mm

    returns: the number of days in the month as an integer value

    purpose: This function will calculate the number of days in a month
	     for any given year and month. Note: January is 1.
****************************************************************************/
int days_in_month(int year, int month)
  {
  int days;

  switch(month)
    {
    case  1: days = 31;
	     break;
    case  2: if (is_leap_year(year) == TRUE)
	       days = 29;
	     else
	       days = 28;
	     break;
    case  3: days = 31;
	     break;
    case  4: days = 30;
	     break;
    case  5: days = 31;
	     break;
    case  6: days = 30;
	     break;
    case  7: days = 31;
	     break;
    case  8: days = 31;
	     break;
    case  9: days = 30;
	     break;
    case 10: days = 31;
	     break;
    case 11: days = 30;
	     break;
    case 12: days = 31;
	     break;
    default: days = NULL;              /* error month not between 1 and 12 */
	     break;
    }
  return(days);
  }


/****************************************************************************
   function: days_elapsed()

 parameters: start_date - date in mmddyy char format
	      stop_date - date in mmddyy char format

    returns: the number of days as a long integer (start_date - stop_date)

    purpose: This function will calculate the difference in days between
	     any two dates.
****************************************************************************/
unsigned long days_elapsed(char *start_date, char *stop_date)
  {
  char curr_date[7],
       cyy[3],
       cmm[3],
       cdd[3];
  long days = 0L;

  memset(cyy, '\0', 3 * sizeof(char));
  memset(cmm, '\0', 3 * sizeof(char));
  memset(cdd, '\0', 3 * sizeof(char));
  for (strcpy(curr_date, start_date);
       (strncmp(curr_date, stop_date, 4) <= 0);
       months_to_date(curr_date, 1L, curr_date))
    {
    cyy[0] = curr_date[0];
    cyy[1] = curr_date[1];
    cmm[0] = curr_date[2];
    cmm[1] = curr_date[3];
    days  += (long) days_in_month(atoi(cyy), atoi(cmm));
    }
  cdd[0] = start_date[4];
  cdd[1] = start_date[5];
  days  -= (atol(cdd) - 1);
  cyy[0] = stop_date[0];
  cyy[1] = stop_date[1];
  cmm[0] = stop_date[2];
  cmm[1] = stop_date[3];
  cdd[0] = stop_date[4];
  cdd[1] = stop_date[5];
  days  -= (long)days_in_month(atoi(cyy), atoi(cmm)) - atol(cdd);
  return(days);
  }


/****************************************************************************
   function: periods_elapsed()

 parameters:     bdate - beginning date
	     curr_date - ending date
	      inc_days - the period size in days

    returns: The number of periods elapsed between two dates as an integer.

    purpose: This function will calculate the number of periods between
	     any to dates.
****************************************************************************/
long periods_elapsed(char *b_date, char *e_date, long inc_days)
  {
  ldiv_t q_r;

  q_r = ldiv(days_elapsed(b_date, e_date), inc_days);
  return(q_r.quot);
  }


/****************************************************************************
   function: days_to_date()

 parameters:    b_date - beginning date in yymmdd char format
	      inc_days - number of days from beginning date
		e_date - the date inc_days from b_date

    returns: none

    purpose: This function will calculate a date given inc_days relative to
	     b_date.
****************************************************************************/
void days_to_date(char *b_date, unsigned long days, char *e_date)
  {
  char cyy[3],
       cmm[3],
       cdd[3];
  int  yy,
       mm,
       dd;

  cyy[0] = b_date[0];
  cyy[1] = b_date[1];
  cyy[2] = '\0';
  cmm[0] = b_date[2];
  cmm[1] = b_date[3];
  cmm[2] = '\0';
  cdd[0] = b_date[4];
  cdd[1] = b_date[5];
  cdd[2] = '\0';
  yy = atoi(cyy);
  mm = atoi(cmm);
  dd = atoi(cdd);
  while (days > 0L)
    {
    dd += 1;
    if (dd > days_in_month(yy, mm))
      {
      dd = 1;
      mm += 1;
      }
    if (mm > 12)
      {
      mm = 1;
      yy += 1;
      }
    days -= 1;
    }
  sprintf(e_date, "%02i%02i%02i", yy, mm, dd);
  return;
  }


/****************************************************************************
   function: months_to_date()

 parameters: b_date - the beginning date in yymmdd char format
	     months - the number of months to be added
	     e_date - the resulting ending date in yymmdd char format

    returns: none

    purpose: This function will add a specified number of months to a
	     beginning date to compute the ending date.
****************************************************************************/
void months_to_date(char *b_date, unsigned long months, char *e_date)
  {
  unsigned      yy, mm, dd;
  unsigned long i;
  int           actual_days;
  char          cyy[3],
		cmm[3],
		cdd[3];

  memset(cyy, '\0', 3);
  memset(cmm, '\0', 3);
  memset(cdd, '\0', 3);
  strncpy(cyy, b_date, 2);
  strncpy(cmm, &b_date[2], 2);
  strncpy(cdd, &b_date[4], 2);
  yy = atoi(cyy);
  mm = atoi(cmm);
  dd = atoi(cdd);
  for (i = 0; i < months; i++)
     {
     mm += 1;
     if (mm > 12)
       {
       mm = 1;
       yy++;
       }
     }
  actual_days = days_in_month(yy, mm);
  if (dd > actual_days)
    dd = actual_days;
  sprintf(e_date, "%02u%02u%02u", yy, mm, dd);
  return;
  }


/****************************************************************************
   function: is_leap_year()

 parameters: year - the year to check

    returns: 0 - TRUE  - if year is a leap year
	     1 - FALSE - if year is not a leap year

    purpose: Determines whether a given year is a leap year.
****************************************************************************/
BOOL is_leap_year(int year)
  {
  /*  A leap year truth table:
      year mod 4 == 0    year mod 100 == 0    year mod 400 == 0   Leap Year
      TRUE               TRUE                 TRUE                TRUE
      TRUE               TRUE                 FALSE               FALSE
      TRUE               FALSE                DON'T CARE          TRUE
      FALSE              DON'T CARE           DON'T CARE          FALSE */
  return((year % 4 == 0) && ((year % 100 != 0) || (year % 400) == 0));
  }                                     /* function is_leap_year */


/****************************************************************************
   function: day_of_week()

 parameters: jul_day - the julian day number

    returns: 0, 1, ... 7
	     where 0 is Monday, 1 is Tuesday, and 6 is Sunday

    purpose: Determines the day of the week a given julian day number.
****************************************************************************/
int day_of_week(long jul_day)
  {
  return((int) (jul_day % 7L));
  }                                     /* function day_of_week */


/****************************************************************************
   function: greg_to_jul()

 parameters: month - gregorian month
	     day   - gregorian day
	     year  - gregorian year

    returns: the julian day number

    purpose: The function converts the Gregorian calendar date to a
	     Julian day number.

  algorithm: This is an adaptation of the FORTRAN code representation of
	     the algorithm presented by H. Fliegl and T. Van Flanders,
	     Communication of the ACM, Vol. 11, No. 10, October, 1968,
	     page 657.
****************************************************************************/
long greg_to_jul(int month, int day, int year)
  {
  long lmonth = (long) month,           /* typecast once for performance */
       lday   = (long) day,
       lyear  = (long) year;

  return(lday - 32075L + 1461L *
	 (lyear + 4800 + (lmonth - 14L) / 12L) /
	 4L + 367L *
	 (lmonth - 2L - (lmonth - 14L) / 12L * 12L) / 12L - 3L *
	 ((lyear + 4900L + (lmonth - 14L) / 12L) / 100L) /
	 4L);
  }


/****************************************************************************
   function: jul_to_greg()

 parameters: jul_date - Julian day number
	     month    - Gregorian month
	     day      - Gregorian day
	     year     - Gregorian year

    returns: None, updades variables pointed to by year, month, day.

    purpose: The function converts the Julian day number to the Gregorian
	     calendar date.

  algorithm: This is an adaptation of the FORTRAN code representation of
	     the algorithm presented by H. Fliegl and T. Van Flanders,
	     Communication of the ACM, Vol. 11, No. 10, October, 1968,
	     page 657.
****************************************************************************/
void jul_to_greg(long jul_date, int *month, int *day, int *year)
  {
  long t1,
       t2,
       yr,
       mo;

  t1 = jul_date + 68569L;
  t2 = 4L * t1 / 146097L;
  t1 = t1 - (146097L * t2 + 3L) / 4L;
  yr = 4000L * (t1 + 1) / 1461001L;
  t1 = t1 - 1461L * yr / 4L + 31;
  mo = 80L * t1 / 2447L;
  *day   = (int) (t1 - 2447L * mo / 80L);
  t1     = mo / 11L;
  *month = (int)(mo + 2L - 12L * t1);
  *year  = (int)(100L * (t2 - 49L) + yr + t1);
  return;
  }



