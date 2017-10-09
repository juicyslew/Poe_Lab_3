const byte IR[2] = {A0, A1};

long prev_t = 0;
int ir_val[2] = {100, 100};
String result = "";

void setup() {
  // put your setup code here, to run once:
  pinMode(IR[0], INPUT);
  pinMode(IR[1], INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  ir_val[0] = analogRead(IR[0]);
  ir_val[1] = analogRead(IR[1]);

  result = result + ir_val[0] + "|" + ir_val[1];
  Serial.println(result);
  result = "";
}
