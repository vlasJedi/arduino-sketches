// port for temp and humidity sensor
const int port = 13;
const int waitNumber = 10000;
// first 4 - are digits positions
const int cathodCount = 4;
const int commonCathodPorts[cathodCount] = {2, 3, 4, 5};
// next 7 - are segments of digit (a, b, c, d, e, f, g)
const int segmentsCount = 7;
const int segmentsPortsSequence[segmentsCount] = {6, 7, 8, 9, 10, 11, 12};
void setup() {
  // put your setup code here, to run once:
  int i = 0;
  while(i < cathodCount) {
    pinMode(commonCathodPorts[i], OUTPUT);
    i++;
  }
  i = 0;
  while(i < segmentsCount) {
    pinMode(segmentsPortsSequence[i], OUTPUT);
    i++;
  }
  
}

float output[2];

void loop() {
  // put your main code here, to run repeatedly:
  readTHdata(output);
  const int renderingTime = 4000;
  int i = 0;
  while (i < renderingTime) {
    render();
    i += 20;
  }
  delay(20);
  
  //useDigitPosition(-1);
}

void render() {
  displayNumber((int) output[0], 2, 0);
  displayNumber((int) output[1], 2, 2);
  delay(20);
}

void displayNumber(int number, int count, int start) {
  int i = 0;
  int val = number;
  // remove any previous highlighted digits
  displayDigit(-1);
  useDigitPosition(-1);
  while(i < count) {
    // do nothing
    if (val == 0) {
      displayDigit(-1);
      useDigitPosition(-1);
      i++;
      continue;
    // display specific digit
    } else {
      int rest = val % 10;
      // apply voltage
      displayDigit(rest);
      val = (val - rest) / 10;
      useDigitPosition(cathodCount - start - 1 - i);
      delay(1);
      // relax voltage
      displayDigit(-1);
      useDigitPosition(-1);
      i++;
    }
  }
}

void useDigitPosition(int id) {
  int i = 0;
  while(i < cathodCount) {
     if (i == id) {
       digitalWrite(commonCathodPorts[i], LOW);
     } else {
       digitalWrite(commonCathodPorts[i], HIGH);
     }
     i++;
  }
}

void displayDigit(int digit) {
  switch(digit) {
    case 0:
      displayZero();
      break;
    case 1:
      displayOne();
      break;
    case 2:
      displayTwo();
      break;
    case 3:
      displayThree();
      break;
    case 4:
      displayFour();
      break;
    case 5:
      displayFive();
      break;
    case 6:
      displaySix();
      break;
    case 7:
      displaySeven();
      break;
    case 8:
      displayEight();
      break;
    case 9:
      displayNine();
      break;
    default:
      displayEmpty();
  }
}

void displayEmpty() {
  int i = 0;
  while(i < segmentsCount) {
    digitalWrite(segmentsPortsSequence[i], LOW);
    i++;
  }
}

void displayZero() {
  int i = 0;
  const int exclusionSegment = 6;
  while(i < segmentsCount) {
    if (i == exclusionSegment) {
      digitalWrite(segmentsPortsSequence[i], LOW);
    } else {
      digitalWrite(segmentsPortsSequence[i], HIGH);
    }
    i++;
  }
}

void displayOne() {
  int i = 0;
  while(i < segmentsCount) {
    if (i == 1 || i == 2) {
      digitalWrite(segmentsPortsSequence[i], HIGH);
    } else {
      digitalWrite(segmentsPortsSequence[i], LOW);
    }
    i++;
  }
}

void displayTwo() {
  int i = 0;
  while(i < segmentsCount) {
    if (i == 2 || i == 5) {
      digitalWrite(segmentsPortsSequence[i], LOW);
    } else {
      digitalWrite(segmentsPortsSequence[i], HIGH);
    }
    i++;
  }
}

void displayThree() {
  int i = 0;
  while(i < segmentsCount) {
    if (i == 4 || i == 5) {
      digitalWrite(segmentsPortsSequence[i], LOW);
    } else {
      digitalWrite(segmentsPortsSequence[i], HIGH);
    }
    i++;
  }
}

void displayFour() {
  int i = 0;
  while(i < segmentsCount) {
    if (i == 1 || i == 2 || i == 5 || i == 6) {
      digitalWrite(segmentsPortsSequence[i], HIGH);
    } else {
      digitalWrite(segmentsPortsSequence[i], LOW);
    }
    i++;
  }
}

void displayFive() {
  int i = 0;
  while(i < segmentsCount) {
    if (i == 1 || i == 4) {
      digitalWrite(segmentsPortsSequence[i], LOW);
    } else {
      digitalWrite(segmentsPortsSequence[i], HIGH);
    }
    i++;
  }
}

void displaySix() {
  int i = 0;
  const int exclusionSegment = 1;
  while(i < segmentsCount) {
    if (i == exclusionSegment) {
      digitalWrite(segmentsPortsSequence[i], LOW);
    } else {
      digitalWrite(segmentsPortsSequence[i], HIGH);
    }
    i++;
  }
}

void displaySeven() {
  int i = 0;
  while(i < segmentsCount) {
    if (i == 0 || i == 1 || i == 2) {
      digitalWrite(segmentsPortsSequence[i], HIGH);
    } else {
      digitalWrite(segmentsPortsSequence[i], LOW);
    }
    i++;
  }
}

void displayEight() {
  int i = 0;
  while(i < segmentsCount) {
    digitalWrite(segmentsPortsSequence[i], HIGH);
    i++;
  }
}

void displayNine() {
  int i = 0;
  const int exclusionSegment = 4;
  while(i < segmentsCount) {
    if (i == exclusionSegment) {
      digitalWrite(segmentsPortsSequence[i], LOW);
    } else {
      digitalWrite(segmentsPortsSequence[i], HIGH);
    }
    i++;
  }
}

// Temp and humidity sensor


int readTHdata(float* output) {
    int bits[40];
    unsigned long timeStart;
    pinMode(port, OUTPUT);
    // ask session
    digitalWrite(port, LOW);
    delay(18);
    digitalWrite(port, HIGH);
    delayMicroseconds(40);
    pinMode(port, INPUT);
    // wait for response
    int res = waitUntil(port, LOW, waitNumber);
    if (res == -1) return -1;
    res = waitUntil(port, HIGH, waitNumber);
    if (res == -1) return -1;
    // data transfer starts
    for (int i = 0; i < 40; i++) {
        res = waitUntil(port, LOW, waitNumber);
        if (res == -1) return -1;
        res = waitUntil(port, HIGH, waitNumber);
        if (res == -1) return -1;
        timeStart = micros();
        res = waitUntil(port, LOW, waitNumber);
        if (res == -1) return -1;
        if (micros() - timeStart >= 40) bits[i] = 1;
        else bits[i] = 0;
    }
    return decodeTempAndHum(bits, output);
}

int decodeTempAndHum(int bits[], float* output) {
    *(output) = toDecimal(bits, 0, 15) / 10.0;
    *(output + 1) = toDecimal(bits, 16, 31) / 10.0;
    return 0;
}

int toDecimal(int arr[], int posStart, int posEnd) {
    int acc = arr[posStart];
    int i = posStart + 1;
    while(i <= posEnd) {
        acc <<= 1;
        acc += arr[i];
        i++;
    }
    return acc;
}

int waitUntil(int port, int waitValue, int iterNumber) {
    while(digitalRead(port) != waitValue) {
        if (iterNumber == 0) return -1;
        iterNumber--;  
    }
    return 0;
}
