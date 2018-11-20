MainController
========================

![MainController](http://engineering3.org/wp-content/uploads/2015/02/Maincontroller_On.jpg)

This is the LabVIEW Control Interface for the RCM Control Stack.


Version History
---------------

* [Version v5.3.2]
  - Changed "Run" Title Bar from SRV MainController (old Surveyor naming convention) to RCM MainController (new E3 naming convention)

* [Version v5.3.1]
  - Changed "Open" Title Bar from SRV MainController (old Surveyor naming convention) to RCM MainController (new E3 naming convention)

* [Version v5.3.0]
  - Adding the ability to work with new sensors (IMU and Thermal)
  - Added check boxes to Analog SensorConfig for I2C Repeated Start, Byte Swap, and Signed/Unsigned
  - Fixed Firmware Flash Error Pop-up
  - Identified a Log Overrun Issue/Pushed to later to address (May 18, 2018)
  - Implemented a new sensors 16-bit ID in the response for all commands (obsoletes the old 'Constant Command' scheme)
  - New 16-bit ID allows RCMx1 digital ports 23-28 to be identified/displayed individually through SensorConfig/SensorView

* [Version v5.2.1]
  - Added Calculated SensorConfig type which lets Multiple SensorView elements respond to a single SensorConfig value
  - Added access to Boolean/LED SensorView elements through analog SensorConfigs/Reads

* [Version 5.1.1]
  - Changed the behavior of boolean sensor indicators to be ON if their value is greater than zero and to be OFF otherwise. This allows a 'threshold exceeded' type of behavior if one were to include the threshold value in the formula for that sensor.
  - Cleaned up the MC_README.vi to include only top-level VIs thus eliminating the reference to deprecated VIs.
  - Deleted many obsoleted and deprecated files from many directories. This includes deleting the following two directories altogether:
      - C:\MainController-master\SRV VIs\OpCodes\
      - C:\MainController-master\SRV VIs\SubVIs\SRV\

* [Version 4.3.3](https://github.com/Engineering-3/MainController) Initial public release, version 4.3.3.  


License Information
-------------------
Firmware is released under [GNU GPL v2](http://www.gnu.org/licenses/old-licenses/gpl-2.0.html).
Distributed as-is; no warranty is given.
