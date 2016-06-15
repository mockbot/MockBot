String ip = "ws://localhost:9090";
boolean isRunning = false;
int mainLoopVal;

PFont fontA = loadFont("courier");

boolean bumpLeft;
boolean bumpRight;

void setup()
{
  size(500,300);
  background(125);
  fill(255);
  textFont(fontA, 20);
  text("Nothing loaded yet!", 20,20);
  noLoop();

  connect(ip);
  isRunning = false;
}

void draw()
{
}

void run()
{
  println("Start");
  subscribe('/sensorPacket',processSensing);

  frameRate(5);
  loop();
  isRunning = true;
  mainLoopVal = setInterval(enclosure_escape,1000);
}

void stop()
{
  println("Stop");
  move(0,0);

  noLoop();
  isRunning = false;
  clearInterval(mainLoopVal);
}

void move_robot(x,z) {
  publish('/cmd_vel','geometry_msgs/Twist','{"linear":{"x":' + x + ',"y":0,"z":0}, "angular":{"x":0,"y":0,"z":' + z + '}}');
}

void processSensing(sensorPacket)
{
  bumpLeft = sensorPacket.bumpLeft;
  bumpRight = sensorPacket.bumpRight;
}

void enclosure_escape()
{
  if(bumpLeft || bumpRight)
  {
    println("hello create, you have bumped into something");
    x = -0.1;
    z = 0.8;
    background(255,0,0);
    text("hello create, you have bumped", 20,20);
  }
  else
  { 
    println("hello create, you can spin now");
    x = 3;
    z = -10;
    background(0,0,0);
    text("hello create, you can spin", 20,20);
  }
  move_robot(x,z);
}


