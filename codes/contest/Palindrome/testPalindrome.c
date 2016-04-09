/* Author : Avinash Awate, Contest Co-ordinator */
/*****************************************************************************
 *                 Programming Contest IITBombayX Palindrome                  *
 *                 ----------------------------------------                  *
 * To allow contest participants to test a function which accepts a string   *
 * and print all the possible palindromes that can be generated using the    *
 * letters of the string                                                     *
 * For the purpose of this contest single characters are a palindrome        *
 * Input  : I.1) A string of  characters                                     *
 * Outputs: O.1) Total number of palindromes found                           *
 *          O.2) Palindromes output on standard output                       *
 *                                                                           *
 *****************************************************************************/

/*****************************************************************************
 *                       Source Code Organisation                            *
 *                       ------------------------                            *
 * testPalindrome.c                                                          *
 * This file allows the participant to test his function for correctness     *
 * This file contains C++ code which opens the input stream, reads the file  *
 * into an array, calls the contestants encoding function and writes the     *
 * data in the output file                                                   *
 * A correct entry will produce an exactly equivalent file                   *
 *                                                                           *
 *****************************************************************************/

/* System Includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

/* Local function prototypes */
int Palindrome(char *inStr);
char *sub(char *sr,char *dst,int pos,int size);
int min(int a,int b);
int max(int a,int b);
int len(char *inStr);
void check(int *ptr,char *ch,int pos,char c);
char * add(char c,int l,char *ch);
int isSame(char *s);
/* Local #defines */
#define MAXLENGTH        (100)
#define SUCCESS                (0)
#define FAILURE                (-1)
#define TRUE                (1)
#define FALSE                (0)

/* Globals */
static char  inputStr[1000];  /* The input array */
int ans=0;

/* Local Static Globals */
static FILE *inputfp=NULL;    /* Input file pointer */
static FILE *outputfp=NULL;   /* Output file pointer */

int main (int argc, char *argv[])
{
int  retval;                  /* Return value of function */
char *inputfile=NULL;         /* Input file name */
char *outputfile=NULL;        /* Output file name */
int  index;                   /* To traverse arrays */
char optionchar;              /* Option chracter returned by getopt */

    /* Set return value to SUCCESS */
    retval = SUCCESS;

    /* Process command line options */
    while ((optionchar = getopt (argc, argv, "i:o:")) != -1)
    {
        switch (optionchar)
        {
            case 'i':
                inputfile = optarg;
                break;
            case 'o':
                outputfile = optarg;
                break;
            case '?':
                if ( (optopt == 'i') || (optopt == 'o') )
                {
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                }
                else
                {
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                }
                retval = FAILURE;
            default:
                fprintf (stderr, "Usage : Palindrome [-i inputfile] [-o outputfile]\n");
                retval = FAILURE;
                break;
        }
    }

    /* Ignore all non option arguments */
    if (retval == SUCCESS)
    {
        for (index = optind; index < argc; index++)
        {
            fprintf(stderr, "Non-option argument %s\n", argv[index]);
        }
    }

    /* If everything OK so far, open input and output files */
    if (retval == SUCCESS)
    {   /* Correct Options specified */
        /* Open input file */
        inputfp = stdin;      /* Default is standard input */
        if (inputfile != NULL)
        {
            inputfp = fopen(inputfile,"r");
            if (inputfp == NULL)
            {
                fprintf (stderr, "Unable to open input file %s.\n", inputfile);
                retval = FAILURE;
            }
        }
        /* Open output file */
        if (outputfile != NULL)
        {
            outputfp = fopen(outputfile,"w");
            if (outputfp == NULL)
            {
                fprintf (stderr, "Unable to open output file %s.\n", outputfile);
                retval = FAILURE;
            }
            else { stdout = outputfp; }
        }
    }

    /* If everything OK so far, read input file into input array */
    if (retval == SUCCESS)
    {
        if (fscanf(inputfp, "%s", inputStr) == 1)
        {
            (void) Palindrome(inputStr);
        }
    }

    /* Clean up */
    if (inputfp != NULL) { fclose(inputfp); }
    if (outputfp != NULL) { fclose(outputfp); }

    /* Return from main */
    return(retval);
}
/*****************************************
 *********** End of Test Code ************
 *****************************************/

/************************************************
 *********** Beginning of submission ************
 ************************************************/

/* Define local variables (if any) here */

/* Define your support function ptototypes here */

/********************************************
 *********** Submission function ************
 *******************************************/
/*
 * The function Palindrome accepts one parameter
 * Inputs
 *     The parameter inStr contains the input string
 * Outputs
 *     The function returns the number of unique palindromes generated
 *     The function also prints each unique palindrome on a separate standard output line
 *
 * Algorithm
 *
 */
int Palindrome(char *inStr)
{
	int i;
	int feq[26]={0};
	int n = len(inStr);
		
	for(i=0;i<n;i++)
	{
		feq[(*(inStr+i))-97]++;
		
	}
	for(i=0;i<26;i++)
	{
		
		if(feq[i]!=0)
		{
			char c[2];
			c[0] = (char)(97+i);
			c[1] = '\0';
			check(feq,c,0,'\0');
		//	printf("%d\n",feq[i]);			
		}
	}
	printf("%d\n",ans);
	return ans;
    /* Return number of sequences */
}
void check(int *ptr,char *ch,int pos,char c)
{
	int i,arr[26]={0};
	char *s = (char *)malloc(1000*1);

	for(i=0;i<26;i++)
		arr[i]=ptr[i];
	
	strcpy(s,ch);
	printf("%s\n",s);
	ans++;
	int l = len(s);
	
	if(c=='\0')
		arr[s[pos]-97]--;	
	else
	{
		arr[c-97]-=2;
		//printf("%d\n",arr[c-97]);
	}
	int flag=0;
	for(i=0;i<26;i++)
	{
		if(l==1 && arr[s[pos]-97]>0 && flag==0)
		{
			//printf(" p %s %d\n",s,i);
			char *tmp = (char *)malloc(1000*1);
			strcpy(tmp,s);
			tmp[pos+1]=tmp[pos];
			tmp[pos+2]='\0';
			check(arr,tmp,0,'\0');
			free(tmp);
			flag=1;
			i=-1;
		}
		else
		{
			if(arr[i]>=2 && arr[i]>0)
			{
				//printf("p %s %d\n",s,arr[i]);
				char *tmp = (char *)malloc(1000*1);
				strcpy(tmp,s);
				tmp = add((char)(97+i),l,tmp);
				check(arr,tmp,0,(char)(97+i));
				free(tmp);
			}			
		}
					
	}
	free(s);
}
int isSame(char *s)
{
	int a = s[0];
	int i=1;
	for(i=1;s[i]!='\0';i++)
		if(s[i]!=a)
			return 0;
return 1;
}
char * add(char c,int l,char *ch)
{
int i;
	for(i=l;i>0;i--)
		ch[i]=ch[i-1];
ch[0]=c;
ch[l+1]=c;
ch[l+2]='\0';
return ch;
}
int *copy(int *src,int *dst)
{
	int i=0;
	for(i=0;i<26;i++)
		dst[i] = src[i];
return dst;
}	

char *sub(char *sr,char *dst,int pos,int size)
{
	int i,j=0;
	dst = malloc((size+1)*1);
	for(i=pos;i<pos+size;i++)
		dst[j++]=sr[i];	
	
dst[j]='\0';
return dst;
}
int min(int a,int b)
{
	if(a>b)
		return b;
	else
		return a;
}
int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}
int len(char *inStr)
{
	int i=0;
	while(inStr[i]!='\0')
		i++;
	return i;
}
