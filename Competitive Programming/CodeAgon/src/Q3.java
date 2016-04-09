import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class Q3
{
	public static void main(String[] args) throws IOException
	{
		sc.init(System.in);
		int t = sc.nextInt();
		
		while(t-->0)
		{
			
			
		
			String a = sc.next();
			String b = sc.next();
			int x = lps(a);
			int y = lps(b);
			System.out.println(a.length()+" "+b.length()+" "+x+" "+y);
			if(x%2==1 && y%2==1)
			{
				
				int[] ch1 = new int[26];
				for(int i=0;i<b.length();i++)
					ch1[b.charAt(i)-97]++;
				for(int i=0;i<26;i++)
				{
					System.out.print(ch1[i]+" ");
					if(ch1[i]%2==1)
						ch1[i]=1;
					else
						ch1[i]=0;
				}
				System.out.println();
				int[] ch2 = new int[26];			
					for(int i=0;i<a.length();i++)
						ch2[a.charAt(i)-97]++;
					for(int i=0;i<26;i++)
					{
						System.out.print(ch2[i]+" ");
						if(ch2[i]%2==1)
							ch2[i]=1;
						else
							ch2[i]=0;
						
					}
					
				int flag=0;
				for(int i=0;i<26;i++)
					if(ch1[i]==ch2[i] && ch1[i]!=0)
						flag=1;
				if(flag==1)
					System.out.println(x+y);
				else
					System.out.println(x+y-1);
					
					
			}
			else
				System.out.println(x+y);
		}
	}
	
	public static int lps(String x)
	{
	
		int[][] arr = new int[x.length()][x.length()];
		
		for(int i=0;i<x.length();i++)
			arr[i][i] = 1;
		
		for (int cl=2; cl<=x.length(); cl++)
	    {
	        for (int i=0; i<x.length()-cl+1; i++)
	        {
	            int j = i+cl-1;
	            if (x.charAt(i) == x.charAt(j) && cl == 2)
	               arr[i][j] = 2;
	            else if (x.charAt(i) == x.charAt(j))
	               arr[i][j] = arr[i+1][j-1] + 2;
	            else
	               arr[i][j] = Math.max(arr[i][j-1], arr[i+1][j]);
	        }
	    }
			return arr[0][x.length()-1];
		
		/*if(i>j)
			return 0;
		if(i==j)
			return 1;
		else if(x.charAt(i)==x.charAt(j))
			return lps(x,i+1,j-1)+2;
		else
			return Math.max(lps(x,i+1,j),lps(x,i,j-1));*/
	}
}
class sc 
{
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