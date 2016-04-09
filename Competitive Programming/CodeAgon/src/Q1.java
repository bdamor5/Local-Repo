import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.*;

public class Q1
{
	public static void main(String[] args) throws IOException
	{
		sc.init(System.in);
		int n = sc.nextInt();
		int[] arr = new int[n];
		HashSet<Long> hs = new HashSet<Long>();
		
		for(int i=0;i<n;i++)
			arr[i] = sc.nextInt();
		int faclen[] = new int[1000001];
		faclen[1]=0;
		faclen[2]=1;
		for(int i=3;i<1000001;i++)
			faclen[i] = Faclen(i,faclen);
		
		//for(int i=1;i<25;i++)
		//	System.out.println(faclen[i]);
		long tmp[] = new long[1000001];
		long ans=0;
		for(int i=2;i<1000001;i++)
			tmp[i] = tmp[i-1]+faclen[i];
		
		
		for(int i=1;i<Math.pow(2, n);i++)
		{
			char ch[] = binary(i);
			long y=0;
			for(int j=0;j<ch.length;j++)
			{
				if(ch[j]=='1')
				{
					y+=tmp[arr[j]];
				//	System.out.println(j+" "+i);
				}
			}
			
			if(y%2==0)
			{
				ans+=y;
			}
		}
		System.out.println(ans);
		
		
	}
	public static char[] binary(int x)
	{
		char ch[] = new char[16];
		for(int i=0;i<16;i++)
		{
			if(x%2==0)
				ch[i]='0';
			else
				ch[i]='1';
			x/=2;
		}
		
		return ch;
	}
	public static int Faclen(int x,int[] arr)
	{
		int ans=0;
		for(int i=2;i<=Math.sqrt(x);i++)
		{
			if(x%i==0)
			{
				ans+=arr[i];
				ans+=arr[x/i];
				break;
			}
			
		}
		if(ans!=0)
			return ans;
		else
			return 1;
	}
}
