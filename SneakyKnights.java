/*
Name: Juan Gonzalez
*/
import java.util.*;

public class SneakyKnights
{
    public static boolean allTheKnightsAreSafe(ArrayList<String> coordinateStrings, int boardSize)
    {
        HashSet<Long> hash = new HashSet<>(coordinateStrings.size() );
        //attack coordinate offsets
        int[]attackx = {2,2,-2,-2,1,1,-1,-1 };
        int[]attacky = {1,-1,1,-1,2,-2,2,-2 };
        //check if any attacks are possible, and insert into the hashset
        for(String some : coordinateStrings )
        {
            //conversions
            String temp =some.split("(\\d)")[0];
            Long x = conv(temp);
            Long y = conv( some.substring(temp.length()) );

            Long cx=x;//dont change x
            Long cy=y;//same here

            for(int i=0; i<8;i++)
            {
                cx=x+attackx[i];
                cy=y+attacky[i];
                //cant be larger than int max so 32 bit
                if(hash.contains((cx << 32) | cy))
                    return false;//attack
            }
            hash.add( (x <<32)  | y );
        }
        //all good
        return true;
        
    }

  	static long conv(String factor)
  	{
        long retVal=0;
        try
        {
            //if its a normal number we good
            return Long.parseLong(factor);

    	}catch(Exception e)
        {
        	//base 26 conversion. power is inverted so start from end.
        	for(int i=factor.length()-1;i>=0;i-- )
        	{
                long reali= (factor.length()-1) -i;
                retVal+=((factor.charAt(i)-'a')+1)*Math.pow(26,reali);
            }
            return retVal;
        }
    }
}
