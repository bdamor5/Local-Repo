import java.util.*;
public class Q4 
{

	static int ans;
	public static void main(String[] args) 
	{
		Scanner sc = new Scanner(System.in);
		int t = sc.nextInt();
		sc.nextLine();
		while(t-->0)
		{
			ans=0;
			String n =sc.nextLine();
			
			int arr[] = new int[n.length()];
			int[] pre = new int[arr.length+1];
			for(int i=0;i<arr.length;i++)
			{
				arr[i] = n.charAt(i)-48;
				
				pre[i+1]=pre[i]+arr[i];
				//System.out.println(pre[i+1]);
			}
			solve(arr,pre,0,0);
			System.out.println(ans);
		}

	}
	public static void solve(int[] arr,int[] prefix,int prev,int index)
	{
		for(int i=index;i<arr.length;i++)
		{
			int curr = prefix[i+1]-prefix[index];
			//System.out.println(curr+" "+prefix[prefix.length-1]);
			
			if(curr>=prev && curr<=prefix[prefix.length-1]-prefix[i+1])
			{
				solve(arr,prefix,curr,i+1);
			}
		}
		ans++;
	}

}
