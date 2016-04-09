package com.example.uttam.scarnesdicegame;

import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.TranslateAnimation;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.Random;
import java.util.concurrent.TimeUnit;

import static java.lang.Thread.sleep;

public class MainActivity extends AppCompatActivity
{
    TextView tvStatus;
    ImageView ivImage;
    Button bRoll, bHold, bReset;

    private int USER_OVERALL_SCORE = 0;
    private int USER_TURN_SCORE = 0;
    private int COMP_OVERALL_SCORE = 0;
    private int COMP_TURN_SCORE = 0;
    Handler handler = new Handler();
    Animation anim,anim2;

    Random random = new Random();
    private int diceImages[] = {R.drawable.dice1,R.drawable.dice2,R.drawable.dice3,R.drawable.dice4,R.drawable.dice5,R.drawable.dice6};

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tvStatus = (TextView) findViewById(R.id.scoreTextView1);
        ivImage = (ImageView) findViewById(R.id.imageView);

        bHold = (Button) findViewById(R.id.holdButton);
        bRoll = (Button) findViewById(R.id.rollButton);
        bReset = (Button) findViewById(R.id.resetButton);

        anim = new TranslateAnimation(0.0f,200.0f,0.0f,0.0f);
        anim.setDuration(200);

        anim2 = new TranslateAnimation(0.0f,-200.0f,0.0f,0.0f);
        anim2.setDuration(200);


        bRoll.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v)
            {
                final int score = random.nextInt(6) + 1 ;

                handler.postDelayed(new Runnable() {
                    @Override
                    public void run()
                    {
                        ivImage.setAnimation(null);
                        ivImage.setAnimation(anim);
                        ivImage.setImageResource(diceImages[score - 1]);


                    }
                }, 1000);

                try {
                    TimeUnit.MILLISECONDS.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                if(score == 1) {
                    USER_TURN_SCORE = 0;
                    tvStatus.setText("Comp Score: " + COMP_OVERALL_SCORE + " User Score: " + USER_OVERALL_SCORE + " \nUser turn Score: " +
                            USER_TURN_SCORE + " Comp turn Score: " + COMP_TURN_SCORE);
                    Toast.makeText(MainActivity.this,"Computer's Turn!! ",Toast.LENGTH_SHORT).show();
                    computerTurn(random.nextInt(4) +1);
                }
                else
                    USER_TURN_SCORE += score;
                tvStatus.setText("Comp Score: " + COMP_OVERALL_SCORE + " User Score: " + USER_OVERALL_SCORE + " \nUser turn Score: " +
                        USER_TURN_SCORE + " Comp turn Score: " + COMP_TURN_SCORE);


                if(USER_OVERALL_SCORE+USER_TURN_SCORE>=100)
                {
                    Toast.makeText(MainActivity.this,"You Win!! ",Toast.LENGTH_SHORT).show();

                    COMP_OVERALL_SCORE = 0;
                    COMP_TURN_SCORE = 0;
                    USER_OVERALL_SCORE = 0;
                    USER_TURN_SCORE = 0;

                    tvStatus.setText("Your Score: " + USER_OVERALL_SCORE + "  Computer Score: " + COMP_OVERALL_SCORE);
                }
            }

        });

        bHold.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                USER_OVERALL_SCORE += USER_TURN_SCORE;
                USER_TURN_SCORE = 0;

                tvStatus.setText("Comp Score: " + COMP_OVERALL_SCORE + " User Score: " + USER_OVERALL_SCORE + " \nUser turn Score: " +
                        USER_TURN_SCORE + " Comp turn Score: " + COMP_TURN_SCORE);

                Toast.makeText(MainActivity.this, "Computer's Turn!! ",Toast.LENGTH_SHORT).show();
                computerTurn(random.nextInt(4) +1);
            }
        });

        bReset.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v)
            {
                COMP_OVERALL_SCORE = 0;
                COMP_TURN_SCORE = 0;
                USER_OVERALL_SCORE = 0;
                USER_TURN_SCORE = 0;

                tvStatus.setText("Your Score: "+USER_OVERALL_SCORE+"  Computer Score: "+COMP_OVERALL_SCORE);
            }
        });


    }
    public void computerTurn(int no_Turns)
    {

        if(no_Turns==0)
        {
            Toast.makeText(MainActivity.this,"Your Turn!! ",Toast.LENGTH_SHORT).show();
            COMP_OVERALL_SCORE += COMP_TURN_SCORE;
            COMP_TURN_SCORE = 0;
            tvStatus.setText("Comp Score: " + COMP_OVERALL_SCORE + " User Score: " + USER_OVERALL_SCORE + " \nUser turn Score: " +
                    USER_TURN_SCORE + " Comp turn Score: " + COMP_TURN_SCORE);
            return;
        }

        Log.d("UC","computer's numbre of roll "+no_Turns);

            final int score = random.nextInt(4) + 2;
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                ivImage.setAnimation(null);
                ivImage.setAnimation(anim2);
                ivImage.setImageResource(diceImages[score - 1]);
                }
            }, 1000);

            try {
                TimeUnit.MILLISECONDS.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            if(score==1)
            {
                COMP_TURN_SCORE = 0;
                Toast.makeText(MainActivity.this,"Your Turn!! ",Toast.LENGTH_SHORT).show();
                tvStatus.setText("Comp Score: " + COMP_OVERALL_SCORE + " User Score: " + USER_OVERALL_SCORE + " \nUser turn Score: " +
                        USER_TURN_SCORE + " Comp turn Score: " + COMP_TURN_SCORE);
                return;
            }
            else
                COMP_TURN_SCORE += score;
            tvStatus.setText("Comp Score: " + COMP_OVERALL_SCORE + " User Score: " + USER_OVERALL_SCORE + " \nUser turn Score: " +
                    USER_TURN_SCORE + " Comp turn Score: " + COMP_TURN_SCORE);

            if(COMP_OVERALL_SCORE+COMP_TURN_SCORE>=100)
            {
                Toast.makeText(MainActivity.this,"Computer Win!! ",Toast.LENGTH_SHORT).show();
                Toast.makeText(MainActivity.this,"New Game Started ",Toast.LENGTH_SHORT).show();
                COMP_OVERALL_SCORE = 0;
                COMP_TURN_SCORE = 0;
                USER_OVERALL_SCORE = 0;
                USER_TURN_SCORE = 0;

                tvStatus.setText("Your Score: " + USER_OVERALL_SCORE + "  Computer Score: " + COMP_OVERALL_SCORE);
            }


        tvStatus.setText("Comp Score: " + COMP_OVERALL_SCORE + " User Score: " + USER_OVERALL_SCORE + " \nUser turn Score: " +
                USER_TURN_SCORE + " Comp turn Score: " + COMP_TURN_SCORE);

        computerTurn(--no_Turns);
    }

}
