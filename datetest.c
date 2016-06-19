/* DateTest.c

   By Michael W. Maher

   Ver 1.0 6/15/92      for MCS 5.1


   The following code was written to test the ASCII date conversion
   routines in dateconv.c written by Michael W. Maher.  All functions are
   ANSI C.  It was tested for ANSI compatibility with the Microsoft C
   compiler V5.51 using the /Za switch. Example:

	CL /Za DATETEST.C

*/


/******************************** includes *********************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"dateconv.h"
#include"dateconv.c"

/**************************** function prototypes **************************/
void main(void);
char test_1(FILE *output);
char test_2(FILE *output);
char test_3(FILE *output);
char test_4(FILE *output);
char test_5(FILE *output);
char *testout(char passfail, char *out);

void main()
  {
  FILE *output;
  char buf[5];

  output = stderr;                     /* direct output to a stream */
  fprintf(output, "\n\n"
		  "DATETEST.C By Michael W. Maher 10/13/92\n"
		  "Testing DATECONV.C C functions...\n\n");

  /* Tests days_in_month() function. */
  fprintf(output, "TEST #%d: %s\n", 1, testout(test_1(output), buf));

  /* Tests the days_to_date() function. */
  fprintf(output, "TEST #%d: %s\n", 2, testout(test_2(output), buf));

  /* Test the months_to_date() function. */
  fprintf(output, "TEST #%d: %s\n", 3, testout(test_3(output), buf));

  /* Test the days_elapsed() function. */
  fprintf(output, "TEST #%d: %s\n", 4, testout(test_4(output), buf));

  /* Test Julian / Gregorian date conversion functions. */
  fprintf(output, "TEST #%d: %s\n", 5, testout(test_5(output), buf));
  return;
  }


/****************************************************************************
   function: testout()

 parameters: passfail - boolean value (PASS or FAIL)
		  out - 5 character string

    returns: "PASS" is returned in the string (out) if passfail contains
	     a PASS char value.
	     "FAIL" is returned in the string (out) if passfail contains
	     a FAIL char value.

    purpose: This function converts a boolean PASS or FAIL value to a
	     string value "PASS" or "FAIL".
****************************************************************************/
char *testout(char passfail, char *out)
  {
  if (passfail == PASS)
    strcpy(out, "PASS");
  else
    strcpy(out, "FAIL");
  return(out);
  }


/****************************************************************************
   function: test_1
 parameters:
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: The following code will test the days_in_month() function.  It
	     will compare the value returned from days_in_month() to a
	     table of correct values.  The function is also tested at
	     boundries such as month 0 and month 13.  Leap year handling is
	     also tested.
****************************************************************************/
char test_1(FILE *output)
  {
  #define MONTH_TEST_SIZE 14
  char status = PASS;
  int  month,
       days,
       answer_table[MONTH_TEST_SIZE];

  answer_table[0] = 0;                 /* boundry month */
  answer_table[1] = 31;
  answer_table[2] = 28;
  answer_table[3] = 31;
  answer_table[4] = 30;
  answer_table[5] = 31;
  answer_table[6] = 30;
  answer_table[7] = 31;
  answer_table[8] = 31;
  answer_table[9] = 30;
  answer_table[10]= 31;
  answer_table[11]= 30;
  answer_table[12]= 31;
  answer_table[13]= 0;                 /* boundry month */
  /* test a non leap year for every month and boundry months 0 & 13 */
  for (month = 0; month < MONTH_TEST_SIZE; month++)
    {
    days = days_in_month(91, month);
    if (days != answer_table[month])
      {
      fprintf(output, "ERROR: result = %i, correct answer = %i\n",
	      days, answer_table[month]);
      status = FAIL;
      }
    }
  /* test leap year February 1980 */
  days = days_in_month(80, 2);
  if (days != 29)
    {
      fprintf(output, "ERROR: result = %i, correct answer = %i\n",
	      days, 29);
      status = FAIL;
      }
  return(status);
  }


