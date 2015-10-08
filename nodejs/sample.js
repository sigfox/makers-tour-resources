var libSerial = require("serialport");  
var port = "/dev/tty.usbserial-XXX";  
var serialPort = new libSerial.SerialPort(port, {  
  baudrate: 9600,
    parser: libSerial.parsers.readline("\r")
}, false);  

serialPort.on("data", function(data){
  console.log(data);
});




console.log("Open port: "+ port);  
serialPort.open(function (error) {  
  if (error) {  
    console.log('Failed to open: '+error);  
  } else { 

    console.log("Serial OK :)")
    serialPort.write("AT&V\n", function(err, result){
     if (err){
       console.log("Something bad happened when calling AT&V : %s", err);
     }
    });
    //sendTestFrame(); 
  }
});

function sendTestFrame(){
  var frame = ""+new Date().getTime();
  if (frame.length % 2 === 1){
   //1 hex char = a half-byte. And we only send _full_ bytes ;) . Meaning no odd-length hex frames
   frame = "0"+frame;
  }
  sendSIGFOXFrame(frame);
  
}
function sendSIGFOXFrame(frame){
  console.log("Send %s", frame);
  serialPort.write("AT$SF="+frame+"\n", function(err, result){
     if (err){
       console.log("Something bad happened when sending this frame : [%s]\n\t%s", frame, err);
     }
    }); 
}
