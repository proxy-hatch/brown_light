# brown_light
### Demo Gif
One device picks up the light sensor output on the other, and displays an on/off indicator LED light.
![Demo gif](resource/demo.gif)

### brown_light RX
![Rx Wiring](resource/brown_light_rx_bb.jpg)
### brown_light TX
![Tx Wiring](resource/brown_light_tx_bb.jpg)

Currently tx and rx are configured with hard-coded IP, polling photoresistor value intervally and sending over UPD.

Roadmap: Implement auto IP setup with [Bonjour/Zeroconf](http://gkaindl.com/software/arduino-ethernet/bonjour)
