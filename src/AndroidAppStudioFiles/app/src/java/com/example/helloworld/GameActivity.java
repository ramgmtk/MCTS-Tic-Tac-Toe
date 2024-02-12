package com.example.helloworld;

import android.content.Intent;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.util.concurrent.atomic.AtomicBoolean;

import src.game;

public class GameActivity extends AppCompatActivity {
    Button reset_button;
    Button[] game_buttons = new Button[9];
    String player_char;
    String cpu_char;
    game my_game;
    AtomicBoolean busy;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_game);
        this.my_game = new game();
        this.busy = new AtomicBoolean(false);
        Log.i("GameActivity", "GameActivity Created");
        Bundle extras = getIntent().getExtras();
        boolean choice = extras.getBoolean("Choice");
        this.player_char = "X";
        cpu_char = "O";
        if (choice) {
            this.player_char = "O";
            this.cpu_char = "X";
        }
        Log.i("GameActivity", "Choice value:" + choice);
        //setup non game ui elements
        reset_button = findViewById(R.id.reset_button);
        reset_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startActivity(new Intent(GameActivity.this, MainActivity.class));
            }
        });

        TextView tv = findViewById(R.id.t_title);
        String title_s = "You are " + this.player_char;
        tv.setText(title_s);
        //setup buttons
        for (int i = 0; i < 9; i++) {
            String b = "button" +  Integer.toString(i + 1);
            int resId = getResources().getIdentifier(b, "id", getPackageName());
            this.game_buttons[i] = (Button)findViewById(resId);
        }
        for (int i = 0; i < 9; i++) {
            int move = i;
            this.game_buttons[i].setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    if (!busy.get()) {
                        busy.set(true);
                        my_game.playerTurn(move);
                        game_buttons[move].setEnabled(false);
                        game_buttons[move].setText(player_char);
                        if (!my_game.is_over()) {
                            int cpu_move = my_game.cpuTurn();
                            game_buttons[cpu_move].setEnabled(false);
                            game_buttons[cpu_move].setText(cpu_char);
                            if (my_game.is_over()) {
                                disableAll();
                            }
                        } else {
                            disableAll();
                        }
                        busy.set(false);
                    }
                }
            });
        }
        if (choice) {
            int cpu_move = my_game.cpuTurn();
            game_buttons[cpu_move].setEnabled(false);
            game_buttons[cpu_move].setText(cpu_char);
        }
    }

    protected void disableAll() {
        for (int i = 0; i < 9; i++) {
            this.game_buttons[i].setEnabled(false);
        }
    }
}
