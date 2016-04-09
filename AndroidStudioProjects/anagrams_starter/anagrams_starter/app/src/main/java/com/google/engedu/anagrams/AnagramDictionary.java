package com.google.engedu.anagrams;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Random;

public class AnagramDictionary
{

    private static final int MIN_NUM_ANAGRAMS = 5;
    private static final int DEFAULT_WORD_LENGTH = 3;
    private static final int MAX_WORD_LENGTH = 7;
    private static int wordLength = DEFAULT_WORD_LENGTH;

    private Random random = new Random();
    private HashSet<String> wordSet = new HashSet<String>();
    private ArrayList<String> wordList = new ArrayList<String>();
    private HashMap<String,ArrayList<String>> lettersToWord = new HashMap<String,ArrayList<String>>();
    private HashMap<Integer,ArrayList<String>> sizeToWord = new HashMap<Integer,ArrayList<String>>();


    public AnagramDictionary(InputStream wordListStream) throws IOException
    {
        BufferedReader in = new BufferedReader(new InputStreamReader(wordListStream));
        String line;



        while((line = in.readLine()) != null)
        {
            String word = line.trim();
            wordSet.add(word);
            wordList.add(word);

            String sortword = alphbeticalOrder(word);
            if(!lettersToWord.containsKey(sortword))
            {
                ArrayList<String> tmp = new ArrayList<String>();
                tmp.add(word);
                lettersToWord.put(sortword,tmp);
            }
            else
            {
                lettersToWord.get(sortword).add(word);
            }


            ArrayList<String> tmp = new ArrayList<String>();

            int l = word.length();

            if(sizeToWord.containsKey(l))
                sizeToWord.get(l).add(word);
            else
            {
                tmp.add(word);
                sizeToWord.put(l,tmp);
            }

        }
    }
    public String alphbeticalOrder(String word)
    {
        char[] charArr = word.toCharArray();
        Arrays.sort(charArr);
        String newWord = new String(charArr);
        return newWord;
    }
    public boolean isGoodWord(String word, String base)
    {
        if(wordSet.contains(word) && !word.contains(base))
            return true;

        return false;
    }

    public ArrayList<String> getAnagramsWithOneMoreLetter(String word)
    {
        ArrayList<String> result = new ArrayList<String>();

        for(int i=97;i<123;i++)
        {
            String newWord = word + (char)i;
            newWord = alphbeticalOrder(newWord);
            if(lettersToWord.containsKey(newWord))
                result.addAll(lettersToWord.get(newWord));
        }

        /* removing words which are not good!! */
        for(int i=0;i<result.size();i++)
            if(!isGoodWord(result.get(i),word))
                result.remove(i);
        return result;
    }

    public String pickGoodStarterWord()
    {
        String word = new String();
        int j;

        ArrayList<String> lengthWord = new ArrayList<String>();


        if(wordLength<=MAX_WORD_LENGTH)
            lengthWord = sizeToWord.get(wordLength);


        int i = random.nextInt(lengthWord.size());


        for(j=i;j<lengthWord.size();j++)
        {
            if(getAnagramsWithOneMoreLetter(lengthWord.get(j)).size()>=MIN_NUM_ANAGRAMS)
            {
                word = lengthWord.get(j);
                break;
            }
        }
        if(wordLength<MAX_WORD_LENGTH)
            wordLength++;
        else
            wordLength = DEFAULT_WORD_LENGTH;
        if(j==lengthWord.size())
        {
            for(j=0;j<i;j++)
            {
                if(getAnagramsWithOneMoreLetter(lengthWord.get(j)).size()>=MIN_NUM_ANAGRAMS)
                {
                    word = lengthWord.get(j);
                    break;
                }
            }
        }
        return word;
    }
}
