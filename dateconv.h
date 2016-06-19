/* DateConv.h

   By Michael W. Maher

   Ver 1.0 9/28/92

   This is the header file for DATECONV.C.

   The toolkit was developed as an aid to C programmers.  The toolkit is
   full ANSI standard C.  The programs were tested with Microsoft C V5.1.
*/

#ifndef DATECONVH
  #define DATECONVH

  /******************************* includes ********************************/
  #include<stdlib.h>
  #include<string.h>

  /******************************** macros *********************************/

  /******************************** defines ********************************/
  #ifndef BOOLEAN_DEFINE
    #define BOOLEAN_DEFINE
    #define BOOL int
    #define TRUE 1
    #define FALSE 0
    #define ON 1
    #define OFF 0
    #define YES 1
    #define NO 0
    #define HOT 1
    #define COLD 0
    #define PASS 1
    #define FAIL 0
    #define RIGHT 1
    #define WRONG 0
    #define UP 1
    #define DOWN 0
  #endif

  /*************************** structure types *****************************/

  /************************* function prototypes ***************************/

  /* number of days in the month given a year (yy) and month (mm) number */
  int days_in_month(int year, int month);

  /* returns the difference in days between two dates in yymmdd format */
  unsigned long days_elapsed(char *start_date, char *stop_date);

  /* adds a number of months to a beginning date yymmdd format */
  void months_to_date(char *b_date, unsigned long months, char *e_date);

  /* calculates the number of periods between the two dates (yymmdd) */
  long periods_elapsed(char *b_date, char *e_date, long inc_days);

  /* given a start date (yymmdd) and days hence calculate the date */
  void days_to_date(char *b_date, unsigned long days, char *e_date);

  /* determines is a year is a leap year */
  BOOL is_leap_year(int year);

  /* returns the day of the week given a julian day number: 0 is Monday
  int day_of_week(long jul_day);

  /* convert a Gregorian date to a Julian day number */
  long greg_to_jul(int month, int day, int year);

  /* convert a Julian day number to a Gregorian date */
  void jul_to_greg(long jul_date, int *month, int *day, int *year);
#endif