/****************************************************************************
   function: test_2
 parameters: none
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: The following code will test the days_to_date() function.
****************************************************************************/
char test_2(FILE *output)
  {
  #define DAYS_TEST_DATES 5
  char status = PASS,
       b_date[7],
       e_date[7],
       *answer_table[DAYS_TEST_DATES];
  long days,
       i;

  /* build the correct answer table */
  answer_table[0] = "910101";
  answer_table[1] = "910131";
  answer_table[2] = "910302";
  answer_table[3] = "910401";
  answer_table[4] = "910501";
  strcpy(b_date, "910101");
  for (days = 0, i = 0; i < DAYS_TEST_DATES; days += 30, i++)
    {
    days_to_date(b_date, days, e_date);
    if (strcmp(e_date, answer_table[i]) != 0)
      {
      fprintf(output,
	      "ERROR: beginning [%s] + days [%ld] = ending [%s] [%s]\n",
	      b_date, days, e_date, answer_table[i]);
      status = FALSE;
      }
    }
  return(status);
  }


/****************************************************************************
   function: test_3

 parameters: output - the destination of the error output

    returns: if successful
	       TRUE
	     else
	       FALSE

    purpose: This function tests the months_to_date() function.  Months to
	     date should add a beginning date to a number of months and
	     produce the resulting ending date.
****************************************************************************/
char test_3(FILE *output)
  {
  #define TEST_DATES 5
  char status = PASS,
       b_date[7],
       e_date[7],
       *answer_table[TEST_DATES];
  long months,
       i;

  /* build the correct answer table */
  answer_table[0] = "910101";
  answer_table[1] = "910401";
  answer_table[2] = "910701";
  answer_table[3] = "911001";
  answer_table[4] = "920101";
  strcpy(b_date, answer_table[0]);
  for (months = 0, i = 0; i < TEST_DATES; months += 3, i++)
    {
    months_to_date(b_date, months, e_date);
    if (strcmp(e_date, answer_table[i]) != 0)
      {
      fprintf(output,
	      "ERROR: beginning [%s] + months [%ld] = ending [%s] [%s]\n",
	      b_date, months, e_date, answer_table[i]);
      status = FALSE;
      }
    }
  return(status);
  }


/****************************************************************************
   function: test_4
 parameters: none
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: This function tests the days_elapsed() function.  The function
	     will count the number of days from a start date to an
	     ending date inclusively.  days_elapsed() is tested for leap
	     years and other date spans.
****************************************************************************/
char test_4(FILE *output)
  {
  #define MAX_TEST_DATES 4
  typedef struct test_data
    {
    char          *start_date;
    char          *stop_date;
    unsigned long days;
    } test_data;

  char      status = PASS;
  test_data data[MAX_TEST_DATES];
  unsigned  long days,
	    i;

  data[0].start_date = "910101";
  data[0].stop_date  = "910102";
  data[0].days       = 2;
  data[1].start_date = "800101";
  data[1].stop_date  = "801231";
  data[1].days       = 366;
  data[2].start_date = "910101";
  data[2].stop_date  = "910131";
  data[2].days       = 31;
  data[3].start_date = "910101";
  data[3].stop_date  = "911231";
  data[3].days       = 365;
  for (i = 0; i < MAX_TEST_DATES; i++)
    {
    days = days_elapsed(data[i].start_date, data[i].stop_date);
    if (days != data[i].days)
      {
      fprintf(output, "ERROR: stop [%s] - start [%s] = [%lu] days != [%lu]\n",
	      data[i].start_date, data[i].stop_date, data[i].days, days);
      status = FALSE;
      }
    }
  return(status);
  }


/****************************************************************************
   function: test_5
 parameters: none
    returns: if successful
	       TRUE
	     else
	       FALSE
    purpose: The following function will test Julian / Gregorian date
	     conversions.
****************************************************************************/
char test_5(FILE *output)
  {
  char test = PASS;
  struct tm *tm_time;
  long      curr_time,
	    jul_day;
  int       month,
	    day,
	    year;

  /* Convert the current Gregorian date to a Julian day and back again. */
  time(&curr_time);
  tm_time = localtime(&curr_time);
  tm_time->tm_mon += 1;                 /* make 1-12 instead of 0-11 */
  jul_day = greg_to_jul(tm_time->tm_mon, tm_time->tm_mday, tm_time->tm_year);
  jul_to_greg(jul_day, &month, &day, &year);
  if ((tm_time->tm_mon  != month) ||
      (tm_time->tm_mday  != day) ||
      (tm_time->tm_year != year))
    {
    fprintf(output, "Julian day:%ld -> C: %i %i %i != converted: %i %i %i\n",
		    jul_day,
		    tm_time->tm_mon, tm_time->tm_mday, tm_time->tm_year,
		    month, day, year);
    test = FAIL;
    }
  return(test);
  }






