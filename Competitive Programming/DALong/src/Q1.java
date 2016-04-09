import java.util.*;
public class Q1 
{
	static long mod;
	public static void main(String[] args)
	{
		Scanner sc= new Scanner(System.in);
		int t = sc.nextInt();
		
		while(t-->0)
		{
			long n = sc.nextLong();
			long k = sc.nextLong();
			long F[][] = new long[2][2];
			F[0][0] = 1;
			F[0][1] = 1;
			F[1][0] = 1;
			F[1][1] = 0;
			mod =(long) Math.pow(2, k);
			pow(n,F);
			System.out.println(F[0][0]%mod);
		}
	}
	public static void pow(long n,long[][] F)
	{
		if(n==0 || n==1)
			return;
		long M[][] = new long[2][2];
		
		M[0][0] = 1;
		M[0][1] = 1;
		M[1][0] = 1;
		M[1][1] = 0;
		  pow(n/2,F);
		  multiply(F, F);
		 
		  if (n%2 != 0)
		     multiply(F, M);
		
	}
	public static void multiply(long[][] F,long[][] M)
	{
		long x =  F[0][0]*M[0][0] + F[0][1]*M[1][0];
		long y =  F[0][0]*M[0][1] + F[0][1]*M[1][1];
		long z =  F[1][0]*M[0][0] + F[1][1]*M[1][0];
		long w =  F[1][0]*M[0][1] + F[1][1]*M[1][1];
		F[0][0] = x%mod;
		F[0][1] = y%mod;
		F[1][0] = z%mod;
		F[1][1] = w%mod;
	}
}
