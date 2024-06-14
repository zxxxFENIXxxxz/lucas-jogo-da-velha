int pos = 0; 
int y=0;
boolean tie=false; 
int button1_state = LOW;
int button2_state = LOW;
int player2_count = 10;
 
int player = 1;
int places = 0;

boolean game_over = false;
 
boolean blink = true;
 
int leds[] = {13, 12,11,
              10, 9, 8, 
              7,  6, 5 };

int state[] = {0, 0, 0,
               0, 0, 0,  
               0, 0, 0 };

 
void setup()
{
  Serial.begin(9600);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  for (int n=0; n < 9; n++) pinMode(leds[n], OUTPUT);
}

void move_pos()
{
  if(places<9)
  {
   boolean ok = false;
    
     while(!ok)
    {
      pos++;
      if (pos > 8) pos = 0;
      if (state[pos] == 0) ok = true;
     }
  }
}

void check_gameover()
{

  
  
    if(places==9&&state[0]>0&&state[1]>0&&state[2]>0&&
     state[3]>0&&state[4]>0&&state[5]>0&&
     state[6]>0&&state[7]>0&&state[8]>0)
  {
   
    game_over=true;
    pos=99;
    
    tie=true;
    
    
    
  }
  
    int x;
  
  x=player;
    
  if(state[0]==x&&state[1]==x&&state[2]==x||
     state[3]==x&&state[4]==x&&state[5]==x||
     state[6]==x&&state[7]==x&&state[8]==x||
     state[0]==x&&state[3]==x&&state[6]==x||
     state[1]==x&&state[4]==x&&state[7]==x||
     state[0]==x&&state[4]==x&&state[8]==x||
     state[2]==x&&state[4]==x&&state[6]==x||
     state[2]==x&&state[5]==x&&state[8]==x)
   
  {   
    pos=99;
    game_over=true;
    tie=false;
  }
 

  
}
 
void check_button1()
{
  // BUTTON 1
  int button = digitalRead(3);
  
  if (button == HIGH && button1_state == LOW)
  {
    button1_state = HIGH;
    
    move_pos();
  }
   
  if (button == LOW && button1_state == HIGH) button1_state = LOW;
}
 
void check_button2()
{
  // BUTTON 2
  int button = digitalRead(2);
  
  if (button == HIGH && button2_state == LOW)
  {
    // set led state
    state[pos] = player;
    
    places++;
    
    move_pos();
    
    button2_state = HIGH;
    
    check_gameover();
    
    if(places==9) game_over=true;
    
    // next player
    player++;
    if (player > 2) player = 1;
         
  }
  
  if (button == LOW && button2_state == HIGH)
    
  {
    y++;
    button2_state = LOW;
  }
}
 
void setLed(int id, int player)
{
  if (player == 0)
  {
    digitalWrite(id, LOW);
  }
  
  if (player == 1)
  {
    digitalWrite(id, HIGH);
  }
  
  if (player == 2)
  {
    if (player2_count > 5)
    {
      digitalWrite(id, HIGH);
    }
    else
    {
      
      digitalWrite(id, LOW);
    }
  }
}
 
void loop()
{
  if (!game_over)
  {
    check_button1();
    check_button2();    
  }
  
  if(game_over==true)
  {
    
  
      
    if(player==2&&tie==false)
    {
    state[0]= 1; state[1]=0; state[2]=1;
    state[3]= 0; state[4]=1; state[5]=0;
    state[6]= 1; state[7]=0; state[8]=1;
    }
    
   
   		if(player==1&&tie==false)
   	 	{
    	state[0]= 1; state[1]=1; state[2]=1;
    	state[3]= 1; state[4]=0; state[5]=1;
    	state[6]= 1; state[7]=1; state[8]=1;
    	}  
    
    	if(tie==true)
        {
    	state[0]= 1; state[1]=1; state[2]=1;
    	state[3]= 1; state[4]=0; state[5]=1;
    	state[6]= 1; state[7]=0; state[8]=1;
        }
  
     }
     
    Serial.println(places);
 
  for (int n=0; n < 9; n++)
  {
    
    if (n != pos) setLed(leds[n], state[n]);
  }
  
  if (!game_over)
  {
    if (blink) 
      digitalWrite(leds[pos], HIGH);
    else
      digitalWrite(leds[pos], LOW);
    
    blink = !blink;
  }
  
  
  
  player2_count--;
  if (player2_count < 0) player2_count = 10;

  delay(100);
  
}