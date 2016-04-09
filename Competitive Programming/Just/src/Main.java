import java.io.*;
import java.util.*;
public class Main
{
	public static void main(String args[]) throws IOException
	{
		Scanner sc = new Scanner(System.in);
		long n = sc.nextInt();
		pair f1 = new pair(sc.nextLong(),sc.nextLong());
		pair f2 = new pair(sc.nextLong(),sc.nextLong());
		long distf1[] = new long[(int)n];
		long distf2[] = new long[(int)n];
		pair arr[] = new pair[(int)n];
		int minpos1=0,minpos2=0;
		for(int i=0;i<n;i++)
		{
			arr[i] = new pair(sc.nextLong(),sc.nextLong());
			distf1[i] = dist(f1,arr[i]);
			if(distf1[i]<distf1[minpos1])
				minpos1 = i;
			distf2[i] = dist(f2,arr[i]);
			if(distf2[i]<distf2[minpos2])
				minpos2 = i;
		}
		long fl1=0,fl2=fl1;
	
		for(int i=0;i<n;i++)
		{
			if(distf1[i]<distf2[i] && fl2<distf2[i])
			{
				if(distf1[i]>fl1)
				fl1 = distf1[i];
			}
			else
			{
				if(distf2[i]>fl2)
				fl2 = distf2[i];
			}
		}
		System.out.println(fl1+fl2);
	}
	public static long dist(pair p1,pair p2)
	{
		long ans = (p1.a - p2.a)*(p1.a - p2.a) + (p1.b - p2.b)*(p1.b - p2.b);
		return ans;
	}
}
class pair
{
	long a = 0;
	long b = 0;
	public pair(long x,long y)
	{
		a = x;
		b=y;
	}
}
class sc {
    static BufferedReader reader;
    static StringTokenizer tokenizer;

    /** call this method to initialize reader for InputStream */
    static void init(InputStream input) {
        reader = new BufferedReader(
                     new InputStreamReader(input) );
        tokenizer = new StringTokenizer("");
    }

    /** get next word */
    static String next() throws IOException {
        while ( ! tokenizer.hasMoreTokens() ) {
            //TODO add check for eof if necessary
            tokenizer = new StringTokenizer(
                   reader.readLine() );
        }
        return tokenizer.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt( next() );
    }
	
    static double nextDouble() throws IOException {
        return Double.parseDouble( next() );
    }
}