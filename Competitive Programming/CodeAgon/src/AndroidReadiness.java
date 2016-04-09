/* 
 * Java is the primary programming language used when building for Android,
 * and this quiz is designed to warm-up your Java programming skills:
 * 
 * There are some missing elements from Human.java and Superhero.java 
 * (see tabs above this window for details) that we could use your help to complete! 
 *
 * --TASK OVERVIEW--
 * In Human.java:
 * - Implement the Comparable Interface using the age field as the differentiator.
 * In Superhero.java:
 * - Extend the class Superhero as a subclass of Human.
 * - Add a String field that stores the hero's alter ego.
 * - Modify the given constructor by adding the alter ego as an additional parameter
 *   and setting it.
 * - Override the introduce() method to ALSO return the alter ego.
 *
 * Feel free to this use space as a sandbox to get started:
 * - Create some Humans and Superheroes.
 * - Have them introduce themselves.
 * - Sort Them!
 * 
 * We recommend testing your code via the "Test Run" button, and
 * submit your completed code with the "Submit" button when you're ready!
 *
 * You can submit as many times as you'd like. There is no penalty 
 * for multiple submissions; the quiz will only retain your most 
 * recent submission. 
*/
import java.util.*;
import java.io.*;

public class AndroidReadiness
{
    public static void main(String[] args) throws IOException
    {
        // Test your code here:
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
         //Write code to receive input
		ArrayList<Human> hm = new ArrayList<Human>(n);
        // Some sample instances
        for(int i=0;i<n;i++)
        {
        	String what = sc.next();
        	if(what.equals("Superhero"))
        		hm.add(new Superhero(sc.next(),sc.nextInt(),sc.next()));
        	else	
        		hm.add(new Human(sc.next(), sc.nextInt()));
        // Create some more characters!
  
        }
        for(int i=0;i<n;i++)
        	System.out.println(hm.get(i).introduce());
        // Make some introductions
        // Note: Superheroes should also share their alter ego! For example,
        // System.out.println(batman.introduce());
        // should print to std out:

        // Hey! I'm Bruce and I'm 26 years old. I'm also known as Batman!
       
        
        
        // Testing your Comparable Interface:
        // Create multiple Humans/Superheros and add them to an ArrayList
        // Example:
        // Superhero ironman = new Superhero("Tony", 35, "Ironman");
        // Human rachel = new Human("Rachel", 22);
        
        // List<Human> people = new ArrayList<Human>();
        // people.add(batman);
        // people.add(rachel);
        // people.add(ironman);
        // people.add(pepper);
        
        
        // Then sort your list (which uses your interface implementation) 
         Collections.sort(hm);
         for(int i=0;i<n;i++)
         	System.out.println(hm.get(i).getAge());
        // Print the age in sorted order (ascending order)
    }
}
class Human implements Comparable<Human> {
 private int age;
    private String name;
    
     public Human(String givenName, int age) {
        this.name = givenName;
        this.age = age;
    }
    
    public String getName() {
        return name;
    }
    
    public int getAge() {
        return age;
    }
    
    public String introduce() {
        return "Hey! I'm " + this.getName() + " and I'm " + this.getAge() + " years old.";
    }
    
    public int compareTo(Human a)
    {
    	if(this.age==a.getAge())
    		return 0;
    	else
	        return this.age > a.getAge() ? 1 : -1;
    }
    // Hint: Implement the method required by the Comparable Interface 
    // using age as the differentiator
}

/*
 * - TASK: Extend the class Superhero as a subclass of Human.
 * - TASK: Add a String field that stores the hero's alter ego!
 * - TASK: Modify the given constructor by adding the alter ego as an additional parameter
 *   and setting it.
 * - TASK: Override the introduce() method to ALSO include the alter ego! (In other words,
 *   you should call the superclass introduce method when you override the method.)
*/

class Superhero extends Human 
{
	private String alterEgo;
    
    public Superhero(String givenName, int age, String alterEgo) 
    {
        super(givenName, age);
        this.alterEgo = alterEgo;
    }
    
    public String getAlterEgo() 
    {
        return alterEgo;
    }
    public String introduce() 
    {
        return "Hey! I'm " + this.getName() + " and I'm " + this.getAge() + " years old."+" I'm also known as "+this.getAlterEgo();
    }
    
}
  