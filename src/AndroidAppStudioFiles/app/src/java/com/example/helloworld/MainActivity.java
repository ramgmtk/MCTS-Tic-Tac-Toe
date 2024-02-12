package com.example.helloworld;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    public Button x_button;
    public Button o_button;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        x_button = findViewById(R.id.x_button);
        o_button = findViewById(R.id.o_button);

        x_button.setOnClickListener(new View.OnClickListener() {
            //credit https://stackoverflow.com/questions/24610527/how-do-i-get-a-button-to-open-another-activity
                @Override
                public void onClick(View view) {
                    //credit to user914425 https://stackoverflow.com/questions/2091465/how-do-i-pass-data-between-activities-in-android-application
                    startActivity(new Intent(MainActivity.this, GameActivity.class).putExtra("Choice", false));
                    Log.i("x", "button clicked");
                }
            }
        );

        o_button.setOnClickListener(new View.OnClickListener() {
                @Override

                public void onClick(View view) {

                    startActivity(new Intent(MainActivity.this, GameActivity.class).putExtra("Choice", true));
                    Log.i("o", "button clicked");
                }
            }
        );
    }
}