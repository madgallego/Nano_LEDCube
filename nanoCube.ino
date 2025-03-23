int pipe[4][4]={{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, A4, A5}};
int layer[4]={A0, A1, A2, A3};

void setup()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      pinMode(pipe[i][j], OUTPUT);
    }
  }
  for(int i = 0; i < 4; i++)
  {
    pinMode(layer[i], OUTPUT);
  }
}

void loop() //all functions aside from the on/off functions will accept an integer as an argument that tells it how many times to iterate.
            //all functions also include a local variable called time that can be adjusted to affect the speed of the pattern
{
  layeroff();
  pipeoff();

  bounce(5);

  expand(3);

  breathe(10);

  rain(20);

  spiral(4);

  raincube(10);

  delay(1000);
}

void layeron()  //turns on all layers
{
  for (int k = 0; k < 4; k++)
  {
    digitalWrite(layer[k], 1);
  }
}

void layeroff() //turns off all layers
{
  for (int k = 0; k < 4; k++)
  {
    digitalWrite(layer[k], 0);
  }
}

void pipeon() //turns on all pipes
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(pipe[i][j], 0);
    }
  }
}

void pipeoff()  //turns off all pipes
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      digitalWrite(pipe[i][j], 1);
    }
  }
}

void bounce(int bounces) 
{
  int time = 500;
  layeroff();
  pipeon();

  while (bounces > 0)
  {
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(layer[i], 1);
      delay(time * (sqrt(i + 1)-sqrt(i)));
      digitalWrite(layer[i], 0);
    }
    for (int i = 3; i > 0; i--)
    {
      digitalWrite(layer[i], 1);
      delay(time * (sqrt(i + 1)-sqrt(i)));
      digitalWrite(layer[i], 0);
    }
    bounces--;
  }
  digitalWrite(layer[0], 1);
  delay(time);
  layeroff();
  pipeoff();
}

void expand(int iterations)
{
  int time = 250;
  pipeoff();
  layeroff();
  while (iterations > 0)
  {
    for (int size = 0; size < 4; size++)
  {
    digitalWrite(layer[size], 1);
    for (int i = 0; i <= size; i++)
    {
      for (int j = 0; j <= size; j++)
      {
        digitalWrite(pipe[i][j], 0);
      }
    }
    delay(time);
  }

  for (int size = 3; size >= 0; size--)
  {
    digitalWrite(layer[3-size], 0);
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(pipe[i][3-size], 1);
      digitalWrite(pipe[3-size][i], 1);
    }
    delay(time);
  }
  iterations--;
  }
}

void breathe(int breaths)
{
  layeroff();
  pipeoff();
  int time = 500;

  for (int i = 1; i < 3; i++)
  {
    for (int j = 1; j < 3; j++)
    {
      digitalWrite(pipe[i][j], 0);
    }
    digitalWrite(layer[i], 1);
  }


  while (breaths > 0)
  {
    delay(time);
    for (int i = 0; i < 4; i++)
    {
      digitalWrite(pipe[0][i], 0);
      digitalWrite(pipe[3][i], 0);
      digitalWrite(pipe[i][0], 0);
      digitalWrite(pipe[i][3], 0);
    }
    digitalWrite(layer[0], 1);
    digitalWrite(layer[3], 1);

    delay(time);

    for (int i = 0; i < 4; i++)
    {
      digitalWrite(pipe[0][i], 1);
      digitalWrite(pipe[3][i], 1);
      digitalWrite(pipe[i][0], 1);
      digitalWrite(pipe[i][3], 1);
    }
    digitalWrite(layer[0], 0);
    digitalWrite(layer[3], 0);

    breaths--;
  }
}

void rain(int drops)
{
  int time = 150;
  layeroff();
  pipeoff();

  while (drops > 0)
  {
    int i = random(0, 3);
    int j = random(0, 3);

    digitalWrite(pipe[i][j], 0);

    for (int k = 0; k < 4; k++)
    {
      digitalWrite(layer[k], 1);
      delay(time);
      digitalWrite(layer[k], 0);
    }

    digitalWrite(pipe[i][j], 1);

    drops--;
  }
}

void spiral(int turns)
{
  int time = 50;
  pipeoff();
  layeron();

  while (turns > 0)
  {
    //open spiral
    for (int i = 1; i < 3; i++)
    {
      digitalWrite(pipe[2][i], 0);
      delay(time);
    }

    for (int i = 2; i > 0; i--)
    {
      digitalWrite(pipe[1][i], 0);
      delay(time);
    }

    for (int i = 1; i < 4; i++)
    {
      digitalWrite(pipe[i][0], 0);
      delay(time);
    }

    for (int i = 1; i < 4; i++)
    {
      digitalWrite(pipe[3][i], 0);
      delay(time);
    }

    for (int i = 2; i >= 0; i--)
    {
      digitalWrite(pipe[i][3], 0);
      delay(time);
    }

    for (int i = 2; i >= 0; i--)
    {
      digitalWrite(pipe[0][i], 0);
      delay(time);
    }

    //now close spiral
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(pipe[0][i], 1);
      delay(time);
    }

    for (int i = 0; i < 3; i++)
    {
      digitalWrite(pipe[i][3], 1);
      delay(time);
    }

    for (int i = 3; i > 0; i--)
    {
      digitalWrite(pipe[3][i], 1);
      delay(time);
    }

    for (int i = 3; i > 0; i--)
    {
      digitalWrite(pipe[i][0], 1);
      delay(time);
    }

    for (int i = 1; i < 3; i++)
    {
      digitalWrite(pipe[1][i], 1);
      delay(time);
    }

    for (int i = 2; i > 0; i--)
    {
      digitalWrite(pipe[2][i], 1);
      delay(time);
    }

    turns--;
  }
}

void raincube(int cubes)
{
  int time = 350;
  layeroff();
  pipeoff();

  while (cubes > 0)
  {
    int i = random(0, 2);
    int j = random(0, 2);

    
    digitalWrite(pipe[i][j], 0);
    digitalWrite(pipe[i + 1][j], 0);
    digitalWrite(pipe[i][j + 1], 0);
    digitalWrite(pipe[i + 1][j + 1], 0);

    
    for (int k = 0; k < 6; k++)
    {
      if (k < 4)
      {
        digitalWrite(layer[k], 1);
      }
      if (k - 2 > -1)
      {
        digitalWrite(layer[k - 2], 0);
      }
      delay(time);
    }

    pipeoff();
    cubes--;
  }
}