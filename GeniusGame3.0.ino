long randNumber;
int sequencia[5];
int buttonState, x, y, z, acertos, vencer = 0;
int contador1 = -1;
int contador2 = 1;
int intro = 1;

const int buzer = 6;

const int buttonPin[4] = {2,3,4,5};
//const int ledPin[4] = {10,11,12,13};

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  pinMode(buttonPin, INPUT);
  //pinMode(ledPin, OUTPUT);
  pinMode(buzer, OUTPUT);
  for (byte m = 0; m <= 4; m = m + 1) { //Definir Rounds
    vencer += m;
    Serial.print("vencer ");
    Serial.println(vencer);
  }
}

void loop() {
  Intro();
  if (contador1 == -1) {
    digitalWrite(buttonPin[0] + 8, HIGH);
    digitalWrite(buttonPin[1] + 8, HIGH);
    digitalWrite(buttonPin[2] + 8, HIGH);
    digitalWrite(buttonPin[3] + 8, HIGH);
    delay(500);
    digitalWrite(buttonPin[0] + 8, LOW);
    digitalWrite(buttonPin[1] + 8, LOW);
    digitalWrite(buttonPin[2] + 8, LOW);
    digitalWrite(buttonPin[3] + 8, LOW);
    delay(500);
    contador1 += 2;
  }

  //Criacao Aleatoria da Sequencia
  while (x < contador1) {
    randNumber = random(2, 6);
    Serial.print("RandNumber ");
    Serial.println(randNumber);
    delay(500);
    sequencia[x] = randNumber;
    x++;
    y = 0;
    z = 0;
    contador2 = contador1;
    for (byte cont = 0; cont < contador1; cont = cont + 1) {
      Serial.print(sequencia[cont]);
    }
    Serial.println("");
  }

  //Acender Leds de Acordo com a Sequencia Criada
  while (z < x) {
    if (z == 0) {
      Serial.println("Memorize a Sequencia! ");
    }
    Serial.print("Ordem ");
    Serial.println(sequencia[z]);
    Serial.print("Valor z ");
    Serial.println(z);
    digitalWrite(sequencia[z] + 8, HIGH);
    delay(500);
    digitalWrite(sequencia[z] + 8, LOW);
    delay(500);
    z++;
    if (z == x) {
      Serial.print("Repita a Sequencia! ");
      Serial.println(" ");
    }
  }
  //Pressionamento dos Botões e Verificacao de Acertos
  while (y < contador2) {
    for (byte cont = 0; cont < 4; cont = cont + 1) {
      buttonState = digitalRead(buttonPin[cont]);
      if(buttonState == 1) {
        Serial.print(buttonPin[cont]);
        digitalWrite(buttonPin[cont] + 8, HIGH);
        delay(500);
        Serial.print("x = ");
        Serial.println(sequencia[y]);
        digitalWrite(buttonPin[cont] + 8, LOW);
        delay(500);
        if(sequencia[y] == buttonPin[cont]) {
          Serial.println("Acertou");
          acertos++;
          tone(buzer,660, 70);
          y++;
          if(y == contador2) {
            contador1++;
          }
        }else {
          Serial.println("Errou");
          Serial.println("Segure Botão Verde Para Iniciar Novamente");
          contador2 = 0;
          tone(buzer,100, 70);
          delay(100);
          intro = 10;
          x = 0;
          while(intro == 10) {
            Lose();
            buttonState = digitalRead(buttonPin[0]);
            if(buttonState == 1) {
              intro = 1;
              contador1 = -1;
              for (byte x = 0; x < 10; x = x + 1) {
                Serial.println("");
              }
            }
            delay(500);
          }
        } 
      }
    }
   }  

   //Garantir Estado do Botao = 0
   Apagar();

   //Acertando Toda Sequencia
   if(acertos == vencer) {//1+2+3+4
     contador1 = 0;
     acertos = 0;
     Serial.println("Ganhou");
     Serial.println("Pressiona Botão Verde Para Iniciar Novamente");
     Win();
   } else if (contador1 == 0) {
     digitalWrite(buttonPin[0] + 8, LOW);
     delay(500);
     digitalWrite(buttonPin[0] + 8, HIGH);
     delay(500);
     digitalWrite(buttonPin[0] + 8, LOW);
     Win();
     buttonState = digitalRead(buttonPin[0]);
      if(buttonState == 1) {
        digitalWrite(10, 0);
        contador2 = 0;
        intro = 1;
        x = 0;
        contador1 = -1;
        for (byte x = 0; x < 10; x = x + 1) {
          Serial.println("");
        }
        delay(500);
      }
   } 
}

void Apagar() {
  buttonState = 0;
  for (byte x = 0; x < 4; x = x + 1) {
      digitalWrite(buttonPin[x], LOW);
  }
}

void Intro() {
  if (intro == 1) {
    tone(buzer,660, 70); //e12
    digitalWrite(buttonPin[0] + 8, HIGH);
    delay(150);
    digitalWrite(buttonPin[0] + 8, LOW);
    tone(buzer,660, 70); //e12
    digitalWrite(buttonPin[1] + 8, HIGH);
    delay(150);
    digitalWrite(buttonPin[1] + 8, LOW);
    tone(buzer,660, 70); //e12
    digitalWrite(buttonPin[2] + 8, HIGH);
    delay(150);
    digitalWrite(buttonPin[2] + 8, LOW);
    tone(buzer,524, 100); //B13
    digitalWrite(buttonPin[3] + 8, HIGH);
    delay(150);
    digitalWrite(buttonPin[3] + 8, LOW);
    tone(buzer,660, 100); //e12
    digitalWrite(buttonPin[2] + 8, HIGH);
    delay(200);
    digitalWrite(buttonPin[2] + 8, LOW);
    tone(buzer,830, 50); //e15
    digitalWrite(buttonPin[1] + 8, HIGH);
    delay(200);
    digitalWrite(buttonPin[1] + 8, LOW);
    delay(300);
    tone(buzer,391, 50); //G12
    digitalWrite(buttonPin[0] + 8, HIGH);
    digitalWrite(buttonPin[1] + 8, HIGH);
    digitalWrite(buttonPin[2] + 8, HIGH);
    digitalWrite(buttonPin[3] + 8, HIGH);
    delay(500);
    digitalWrite(buttonPin[0] + 8, LOW);
    digitalWrite(buttonPin[1] + 8, LOW);
    digitalWrite(buttonPin[2] + 8, LOW);
    digitalWrite(buttonPin[3] + 8, LOW);
    delay(500);
    intro++;
  }
}

void Win() {
  tone(buzer,330*8, 70); //D14
  delay(40);
  tone(buzer,400*8, 70); //G12
  delay(40);
  tone(buzer,660*8, 70); //B17
  delay(40);
  tone(buzer,524*8, 70); //B13
  delay(40);
  tone(buzer,588*8, 70); //B15
  delay(40);
  tone(buzer,800*8, 100); //e15
}

void Lose() {
  digitalWrite(buttonPin[0] + 8, HIGH);
  tone(buzer,100, 100);
  digitalWrite(buttonPin[0] + 8, LOW);
  delay(300);
  digitalWrite(buttonPin[0] + 8, HIGH);
  tone(buzer,200, 100);
  digitalWrite(buttonPin[0] + 8, LOW);
  delay(300);
  tone(buzer,100, 100);
  digitalWrite(buttonPin[0] + 8, HIGH);
  delay(300);
  tone(buzer,300, 200);
  digitalWrite(buttonPin[0] + 8, LOW);
  delay(300);
  digitalWrite(buttonPin[0] + 8, HIGH);
}
