#SmartEverything  - Serial mirror

Use the Arduino Serial Monitor as a command interface for the [Telit](http://www.telit.com/products/product-service-selector/product-service-selector/show/product/le51-868-s/) LE51-868 module.

##Run

* Upload the sketch to your [SmartEverything](http://smarteverything.it)
	* Board Type: Smart Everything (through USB)
* Open the Arduino Serial Monitor
* You should see two messages in the console
	* `** READY **` 
	* ``TLT.xx.yy-Rx`` which is your firmware's version
* Type any AT command in the Serial Monitor, they will be forwarded to the module
	* `AT/L` : outputs the firmware version
	* `AT$SB=0|1` : sends a single bit frame
	* `AT$SF=DEADBEEFCAFE` : sends a SIGFOX frame (hex, up to 12 bytes)
	* `AT$SF=DEADBEEFCAFE,1` : same + asks for a downlink response
		* After ~20seconds, you'll see the received message showing up in the console
		
		
Check the SIGFOX cloud interface to be sure your messages are sent/received as expected