package codemutant;
import java.io.BufferedInputStream;
import java.io.IOException;
import java.util.*;
public class Q1 
{

	public static void main(String[] args) 
	{
		
		int n = FastIO.readInt();
		
		String s = FastIO.read();
		int q = FastIO.readInt();
		int dar[][] = new int[s.length()][26];
		for(int i=0;i<s.length();i++)
		{
			dar[i][s.charAt(i)-97]++;	
		}
		for(int i=1;i<s.length();i++)
			for(int j=0;j<26;j++)
				dar[i][j]+=dar[i-1][j];
		while(q-->0)
		{
			int l = FastIO.readInt();
			int r = FastIO.readInt();
			
			String s1 = s.substring(l-1,r);
			//System.out.println(s1);
				int arr[] = new int[26];
				for(int i=0;i<26;i++)
				{
					arr[i] = dar[r-1] [i];
					if(l-2>=0)
						arr[i]-=dar[l-2][i];
				}
				//for(int i=0;i<s1.length();i++)
				//	arr[s1.charAt(i)-97]++;
				int count=0;
				for(int i=0;i<26;i++)
					if(arr[i]%2==1)
						count++;
				if(count<=2 && s1.length()>=2)
					System.out.println("YES");
				else
					System.out.println("NO");
			
			
		}

	}
	
}
class FastIO
{
    static BufferedInputStream in = new BufferedInputStream(System.in);
    static int readInt() {
        int no = 0;
        boolean minus = false;
        try {
            int a = in.read();
            while (a == 32 || a == 10) //10 is newline & 32 is AFastIOII for space
                a = in.read();
            if (a == '-') {
                minus = true;
                a = in.read();
            }
            while (a != 10 && a != 32 && a != -1) {
                no = no * 10 + (a - '0');
                a = in.read();
            }
        }catch (IOException e) {
            e.printStackTrace();
        }
        return minus ? -no: no;
    }
    static String read() {
        StringBuilder str = new StringBuilder();
        try {
            int a = in.read();
            while (a == 32)
                a = in.read();
            while (a != 10 && a != 32 && a != -1) {
                str.append((char)a);
                a = in.read();
            }
        } catch(Exception e) {
            e.printStackTrace();
        }
        return str.toString();
    }
    public static void main (String[] args) {
        /*Accepting input in the format
         *<integer> <word>
         */
        int no = readInt();
        String str = read();
    }
}
