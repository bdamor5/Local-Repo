import java.util.*;
public class Q5 
{
	static int mod = 1000000007;
	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		long arr[][] = new long[1001][1010];
		arr[1][1] = 1;
		arr[1][2] = 2;
		arr[2][1] = 2;
		for(int i=2;i<1001;i++)
		{
			if(i>2)
				arr[i][1] = arr[i-1][i];
			for(int j=2;j<=i+1;j++)
			{
				arr[i][j] = (arr[i][j-1]+arr[i-1][j-1])%mod;
			}
		}
		while(t-->0)
		{
			int n = sc.nextInt();
			System.out.println(arr[n][1]%mod);
		}
	}

}
