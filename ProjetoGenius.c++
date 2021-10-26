/*******************************************************************************
 Projeto Jogo Genius - Arduino
*******************************************************************************/

const int c = 261; // Do
const int d = 293; // Re
const int e = 329; // Mi

const int ERRO = 11;
const int ledG = 10;
const int ledB = 9;
const int ledY = 8;
const int b1 = 6;
const int b2 = 5;
const int b3 = 4;
const int pino_buzzer = 7;

int level = 0, i, compara = 0; 
long notas[50] , resultado[50];

bool flag = LOW, flag_b1 = LOW, flag_b2 = LOW, flag_b3 = LOW, decrease = LOW;

void setup() {
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(pino_buzzer, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledY, OUTPUT);
  pinMode(ERRO, OUTPUT);
  Serial.begin(9600);
  randomSeed(analogRead(0));

}

void loop() {
  notas[level] = random(1, 4);
  delay(10);
  for ( i = 0; i < level; i++) {
    if (notas[i] == 1) {
      tone(pino_buzzer, c);
      digitalWrite(ledG, HIGH);
      delay(500);
      noTone(pino_buzzer);
      digitalWrite(ledG, LOW);
    }
    else if (notas[i] == 2) {
      tone(pino_buzzer, d);
      digitalWrite(ledB, HIGH);
      delay(500);
      noTone(pino_buzzer);
      digitalWrite(ledB, LOW);
    }
    else {
      tone(pino_buzzer, e);
      digitalWrite(ledY, HIGH);
      delay(500);
      noTone(pino_buzzer);
      digitalWrite(ledY, LOW);
    }
    delay(500);
  }
  flag = HIGH;
  i = 0;
  compara = 0;

  while (flag == HIGH) {
    bool leitura_b1 = digitalRead(b1);
    bool leitura_b2 = digitalRead(b2);
    bool leitura_b3 = digitalRead(b3);
    if ( i < level) {
      if (leitura_b1 == LOW) {
        flag_b1 = HIGH;
        while(digitalRead(b1) == LOW){}
      } else if (leitura_b1 == HIGH && flag_b1 == HIGH) {
        resultado[i] = 1;
        i++;
        flag_b1 = LOW;
      }
      if (leitura_b2 == LOW) {
        flag_b2 = HIGH;
        while(digitalRead(b2) == LOW){}
      } else if (leitura_b2 == HIGH && flag_b2 == HIGH) {
        resultado[i] = 2;
        i++;
        flag_b2 = LOW;
      }
      if (leitura_b3 == LOW) {
        flag_b3 = HIGH;
        while(digitalRead(b3) == LOW){}
      } else if (leitura_b3 == HIGH && flag_b3 == HIGH) {
        resultado[i] = 3;
        i++;
        flag_b3 = LOW;
      }
      delay(100);
    } else {
      for (int i = 0; i < level; i++) {
        resultado[i] = (resultado[i] - notas[i]);
        if (resultado[i] < 0) {
          resultado[i] = resultado[i] * -1;
        }
        compara = compara + resultado[i];
        Serial.println(compara);
        if (compara > 0) {
          decrease = HIGH;
        } else {
          decrease = LOW;
        }
      }
      if (decrease == HIGH) {
        level = 0;
        decrease = LOW;
        Serial.print("Voce errou !");
        for (i = 0; i < 5; i++) {
          digitalWrite(ERRO, HIGH);
          delay(50);
          digitalWrite(ERRO, LOW);
          delay(50);
        }
      } else {
        level++;
        Serial.print("Parabens! Voce avancou para o proximo level ");
        Serial.println(level);
      }
      flag = LOW;
      delay(500);
    }
  }
}