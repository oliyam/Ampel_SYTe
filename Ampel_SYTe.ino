const int size_=3;
int led_pins[]={2,3,4},pin_switch=5;
bool led_state[size_]={0,0,0};

//ampelzyklus
bool cycle_[][size_]={
    {0,0,1},//grün
    {0,0,0},{0,0,1},{0,0,0},{0,0,1},{0,0,0},{0,0,1},{0,0,0},{0,0,1},//grün blinken
    {0,1,0},//gelb
    {1,0,0},//rot
    {1,1,0}//rotgelb
};
long cycle_interval[]={
    4500,//grün dauer
    500,500,500,500,500,500,500,500,//grün blinken dauer
    2500,//gelb dauer
    5000,//rot dauer
    2500//rotgelb dauer
};
//gelb blinken
bool blink_[][size_]={
    {0,1,0},//gelb an
    {0,0,0}//gelb aus
};
long blink_interval[]={
    500,//gelb an dauer
    500//gelb aus dauer
};

void setup()
{
  Serial.begin(9600);
  for(int i=0;i<size_;i++)
    pinMode(led_pins[i], OUTPUT);
  pinMode(pin_switch, INPUT);
}

int now_blink=0,now_cycle=0;
unsigned long previous=0,current=millis();

void update(bool cycle[][size_], long interval[], bool output[], int& now, int cycle_length){
  if(current-previous>=interval[now]){
    previous=current;
    now=(now+1)%cycle_length;
    for(int i=0;i<size_;i++)
      output[i]=cycle[now][i];
  }
}

void loop()
{ 
  current=millis();
  
  if(digitalRead(pin_switch)){
    update(cycle_,cycle_interval,led_state,now_cycle,sizeof(cycle_)/size_);
    now_blink=0;
  }
  else{
    update(blink_,blink_interval,led_state,now_blink,sizeof(blink_)/size_);
    now_cycle=0;
  }
  //write to pins
  for(int i=0;i<size_;i++)
    digitalWrite(led_pins[i],led_state[i]);
}
