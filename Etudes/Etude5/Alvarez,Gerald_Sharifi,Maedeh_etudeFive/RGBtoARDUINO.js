var serial;                             // variable to hold an instance of the serialport library
var portName = '/dev/cu.usbmodem1421';  // fill in your serial port name here
var rectY =30;
var rectHeight =200;
var myEllipses =[];
var currentSelected = -1;
var currentIndex =-1;



function setup() {
  colorMode(HSB,255);
  createCanvas(windowWidth, windowHeight);
  serial = new p5.SerialPort();       // make a new instance of the serialport library
 serial.on('list', printList);  // set a callback function for the serialport list event
 serial.on('connected', serverConnected); // callback for connecting to the server
 serial.on('open', portOpen);        // callback for the port opening
 serial.on('data', serialEvent);     // callback for when new data arrives
 serial.on('error', serialError);    // callback for errors
 serial.on('close', portClose);      // callback for the port closing

 serial.list();                      // list the serial ports
 serial.open(portName);              // open a serial port

 for(var i = 0; i< 8; i++)
 {
   // myEllipses.push(new Circle(char(i + 65), (windowHeight/8)+(i*1.10*(windowHeight/4)), windowHeight/4, windowHeight/8));
   myEllipses.push(new Circle(char(i + 65), (windowHeight/8)+(i*1.10*(windowHeight/8)), windowHeight/4, windowHeight/8));
 }
}


function draw()
{
  background(0);
  for(var i = 0; i< 8; i++)
  {
    myEllipses[i].display();
  }

}

/* CALL BACK FUNCTIONS */

function printList(portList) {
  // portList is an array of serial port names
  for (var i = 0; i < portList.length; i++) {
    // Display the list the console:
    println(i + " " + portList[i]);
  }
}

function serverConnected() {
  println('connected to server.');
}

function portOpen() {
  println('the serial port opened.')
}

function serialEvent() {

}

function serialError(err) {
  println('Something went wrong with the serial port. ' + err);
}

function portClose() {
  println('The serial port closed.');
}

function mouseDragged()
{
  for(var i =0; i< 8;i++)
  {
    var dist_Coll  = dist(mouseX, mouseY, myEllipses[i].x,myEllipses[i].y);
    if(abs(dist_Coll)< myEllipses[i].circleSize/2)
    {
       currentSelected=myEllipses[i].index;
        tempX =  mouseX - myEllipses[i].x;
        tempY =  mouseY - myEllipses[i].y;

      //  this.y= -(mouseY - height/2);
        hue = atan2(tempY, tempX); // atan2(y, x) lets you get the angle
        //console.log(degrees(hue));
        hue = map(hue, -PI, PI, 0, 255);
        myEllipses[i].colorFill = color(hue, 255, 255);

        myEllipses[i].r = red(myEllipses[i].colorFill);
        myEllipses[i].g = green(myEllipses[i].colorFill);
        myEllipses[i].b = blue(myEllipses[i].colorFill);
        //console.log(myEllipses[i].r);
       //console.log(myEllipses[i].g);
        //console.log(myEllipses[i].b);
        currentIndex =i;
    }
  }
}

function mouseReleased()
{
  if(currentSelected !=-1)
  {
    console.log(currentSelected);
    console.log(int(myEllipses[currentIndex].r));
    console.log(int(myEllipses[currentIndex].g));
    console.log(int(myEllipses[currentIndex].b));

    serial.write(currentSelected);
    serial.write(int(myEllipses[currentIndex].r));
    serial.write(int(myEllipses[currentIndex].g));
    serial.write(int(myEllipses[currentIndex].b));


  }
}



/*function mouseDragged() {
 // map the mouseY to a range from 0 to 255:

 for(var i =0; i< 1;i++)
 {
   var dist_Coll  = dist(mouseX, mouseY, myEllipses[i].x,myEllipses[i].y);
   if(abs(dist_Coll)< myEllipses[i].circleSize/2)
   {
     console.log(myEllipses[i].index);
     if(myEllipses[i].circleSize<20 || myEllipses[i].circleSize>150)
     {
       myEllipses[i].speed*=-1;

     }
    //myEllipses[i].circleSize+=myEllipses[i].speed;
     serial.write(myEllipses[i].index);
     //console.log(myEllipses[i].circleSize);
      serial.write(floor(map(myEllipses[i].circleSize,20,150,0,180)));
     //break;

   }
 }

 //outByte = int(map(mouseY, 0, height, 0, 255));
 // send it out the serial port:
 //serial.write(outByte);
}*/

function Circle(i,x,y, s)
{
  this.speed =1;
  this.index =i;
  this.x = x;
  this.y = y;
  this.circleSize = s;
  this.colorFill =color(0,0,255);
  this.r =0;
  this.g = 0;
  this.b=0;
  //this.colorFill = color(random(255),random(255),random(255));
  this.display = function()
  {


  fill(this.colorFill);
  noStroke();
  ellipseMode(CENTER);
  ellipse(this.x, this.y, this.circleSize, this.circleSize);
  //textSize(30);
  //text(hue, 25 + mouseX, mouseY);
  //stroke(128);
  //line(width/2, height/2, mouseX, mouseY);


    //fill(this.colorFill);
  //  ellipse(this.x,this.y, this.circleSize,this.circleSize);
  }
}
